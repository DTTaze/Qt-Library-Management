#include "Muon_tra.h"
using namespace std;
DanhSachMUONTRA* danh_sach_muon_tra;
SachMuon DanhSachSachMuon[MAXSACH];
int SoLuongSach = 0;
/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn,
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

int TrangThai(Date ngay_muon, Date ngay_tra) { // trạng thái sách của độc giả
    if(ngay_tra.day == 0) {return 0;} // chưa trả
    else if(ngay_tra.day >0 ) {
        return 1; // đã trả
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


int DemSoSachDangMuon(DanhSachMUONTRA *demsach) {
    DanhSachMUONTRA *temp = demsach;
    int dem = 0;

    while(temp!=nullptr) {
        if(temp->data.trangthai == 0) {
            temp = temp->next;
            dem++;
        }
    }
    return dem;
}

void ThemSach (DanhSachMUONTRA*& head, string ma, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA data(ma, ngayMuon, ngayTra);
    DanhSachMUONTRA *newMUONTRA = new DanhSachMUONTRA(data);

    if (head == nullptr || ma < head->data.masach) {
        newMUONTRA->next = head;
        head = newMUONTRA;
    } else {
        DanhSachMUONTRA *temp = head;
        while (temp->next != nullptr && temp->next->data.masach < ma) {
            temp = temp->next;
        }
        newMUONTRA->next = temp->next;
        temp->next = newMUONTRA;
    }
}

void MuonSach(const int& maThe, const string& maSach) {
    // Tìm kiếm thẻ độc giả theo mã
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, maThe);

    // Kiểm tra nếu thẻ độc giả không tồn tại
    if (doc_gia == nullptr) {
        QMessageBox::warning(nullptr, "Lỗi", "Thẻ độc giả không tồn tại.");
        return;
    }

    // Đếm số sách đang mượn
    int sosach = DemSoSachDangMuon(doc_gia->thong_tin.head_lsms);

    // Kiểm tra trạng thái thẻ và số sách đang mượn
    if (doc_gia->thong_tin.TrangThai == Khoa || sosach >= 3) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể cho độc giả mượn sách vì thẻ độc giả đã bị khóa hoặc đã mượn nhiều hơn 3 quyển.");
        return;
    }

    // Nhập ngày mượn
    Date ngaymuon = NgayMuon();
    // Kiểm tra tính hợp lệ của ngày mượn
    if (ngaymuon.day == 0 || ngaymuon.month == 0 || ngaymuon.year == 0) {
        QMessageBox::warning(nullptr, "Lỗi", "Ngày mượn không hợp lệ.");
        return;
    }

    // Nhập ngày trả (có thể thêm logic ở đây để tự động tính toán ngày trả)
    Date ngaytra;
    ngaytra.day = ngaymuon.day + 14; // Giả sử cho mượn trong 14 ngày
    ngaytra.month = ngaymuon.month;
    ngaytra.year = ngaymuon.year;

    // Thêm sách vào lịch sử mượn
    ThemSach(doc_gia->thong_tin.head_lsms, maSach, ngaymuon, ngaytra);
    ThemSach(danh_sach_muon_tra, maSach, ngaymuon, ngaytra);
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
            current->data.trangthai = 1;
            string ten_sach = ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach);
            if (!ten_sach.empty()) {
                string ma_ISBN = ma_sach.substr(0,17);
                int i = 0;
                for (; i < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->ISBN != ma_ISBN;i++);
                danh_sach_dau_sach.node[i]->dms->trangthai = 0;
                qDebug()<<danh_sach_dau_sach.node[i]->dms->masach;
            }

            break;
        }
        current = current->next;
    }
    QMessageBox::information(nullptr, "Thông báo", "Trả sách thành công.");
}


void DanhSachSachDocGiaMuon(const unsigned int & ma_the, QTableWidget* tableWidget) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, ma_the);
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;
    while(current != nullptr) {
        ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach );
        current = current->next;
    }
}

DanhSachMUONTRA* CopyDanhSachMUONTRA(DanhSachMUONTRA *danh_sach_goc) {
    if(danh_sach_goc == nullptr) return nullptr;

    DanhSachMUONTRA *copy = new DanhSachMUONTRA(danh_sach_goc->data);
    DanhSachMUONTRA *temp = danh_sach_goc->next;
    DanhSachMUONTRA *head_copy = copy;

    while(temp != nullptr) {
        head_copy->next = new DanhSachMUONTRA(temp->data);
        head_copy = head_copy->next;
        temp = temp->next;
    }
    return copy;
}



void ChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, Danh_Sach_The_Doc_Gia* docGia, DanhSachMUONTRA* currentMuonTra) {
    // Tính toán số ngày quá hạn từ currentMuonTra thay vì chỉ dùng head_lsms
    int soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, currentMuonTra->data.NgayTra);

    // Tạo node mới với thông tin từ currentMuonTra
    DanhSachMUONTRA* newNode = new DanhSachMUONTRA(*currentMuonTra);

    // Nếu danh sách quá hạn rỗng hoặc so sánh thấy số ngày quá hạn của bản ghi mới lớn hơn, chèn vào đầu danh sách
    if (danh_sach_lich_su_muon_tra == nullptr || SoNgayQuaHan(danh_sach_lich_su_muon_tra->data.NgayMuon, danh_sach_lich_su_muon_tra->data.NgayTra) < soNgayQuaHan) {
        newNode->next = danh_sach_lich_su_muon_tra;
        danh_sach_lich_su_muon_tra = newNode;
        return;
    }

    // Duyệt danh sách quá hạn để tìm vị trí chèn
    DanhSachMUONTRA* current = danh_sach_lich_su_muon_tra;
    while (current->next != nullptr && SoNgayQuaHan(current->data.NgayMuon, current->data.NgayTra) > soNgayQuaHan) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}



void KiemTraVaChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, Danh_Sach_The_Doc_Gia* docGia) {
    DanhSachMUONTRA* currentMuonTra = docGia->thong_tin.head_lsms;

    // Duyệt qua danh sách mượn trả của độc giả
    while (currentMuonTra != nullptr) {
        int soNgayQuaHan = 0;

        if (currentMuonTra->data.trangthai == 0) {
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, NgayHomNay());
        }
        else if (currentMuonTra->data.trangthai == 1) {
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, currentMuonTra->data.NgayTra);
        }

        // Nếu số ngày quá hạn > 0, gọi hàm ChenDocGiaQuaHan với currentMuonTra hiện tại
        if (soNgayQuaHan > 0) {
            ChenDocGiaQuaHan(danh_sach_lich_su_muon_tra, docGia, currentMuonTra);
        }

        currentMuonTra = currentMuonTra->next;
    }
}


// int DemDocGiaQuaHan(DocGiaQuaHan *head) {
//     DocGiaQuaHan *temp = head;
//     int count = 0;
//     while(temp != nullptr) {
//         temp = temp->next;
//         count ++;
//     }
//     return count;
// }
// void Them_Vao_QTableWidget(QTableWidget* tableWidget, const The_Doc_Gia& docGia) { // Hàm thêm nút thông tin vào table
//     int row = tableWidget->rowCount();
//     tableWidget->insertRow(row);

//     // Thêm dữ liệu vào từng ô
//     tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(docGia.Ho))); // Họ
//     tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(docGia.Ten))); // Tên
//     tableWidget->setItem(row, 2, new QTableWidgetItem(docGia.phai == Nam ? "Nam" : "Nữ")); // Phái
//     tableWidget->setItem(row, 3, new QTableWidgetItem(docGia.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Không Hoạt Động")); // Trạng thái
// }



void Them_Vao_QTableWidget_danhsachmuontra(QTableWidget* tableWidget, const The_Doc_Gia& docGia, DanhSachMUONTRA *&danh_sach_lich_su_muon_tra) {
    DanhSachMUONTRA* currentMuonTra = danh_sach_lich_su_muon_tra;

    // Duyệt qua từng bản ghi trong danh sách mượn trả của độc giả
    while (currentMuonTra != nullptr) {
        int row = tableWidget->rowCount(); // Lấy số dòng hiện có trong bảng
        tableWidget->insertRow(row); // Thêm một dòng mới
        string ngaymuon = ChuyenDateSangString(currentMuonTra->data.NgayMuon);
        string ngaytra = (currentMuonTra->data.trangthai == 1) ? ChuyenDateSangString(currentMuonTra->data.NgayTra) : "Chưa trả";

        // Thêm thông tin mã thẻ, họ, tên và phái của độc giả vào các ô tương ứng
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(docGia.MATHE))); // Mã thẻ
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(docGia.Ho))); // Họ
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(docGia.Ten))); // Tên
        tableWidget->setItem(row, 3, new QTableWidgetItem(docGia.phai == Nam ? "Nam" : "Nữ")); // Phái

        // Thêm thông tin mượn trả vào các ô tương ứng
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(currentMuonTra->data.masach))); // Mã sách
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(ngaymuon))); // Ngày mượn
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(ngaytra))); // Ngày trả

        // Tính số ngày quá hạn
        int soNgayQuaHan = 0;
        if (currentMuonTra->data.trangthai == 0) {
            // Nếu sách chưa được trả, tính số ngày quá hạn so với ngày hiện tại
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, NgayHomNay());
        } else if (currentMuonTra->data.trangthai == 1) {
            // Nếu sách đã trả, tính số ngày quá hạn so với ngày trả
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, currentMuonTra->data.NgayTra);
        }
        tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(soNgayQuaHan))); // Số ngày quá hạn

        // Chuyển sang bản ghi mượn trả tiếp theo
        currentMuonTra = currentMuonTra->next;
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
    qDebug()<<"bat dau sao chep\n";
    int n = SoLuongSach;
    for (int i = 0; i < n;i++){
        copy[i]=i;
    }
    qDebug()<<"ket thuc\n\n";
}

void CapNhatTuDanhSachMUONTRA () {
    DanhSachMUONTRA *head = danh_sach_muon_tra;
    while(head!=nullptr) {
        CapNhatSoLuotMuon(head->data.masach);
        head = head->next;
    }
}

void Top10QuyenSachNhieuLuotMuonNhat(QTableView* tableView) {
    CapNhatTuDanhSachMUONTRA();
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
/*------------------------------------------------------------------------------------------------------------*/

void SapXepTheoThoiGianQuaHan(DanhSachMUONTRA *&head)
{
    DanhSachMUONTRA *p;
    DanhSachMUONTRA *q;
    DanhSachMUONTRA *pmin;

    for (p = head; p != NULL; p = p->next)
    {
        int min = SoNgayQuaHan(p->data.NgayMuon, NgayHomNay());
        pmin = p;

        for(q = p->next; q != NULL; q = q->next)
        {
            if (SoNgayQuaHan(q->data.NgayMuon, NgayHomNay()) < min)
            {
                min = SoNgayQuaHan(q->data.NgayMuon, NgayHomNay());
                pmin = q;
            }
        }

        if (pmin != p)
        {
            MUONTRA temp = p->data;
            p->data = pmin->data;
            pmin->data = temp;
        }
    }
}

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
                if ( current->data.trangthai == 1 ) {
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


void inDanhSachDocGiaMuonQuaHan(QTableView *tableView) {
    danhSachDocGiaMuonQuaHan* current = layDanhSachDocGiaMuonQuaHan(root);
    QStandardItemModel* model = new QStandardItemModel();
    int i = 0;
    while( current != nullptr) {
        int so_ngay_qua_han = SoNgayQuaHan(current->value.second->data.NgayMuon, current->value.second->data.NgayTra);
        if ( so_ngay_qua_han <= 7) {
            current = current->next;
            continue;
        }

            model->insertRow(i);
            model->setItem(i, 0, new QStandardItem(QString::number(current->value.first->thong_tin.MATHE)));
            model->setItem(i, 1, new QStandardItem(QString::fromStdString(current->value.first->thong_tin.Ho)));
            model->setItem(i, 2, new QStandardItem(QString::fromStdString(current->value.first->thong_tin.Ten)));
            model->setItem(i, 3, new QStandardItem(current->value.first->thong_tin.phai == Nam ? "Nam" : "Nữ"));
            model->setItem(i, 4, new QStandardItem(current->value.first->thong_tin.TrangThai == Dang_Hoat_Dong ? "Đang Hoạt Động" : "Khóa"));
            model->setItem(i, 5, new QStandardItem(QString::number(so_ngay_qua_han)));
            current = current->next;
            i++;
    }
    tableView->setModel(model);
}


