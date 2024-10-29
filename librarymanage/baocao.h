#ifndef BAOCAO_H
#define BAOCAO_H

#include <QDialog>
#include "dau_sach.h"
#include "The_doc_gia.h"
#include "Muon_tra.h"

namespace Ui {
class baocao;
}

class baocao : public QDialog
{
    Q_OBJECT

public:
    explicit baocao(QWidget *parent = nullptr);
    ~baocao();

private:
    Ui::baocao *ui;
};

#endif // BAOCAO_H
