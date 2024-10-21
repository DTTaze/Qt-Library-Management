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
    explicit themdausach(QWidget *parent = nullptr);
    ~themdausach();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::themdausach *ui;
};

#endif // THEMDAUSACH_H
