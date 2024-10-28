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
#include "dau_sach.h"
#include <QDebug>

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)

{
    ui->setupUi(this);
    QObject::connect(ui->dauSach_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page1Widget); // Chuyển sang tab Đầu Sách
    QObject::connect(ui->thedocgia_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page2Widget); // Chuyển sang tab Độc Giả
    QObject::connect(ui->muontra_pushButton, &QPushButton::clicked, this, &LibraryManagementSystem::page3Widget); // Chuyển sang tab Mượn Trả
    QObject::connect(ui->lineEdit_timkiemds, &QLineEdit::textChanged, this, &LibraryManagementSystem::on_lineEdit_timkiemds_textChanged);

    Doc_File_Ma_The();
    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách
    Doc_Thong_Tin_Tu_File(danh_sach_muon_tra,ui->tableWidget_2); // Load thông tin từ file docgia_100.txt vào cây

    InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach, ui->tableView_dausach); // In bảng đầu sách
    Them_Cay_Vao_QTableWidget(ui->tableWidget_2, root); // In bảng danh sách thẻ độc giả

    Top10QuyenSachNhieuLuotMuonNhat(ui->topTenMuonNhieuNhat_tableView);
    inDanhSachDocGiaMuonQuaHan(ui->tableView_danhsachquahan);
}

void LibraryManagementSystem::page1Widget() // Chuyển đổi giữa các tab Đầu Sách, Độc Giả, và Mượn Sách
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_dausach);
    InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach, ui->tableView_dausach);
    qDebug()<<"test";
}

void LibraryManagementSystem::page2Widget()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_docgia);
}

void LibraryManagementSystem::page3Widget()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_muontra);
}

void LibraryManagementSystem::on_luuFile_pushButton_clicked()
{
    Ghi_The_Vao_File();
    Ghi_Ma_The_Vao_File(index_MangRandom);
    InVaoTXT();
}
//------------------------------------Hàm sử dụng ở Đầu Sách-----------------------------------------------------------------------
LibraryManagementSystem::~LibraryManagementSystem()
{
    delete ui;
}

void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai;
    intheloai.setModal(true);
    intheloai.exec();
}

void LibraryManagementSystem::on_lineEdit_timkiemds_textChanged(const QString text) {
    QString key ;
    bool lastWasSpace = false; // Để kiểm tra ký tự trước đó có phải là dấu cách không

    for (QChar c : text) {
        if (c.isLetter() || c.isDigit() || c.isPunct() || c.isSymbol()) {
            key += c; // Thêm ký tự hợp lệ (chữ hoặc số) vào key
            lastWasSpace = false; // Reset trạng thái lastWasSpace
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                key += ' '; // Thêm một dấu cách nếu không phải là dấu cách trước đó
                lastWasSpace = true; // Đánh dấu rằng dấu cách đã được thêm
            }
        }
    }

    string valid_key = key.toStdString();
    // Xóa khoảng trắng ở đầu
    valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));

    ui->lineEdit_timkiemds->setText(QString::fromStdString(valid_key));

    // Kiểm tra nếu key rỗng, không cần tìm kiếm
    if (valid_key.empty()) {
        valid_key=""; // Không gọi hàm tìm kiếm
    }

    // Gọi hàm tìm kiếm với key đã được lọc
    TimKiemTenSach(danh_sach_dau_sach, ui->tableView_dausach, valid_key);
}

void LibraryManagementSystem::on_themSach_pushButton_clicked()
{
    if (KiemTraDaySachKV(danh_sach_dau_sach)){
        QMessageBox::information(this, "Thông báo", "Số sách đẫ đầy");
    }else{
        themdausach themds;
        themds.setModal(true);
        if (themds.exec() == QDialog::Accepted){
            InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach,ui->tableView_dausach);
        }
    }
}

void LibraryManagementSystem::on_themSach_pushButton_2_clicked()
{
    QModelIndex index = ui->tableView_dausach->currentIndex();
    int row = index.row();
    if (row == -1) return;

    int column = 0;

    QVariant data = index.sibling(row, column).data();

    string ma_ISBN = data.toString().toStdString();
    int i = 0;
    for (; i < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->ISBN != ma_ISBN;i++);
    if (danh_sach_dau_sach.node[i]->dms->trangthai == 1 ) {QMessageBox::warning(this, "Lỗi", "Sách đã được mượn.");}
    else if(danh_sach_dau_sach.node[i]->dms->trangthai == 0) {danh_sach_dau_sach.node[i]->dms->trangthai=2;}
    else QMessageBox::warning(this, "Lỗi", "Sách đã được thanh lý.");
    if (ui->lineEdit_timkiemds->text().isEmpty()){
        InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach,ui->tableView_dausach);
    }else{
        string key = ui->lineEdit_timkiemds->text().toStdString();
        InFullTheoTenSach(key,ui->tableView_dausach);
    }
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

void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index) // Hàm sắp xếp theo mã hoặc tên
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
        docGia.Ho = themDocGia.getHo().trimmed().toStdString();
        docGia.Ten = themDocGia.getTen().trimmed().toStdString();
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

void LibraryManagementSystem::on_xoaDocGia_pushButton_clicked() // Xóa độc giả
{
    int currentRow = ui->tableWidget_2->currentRow();

    if (currentRow == -1) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một độc giả để xóa.");
        return;
    }

    QTableWidgetItem* item = ui->tableWidget_2->item(currentRow, 0); // Lấy thông tin từ cột đầu tiên
    if (item) {
        int MATHE = item->text().toInt();
        Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, MATHE);
        if ( p->thong_tin.head_lsms != nullptr || p->thong_tin.TrangThai == TrangThaiCuaThe::Khoa) {
            QMessageBox::warning(this, "Cảnh báo", "Không thể xóa thẻ độc giả này");
        } else {
            Xoa_Doc_Gia(root, MATHE);
            DS_PTR = 0;
            Copy_Cay_Sang_Mang(root);

            ui->tableWidget_2->removeRow(currentRow); // Xóa hàng từ bảng

            CapNhatBang();
            QMessageBox::information(this, "Thông báo", "Độc giả đã được xóa thành công.");
        }
    } else {
        QMessageBox::warning(this, "Cảnh báo", "Không thể lấy thông tin độc giả.");
    }
}

void LibraryManagementSystem::on_tableWidget_2_itemChanged(QTableWidgetItem* item) // Theo dõi thay đổi ở ô
{
    int row = item->row();
    int column = item->column();

    QTableWidgetItem* maTheItem = ui->tableWidget_2->item(row, 0);
    int maThe = maTheItem->text().toInt();

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
        if (newValue != "Đang Hoạt Động" && newValue != "Khóa") {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị trạng thái không hợp lệ. Vui lòng nhập 'Đang Hoạt Động' hoặc 'Bị Khóa'.");
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "TrangThai", newValue.toStdString());
        break;
    default:
        break;
    }
}

void LibraryManagementSystem::on_tableWidget_2_cellDoubleClicked(int row, int column)
{
    if ( column == 0 ) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể thay đổi mã thẻ");
        QTableWidgetItem *item = ui->tableWidget_2->item(row, 0);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Đặt ô này thành chỉ có thể xem
        }
    }
}

//------------------------------------Hàm sử dụng ở thẻ Mượn Trả---------------------------------------------------------------------------------------------
void LibraryManagementSystem::on_muonSach_pushButton_clicked()
{
    muonsach muon_sach;
    muon_sach.setModal(true);
    if (muon_sach.exec() == QDialog::Accepted) {

        // if (themDocGia.exec() == QDialog::Accepted) {

        //     The_Doc_Gia docGia;
        //     docGia.MATHE = LayMaTheNgauNhien();
        //     docGia.Ho = themDocGia.getHo().trimmed().toStdString();
        //     docGia.Ten = themDocGia.getTen().trimmed().toStdString();
        //     if ( themDocGia.getPhai() == "Nam") {
        //         docGia.phai = Phai::Nam;
        //     } else {
        //         docGia.phai = Phai::Nu;
        //     }
        //     docGia.TrangThai = TrangThaiCuaThe::Dang_Hoat_Dong;

        //     Them_Doc_Gia(root, docGia);
        //     Them_Doc_Gia_Vao_Mang(Tim_Kiem(root, docGia.MATHE));
        //     CapNhatBang();
        // }
    }
}


void LibraryManagementSystem::on_traSach_pushButton_clicked()
{
    trasach tra_sach;
    tra_sach.setModal(true);
    tra_sach.exec();
}


void LibraryManagementSystem::on_timSach_pushButton_clicked()
{
    timkiemmasach timkiem;
    timkiem.setModal(true);
    timkiem.exec();
}





