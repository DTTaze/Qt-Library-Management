#include "timkiemmasach.h"
#include "ui_timkiemmasach.h"

timkiemmasach::timkiemmasach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::timkiemmasach)
{
    ui->setupUi(this);
    ui->lineEdit_mathe->setPlaceholderText("Nhập mã thẻ độc giả");
}

timkiemmasach::~timkiemmasach()
{
    delete ui;
}
int timkiemmasach::getMaThe() {
    return ui->lineEdit_mathe->text().toInt();
}

void timkiemmasach::inThongTin(const int& ma_the) {

    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, ma_the);
    ui->tableWidget_timkiemmasach->setRowCount(0);
    string hovaten = p->thong_tin.Ho + " " + p->thong_tin.Ten;
    DanhSachMUONTRA *current = p->thong_tin.head_lsms;

    ui->lineEdit_ten_2->setText(QString::fromStdString(hovaten));
    ui->lineEdit_phai_2->setText(p->thong_tin.phai == Nam ? "Nam" : "Nữ");
    ui->lineEdit_trangthai_2->setText(p->thong_tin.TrangThai == Dang_Hoat_Dong ? "Dang Hoạt Động": "Khóa");

    while ( current != nullptr && current->data.NgayTra.day == 0) {
        int indexRow = ui->tableWidget_timkiemmasach->rowCount();
        ui->tableWidget_timkiemmasach->insertRow(indexRow);
        ui->tableWidget_timkiemmasach->setItem(indexRow, 0, new QTableWidgetItem(QString::fromStdString(current->data.masach)));
        ui->tableWidget_timkiemmasach->setItem(indexRow, 1, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach))));
        ui->tableWidget_timkiemmasach->setItem(indexRow, 2, new QTableWidgetItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
        if ( SoNgayQuaHan(current->data.NgayMuon, NgayHomNay()) <= 7 ) {
            ui->tableWidget_timkiemmasach->setItem(indexRow, 3, new QTableWidgetItem("Không"));
        } else {
            ui->tableWidget_timkiemmasach->setItem(indexRow, 3, new QTableWidgetItem("Có"));
        }
        indexRow++;
        current = current->next;
    }

}

void timkiemmasach::on_lineEdit_mathe_textChanged(const QString &text)
{
    if ( text.isEmpty() ) {
        ui->lineEdit_mathe->setStyleSheet("background-color: white;");
        while (ui->tableWidget_timkiemmasach->rowCount() > 0) {
            ui->tableWidget_timkiemmasach->removeRow(0);
        }
        ui->lineEdit_ten_2->setText("");
        ui->lineEdit_phai_2->setText("");
        ui->lineEdit_trangthai_2->setText("");
        return;
    }
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, text.toInt());
    if ( p != nullptr ) {
        inThongTin(p->thong_tin.MATHE);
        ui->lineEdit_mathe->setStyleSheet("background-color: lightgreen;");
    } else {
        ui->lineEdit_ten_2->setText("");
        ui->lineEdit_phai_2->setText("");
        ui->lineEdit_trangthai_2->setText("");
        ui->lineEdit_mathe->setStyleSheet("background-color: lightcoral;");
        while (ui->tableWidget_timkiemmasach->rowCount() > 0) {
            ui->tableWidget_timkiemmasach->removeRow(0);
        }
    }
}





void timkiemmasach::on_pushButton_cancel_clicked()
{
    close();
}

