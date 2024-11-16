#ifndef NHAP_DAUSACH_H
#define NHAP_DAUSACH_H

#include <QDialog>
#include "Dau_sach.h"

namespace Ui {
class nhap_dausach;
}

class nhap_dausach : public QDialog
{
    Q_OBJECT

public:
    explicit nhap_dausach(int index,QWidget *parent = nullptr);
    ~nhap_dausach();
    void KhoaNhapDauSach();
    void MoKhoaNhapDauSach();
    void XoaThongTinTrongNhapDauSach();

    void HienThiThongTinSachTrongNhapDauSach(int index_dausach);

private slots:
    void on_lineEdit_ISBN_2_textChanged(const QString &arg1);

    void on_pushButton_cancel_clicked();

    void on_pushButton_nhap_clicked();

    void on_comboBox_vitri_2_currentTextChanged(const QString &arg1);

private:
    Ui::nhap_dausach *ui;
    int index_dausach;
};

#endif // NHAP_DAUSACH_H
