#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "timkiemmasach.h"
#include "intheotheloai.h"
#include "The_doc_gia.h"
#include <QDebug>

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
    , danh_sach_dau_sach()
    ,danh_muc_sach(nullptr)
{
    ui->setupUi(this);
    QObject::connect(ui->dauSach_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page1Widget);
    QObject::connect(ui->thedocgia_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page2Widget);
    QObject::connect(ui->muontra_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page3Widget);

    Doc_Thong_Tin_Tu_File(root, ui->tableWidget_2);
    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this);

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

void LibraryManagementSystem::page1Widget()
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


void LibraryManagementSystem::on_pushButton_intheloai_clicked()
{
    InTheoTheLoai intheloai(danh_sach_dau_sach,this);
    intheloai.setModal(true);
    intheloai.exec();
}

