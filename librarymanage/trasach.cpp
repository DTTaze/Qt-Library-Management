#include "trasach.h"
#include "ui_trasach.h"

trasach::trasach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::trasach)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Nhập mã sách trả");
}

trasach::~trasach()
{
    delete ui;
}
