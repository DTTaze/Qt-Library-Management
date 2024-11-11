#include "Muon_tra.h"
using namespace std;

SachMuon DanhSachSachMuon[MAXSACH]; // Chuyển thành cục bộ ( đang chuyển đến hàm đặt lại số lượt mượn)
int SoLuongSach = 0;

int TrangThai(Date ngay_muon, Date ngay_tra) {
    return ngay_tra.day == 0 ? Chua_Tra : Da_Tra;
}

int TimViTriMaSachTrongDanhSachSachMuon( string maSach) {
    string ma_ISBN = maSach.substr(0, 17);
    for (int i = 0; i < SoLuongSach; i++) {
        if (DanhSachSachMuon[i].masach == ma_ISBN) {
            return i;
        }
    }
    return -1;
}

void CapNhatSoLuotMuon ( string ma_sach) {
    int vitri = TimViTriMaSachTrongDanhSachSachMuon(ma_sach) ;
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
        if(temp->data.trangthai == 0 || temp->data.trangthai == 2) {
            dem++;
        }
        temp = temp->next;
    }
    return dem;
}

void DatLaiSoLuotMuon() {
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

bool CoTheMuonSach(DanhMucSach* danhmucsach, Danh_Sach_The_Doc_Gia *doc_gia) {
    int SoSachDangMuon = DemSoSachDangMuon(doc_gia->thong_tin.head_lsms);

    DanhMucSach* cur = danhmucsach;
    if (doc_gia->thong_tin.TrangThai == Khoa || SoSachDangMuon >= 3
        || MuonSachQuaHan(doc_gia->thong_tin.head_lsms)
        || cur->trangthai != 0 ) { // Chỉnh sửa lại int theo tên hằng
        return false;
    }
    return true;
}

void MuonSach( const int& maThe, const string& maSach) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, maThe);
    Date ngaymuon = NgayHomNay();

    Date ngaytra; // ngaytra = {0/0/0}

    if (doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    DanhMucSach *cur = TimDiaChiSachTrongDanhMucSach(maSach);

    if ( !CoTheMuonSach(cur, doc_gia) ) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể cho độc giả mượn sách.");
        return;
    }

    ThemSachVaoLichSuMuonSach(doc_gia->thong_tin.head_lsms, maSach,Chua_Tra, ngaymuon, ngaytra);
    CapNhatTrangThaiSach(maSach, da_duoc_muon); // Chỉnh sửa lại int theo tên hằng
    CapNhatSoLuotMuon(maSach);

    QMessageBox::information(nullptr, "Thông báo", "Mượn sách thành công.");
}



void TraSach(const unsigned int& ma_the, const string& ma_sach) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, ma_the);

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

                CapNhatTrangThaiSach(ma_sach, co_the_muon); // Cập nhật theo tên hằng
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

void CapNhatSoLuotMuonTuDanhSachLichSuMuonTra (DanhSachMUONTRA *danh_sach_muon_tra) {
    DanhSachMUONTRA *current = danh_sach_muon_tra;
    while( current != nullptr ) {
        CapNhatSoLuotMuon(current->data.masach);
        current = current->next;
    }
}

void Top10QuyenSachNhieuLuotMuonNhat(DanhSachMUONTRA * danh_sach_muon_tra, QTableView* tableView) {

    CapNhatSoLuotMuonTuDanhSachLichSuMuonTra(danh_sach_muon_tra);
    MergeSortSachMuon(DanhSachSachMuon, 0, SoLuongSach-1);
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, "Tên sách"); // Tiêu đề cột 1
    model->setHeaderData(1, Qt::Horizontal, "Số lượt mượn"); // Tiêu đề cột 2


    for (int i = 0; i < SoLuongSach && i<10; i++) {
        model->insertRow(i);
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, DanhSachSachMuon[i].masach)))); // Họ
        model->setItem(i, 1, new QStandardItem(QString::number(DanhSachSachMuon[i].demsoluotmuon))); // Mã thẻ

    }
    tableView->setModel(model);
    tableView->setColumnWidth(0, 300);

}


void NhapThongTinVaoTop10(QTableView *tableView, Danh_Sach_The_Doc_Gia *root) {
    if (root == nullptr) return;
    NhapThongTinVaoTop10(tableView, root->ptr_left);
    Top10QuyenSachNhieuLuotMuonNhat(root->thong_tin.head_lsms, tableView);
    NhapThongTinVaoTop10(tableView, root->ptr_right);
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

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan (Danh_Sach_The_Doc_Gia* root) { // Chuyển thành đệ quy
    Queue<Danh_Sach_The_Doc_Gia*> q;
    danhSachDocGiaMuonQuaHan* head = nullptr;
    if ( root == nullptr ) {
        return head;
    }
    q.push(root);
    while ( !q.empty() ) {
        Danh_Sach_The_Doc_Gia* p = q.front();
        q.pop();

        if(p->thong_tin.head_lsms != nullptr) {
            DanhSachMUONTRA* current = p->thong_tin.head_lsms;
            while ( current != nullptr ) {

                if ( current->data.trangthai == 0 && SoNgayQuaHan(current->data.NgayMuon, current->data.NgayTra) > 0) {
                    danhSachDocGiaMuonQuaHan* n = new danhSachDocGiaMuonQuaHan;
                    n->value.first = p;
                    n->value.second = current;
                    InsertOder(head, n);
                    break;
                }
                current = current->next;
            }
        }

        if ( p->ptr_left != nullptr ) {
            q.push(p->ptr_left);
        }
        if ( p->ptr_right != nullptr ) {
            q.push(p->ptr_right);
        }
    }
    return head;
}


void inDanhSachDocGiaMuonQuaHan(QTableView *tableView, Danh_Sach_The_Doc_Gia *root) {
    danhSachDocGiaMuonQuaHan* current = layDanhSachDocGiaMuonQuaHan(root);
    QStandardItemModel* model = new QStandardItemModel();
    int row = 0;
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "Mã Thẻ");
    model->setHeaderData(1, Qt::Horizontal, "Họ Và Tên");
    model->setHeaderData(2, Qt::Horizontal, "Giới Tính");
    model->setHeaderData(3, Qt::Horizontal, "Trạng Thái");
    model->setHeaderData(4, Qt::Horizontal, "Ngày Quá Hạn");
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
        model->setItem(row, 4, new QStandardItem(QString::number(so_ngay_qua_han)));
        current = current->next;
        row++;
    }


    tableView->setModel(model);
    tableView->resizeColumnsToContents();

}

void ChuaDenSach(int mathe, string masach) {
    Danh_Sach_The_Doc_Gia *p = Tim_Kiem(root, mathe);
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
    Danh_Sach_The_Doc_Gia *p = Tim_Kiem(root, mathe);
    p->thong_tin.TrangThai = Dang_Hoat_Dong;
    DanhSachMUONTRA *sach_mat = p->thong_tin.head_lsms;
    while(sach_mat != nullptr) {
        if(sach_mat->data.masach == masach && sach_mat->data.trangthai != Da_Tra) {
            sach_mat->data.trangthai = Da_Tra;
            CapNhatTrangThaiSach(masach, co_the_muon); // Điều chỉnh lại theo hằng
            break;
        }
        sach_mat = sach_mat->next;
    }
}


