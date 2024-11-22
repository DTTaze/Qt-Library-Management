#include "librarymanagementsystem.h"
#include "./ui_librarymanagementsystem.h"
#include "muonsach.h"
#include "trasach.h"
#include "intheotheloai.h"
#include "thanh_ly.h"
#include "themdausach.h"
#include "queue.h"
#include "Muon_tra.h"
#include "dau_sach.h"
#include "danhmucsach.h"
#include "xoa_dau_sach.h"
#include "The_doc_gia.h"
#include "themDocGia_dialog.h"
#include "hieuChinhDocGia_dialog.h"
#include "edit_sach.h"
#include "nhap_dausach.h"
#include "xoaDocGia_dialog.h"

LibraryManagementSystem::LibraryManagementSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryManagementSystem)
{
    ui->setupUi(this);
    QLocale::setDefault(QLocale(QLocale::Vietnamese, QLocale::Vietnam));
    DocTuFileDauSach(this);

    InToanBoDauSach(ui->tableWidget_dausach);

    docFileMaThe();
    docFileThongTinTheDocGia();

    setupbaocao_pushButton();

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
            GhiDauSachVaoFile();
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

void LibraryManagementSystem::on_luuFile_pushButton_clicked()
{
    ghiMaTheVaoFile();
    ghiThongTinTheDocGia();
    GhiDauSachVaoFile();
    Saved = true;
    QMessageBox::information(this,"Thông báo","Lưu thành công.");
}

void LibraryManagementSystem::tabDauSach()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_dausach);
    InToanBoDauSach(ui->tableWidget_dausach);
}

void LibraryManagementSystem::on_dauSach_pushButton_clicked()
{
    tabDauSach();
}

void LibraryManagementSystem::tabTheDocGia()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_docgia);
    CapNhatBang();
}

void LibraryManagementSystem::on_thedocgia_pushButton_clicked()
{
    tabTheDocGia();
}

void LibraryManagementSystem::tabMuonTra()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_muontra);
}

void LibraryManagementSystem::on_muontra_pushButton_clicked()
{
    tabMuonTra();
}

void LibraryManagementSystem::showTop10SachPage()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_baocao);
    ui->stackedWidget->setCurrentWidget(ui->page_Top10);
    int SoLuongSach = 0;
    SachMuon DanhSachSachMuon[danh_sach_dau_sach.soluongdausach];

    Top10QuyenSachNhieuLuotMuonNhat(SoLuongSach, DanhSachSachMuon,ui->Top10Sach_tableWidget);
}

void LibraryManagementSystem::showMuonQuaHanPage()
{
    ui->stackedWidget_infor->setCurrentWidget(ui->page_baocao);
    ui->stackedWidget->setCurrentWidget(ui->page_MuonQuaHan);

    inDanhSachDocGiaMuonQuaHan(ui->danhSachQuaHan_tableWidget, root);
}

void LibraryManagementSystem::setupbaocao_pushButton() {
    QMenu *menu = new QMenu(this);

    QAction *top10SachAction = new QAction("Top 10 Sách", this);
    QAction *muonSachQuaHanAction = new QAction("Mượn Sách Quá Hạn", this);

    menu->addAction(top10SachAction);
    menu->addAction(muonSachQuaHanAction);

    menu->setStyleSheet(
        "QMenu {"
        "   background-color: #ffffff;"
        "   border: none;"
        "   padding: 5px 0;"
        "   width: 225px;"
        "}"
        "QMenu::item {"
        "   padding: 13px 16px;"
        "   font-family: 'Roboto Mono', sans-serif;"
        "   font-size: 18px;"
        "   letter-spacing: 0.8px;"
        "   color: black;"
        "   font-weight: bold;"
        "}"
        "QMenu::item:selected {"
        "   background-color: #C4C4C4;"
        "}"
        "QMenu::item:pressed {"
        "   background-color: #C4C4C4;"
        "   border-top: 4px solid;"
        "}"
        "QMenu::item:disabled {"
        "   background-color: #D6D6D6;"
        "   color: #7F7F7F;"
        "}"
    );

    ui->baocao_pushButton->setMenu(menu);

    connect(top10SachAction, &QAction::triggered, this, &LibraryManagementSystem::showTop10SachPage);
    connect(muonSachQuaHanAction, &QAction::triggered, this, &LibraryManagementSystem::showMuonQuaHanPage);
}

//------------------------------------Hàm sử dụng ở Đầu Sách-----------------------------------------------------------------------
void LibraryManagementSystem::on_lineEdit_timkiemds_textChanged(const QString text) {
    QString key ;
    bool lastWasSpace = false;

    for (QChar c : text) {
        if (c.isLetter() || c.isDigit() || c.isPunct() || c.isSymbol()) {
            key += c;
            lastWasSpace = false;
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                key += ' ';
                lastWasSpace = true;
            }
        }
    }

    string valid_key = key.toStdString();
    valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));

    ui->lineEdit_timkiemds->setText(QString::fromStdString(valid_key));

    if (valid_key.empty()) {
        valid_key="";
    }

    TimKiemTenSach(ui->tableWidget_dausach, valid_key);
}

void LibraryManagementSystem::on_inTheLoai_pushButton_clicked()
{
    InTheoTheLoai intheloai;
    intheloai.setModal(true);
    intheloai.setWindowTitle("In danh sách theo thể loại");
    intheloai.exec();
}

void LibraryManagementSystem::MoCuaSoDanhMucSach(int ViTriDauSach) {
    Danhmucsach dms(ViTriDauSach);
    dms.setModal(true);
    dms.setWindowTitle("Danh mục sách");
    dms.exec();
}

void LibraryManagementSystem::on_tableWidget_dausach_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QTableWidgetItem *headerItem = ui->tableWidget_dausach->verticalHeaderItem(row);
    if (headerItem) {
        int ViTriDauSach = headerItem->text().toInt();
        MoCuaSoDanhMucSach(ViTriDauSach);
    }
}

void LibraryManagementSystem::MoCuaSoThemSach(){
    themdausach themds;
    themds.setModal(true);
    themds.setWindowTitle("Thêm sách");
    if (themds.exec() == QDialog::Accepted){
        InToanBoDauSach(ui->tableWidget_dausach);
        Saved = false;
    }
}

void LibraryManagementSystem::on_themSach_pushButton_clicked()
{
    if (DayDauSach()){
        QMessageBox::information(this, "Thông báo", "Số sách đẫ đầy");
        return;
    }
    MoCuaSoThemSach();
}

void LibraryManagementSystem::MoCuaSoEditSach(int i_ds){
    Edit_sach edit(i_ds);
    edit.setModal(true);
    edit.setWindowTitle("Sửa sách");
    if (edit.exec() ==  QDialog::Accepted){
        if (ui->lineEdit_timkiemds->text().isEmpty()){
            InToanBoDauSach(ui->tableWidget_dausach);
        }else{
            string key = ui->lineEdit_timkiemds->text().toStdString();
            InTheoTenTimKiem(key,ui->tableWidget_dausach);
        }
        Saved = false;
    }
}

void LibraryManagementSystem::on_editSach_pushButton_clicked()
{
    QModelIndex index = ui->tableWidget_dausach->currentIndex();
    int row = index.row();
    QTableWidgetItem *headerItem = ui->tableWidget_dausach->verticalHeaderItem(row);
    if (headerItem){
        int index_dausach = headerItem->text().toInt();
        MoCuaSoEditSach(index_dausach);
    }else{
        MoCuaSoEditSach(-1);
    }
}

void LibraryManagementSystem::MoCuaSoXoaSach(int i_ds){
    Xoa_dau_sach del_dausach(i_ds);
    del_dausach.setModal(true);
    del_dausach.setWindowTitle("Xóa đầu sách");
    if (del_dausach.exec() == QDialog::Accepted){
        InToanBoDauSach(ui->tableWidget_dausach);
        Saved = false;
    }
}

void LibraryManagementSystem::on_xoaSach_pushButton_clicked()
{
    if (danh_sach_dau_sach.soluongdausach <= 0){QMessageBox::critical(nullptr,"Lỗi","Không có đầu sách để xóa."); return;}
    QModelIndex index = ui->tableWidget_dausach->currentIndex();
    int row = index.row();
    QTableWidgetItem *headerItem = ui->tableWidget_dausach->verticalHeaderItem(row);
    if (headerItem){
        int index_dausach = headerItem->text().toInt();
        if (TonTaiMaSachDaDuocMuonTrongDauSach(index_dausach)){
            QMessageBox::critical(nullptr,"Lỗi","Tồn tại mã sách đang được mượn\nKhông thể xóa đầu sách.");
            return;
        }
        MoCuaSoXoaSach(index_dausach);
    }else{
        MoCuaSoXoaSach(-1);
    }
}

void LibraryManagementSystem::MoCuaSoThanhLySach(int i_ds){
    Thanh_ly thanhly(i_ds);
    thanhly.setModal(true);
    thanhly.setWindowTitle("Thanh lý sách");
    if (thanhly.exec() == QDialog::Accepted){
        Saved = false;
    }
}

void LibraryManagementSystem::on_thanhly_pushButton_clicked()
{
    QModelIndex index = ui->tableWidget_dausach->currentIndex();
    int row = index.row();
    QTableWidgetItem *headerItem = ui->tableWidget_dausach->verticalHeaderItem(row);
    if(headerItem){
        int DS_index = headerItem->text().toInt();
        bool allowed = false;
        for (DanhMucSach* cur = danh_sach_dau_sach.node[DS_index]->dms;cur!=nullptr;cur=cur->next){
            if(cur->trangthai == 0){
                allowed = true;
                break;
            }
        }
        if(allowed != true){
            QMessageBox::warning(this,"Cảnh báo","Không có sách có thể thanh lý");
            return;
        }else{
            MoCuaSoThanhLySach(DS_index);
        }
    }else{
        MoCuaSoThanhLySach(-1);
    }
}

void LibraryManagementSystem::MoCuaSoNhapDauSach(int i_ds){
    nhap_dausach nhap_dausach(i_ds);
    nhap_dausach.setModal(true);
    nhap_dausach.setWindowTitle("Nhập đầu sách");
    if (nhap_dausach.exec() == QDialog::Accepted){
        InToanBoDauSach(ui->tableWidget_dausach);
        Saved = false;
    }
}

void LibraryManagementSystem::on_nhapSach_pushButton_clicked()
{
    QModelIndex index = ui->tableWidget_dausach->currentIndex();
    int row = index.row();
    QTableWidgetItem *headerItem = ui->tableWidget_dausach->verticalHeaderItem(row);
    if (headerItem){
        int index_dausach = headerItem->text().toInt();
        MoCuaSoNhapDauSach(index_dausach);
    }else{
        MoCuaSoNhapDauSach(-1);
    }
}


//------------------------------------Hàm sử dụng ở Tab Độc Giả-----------------------------------------------------------------------
void LibraryManagementSystem::datBatDauHangVeKhong() {
    ui->danhSachTheDocGia_tableWidget->setRowCount(0);
}

bool LibraryManagementSystem::laSapXepDanhSachTheoMaSo() {
    return ui->sapXepDocGia_ComboBox->currentIndex() == 0;
}

void LibraryManagementSystem::CapNhatBang()
{
    datBatDauHangVeKhong();

    if ( laSapXepDanhSachTheoMaSo() ) {
        inDanhSachTheDocGiaTheoMaSo(ui->danhSachTheDocGia_tableWidget, root);
    } else {
        xoaDanhSachTheoTen();
        taoDanhSachTheoTen(root);
        inDanhSachTheDocGiaTheoTen(ui->danhSachTheDocGia_tableWidget);
    }
    ui->danhSachTheDocGia_tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->danhSachTheDocGia_tableWidget->resizeColumnsToContents();
}

void LibraryManagementSystem::on_sapXepDocGia_ComboBox_currentIndexChanged(int index)
{
    CapNhatBang();
}

bool LibraryManagementSystem::hetMaThe() {
    return ui->danhSachTheDocGia_tableWidget->rowCount() == SOLUONGMATHETOIDA;
}

void LibraryManagementSystem::on_themDocGia_pushButton_clicked()
{
    themDocGia_Dialog themDocGia;

    if ( hetMaThe() ) {
        QMessageBox::warning(nullptr, "Thông báo", "Đã hết mã thẻ");
        themDocGia.close();
        return;
    }

    themDocGia.setModal(true);
    if (themDocGia.exec() == QDialog::Accepted) {
        The_Doc_Gia docGia;
        docGia.MATHE = layMaThe();
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

void LibraryManagementSystem::on_hieuChinhDocGia_pushButton_clicked()
{
    int currentRow = ui->danhSachTheDocGia_tableWidget->currentRow();

    hieuChinhDocGia_dialog hieuChinhDocGia;
    hieuChinhDocGia.setModal(true);

    if (currentRow != -1) {
        QTableWidgetItem* itemMaThe = ui->danhSachTheDocGia_tableWidget->item(currentRow, 0);
        Danh_Sach_The_Doc_Gia* docGia = timKiemTheDocGia( itemMaThe->text().toInt() );

        hieuChinhDocGia.setMaThe( docGia->thong_tin.MATHE );
        hieuChinhDocGia.setHoVaTen(docGia->thong_tin.Ho, docGia->thong_tin.Ten);
        hieuChinhDocGia.setGioiTinh(docGia->thong_tin.phai);
        hieuChinhDocGia.setTrangThaiThe( docGia->thong_tin.TrangThai );
    }

    if ( hieuChinhDocGia.exec() == QDialog::Accepted ) {
        int maThe = hieuChinhDocGia.getMaThe();
        The_Doc_Gia thongTinMoi;
        QString hoVaTen = hieuChinhDocGia.getHoVaTen();
        int viTriDeTachHoVaTen = hoVaTen.lastIndexOf(" ") + 1;

        thongTinMoi.Ho = hoVaTen.mid(0, viTriDeTachHoVaTen).toStdString();
        thongTinMoi.Ten = hoVaTen.mid(viTriDeTachHoVaTen).toStdString();
        thongTinMoi.phai = hieuChinhDocGia.getGioiTinh();
        thongTinMoi.TrangThai = hieuChinhDocGia.getTrangThaiThe();

        hieuChinhThongTinTheDocGia(maThe, thongTinMoi);

        QMessageBox::information(this, "Thông báo", "Đã cập nhật thông tin thành công");
        Saved = false;
    }

    CapNhatBang();
}

void LibraryManagementSystem::on_xoaDocGia_pushButton_clicked()
{
    xoaDocGia_dialog xoaDocGia;
    xoaDocGia.setModal(true);
    if ( xoaDocGia.exec() == QDialog::Accepted ) {
        Saved = false;
        CapNhatBang();
        QMessageBox::information(this, "Thông báo", "Độc giả đã được xóa thành công.");
    }

}
//------------------------------------Hàm sử dụng ở thẻ Mượn Trả---------------------------------------------------------------------------------------------


int LibraryManagementSystem::getmaThe() {
    return ui->lineEdit_maThe->text().toInt();
}

void LibraryManagementSystem::inThongTin(const int& ma_the) {

    Danh_Sach_The_Doc_Gia* doc_gia = timKiemTheDocGia(ma_the);
    ui->tableWidget_muonTra->setRowCount(0);
    // ui->tableWidget_muonTra->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    string hovaten = doc_gia->thong_tin.Ho + " " + doc_gia->thong_tin.Ten;
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;

    ui->lineEdit_hoTen->setText(QString::fromStdString(hovaten));
    ui->lineEdit_Phai->setText(doc_gia->thong_tin.phai == Nam ? "Nam" : "Nữ");
    ui->lineEdit_trangThai->setText(doc_gia->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động": "Khóa");

    while ( current != nullptr ) {
        if ( current->data.trangthai != Da_Tra) {
            int indexRow = ui->tableWidget_muonTra->rowCount();
            QCheckBox *checkBox = new QCheckBox(this);
            ui->tableWidget_muonTra->insertRow(indexRow);
            ui->tableWidget_muonTra->setCellWidget(indexRow, 0, checkBox);
            ui->tableWidget_muonTra->setItem(indexRow, 1, new QTableWidgetItem(QString::fromStdString(current->data.masach)));
            ui->tableWidget_muonTra->setItem(indexRow, 2, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(current->data.masach))));
            ui->tableWidget_muonTra->setItem(indexRow, 3, new QTableWidgetItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
            ui->tableWidget_muonTra->setItem(indexRow, 4, new QTableWidgetItem(QString::number(DemSoNgay(current->data.NgayMuon, NgayHomNay()))));
            ui->tableWidget_muonTra->setItem(indexRow, 5, new QTableWidgetItem(current->data.trangthai == Mat_Sach ? "Mất Sách" : "Chưa Trả"));
            indexRow++;
        }
        current = current->next;
    }

    ui->tableWidget_muonTra->resizeColumnsToContents();
    ui->tableWidget_muonTra->setColumnWidth(2, 250);

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

    QString filteredText;
    bool lastWasSpace = false;

    for (QChar c : arg1) {
        if (c.isDigit()) {
            filteredText += c;
            lastWasSpace = false;
        } else if (c.isSpace() && !lastWasSpace) {
            filteredText += ' ';
            lastWasSpace = true;
        }
    }

    filteredText = filteredText.trimmed();

    if (filteredText != arg1) {
        ui->lineEdit_maThe->setText(filteredText);
    }

    Danh_Sach_The_Doc_Gia* p = timKiemTheDocGia(filteredText.toInt());
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

bool LibraryManagementSystem::laISBN( string text ) {
    return text.length() == 13 || text.length() == 17;
}

bool LibraryManagementSystem::laMaSach( string text ) {
    return text.length() > 18;
}

void LibraryManagementSystem::clearBookInformation() {
    ui->lineEdit_tacGia->clear();
    ui->lineEdit_trangThaiSach->clear();
}

void LibraryManagementSystem::inThongTinmaSach(string text) {
    if( laISBN(text) ) {
        ui->lineEdit_maSach->setStyleSheet("background-color: lightgreen");
    }
    else if( laMaSach(text)) {
        if( TonTaiMaSach(text) ) {;
            ui->lineEdit_maSach->setStyleSheet("background-color: lightgreen");
        } else {
            ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
            clearBookInformation();
        }
    } else {
        ui->lineEdit_maSach->setStyleSheet("background-color: lightcoral");
        return;
    }

    int vitri = TimKiemViTriDauSach(text);

    if (vitri != -1 ) {
        string trang_thai_std;

        ui->lineEdit_tenSach->setText(QString::fromStdString( danh_sach_dau_sach.node[vitri]->tensach) );
        ui->lineEdit_tacGia->setText(QString::fromStdString( danh_sach_dau_sach.node[vitri]->tacgia) );
        DanhMucSach *danh_muc_sach = danh_sach_dau_sach.node[vitri]->dms;

        if ( laMaSach(text) ) {
            while(danh_muc_sach != nullptr) {
                if(danh_muc_sach->masach == text) {
                    switch(danh_muc_sach->trangthai) {
                        case 0: trang_thai_std = "Có thể mượn"; break;
                        case 1: trang_thai_std = "Đã được mượn"; break;
                        case 2: trang_thai_std = "Đã thanh lý"; break;
                    }
                    ui->lineEdit_trangThaiSach->setText(QString::fromStdString(trang_thai_std));
                    break;
                }
                danh_muc_sach = danh_muc_sach->next;
            }
        } else if ( laISBN(text) ) {
            while( danh_muc_sach != nullptr ) {
                if(danh_muc_sach->trangthai == 0) {
                    trang_thai_std = "Có thể mượn";
                    break;
                } else {
                    switch ( danh_muc_sach->trangthai ) {
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
        clearBookInformation();
    }
}

void LibraryManagementSystem::on_lineEdit_maSach_textChanged(const QString &arg1)
{
    QString filteredText;
    bool lastWasSpace = false;

    for (QChar c : arg1) {
        if (c.isDigit() || c == '-') {
            filteredText += c;
            lastWasSpace = false;
        } else if (c.isSpace() && !lastWasSpace) {
            filteredText += ' ';
            lastWasSpace = true;
        }
    }

    filteredText = filteredText.trimmed();

    if (filteredText != arg1) {
        ui->lineEdit_maSach->setText(filteredText);
    }

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
        ui->lineEdit_maSach->setStyleSheet("background-color: white");
        ui->lineEdit_tenSach->clear();
        ui->lineEdit_tacGia->clear();
        ui->lineEdit_trangThaiSach->clear();
    }
}


//--------------------------------------
bool LibraryManagementSystem::MaTheHoacMaSachRong() {
    return ui->lineEdit_maSach->text().isEmpty() || ui->lineEdit_maThe->text().isEmpty();
}

string LibraryManagementSystem::getMaSach(){
    return ui->lineEdit_maSach->text().toStdString();
}

string LibraryManagementSystem::getmaSachCoTheMuon() {
    string ma_ISBN = getMaSach();
    int vitri = TimKiemViTriDauSach(ma_ISBN);
    if (vitri != -1) {
        DanhMucSach* danh_muc_sach= danh_sach_dau_sach.node[vitri]->dms;
        while (danh_muc_sach != nullptr) {
            if(danh_muc_sach->trangthai == 0) {
                return danh_muc_sach->masach;
            }
            danh_muc_sach = danh_muc_sach->next;
        }
    }
    return "";
}

bool LibraryManagementSystem::MaTheHoacMaSachKhongTonTai() {
    Danh_Sach_The_Doc_Gia *doc_gia = timKiemTheDocGia(getmaThe());
    if(doc_gia == nullptr) return true;
    int vitridausach = TimKiemViTriDauSach(getMaSach());
    if(vitridausach == -1) return true;

    return false;
}

void LibraryManagementSystem::on_muonSach_pushButton_clicked()
{
    if(MaTheHoacMaSachRong()) {
        QMessageBox::information(nullptr, "Thông báo", "Bạn chưa nhập mã ISBN hoặc mã thẻ độc giả để mượn sách.");
        return;
    }

    if(MaTheHoacMaSachKhongTonTai()) {
        QMessageBox::information(nullptr, "Thông báo", "Mã thẻ hoặc mã sách không tồn tại.");
        return;
    }

    string maSach = getMaSach();

    if(laISBN(maSach)) {
        if(getmaSachCoTheMuon() == "") {
            QMessageBox::information(nullptr, "Thông báo", "Không thể mượn sách.");
            return;
        }
        MuonSach(getmaThe(), getmaSachCoTheMuon());
    } else if (laMaSach(maSach)){
        MuonSach(getmaThe(), maSach);
    } else {
        return;
    }

    ui->tableWidget_muonTra->setRowCount(0);
    inThongTin(getmaThe());
    ui->lineEdit_maSach->clear();

    Saved = false;

}

void LibraryManagementSystem::on_traSach_pushButton_clicked()
{
    if(ui->lineEdit_maThe->text().isEmpty()) {
        QMessageBox::information(nullptr, "Thông báo", "Bạn chưa nhập mã thẻ độc giả để trả sách.");
        return;
    }

    bool coTraSach = false;
    for (int row = 0; row < ui->tableWidget_muonTra->rowCount(); row++) {
        QWidget *traSach_widget = ui->tableWidget_muonTra->cellWidget(row, 0);
        QCheckBox *traSach_checkBox = qobject_cast<QCheckBox *>(traSach_widget);
        if ( traSach_checkBox->isChecked() ) {
            coTraSach = true;
            QString ma_sach = ui->tableWidget_muonTra->item(row, 1)->text();
            string maSach = ma_sach.toStdString();
            TraSach(getmaThe(), maSach);
        }
    }
    if( !coTraSach )  {
        QMessageBox::information(nullptr, "Thông báo", "Bạn chưa chọn sách để trả.");
        return;
    }

    inThongTin(getmaThe());
    Saved = false;
}


void LibraryManagementSystem::on_MatSach_pushButton_2_clicked()
{
    if(!ui->lineEdit_maThe->text().isEmpty()) {
        bool thongbao[3] = {0, 0, 0};
        for(int row = 0 ; row < ui->tableWidget_muonTra->rowCount(); row ++) {
            QWidget *traSach_widget = ui->tableWidget_muonTra->cellWidget(row, 0);
            QCheckBox *traSach_checkBox = qobject_cast<QCheckBox *>(traSach_widget);
            if ( traSach_checkBox->isChecked() ) {
                QString ma_sach =ui->tableWidget_muonTra->item(row, 1)->text();
                string maSach = ma_sach.toStdString();
                QString trang_thai = ui->tableWidget_muonTra->item(row, 5)->text();
                string trangthai = trang_thai.toStdString();
                if(thongbao[0] == 1 && trangthai == "Chưa Trả") {
                    DaDenSach(getmaThe(), maSach);
                } else if (thongbao[1] == 1 && trangthai == "Chưa Trả") {
                    ChuaDenSach(getmaThe(), maSach);
                } else if (thongbao[2] == 1 && trangthai == "Mất Sách") {
                    DaDenSach(getmaThe(), maSach);
                } else {
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

                                thongbao[0] = true;
                            }
                        } else {
                            ChuaDenSach(getmaThe(), maSach);
                            if(thongbao[1] == false) {
                                QMessageBox::information(this, "Thông báo", "Sách đã được đánh dấu là chưa đền.");

                                thongbao[1] = true;
                            }
                        }

                    }
                    else {
                        DaDenSach(getmaThe(), maSach);
                        if(thongbao[2] == false) {
                            QMessageBox::information(this, "Thông báo", "Sách đã được đánh dấu là đã đền.");
                            thongbao[2] = true;
                        }
                    }
                }
            }
        }
        if(thongbao[0] == 0 && thongbao[1] == 0 && thongbao[2] == 0) {
            QMessageBox::information(nullptr, "Thông báo", "Bạn chưa chọn sách để báo mất/đền sách.");
            return;
        }
        inThongTin(getmaThe());
        Saved = false;
    } else {
        QMessageBox::information(nullptr, "Thông báo", "Bạn chưa nhập mã thẻ độc giả. ");
    }
}


