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

    void on_spinBox_namsb_valueChanged(int arg1);

    void on_lineEdit_ISBN_textChanged(const QString &arg1);

    void on_lineEdit_tensach_textChanged(const QString &arg1);

    void on_lineEdit_theloai_textChanged(const QString &arg1);

    void on_comboBox_vitri_currentTextChanged(const QString &arg1);

    void on_lineEdit_tacgia_textChanged(const QString &arg1);

private:
    Ui::themdausach *ui;
};

#endif // THEMDAUSACH_H
