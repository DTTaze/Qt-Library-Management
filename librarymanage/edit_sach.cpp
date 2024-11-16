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
        HienThiThongTinSachTrongEditSach(index_dausach);
        HienThiDanhMucSachTrongEditSach(index_dausach);
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
    ui->spinBox_namsb_1->setReadOnly(true);
    ui->spinBox_sotrang_1->setReadOnly(true);
}

void Edit_sach::MoKhoaEditDauSach(){
    ui->lineEdit_tacgia_1->setReadOnly(false);
    ui->lineEdit_tensach_1->setReadOnly(false);
    ui->lineEdit_theloai_1->setReadOnly(false);
    ui->spinBox_namsb_1->setReadOnly(false);
    ui->spinBox_sotrang_1->setReadOnly(false);
}

void Edit_sach::on_pushButton_ok_clicked()
{
    // Lấy dữ liệu từ các ô input và combobox
    QString ISBN = ui->lineEdit_ISBN_1->text().simplified();
    QString tensach = ui->lineEdit_tensach_1->text().simplified();
    QString tacgia = ui->lineEdit_tacgia_1->text().simplified();
    QString theloai = ui->lineEdit_theloai_1->text().simplified();
    int sotrang = ui->spinBox_sotrang_1->value();
    int namsx = ui->spinBox_namsb_1->value();

    // Chuyển đổi sang string
    string isbnStd = ISBN.toStdString();
    string tensachStd = tensach.toStdString();
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();

    // Biến lưu trữ thông báo lỗi
    QString errorMessage;

    // Kiểm tra từng điều kiện và thêm lỗi vào errorMessage nếu có
    if (ISBN.isEmpty()) {
        QMessageBox::warning(this,"Cảnh báo", "Bạn chưa điền ISBN.\n");
        return;
    } else if (int i = TimKiemViTriDauSach(isbnStd) == -1) {
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

    if (namsx <= 0) {
        errorMessage += "Năm xuất bản phải lớn hơn 0.\n";
    }

    // Nếu có lỗi, hiển thị thông báo và thoát hàm
    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", errorMessage);
        return;
    }

    string ma_isbn = ui->lineEdit_ISBN_1->text().toStdString();
    int index_dausach = TimKiemViTriDauSach(ma_isbn);
    danh_sach_dau_sach.node[index_dausach]->tensach = tensachStd;
    danh_sach_dau_sach.node[index_dausach]->tacgia = tacgiaStd;
    danh_sach_dau_sach.node[index_dausach]->theloai = theloaiStd;
    danh_sach_dau_sach.node[index_dausach]->sotrang = sotrang;
    danh_sach_dau_sach.node[index_dausach]->namsx = namsx;

    // Đóng hộp thoại sau khi thêm thành công
    accept();
}


void Edit_sach::on_pushButton_cancel_clicked()
{
    close();
}

void Edit_sach::HienThiDanhMucSachTrongEditSach(int index_dausach){
    int row = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[index_dausach]->dms; cur != nullptr; cur = cur->next){
        row = ui->tableWidget_danhmucsach_1->rowCount();
        ui->tableWidget_danhmucsach_1->insertRow(row);

        // Cột 0 - Mã sách (không chỉnh sửa)
        QTableWidgetItem *itemMaSach = new QTableWidgetItem(QString::fromStdString(cur->masach));
        itemMaSach->setFlags(itemMaSach->flags() & ~Qt::ItemIsEditable); // Không cho chỉnh sửa
        ui->tableWidget_danhmucsach_1->setItem(row, 0, itemMaSach);

        // Cột 1 - Vị trí (có thể chỉnh sửa)
        ui->tableWidget_danhmucsach_1->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        // Cột 2 - Trạng thái (không chỉnh sửa)
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

void Edit_sach::HienThiThongTinSachTrongEditSach(int index_dausach){
    ui->lineEdit_tacgia_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tacgia));
    ui->lineEdit_tensach_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tensach));
    ui->lineEdit_theloai_1->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->theloai));
    ui->spinBox_namsb_1->setValue(danh_sach_dau_sach.node[index_dausach]->namsx);
    ui->spinBox_sotrang_1->setValue(danh_sach_dau_sach.node[index_dausach]->sotrang);
    HienThiDanhMucSachTrongEditSach(index_dausach);
}

void Edit_sach::XoaThongTinTrongEditSach(){
    ui->lineEdit_tacgia_1->setText("");
    ui->lineEdit_tensach_1->setText("");
    ui->lineEdit_theloai_1->setText("");
    ui->spinBox_namsb_1->setValue(0);
    ui->spinBox_sotrang_1->setValue(0);
    ui->tableWidget_danhmucsach_1->clearContents();
    ui->tableWidget_danhmucsach_1->setRowCount(0);
}
void Edit_sach::on_lineEdit_ISBN_1_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        // Nếu text rỗng, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_1->setStyleSheet("");
        XoaThongTinTrongEditSach();
        return;
    }

    QString LocKiTu;
    int cursorPosition = ui->lineEdit_ISBN_1->cursorPosition();

    // Lọc ký tự hợp lệ là chữ số
    LocKiTuISBNHopLe(text, LocKiTu);

    // Cập nhật nội dung của lineEdit với các ký tự hợp lệ
    ui->lineEdit_ISBN_1->setText(LocKiTu);

    // Thiết lập lại vị trí con trỏ
    ui->lineEdit_ISBN_1->setCursorPosition(qMin(cursorPosition, LocKiTu.length()));

    string ma_isbn_hople = LocKiTu.toStdString();
    int index = TimKiemViTriDauSach(ma_isbn_hople);

    // Kiểm tra và đặt màu nền cho lineEdit dựa vào điều kiện
    if (LocKiTu.length() == 0) {
        // Nếu ISBN rỗng sau khi lọc, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_1->setStyleSheet("");
        XoaThongTinTrongEditSach();
    } else if (index != -1) {

        ui->lineEdit_ISBN_1->setStyleSheet("background-color: lightgreen;");
        HienThiThongTinSachTrongEditSach(index);
        MoKhoaEditDauSach();
    } else {
        // ISBN đã tồn tại, đặt nền đỏ và khóa nhập đầu sách
        ui->lineEdit_ISBN_1->setStyleSheet("background-color: lightcoral;");
        KhoaEditDauSach();
        XoaThongTinTrongEditSach();
    }
}



void Edit_sach::on_spinBox_namsb_1_valueChanged(int arg1)
{
    if(arg1 != 0){
        // Lay nam hien tai
        std::time_t now = std::time(0);
        std::tm *localTime = std::localtime(&now);
        int currentYear = localTime->tm_year + 1900; // Nam hien tai
        // Kiểm tra xem năm nhập vào có lớn hơn năm hiện tại không
        if (arg1 > currentYear) {
            // Nếu lớn hơn năm hiện tại, thông báo và đặt lại giá trị
            QMessageBox::warning(this, "Lỗi", "Năm không hợp lệ! Vui lòng nhập lại.");

            // Đặt lại giá trị cho QSpinBox về năm hiện tại
            ui->spinBox_namsb_1->setValue(currentYear);
        }
    }
}

void Edit_sach::on_lineEdit_tensach_1_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        string valid_key ;
        int cursorPosition = ui->lineEdit_tensach_1->cursorPosition(); // Lưu vị trí con trỏ

        LocKiTuTensachHopLe(text,valid_key);
        // Cập nhật lại tên sách vào QLineEdit
        ui->lineEdit_tensach_1->setText(QString::fromStdString(valid_key));

        // Đặt lại vị trí con trỏ
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

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu
        // Cập nhật lại tên thể loại vào QLineEdit
        ui->lineEdit_theloai_1->setText(QString::fromStdString(valid_key));
    }
}

void Edit_sach::on_lineEdit_tacgia_1_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString key = RemoveSpace(text);
        key = CapitalizeWords(key);
        string valid_key = key.toStdString();

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu
        // Cập nhật lại tên thể loại vào QLineEdit
        ui->lineEdit_tacgia_1->setText(QString::fromStdString(valid_key));
    }
}

void Edit_sach::on_tableWidget_danhmucsach_1_itemChanged(QTableWidgetItem *item)
{
    if(item->isSelected()){
        QString text = item->text();
        string ma_sach = ui->tableWidget_danhmucsach_1->item(item->row(),0)->text().toStdString();
        DanhMucSach* danh_muc_sach = DanhMucSachTrongDauSach(ma_sach);
        if(!text.isEmpty()){
            string key = text.toStdString();

            // Chỉ cho phép một ký tự
            if (key.length() > 1) {
                QMessageBox::warning(this,"Cảnh báo","Vị trí chỉ chứa 1 kí tự.");
                string vi_tri_ban_dau = danh_muc_sach->vitri;
                item->setText(QString::fromStdString(vi_tri_ban_dau));
                return;
            }

            // Kiểm tra nếu ký tự là a-z hoặc A-Z
            if (!key.empty() && (isalpha(key[0]))) {
                // Chuyển ký tự thành in hoa
                key[0] = toupper(key[0]); // Chuyển đổi ký tự thành chữ in hoa
            } else {
                QMessageBox::warning(this,"Cảnh báo","Vui lòng chọn từ a-z hoặc A-Z.");
                string vi_tri_ban_dau = danh_muc_sach->vitri;
                item->setText(QString::fromStdString(vi_tri_ban_dau));
                return;
            }

            danh_muc_sach->vitri = key[0];
            // Cập nhật lại giá trị trong lineEdit
            item->setText(QString::fromStdString(key));
        }else{
            string vi_tri_ban_dau = danh_muc_sach->vitri;
            item->setText(QString::fromStdString(vi_tri_ban_dau));
            return;
        }
    }
}


