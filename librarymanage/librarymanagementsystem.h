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

    void tabBaoCao(int SoLuongSach);

    void on_luuFile_pushButton_clicked();

    void on_dauSach_pushButton_clicked();

    void on_thedocgia_pushButton_clicked();

    void on_muontra_pushButton_clicked();

    void on_baocao_pushButton_clicked();
//---------------------------------------------------------------Hàm Đầu Sách-----------------------------------------------------------------------------------------------------------
    void on_lineEdit_timkiemds_textChanged(const QString text);

    void on_inTheLoai_pushButton_clicked();

    void on_themSach_pushButton_clicked();

    void on_thanhly_pushButton_clicked();

    void HienMaSach(const QModelIndex &index);
//--------------------------------------------------------------Hàm Thẻ Độc Giả -----------------------------------------------------------------------------------------------------------
    void on_themDocGia_pushButton_clicked();

    void on_sapXepDocGia_ComboBox_currentIndexChanged(int index);

    void on_xoaDocGia_pushButton_clicked();

    void on_danhSachTheDocGia_tableWidget_itemChanged(QTableWidgetItem *item);

    void CapNhatBang();

    bool kiemTraChuoi(QString s);

    void on_danhSachTheDocGia_tableWidget_cellDoubleClicked(int row, int column);
//---------------------------------------------------------------Hàm Mượn Trả -----------------------------------------------------------------------------------------------------------
    bool laISBN(string text );

    bool laMaSach(string text);

    void clearBookInformation();

    int getmaThe() ;

    void inThongTin(const int& ma_the) ;

    void on_lineEdit_maThe_textChanged(const QString &arg1);

    string getmaSachCoTheMuon() ;

    void inThongTinmaSach( string key_ma_sach);

    void on_lineEdit_maSach_textChanged(const QString &arg1);

    void on_traSach_pushButton_clicked();

    void on_muonSach_pushButton_clicked();

    void on_MatSach_pushButton_2_clicked();


public slots:

private:
    Ui::LibraryManagementSystem *ui;
    bool Saved;
    QStandardItemModel* model_Dausach;
protected:
    void closeEvent(QCloseEvent *event) override; // Khai báo hàm closeEvent

};
#endif // LIBRARYMANAGEMENTSYSTEM_H

