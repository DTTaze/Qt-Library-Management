#ifndef THANH_LY_H
#define THANH_LY_H

#include <QDialog>
#include "dau_sach.h"
namespace Ui {
class Thanh_ly;
}

class Thanh_ly : public QDialog
{
    Q_OBJECT

public:
    explicit Thanh_ly(int DS_vitri,QWidget *parent = nullptr);
    ~Thanh_ly();
    void HienThongtinSachTonTai(int vi_tri);

    void KhoaThanhLyDauSach();
    void XoaThongTinTrongThanhLySach();

private slots:
    void on_pushButton_thanhly_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_chontatca_clicked();

    void on_pushButton_bochon_clicked();

    void on_lineEdit_ISBN_textChanged(const QString &arg1);

private:
    Ui::Thanh_ly *ui;
    int vi_tri_DS;
};

#endif // THANH_LY_H
