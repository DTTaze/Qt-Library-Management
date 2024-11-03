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
    explicit Thanh_ly(const string &ISBN,QWidget *parent = nullptr);
    ~Thanh_ly();
    void HienThongtin(const string &ma_isbn);

private slots:
    void on_pushButton_thanhly_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_chontatca_clicked();

    void on_pushButton_bochon_clicked();

private:
    Ui::Thanh_ly *ui;
    string ma_ISBN;
};

#endif // THANH_LY_H
