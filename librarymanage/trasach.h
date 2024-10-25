#ifndef TRASACH_H
#define TRASACH_H

#include <QDialog>
#include "dau_sach.h"
#include "Muon_tra.h"
#include "The_doc_gia.h"
namespace Ui {
class trasach;
}

class trasach : public QDialog
{
    Q_OBJECT

public:
    explicit trasach(QWidget *parent = nullptr);
    ~trasach();
    int getMaThe();
    void inThongTin(const int& ma_the);

private slots:
    void on_lineEdit_mathe_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_trasach_clicked();

private:
    Ui::trasach *ui;
};

#endif // TRASACH_H
