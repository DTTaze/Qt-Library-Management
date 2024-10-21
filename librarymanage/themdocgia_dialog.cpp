#include "themdocgia_dialog.h"
#include "ui_themdocgia_dialog.h"

themDocGia_Dialog::themDocGia_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::themDocGia_Dialog)
{
    ui->setupUi(this);
}

themDocGia_Dialog::~themDocGia_Dialog()
{
    delete ui;
}

QString themDocGia_Dialog::getHo() {
    return ui->hoEdit->text();
}
QString themDocGia_Dialog::getTen() {
    return ui->ten_lineEdit->text();
}
QString themDocGia_Dialog::getPhai()
{
    return ui->nam_radioButton->isChecked() ? "Nam" : "Nữ";
}


void themDocGia_Dialog::on_ok_pushButton_clicked()
{
    if (getHo().isEmpty()) {
        ui->baoloiHo_label->setText("Vui lòng điền họ");
    }
    if (getTen().isEmpty()) {
        ui->baoLoiTen_label->setText("Vui lòng điền tên");
    }
    if ( ui->nam_radioButton->isChecked() == false && ui->nu_radioButton->isChecked() == false ) {
        ui->baoLoiPhai_label->setText("Vui lòng chọn phái");
    }
    if (!getHo().isEmpty() && !getTen().isEmpty() && (ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked()) ) {
        if ( kiemTraChuoi(getHo()) && kiemTraChuoi(getTen())) {
            accept();
        }
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin hoặc đã điền sai");
    }
}


void themDocGia_Dialog::on_cancel_pushButton_clicked()
{
    close();
}

void themDocGia_Dialog::on_hoEdit_textChanged(const QString &arg1)
{
    QString newText = arg1;
    while (newText.contains("  ")) {
        newText.replace("  ", " ");
    }
    if (newText != arg1) {
        ui->hoEdit->setText(newText);
    }
    if ( kiemTraChuoi(arg1) == false ) {
        ui->baoloiHo_label->setText("Họ chỉ bao gồm chữ hoa hoặc thường");
    } else {
        ui->baoloiHo_label->setText("");
    }
}

bool themDocGia_Dialog::kiemTraChuoi(QString s) {
    for ( int i = 0; i < s.length(); i++ ) {
        if ( !s[i].isLetter() && !s[i].isSpace() ) {
            return false;
        }
    }
    return true;
}


void themDocGia_Dialog::on_ten_lineEdit_textChanged(const QString &arg1)
{
    QString newText = arg1;
    while (newText.contains("  ")) {
        newText.replace("  ", " ");
    }
    if (newText != arg1) {
        ui->hoEdit->setText(newText);
    }
    if ( kiemTraChuoi(arg1) == false ) {
        ui->baoLoiTen_label->setText("Họ chỉ bao gồm chữ hoa hoặc thường");
    } else {
        ui->baoLoiTen_label->setText("");
    }
}


void themDocGia_Dialog::on_nam_radioButton_clicked()
{
    if ( ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked()) {
        ui->baoLoiPhai_label->setText("");
    }
}

