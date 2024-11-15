#include "Muon_tra.h"
using namespace std;


int TrangThai(Date ngay_muon, Date ngay_tra) {
    return ngay_tra.day == 0 ? Chua_Tra : Da_Tra;
}

int TimViTriMaSachTrongDanhSachSachMuon(int &SoLuongSach, SachMuon DanhSachSachMuon[], string maSach) {
    string ma_ISBN = maSach.substr(0, 17);
    for (int i = 0; i < SoLuongSach; i++) {
        if (DanhSachSachMuon[i].masach == ma_ISBN) {
            return i;
        }
    }
    return -1;
}

void CapNhatSoLuotMuon (int &SoLuongSach, string ma_sach, SachMuon DanhSachSachMuon[]) {
    int vitri = TimViTriMaSachTrongDanhSachSachMuon(SoLuongSach, DanhSachSachMuon, ma_sach) ;
    string ma_ISBN = ma_sach.substr(0, 17);
    if(vitri != -1) {
        DanhSachSachMuon[vitri].demsoluotmuon++;
    } else {
        DanhSachSachMuon[SoLuongSach].masach = ma_ISBN;
        DanhSachSachMuon[SoLuongSach].demsoluotmuon = 1;
        SoLuongSach++;
    }
}

int DemSoSachDangMuon(DanhSachMUONTRA *demsach) {
    DanhSachMUONTRA *temp = demsach;
    int dem = 0;

    while(temp!=nullptr) {
        if(temp->data.trangthai == 0 || temp->data.trangthai == 2) { // viết hàm bool
            dem++;
        }
        temp = temp->next;
    }
    return dem;
}

void DatLaiSoLuotMuon(int &SoLuongSach, SachMuon DanhSachSachMuon[]) {
    for(int i = 0; i < SoLuongSach; i++) {
        DanhSachSachMuon[i].demsoluotmuon = 0;
    }
}

void ThemSachVaoLichSuMuonSach (DanhSachMUONTRA*& head, string ma,int trangthai, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA data(ma, ngayMuon, ngayTra, trangthai);
    DanhSachMUONTRA* newMUONTRA = new DanhSachMUONTRA(data);

    if (head == nullptr) {
        head = newMUONTRA;
    } else {
        newMUONTRA->next = head;
        head = newMUONTRA;
    }
}


bool MuonSachQuaHan(DanhSachMUONTRA *head) {
    DanhSachMUONTRA *p = head;
    while(p != nullptr) {
        if(p->data.NgayTra.day == 0 ){
            if(SoNgayQuaHan(p->data.NgayMuon, NgayHomNay()) > 0) return true;
        }
        p = p->next;
    }
    return false;
}

DanhMucSach* TimDiaChiSachTrongDanhMucSach(string maSach) {
    string ma_isbn = maSach.substr(0, 17);
    int vitri = TimKiemViTriDauSach(ma_isbn);
    if (vitri == -1) {
        return nullptr;
    }
    for (DanhMucSach* current = danh_sach_dau_sach.node[vitri]->dms ; current != nullptr; current = current->next) {
        if (current->masach == maSach) return current;
    }
    return nullptr;
}

bool KiemTraVaInRaLoiKhiMuonSach(string maSach, DanhMucSach* danhmucsach, Danh_Sach_The_Doc_Gia *doc_gia) {
    string ma_sach = maSach.substr(0, 17);
    int SoSachDangMuon = DemSoSachDangMuon(doc_gia->thong_tin.head_lsms);
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;
    DanhMucSach* cur = danhmucsach;
    if(doc_gia->thong_tin.TrangThai == Khoa) {
        QMessageBox::warning(nullptr, "Lỗi", "Không mượn được sách vì thẻ độc giả bị khóa.");
        return false;
    }
    if(SoSachDangMuon >= 3) {
        QMessageBox::warning(nullptr, "Lỗi", "đã mượn 3 quyển sách, trả sách để mượn thêm.");
        return false;
    }
    if(MuonSachQuaHan(doc_gia->thong_tin.head_lsms)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không được mượn sách vì đã có sách mượn quá hạn.");
        return false;
    }
    if(cur->trangthai != co_the_muon) {
        QMessageBox::warning(nullptr, "Lỗi", "Sách đã được mượn hoặc thanh lý.");
        return false;
    }
    while(current != nullptr) {
        string ma_ISBN = current->data.masach.substr(0, 17);
        if(ma_sach == ma_ISBN && current->data.trangthai == Chua_Tra) {
            QMessageBox::warning(nullptr, "Lỗi", "Bạn đã mượn sách này rồi, vui lòng chọn sách khác.");
            return false;
        }
        current = current->next;
    }
    return true;
}

void MuonSach( const int& maThe, const string& maSach) {
    Danh_Sach_The_Doc_Gia *doc_gia = timKiemTheDocGia(maThe);
    Date ngaymuon = NgayHomNay();

    Date ngaytra; // ngaytra = {0/0/0}

    if (doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    DanhMucSach *cur = TimDiaChiSachTrongDanhMucSach(maSach);

    if ( !KiemTraVaInRaLoiKhiMuonSach(maSach, cur, doc_gia) ) {
        return;
    }

    ThemSachVaoLichSuMuonSach(doc_gia->thong_tin.head_lsms, maSach,Chua_Tra, ngaymuon, ngaytra);
    CapNhatTrangThaiSach(maSach, da_duoc_muon);

}



void TraSach(const unsigned int& ma_the, const string& ma_sach) {
    Danh_Sach_The_Doc_Gia *doc_gia = timKiemTheDocGia(ma_the);

    if (doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    if (doc_gia->thong_tin.head_lsms == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Độc giả này không có sách mượn.");
        return;
    }

    DanhSachMUONTRA* current = doc_gia->thong_tin.head_lsms;
    while (current != nullptr) {
        if (current->data.masach == ma_sach && current->data.trangthai != Da_Tra) {

                current->data.NgayTra = NgayHomNay();
                current->data.capNhatTrangThaiMuonTra(NgayHomNay());

                CapNhatTrangThaiSach(ma_sach, co_the_muon);
                capNhatTrangThaiThe(doc_gia);

                break;
        }
        current = current->next;
    }
}



void MergeSachMuon(SachMuon* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    SachMuon* L = new SachMuon[n1];
    SachMuon* R = new SachMuon[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].demsoluotmuon > R[j].demsoluotmuon) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Sao chép các phần tử còn lại của L (nếu còn)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sao chép các phần tử còn lại của R (nếu còn)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void MergeSortSachMuon(SachMuon* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Đệ quy chia đôi mảng
        MergeSortSachMuon(arr, left, mid);
        MergeSortSachMuon(arr, mid + 1, right);

        // Gộp hai mảng đã sắp xếp
        MergeSachMuon(arr, left, mid, right);
    }
}

void CapNhatSoLuotMuonTuDanhSachLichSuMuonTra (int &SoLuongSach, SachMuon DanhSachSachMuon [], DanhSachMUONTRA *danh_sach_muon_tra) {
    DanhSachMUONTRA *current = danh_sach_muon_tra;
    while( current != nullptr ) {
        CapNhatSoLuotMuon(SoLuongSach, current->data.masach, DanhSachSachMuon);
        current = current->next;
    }
}

void Top10QuyenSachNhieuLuotMuonNhat(int &SoLuongSach, SachMuon DanhSachSachMuon[], DanhSachMUONTRA * danh_sach_muon_tra, QTableView *tableView) {

    CapNhatSoLuotMuonTuDanhSachLichSuMuonTra(SoLuongSach, DanhSachSachMuon,danh_sach_muon_tra);
    MergeSortSachMuon(DanhSachSachMuon, 0, SoLuongSach-1);
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "ISBN");
    model->setHeaderData(1, Qt::Horizontal, "Tên sách");
    model->setHeaderData(2, Qt::Horizontal, "Tác Giả");
    model->setHeaderData(3, Qt::Horizontal, "Năm Sản Xuất");
    model->setHeaderData(4, Qt::Horizontal, "Thể Loại");
    model->setHeaderData(5, Qt::Horizontal, "Số lượt mượn");


    for (int i = 0; i < SoLuongSach && i < 10; i++) {
        int vitridausach = TimKiemViTriDauSach(DanhSachSachMuon[i].masach);
        model->insertRow(i);

        model->setItem(i, 0, new QStandardItem(QString::fromStdString(DanhSachSachMuon[i].masach)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, DanhSachSachMuon[i].masach))));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[vitridausach]->tacgia)));
        model->setItem(i, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[vitridausach]->namsx)));
        model->setItem(i, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[vitridausach]->theloai)));
        model->setItem(i, 5, new QStandardItem(QString::number(DanhSachSachMuon[i].demsoluotmuon)));

        // Thay đổi màu cho toàn hàng
        if (i == 0) { // Top 1
            for (int col = 0; col < 6; ++col) {
                model->setData(model->index(i, col), QBrush(Qt::yellow), Qt::BackgroundRole);
            }
        } else if (i == 1) { // Top 2
            for (int col = 0; col < 6; ++col) {
                model->setData(model->index(i, col), QBrush(Qt::lightGray), Qt::BackgroundRole);
            }
        } else if (i == 2) { // Top 3
            for (int col = 0; col < 6; ++col) {
                model->setData(model->index(i, col), QBrush(Qt::cyan), Qt::BackgroundRole);
            }
        }
    }
    tableView->setModel(model);
    tableView->viewport()->update();

    tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    tableView->setColumnWidth(0, 150);
    tableView->setColumnWidth(1, 300);

}


void NhapThongTinVaoTop10(int &SoLuongSach, SachMuon DanhSachSachMuon[], QTableView *tableView, Danh_Sach_The_Doc_Gia *root) {
    if (root == nullptr) return;
    NhapThongTinVaoTop10(SoLuongSach, DanhSachSachMuon, tableView, root->ptr_left);
    Top10QuyenSachNhieuLuotMuonNhat(SoLuongSach, DanhSachSachMuon, root->thong_tin.head_lsms, tableView);
    NhapThongTinVaoTop10(SoLuongSach,DanhSachSachMuon, tableView, root->ptr_right);
}

/*------------------------------------------------------------------------------------------------------------*/

void InsertOder(danhSachDocGiaMuonQuaHan*& head, danhSachDocGiaMuonQuaHan* current){
    if (current == nullptr) {
        return;
    }
    if (head == nullptr || current->value.second->data.NgayMuon < head->value.second->data.NgayMuon) {
        current->next = head;
        head = current;
    } else {
        danhSachDocGiaMuonQuaHan* s = head;
        danhSachDocGiaMuonQuaHan* t = nullptr;

        while (s != nullptr && s->value.second->data.NgayMuon < current->value.second->data.NgayMuon) {
            t = s;
            s = s->next;
        }

        if (t != nullptr) {
            t->next = current;
        }
        current->next = s;
    }
}

void DuyetCayDeLayDocGiaQuaHan(danhSachDocGiaMuonQuaHan*& head, Danh_Sach_The_Doc_Gia* p) {
    if (p == nullptr) {
        return;
    }

    // Kiểm tra thông tin mượn trả
    if (p->thong_tin.head_lsms != nullptr) {
        DanhSachMUONTRA* current = p->thong_tin.head_lsms;
        while (current != nullptr) {
            if (current->data.trangthai == 0 && SoNgayQuaHan(current->data.NgayMuon, current->data.NgayTra) > 0) {
                danhSachDocGiaMuonQuaHan* n = new danhSachDocGiaMuonQuaHan;
                n->value.first = p;
                n->value.second = current;
                InsertOder(head, n);
                break;
            }
            current = current->next;
        }
    }

    // Đệ quy qua cây trái và phải
    DuyetCayDeLayDocGiaQuaHan(head, p->ptr_left);
    DuyetCayDeLayDocGiaQuaHan(head, p->ptr_right);
}

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan(Danh_Sach_The_Doc_Gia* root) {
    danhSachDocGiaMuonQuaHan* head = nullptr;
    DuyetCayDeLayDocGiaQuaHan(head, root);
    return head;
}

void GiaiPhongDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan* head) {
    while (head != nullptr) {
        danhSachDocGiaMuonQuaHan* temp = head;
        head = head->next;
        delete temp;
    }
}



void inDanhSachDocGiaMuonQuaHan(QTableView *tableView, Danh_Sach_The_Doc_Gia *root) {
    danhSachDocGiaMuonQuaHan* current = layDanhSachDocGiaMuonQuaHan(root);
    QStandardItemModel* model = new QStandardItemModel();
    int row = 0;
    model->setColumnCount(7);
    model->setHeaderData(0, Qt::Horizontal, "Mã Thẻ");
    model->setHeaderData(1, Qt::Horizontal, "Họ Và Tên");
    model->setHeaderData(2, Qt::Horizontal, "Giới Tính");
    model->setHeaderData(3, Qt::Horizontal, "Trạng Thái");
    model->setHeaderData(4, Qt::Horizontal, "Mã Sách");
    model->setHeaderData(5, Qt::Horizontal, "Tên Sách");
    model->setHeaderData(6, Qt::Horizontal, "Ngày Quá Hạn");
    while( current != nullptr) {
        Date ngay_hom_nay = NgayHomNay();
        int so_ngay_qua_han = SoNgayQuaHan(current->value.second->data.NgayMuon, ngay_hom_nay);
        if ( so_ngay_qua_han <= 7) {
            current = current->next;
            continue;
        }
        string hovaten = current->value.first->thong_tin.Ho + " " + current->value.first->thong_tin.Ten;
        model->insertRow(row);
        model->setItem(row, 0, new QStandardItem(QString::number(current->value.first->thong_tin.MATHE)));
        model->setItem(row, 1, new QStandardItem(QString::fromStdString(hovaten)));
        model->setItem(row, 2, new QStandardItem(current->value.first->thong_tin.phai == Nam ? "Nam" : "Nữ"));
        model->setItem(row, 3, new QStandardItem(current->value.first->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Khóa"));
        model->setItem(row, 4, new QStandardItem(QString::fromStdString(current->value.second->data.masach)));
        model->setItem(row, 5, new QStandardItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->value.second->data.masach))));
        model->setItem(row, 6, new QStandardItem(QString::number(so_ngay_qua_han)));
        current = current->next;
        row++;
    }


    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    GiaiPhongDanhSachDocGiaMuonQuaHan(current);

}

void ChuaDenSach(int mathe, string masach) {
    Danh_Sach_The_Doc_Gia *p = timKiemTheDocGia(mathe);
    p->thong_tin.TrangThai = Khoa;
    DanhSachMUONTRA *sach_mat = p->thong_tin.head_lsms;

    while(sach_mat != nullptr) {
        if(sach_mat->data.masach == masach && sach_mat->data.trangthai == Chua_Tra) {
            sach_mat->data.trangthai = Mat_Sach;
            break;
        }
        sach_mat = sach_mat->next;
    }

}

void DaDenSach(int mathe, string masach) {
    Danh_Sach_The_Doc_Gia *p = timKiemTheDocGia(mathe);
    p->thong_tin.TrangThai = Dang_Hoat_Dong;
    DanhSachMUONTRA *sach_mat = p->thong_tin.head_lsms;
    while(sach_mat != nullptr) {
        if(sach_mat->data.masach == masach && sach_mat->data.trangthai != Da_Tra) {
            sach_mat->data.trangthai = Da_Tra;
            CapNhatTrangThaiSach(masach, co_the_muon);
            break;
        }
        sach_mat = sach_mat->next;
    }
}


