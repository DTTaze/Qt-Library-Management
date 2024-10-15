#include "The_doc_gia.h"
#include "Muon_tra.h"

Danh_Sach_The_Doc_Gia* root;
Danh_Sach_The_Doc_Gia* rp;
void Them_Doc_Gia(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.MATHE == thong_tin_the_doc_gia.MATHE ) {
            cout << "Ma the doc gia da ton tai." << endl;
            return;
        }
        if ( root->thong_tin.MATHE < thong_tin_the_doc_gia.MATHE ) {
            Them_Doc_Gia(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

void Them_Doc_Gia_Theo_Ten(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.Ten == thong_tin_the_doc_gia.Ten ) {
            cout << "Ten doc gia da ton tai." << endl;
            return;
        }
        if ( root->thong_tin.Ten < thong_tin_the_doc_gia.Ten ) {
            Them_Doc_Gia(root->ptr_right, thong_tin_the_doc_gia);
        } else {
            Them_Doc_Gia(root->ptr_left, thong_tin_the_doc_gia);
        }
    }
}

void Xoa_Truong_Hop_Co_Hai_Cay_Con(Danh_Sach_The_Doc_Gia* r ) {
    if ( r->ptr_left != nullptr ) {
        Xoa_Truong_Hop_Co_Hai_Cay_Con(r->ptr_left);
    } else {
        rp->thong_tin = r->thong_tin;
        Danh_Sach_The_Doc_Gia* temp = r;
        r = r->ptr_right;
        delete temp;
    }
}

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia* &r, const int& ma_the_doc_gia) {
    if ( r == nullptr ) {
        cout << "Khong Tim Thay " << ma_the_doc_gia << endl;
    }
    else {
        if ( r->thong_tin.MATHE < ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_right, ma_the_doc_gia );
        } else if ( r->thong_tin.MATHE > ma_the_doc_gia ) {
            Xoa_Doc_Gia(r->ptr_left, ma_the_doc_gia );
        } else {
            rp = r;
            if ( rp->ptr_right == nullptr ) {
                r = rp->ptr_left;
            } else if ( rp->ptr_left == nullptr ) {
                r = rp->ptr_right;
            } else {
                Xoa_Truong_Hop_Co_Hai_Cay_Con(rp->ptr_right);
            }
            delete rp;
        }
    }
}

Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, const int& mathe ) {
    Danh_Sach_The_Doc_Gia* curr = root;
    while ( curr != nullptr && curr->thong_tin.MATHE != mathe ) {
        if ( curr->thong_tin.MATHE < mathe ) {
            curr = curr->ptr_right;
        } else {
            curr = curr->ptr_left;
        }
    }
    return curr;
}

void Tao_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* root_maso, Danh_Sach_The_Doc_Gia* &root_ten) {
    if ( root_maso == nullptr ) {
        return;
    }

    Them_Doc_Gia_Theo_Ten(root_ten, root_maso->thong_tin);
    Tao_Danh_Sach_Theo_Ten(root_maso->ptr_left, root_ten);
    Tao_Danh_Sach_Theo_Ten(root_maso->ptr_right, root_ten);
}

void Xoa_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* &root_ten) {
    if ( root_ten == nullptr ) {
        return;
    }
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_left);
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_right);
    delete root_ten;
}

void Doc_Thong_Tin_Tu_File(Danh_Sach_The_Doc_Gia*& root_ma_so, QTableWidget* tableWidget) {
    QFile file("docgia_100.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // Mở file với chế độ đọc
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file"); // Thay đổi nullptr thành `this` nếu trong lớp
        return;
    }

    while (!file.atEnd()) { // Kiểm tra đến cuối file
        QByteArray line = file.readLine(); // Đọc từng dòng
        QString strLine = QString(line).trimmed(); // Xử lý dòng đọc được
        QStringList fields = strLine.split(" "); // Tách theo khoảng trắng

        if (fields.size() <= 4) {
            continue; // Bỏ qua nếu không đủ trường
        }

        bool ok;
        unsigned int mathe = fields[0].toUInt(&ok); // Chuyển đổi mã thẻ sang số nguyên
        if (!ok) {
            continue; // Bỏ qua nếu không thể chuyển đổi
        }

        QString Ho = fields[1] + " " + fields[2];
        QString Ten = fields[3];
        Phai phai = (fields[4] == "Nam") ? Nam : Nu;

        The_Doc_Gia docGia;
        docGia.MATHE = mathe;
        docGia.Ho = Ho;
        docGia.Ten = Ten;
        docGia.phai = phai;
        docGia.TrangThai = Dang_Hoat_Dong; // Trạng thái mặc định

        Them_Doc_Gia(root_ma_so, docGia); // Thêm độc giả vào cây
        Them_Vao_QTableWidget(tableWidget, docGia); // Thêm vào QTableWidget
    }

    file.close(); // Đóng file
}

void Them_Vao_QTableWidget(QTableWidget* tableWidget, const The_Doc_Gia& docGia) {
    int row = tableWidget->rowCount(); // Lấy số hàng hiện tại
    tableWidget->insertRow(row); // Thêm hàng mới

    // Thêm dữ liệu vào từng ô
    tableWidget->setItem(row, 0, new QTableWidgetItem(docGia.Ho)); // Họ
    tableWidget->setItem(row, 1, new QTableWidgetItem(docGia.Ten)); // Tên
    tableWidget->setItem(row, 2, new QTableWidgetItem(docGia.phai == Nam ? "Nam" : "Nữ")); // Phái
    tableWidget->setItem(row, 3, new QTableWidgetItem(docGia.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Không Hoạt Động")); // Trạng thái
}
