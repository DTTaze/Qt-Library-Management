#include "danhmucsach.h"
#include "ui_danhmucsach.h"
#include "dau_sach.h"

Danhmucsach::Danhmucsach(int Vi_tri_DS,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Danhmucsach)
    , Vitridausach(Vi_tri_DS)
{
    ui->setupUi(this);

    int row = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[Vitridausach]->dms; cur != nullptr; cur = cur->next){
        row = ui->tableWidget_danhmucsach->rowCount();
        ui->tableWidget_danhmucsach->insertRow(row);


        ui->tableWidget_danhmucsach->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(cur->masach)));
        ui->tableWidget_danhmucsach->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        int trangthai = cur->trangthai;
        QString trang_thai_qt;
        switch(trangthai) {
            case 0: trang_thai_qt = "Có thể mượn"; break;
            case 1: trang_thai_qt = "Đã được mượn"; break;
            case 2: trang_thai_qt = "Đã thanh lý"; break;
        }
        ui->tableWidget_danhmucsach->setItem(row, 2, new QTableWidgetItem(trang_thai_qt));
    }

    ui->tableWidget_danhmucsach->resizeColumnsToContents();
    ui->tableWidget_danhmucsach->setColumnWidth(0,200);
}

Danhmucsach::~Danhmucsach()
{
    delete ui;
}
