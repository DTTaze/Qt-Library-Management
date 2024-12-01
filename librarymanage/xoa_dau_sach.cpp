#include "xoa_dau_sach.h"
#include "ui_xoa_dau_sach.h"
#include "Dau_sach.h"

Xoa_dau_sach::Xoa_dau_sach(int index,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Xoa_dau_sach)
    , index_dausach(index)
{
    ui->setupUi(this);
    ui->lineEdit_tacgia_2->setReadOnly(true);
    ui->lineEdit_tensach_2->setReadOnly(true);
    ui->lineEdit_theloai_2->setReadOnly(true);
    ui->spinBox_namxb_2->setReadOnly(true);
    ui->spinBox_sotrang_2->setReadOnly(true);

    if(index_dausach != -1){
        ui->lineEdit_ISBN_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->ISBN));
    }
}

Xoa_dau_sach::~Xoa_dau_sach()
{
    delete ui;
}

void Xoa_dau_sach::HienThiDanhMucSachTrongXoaSach(int index_dausach){
    int row = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[index_dausach]->dms; cur != nullptr; cur = cur->next){
        row = ui->tableWidget_danhmucsach_2->rowCount();
        ui->tableWidget_danhmucsach_2->insertRow(row);

        // Cột 0 - Mã sách (không chỉnh sửa)
        QTableWidgetItem *itemMaSach = new QTableWidgetItem(QString::fromStdString(cur->masach));
        itemMaSach->setFlags(itemMaSach->flags() & ~Qt::ItemIsEditable); // Không cho chỉnh sửa
        ui->tableWidget_danhmucsach_2->setItem(row, 0, itemMaSach);

        // Cột 1 - Vị trí (có thể chỉnh sửa)
        ui->tableWidget_danhmucsach_2->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        // Cột 2 - Trạng thái (không chỉnh sửa)
        int trangthai = cur->trangthai;
        QString trang_thai_qt;
        switch(trangthai) {
        case 0: trang_thai_qt = "Có thể mượn"; break;
        case 1: trang_thai_qt = "Đã được mượn"; break;
        case 2: trang_thai_qt = "Đã thanh lý"; break;
        }
        ui->tableWidget_danhmucsach_2->setItem(row, 2, new QTableWidgetItem(trang_thai_qt));
    }

    ui->tableWidget_danhmucsach_2->resizeColumnsToContents();
    ui->tableWidget_danhmucsach_2->setColumnWidth(0,200);
}

void Xoa_dau_sach::HienThiThongTinSachTrongXoatSach(int index_dausach){
    ui->lineEdit_tacgia_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tacgia));
    ui->lineEdit_tensach_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tensach));
    ui->lineEdit_theloai_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->theloai));
    ui->spinBox_namxb_2->setValue(danh_sach_dau_sach.node[index_dausach]->namxb);
    ui->spinBox_sotrang_2->setValue(danh_sach_dau_sach.node[index_dausach]->sotrang);
    HienThiDanhMucSachTrongXoaSach(index_dausach);
}

void Xoa_dau_sach::XoaThongTinTrongXoaSach(){
    ui->lineEdit_tacgia_2->setText("");
    ui->lineEdit_tensach_2->setText("");
    ui->lineEdit_theloai_2->setText("");
    ui->spinBox_namxb_2->setValue(0);
    ui->spinBox_sotrang_2->setValue(0);
    ui->tableWidget_danhmucsach_2->clearContents();
    ui->tableWidget_danhmucsach_2->setRowCount(0);
}



void Xoa_dau_sach::on_lineEdit_ISBN_2_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        // Nếu text rỗng, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_2->setStyleSheet("");
        XoaThongTinTrongXoaSach();
        return;
    }

    QString LocKiTu;
    int cursorPosition = ui->lineEdit_ISBN_2->cursorPosition();
    int removedChars = 0;
    // Lọc ký tự hợp lệ là chữ số
    LocKiTuISBNHopLe(text,LocKiTu,cursorPosition,removedChars);

    ui->lineEdit_ISBN_2->blockSignals(true);
    ui->lineEdit_ISBN_2->setText(LocKiTu);
    ui->lineEdit_ISBN_2->blockSignals(false);

    cursorPosition -= removedChars;
    if (cursorPosition < 0) {
        cursorPosition = 0;
    } else if (cursorPosition > LocKiTu.length()) {
        cursorPosition = LocKiTu.length();
    }
    // Thiết lập lại vị trí con trỏ
    ui->lineEdit_ISBN_2->setCursorPosition(cursorPosition);

    string ma_isbn_hople = LocKiTu.toStdString();
    int index = TimKiemViTriDauSach(ma_isbn_hople);

    // Kiểm tra và đặt màu nền cho lineEdit dựa vào điều kiện
    if (LocKiTu.length() == 0) {
        // Nếu ISBN rỗng sau khi lọc, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_2->setStyleSheet("");
        XoaThongTinTrongXoaSach();
    } else if (index != -1) {

        ui->lineEdit_ISBN_2->setStyleSheet("background-color: lightgreen;");
        HienThiThongTinSachTrongXoatSach(index);
    } else {
        // ISBN đã tồn tại, đặt nền đỏ và khóa nhập đầu sách
        ui->lineEdit_ISBN_2->setStyleSheet("background-color: lightcoral;");
        XoaThongTinTrongXoaSach();
    }
}


void Xoa_dau_sach::on_pushButton_cancel_2_clicked()
{
    close();
}

void Xoa_dau_sach::on_pushButton_XoaDauSacg_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa",
                                  "Bạn có chắc chắn muốn xóa đầu sách này không?",
                                  QMessageBox::Yes | QMessageBox::No);


    if (reply == QMessageBox::Yes) {
        XoaDauSach(index_dausach);
        QMessageBox::information(this,"Thông báo","Đã xóa Đầu sách thành công");
        accept();  // Đồng ý và tiếp tục
    } else {
        // Nếu người dùng chọn No
        return;  // Không làm gì và thoát
    }
}

