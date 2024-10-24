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
    return ui->hoEdit->text().trimmed();
}
QString themDocGia_Dialog::getTen() {
    return ui->ten_lineEdit->text().trimmed();
}
QString themDocGia_Dialog::getPhai()
{
    return ui->nam_radioButton->isChecked() ? "Nam" : "Nữ";
}


void themDocGia_Dialog::on_ok_pushButton_clicked()
{
    if (getHo().isEmpty()) {
        ui->hoEdit->setStyleSheet("QLineEdit{background-color:#ff8e8e;}");
    }
    if (getTen().isEmpty()) {
        ui->ten_lineEdit->setStyleSheet("QLineEdit{background-color:#ff8e8e;}");
    }
    if ( ui->nam_radioButton->isChecked() == false && ui->nu_radioButton->isChecked() == false ) {

    }
    if (!getHo().isEmpty() && !getTen().isEmpty() && (ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked()) ) {
        if ( kiemTraChuoi(getHo()) && kiemTraChuoi(getTen())) {
            accept();
        }
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin hoặc đã điền sai");
    }
}

void themDocGia_Dialog::xuLyChuoi(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;
    if (newText == " ") {
        newText.replace(" ", "");
    }

    while (newText.contains("  ")) {
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

void themDocGia_Dialog::on_cancel_pushButton_clicked()
{
    close();
}

void themDocGia_Dialog::on_hoEdit_textChanged(const QString &arg1)
{
    xuLyChuoi(arg1, ui->hoEdit);
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
    xuLyChuoi(arg1, ui->ten_lineEdit);
}


void themDocGia_Dialog::on_nam_radioButton_clicked()
{
}

