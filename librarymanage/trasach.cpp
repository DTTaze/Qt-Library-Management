#include "trasach.h"
#include "ui_trasach.h"

trasach::trasach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::trasach)
{
    ui->setupUi(this);

}

trasach::~trasach()
{
    delete ui;
}


int trasach::getMaThe() {
    return ui->lineEdit_mathe->text().toInt();
}

void trasach::inThongTin(const int& ma_the) {

    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, ma_the);
    ui->tableWidget_trasach->setRowCount(0);
    string hovaten = p->thong_tin.Ho + " " + p->thong_tin.Ten;
    DanhSachMUONTRA *current = p->thong_tin.head_lsms;

    ui->lineEdit_ten->setText(QString::fromStdString(hovaten));
    ui->lineEdit_phai->setText(p->thong_tin.phai == Nam ? "Nam" : "Nữ");
    ui->lineEdit_trangthai->setText(p->thong_tin.TrangThai == Dang_Hoat_Dong ? "Dang Hoạt Động": "Khóa");

    while ( current != nullptr && current->data.NgayTra.day == 0) {
        int indexRow = ui->tableWidget_trasach->rowCount();
        ui->tableWidget_trasach->insertRow(indexRow);
        ui->tableWidget_trasach->setItem(indexRow, 0, new QTableWidgetItem(QString::fromStdString(current->data.masach)));
        ui->tableWidget_trasach->setItem(indexRow, 1, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach))));
        ui->tableWidget_trasach->setItem(indexRow, 2, new QTableWidgetItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
        qDebug() << current->data.masach << " " << ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach) << " " << ChuyenDateSangString(current->data.NgayMuon) << ChuyenDateSangString(current->data.NgayTra);
        if ( SoNgayQuaHan(current->data.NgayMuon, NgayHomNay()) <= 7 ) {
            ui->tableWidget_trasach->setItem(indexRow, 3, new QTableWidgetItem("Không"));
        } else {
            ui->tableWidget_trasach->setItem(indexRow, 3, new QTableWidgetItem("Có"));
        }
        indexRow++;
        current = current->next;
    }

}

void trasach::on_lineEdit_mathe_textChanged(const QString &text)
{
    if ( text.isEmpty() ) {
        ui->lineEdit_mathe->setStyleSheet("background-color: white;");
        while (ui->tableWidget_trasach->rowCount() > 0) {
            ui->tableWidget_trasach->removeRow(0);
        }
        ui->lineEdit_ten->setText("");
        ui->lineEdit_phai->setText("");
        ui->lineEdit_trangthai->setText("");
        return;
    }
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, text.toInt());
    if ( p != nullptr ) {
        inThongTin(p->thong_tin.MATHE);
        ui->lineEdit_mathe->setStyleSheet("background-color: lightgreen;");
    } else {
        ui->lineEdit_ten->setText("");
        ui->lineEdit_phai->setText("");
        ui->lineEdit_trangthai->setText("");
        ui->lineEdit_mathe->setStyleSheet("background-color: lightcoral;");
        while (ui->tableWidget_trasach->rowCount() > 0) {
            ui->tableWidget_trasach->removeRow(0);
        }
    }
}


void trasach::on_pushButton_clicked()
{
    close();
}


void trasach::on_pushButton_trasach_clicked()
{
    int currentRow = ui->tableWidget_trasach->currentRow();

    if (currentRow == -1) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn sách để trả.");
        return;
    }

    QTableWidgetItem* item = ui->tableWidget_trasach->item(currentRow, 0);
    string maSach = item->text().toStdString();

    TraSach(ui->lineEdit_mathe->text().toInt(), maSach);
    inThongTin(ui->lineEdit_mathe->text().toInt());
}

