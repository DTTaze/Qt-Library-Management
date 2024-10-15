#ifndef MUONSACH_H
#define MUONSACH_H

#include <QDialog>

namespace Ui {
class muonsach;
}

class muonsach : public QDialog
{
    Q_OBJECT

public:
    explicit muonsach(QWidget *parent = nullptr);
    ~muonsach();

private:
    Ui::muonsach *ui;
};

#endif // MUONSACH_H
