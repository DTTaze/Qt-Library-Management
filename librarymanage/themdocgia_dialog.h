#ifndef THEMDOCGIA_DIALOG_H
#define THEMDOCGIA_DIALOG_H

#include <QDialog>

namespace Ui {
class themDocGia_Dialog;
}

class themDocGia_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit themDocGia_Dialog(QWidget *parent = nullptr);
    ~themDocGia_Dialog();

private:
    Ui::themDocGia_Dialog *ui;
};

#endif // THEMDOCGIA_DIALOG_H
