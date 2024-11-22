#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H
#define MAXSACH 10000

#include <QMainWindow>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QCheckBox>
#include <QComboBox>
#include <QMenu>
#include "Dau_sach.h"
#include "queue.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class LibraryManagementSystem;
}
QT_END_NAMESPACE

class LibraryManagementSystem : public QMainWindow
{
    Q_OBJECT

public:
    LibraryManagementSystem(QWidget *parent = nullptr);
    ~LibraryManagementSystem();

private slots:
    void tabDauSach();

    void tabTheDocGia();

    void tabMuonTra();

    void on_dauSach_pushButton_clicked();

    void on_thedocgia_pushButton_clicked();

    void on_muontra_pushButton_clicked();

    void setupbaocao_pushButton();

    void showTop10SachPage();

    void showMuonQuaHanPage();

    void on_luuFile_pushButton_clicked();
//---------------------------------------------------------------Hàm Đầu Sách-----------------------------------------------------------------------------------------------------------
    void on_lineEdit_timkiemds_textChanged(const QString text);

    void on_inTheLoai_pushButton_clicked();

    void MoCuaSoDanhMucSach(int ViTriDauSach);

    void on_tableWidget_dausach_doubleClicked(const QModelIndex &index);

    void MoCuaSoThemSach();

    void on_themSach_pushButton_clicked();

    void MoCuaSoEditSach(int i_ds);

    void on_editSach_pushButton_clicked();

    void MoCuaSoXoaSach(int i_ds);

    void on_xoaSach_pushButton_clicked();

    void MoCuaSoThanhLySach(int i_ds);

    void on_thanhly_pushButton_clicked();

    void MoCuaSoNhapDauSach(int i_ds);

    void on_nhapSach_pushButton_clicked();
//--------------------------------------------------------------Hàm Thẻ Độc Giả -----------------------------------------------------------------------------------------------------------
    void CapNhatBang();

    void datBatDauHangVeKhong();

    bool laSapXepDanhSachTheoMaSo();

    void on_sapXepDocGia_ComboBox_currentIndexChanged(int index);

    bool hetMaThe();

    void on_themDocGia_pushButton_clicked();

    void on_hieuChinhDocGia_pushButton_clicked();

    void on_xoaDocGia_pushButton_clicked();
//---------------------------------------------------------------Hàm Mượn Trả -----------------------------------------------------------------------------------------------------------
    bool laISBN(string text );

    bool laMaSach(string text);

    void clearBookInformation();

    int getmaThe() ;

    string getMaSach();

    void inThongTin(const int& ma_the) ;

    void on_lineEdit_maThe_textChanged(const QString &arg1);

    string getmaSachCoTheMuon() ;

    void inThongTinmaSach( string key_ma_sach);

    void on_lineEdit_maSach_textChanged(const QString &arg1);

    bool MaTheHoacMaSachRong();

    bool MaTheHoacMaSachKhongTonTai() ;

    void on_traSach_pushButton_clicked();

    void on_muonSach_pushButton_clicked();

    void on_MatSach_pushButton_2_clicked();

public slots:

private:
    Ui::LibraryManagementSystem *ui;
    bool Saved;
protected:
    void closeEvent(QCloseEvent *event) override; // Khai báo hàm closeEvent

};
#endif // LIBRARYMANAGEMENTSYSTEM_H

