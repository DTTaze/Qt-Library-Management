#include "edit_sach.h"
#include "ui_edit_sach.h"

Edit_sach::Edit_sach(int index,QWidget *parent)
    : QDialog(parent)
    , index_dausach(index)
    , ui(new Ui::Edit_sach)
{
    ui->setupUi(this);
    if(index_dausach != -1){
        ui->lineEdit_ISBN_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->ISBN));
    }
}

Edit_sach::~Edit_sach()
{
    delete ui;
}

void Edit_sach::KhoaEditDauSach(){
    ui->lineEdit_tacgia_1->setReadOnly(true);
    ui->lineEdit_tensach_1->setReadOnly(true);
    ui->lineEdit_theloai_1->setReadOnly(true);
    ui->spinBox_namxb_1->setReadOnly(true);
    ui->spinBox_sotrang_1->setReadOnly(true);
}

void Edit_sach::MoKhoaEditDauSach(){
    ui->lineEdit_tacgia_1->setReadOnly(false);
    ui->lineEdit_tensach_1->setReadOnly(false);
    ui->lineEdit_theloai_1->setReadOnly(false);
    ui->spinBox_namxb_1->setReadOnly(false);
    ui->spinBox_sotrang_1->setReadOnly(false);
}

void Edit_sach::HienThiThongTinSachTrongEditSach(int index_dausach){
    ui->lineEdit_tacgia_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tacgia));
    ui->lineEdit_tensach_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tensach));
    ui->lineEdit_theloai_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->theloai));
    ui->spinBox_namxb_1->setValue(danh_sach_dau_sach.node[index_dausach]->namxb);
    ui->spinBox_sotrang_1->setValue(danh_sach_dau_sach.node[index_dausach]->sotrang);
    HienThiDanhMucSachTrongEditSach(index_dausach);
}

void Edit_sach::HienThiDanhMucSachTrongEditSach(int index_dausach){
    int row = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[index_dausach]->dms; cur != nullptr; cur = cur->next){
        row = ui->tableWidget_danhmucsach_1->rowCount();
        ui->tableWidget_danhmucsach_1->insertRow(row);

        QTableWidgetItem *itemMaSach = new QTableWidgetItem(QString::fromStdString(cur->masach));
        itemMaSach->setFlags(itemMaSach->flags() & ~Qt::ItemIsEditable); // Không cho chỉnh sửa
        ui->tableWidget_danhmucsach_1->setItem(row, 0, itemMaSach);

        ui->tableWidget_danhmucsach_1->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        int trangthai = cur->trangthai;
        QString trang_thai_qt;
        switch(trangthai) {
        case 0: trang_thai_qt = "Có thể mượn"; break;
        case 1: trang_thai_qt = "Đã được mượn"; break;
        case 2: trang_thai_qt = "Đã thanh lý"; break;
        }
        QTableWidgetItem *itemTrangThai = new QTableWidgetItem(trang_thai_qt);
        itemTrangThai->setFlags(itemTrangThai->flags() & ~Qt::ItemIsEditable); // Không cho chỉnh sửa
        ui->tableWidget_danhmucsach_1->setItem(row, 2, itemTrangThai);
    }

    ui->tableWidget_danhmucsach_1->resizeColumnsToContents();
    ui->tableWidget_danhmucsach_1->setColumnWidth(0,200);
}

void Edit_sach::XoaThongTinTrongEditSach(){
    ui->lineEdit_tacgia_1->setText("");
    ui->lineEdit_tensach_1->setText("");
    ui->lineEdit_theloai_1->setText("");
    ui->spinBox_namxb_1->setValue(0);
    ui->spinBox_sotrang_1->setValue(0);
    ui->tableWidget_danhmucsach_1->clearContents();
    ui->tableWidget_danhmucsach_1->setRowCount(0);
}

void Edit_sach::on_pushButton_ok_clicked()
{
    QString ISBN = ui->lineEdit_ISBN_1->text().simplified();
    QString tensach = ui->lineEdit_tensach_1->text().simplified();
    QString tacgia = ui->lineEdit_tacgia_1->text().simplified();
    QString theloai = ui->lineEdit_theloai_1->text().simplified();
    int sotrang = ui->spinBox_sotrang_1->value();
    int namxb = ui->spinBox_namxb_1->value();

    string isbnStd = ISBN.toStdString();
    string tensachStd = tensach.toStdString();
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();

    QString errorMessage;

    int index_dausach = TimKiemViTriDauSach(isbnStd);
    if (ISBN.isEmpty()) {
        QMessageBox::warning(this,"Cảnh báo", "Bạn chưa điền ISBN.\n");
        return;
    } else if ( index_dausach == -1) {
        QMessageBox::warning(this,"Cảnh báo", "Mã đầu sách không tồn tại.");
        return;
    } else if (!MaISBNQTHopLe(ISBN)) {
        QMessageBox::warning(this,"Cảnh báo", "Mã không hợp lệ.");
        return;
    }

    QString messages[] = {
        "Tên sách rỗng.\n",
        "Tên tác giả rỗng.\n",
        "Thể loại rỗng.\n",
    };
    string inputs[] = {tensachStd, tacgiaStd, theloaiStd};

    for (int i = 0; i < 3; ++i) {
        if (inputs[i].empty()) {
            errorMessage += messages[i];
        }
    }

    if (sotrang <= 0) {
        errorMessage += "Số trang phải lớn hơn 0.\n";
    }

    if (namxb <= 0) {
        errorMessage += "Năm xuất bản phải lớn hơn 0.\n";
    }

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", errorMessage);
        return;
    }

    if(danh_sach_dau_sach.node[index_dausach]->tensach != tensachStd){
        ChenDauSachSauKhiThayDoi(tensachStd,index_dausach);
        danh_sach_dau_sach.node[index_dausach]->tensach = tensachStd;
    }
    danh_sach_dau_sach.node[index_dausach]->tacgia = tacgiaStd;
    danh_sach_dau_sach.node[index_dausach]->theloai = theloaiStd;
    danh_sach_dau_sach.node[index_dausach]->sotrang = sotrang;
    danh_sach_dau_sach.node[index_dausach]->namxb = namxb;

    accept();
}


void Edit_sach::on_pushButton_cancel_clicked()
{
    close();
}

void Edit_sach::on_lineEdit_ISBN_1_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        ui->lineEdit_ISBN_1->setStyleSheet("");
        XoaThongTinTrongEditSach();
        return;
    }

    QString LocKiTu;
    int cursorPosition = ui->lineEdit_ISBN_1->cursorPosition();

    LocKiTuISBNHopLe(text, LocKiTu);

    ui->lineEdit_ISBN_1->setText(LocKiTu);

    ui->lineEdit_ISBN_1->setCursorPosition(qMin(cursorPosition, LocKiTu.length()));

    string ma_isbn_hople = LocKiTu.toStdString();
    int index = TimKiemViTriDauSach(ma_isbn_hople);

    if (LocKiTu.length() == 0) {
        ui->lineEdit_ISBN_1->setStyleSheet("");
        XoaThongTinTrongEditSach();
    } else if (index != -1) {

        ui->lineEdit_ISBN_1->setStyleSheet("background-color: lightgreen;");
        HienThiThongTinSachTrongEditSach(index);
        MoKhoaEditDauSach();
    } else {
        ui->lineEdit_ISBN_1->setStyleSheet("background-color: lightcoral;");
        KhoaEditDauSach();
        XoaThongTinTrongEditSach();
    }
}



void Edit_sach::on_spinBox_namxb_1_valueChanged(int arg1)
{
    if(arg1 != 0){
        std::time_t now = std::time(0);
        std::tm *localTime = std::localtime(&now);
        int currentYear = localTime->tm_year + 1900;
        if (arg1 > currentYear) {
            QMessageBox::warning(this, "Lỗi", "Năm không hợp lệ! Vui lòng nhập lại.");
            ui->spinBox_namxb_1->setValue(currentYear);
        }
    }
}

void Edit_sach::on_lineEdit_tensach_1_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        string valid_key ;
        int cursorPosition = ui->lineEdit_tensach_1->cursorPosition(); // Lưu vị trí con trỏ

        LocKiTuTensachHopLe(text,valid_key);
        ui->lineEdit_tensach_1->setText(QString::fromStdString(valid_key));
        if (cursorPosition < valid_key.length()) {
            ui->lineEdit_tensach_1->setCursorPosition(cursorPosition);
        } else {
            ui->lineEdit_tensach_1->setCursorPosition(valid_key.length());
        }
    }
}


void Edit_sach::on_lineEdit_theloai_1_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString key = RemoveSpace(text);
        key = CapitalizeWords(key);
        string valid_key = key.toStdString();

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));
        ui->lineEdit_theloai_1->setText(QString::fromStdString(valid_key));
    }
}

void Edit_sach::on_lineEdit_tacgia_1_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString key = RemoveSpace(text);
        key = CapitalizeWords(key);
        string valid_key = key.toStdString();

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));
        ui->lineEdit_tacgia_1->setText(QString::fromStdString(valid_key));
    }
}

void Edit_sach::on_tableWidget_danhmucsach_1_itemChanged(QTableWidgetItem *item)
{
    if(item->isSelected()){
        QString text = item->text();
        string ma_sach = ui->tableWidget_danhmucsach_1->item(item->row(),0)->text().toStdString();
        DanhMucSach* danh_muc_sach = TimDiaChiSachTrongDanhMucSach(ma_sach);
        if(!text.isEmpty()){
            string key = text.toStdString();

            if (key.length() > 1) {
                QMessageBox::warning(this,"Cảnh báo","Vị trí chỉ chứa 1 kí tự.");
                string vi_tri_ban_dau = danh_muc_sach->vitri;
                item->setText(QString::fromStdString(vi_tri_ban_dau));
                return;
            }

            if (!key.empty() && (isalpha(key[0]))) {
                key[0] = toupper(key[0]);
            } else {
                QMessageBox::warning(this,"Cảnh báo","Vui lòng chọn từ a-z hoặc A-Z.");
                string vi_tri_ban_dau = danh_muc_sach->vitri;
                item->setText(QString::fromStdString(vi_tri_ban_dau));
                return;
            }

            danh_muc_sach->vitri = key[0];
            item->setText(QString::fromStdString(key));
        }else{
            string vi_tri_ban_dau = danh_muc_sach->vitri;
            item->setText(QString::fromStdString(vi_tri_ban_dau));
            return;
        }
    }
}


