#ifndef HIEUCHINHDOCGIA_DIALOG_H
#define HIEUCHINHDOCGIA_DIALOG_H

#include <QDialog>
#include "The_doc_gia.h"

namespace Ui {
class hieuChinhDocGia_dialog;
}

class hieuChinhDocGia_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit hieuChinhDocGia_dialog(QWidget *parent = nullptr);
    ~hieuChinhDocGia_dialog();
    void setMaThe( int maThe );
    void setHoVaTen( string ho, string ten);
    void setGioiTinh( Phai gioitinh );
    void setTrangThaiThe( TrangThaiCuaThe trangthai );

    int getMaThe();
    QString getHoVaTen();
    Phai getGioiTinh();
    TrangThaiCuaThe getTrangThaiThe();

    void xuLyChuoi(const QString &s, QLineEdit* lineEdit);
    void xuLySo(const QString &arg1, QLineEdit* lineEdit);


private slots:
    void on_hoVaTen_lineEdit_textChanged(const QString &arg1);

    void on_maThe_lineEdit_textChanged(const QString &arg1);

private:
    Ui::hieuChinhDocGia_dialog *ui;
};

#endif // HIEUCHINHDOCGIA_DIALOG_H
