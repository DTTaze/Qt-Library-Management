#include "The_doc_gia.h"

danhSachMaThe mangMaThe;
int index_MangRandom = 0;

Danh_Sach_Theo_Ten DS_Tam_Thoi[MAXRANDOM];
int DS_PTR = 0;

Danh_Sach_The_Doc_Gia* root;
//--------------------------------------------------------Hàm liên quan đến mã thẻ------------------------------------------------------------------------------
void taoMangTrungVi(int& index, int start, int end) {
    Queue<pair<int,int>> ranges; // Queue dùng để duyệt các khoảng theo thứ tự hạng
    ranges.push({start, end}); // [a,b]

    while (!ranges.empty()) { // Lặp lại cho tới khi không còn khoảng nào
        auto range = ranges.front();
        ranges.pop();

        int a = range.first;
        int b = range.second;

        if (a > b) continue; // Nếu mà khoảng không hợp lệ thì bỏ qua

        int median = (a + b) / 2; // Tìm vị trí chính giữa
        // Mang_Ma_The[index++] = median; // Thêm giá trị vào mảng
        mangMaThe.maThe[index++] = median; // Thêm giá trị vào mảng
        ranges.push({a, median - 1}); // [a - 1, median]
        ranges.push({median + 1, b}); // [median + 1, b]
    }
}

void Tao_Mang_The() {
    int index = 0;
    taoMangTrungVi(index, 1, 10000);
}

int LayMaTheNgauNhien() {
    if ( mangMaThe.maThe[index_MangRandom] == 0 || index_MangRandom > mangMaThe.soLuongMaThe) {
        QMessageBox::warning(nullptr,"Lỗi", "Đã hết mã thẻ");
        return 0;
    }
    return mangMaThe.maThe[index_MangRandom++];
}

void Doc_File_Ma_The() {
    ifstream inFile("Ma_The.txt");
    if (!inFile) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể đọc file Ma_The.txt");
    }
    for (int i = 0; i < MAXRANDOM; ++i) {
        inFile >> mangMaThe.maThe[i];
        mangMaThe.soLuongMaThe++;
    }
}

void Ghi_Ma_The_Vao_File(int index) {
    ofstream outFile("Ma_The.txt");
    if (!outFile) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể ghi file Ma_The.txt");
    }
    for (int i = index; i < mangMaThe.soLuongMaThe; i++) {
        outFile << mangMaThe.maThe[i] << " "; // Ghi từng số, cách nhau bằng khoảng trắng
    }
    outFile.close();
}
//---------------------------------------------------Hàm liên quan đến tạo bảng theo tên------------------------------------------------------------------------------------
void Them_Doc_Gia_Vao_Mang(Danh_Sach_The_Doc_Gia* docgia) {
    if ( DS_PTR < MAXRANDOM ) {
        int index = 0;
        while (index < DS_PTR && (docgia->thong_tin.Ten > DS_Tam_Thoi[index].ten || (docgia->thong_tin.Ten == DS_Tam_Thoi[index].ten && docgia->thong_tin.Ten > DS_Tam_Thoi[index].PTR->thong_tin.Ho))) {
            index++;
        }
        for ( int i = DS_PTR; i > index; i-- ) {
            DS_Tam_Thoi[i] = DS_Tam_Thoi[i - 1];
        }
        DS_Tam_Thoi[index].ten = docgia->thong_tin.Ten;
        DS_Tam_Thoi[index].PTR = docgia;
        DS_PTR++;
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Mảng thẻ tạm thời đã đầu");
    }
}

void Copy_Cay_Sang_Mang(Danh_Sach_The_Doc_Gia* root) {
    if ( root == nullptr ) return;
    Them_Doc_Gia_Vao_Mang(root);
    Copy_Cay_Sang_Mang(root->ptr_left);
    Copy_Cay_Sang_Mang(root->ptr_right);
}

void Them_Mang_Vao_QTableWidget(QTableWidget* tableWidget) {
    for( int i = 0; i < DS_PTR; i++) {
        Them_Vao_QTableWidget(tableWidget, DS_Tam_Thoi[i].PTR);
    }
}

//-------------------------------------------------Hàm liên quan đến thao tác trên cây--------------------------------------------------------------------------------------
void Them_Doc_Gia(Danh_Sach_The_Doc_Gia*& root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        Danh_Sach_The_Doc_Gia* con_tro_the_doc_gia = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
        root = con_tro_the_doc_gia;
    } else {
        if ( root->thong_tin.MATHE == thong_tin_the_doc_gia.MATHE ) {
            QMessageBox::warning(nullptr, "Lỗi", "Mã thẻ độc giả đã tồn tại.");
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
        if (root->ptr_left == nullptr) {
            Danh_Sach_The_Doc_Gia* temp = root;
            root = root->ptr_right;
            delete temp;
        }
        else if (root->ptr_right == nullptr) {
            Danh_Sach_The_Doc_Gia* temp = root;
            root = root->ptr_left;
            delete temp;
        }
        else {
            Danh_Sach_The_Doc_Gia* minNode = root->ptr_right;
            while (minNode->ptr_left != nullptr) {
                minNode = minNode->ptr_left;
            }
            root->thong_tin = minNode->thong_tin;
            Xoa_Truong_Hop_Co_Hai_Cay_Con(root->ptr_right);
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
void Ghi_The_Vao_File() {
    ofstream outFile("docgia_100.txt");
    if ( !outFile ) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể ghi file docgia_100.txt");
    }
    if ( root == nullptr ) return;

    Queue<Danh_Sach_The_Doc_Gia*> q;
    q.push(root);

    while ( !q.empty() ) {
        Danh_Sach_The_Doc_Gia* current = q.front();
        q.pop();

        outFile << current->thong_tin.MATHE << "|"
                << current->thong_tin.Ho << "|"
                << current->thong_tin.Ten << "|"
                << (current->thong_tin.phai == Nam ? "Nam" : "Nữ") << "|";
        if ( current->thong_tin.TrangThai == TrangThaiCuaThe::Dang_Hoat_Dong ) {
            outFile << "1" << "|";
        } else {
            outFile << "0" << "|";
        }
        if ( current->thong_tin.head_lsms != nullptr ) {
            DanhSachMUONTRA* temp = current->thong_tin.head_lsms;
            while ( temp != nullptr ) {
                outFile << current->thong_tin.head_lsms->data.masach << "|";
                if ( current->thong_tin.TrangThai == 0 ) {
                    outFile << "0" << "|";
                } else if ( current->thong_tin.TrangThai == 1 ) {
                    outFile << "1" << "|";
                } else {
                    outFile << "2" << "|";
                }
                outFile << ChuyenDateSangString(current->thong_tin.head_lsms->data.NgayMuon) << "|"
                        << ChuyenDateSangString(current->thong_tin.head_lsms->data.NgayTra) << "|";
                temp = temp->next;
            }
        }
        outFile << endl;
        if ( current->ptr_left != nullptr ) {
            q.push(current->ptr_left);
        }
        if ( current->ptr_right != nullptr ) {
            q.push(current->ptr_right);
        }
    }
    outFile.close();
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Doc_Thong_Tin_Tu_File(DanhSachMUONTRA*& danh_sach_muon_tra, QTableWidget* tableWidget) { // Hàm đọc thông tin từ file sao đó thêm nó vào cây nhị phân tìm kiếm
    ifstream inFile("docgia_100.txt");
    if (!inFile) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file docgia_100.txt");
        return;
    }

    string line;
    while (getline(inFile, line)) {
        QString strLine = QString::fromStdString(line).trimmed(); // Đọc và xử lý dòng
        QStringList fields = strLine.split("|"); // Tách theo |

        if (fields.size() < 5) {
            continue;
        }

        The_Doc_Gia docGia;
        docGia.MATHE = fields[0].toUInt();
        docGia.Ho = fields[1].toStdString();
        docGia.Ten = fields[2].toStdString();
        if ( fields[3] == "Nam") {
            docGia.phai = Nam;
        } else if ( fields[3] == "Nữ"){
            docGia.phai = Nu;
        } else {
            QMessageBox::warning(nullptr, "Lỗi", "Giới tính không hợp lệ");
        }
        if ( fields[4] == "1" ) {
            docGia.TrangThai = Dang_Hoat_Dong;
        } else if ( fields[4] == "0" ){
            docGia.TrangThai = Khoa;
        } else {
            QMessageBox::warning(nullptr, "Lỗi", "Trạng thái không hợp lệ");
        }
        Them_Doc_Gia(root, docGia);

        Danh_Sach_The_Doc_Gia* p = Tim_Kiem(root, docGia.MATHE);
        int index = 5;
        while ( index < fields.size() ) {
            if (fields[index].isEmpty()) break;

            string ma_sach = fields[index].toStdString();
            int trangthai = fields[index + 1].toInt();
            Date ngay_muon = ChuyenStringSangDate(fields[index+2].toStdString());
            Date ngay_tra;
            if (!fields[index + 3].isEmpty()){
                ngay_tra = ChuyenStringSangDate(fields[index+3].toStdString());
            }

            ThemSach(p->thong_tin.head_lsms, ma_sach, ngay_muon, ngay_tra);
            ThemSach(danh_sach_muon_tra, ma_sach, ngay_muon, ngay_tra);
            CapNhatTrangThaiSach(ma_sach, trangthai);
            index += 4;
        }
    }
    inFile.close();
}
//---------------------------------------------------------------------------------------------------------------------------------------
void Them_Vao_QTableWidget(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* docGia) { // Hàm thêm nút thông tin vào table
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    // Thêm dữ liệu vào từng ô
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(docGia->thong_tin.MATHE))); // Mã thẻ
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(docGia->thong_tin.Ho))); // Họ
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(docGia->thong_tin.Ten))); // Tên
    tableWidget->setItem(row, 3, new QTableWidgetItem(docGia->thong_tin.phai == Nam ? "Nam" : "Nữ")); // Phái
    tableWidget->setItem(row, 4, new QTableWidgetItem(docGia->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Khóa")); // Trạng thái
}

void Them_Cay_Vao_QTableWidget(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root ) { // Hàm thêm thông tin từ cây vào table
    if ( root == nullptr ) return;
    Them_Cay_Vao_QTableWidget(tableWidget, root->ptr_left);
    Them_Vao_QTableWidget(tableWidget, root);
    Them_Cay_Vao_QTableWidget(tableWidget, root->ptr_right);
}
//---------------------------------------------------------------------------------------------------------------------------------------


