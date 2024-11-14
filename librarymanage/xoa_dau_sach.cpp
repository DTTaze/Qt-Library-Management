#include "xoa_dau_sach.h"
#include "ui_xoa_dau_sach.h"
#include "Dau_sach.h"

Xoa_dau_sach::Xoa_dau_sach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Xoa_dau_sach)
{
    ui->setupUi(this);
}

Xoa_dau_sach::~Xoa_dau_sach()
{
    delete ui;
}
