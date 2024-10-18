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
    if (!getHo().isEmpty() && !getTen().isEmpty() && (ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked()) ) {
        accept();
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin");
    }
}


void themDocGia_Dialog::on_cancel_pushButton_clicked()
{
    close();
}

