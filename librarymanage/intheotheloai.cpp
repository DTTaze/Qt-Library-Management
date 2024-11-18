#include "intheotheloai.h"
#include "ui_intheotheloai.h"

InTheoTheLoai::InTheoTheLoai(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InTheoTheLoai)
{
    ui->setupUi(this);
    InTheoTungTheLoai(ui->tableView_intheloai);
}

InTheoTheLoai::~InTheoTheLoai()
{
    delete ui;
}
