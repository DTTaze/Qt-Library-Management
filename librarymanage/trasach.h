#ifndef TRASACH_H
#define TRASACH_H

#include <QDialog>

namespace Ui {
class trasach;
}

class trasach : public QDialog
{
    Q_OBJECT

public:
    explicit trasach(QWidget *parent = nullptr);
    ~trasach();

private:
    Ui::trasach *ui;
};

#endif // TRASACH_H
