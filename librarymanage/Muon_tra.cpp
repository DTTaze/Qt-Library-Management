#include "Muon_tra.h"
#include "The_doc_gia.h"
using namespace std;

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, 
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

int TrangThai(Date ngay_muon, Date ngay_tra) { // trạng thái sách của độc giả 
    int songay = DemSoNgay(ngay_muon, ngay_tra);
    if(songay != -1) {
        if(ngay_tra.day == 0) {return 0;} // chưa trả
        else if(songay<=7) {
            return 1; // đã trả
        }
        else {
            return 2; // mất sách
        }
    } else {cout<<"nhap sai! vui long nhap lai."<<endl;return -1;}
}


int DemSoSachDangMuon(DanhSachMUONTRA *demsach) {
    DanhSachMUONTRA *temp = demsach;
    int dem = 0;
    
    while(temp!=nullptr) {
        if(temp->data.trangthai == 0 || temp->data.trangthai == 2) {
        temp = temp->next;
        dem++;
        }
    }
    return dem;
}

void ThemSach (DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA data(ma, ngayMuon, ngayTra);
    DanhSachMUONTRA * newMUONTRA = new DanhSachMUONTRA(data);
    if (head == nullptr)
    {
        head = newMUONTRA;
    }
    else {
        DanhSachMUONTRA * temp = head;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
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

void InManHinhDSSachDangMuon(Danh_Sach_The_Doc_Gia *head) {
    Danh_Sach_The_Doc_Gia *doc_gia = head;
    DanhSachMUONTRA *danh_sach = doc_gia->thong_tin.head_lsms;
    while(danh_sach != nullptr) {
        cout<<" "<<endl;
    }
}

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

void ThemSachVaoLSMS(DanhSachMUONTRA * &sach, string ma, const Date &ngayMuon, const Date &ngayTra) {
    MUONTRA thongtinmuontra (ma, ngayMuon, ngayTra);
    DanhSachMUONTRA * newLichSu = new DanhSachMUONTRA( thongtinmuontra);
    if (sach == nullptr)
    {
        sach = newLichSu;
    }
    else {
        DanhSachMUONTRA* temp = sach;
        while(temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newLichSu;
    }
}

void MuonSach (Danh_Sach_The_Doc_Gia *doc_gia) {
    Danh_Sach_The_Doc_Gia *tmp = doc_gia;
    DanhSachMUONTRA *lichsu = tmp->thong_tin.head_lsms;
    
    int sosach = DemSoSachDangMuon(lichsu);
    if(doc_gia->thong_tin.TrangThai == Khoa || lichsu->data.trangthai == 2 || sosach>3) {
        cout<<"khong the muon sach"<<endl;
        return;
    } else {
        int luachon = 0; // 1: muon sach    2: thoat ra
        while (sosach <= 3 || luachon == 2) {
            cout<<"nhap lua chon: "; cin>>luachon;
            string ma; 
            cout<<"nhap ma: ";
            getline(cin, ma);
            Date ngaymuon = NgayMuon();
            Date ngaytra = NgayTraThucTe();
            ThemSach(lichsu, ma, ngaymuon, ngaytra);
            ThemSachVaoLSMS(lichsu, ma, ngaymuon, ngaytra);
        }
    }
}


void TraSach (Danh_Sach_The_Doc_Gia *doc_gia, string ma_sach) {
    Danh_Sach_The_Doc_Gia *temp = doc_gia;
    
    while (temp->thong_tin.head_lsms != nullptr) {
        if(temp->thong_tin.head_lsms->data.masach == ma_sach) {
            temp->thong_tin.head_lsms->data.NgayTra = NgayTraThucTe();
            cout<<"da tra sach thanh cong"<<endl;
            return;
        }else {

        }
    }
    cout<<"khong co thong tin ve sach doc gia muon" << endl;
}

// void DanhSachSachDocGiaMuon(Danh_Sach_The_Doc_Gia *doc_gia) {
//     cout<<"ten doc gia: " << doc_gia->thong_tin.Ho << " " << doc_gia->thong_tin.Ten << endl;
//     InManHinhDSSach(doc_gia);
// }

// void DocFile(const string &tenFile, DocGiaMuonSach *&doc_gia) {
//     ifstream file("Danh_sach_dau_sach.txt");
//     if (!file.is_open()) {
//         cout << "Không thể mở file." << endl;
//         return;
//     }

//     string line;
//     while (getline(file, line)) {
//         size_t pos = 0;

//         auto nextToken = [&](char delimiter) {
//             size_t newPos = line.find(delimiter, pos);
//             string token = line.substr(pos, newPos - pos);
//             pos = newPos + 1;
//             return token;
//         };

//         string isbn = nextToken('|');
//         string tensach = nextToken('|');
//         int sotrang = stoi(nextToken('|'));
//         string tacgia = nextToken('|');
//         int namsx = stoi(nextToken('|'));
//         string theloai = nextToken('|');
//         nextToken('|'); // Skip one field
//         string masach = nextToken('|');
//         string nguoiMuon = nextToken('|');

//         Date ngaymuon;
//         string ngayMuonStr = nextToken('|');
//         sscanf(ngayMuonStr.c_str(), "%d/%d/%d", &ngaymuon.day, &ngaymuon.month, &ngaymuon.year);

//         Date ngaytra;
//         string ngayTraStr = nextToken('|');
//         if (!ngayTraStr.empty()) {
//             sscanf(ngayTraStr.c_str(), "%d/%d/%d", &ngaytra.day, &ngaytra.month, &ngaytra.year);
//         } else {
//             ngaytra = {0, 0, 0}; // If no return date is provided
//         }

//         int trangthai = stoi(nextToken('|'));

//         // Add the book to the borrow list
//         ThemSach(doc_gia->danhsachmuontra, masach, tensach, ngaymuon, ngaytra);
//     }

//     file.close();
// }
