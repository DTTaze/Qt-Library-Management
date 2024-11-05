#include "themdocgia_dialog.h"
#include "ui_themdocgia_dialog.h"

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

void themDocGia_Dialog::on_hoVaTen_lineEdit_textChanged(const QString &arg1)
{
    xuLyChuoi(arg1, ui->hoVaTen_lineEdit);
}

void themDocGia_Dialog::xuLyChuoi(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;

    if (newText == " ") {
        newText.replace(" ", "");
    }

    if (newText.contains("  ")) {
        newText.replace("  ", " ");
    }

    if (!newText.isEmpty() && !newText[newText.length() - 1].isLetter() && !newText[newText.length() - 1].isSpace()) {
        newText = newText.mid(0, newText.length() - 1);
    }

    for ( int i = 0; i < newText.length(); i++ ) {
        if ( i == 0 ) {
            newText[0] = newText[0].toUpper();
        }
        if ( i > 0 && newText[i-1] == ' ') {
            newText[i] = newText[i].toUpper();
        }
    }

    if (newText != arg1) {
        lineEdit->setText(newText);
    }
}

void themDocGia_Dialog::on_cancel_pushButton_clicked()
{
    close();
}

void themDocGia_Dialog::on_ok_pushButton_clicked()
{
    if ( !getHoVaTen().isEmpty() && (ui->nam_radioButton->isChecked() || ui->nu_radioButton->isChecked())) {
        accept();
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin.");
    }
}

QString themDocGia_Dialog::getHoVaTen() {
    return ui->hoVaTen_lineEdit->text().trimmed();
}

QString themDocGia_Dialog::getPhai()
{
    return ui->nam_radioButton->isChecked() ? "Nam" : "Nữ";
}


