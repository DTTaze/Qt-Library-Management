#ifndef INTHEOTHELOAI_H
#define INTHEOTHELOAI_H

#include <QDialog>
#include "dau_sach.h"
#include <QDebug>

namespace Ui {
class InTheoTheLoai;
}

class InTheoTheLoai : public QDialog
{
    Q_OBJECT

public:
    explicit InTheoTheLoai(QWidget *parent = nullptr);
    ~InTheoTheLoai();

private:
    Ui::InTheoTheLoai *ui;
};

#endif // INTHEOTHELOAI_H
