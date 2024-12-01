#include "themDocGia_dialog.h"
#include "ui_themDocGia_dialog.h"

themDocGia_Dialog::themDocGia_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::themDocGia_Dialog)
{
    ui->setupUi(this);
}

themDocGia_Dialog::~themDocGia_Dialog()
{
    delete ui;
}

void themDocGia_Dialog::xuLyChuoi(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;

    if (!newText.isEmpty() && newText[0] == ' ') {
        newText = newText.mid(1);
    }

    while (newText.contains("  ")) {
        newText.replace("  ", " ");
    }

    for (int i = 0; i < newText.length(); ++i) {
        if (i == 0 || newText[i - 1] == ' ') {
            newText[i] = newText[i].toUpper();
        }
    }

    if (!newText.isEmpty() && !newText.back().isLetter() && !newText.back().isSpace()) {
        newText = newText.mid(0, newText.length() - 1);
    }

    if (newText != arg1) {
        lineEdit->setText(newText);
    }
}

void themDocGia_Dialog::on_hoVaTen_lineEdit_textChanged(const QString &arg1)
{
    int currentPointerPosition = ui->hoVaTen_lineEdit->cursorPosition();
    xuLyChuoi(arg1, ui->hoVaTen_lineEdit);
    ui->hoVaTen_lineEdit->setCursorPosition(qMin(currentPointerPosition, ui->hoVaTen_lineEdit->text().length()));
}

QString themDocGia_Dialog::getHoVaTen() {
    return ui->hoVaTen_lineEdit->text().trimmed();
}

QString themDocGia_Dialog::getPhai()
{
    return ui->nam_radioButton->isChecked() ? "Nam" : "Nữ";
}


void themDocGia_Dialog::on_ok_pushButton_clicked()
{
    if ( !getHoVaTen().contains(" ")) {
        QMessageBox::warning(nullptr, "Lỗi", "Độc giả phải có đầy đủ họ và tên.");
        return;
    }

    if ( !getHoVaTen().isEmpty() && (ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked())) {
        accept();
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin.");
    }
}

void themDocGia_Dialog::on_cancel_pushButton_clicked()
{
    close();
}


