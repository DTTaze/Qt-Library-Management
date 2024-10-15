#include "muonsach.h"
#include "ui_muonsach.h"

muonsach::muonsach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::muonsach)
{
    ui->setupUi(this);
    ui->sachcanmuon_earch->setPlaceholderText("Nhập mã thẻ độc giả");
    ui->mathedocgia_search->setPlaceholderText("Nhập sách cần mượn");
}

muonsach::~muonsach()
{
    delete ui;
}
