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
    QString newText;
    bool lastWasSpace = false;

    int cursorPosition = lineEdit->cursorPosition();
    int removedChars = 0;

    for (int i = 0; i < arg1.length(); ++i) {
        QChar c = arg1[i];
        if (c.isLetter()) {
            if (newText.isEmpty() || lastWasSpace) {
                newText += c.toUpper();
            } else {
                newText += c.toLower();
            }
            lastWasSpace = false;
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                newText += ' ';
                lastWasSpace = true;
            }
        } else {
            ++removedChars;
        }
    }

    newText = newText.trimmed();

    lineEdit->blockSignals(true);
    if (newText != arg1) {
        lineEdit->setText(newText);
    }
    lineEdit->blockSignals(false);

    int newCursorPosition = cursorPosition - removedChars;

    newCursorPosition = qBound(0, newCursorPosition, newText.length());

    lineEdit->setCursorPosition(newCursorPosition);
}

void themDocGia_Dialog::on_hoVaTen_lineEdit_textChanged(const QString &arg1)
{
    xuLyChuoi(arg1, ui->hoVaTen_lineEdit);
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


