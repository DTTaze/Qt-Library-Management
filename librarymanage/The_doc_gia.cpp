#include "The_doc_gia.h"

Danh_Sach_The_Doc_Gia* root;
Danh_Sach_The_Doc_Gia* rp;
Mang_The_Doc_Gia Mang_The_Doc_Gia_Tam_Thoi;
int Mang_Ma_The[MAXRANDOM];
int index_MangRandom = 10;
//--------------------------------------------------------------------------------------------------------------------------------------
int LayMaTheNgauNhien() {
    if ( index_MangRandom > MAXRANDOM ) {
        cout << "Het ma the";
        return -1;
    }
    return Mang_Ma_The[index_MangRandom++];
}

void Doc_File_Ma_The() {
    ifstream inFile("Ma_The.txt");
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
    }
    for (int i = 0; i < MAXRANDOM; ++i) {
        inFile >> Mang_Ma_The[i]; // Đọc từng số vào mảng
    }
    cout << "Array read from file: ";
}

void Ghi_Ma_The_Vao_File(int index) {
    ofstream outFile("So_The.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
    }
    for (int i = index; i < MAXRANDOM; ++i) {
        outFile << Mang_Ma_The[i] << " "; // Ghi từng số, cách nhau bằng khoảng trắng
    }
    outFile.close();
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Copy_Cay_Sang_Mang(Danh_Sach_The_Doc_Gia* root) {
    if ( root == nullptr ) return;
    Them_Doc_Gia_Mang(root->thong_tin);
    Copy_Cay_Sang_Mang(root->ptr_left);
    Copy_Cay_Sang_Mang(root->ptr_right);
}
void Them_Doc_Gia_Mang(const The_Doc_Gia& docgia) {
    if ( Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The < MAXRANDOM ) {
        int index = 0;
        while (index < Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The && (docgia.Ten > Mang_The_Doc_Gia_Tam_Thoi.DS[index].Ten || (docgia.Ten == Mang_The_Doc_Gia_Tam_Thoi.DS[index].Ten && docgia.Ho > Mang_The_Doc_Gia_Tam_Thoi.DS[index].Ho))) {
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

void Them_Mang_Vao_QTableWidget(QTableWidget* tableWidget) {
    for( int i = 0; i < Mang_The_Doc_Gia_Tam_Thoi.So_Luong_Ma_The; i++) {
        Them_Vao_QTableWidget(tableWidget, Mang_The_Doc_Gia_Tam_Thoi.DS[i]);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------
void Them_Doc_Gia(Danh_Sach_The_Doc_Gia*& root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
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

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia*& root, const int& ma_the_doc_gia) {
    if (root == nullptr) {
        QMessageBox::information(nullptr, "Thông báo", "Không tìm thấy độc giả");
        return;
    }

    if (root->thong_tin.MATHE < ma_the_doc_gia) {
        Xoa_Doc_Gia(root->ptr_right, ma_the_doc_gia);
    } else if (root->thong_tin.MATHE > ma_the_doc_gia) {
        Xoa_Doc_Gia(root->ptr_left, ma_the_doc_gia);
    } else { // root->MATHE == ma_the_doc_gia
        // Trường hợp 1: Nút chỉ có bên phải
        if (root->ptr_left == nullptr) {
            Danh_Sach_The_Doc_Gia* temp = root;
            root = root->ptr_right; // Di chuyển con trỏ sang nút bên phải
            delete temp; // Xóa nút hiện tại
        }
        // Trường hợp 2: Nút chỉ có bên trái
        else if (root->ptr_right == nullptr) {
            Danh_Sach_The_Doc_Gia* temp = root;
            root = root->ptr_left; // Di chuyển con trỏ sang nút bên trái
            delete temp; // Xóa nút hiện tại
        }
        // Trường hợp 3: Nút có cả hai con
        else {
            Danh_Sach_The_Doc_Gia* minNode = root->ptr_right;
            while (minNode->ptr_left != nullptr) {
                minNode = minNode->ptr_left; // Tìm nút nhỏ nhất trong cây con bên phải
            }
            root->thong_tin = minNode->thong_tin; // Sao chép thông tin
            Xoa_Truong_Hop_Co_Hai_Cay_Con(root->ptr_right); // Xóa nút nhỏ nhất
        }
    }
}

Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, const int& mathe ) {
    Danh_Sach_The_Doc_Gia* current = root;
    while ( current != nullptr && current->thong_tin.MATHE != mathe ) {
        if ( current->thong_tin.MATHE < mathe ) {
            current = current->ptr_right;
        } else {
            current = current->ptr_left;
        }
    }
    return current;
}

void Cap_Nhat_Thong_Tin_Doc_Gia(int maThe, const std::string& field, const std::string& newValue) {
    Danh_Sach_The_Doc_Gia* docGia = Tim_Kiem(root, maThe);
    if (docGia) {
        if (field == "Ho") {
            docGia->thong_tin.Ho = newValue; // Cập nhật họ
        } else if (field == "Ten") {
            docGia->thong_tin.Ten = newValue; // Cập nhật tên
        } else if (field == "Phai") {
            docGia->thong_tin.phai = (newValue == "Nam") ? Nam : Nu; // Cập nhật phái
        } else if (field == "TrangThai") {
            docGia->thong_tin.TrangThai = (newValue == "Đang Hoạt Động") ? Dang_Hoat_Dong : Khoa; // Cập nhật trạng thái
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Doc_Thong_Tin_Tu_File(Danh_Sach_The_Doc_Gia*& root_ma_so,DanhSachMUONTRA*& danh_sach_muon_tra, QTableWidget* tableWidget) { // Hàm đọc thông tin từ file sao đó thêm nó vào cây nhị phân tìm kiếm
    QFile file("docgia_100.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file");
        return;
    }

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString strLine = QString(line).trimmed(); // Đọc và xử lý dòng
        QStringList fields = strLine.split("|"); // Tách theo |

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
        // Them_Doc_Gia_Mang(docGia);
        if(fields[4].isEmpty()){
            continue;
        }else{
            string ma_sach = fields[4].toStdString();
            string ngay_muon = fields[5].toStdString();
            string ngay_tra = fields[6].toStdString();
            Them_lich_su_sach(&docGia,danh_sach_muon_tra,ma_sach,ngay_muon,ngay_tra);
        }
    }
    Copy_Cay_Sang_Mang(root);
    file.close(); // Đóng file
}
//---------------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------------


