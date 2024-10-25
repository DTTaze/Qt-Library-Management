#ifndef MUONSACH_H
#define MUONSACH_H

#include <QDialog>
#include "The_doc_gia.h"
#include "dau_sach.h"
#include "Muon_tra.h"

namespace Ui {
class muonsach;
}

class muonsach : public QDialog
{
    Q_OBJECT

public:
    explicit muonsach(QWidget *parent = nullptr);
    ~muonsach();
    int getMaThe();
    string getMaSach();
    void inThongTin(int maThe, QTableView* tableView);

private slots:
    void on_pushButton_ok_clicked();

    void on_maThe_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_cancel_clicked();

private:
    Ui::muonsach *ui;
};

#endif // MUONSACH_H
