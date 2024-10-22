#include "intheotheloai.h"
#include "ui_intheotheloai.h"

InTheoTheLoai::InTheoTheLoai(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InTheoTheLoai)
{
    ui->setupUi(this);
    qDebug()<<danh_sach_dau_sach.demsach;
    InTheoTungTheLoai(danh_sach_dau_sach,ui->tableView_intheloai);
}

InTheoTheLoai::~InTheoTheLoai()
{
    delete ui;
}
