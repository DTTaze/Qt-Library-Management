#include "hieuChinhDocGia_dialog.h"
#include "ui_hieuChinhDocGia_dialog.h"

hieuChinhDocGia_dialog::hieuChinhDocGia_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::hieuChinhDocGia_dialog)
{
    ui->setupUi(this);
}

hieuChinhDocGia_dialog::~hieuChinhDocGia_dialog()
{
    delete ui;
}

void hieuChinhDocGia_dialog::setMaThe( int maThe ) {
    ui->maThe_lineEdit->setText(QString::number(maThe) );
}
void hieuChinhDocGia_dialog::setHoVaTen(string ho, string ten) {
    ui->hoVaTen_lineEdit->setText(QString::fromStdString(ho) + " " + QString::fromStdString(ten));
}
void hieuChinhDocGia_dialog::setGioiTinh(Phai gioitinh) {
    if ( gioitinh == Nam) {
        ui->gioiTinh_comboBox->setCurrentIndex(0);
    } else {
        ui->gioiTinh_comboBox->setCurrentIndex(1);
    }
}
void hieuChinhDocGia_dialog::setTrangThaiThe(TrangThaiCuaThe trangthai) {
    if ( trangthai == Dang_Hoat_Dong) {
        ui->trangThaiThe_comboBox->setCurrentIndex(0);
    } else {
        ui->trangThaiThe_comboBox->setCurrentIndex(1);
    }
}

int hieuChinhDocGia_dialog::getMaThe() {
    return ui->maThe_lineEdit->text().toInt();
}

QString hieuChinhDocGia_dialog::getHoVaTen() {
    return ui->hoVaTen_lineEdit->text().simplified();
}
Phai hieuChinhDocGia_dialog::getGioiTinh() {
    return ( ui->gioiTinh_comboBox->currentIndex() == 0 ) ? Nam : Nu;
}
TrangThaiCuaThe hieuChinhDocGia_dialog::getTrangThaiThe() {
    return ( ui->trangThaiThe_comboBox->currentIndex() == 0 ) ? Dang_Hoat_Dong : Khoa;
}

void hieuChinhDocGia_dialog::xuLySo(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;

    if (newText.contains(" ")) {
        newText.replace(" ", "");
    }

    if (!newText.isEmpty() && !newText[newText.length() - 1].isDigit() ) {
        newText = newText.mid(0, newText.length() - 1);
    }

    if (newText != arg1) {
        lineEdit->setText(newText);
    }
}

bool timThayTheDocGia(Danh_Sach_The_Doc_Gia* docGia) {
    return docGia != nullptr;
}

void hieuChinhDocGia_dialog::on_maThe_lineEdit_textChanged(const QString &arg1)
{
    xuLySo(arg1, ui->maThe_lineEdit);
    int maThe = getMaThe();
    Danh_Sach_The_Doc_Gia* docGia = timKiemTheDocGia(maThe);
    if ( timThayTheDocGia(docGia) ) {
        ui->maThe_lineEdit->setStyleSheet("background-color: lightgreen");
        setHoVaTen(docGia->thong_tin.Ho, docGia->thong_tin.Ten);
        setGioiTinh(docGia->thong_tin.phai);
        setTrangThaiThe(docGia->thong_tin.TrangThai);
    } else {
        ui->maThe_lineEdit->setStyleSheet("background-color: lightcoral");
    }
}

void hieuChinhDocGia_dialog::xuLyChuoi(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;

    if (newText == " ") {
        newText.replace(" ", "");
    }

    if (newText.contains("  ")) {
        newText.replace("  ", " ");
    }

    if (!newText.isEmpty() && !newText[newText.length() - 1].isLetter() && !newText[newText.length() - 1].isSpace()) {
        newText = newText.mid(0, newText.length() - 1);
    }

    for ( int i = 0; i < newText.length(); i++ ) {
        if ( i == 0 ) {
            newText[0] = newText[0].toUpper();
        }
        if ( i > 0 && newText[i-1] == ' ') {
            newText[i] = newText[i].toUpper();
        }
    }

    if (newText != arg1) {
        lineEdit->setText(newText);
    }
}

void hieuChinhDocGia_dialog::on_hoVaTen_lineEdit_textChanged(const QString &arg1)
{
    int currentPointerPosition = ui->hoVaTen_lineEdit->cursorPosition();
    xuLyChuoi(arg1, ui->hoVaTen_lineEdit);
    ui->hoVaTen_lineEdit->setCursorPosition(currentPointerPosition);
}

void hieuChinhDocGia_dialog::on_Ok_pushButton_clicked()
{
    int maThe = getMaThe();
    Danh_Sach_The_Doc_Gia* docGia = timKiemTheDocGia(maThe);
    if ( docGia == nullptr ) {
        QMessageBox::warning(this, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    QString hoVaTen = getHoVaTen();
    if ( hoVaTen.isEmpty() || !hoVaTen.contains(" ")) {
        QMessageBox::warning(this, "Lỗi", "Độc giả phải có đầy đủ họ và tên.");
        return;
    }
    accept();
}


void hieuChinhDocGia_dialog::on_Cancel_pushButton_clicked()
{
    close();
}

