#include "The_doc_gia.h"

Danh_Sach_Theo_Ten* head = nullptr;

Queue<int> danhSachMaThe;

Danh_Sach_The_Doc_Gia* root;
Danh_Sach_The_Doc_Gia* rp;
//--------------------------------------------------------Hàm liên quan đến mã thẻ------------------------------------------------------------------------------
void taoDanhSachMaThe(int start, int end) {
    danhSachMaThe.clear();
    Queue<pair<int,int>> ranges; // Queue dùng để duyệt các khoảng theo thứ tự hạng
    ranges.push({start, end}); // [a,b]

    while (!ranges.empty()) { // Lặp lại cho tới khi không còn khoảng nào
        auto range = ranges.front();
        ranges.pop();

        int a = range.first;
        int b = range.second;

        if (a > b) continue; // Nếu mà khoảng không hợp lệ thì bỏ qua

        int median = (a + b) / 2; // Tìm vị trí chính giữa
        danhSachMaThe.push(median);
        ranges.push({a, median - 1}); // [a - 1, median]
        ranges.push({median + 1, b}); // [median + 1, b]
    }
}

void docFileMaThe() {
    ifstream inFile("Ma_The.txt");
    if (!inFile) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể đọc file Ma_The.txt");
    }

    int maThe;
    while (inFile >> maThe) {
        danhSachMaThe.push(maThe);
    }
    inFile.close();
}

void ghiMaTheVaoFile() {
    ofstream outFile("Ma_The.txt");
    if (!outFile) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể ghi file Ma_The.txt");
    }

    Queue<int> tempQueue = danhSachMaThe;
    while ( !tempQueue.empty() ) {
        outFile << tempQueue.front() << " ";
        tempQueue.pop();
    }
    outFile.close();
}

int layMaThe() {
    if (danhSachMaThe.empty()) {
        QMessageBox::warning(nullptr, "Lỗi", "Danh sách mã thẻ rỗng!");
        return -1;
    }
    int maThe = danhSachMaThe.front();
    danhSachMaThe.pop();
    danhSachMaThe.push(maThe);
    return maThe;
}
//---------------------------------------------------Hàm liên quan đến tạo bảng theo tên------------------------------------------------------------------------------------
void taoDanhSachTheoTen(Danh_Sach_The_Doc_Gia* root) {
    if ( root == nullptr ) return;
    themVaoCoThuTuDanhSachTheDocGiaTheoTen(root);
    taoDanhSachTheoTen(root->ptr_left);
    taoDanhSachTheoTen(root->ptr_right);
}

void xoaDanhSachTheoTen() {
    Danh_Sach_Theo_Ten* current = head;
    Danh_Sach_Theo_Ten* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

void themVaoCoThuTuDanhSachTheDocGiaTheoTen(Danh_Sach_The_Doc_Gia* docgia) {
    Danh_Sach_Theo_Ten* newNode = new Danh_Sach_Theo_Ten;
    newNode->PTR = docgia;
    newNode->ten = docgia->thong_tin.Ten;

    Danh_Sach_Theo_Ten* truoc = nullptr;
    Danh_Sach_Theo_Ten* sau = head;

    while (sau != nullptr && newNode->ten > sau->ten) {
        truoc = sau;
        sau = sau->next;
    }

    newNode->next = sau;
    if (truoc == nullptr) {
        head = newNode;
    } else {
        truoc->next = newNode;
    }
}

void inDanhSachTheDocGiaTheoTen(QTableWidget* tableWidget) {
    Danh_Sach_Theo_Ten* temp = head;
    while ( temp != nullptr ) {
        themTheDocGiaVaoBang(tableWidget, temp->PTR);
        temp = temp->next;
    }
}

//-------------------------------------------------Hàm liên quan đến thao tác trên cây--------------------------------------------------------------------------------------
void Them_Doc_Gia(Danh_Sach_The_Doc_Gia*& root, const The_Doc_Gia& thong_tin_the_doc_gia ) {
    if ( root == nullptr ) {
        root = new Danh_Sach_The_Doc_Gia(thong_tin_the_doc_gia);
    } else {
        if ( root->thong_tin.MATHE == thong_tin_the_doc_gia.MATHE ) {
            QMessageBox::warning(nullptr, "Lỗi", "Mã thẻ độc giả đã tồn tại.");
            return;
        } else if ( root->thong_tin.MATHE < thong_tin_the_doc_gia.MATHE ) {
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
        rp = r;
        r = rp->ptr_right;
    }
}

void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia*& root, const int& ma_the_doc_gia) {
    if (root->thong_tin.MATHE < ma_the_doc_gia) {
        Xoa_Doc_Gia(root->ptr_right, ma_the_doc_gia);
    } else if (root->thong_tin.MATHE > ma_the_doc_gia) {
        Xoa_Doc_Gia(root->ptr_left, ma_the_doc_gia);
    } else { // root->MATHE == ma_the_doc_gia
        rp = root;
        if (root->ptr_left == nullptr) {
            root = rp->ptr_right;
        }
        else if (root->ptr_right == nullptr) {
            root = root->ptr_left;
        }
        else {
            Xoa_Truong_Hop_Co_Hai_Cay_Con(rp->ptr_right);
        }
        delete rp;
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

void Cap_Nhat_Thong_Tin_Doc_Gia(int maThe, const string& field, const string& newValue) {
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

void capNhatTrangThaiThe(Danh_Sach_The_Doc_Gia* docGia) {
    DanhSachMUONTRA* temp = docGia->thong_tin.head_lsms;
    while ( temp != nullptr ) {
        if ( SoNgayQuaHan(temp->data.NgayMuon, temp->data.NgayTra) > 7 || temp->data.trangthai == 2 ) { // Thẻ sẽ bị khóa nếu số ngày mượn quá 7 ngày hoặc làm mất sách
            docGia->thong_tin.TrangThai = Khoa;
        }
        temp = temp->next;
    }
    docGia->thong_tin.TrangThai = Dang_Hoat_Dong;
}
//---------------------------------------------------------------------------------------------------------------------------------------
void docFileThongTinTheDocGia( QTableWidget* tableWidget) { // Hàm đọc thông tin từ file sao đó thêm nó vào cây nhị phân tìm kiếm
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
            int trangthaimuontra = fields[index + 1].toInt();
            Date ngay_muon = ChuyenStringSangDate(fields[index+2].toStdString());
            Date ngay_tra;
            if (!fields[index + 3].isEmpty()){
                ngay_tra = ChuyenStringSangDate(fields[index+3].toStdString());
            }

            ThemSach(p->thong_tin.head_lsms, ma_sach,trangthaimuontra, ngay_muon, ngay_tra);
            if(trangthaimuontra == 0 || trangthaimuontra == 2) {
                CapNhatTrangThaiSach(ma_sach, 1);
            }
            else {
                CapNhatTrangThaiSach(ma_sach, 0);
            }

            index += 4;
        }
    }
    inFile.close();
}

void ghiThongTinTheDocGia() {
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
                << (current->thong_tin.phai == Nam ? "Nam" : "Nữ") << "|"
                << (current->thong_tin.TrangThai == TrangThaiCuaThe::Dang_Hoat_Dong ? "1" : "0" ) << "|";

        DanhSachMUONTRA* temp = current->thong_tin.head_lsms;
        while (temp != nullptr) {
            outFile << temp->data.masach << "|"
                    << (temp->data.trangthai == Chua_Tra ? "0" : "1") << "|"
                    << ChuyenDateSangString(temp->data.NgayMuon) << "|"
                    << ChuyenDateSangString(temp->data.NgayTra) << "|";
            temp = temp->next;
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
void themTheDocGiaVaoBang(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* docGia) {
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(docGia->thong_tin.MATHE)));
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(docGia->thong_tin.Ho)));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(docGia->thong_tin.Ten)));
    tableWidget->setItem(row, 3, new QTableWidgetItem(docGia->thong_tin.phai == Nam ? "Nam" : "Nữ"));
    tableWidget->setItem(row, 4, new QTableWidgetItem(docGia->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Khóa"));
}

void inDanhSachTheDocGiaTheoMaSo(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root ) {
    if ( root == nullptr ) return;
    inDanhSachTheDocGiaTheoMaSo(tableWidget, root->ptr_left);
    themTheDocGiaVaoBang(tableWidget, root);
    inDanhSachTheDocGiaTheoMaSo(tableWidget, root->ptr_right);
}
//---------------------------------------------------------------------------------------------------------------------------------------


