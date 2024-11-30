#include "xoaDocGia_dialog.h"
#include "ui_xoaDocGia_dialog.h"

xoaDocGia_dialog::xoaDocGia_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::xoaDocGia_dialog)
{
    ui->setupUi(this);
}

xoaDocGia_dialog::~xoaDocGia_dialog()
{
    delete ui;
}

void xoaDocGia_dialog::setMaThe(int maThe) {
    ui->maThe_lineEdit->setText(QString::number(maThe));
}

void xoaDocGia_dialog::setHoVaTen(string ho, string ten) {
    ui->hoVaTen_lineEdit->setText(QString::fromStdString(ho) + " " + QString::fromStdString(ten));
}

void xoaDocGia_dialog::setGioiTinh(Phai gioitinh) {
    if ( gioitinh == Nam) {
        ui->gioiTinh_lineEdit->setText("Nam");
    } else {
        ui->gioiTinh_lineEdit->setText("Nữ");
    }
}

void xoaDocGia_dialog::setTrangThaiThe(TrangThaiCuaThe trangthai) {
    if ( trangthai == Dang_Hoat_Dong) {
        ui->trangThaiThe_lineEdit->setText("Đang hoạt động");
    } else {
        ui->trangThaiThe_lineEdit->setText("Khóa");
    }
}

void xoaDocGia_dialog::xuLyChuoi(const QString &arg1, QLineEdit* lineEdit) {
    QString newText = arg1;

    if (newText.contains(" ")) {
        newText.replace(" ", "");
    }

    if (!newText.isEmpty() && !newText[newText.length() - 1].isDigit() ) {
        newText = newText.mid(0, newText.length() - 1);
    }

    if (newText != arg1) {
        lineEdit->setText(newText);
    }
}

void xoaDocGia_dialog::on_maThe_lineEdit_textChanged(const QString &arg1)
{
    xuLyChuoi(arg1, ui->maThe_lineEdit);
    int maThe = ui->maThe_lineEdit->text().toInt();
    Danh_Sach_The_Doc_Gia* docGia = timKiemTheDocGia(maThe);
    if ( docGia != nullptr ) {
        ui->hoVaTen_lineEdit->setText( QString::fromStdString(docGia->thong_tin.Ho) + " " + QString::fromStdString(docGia->thong_tin.Ten) );
        if ( docGia->thong_tin.phai == Nam ) {
            ui->gioiTinh_lineEdit->setText("Nam");
        } else {
            ui->gioiTinh_lineEdit->setText("Nữ");
        }
        if ( docGia->thong_tin.TrangThai == Dang_Hoat_Dong ) {
            ui->trangThaiThe_lineEdit->setText("Đang hoạt động");
        } else {
            ui->trangThaiThe_lineEdit->setText("Nữ");
        }
        ui->maThe_lineEdit->setStyleSheet("background-color: lightgreen");
    } else {
        ui->maThe_lineEdit->setStyleSheet("background-color: lightcoral");
    }
}

void xoaDocGia_dialog::on_ok_pushButton_clicked()
{
    if ( ui->maThe_lineEdit->text().isEmpty() ) {
        QMessageBox::information(this, "Lỗi", "Bạn chưa nhập mã thẻ");
        return;
    }

    int maThe = ui->maThe_lineEdit->text().toInt();
    Danh_Sach_The_Doc_Gia* docGia = timKiemTheDocGia(maThe);

    if ( docGia == nullptr ) {
        QMessageBox::information(this, "Lỗi", "Thẻ độc giả không tồn tại");
        return;
    } else {
        if ( docGia->thong_tin.head_lsms != nullptr || docGia->thong_tin.TrangThai == Khoa ) {
            QMessageBox::information(this, "Lỗi", "Bạn không thể xóa thẻ độc giả này");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Thông báo",
                                      "Bạn có chắc muốn xóa thẻ độc giả này?",
                                      QMessageBox::Yes | QMessageBox::No);
        if ( reply == QMessageBox::Yes ) {
            Xoa_Doc_Gia(root, maThe);
            accept();
        } else {
            return;
        }
    }
}


void xoaDocGia_dialog::on_cancel_pushButton_clicked()
{
    close();
}

