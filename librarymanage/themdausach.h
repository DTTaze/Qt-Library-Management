#ifndef THEMDAUSACH_H
#define THEMDAUSACH_H

#include <QDialog>
#include "dau_sach.h"
namespace Ui {
class themdausach;
}

class themdausach : public QDialog
{
    Q_OBJECT

public:
    explicit themdausach(DanhSachDauSach &danh_sach_dau_sach,DanhMucSach* &danh_muc_sach,QWidget *parent = nullptr);
    ~themdausach();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::themdausach *ui;
    DanhSachDauSach& danh_sach_dau_sach;
    DanhMucSach* &danh_muc_sach;
};

#endif // THEMDAUSACH_H
