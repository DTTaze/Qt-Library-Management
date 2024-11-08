#ifndef DANHMUCSACH_H
#define DANHMUCSACH_H

#include <QDialog>

namespace Ui {
class Danhmucsach;
}

class Danhmucsach : public QDialog
{
    Q_OBJECT

public:
    explicit Danhmucsach(int Vi_tri_DS,QWidget *parent = nullptr);
    ~Danhmucsach();

private:
    Ui::Danhmucsach *ui;
    int Vitridausach;
};

#endif // DANHMUCSACH_H
