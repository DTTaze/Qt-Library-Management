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
    explicit Xoa_dau_sach(QWidget *parent = nullptr);
    ~Xoa_dau_sach();

private:
    Ui::Xoa_dau_sach *ui;
};

#endif // XOA_DAU_SACH_H
