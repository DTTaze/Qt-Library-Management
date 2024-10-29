#include "baocao.h"
#include "ui_baocao.h"

baocao::baocao(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::baocao)
{
    ui->setupUi(this);
    NhapThongTinVaoTop10(ui->topTenMuonNhieuNhat_tableView,root); // In thông tin top 10 sách nhiều lượt xem
    inDanhSachDocGiaMuonQuaHan(ui->tableView_danhsachquahan, root);
}

baocao::~baocao()
{
    delete ui;
}
