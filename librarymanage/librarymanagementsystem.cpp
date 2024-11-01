#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "intheotheloai.h"
#include "themdausach.h"
#include "queue.h"
#include "The_doc_gia.h"
#include "themdocgia_dialog.h"
#include "Muon_tra.h"
#include "dau_sach.h"
#include "themdocgia_dialog.h"

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
{
    ui->setupUi(this);

    docFileMaThe();
    DocTuFile(danh_sach_dau_sach,danh_muc_sach,ui->tableView_dausach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách
    Doc_Thong_Tin_Tu_File(ui->danhSachTheDocGia_tableWidget); // Load thông tin từ file docgia_100.txt vào cây

    InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach, ui->tableView_dausach); // In bảng đầu sách

    Them_Cay_Vao_QTableWidget(ui->danhSachTheDocGia_tableWidget, root); // In bảng danh sách thẻ độc giả

    inDanhSachDocGiaMuonQuaHan(ui->danhSachQuaHan_tableView, root); // In danh sách độc giả mượn quá hạn
    NhapThongTinVaoTop10(ui->topTenMuonNhieuNhat_tableView,root); // In thông tin top 10 sách nhiều lượt xem

    Saved = true;
}

LibraryManagementSystem::~LibraryManagementSystem()
{
    delete ui;
}

void LibraryManagementSystem::closeEvent(QCloseEvent *event) {
    if (!Saved) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Chưa lưu",
                                      "Bạn có muốn lưu trước khi thoát không?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            ghiMaTheVaoFile();
            Ghi_The_Vao_File();
            InVaoTXT();
            event->accept();
        } else if (reply == QMessageBox::No) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}
void LibraryManagementSystem::tabDauSach() // Chuyển đổi giữa các tab Đầu Sách, Độc Giả, và Mượn Sách
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_dausach);
    InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach, ui->tableView_dausach);
}

void LibraryManagementSystem::tabTheDocGia()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_docgia);
    ui->danhSachTheDocGia_tableWidget->setRowCount(0);
    Them_Cay_Vao_QTableWidget(ui->danhSachTheDocGia_tableWidget, root);
}

void LibraryManagementSystem::tabMuonTra()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_muontra);
}

void LibraryManagementSystem::tabBaoCao()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_baoCao);
}

void LibraryManagementSystem::on_dauSach_pushButton_clicked()
{
    tabDauSach();
}


void LibraryManagementSystem::on_thedocgia_pushButton_clicked()
{
    tabTheDocGia();
}


void LibraryManagementSystem::on_muontra_pushButton_clicked()
{
    tabMuonTra();
}


void LibraryManagementSystem::on_baocao_pushButton_clicked()
{
    tabBaoCao();
}

void LibraryManagementSystem::on_luuFile_pushButton_clicked()
{
    ghiMaTheVaoFile();
    Ghi_The_Vao_File();
    InVaoTXT();
    Saved = true;
}
//------------------------------------Hàm sử dụng ở Đầu Sách-----------------------------------------------------------------------

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
            Saved = false;
        }
    }
}
//Nut Thanh ly
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
    else if(danh_sach_dau_sach.node[i]->dms->trangthai == 0) {danh_sach_dau_sach.node[i]->dms->trangthai=2; Saved = false;}
    else QMessageBox::warning(this, "Lỗi", "Sách đã được thanh lý.");
    if (ui->lineEdit_timkiemds->text().isEmpty()){
        InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach,ui->tableView_dausach);
    }else{
        string key = ui->lineEdit_timkiemds->text().toStdString();
        InFullTheoTenSach(key,ui->tableView_dausach);
    }
}

//------------------------------------Hàm sử dụng ở Tab Độc Giả-----------------------------------------------------------------------
bool LibraryManagementSystem::kiemTraChuoi(QString s) {
    for ( int i = 0; i < s.length(); i++ ) {
        if ( !s[i].isLetter() && !s[i].isSpace() ) {
            return false;
        }
    }
    return true;
}

void LibraryManagementSystem::CapNhatBang()
{
    ui->danhSachTheDocGia_tableWidget->setRowCount(0);

    if ( ui->sapXepDocGia_ComboBox->currentIndex() == 0 ) {
        xoaDanhSachTheoTen();
        Them_Cay_Vao_QTableWidget(ui->danhSachTheDocGia_tableWidget, root);

    } else {
        taoDanhSachTheoTen(root);
        inDanhSachVaoBang(ui->danhSachTheDocGia_tableWidget);
    }
}

void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index) // Hàm sắp xếp theo mã hoặc tên
{
    CapNhatBang();
}

void LibraryManagementSystem::on_themDocGia_pushButton_clicked() // Mở ra cửa số để nhập thông tin độc giả cần thêm
{
    if ( ui->danhSachTheDocGia_tableWidget->rowCount() == 10000 ) {
        QMessageBox::warning(nullptr, "Thông báo", "Đã hết mã thẻ");
        return;
    }
    themDocGia_Dialog themDocGia;
    themDocGia.setModal(true);
    if (themDocGia.exec() == QDialog::Accepted) {

        The_Doc_Gia docGia;
        int maThe = layMaThe();
        while ( true ) { // Tìm mã thẻ chưa tồn tại trong danh sách
            if ( Tim_Kiem(root, maThe ) == nullptr ) { // Chỉ dừng khi tìm được
                break;
            }
            maThe = layMaThe();
        }
        docGia.MATHE = maThe;
        docGia.Ho = themDocGia.getHo().trimmed().toStdString();
        docGia.Ten = themDocGia.getTen().trimmed().toStdString();
        if ( themDocGia.getPhai() == "Nam") {
            docGia.phai = Phai::Nam;
        } else {
            docGia.phai = Phai::Nu;
        }
        docGia.TrangThai = Dang_Hoat_Dong;

        Them_Doc_Gia(root, docGia);
        themVaoDanhSachTheoTenCoThuTu(Tim_Kiem(root, docGia.MATHE));
        CapNhatBang();
        Saved = false;
    }
}

void LibraryManagementSystem::on_xoaDocGia_pushButton_clicked() // Xóa độc giả
{
    int currentRow = ui->danhSachTheDocGia_tableWidget->currentRow();

    if (currentRow == -1) {
        QMessageBox::warning(this, "Cảnh báo", "Vui lòng chọn một độc giả để xóa.");
        return;
    }

    QTableWidgetItem* item = ui->danhSachTheDocGia_tableWidget->item(currentRow, 0); // Lấy thông tin từ cột đầu tiên
    if (item) {
        int MATHE = item->text().toInt();
        Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, MATHE);
        if ( p->thong_tin.head_lsms != nullptr || p->thong_tin.TrangThai == TrangThaiCuaThe::Khoa) {
            QMessageBox::warning(this, "Cảnh báo", "Không thể xóa thẻ độc giả này.");
        } else {
            Xoa_Doc_Gia(root, MATHE);
            taoDanhSachTheoTen(root);

            ui->danhSachTheDocGia_tableWidget->removeRow(currentRow); // Xóa hàng từ bảng

            CapNhatBang();
            Saved = false;
            QMessageBox::information(this, "Thông báo", "Độc giả đã được xóa thành công.");
        }
    } else {
        QMessageBox::warning(this, "Cảnh báo", "Không thể lấy thông tin độc giả.");
    }
    Saved = false;
}

void LibraryManagementSystem::on_danhSachTheDocGia_tableWidget_itemChanged(QTableWidgetItem* item) // Theo dõi thay đổi ở ô
{
    int row = item->row();
    int column = item->column();

    QTableWidgetItem* maTheItem = ui->danhSachTheDocGia_tableWidget->item(row, 0);
    int maThe = maTheItem->text().toInt();

    QString newValue = item->text();
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, maThe);

    switch (column) {
    case 1:
        if (kiemTraChuoi(newValue) == false ) {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị họ không hợp lệ.");
            item->setText(QString::fromStdString(p->thong_tin.Ho));
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ho", newValue.toStdString());
        break;
    case 2:
        if (kiemTraChuoi(newValue) == false ) {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị tên không hợp lệ.");
            item->setText(QString::fromStdString(p->thong_tin.Ten));
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Ten", newValue.toStdString());
        break;
    case 3:
        if (newValue != "Nam" && newValue != "Nữ") {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị phái không hợp lệ. Vui lòng nhập 'Nam' hoặc 'Nữ'.");
            item->setText(QString::fromStdString(p->thong_tin.phai == Nam ? "Nam":"Nữ"));
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "Phai", newValue.toStdString());
        break;
    case 4:
        if (newValue != "Đang Hoạt Động" && newValue != "Khóa") {
            QMessageBox::warning(this, "Cảnh báo", "Giá trị trạng thái không hợp lệ. Vui lòng nhập 'Đang Hoạt Động' hoặc 'Bị Khóa'.");
            item->setText(QString::fromStdString(p->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang hoạt động":"Khóa"));
            return;
        }
        Cap_Nhat_Thong_Tin_Doc_Gia(maThe, "TrangThai", newValue.toStdString());
        break;
    default:
        break;
        Saved = false;
    }
}

void LibraryManagementSystem::on_danhSachTheDocGia_tableWidget_cellDoubleClicked(int row, int column)
{
    if ( column == 0 ) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể thay đổi mã thẻ.");
        QTableWidgetItem *item = ui->danhSachTheDocGia_tableWidget->item(row, 0);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}


//------------------------------------Hàm sử dụng ở thẻ Mượn Trả---------------------------------------------------------------------------------------------


int LibraryManagementSystem::getmaThe() {
    return ui->lineEdit_maThe->text().toInt();
}

void LibraryManagementSystem::inThongTin(const int& ma_the) {

    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, ma_the);
    ui->tableWidget_muonTra->setRowCount(0);
    string hovaten = p->thong_tin.Ho + " " + p->thong_tin.Ten;
    DanhSachMUONTRA *current = p->thong_tin.head_lsms;

    ui->lineEdit_hoTen->setReadOnly(true);
    ui->lineEdit_Phai->setReadOnly(true);
    ui->lineEdit_trangThai->setReadOnly(true);

    ui->lineEdit_hoTen->setText(QString::fromStdString(hovaten));
    ui->lineEdit_Phai->setText(p->thong_tin.phai == Nam ? "Nam" : "Nữ");
    ui->lineEdit_trangThai->setText(p->thong_tin.TrangThai == Dang_Hoat_Dong ? "Dang Hoạt Động": "Khóa");

    while ( current != nullptr ) {
        if ( current->data.trangthai == 0 ) {
            int indexRow = ui->tableWidget_muonTra->rowCount();
            QCheckBox *checkBox = new QCheckBox(this);
            ui->tableWidget_muonTra->insertRow(indexRow);
            ui->tableWidget_muonTra->setCellWidget(indexRow, 0, checkBox);
            ui->tableWidget_muonTra->setItem(indexRow, 1, new QTableWidgetItem(QString::fromStdString(current->data.masach)));
            ui->tableWidget_muonTra->setItem(indexRow, 2, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach))));
            ui->tableWidget_muonTra->setItem(indexRow, 3, new QTableWidgetItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
            ui->tableWidget_muonTra->setItem(indexRow, 4, new QTableWidgetItem(QString::number(DemSoNgay(current->data.NgayMuon, NgayHomNay()))));
            indexRow++;
        }
        current = current->next;
    }
}

void LibraryManagementSystem::on_lineEdit_maThe_textChanged(const QString &arg1)
{
    if ( arg1.isEmpty() ) {
        ui->lineEdit_maThe->setStyleSheet("background-color: white;");
        while (ui->tableWidget_muonTra->rowCount() > 0) {
            ui->tableWidget_muonTra->removeRow(0);
        }
        ui->lineEdit_hoTen->setText("");
        ui->lineEdit_Phai->setText("");
        ui->lineEdit_trangThai->setText("");
        return;
    }
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, arg1.toInt());
    if ( p != nullptr ) {
        inThongTin(p->thong_tin.MATHE);
        ui->lineEdit_maThe->setStyleSheet("background-color: lightgreen;");
    } else {
        ui->lineEdit_hoTen->setText("");
        ui->lineEdit_Phai->setText("");
        ui->lineEdit_trangThai->setText("");
        ui->lineEdit_maThe->setStyleSheet("background-color: lightcoral;");
        while (ui->tableWidget_muonTra->rowCount() > 0) {
            ui->tableWidget_muonTra->removeRow(0);
        }
    }
    ui->tableWidget_muonTra->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

//===================


void LibraryManagementSystem::inThongTinmaSach(string key_ma_sach) {
    // Đưa chuỗi về dạng chữ thường
    string key_tensach = ChuyenMaSachThanhTenSach(danh_sach_dau_sach, key_ma_sach);
    ChuyenVeChuThuong(key_tensach);
    ui->lineEdit_tenSach->setReadOnly(true);
    ui->lineEdit_tacGia->setReadOnly(true);
    ui->lineEdit_trangThaiSach->setReadOnly(true);

    bool found = false; // Đánh dấu nếu tìm thấy sách

    for (int i = 0; i < danh_sach_dau_sach.demsach; i++) {
        string ten_sach = danh_sach_dau_sach.node[i]->tensach;
        ChuyenVeChuThuong(ten_sach);

        if (ten_sach == key_tensach) {
            int trangthai = danh_sach_dau_sach.node[i]->dms->trangthai;
            string trang_thai_std;

            ui->lineEdit_tenSach->setText(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach));
            ui->lineEdit_tacGia->setText(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia));

            switch(trangthai) {
            case 0: trang_thai_std = "Có thể mượn"; break;
            case 1: trang_thai_std = "Đã được mượn"; break;
            case 2: trang_thai_std = "Đã thanh lý"; break;
            }
            ui->lineEdit_trangThaiSach->setText(QString::fromStdString(trang_thai_std));

            found = true;
            break; // Dừng sau khi tìm thấy sách đầu tiên
        }
    }

    // Nếu không tìm thấy sách, đặt lại các trường hiển thị
    if (!found) {
        ui->lineEdit_tenSach->clear();
        ui->lineEdit_tacGia->clear();
        ui->lineEdit_trangThaiSach->clear();
    }
}


void LibraryManagementSystem::on_lineEdit_maSach_textChanged(const QString &arg1) {
    QString key;
    bool lastWasSpace = false;

    for (QChar c : arg1) {
        if (c.isDigit() || c.isPunct()) {
            key += c;
            lastWasSpace = false;
        } else if (c.isSpace() && !lastWasSpace) {
            key += ' ';
            lastWasSpace = true;
        }
    }

    string valid_key = key.toStdString();
    valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));

    // Cập nhật lại chuỗi đã lọc
    if (valid_key != arg1.toStdString()) {
        ui->lineEdit_maSach->setText(QString::fromStdString(valid_key));
    }

    // Nếu chuỗi tìm kiếm rỗng, không thực hiện tìm kiếm
    if (!valid_key.empty()) {
        inThongTinmaSach(valid_key);
    } else {
        // Nếu ô tìm kiếm rỗng, xóa các trường hiển thị
        ui->lineEdit_tenSach->clear();
        ui->lineEdit_tacGia->clear();
        ui->lineEdit_trangThaiSach->clear();
    }
}

//--------------------------------------

void LibraryManagementSystem::on_traSach_pushButton_clicked()
{
    int row = 0;
    for (; row < ui->tableWidget_muonTra->rowCount(); row++) {
        QWidget *traSach_widget = ui->tableWidget_muonTra->cellWidget(row, 0);
        QCheckBox *traSach_checkBox = qobject_cast<QCheckBox *>(traSach_widget);
        if ( traSach_checkBox->isChecked() ) {
            QString ma_sach =ui->tableWidget_muonTra->item(row, 1)->text();
            string maSach = ma_sach.toStdString();
            TraSach(getmaThe(), maSach);
        }
    }
    Saved = false;
}

string LibraryManagementSystem::getmaSach() {
    return ui->lineEdit_maSach->text().toStdString();
}

void LibraryManagementSystem::on_muonSach_pushButton_clicked()
{
    MuonSach(getmaThe(), getmaSach());
    Saved = false;
}


