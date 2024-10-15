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
