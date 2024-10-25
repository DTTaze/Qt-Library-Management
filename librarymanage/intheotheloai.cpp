#include "intheotheloai.h"
#include "ui_intheotheloai.h"

InTheoTheLoai::InTheoTheLoai(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InTheoTheLoai)
{
    ui->setupUi(this);
    InTheoTungTheLoai(danh_sach_dau_sach,ui->tableView_intheloai);
}

InTheoTheLoai::~InTheoTheLoai()
{
    delete ui;
}
