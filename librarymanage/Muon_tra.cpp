#include "Muon_tra.h"
using namespace std;

int TrangThai(Date ngay_muon, Date ngay_tra) {
    return ngay_tra.day == 0 ? Chua_Tra : Da_Tra;
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
    DanhSachMUONTRA* current = head;
    while( current != nullptr ) {
        if( current->data.NgayTra.day == 0 ){
            if( SoNgayQuaHan(current->data.NgayMuon, NgayHomNay()) > 0 ) {
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

bool chuaTraSach(DanhSachMUONTRA *current){
    return current->data.trangthai == Chua_Tra ? true : false;
}

int DemSoSachDangMuon(DanhSachMUONTRA* head) {
    DanhSachMUONTRA *current = head;
    int soSachDangMuon = 0;

    while( current != nullptr) {
        if( chuaTraSach(current) ) {
            soSachDangMuon++;
        }
        current = current->next;
    }
    return soSachDangMuon;
}



bool DocGiaDangMuonSachNay(Danh_Sach_The_Doc_Gia *doc_gia, string maSach) {
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;
    string ma_sach = maSach.substr(0, 17);
    while(current != nullptr) {
        string ma_ISBN = current->data.masach.substr(0, 17);
        if(ma_sach == ma_ISBN && current->data.trangthai == Chua_Tra) {
            return true;
        }
    }
    return false;
}

bool KhongTonTaiMaSach(string ma_sach) {
    return TimDiaChiSachTrongDanhMucSach(ma_sach) != nullptr ? false : true;
}

bool KiemTraVaInRaLoiKhiMuonSach(int maThe, string maSach) {
    Danh_Sach_The_Doc_Gia* doc_gia= timKiemTheDocGia(maThe);
    if(doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Không tìm thấy độc giả. ");
        return false;
    }

    if(doc_gia->thong_tin.TrangThai == Khoa) {
        QMessageBox::warning(nullptr, "Lỗi", "Không mượn được sách vì thẻ độc giả bị khóa.");
        return false;
    }

    int SoSachDangMuon = DemSoSachDangMuon(doc_gia->thong_tin.head_lsms);
    if(SoSachDangMuon >= 3) {
        QMessageBox::warning(nullptr, "Lỗi", "đã mượn 3 quyển sách, trả sách để mượn thêm.");
        return false;
    }

    if(MuonSachQuaHan(doc_gia->thong_tin.head_lsms)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không được mượn sách vì đã có sách mượn quá hạn.");
        return false;
    }

    if(DocGiaDangMuonSachNay(doc_gia, maSach)) {
        QMessageBox::warning(nullptr, "Lỗi", "Bạn đã mượn sách này rồi, vui lòng chọn sách khác.");
        return false;
    }

    int vitridausach = TimKiemViTriDauSach(maSach); // Sách đã được mượn mà vẫn cho mượn
    if(vitridausach == -1) {
        QMessageBox::warning(nullptr, "Lỗi", "Không tìm thấy đầu sách.");
        return false;
    }

    DanhMucSach* cur = danh_sach_dau_sach.node[vitridausach]->dms;
    if(cur->trangthai != co_the_muon) {
        QMessageBox::warning(nullptr, "Lỗi", "Sách đã được mượn hoặc thanh lý.");
        return false;
    }

    if(KhongTonTaiMaSach(maSach)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không tồn tại mã sách.");
        return false;
    }

    return true;
}

void MuonSach( const int& maThe, const string& maSach) {
    Danh_Sach_The_Doc_Gia *doc_gia = timKiemTheDocGia(maThe);

    Date ngaytra; // ngaytra = {0/0/0}

    if ( !KiemTraVaInRaLoiKhiMuonSach(maThe, maSach) ) {
        return;
    }

    Date ngaymuon = NgayHomNay();
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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

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

        MergeSortSachMuon(arr, left, mid);
        MergeSortSachMuon(arr, mid + 1, right);

        MergeSachMuon(arr, left, mid, right);
    }
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

void CapNhatSoLuotMuonTuDanhSachLichSuMuonTra (int &SoLuongSach, SachMuon DanhSachSachMuon [], DanhSachMUONTRA *danh_sach_muon_tra) {
    DanhSachMUONTRA *current = danh_sach_muon_tra;
    while( current != nullptr ) {
        CapNhatSoLuotMuon(SoLuongSach, current->data.masach, DanhSachSachMuon);
        current = current->next;
    }
}

void NhapThongTinVaoTop10(int &SoLuongSach, SachMuon DanhSachSachMuon[], Danh_Sach_The_Doc_Gia *root) {
    if (root == nullptr) return;
    NhapThongTinVaoTop10(SoLuongSach, DanhSachSachMuon, root->ptr_left);
    CapNhatSoLuotMuonTuDanhSachLichSuMuonTra(SoLuongSach, DanhSachSachMuon, root->thong_tin.head_lsms);
    NhapThongTinVaoTop10(SoLuongSach,DanhSachSachMuon, root->ptr_right);
}

void Top10QuyenSachNhieuLuotMuonNhat(int &SoLuongSach, SachMuon DanhSachSachMuon[], QTableWidget *tableWidget) {

    NhapThongTinVaoTop10(SoLuongSach, DanhSachSachMuon,root);
    MergeSortSachMuon(DanhSachSachMuon, 0, SoLuongSach-1);

    for(int row = 0; row < SoLuongSach && row < 10; row++) {
        int vitri = TimKiemViTriDauSach(DanhSachSachMuon[row].masach);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(DanhSachSachMuon[row].masach)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach( DanhSachSachMuon[row].masach))));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[vitri]->tacgia)));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(danh_sach_dau_sach.node[vitri]->namsx)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(DanhSachSachMuon[row].demsoluotmuon)));
    }
    tableWidget->resizeColumnsToContents();
}


void chenCoThuTuVaoDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan*& head, danhSachDocGiaMuonQuaHan* current){
    if (current == nullptr) {
        return;
    }
    if (head == nullptr || current->value.second->data.NgayMuon < head->value.second->data.NgayMuon) {
        current->next = head;
        head = current;
    } else {
        danhSachDocGiaMuonQuaHan* s = head;
        danhSachDocGiaMuonQuaHan* t = nullptr;

        while (s != nullptr && s->value.second->data.NgayMuon <= current->value.second->data.NgayMuon) {
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

    if (p->thong_tin.head_lsms != nullptr) {
        DanhSachMUONTRA* current = p->thong_tin.head_lsms;
        while (current != nullptr) {
            if (current->data.trangthai == 0 && SoNgayQuaHan(current->data.NgayMuon, current->data.NgayTra) > 0) {
                danhSachDocGiaMuonQuaHan* n = new danhSachDocGiaMuonQuaHan;
                n->value.first = p;
                n->value.second = current;
                chenCoThuTuVaoDanhSachDocGiaMuonQuaHan(head, n);
            }
            current = current->next;
        }
    }

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

void inDanhSachDocGiaMuonQuaHan(QTableWidget *tableWidget, Danh_Sach_The_Doc_Gia *root) {
    danhSachDocGiaMuonQuaHan* current = layDanhSachDocGiaMuonQuaHan(root);
    int row = 0;
    while( current != nullptr) {
        string hovaten = current->value.first->thong_tin.Ho + " " + current->value.first->thong_tin.Ten;
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(current->value.first->thong_tin.MATHE)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(hovaten)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(current->value.first->thong_tin.phai == Nam ? "Nam" : "Nữ"));
        tableWidget->setItem(row, 3, new QTableWidgetItem(current->value.first->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Khóa"));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(current->value.second->data.masach)));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(ChuyenMaSachThanhTenSach(current->value.second->data.masach))));
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(SoNgayQuaHan(current->value.second->data.NgayMuon, NgayHomNay()))));
        current = current->next;
        row++;
    }
    tableWidget->resizeColumnsToContents();

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


