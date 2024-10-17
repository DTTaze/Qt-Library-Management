#include "The_doc_gia.h"

Danh_Sach_The_Doc_Gia* root;
Danh_Sach_The_Doc_Gia* rp;
Danh_Sach_The_Doc_Gia* root_ten;
Mang_The_Doc_Gia Mang_The_Doc_Gia_Tam_Thoi;
int Mang_Ma_The[MAXRANDOM];
int index_left = 4;
int index_right = 5004;
bool layTuTrai = true;

void Tao_Mang_The() {
    int index = 0;
    taoMangTrungVi(index, 1, 10000);
}

void taoMangTrungVi(int& index, int start, int end) {
    if (start > end) return;
    int mid = start + (end - start) / 2;
    Mang_Ma_The[index++] = mid;  // Gán giá trị vào mảng và tăng index
    taoMangTrungVi(index, start, mid - 1);  // Nửa trái
    taoMangTrungVi(index, mid + 1, end);    // Nửa phải
}

int LayMaTheNgauNhien() {
    if (index_left >= 5000 && index_right >= 10000) {
        std::cout << "Da het ma the" << std::endl;
        return -1;  // Trả về -1 khi hết mã thẻ
    }

    if (layTuTrai && index_left < 5000) {
        layTuTrai = false;
        return Mang_Ma_The[index_left++];
    } else if (!layTuTrai && index_right < 10000) {
        layTuTrai = true;
        return Mang_Ma_The[index_right++];
    }

    // Nếu nửa trái hoặc nửa phảiN đã hết, chuyển sang nửa còn lại
    if (index_left >= 5000) {  // Nếu nửa trái đã hết
        layTuTrai = false;
        return Mang_Ma_The[index_right++];
    }

    if (index_right >= 10000) {  // Nếu nửa phải đã hết
        layTuTrai = true;
        return Mang_Ma_The[index_left++];
    }

    return 5000;  // Giá trị mặc định nếu không thỏa mãn điều kiện nào
}

void Them_Doc_Gia_Mang(const The_Doc_Gia& docgia) {
    if ( Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The < MAXRANDOM ) {
        int index = 0;
        while (index < Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The && docgia.Ten > Mang_The_Doc_Gia_Tam_Thoi.DS[index].Ten) {
            index++;
        }
        for ( int i = Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The; i > index; i-- ) {
            Mang_The_Doc_Gia_Tam_Thoi.DS[i] = Mang_The_Doc_Gia_Tam_Thoi.DS[i - 1];
        }
        Mang_The_Doc_Gia_Tam_Thoi.DS[index] = docgia;
        Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The++;
    } else {
        cout << "Mang the da day";
    }
}

Danh_Sach_The_Doc_Gia* Tao_Cay_Theo_Ten(int start, int end) {
    if ( start > end ) return nullptr;
    int mid = ( start + end ) / 2;
    Danh_Sach_The_Doc_Gia* newNode = new Danh_Sach_The_Doc_Gia;
    newNode->thong_tin = Mang_The_Doc_Gia_Tam_Thoi.DS[mid];
    newNode->ptr_left = Tao_Cay_Theo_Ten(start, mid - 1);
    newNode->ptr_right = Tao_Cay_Theo_Ten(mid + 1, end);
    return newNode;
}

void Xoa_Danh_Sach_Theo_Ten(Danh_Sach_The_Doc_Gia* &root_ten) {
    if ( root_ten == nullptr ) {
        return;
    }
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_left);
    Xoa_Danh_Sach_Theo_Ten(root_ten->ptr_right);
    delete root_ten;
}

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

void Xoa_Truong_Hop_Co_Hai_Cay_Con(Danh_Sach_The_Doc_Gia*& r ) {
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


void Doc_Thong_Tin_Tu_File(Danh_Sach_The_Doc_Gia*& root_ma_so, QTableWidget* tableWidget) { // Hàm đọc thông tin từ file sao đó thêm nó vào cây nhị phân tìm kiếm
    QFile file("docgia_100.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file");
        return;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString strLine = QString(line).trimmed(); // Đọc và xử lý dòng
        QStringList fields = strLine.split("|"); // Tách theo khoảng trắng

        if (fields.size() < 7) {
            continue; // Bỏ qua nếu không đủ trường
        }

        bool ok;
        unsigned int mathe = fields[0].toUInt(&ok);
        if (!ok) {
            continue; // Bỏ qua nếu không thể chuyển đổi
        }
        string Ho = fields[1].toStdString();
        string Ten = fields[2].toStdString();
        Phai phai = (fields[3].trimmed() == "Nam") ? Nam : Nu;

        The_Doc_Gia docGia;
        docGia.MATHE = mathe;
        docGia.Ho = Ho;
        docGia.Ten = Ten;
        docGia.phai = phai;
        docGia.TrangThai = Dang_Hoat_Dong;
        Them_Doc_Gia(root, docGia);
        Them_Doc_Gia_Mang(docGia);
    }
    file.close(); // Đóng file
}

void Them_Vao_QTableWidget(QTableWidget* tableWidget, const The_Doc_Gia& docGia) { // Hàm thêm nút thông tin vào table
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    // Thêm dữ liệu vào từng ô
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(docGia.MATHE))); // Mã thẻ
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(docGia.Ho))); // Họ
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(docGia.Ten))); // Tên
    tableWidget->setItem(row, 3, new QTableWidgetItem(docGia.phai == Nam ? "Nam" : "Nữ")); // Phái
    tableWidget->setItem(row, 4, new QTableWidgetItem(docGia.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Không Hoạt Động")); // Trạng thái
}

void Them_Cay_Vao_QTableWidget(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root ) { // Hàm thêm thông tin từ cây vào table
    if ( root == nullptr ) return;
    Them_Cay_Vao_QTableWidget(tableWidget, root->ptr_left);
    The_Doc_Gia tam_thoi = root->thong_tin;
    Them_Vao_QTableWidget(tableWidget, tam_thoi);
    Them_Cay_Vao_QTableWidget(tableWidget, root->ptr_right);
}



