#include "muonsach.h"
#include "ui_muonsach.h"

muonsach::muonsach(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::muonsach)
{
    ui->setupUi(this);
    ui->maSach_lineEdit->setPlaceholderText("Nhập mã thẻ độc giả");
    ui->maThe_lineEdit->setPlaceholderText("Nhập sách cần mượn");

}

muonsach::~muonsach()
{
    delete ui;
}

int muonsach::getMaThe() {
    return ui->maThe_lineEdit->text().toInt();
}

string muonsach::getMaSach() {
    return ui->maSach_lineEdit->text().toStdString();
}

void muonsach::inThongTin(int maThe, QTableView* tableView) {
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, maThe);
    DanhSachMUONTRA* current = p->thong_tin.head_lsms;
    QStandardItemModel* model = new QStandardItemModel(3, 5);

    QString headers[5] = {
        "Mã sách",
        "Tên sách",
        "Ngày mượn",
        "Ngày trả",
        "Trạng thái",
    };

    for (int i = 0; i < 5; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }
    int indexRow = 0;
    while ( current != nullptr ) {
        model->setItem(indexRow, 0, new QStandardItem(QString::fromStdString(current->data.masach)));
        model->setItem(indexRow, 1, new QStandardItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach))));
        model->setItem(indexRow, 2, new QStandardItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayMuon))));
        model->setItem(indexRow, 3, new QStandardItem(QString::fromStdString(ChuyenDateSangString(current->data.NgayTra))));
        model->setItem(indexRow, 4, new QStandardItem(QString::number(current->data.trangthai)));
        indexRow++;
        current = current->next;
    }
    tableView->setModel(model);
}

void muonsach::on_pushButton_ok_clicked()
{
    if ( ui->maThe_lineEdit->text().isEmpty() || ui->maSach_lineEdit->text().isEmpty()) {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn chưa điện đầy đủ thông tin.");
        return;
    }
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, getMaThe());
    if ( DemSoSachDangMuon(p->thong_tin.head_lsms) > 3 || p->thong_tin.TrangThai == TrangThaiCuaThe::Khoa ) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể cho độc giả mượn sách vì thẻ độc giả độc đã bị khóa hoặc đã mượn nhiều hơn 3 quyển");
        return;
    }
    MuonSach(getMaThe(), getMaSach());
    accept();
}


void muonsach::on_maThe_lineEdit_textChanged(const QString &arg1)
{
    Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, arg1.toInt());
    if ( p != nullptr ) {
        inThongTin(p->thong_tin.MATHE, ui->sachMuon_table);
    }
}


void muonsach::on_pushButton_cancel_clicked()
{
    close();
}

