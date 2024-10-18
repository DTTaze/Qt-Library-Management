#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "timkiemmasach.h"
#include "intheotheloai.h"
#include "The_doc_gia.h"
#include "themdocgia_dialog.h"
#include "Muon_tra.h"
#include <QDebug>

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
    , danh_sach_dau_sach()
    ,danh_muc_sach(nullptr)
    ,danh_sach_muon_tra()
{
    ui->setupUi(this);
    QObject::connect(ui->dauSach_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page1Widget); // Chuyển sang tab Đầu Sách
    QObject::connect(ui->thedocgia_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page2Widget); // Chuyển sang tab Độc Giả
    QObject::connect(ui->muontra_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page3Widget); // Chuyển sang tab Mượn Trả
    connect(ui->tableWidget_2, &QTableWidget::itemChanged, this, &LibraryManagementSystem::on_tableWidget_2_itemChanged);

    Tao_Mang_The();

    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách
    Doc_Thong_Tin_Tu_File(root,danh_sach_muon_tra, ui->tableWidget_2); // Load thông tin từ file docgia_100.txt vào cây
    Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root); // Thêm cây vào tableWidget_2

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
//------------------------------------Hàm sử dụng ở Thẻ Độc Giả-----------------------------------------------------------------------
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
void LibraryManagementSystem::on_themDocGia_pushButton_clicked() // Mở ra cửa số để nhập thông tin độc giả cần thêm
{
    themDocGia_Dialog themDocGia;
    themDocGia.setModal(true);
    if (themDocGia.exec() == QDialog::Accepted) {
        // Lấy thông tin từ dialog và thêm vào cây
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
        Them_Doc_Gia_Mang(docGia);
        for ( int i = 0; i < Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The; i++ ) {
            cout << Mang_The_Doc_Gia_Tam_Thoi.DS[i].Ten << endl;
        }
        ui->sapXepDocGia_ComboBox->setCurrentIndex(0);
        ui->tableWidget_2->setRowCount(0);
        Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root);
    }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai(danh_sach_dau_sach,this);
    intheloai.setModal(true);
    intheloai.exec();
}

void LibraryManagementSystem::on_xoaDocGia_pushButton_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();
    QTableWidgetItem* item = ui->tableWidget_2->item(currentRow, 0);
    int MATHE = item->text().toInt();
    if ( currentRow != -1 ) {
        Xoa_Doc_Gia(root, MATHE);
        ui->tableWidget_2->setRowCount(0);
        Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root);
    } else {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một độc giả để xóa.");
    }
}


void LibraryManagementSystem::on_tableWidget_2_itemChanged(QTableWidgetItem* item)
{
    // Lấy chỉ số hàng và cột của ô đã thay đổi
    int row = item->row();
    int column = item->column();

    // Lấy mã thẻ ở cột 0
    QTableWidgetItem* maTheItem = ui->tableWidget_2->item(row, 0);
    bool ok;
    int maThe = maTheItem->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Cảnh báo", "Không thể lấy mã thẻ.");
        return;
    }

    // Lấy giá trị mới từ ô đã thay đổi
    QString newValue = item->text();

    // Cập nhật thông tin vào cây hoặc danh sách tương ứng
    // Giả sử bạn có hàm cập nhật thông tin trong cây nhị phân hoặc danh sách
    switch (column) {
    case 1: // Cột Họ
        // Cập nhật họ của độc giả
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ho", newValue.toStdString());
        break;
    case 2: // Cột Tên
        // Cập nhật tên của độc giả
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ten", newValue.toStdString());
        break;
    case 3: // Cột Phái
        // Cập nhật phái
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Phai", newValue.toStdString());
        break;
    case 4: // Cột Trạng thái
        // Cập nhật trạng thái
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "TrangThai", newValue.toStdString());
        break;
    default:
        break;
    }
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

