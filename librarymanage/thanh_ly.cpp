#include "thanh_ly.h"
#include "ui_thanh_ly.h"

Thanh_ly::Thanh_ly(int DS_vitri,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Thanh_ly)
    , vi_tri_DS(DS_vitri)
{
    ui->setupUi(this);
    if(vi_tri_DS != -1){
        ui->lineEdit_ISBN->setText(QString::fromStdString(danh_sach_dau_sach.node[vi_tri_DS]->ISBN));
    }else{
        XoaThongTinTrongThanhLySach();
    }
}

Thanh_ly::~Thanh_ly()
{
    delete ui;

}

void Thanh_ly::KhoaThanhLyDauSach(){
    ui->lineEdit_tensach->setReadOnly(true);
    ui->lineEdit_sotrang->setReadOnly(true);
    ui->lineEdit_tacgia->setReadOnly(true);
    ui->lineEdit_namsb->setReadOnly(true);
    ui->lineEdit_theloai->setReadOnly(true);
}

void Thanh_ly::XoaThongTinTrongThanhLySach(){
    ui->lineEdit_tacgia->setText("");
    ui->lineEdit_tensach->setText("");
    ui->lineEdit_theloai->setText("");
    ui->lineEdit_namsb->setText("0");
    ui->lineEdit_sotrang->setText("0");
    ui->tableWidget_thanhly->clearContents();
    ui->tableWidget_thanhly->setRowCount(0);
}

void Thanh_ly::HienThongtinSachTonTai(int vi_tri){
    // Thiết lập các QLineEdit chỉ đọc
    KhoaThanhLyDauSach();
    ui->lineEdit_tensach->setText(QString::fromStdString(danh_sach_dau_sach.node[vi_tri]->tensach));
    ui->lineEdit_sotrang->setText(QString::number(danh_sach_dau_sach.node[vi_tri]->sotrang));
    ui->lineEdit_tacgia->setText(QString::fromStdString(danh_sach_dau_sach.node[vi_tri]->tacgia));
    ui->lineEdit_namsb->setText(QString::number(danh_sach_dau_sach.node[vi_tri]->namsx));
    ui->lineEdit_theloai->setText(QString::fromStdString(danh_sach_dau_sach.node[vi_tri]->theloai));

    int row_count = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[vi_tri]->dms; cur != nullptr && row_count < danh_sach_dau_sach.node[vi_tri]->SoLuongSachTrongDausach;cur = cur->next , row_count++){
        ui->tableWidget_thanhly->insertRow(row_count);
        // Kiểm tra trạng thái
        if (cur->trangthai == 0) {
            // Tạo một checkbox chỉ khi trạng thái là 0
            QCheckBox* checkBox = new QCheckBox();
            checkBox->setChecked(false); // Đặt checkbox ban đầu là unchecked

            // Đặt checkbox vào ô đầu tiên của hàng
            ui->tableWidget_thanhly->setCellWidget(row_count, 0, checkBox);
        } else {
            // Nếu trạng thái không phải 0, để ô đầu tiên trống
            ui->tableWidget_thanhly->setCellWidget(row_count, 0, nullptr); // Để ô đầu tiên trống
        }

        ui->tableWidget_thanhly->setItem(row_count, 1 , new QTableWidgetItem(QString::fromStdString(cur->masach)));
        ui->tableWidget_thanhly->setItem(row_count, 2 , new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        QString trang_thai_std;
        switch (cur->trangthai){
        case 0:trang_thai_std = "Có thể mượn";break;
        case 1:trang_thai_std = "Đã được mượn";break;
        case 2:trang_thai_std = "Đã thanh lý";break;
        }
        ui->tableWidget_thanhly->setItem(row_count, 3 , new QTableWidgetItem(trang_thai_std));
    }
    ui->tableWidget_thanhly->resizeColumnsToContents();
    ui->tableWidget_thanhly->setColumnWidth(1,160);
}


void Thanh_ly::on_lineEdit_ISBN_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        ui->lineEdit_ISBN->setStyleSheet("");
        XoaThongTinTrongThanhLySach();
        return;
    }

    QString LocKiTu;
    int cursorPosition = ui->lineEdit_ISBN->cursorPosition();

    LocKiTuISBNHopLe(text, LocKiTu);

    ui->lineEdit_ISBN->setText(LocKiTu);

    ui->lineEdit_ISBN->setCursorPosition(qMin(cursorPosition, LocKiTu.length()));

    string ma_isbn_hople = LocKiTu.toStdString();
    int index = TimKiemViTriDauSach(ma_isbn_hople);

    // Kiểm tra và đặt màu nền cho lineEdit dựa vào điều kiện
    if (LocKiTu.length() == 0) {
        // Nếu ISBN rỗng sau khi lọc, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN->setStyleSheet("");
        XoaThongTinTrongThanhLySach();
    } else if (index != -1) {
        ui->lineEdit_ISBN->setStyleSheet("background-color: lightgreen;");
        HienThongtinSachTonTai(index);;
    } else {
        // ISBN đã tồn tại, đặt nền đỏ và khóa nhập đầu sách
        ui->lineEdit_ISBN->setStyleSheet("background-color: lightcoral;");
        XoaThongTinTrongThanhLySach();
    }
}

void Thanh_ly::on_pushButton_thanhly_clicked()
{
    int sach_thanh_ly = 0;
    int rowCount = ui->tableWidget_thanhly->rowCount(); // Lấy số hàng trong bảng

    if (rowCount == 0) {QMessageBox::warning(this, "Cảnh báo", "Không có sách để thanh lý");return;}

    for (int row = 0; row < rowCount; ++row) {
        QWidget *widget = ui->tableWidget_thanhly->cellWidget(row, 0); // Lấy widget trong ô này

        if (QCheckBox *checkBox = qobject_cast<QCheckBox*>(widget)) { // Kiểm tra nếu widget là QCheckBox
            if (checkBox->isChecked()) { // Nếu checkbox đã được tích chọn

                QString ma_sach = ui->tableWidget_thanhly->item(row,1)->text();
                string ma_sachstd = ma_sach.toStdString();

                for (DanhMucSach* cur = danh_sach_dau_sach.node[vi_tri_DS]->dms;cur!=nullptr;cur=cur->next){
                    if(cur->masach == ma_sachstd){
                        cur->trangthai = 2;
                    }
                }

                sach_thanh_ly++;
            }
        }
    }

    if (sach_thanh_ly > 0){
        QString message = QString("Số lượng sách thanh lý: %1").arg(sach_thanh_ly);
        QMessageBox::information(this, "Thông báo", message);

        accept();
    }else QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn sách thanh lý ");return;
}


void Thanh_ly::on_pushButton_cancel_clicked()
{
    close();
}


void Thanh_ly::on_pushButton_chontatca_clicked()
{
    int rowCount = ui->tableWidget_thanhly->rowCount(); // Lấy số hàng trong bảng
    if (rowCount == 0) {QMessageBox::warning(this, "Cảnh báo", "Không có sách để chọn");return;}
    for (int row = 0; row < rowCount; ++row) {
        QWidget *widget = ui->tableWidget_thanhly->cellWidget(row, 0); // Lấy widget trong ô này

        if (QCheckBox *checkBox = qobject_cast<QCheckBox*>(widget)) { // Kiểm tra nếu widget là QCheckBox
            checkBox->setChecked(true); // Tích chọn checkbox
        }
    }
}



void Thanh_ly::on_pushButton_bochon_clicked()
{
    int rowCount = ui->tableWidget_thanhly->rowCount(); // Lấy số hàng trong bảng
    if (rowCount == 0) {QMessageBox::warning(this, "Cảnh báo", "Không có sách để xóa");return;}
    for (int row = 0; row < rowCount; ++row) {
        QWidget *widget = ui->tableWidget_thanhly->cellWidget(row, 0); // Lấy widget trong ô này

        if (QCheckBox *checkBox = qobject_cast<QCheckBox*>(widget)) { // Kiểm tra nếu widget là QCheckBox
            checkBox->setChecked(false); // Tích chọn checkbox
        }
    }
}



