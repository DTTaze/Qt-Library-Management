#include "timkiemmasach.h"
#include "ui_timkiemmasach.h"

timkiemmasach::timkiemmasach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::timkiemmasach)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Nhập mã thẻ độc giả");
}

timkiemmasach::~timkiemmasach()
{
    delete ui;
}
