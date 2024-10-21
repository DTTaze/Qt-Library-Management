#include "themdausach.h"
#include "ui_themdausach.h"

themdausach::themdausach( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::themdausach)
{
    ui->setupUi(this);
}

themdausach::~themdausach()
{
    delete ui;
}

void themdausach::on_buttonBox_accepted()
{
    QString ISBN = ui->lineEdit_ISBN->text();
    QString tensach =  ui->lineEdit_tensach->text();
    QString tacgia =  ui->lineEdit_tacgia->text();
    QString theloai = ui->lineEdit_theloai->text();
    QString vitri = ui->lineEdit_vitri->text();
    int sotrang = ui->spinBox_sotrang->value();
    int namsx = ui->spinBox_namsb->value();
    if(!ISBN.isEmpty() && !tensach.isEmpty() &&!tacgia.isEmpty() &&!theloai.isEmpty() && sotrang != 0 && namsx != 0){
        // Chuyển đổi từ QString sang std::string
        std::string isbnStd = ISBN.toStdString();
        std::string tensachStd = tensach.toStdString();
        std::string tacgiaStd = tacgia.toStdString();
        std::string theloaiStd = theloai.toStdString();
        std::string vitriStd = vitri.toStdString();

        // Gọi hàm ThemDauSach với các tham số đã chuyển đổi
        ThemDauSach(danh_sach_dau_sach,isbnStd, tensachStd, sotrang,tacgiaStd, namsx,theloaiStd,danh_muc_sach,0,vitriStd);
        accept();
    }else {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điền đầy đủ thông tin");
    }

}


void themdausach::on_buttonBox_rejected()
{
    close();
}

