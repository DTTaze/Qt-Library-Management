#ifndef XOA_DAU_SACH_H
#define XOA_DAU_SACH_H

#include <QDialog>

namespace Ui {
class Xoa_dau_sach;
}

class Xoa_dau_sach : public QDialog
{
    Q_OBJECT

public:
    explicit Xoa_dau_sach(int index,QWidget *parent = nullptr);
    ~Xoa_dau_sach();
    void HienThiDanhMucSachTrongXoaSach(int index_dausach);
    void HienThiThongTinSachTrongXoatSach(int index_dausach);
    void XoaThongTinTrongXoaSach();
    void XoaDauSach(int index);

private slots:
    void on_lineEdit_ISBN_2_textChanged(const QString &arg1);

    void on_pushButton_cancel_2_clicked();

    void on_pushButton_XoaDauSacg_clicked();

private:
    Ui::Xoa_dau_sach *ui;
    int index_dausach;
};

#endif // XOA_DAU_SACH_H
