#include "Muon_tra.h"
using namespace std;

SachMuon DanhSachSachMuon[MAXSACH];
int SoLuongSach = 0;
/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn,
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

int TrangThai(Date ngay_muon, Date ngay_tra) { // trạng thái sách của độc giả

    if(ngay_tra.day == 0)
    {
        return Chua_Tra;
    }
    else
    {
        return Da_Tra;
    }
}

int TimViTriMaSach(string maSach) {
    for (int i = 0; i < SoLuongSach; i++) {
        if (DanhSachSachMuon[i].masach == maSach) {
            return i;
        }
    }
    return -1; // Không tìm thấy
}

void CapNhatSoLuotMuon (string ma_sach) {
    int vitri = TimViTriMaSach(ma_sach) ;
    if(vitri != -1) {
        DanhSachSachMuon[vitri].demsoluotmuon++;
    } else {
        DanhSachSachMuon[SoLuongSach].masach = ma_sach;
        DanhSachSachMuon[SoLuongSach].demsoluotmuon = 1;
        SoLuongSach++;
    }
}

void DatLaiSoLuotMuon() {
    for (int i = 0; i < SoLuongSach; i++) {
        DanhSachSachMuon[i].demsoluotmuon = 0;
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

void ThemSach (DanhSachMUONTRA*& head, string ma,int trangthai, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA data(ma, ngayMuon, ngayTra, trangthai);
    DanhSachMUONTRA* newMUONTRA = new DanhSachMUONTRA(data);

    if (head == nullptr) {
        head = newMUONTRA;
    } else {
        DanhSachMUONTRA* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newMUONTRA;
    }
}

bool SachDaMuon (DanhSachMUONTRA *head, string masach) {
    DanhSachMUONTRA *p = head;
    while(p!=nullptr) {
        if(p->data.masach == masach && p->data.NgayTra.day == 0) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool KiemTraSachCoQuaHanKhong(DanhSachMUONTRA *head) {
    DanhSachMUONTRA *p = head;
    Date ngaytra;
    while(p != nullptr) {
        if(p->data.NgayTra.day == 0 ){
            ngaytra = NgayHomNay();
            if(SoNgayQuaHan(p->data.NgayMuon, ngaytra) > 7) return 1;
        }
        p = p->next;
    }
    return 0;
}

void MuonSach( const int& maThe, const string& maSach) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, maThe);
    string ma_isbn = maSach.substr(0, 17);
    int vitri = TimKiemIndexDauSach(ma_isbn);
    // Nhập ngày mượn
    Date ngaymuon = NgayHomNay();

    // Nhập ngày trả (có thể thêm logic ở đây để tự động tính toán ngày trả)
    Date ngaytra;

    if (doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    int sosach = DemSoSachDangMuon(doc_gia->thong_tin.head_lsms); // Đếm số sách đang mượn
    DanhMucSach* cur = danh_sach_dau_sach.node[vitri]->dms;
    for (; cur!= nullptr; cur = cur->next){
        if(cur->masach == maSach) break;
    }

    // Kiểm tra trạng thái thẻ và số sách đang mượn
    if (maSach == ""||doc_gia->thong_tin.TrangThai == Khoa ||
        sosach >= 3 || SachDaMuon(doc_gia->thong_tin.head_lsms, maSach) ||
        KiemTraSachCoQuaHanKhong(doc_gia->thong_tin.head_lsms) ||
        cur->trangthai == 1 || cur->trangthai == 2) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể cho độc giả mượn sách vì thẻ độc giả đã bị khóa hoặc sách không tồn tại hoặc đã mượn nhiều hơn 3 quyển.");
        return;
    }

    // Thêm sách vào lịch sử mượn
    ThemSach(doc_gia->thong_tin.head_lsms, maSach,0, ngaymuon, ngaytra);
    CapNhatTrangThaiSach(maSach, 1);
    CapNhatSoLuotMuon(maSach); // Cập nhật số lượt mượn cho sách

    // Thông báo thành công
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
        if (current->data.masach == ma_sach && current->data.trangthai == 0) {

                current->data.NgayTra = NgayHomNay();
                current->data.capNhatTrangThaiMuonTra(NgayHomNay());

                CapNhatTrangThaiSach(ma_sach, 0);
                capNhatTrangThaiThe(doc_gia);

                break;
        }
        current = current->next;
    }
}



void MergeSachMuon(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        int Left_soluotmuon = DanhSachSachMuon[L[i]].demsoluotmuon;
        int Right_soluotmuon = DanhSachSachMuon[R[j]].demsoluotmuon;

        if (Left_soluotmuon > Right_soluotmuon) {
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


void MergeSortSachMuon(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;


        MergeSortSachMuon(arr, left, mid);
        MergeSortSachMuon(arr, mid + 1, right);


        MergeSachMuon(arr, left, mid, right);
    }
}

void SaoChepDanhSachSachMuon( int* copy) {
    int n = SoLuongSach;
    for (int i = 0; i < n;i++){
        copy[i]=i;
    }
}

void CapNhatTuDanhSachMUONTRA (DanhSachMUONTRA *danh_sach_muon_tra) {
    DanhSachMUONTRA *head = danh_sach_muon_tra;
    while( head != nullptr ) {
        CapNhatSoLuotMuon(head->data.masach);
        head = head->next;
    }
}

void Top10QuyenSachNhieuLuotMuonNhat(DanhSachMUONTRA * danh_sach_muon_tra, QTableView* tableView) {
    tableView->setModel(nullptr);

    CapNhatTuDanhSachMUONTRA(danh_sach_muon_tra);
    int *copy = new int[SoLuongSach] ();
    SaoChepDanhSachSachMuon(copy);
    MergeSortSachMuon(copy, 0, SoLuongSach-1);
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, "Tên sách"); // Tiêu đề cột 1
    model->setHeaderData(1, Qt::Horizontal, "Số lượt mượn"); // Tiêu đề cột 2


    for (int i = 0; i < SoLuongSach && i<10; i++) {
        model->insertRow(i);
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(ChuyenMaSachThanhTenSach(danh_sach_dau_sach, DanhSachSachMuon[copy[i]].masach)))); // Họ
        model->setItem(i, 1, new QStandardItem(QString::number(DanhSachSachMuon[copy[i]].demsoluotmuon))); // Mã thẻ

    }
    tableView->setModel(model);
    tableView->setColumnWidth(0, 150);

    delete[] copy;
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

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan (Danh_Sach_The_Doc_Gia* root) {
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

                if ( current->data.trangthai == 0) {
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
    tableView->setColumnWidth(0,160);
}

/* viết 2 hàm: hàm thứ nhất là mất sách, khi báo mất sách sẽ hiện thông tin là đền hay chưa, nếu đền rồi thì trạng thái thẻ giữ im
còn trạng thái mượn trả hiện đã trả, trạng thái sách hiện là có thể cho mượn
còn nếu nhấn nút chưa đền thì trạng thái thẻ bị khóa, trạng thái mượn trả chuyển sang mất sách, trạng thái sách vẫn hiện là chưa
mượn được
                hàm thứ 2 là trạng thái mượn trả đang là mất sách, nhất vào nút đền sách thì sẽ đổi trạng thái thẻ sang đang hoạt
động, trạng thái mượn trả là đã trả, trạng thái sách là có thể cho mượn được
*/
void ChuaDenSach(int mathe, string masach) {
    Danh_Sach_The_Doc_Gia *p = Tim_Kiem(root, mathe);
    DanhSachMUONTRA *sach_mat = p->thong_tin.head_lsms;
    while(sach_mat != nullptr) {
        if(sach_mat->data.masach == masach) {
            p->thong_tin.TrangThai = Khoa;
            sach_mat->data.trangthai = 2;
            CapNhatTrangThaiSach(masach, 1);
            break;
        }
        sach_mat = sach_mat->next;
    }

}

void DaDenSach(int mathe, string masach) {
    Danh_Sach_The_Doc_Gia *p = Tim_Kiem(root, mathe);
    DanhSachMUONTRA *sach_mat = p->thong_tin.head_lsms;
    while(sach_mat != nullptr) {
        if(sach_mat->data.masach == masach) {
            p->thong_tin.TrangThai = Dang_Hoat_Dong;
            sach_mat->data.trangthai = 1;
            CapNhatTrangThaiSach(masach, 0);
            break;
        }
        sach_mat = sach_mat->next;
    }
}


