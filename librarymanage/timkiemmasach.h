#ifndef TIMKIEMMASACH_H
#define TIMKIEMMASACH_H

#include <QDialog>

namespace Ui {
class timkiemmasach;
}

class timkiemmasach : public QDialog
{
    Q_OBJECT

public:
    explicit timkiemmasach(QWidget *parent = nullptr);
    ~timkiemmasach();

private:
    Ui::timkiemmasach *ui;
};

#endif // TIMKIEMMASACH_H
