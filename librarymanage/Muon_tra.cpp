#include "Muon_tra.h"
#include "The_doc_gia.h"
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

void ThemSach (DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) {
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

bool Empty(DanhSachMUONTRA * First)
{   return(First == NULL);
}

int XoaSachDauTien (DanhSachMUONTRA *&First)
{ DanhSachMUONTRA * p;
    if (Empty(First))      return 0;
    p = First;    // nut can xoa la nut dau
    First = p->next;
    delete p;
    return 1;
}

int XoaSachSauSachP(DanhSachMUONTRA * p)
{   DanhSachMUONTRA * q;
    // nếu p là NULL hoặc sau p không có nút
    if((p == NULL) || (p->next == NULL))
        return 0;
    q = p->next;  // q chi nut can xoa
    p->next = q->next;
    delete q;
    return 1;
}

int XoaSachTheoThongTin(DanhSachMUONTRA * &head, string ma) {
    DanhSachMUONTRA * p=head;
    if (head == NULL ) return 0;
    if (head->data.masach == ma ) {
        XoaSachDauTien(head); return 1;
    }

    while (p->next != nullptr) {
        if (p->next->data.masach == ma) {
            XoaSachSauSachP(p);
            return 1;
        }
        p = p->next;
    }

    return 0;
}

// void InManHinhDSSach(Danh_Sach_The_Doc_Gia * head) {
//     Danh_Sach_The_Doc_Gia * doc_gia = head;
//     DanhSachMUONTRA *tmp = doc_gia->thong_tin.head_lsms;
//     while(tmp != nullptr) {
//         cout << tmp->data.masach <<endl;
//         InManHinhNgayThangNam(tmp->data.NgayMuon);
//         InManHinhNgayThangNam(tmp->data.NgayTra);
//         if(tmp->data.trangthai == 0) {
//             cout<< "0" << endl;
//         } else if(tmp->data.trangthai == 1) {
//             cout<< "1" << endl;
//         } else {
//             DenSach densach;
//             if(densach == daden) {
//                 doc_gia->thong_tin.TrangThai = Dang_Hoat_Dong;
//                 tmp->data.trangthai = 1;
//                 cout<< "1" << endl;
//             }
//             else {
//                 doc_gia->thong_tin.TrangThai = Khoa;
//                 cout<< "2" << endl;
//             }
//         }
//         tmp = tmp->next;
//     }
// }


// void LuuNgayMuon(const string& fileName, const Date& ngay_muon) {
//     ofstream file(fileName);
//     if (file.is_open()) {
//         file << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year;
//         file.close();
//         cout << "Ngay muon sach da duoc luu: " << ngay_muon.day << "/" << ngay_muon.month << "/" << ngay_muon.year << endl;
//     } else {
//         cout << "Khong the mo file de ghi." << endl;
//     }
// }


void MuonSach (const int& ma_the) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, ma_the);
    DanhSachMUONTRA *lichsu = doc_gia->thong_tin.head_lsms;

    int sosach = DemSoSachDangMuon(lichsu);
    if(doc_gia->thong_tin.TrangThai == Khoa || lichsu->data.trangthai == 2 || sosach>=3) {
        cout<<"khong the muon sach"<<endl;
        return;
    } else {
        int luachon = 0; // 1: muon sach    2: thoat ra
        while (sosach < 3 || luachon == 1) {
            cout<<"nhap lua chon: "; cin>>luachon;
            string ma;
            cout<<"nhap ma: ";
            getline(cin, ma);
            Date ngaymuon = NgayMuon();
            Date ngaytra ;
            ThemSach(lichsu, ma, ngaymuon, ngaytra);
            ThemSach(danh_sach_muon_tra, ma, ngaymuon, ngaytra);
            sosach++;
            CapNhatSoLuotMuon(ma);
            // ThemSachVaoLSMS(lichsu, ma, ngaymuon, ngaytra);
        }
    }
    delete lichsu;
    delete doc_gia;
}


void TraSach (const unsigned int& ma_the, string ma_sach) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, ma_the);
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;
    string ten_sach = ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach );
        if(doc_gia == nullptr || ten_sach == "") {return;}
    for (int i =0; danh_sach_dau_sach.node[i] != nullptr; i++ ) {
        if(current->data.masach == ma_sach) {
            current->data.NgayTra = NgayTraThucTe();
            danh_sach_dau_sach.node[i] = 0;
            current->data.trangthai = 1;
            return;
        }
        current  = current->next;
    }
}

void DanhSachSachDocGiaMuon(const unsigned int & ma_the, QTableWidget* tableWidget) {
    Danh_Sach_The_Doc_Gia *doc_gia = Tim_Kiem(root, ma_the);
    DanhSachMUONTRA *current = doc_gia->thong_tin.head_lsms;
    while(current != nullptr) {
        ChuyenMaSachThanhTenSach(danh_sach_dau_sach, current->data.masach );
        current = current->next;
        // tableWidget-
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

void Them_lich_su_sach(Danh_Sach_The_Doc_Gia* the_doc_gia, DanhSachMUONTRA *&danh_sach_lich_su_muon_tra, string ma_sach, string ngay_muon, string ngay_tra) {
    // Chuyển chuỗi sang Date
    Date ngaymuon = NhapChuoiNgayThangNam(ngay_muon);
    Date ngaytra = NhapChuoiNgayThangNam(ngay_tra);

    // Tính số ngày quá hạn
    int songayquahan = SoNgayQuaHan(ngaymuon, ngaytra);

    // Tạo một node MUONTRA mới
    MUONTRA muontra(ma_sach, ngaymuon, ngaytra);

    // Nếu danh sách mượn trả của độc giả rỗng, khởi tạo danh sách mới
    if (the_doc_gia->thong_tin.head_lsms == nullptr) {
        the_doc_gia->thong_tin.head_lsms = new DanhSachMUONTRA(muontra);
    } else {
        // Duyệt đến cuối danh sách và thêm phần tử mới
        DanhSachMUONTRA *current = the_doc_gia->thong_tin.head_lsms;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new DanhSachMUONTRA(muontra);
    }

    // Nếu sách đã quá hạn, sao chép danh sách mượn trả
    if (songayquahan > 0) {
        danh_sach_lich_su_muon_tra = CopyDanhSachMUONTRA(the_doc_gia->thong_tin.head_lsms);
        KiemTraVaChenDocGiaQuaHan(danh_sach_lich_su_muon_tra, the_doc_gia);
    }
}

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

void Top10QuyenSachNhieuLuotMuonNhat() {
    for(int i =1; i<SoLuongSach; i++) {
        for(int j = i+1; j<=SoLuongSach; j++) {
            if(DanhSachSachMuon[i].demsoluotmuon > DanhSachSachMuon[j].demsoluotmuon) {
                swap(DanhSachSachMuon[i], DanhSachSachMuon[j]);
            }
        }
    }

    for(int i = 1; i<=10; i++) {
        string ten_sach = ChuyenMaSachThanhTenSach(danh_sach_dau_sach, DanhSachSachMuon[i].masach );
        cout << ten_sach << endl;
    }

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


DanhSachMUONTRA *DanhSachQuaHan () {
    DanhSachMUONTRA *danhsachquahan = nullptr;
    DanhSachMUONTRA *head = danh_sach_muon_tra;
    if (head == nullptr) return nullptr;
    while (head != nullptr) {
        if(head->data.NgayTra.day == 0 ) {
            int songayquahan = SoNgayQuaHan(head->data.NgayMuon, NgayHomNay());
            if(songayquahan > 0) {
                DanhSachMUONTRA *node = new DanhSachMUONTRA;
                node->data = head->data;
                node->next = danhsachquahan;
                danhsachquahan = node;
                }
            }
        head = head->next;
        }
    SapXepTheoThoiGianQuaHan(danhsachquahan);
    return danhsachquahan;
}

string TimKiemTenDocGia (Danh_Sach_The_Doc_Gia *root, string ma_sach)
{
    Danh_Sach_The_Doc_Gia* p;   p = root;
    while (p != NULL && p->thong_tin.head_lsms->data.masach != ma_sach)
        if(ma_sach < p->thong_tin.head_lsms->data.masach)
            p = p->ptr_left;
        else
            p = p->ptr_right;
    string ho_va_ten = p->thong_tin.Ho + " " + p->thong_tin.Ten;

    return ho_va_ten;
}

void InDocGiaQuaHan(Danh_Sach_The_Doc_Gia * root) {
    DanhSachMUONTRA *head = DanhSachQuaHan();
    while(head != nullptr) {
        string HoVaTen = TimKiemTenDocGia(root, head->data.masach);
        int so_ngay_qua_han = SoNgayQuaHan(head->data.NgayMuon, NgayHomNay());
        cout<<HoVaTen << so_ngay_qua_han <<endl;
        head = head->next;
    }
}


