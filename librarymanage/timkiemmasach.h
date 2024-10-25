#ifndef TIMKIEMMASACH_H
#define TIMKIEMMASACH_H

#include <QDialog>
#include "dau_sach.h"
#include "Muon_tra.h"
#include "The_doc_gia.h"

namespace Ui {
class timkiemmasach;
}

class timkiemmasach : public QDialog
{
    Q_OBJECT

public:
    explicit timkiemmasach(QWidget *parent = nullptr);
    ~timkiemmasach();
    int getMaThe();
    void inThongTin(const int& ma_the);

private slots:
     void on_lineEdit_mathe_textChanged(const QString &arg1);
    void on_pushButton_cancel_clicked();

private:
    Ui::timkiemmasach *ui;
};

#endif // TIMKIEMMASACH_H
