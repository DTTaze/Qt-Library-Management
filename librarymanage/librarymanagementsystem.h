#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H
#define MAXSACH 10000

#include <QMainWindow>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include "Dau_sach.h"
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
    void page1Widget();
    void page2Widget();
    void page3Widget();
    void page4Widget();
    void on_luuFile_pushButton_clicked();
//---------------------------------------------------------------Hàm Đầu Sách-----------------------------------------------------------------------------------------------------------
    void on_lineEdit_timkiemds_textChanged(const QString text);

    void on_inTheLoai_pushButton_clicked();

    void on_themSach_pushButton_clicked();
//--------------------------------------------------------------Hàm Thẻ Độc Giả -----------------------------------------------------------------------------------------------------------
    void on_themDocGia_pushButton_clicked();

    void on_sapXepDocGia_ComboBox_currentIndexChanged(int index);

    void on_xoaDocGia_pushButton_clicked();

    void on_tableWidget_2_itemChanged(QTableWidgetItem *item);

    void CapNhatBang();

    bool kiemTraChuoi(QString s);

    void on_tableWidget_2_cellDoubleClicked(int row, int column);
//---------------------------------------------------------------Hàm Mượn Trả -----------------------------------------------------------------------------------------------------------
    void on_muonSach_pushButton_clicked();

    void on_traSach_pushButton_clicked();

    void on_themSach_pushButton_2_clicked();

    int getmaThe() ;

    void inThongTin(const int& ma_the) ;

    void on_lineEdit_maThe_textChanged(const QString &arg1);
    string getmaSach();

    void on_lineEdit_maSach_textChanged(const QString &arg1);

public slots:

private:
    Ui::LibraryManagementSystem *ui;
    bool Saved;
protected:
    void closeEvent(QCloseEvent *event) override; // Khai báo hàm closeEvent

};
#endif // LIBRARYMANAGEMENTSYSTEM_H
