#ifndef LIBRARYMANAGEMENTSYSTEM_H
#define LIBRARYMANAGEMENTSYSTEM_H
#define MAXSACH 10000

#include <QMainWindow>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include "Dau_sach.h"
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
    DanhSachDauSach danh_sach_dau_sach;
    DanhMucSach* danh_muc_sach;


private slots:

    void on_muonsach_buttom_clicked();

    void on_trasach_buttom_clicked();

    void on_timsach_buttom_clicked();

    void page1Widget();
    void page2Widget();
    void page3Widget();

    void on_lineEdit_timkiemds_textChanged(const QString text);

    void on_pushButton_intheloai_clicked();

public slots:



private:
    Ui::LibraryManagementSystem *ui;

};
#endif // LIBRARYMANAGEMENTSYSTEM_H
