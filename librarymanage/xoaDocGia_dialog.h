#ifndef XOADOCGIA_DIALOG_H
#define XOADOCGIA_DIALOG_H

#include <QDialog>
#include "The_doc_gia.h"

namespace Ui {
class xoaDocGia_dialog;
}

class xoaDocGia_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit xoaDocGia_dialog(QWidget *parent = nullptr);
    ~xoaDocGia_dialog();
    void setMaThe(int maThe);
    void setHoVaTen(string ho, string ten);
    void setTrangThaiThe(TrangThaiCuaThe trangthai);
    void setGioiTinh(Phai gioiTinh);
    void xuLyChuoi(const QString &arg1, QLineEdit* lineEdit);

private slots:
    void on_maThe_lineEdit_textChanged(const QString &arg1);

    void on_ok_pushButton_clicked();

    void on_cancel_pushButton_clicked();

private:
    Ui::xoaDocGia_dialog *ui;
};

#endif // XOADOCGIA_DIALOG_H
