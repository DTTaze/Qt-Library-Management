#include "nhap_dausach.h"
#include "ui_nhap_dausach.h"

nhap_dausach::nhap_dausach(int index,QWidget *parent)
    : QDialog(parent)
    , index_dausach(index)
    , ui(new Ui::nhap_dausach)
{
    ui->setupUi(this);
    KhoaNhapDauSach();

    if(index_dausach != -1){
        ui->lineEdit_ISBN_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->ISBN));
    }else{
        XoaThongTinTrongNhapDauSach();
    }
}

nhap_dausach::~nhap_dausach()
{
    delete ui;
}

void nhap_dausach::KhoaNhapDauSach(){
    ui->lineEdit_tacgia_2->setReadOnly(true);
    ui->lineEdit_tensach_2->setReadOnly(true);
    ui->lineEdit_theloai_2->setReadOnly(true);
    ui->spinBox_namsb_2->setReadOnly(true);
    ui->spinBox_sotrang_2->setReadOnly(true);
    ui->comboBox_vitri_2->setEnabled(false);
    ui->spinBox_soluong_2->setReadOnly(true);
}

void nhap_dausach::MoKhoaNhapDauSach(){
    ui->comboBox_vitri_2->setEnabled(true);
    ui->spinBox_soluong_2->setReadOnly(false);
}

void nhap_dausach::XoaThongTinTrongNhapDauSach(){
    ui->lineEdit_tacgia_2->setText("");
    ui->lineEdit_tensach_2->setText("");
    ui->lineEdit_theloai_2->setText("");
    ui->spinBox_namsb_2->setValue(0);
    ui->spinBox_sotrang_2->setValue(0);
    ui->comboBox_vitri_2->setCurrentText("");
}

void nhap_dausach::HienThiThongTinSachTrongNhapDauSach(int index_dausach){
    ui->lineEdit_tacgia_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tacgia));
    ui->lineEdit_tensach_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->tensach));
    ui->lineEdit_theloai_2->setText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->theloai));
    ui->comboBox_vitri_2->setCurrentText(QString::fromStdString(danh_sach_dau_sach.node[index_dausach]->dms->vitri));
    ui->spinBox_namsb_2->setValue(danh_sach_dau_sach.node[index_dausach]->namsx);
    ui->spinBox_sotrang_2->setValue(danh_sach_dau_sach.node[index_dausach]->sotrang);
}

void nhap_dausach::on_lineEdit_ISBN_2_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        // Nếu text rỗng, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_2->setStyleSheet("");
        XoaThongTinTrongNhapDauSach();
        return;
    }

    QString LocKiTu;
    int cursorPosition = ui->lineEdit_ISBN_2->cursorPosition();

    // Lọc ký tự hợp lệ là chữ số
    LocKiTuISBNHopLe(text, LocKiTu);

    // Cập nhật nội dung của lineEdit với các ký tự hợp lệ
    ui->lineEdit_ISBN_2->setText(LocKiTu);

    // Thiết lập lại vị trí con trỏ
    ui->lineEdit_ISBN_2->setCursorPosition(qMin(cursorPosition, LocKiTu.length()));

    string ma_isbn_hople = LocKiTu.toStdString();
    int index = TimKiemViTriDauSach(ma_isbn_hople);

    // Kiểm tra và đặt màu nền cho lineEdit dựa vào điều kiện
    if (LocKiTu.length() == 0) {
        // Nếu ISBN rỗng sau khi lọc, đặt màu nền về mặc định và xóa nội dung của tableWidget
        ui->lineEdit_ISBN_2->setStyleSheet("");
        XoaThongTinTrongNhapDauSach();
    } else if (index != -1) {

        ui->lineEdit_ISBN_2->setStyleSheet("background-color: lightgreen;");
        HienThiThongTinSachTrongNhapDauSach(index);
        MoKhoaNhapDauSach();
    } else {
        // ISBN đã tồn tại, đặt nền đỏ và khóa nhập đầu sách
        ui->lineEdit_ISBN_2->setStyleSheet("background-color: lightcoral;");
        KhoaNhapDauSach();
        XoaThongTinTrongNhapDauSach();
    }
}


void nhap_dausach::on_pushButton_cancel_clicked()
{
    close();
}


void nhap_dausach::on_pushButton_nhap_clicked()
{
    // Lấy dữ liệu từ các ô input và combobox
    QString ISBN = ui->lineEdit_ISBN_2->text().simplified();
    QString tensach = ui->lineEdit_tensach_2->text().simplified();
    QString tacgia = ui->lineEdit_tacgia_2->text().simplified();
    QString theloai = ui->lineEdit_theloai_2->text().simplified();
    QString vitri = ui->comboBox_vitri_2->currentText().simplified();
    int sotrang = ui->spinBox_sotrang_2->value();
    int namsx = ui->spinBox_namsb_2->value();
    int soluong = ui->spinBox_soluong_2->value();

    // Chuyển đổi sang string
    string isbnStd = ISBN.toStdString();
    string tensachStd = tensach.toStdString();
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();
    string vitriStd = vitri.toStdString();

    // Biến lưu trữ thông báo lỗi
    QString errorMessage;

    // Kiểm tra từng điều kiện và thêm lỗi vào errorMessage nếu có
    if (ISBN.isEmpty()) {
        QMessageBox::warning(this,"Cảnh báo", "Bạn chưa điền ISBN.\n");
        return;
    }

    if (int i = TimKiemViTriDauSach(isbnStd) == -1) {
        QMessageBox::warning(this,"Cảnh báo", "Mã đầu sách không tồn tại.");
        return;
    }

    if (vitriStd.empty()) {
        QMessageBox::warning(this, "Lỗi", "Bạn chưa điền vị trí.\n");
        return;
    }

    for (int i = 0; i < soluong; i++) {
        DauSach ds;
        ds.ISBN = isbnStd;
        ds.tensach = tensachStd;
        ds.sotrang = sotrang;
        ds.tacgia = tacgiaStd;
        ds.namsx = namsx;
        ds.theloai = theloaiStd;
        ThemHoacNhapDauSach(ds, co_the_muon, vitriStd, "");
    }

    // Hiển thị thông tin đã nhập
    QString infoMessage = QString("Thông tin đã nhập:\nISBN: %1\nTên sách: %2\nTác giả: %3\nThể loại: %4\nSố trang: %5\nNăm xuất bản: %6\nVị trí: %7\nSố lượng: %8\nTrạng Thái: Cho mượn được")
                              .arg(QString::fromStdString(isbnStd))
                              .arg(QString::fromStdString(tensachStd))
                              .arg(QString::fromStdString(tacgiaStd))
                              .arg(QString::fromStdString(theloaiStd))
                              .arg(sotrang)
                              .arg(namsx)
                              .arg(QString::fromStdString(vitriStd))
                              .arg(soluong);

    QMessageBox::information(this, "Đầu sách đã nhập", infoMessage);

    // Đóng hộp thoại sau khi thêm thành công
    accept();
}


void nhap_dausach::on_comboBox_vitri_2_currentTextChanged(const QString &text)
{
    if(!text.isEmpty()){
        string key = text.toStdString();

        // Chỉ cho phép một ký tự
        if (key.length() > 1) {
            key = key.substr(0, 1); // Giới hạn chỉ lấy ký tự đầu tiên
        }

        // Kiểm tra nếu ký tự là a-z hoặc A-Z
        if (!key.empty() && (isalpha(key[0]))) {
            // Chuyển ký tự thành in hoa
            key[0] = toupper(key[0]); // Chuyển đổi ký tự thành chữ in hoa
        } else {
            key.clear(); // Nếu không phải là chữ cái a-z hoặc A-Z, xóa key
        }

        // Cập nhật lại giá trị trong lineEdit
        ui->comboBox_vitri_2->setCurrentText(QString::fromStdString(key));
    }
}

