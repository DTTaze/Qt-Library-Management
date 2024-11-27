#ifndef EDIT_SACH_H
#define EDIT_SACH_H

#include <QDialog>
#include "Dau_sach.h"

namespace Ui {
class Edit_sach;
}

class Edit_sach : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_sach(int index,QWidget *parent = nullptr);
    ~Edit_sach();
    void KhoaEditDauSach();
    void MoKhoaEditDauSach();
    void HienThiThongTinSachTrongEditSach(int index_dausach);
    void HienThiDanhMucSachTrongEditSach(int index_dausach);
    void XoaThongTinTrongEditSach();
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

    void on_lineEdit_ISBN_1_textChanged(const QString &arg1);

    void on_spinBox_namxb_1_valueChanged(int arg1);

    void on_lineEdit_tensach_1_textChanged(const QString &arg1);

    void on_lineEdit_theloai_1_textChanged(const QString &arg1);

    void on_lineEdit_tacgia_1_textChanged(const QString &arg1);

    void on_tableWidget_danhmucsach_1_itemChanged(QTableWidgetItem *item);

private:
    Ui::Edit_sach *ui;
    int index_dausach;
};

#endif // EDIT_SACH_H
