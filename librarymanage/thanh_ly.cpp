#include "thanh_ly.h"
#include "ui_thanh_ly.h"

Thanh_ly::Thanh_ly(const string &ISBN,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Thanh_ly)
    , ma_ISBN(ISBN)
{
    ui->setupUi(this);

    HienThongtin(ma_ISBN);
}

Thanh_ly::~Thanh_ly()
{
    delete ui;

}

void Thanh_ly::HienThongtin(const string &ma_isbn){
    int index = TimKiemIndexDauSach(ma_isbn);
    ui->lineEdit_ISBN->setText(QString::fromStdString(ma_isbn));
    ui->lineEdit_tensach->setText(QString::fromStdString(danh_sach_dau_sach.node[index]->tensach));
    ui->lineEdit_sotrang->setText(QString::number(danh_sach_dau_sach.node[index]->sotrang));
    ui->lineEdit_tacgia->setText(QString::fromStdString(danh_sach_dau_sach.node[index]->tacgia));
    ui->lineEdit_namsb->setText(QString::number(danh_sach_dau_sach.node[index]->namsx));
    ui->lineEdit_theloai->setText(QString::fromStdString(danh_sach_dau_sach.node[index]->theloai));

    int row_count = 0;
    for(DanhMucSach* cur = danh_sach_dau_sach.node[index]->dms; cur != nullptr && row_count < danh_sach_dau_sach.node[index]->demsosach;cur = cur->next , row_count++){
        ui->tableWidget_thanhly->insertRow(row_count);

        // Kiểm tra trạng thái
        if (cur->trangthai == 0) {
            // Tạo một checkbox chỉ khi trạng thái là 0
            QCheckBox* checkBox = new QCheckBox();
            checkBox->setChecked(false); // Đặt checkbox ban đầu là unchecked

            // Đặt checkbox vào ô đầu tiên của hàng
            ui->tableWidget_thanhly->setCellWidget(row_count, 0, checkBox);
        } else {
            // Nếu trạng thái không phải 0, để ô đầu tiên trống
            ui->tableWidget_thanhly->setCellWidget(row_count, 0, nullptr); // Để ô đầu tiên trống
        }

        ui->tableWidget_thanhly->setItem(row_count, 1 , new QTableWidgetItem(QString::fromStdString(cur->masach)));
        ui->tableWidget_thanhly->setItem(row_count, 2 , new QTableWidgetItem(QString::fromStdString(cur->vitri)));

        QString trang_thai_std;
        switch (cur->trangthai){
        case 0:trang_thai_std = "Có thể mượn";break;
        case 1:trang_thai_std = "Đã được mượn";break;
        case 2:trang_thai_std = "Đã thanh lý";break;
        }
        ui->tableWidget_thanhly->setItem(row_count, 3 , new QTableWidgetItem(trang_thai_std));
    }
    ui->tableWidget_thanhly->resizeColumnsToContents();
    ui->tableWidget_thanhly->setColumnWidth(1,160);
}
