#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "timkiemmasach.h"
#include "intheotheloai.h"
#include "themdausach.h"
#include "The_doc_gia.h"
#include "themdocgia_dialog.h"
#include "Muon_tra.h"
#include <QDebug>

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
    , danh_sach_dau_sach()
    ,danh_muc_sach(nullptr)
    ,danh_sach_muon_tra(nullptr)
{
    ui->setupUi(this);
    QObject::connect(ui->dauSach_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page1Widget); // Chuyển sang tab Đầu Sách
    QObject::connect(ui->thedocgia_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page2Widget); // Chuyển sang tab Độc Giả
    QObject::connect(ui->muontra_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page3Widget); // Chuyển sang tab Mượn Trả
    QObject::connect(ui->timKiemDs_lineEdit, &QLineEdit::textChanged, this, &LibraryManagementSystem::on_lineEdit_timkiemds_textChanged);

    Doc_File_Ma_The();
    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách
    Doc_Thong_Tin_Tu_File(root,danh_sach_muon_tra,ui->tableWidget_2); // Load thông tin từ file docgia_100.txt vào cây

    Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root); // Thêm cây vào tableWidget_2
    Them_Cay_Vao_QTableWidget_danhsachquahan(ui->tableWidget_danhsachquahan, root, danh_sach_muon_tra);
}

LibraryManagementSystem::~LibraryManagementSystem()
{
    delete ui;
}

void LibraryManagementSystem::on_lineEdit_timkiemds_textChanged(const QString text){
    string key = text.toStdString();
    TimKiemTenSach(danh_sach_dau_sach,ui->tableView_dausach,key);
}

void LibraryManagementSystem::page1Widget() // Chuyển đổi giữa các tab Đầu Sách, Độc Giả, và Mượn Sách
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_dausach);
}

void LibraryManagementSystem::page2Widget()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_docgia);
}

void LibraryManagementSystem::page3Widget()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_muontra);

}
//------------------------------------Hàm sử dụng ở Thẻ Độc Giả-----------------------------------------------------------------------
void LibraryManagementSystem::CapNhatBang()
{
    ui->tableWidget_2->setRowCount(0);

    if ( ui->sapXepDocGia_ComboBox->currentIndex() == 0 ) {
        Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root);
    } else {
        DS_PTR = 0;
        Copy_Cay_Sang_Mang(root);
        Them_Mang_Vao_QTableWidget(ui->tableWidget_2);
    }
}
void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index)
{
    CapNhatBang();
}
void LibraryManagementSystem::on_themDocGia_pushButton_clicked() // Mở ra cửa số để nhập thông tin độc giả cần thêm
{
    themDocGia_Dialog themDocGia;
    themDocGia.setModal(true);
    if (themDocGia.exec() == QDialog::Accepted) {

        The_Doc_Gia docGia;
        docGia.MATHE = LayMaTheNgauNhien();
        docGia.Ho = themDocGia.getHo().toStdString();
        docGia.Ten = themDocGia.getTen().toStdString();
        if ( themDocGia.getPhai() == "Nam") {
            docGia.phai = Phai::Nam;
        } else {
            docGia.phai = Phai::Nu;
        }
        docGia.TrangThai = TrangThaiCuaThe::Dang_Hoat_Dong;

        Them_Doc_Gia(root, docGia);
        Them_Doc_Gia_Vao_Mang(Tim_Kiem(root, docGia.MATHE));
        CapNhatBang();
    }
}

void LibraryManagementSystem::on_xoaDocGia_pushButton_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();

    if (currentRow == -1) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một độc giả để xóa.");
        return;
    }

    QTableWidgetItem* item = ui->tableWidget_2->item(currentRow, 0); // Lấy thông tin từ cột đầu tiên
    if (item) {
        int MATHE = item->text().toInt();

        Xoa_Doc_Gia(root, MATHE);
        DS_PTR = 0;
        Copy_Cay_Sang_Mang(root);

        ui->tableWidget_2->removeRow(currentRow); // Xóa hàng từ bảng

        CapNhatBang();

        QMessageBox::information(this, "Thông báo", "Độc giả đã được xóa thành công.");
    } else {
        QMessageBox::warning(this, "Cảnh báo", "Không thể lấy thông tin độc giả.");
    }
}

void LibraryManagementSystem::on_tableWidget_2_itemChanged(QTableWidgetItem* item)
{
    int row = item->row();
    int column = item->column();

    QTableWidgetItem* maTheItem = ui->tableWidget_2->item(row, 0);
    bool ok;
    int maThe = maTheItem->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Cảnh báo", "Không thể lấy mã thẻ.");
        return;
    }

    QString newValue = item->text();

    switch (column) {
    case 1:
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ho", newValue.toStdString());
        break;
    case 2:

        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ten", newValue.toStdString());
        break;
    case 3:
        if (newValue != "Nam" && newValue != "Nữ") {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị phái không hợp lệ. Vui lòng nhập 'Nam' hoặc 'Nữ'.");
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Phai", newValue.toStdString());
        break;
    case 4:
        if (newValue != "Đang Hoạt Động" && newValue != "Bị Khóa") {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị trạng thái không hợp lệ. Vui lòng nhập 'Đang Hoạt Động' hoặc 'Bị Khóa'.");
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "TrangThai", newValue.toStdString());
        break;
    default:
        break;
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai(danh_sach_dau_sach,this);
    intheloai.setModal(true);
    intheloai.exec();
}

void LibraryManagementSystem::on_muonsach_buttom_clicked()
{
    muonsach muon_sach;
    muon_sach.setModal(true);
    muon_sach.exec();
}

void LibraryManagementSystem::on_trasach_buttom_clicked()
{
    trasach tra_sach;
    tra_sach.setModal(true);
    tra_sach.exec();
}

void LibraryManagementSystem::on_timsach_buttom_clicked()
{
    timkiemmasach timkiem;
    timkiem.setModal(true);
    timkiem.exec();
}

void LibraryManagementSystem::on_tableView_dausach_activated(const QModelIndex &index)
{

}

void LibraryManagementSystem::on_themSach_pushButton_clicked()
{
    themdausach themds(danh_sach_dau_sach,danh_muc_sach,this);
    themds.setModal(true);
    themds.exec();
}


void LibraryManagementSystem::on_luuFile_pushButton_clicked()
{
    Ghi_The_Vao_File();
}

