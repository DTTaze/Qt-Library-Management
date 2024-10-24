#include "muonsach.h"
#include "ui_muonsach.h"

muonsach::muonsach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::muonsach)
{
    ui->setupUi(this);
    ui->maSach_lineEdit->setPlaceholderText("Nhập mã thẻ độc giả");
    ui->maThe_lineEdit->setPlaceholderText("Nhập sách cần mượn");
}

muonsach::~muonsach()
{
    delete ui;
}
