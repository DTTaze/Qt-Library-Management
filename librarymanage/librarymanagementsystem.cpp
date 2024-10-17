#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "timkiemmasach.h"
#include "intheotheloai.h"
#include "The_doc_gia.h"
#include "themdocgia_dialog.h"
#include <QDebug>

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
    , danh_sach_dau_sach()
    ,danh_muc_sach(nullptr)
{
    ui->setupUi(this);
    QObject::connect(ui->dauSach_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page1Widget); // Chuyển sang tab Đầu Sách
    QObject::connect(ui->thedocgia_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page2Widget); // Chuyển sang tab Độc Giả
    QObject::connect(ui->muontra_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page3Widget); // Chuyển sang tab Mượn Trả

    Doc_Thong_Tin_Tu_File(root, ui->tableWidget_2); // Load thông tin từ file docgia_100.txt vào cây
    Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root); // Thêm cây vào tableWidget_2
    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách

    QObject::connect(ui->timKiemDs_lineEdit, &QLineEdit::textChanged, this, &LibraryManagementSystem::on_lineEdit_timkiemds_textChanged);

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

void LibraryManagementSystem::on_themDocGia_pushButton_clicked() // Mở ra cửa số để nhập thông tin độc giả cần thêm
{
    themDocGia_Dialog themDocGia;
    themDocGia.setModal(true);
    themDocGia.exec();
}

void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index)
{
    ui->tableWidget_2->setRowCount(0); // Làm sạch bảng trước khi thêm dữ liệu mới

    if (index == 0) { // 0 là chỉ số cho mã số
        Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root);
    } else if (index == 1) { // 1 là chỉ số cho tên
        root_ten = Tao_Cay_Theo_Ten(0, Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The - 1);
        Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root_ten);
        Xoa_Danh_Sach_Theo_Ten(root_ten);
    }
}

void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai(danh_sach_dau_sach,this);
    intheloai.setModal(true);
    intheloai.exec();
}


