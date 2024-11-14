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

void hieuChinhDocGia_dialog::setMaThe( QString maThe ) {
    ui->maThe_lineEdit->setText(maThe);
}
void hieuChinhDocGia_dialog::setHoVaTen(QString ho, QString ten) {
    ui->hoVaTen_lineEdit->setText(ho + ten);
}
void hieuChinhDocGia_dialog::setGioiTinh(QString gioitinh) {
    if ( gioitinh == "Nam") {
        ui->gioiTinh_comboBox->setCurrentIndex(0);
    } else {
        ui->gioiTinh_comboBox->setCurrentIndex(1);
    }
}
void hieuChinhDocGia_dialog::setTrangThaiThe(QString trangthai) {
    if ( trangthai == "Đang Hoạt Động") {
        ui->trangThaiThe_comboBox->setCurrentIndex(0);
    } else {
        ui->trangThaiThe_comboBox->setCurrentIndex(1);
    }
}

QString hieuChinhDocGia_dialog::getHoVaTen() {
    return ui->hoVaTen_lineEdit->text();
}
Phai hieuChinhDocGia_dialog::getGioiTinh() {
    return ( ui->gioiTinh_comboBox->currentIndex() == 0 ) ? Nam : Nu;
}
TrangThaiCuaThe hieuChinhDocGia_dialog::getTrangThaiThe() {
    return ( ui->trangThaiThe_comboBox->currentIndex() == 0 ) ? Dang_Hoat_Dong : Khoa;
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
    xuLyChuoi(arg1, ui->hoVaTen_lineEdit);
}

