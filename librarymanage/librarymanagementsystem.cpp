#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "intheotheloai.h"
#include "thanh_ly.h"
#include "themdausach.h"
#include "queue.h"
#include "The_doc_gia.h"
#include "themdocgia_dialog.h"
#include "Muon_tra.h"
#include "dau_sach.h"
#include "themdocgia_dialog.h"

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    ,model_Dausach(new QStandardItemModel(0, 7, this))
    , ui(new Ui::LibraryManagementSystem)
{
    ui->setupUi(this);
    DocTuFile(danh_sach_dau_sach,this); // Load thông tin từ file Danh_sach_dau_sach.txt vào Bảng Danh Sách Đầu Sách

    docFileMaThe();
    docFileThongTinTheDocGia(ui->danhSachTheDocGia_tableWidget);

    InToanBoDauSach(danh_sach_dau_sach,danh_sach_dau_sach.soluongdausach, ui->tableView_dausach,model_Dausach); // In bảng đầu sách

    connect(ui->tableView_dausach, &QTableView::doubleClicked, this, &LibraryManagementSystem::HienMaSach);
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
            ghiThongTinTheDocGia();
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
    InToanBoDauSach(danh_sach_dau_sach,danh_sach_dau_sach.soluongdausach, ui->tableView_dausach,model_Dausach);
}

void LibraryManagementSystem::tabTheDocGia()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_docgia);
    CapNhatBang();
}

void LibraryManagementSystem::tabMuonTra()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_muontra);
}

void LibraryManagementSystem::tabBaoCao()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_baoCao);
    inDanhSachDocGiaMuonQuaHan(ui->danhSachQuaHan_tableView, root); // In danh sách độc giả mượn quá hạn
    DatLaiSoLuotMuon();
    NhapThongTinVaoTop10(ui->topTenMuonNhieuNhat_tableView,root);
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
    ghiThongTinTheDocGia();
    InVaoTXT();
    Saved = true;
}
//------------------------------------Hàm sử dụng ở Đầu Sách-----------------------------------------------------------------------

void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai;
    intheloai.setModal(true);
    intheloai.setWindowTitle("In danh sách theo thể loại");
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
    TimKiemTenSach(danh_sach_dau_sach, ui->tableView_dausach,model_Dausach, valid_key);


}

void LibraryManagementSystem::HienMaSach(const QModelIndex &index) {
    // Kiểm tra nếu lineEdit_timkiemds rỗng
    if (ui->lineEdit_timkiemds->text().isEmpty()) {
        return; // Không thực hiện thao tác nào nếu lineEdit rỗng
    }

    if (index.isValid()) {
        // Lấy dữ liệu của cột đầu tiên của hàng được nhấn
        QVariant data = index.siblingAtColumn(0).data();
        // Kiểm tra và in ra dữ liệu nếu có
        if (data.isValid()) {
        string Ma_ISBN = data.toString().toStdString();
        HienMaSachTrongTableMoi(Ma_ISBN,ui->tableView_dausach,model_Dausach,ui->lineEdit_timkiemds->text().toStdString());
        }
    }
}

void LibraryManagementSystem::on_themSach_pushButton_clicked()
{
    if (KiemTraDaySachKV(danh_sach_dau_sach)){
        QMessageBox::information(this, "Thông báo", "Số sách đẫ đầy");
    }else{
        themdausach themds;
        themds.setModal(true);
        if (themds.exec() == QDialog::Accepted){
            InToanBoDauSach(danh_sach_dau_sach,danh_sach_dau_sach.soluongdausach,ui->tableView_dausach,model_Dausach);
            Saved = false;
        }
    }
}

void LibraryManagementSystem::on_thanhly_pushButton_clicked()
{
    QModelIndex index = ui->tableView_dausach->currentIndex();
    int row = index.row();
    if (row == -1) {QMessageBox::information(this, "Thông báo", "Vui lòng chọn sách thanh lý.");return;}

    int column = 0;

    QVariant data = index.sibling(row, column).data();
    if (data.isValid() == false) {QMessageBox::warning(this,"Cảnh báo","Vui lòng chọn đầu sách chứa ISBN");return;}
    string ma_ISBN = data.toString().toStdString();

    int DS_index = TimKiemViTriDauSach(ma_ISBN);
    bool allowed = false;
    for (DanhMucSach* cur = danh_sach_dau_sach.node[DS_index]->dms;cur!=nullptr;cur=cur->next){
        if(cur->trangthai == 0){
            allowed = true;
        }
    }
    if(allowed != true){
        QMessageBox::warning(this,"Cảnh báo","Không có sách có thể thanh lý");
        return;
    }else{
        Thanh_ly thanhly(DS_index);
        thanhly.setModal(true);
        thanhly.setWindowTitle("In danh sách theo thể loại");
        if (thanhly.exec() == QDialog::Accepted){
            string TuKhoa = ui->lineEdit_timkiemds->text().toStdString();
            if ( !TuKhoa.empty()){//nếu đang tìm kiếm và thực hiện thao tác thanh lý
                HienMaSachTrongTableMoi(ma_ISBN,ui->tableView_dausach,model_Dausach,TuKhoa);
            }
            Saved = false;
        }
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
        inDanhSachTheDocGiaTheoMaSo(ui->danhSachTheDocGia_tableWidget, root);
    } else {
        xoaDanhSachTheoTen();
        taoDanhSachTheoTen(root);
        inDanhSachTheDocGiaTheoTen(ui->danhSachTheDocGia_tableWidget);
    }
}

void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index) // Hàm sắp xếp theo mã hoặc tên
{
    CapNhatBang();
}

void LibraryManagementSystem::on_themDocGia_pushButton_clicked() // Mở ra cửa số để nhập thông tin độc giả cần thêm
{
    themDocGia_Dialog themDocGia;

    if ( ui->danhSachTheDocGia_tableWidget->rowCount() == MAXRANDOM ) { // Kiểm tra đã hết mã thẻ hay chưa
        QMessageBox::warning(nullptr, "Thông báo", "Đã hết mã thẻ");
        themDocGia.close();
        return;
    }
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
        QString hoVaTen = themDocGia.getHoVaTen();
        int viTriDeTachHoVaTen = hoVaTen.lastIndexOf(" ") + 1;

        docGia.Ho = hoVaTen.mid(0, viTriDeTachHoVaTen).toStdString();
        docGia.Ten = hoVaTen.mid(viTriDeTachHoVaTen).toStdString();
        if ( themDocGia.getPhai() == "Nam") {
            docGia.phai = Phai::Nam;
        } else {
            docGia.phai = Phai::Nu;
        }
        docGia.TrangThai = Dang_Hoat_Dong;

        Them_Doc_Gia(root, docGia);
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
    ui->lineEdit_trangThai->setText(p->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động": "Khóa");

    while ( current != nullptr ) {
        if ( current->data.trangthai == 0 || current->data.trangthai == 2) {
            int indexRow = ui->tableWidget_muonTra->rowCount();
            QCheckBox *checkBox = new QCheckBox(this);
            ui->tableWidget_muonTra->insertRow(indexRow);
            ui->tableWidget_muonTra->setCellWidget(indexRow, 0, checkBox);
            ui->tableWidget_muonTra->setItem(indexRow, 1, new QTableWidgetItem(QString::fromStdString(current->data.masach)));
            ui->tableWidget_muonTra->setItem(indexRow, 2, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach))));
            ui->tableWidget_muonTra->setItem(indexRow, 3, new QTableWidgetItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
            ui->tableWidget_muonTra->setItem(indexRow, 4, new QTableWidgetItem(QString::number(DemSoNgay(current->data.NgayMuon, NgayHomNay()))));
            ui->tableWidget_muonTra->setItem(indexRow, 5, new QTableWidgetItem(current->data.trangthai == 2 ? "Mất Sách" : "Chưa Trả"));
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
    if(key_ma_sach.size() == 13 || key_ma_sach.size() == 17) {
        ui->lineEdit_maSach->setStyleSheet("background-color: lightgreen");
    }
    else if(key_ma_sach.size() > 18) {
        if(TonTaiMaSachDS(key_ma_sach)) {;
            ui->lineEdit_maSach->setStyleSheet("background-color: lightgreen");
        }
        else {
            ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
            ui->lineEdit_tenSach->clear();
            ui->lineEdit_tacGia->clear();
            ui->lineEdit_trangThaiSach->clear();
            return;
        }
    } else {
        ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
        return;
    }
    int vitri = TimKiemViTriDauSach(key_ma_sach);
    ui->lineEdit_tenSach->setReadOnly(true);
    ui->lineEdit_tacGia->setReadOnly(true);
    ui->lineEdit_trangThaiSach->setReadOnly(true);

    if (vitri != -1 ) {
        string trang_thai_std;

        ui->lineEdit_tenSach->setText(QString::fromStdString(danh_sach_dau_sach.node[vitri]->tensach));
        ui->lineEdit_tacGia->setText(QString::fromStdString(danh_sach_dau_sach.node[vitri]->tacgia));
        DanhMucSach *danh_muc_sach = danh_sach_dau_sach.node[vitri]->dms;
        int trangthai;
        if (key_ma_sach.size() > 17) {
            while(danh_muc_sach != nullptr) {
                trangthai = danh_muc_sach->trangthai;
                if(danh_muc_sach->masach == key_ma_sach) {
                    switch(trangthai) {
                    case 0: trang_thai_std = "Có thể mượn"; break;
                    case 1: trang_thai_std = "Đã được mượn"; break;
                    case 2: trang_thai_std = "Đã thanh lý"; break;
                    }
                    ui->lineEdit_trangThaiSach->setText(QString::fromStdString(trang_thai_std));
                    break;
                }
                danh_muc_sach = danh_muc_sach->next;
            }
        } else if (key_ma_sach.size() == 13 || key_ma_sach.size() == 17) {
            while(danh_muc_sach != nullptr) {
                trangthai = danh_muc_sach->trangthai;
                if(trangthai == 0) {
                    trang_thai_std = "Có thể mượn";
                    break;
                } else {
                    switch(trangthai) {
                    case 1: trang_thai_std = "Đã được mượn"; break;
                    case 2: trang_thai_std = "Đã thanh lý"; break;
                    }
                }
                danh_muc_sach = danh_muc_sach->next;
            }

        }
        ui->lineEdit_trangThaiSach->setText(QString::fromStdString(trang_thai_std));
    } else {
        ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
        ui->lineEdit_tenSach->clear();
        ui->lineEdit_tacGia->clear();
        ui->lineEdit_trangThaiSach->clear();
    }
}

void LibraryManagementSystem::on_lineEdit_maSach_textChanged(const QString &arg1)
{
    QString filteredText;
    bool lastWasSpace = false;

    // Lọc chuỗi để loại bỏ các ký tự không cần thiết
    for (QChar c : arg1) {
        if (c.isDigit() || c.isPunct()) {
            filteredText += c;
            lastWasSpace = false;
        } else if (c.isSpace() && !lastWasSpace) {
            filteredText += ' ';
            lastWasSpace = true;
        }
    }

    // Xóa khoảng trắng đầu và cuối của chuỗi
    filteredText = filteredText.trimmed();

    // Cập nhật lại chuỗi đã lọc nếu có thay đổi
    if (filteredText != arg1) {
        ui->lineEdit_maSach->setText(filteredText);
    }

    // Nếu chuỗi tìm kiếm không rỗng, thực hiện tìm kiếm
    if (!filteredText.isEmpty()) {
        if(filteredText.length() == 13 || filteredText.length() >= 17) {
            inThongTinmaSach(filteredText.toStdString());
        }
        else {
            ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
            ui->lineEdit_tenSach->clear();
            ui->lineEdit_tacGia->clear();
            ui->lineEdit_trangThaiSach->clear();
        }
    } else {
        // Nếu ô tìm kiếm rỗng, xóa các trường hiển thị thông tin
        ui->lineEdit_maSach->setStyleSheet("background-color: white");
        ui->lineEdit_tenSach->clear();
        ui->lineEdit_tacGia->clear();
        ui->lineEdit_trangThaiSach->clear();
    }
}


//--------------------------------------

void LibraryManagementSystem::on_traSach_pushButton_clicked()
{
    int row = 0;
    bool thongbao = 0;
    for (; row < ui->tableWidget_muonTra->rowCount(); row++) {
        QWidget *traSach_widget = ui->tableWidget_muonTra->cellWidget(row, 0);
        QCheckBox *traSach_checkBox = qobject_cast<QCheckBox *>(traSach_widget);
        if ( traSach_checkBox->isChecked() ) {
            QString ma_sach =ui->tableWidget_muonTra->item(row, 1)->text();
            string maSach = ma_sach.toStdString();
            TraSach(getmaThe(), maSach);
            if(thongbao == 0) {
                QMessageBox::information(nullptr, "Thông báo", "Trả sách thành công.");
                thongbao = 1;
            }
        }
    }
    ui->tableWidget_muonTra->setRowCount(0);
    inThongTin(getmaThe());
    ui->lineEdit_maSach->clear();
    Saved = false;
}

string LibraryManagementSystem::getmaSachCoTheMuon() {
    string ma_ISBN =  ui->lineEdit_maSach->text().toStdString();
    int vitri = TimKiemViTriDauSach(ma_ISBN);
    if (vitri != -1) {
        DanhMucSach *danh_muc_sach= danh_sach_dau_sach.node[vitri]->dms;
        while (danh_muc_sach != nullptr) {
            if(danh_muc_sach->trangthai == 0) {
                return danh_muc_sach->masach;
            }
            danh_muc_sach = danh_muc_sach->next;
        }
    }
    return "";
}

void LibraryManagementSystem::on_muonSach_pushButton_clicked()
{
    if(!ui->lineEdit_maSach->text().isEmpty() && !ui->lineEdit_maThe->text().isEmpty()) {
        string maSach = ui->lineEdit_maSach->text().toStdString();
        if(maSach.size() == 13 || maSach.size() == 17) {
            if(getmaSachCoTheMuon() == "") {
                QMessageBox::information(nullptr, "Thông báo", "Không thể mượn sách.");
                return;
            }
            MuonSach(getmaThe(), getmaSachCoTheMuon());
            ui->tableWidget_muonTra->setRowCount(0);
            inThongTin(getmaThe());
            inThongTinmaSach(getmaSachCoTheMuon());
        }
        else {
            MuonSach(getmaThe(), maSach);
            ui->tableWidget_muonTra->setRowCount(0);
            inThongTin(getmaThe());
            inThongTinmaSach(maSach);
        }
        Saved = false;
    } else {
        QMessageBox::information(nullptr, "Thông báo", "Bạn chưa nhập mã ISBN hoặc mã thẻ độc giả để mượn sách.");
    }

}



void LibraryManagementSystem::on_MatSach_pushButton_2_clicked()
{

    bool thongbao[3] = {0, 0, 0};
    for(int row = 0; row < ui->tableWidget_muonTra->rowCount(); row ++) {
        QWidget *traSach_widget = ui->tableWidget_muonTra->cellWidget(row, 0);
        QCheckBox *traSach_checkBox = qobject_cast<QCheckBox *>(traSach_widget);
        if ( traSach_checkBox->isChecked() ) {
            QString ma_sach =ui->tableWidget_muonTra->item(row, 1)->text();
            string maSach = ma_sach.toStdString();
            QString trang_thai = ui->tableWidget_muonTra->item(row, 5)->text();
            string trangthai = trang_thai.toStdString();
            if(trangthai == "Chưa Trả") {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(
                    this,
                    "Đền sách",
                    "Bạn đã đền sách chưa?",
                    QMessageBox::Yes | QMessageBox::No
                );
                if (reply == QMessageBox::Yes) {
                    DaDenSach(getmaThe(), maSach);
                    if(thongbao[0] == false) {
                        QMessageBox::information(this, "Thông báo", "Sách đã được đánh dấu là đã đền.");
                        inThongTin(getmaThe());
                        thongbao[0] = true;
                    }
                } else {
                    ChuaDenSach(getmaThe(), maSach);
                    if(thongbao[1] == false) {
                        QMessageBox::information(this, "Thông báo", "Sách đã được đánh dấu là chưa đền.");
                        inThongTin(getmaThe());
                        thongbao[1] = true;
                    }
                }
            }
            else {
                DaDenSach(getmaThe(), maSach);
                if(thongbao[2] == false) {
                    QMessageBox::information(this, "Thông báo", "Sách đã được đánh dấu là đã đền.");
                    inThongTin(getmaThe());
                    thongbao[2] = true;
                }
            }
        }
    }
}







