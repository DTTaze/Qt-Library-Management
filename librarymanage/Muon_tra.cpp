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

void DanhSachSachDocGiaMuon(Danh_Sach_The_Doc_Gia *doc_gia) {
    cout<<"ten doc gia: " << doc_gia->thong_tin.Ho << " " << doc_gia->thong_tin.Ten << endl;
    InManHinhDSSachDangMuon(doc_gia);
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



void ChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, The_Doc_Gia* docGia, DanhSachMUONTRA* currentMuonTra) {
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



void KiemTraVaChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, The_Doc_Gia* docGia) {
    DanhSachMUONTRA* currentMuonTra = docGia->head_lsms;

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

void Them_lich_su_sach(The_Doc_Gia *the_doc_gia, DanhSachMUONTRA *&danh_sach_lich_su_muon_tra, string ma_sach, string ngay_muon, string ngay_tra) {
    // Chuyển chuỗi sang Date
    Date ngaymuon = NhapChuoiNgayThangNam(ngay_muon);
    Date ngaytra = NhapChuoiNgayThangNam(ngay_tra);

    // Tính số ngày quá hạn
    int songayquahan = SoNgayQuaHan(ngaymuon, ngaytra);

    // Tạo một node MUONTRA mới
    MUONTRA muontra(ma_sach, ngaymuon, ngaytra);

    // Nếu danh sách mượn trả của độc giả rỗng, khởi tạo danh sách mới
    if (the_doc_gia->head_lsms == nullptr) {
        the_doc_gia->head_lsms = new DanhSachMUONTRA(muontra);
    } else {
        // Duyệt đến cuối danh sách và thêm phần tử mới
        DanhSachMUONTRA *current = the_doc_gia->head_lsms;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new DanhSachMUONTRA(muontra);
    }

    // Nếu sách đã quá hạn, sao chép danh sách mượn trả
    if (songayquahan > 0) {
        danh_sach_lich_su_muon_tra = CopyDanhSachMUONTRA(the_doc_gia->head_lsms);
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

void Them_Cay_Vao_QTableWidget_danhsachquahan(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root, DanhSachMUONTRA *danh_sach_lich_su_muon_tra) {
    if (root == nullptr) return; // Nếu cây rỗng, thoát hàm

    // Đệ quy duyệt cây con trái trước
    Them_Cay_Vao_QTableWidget_danhsachquahan(tableWidget, root->ptr_left, danh_sach_lich_su_muon_tra);

    // Lấy thông tin của độc giả hiện tại
    The_Doc_Gia docGiaHienTai = root->thong_tin;

    // Kiểm tra danh sách mượn trả của độc giả hiện tại xem có quá hạn không
    DanhSachMUONTRA* currentMuonTra = docGiaHienTai.head_lsms;
    bool co_qua_han = false;

    while (currentMuonTra != nullptr) {
        int soNgayQuaHan = 0;

        // Nếu sách chưa trả, kiểm tra số ngày quá hạn so với ngày hiện tại
        if (currentMuonTra->data.trangthai == 0) {
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, NgayHomNay());
        } else if (currentMuonTra->data.trangthai == 1) {
            // Nếu sách đã trả, kiểm tra số ngày quá hạn so với ngày trả
            soNgayQuaHan = SoNgayQuaHan(currentMuonTra->data.NgayMuon, currentMuonTra->data.NgayTra);
        }

        // Nếu có ngày quá hạn (số ngày quá hạn lớn hơn 0), gán cờ `co_qua_han` thành true
        if (soNgayQuaHan > 0) {
            co_qua_han = true;
            break; // Không cần kiểm tra thêm, chỉ cần biết có quá hạn
        }

        currentMuonTra = currentMuonTra->next; // Duyệt sang bản ghi mượn trả tiếp theo
    }

    // Nếu có sách quá hạn, thêm thông tin độc giả vào bảng
    if (co_qua_han) {
        Them_Vao_QTableWidget_danhsachmuontra(tableWidget, docGiaHienTai, docGiaHienTai.head_lsms);
    }

    // Đệ quy duyệt cây con phải
    Them_Cay_Vao_QTableWidget_danhsachquahan(tableWidget, root->ptr_right, danh_sach_lich_su_muon_tra);
}




// void DocFileDocGiaQuaHan(DocGiaQuaHan *danhsachquahan, QTableView* tableView_danhsachquahan, QWidget* parent) {
//     ifstream file("docgia_100.txt");
//     if (!file.is_open()) {
//         QMessageBox::warning(parent, "Lỗi", "Không thể đọc file docgia_100.txt");
//         return;
//     }
//     std::string line;

//     while (std::getline(file, line)) {
//         std::string ten, ho, masach;
//         Phai phai;
//         Date ngaymuon, ngaytra;
//         int songayquahan;
//         // Tach thong tin tung dong
//         size_t pos = 0;

//         pos = line.find('|');
//         line.erase(0, pos + 1);

//         // Chỉnh sửa để phù hợp với định dạng file
//         pos = line.find('|');
//         ho = line.substr(0, pos); line.erase(0, pos + 1);

//         pos = line.find('|');
//         ten = line.substr(0, pos); line.erase(0, pos + 1);

//         pos = line.find('|');
//         std::string strPhai = line.substr(0, pos);
//         if (strPhai == "Nam") {
//             phai = Nam;
//         } else if (strPhai == "Nữ") {
//             phai = Nu;
//         }
//         line.erase(0, pos + 1);

//         pos = line.find('|');
//         masach = line.substr(0, pos); line.erase(0, pos + 1);

//         // Tách ngày mượn (dd/mm/yyyy)
//         pos = line.find('/');
//         std::string dayStr = line.substr(0, pos);
//         line.erase(0, pos + 1);


//         if (!dayStr.empty() && std::all_of(dayStr.begin(), dayStr.end(), ::isdigit)) {
//             ngaymuon.day = stoi(dayStr);  // Chuyển đổi chuỗi thành số nguyên
//         } else {
//             // Xử lý lỗi, ví dụ bỏ qua dòng này hoặc báo lỗi

//             continue;
//         }

//         pos = line.find('/');
//         std::string monthStr = line.substr(0, pos);
//         line.erase(0, pos + 1);

//         if (!monthStr.empty() && std::all_of(monthStr.begin(), monthStr.end(), ::isdigit)) {
//             ngaymuon.month = stoi(monthStr);  // Chuyển đổi chuỗi thành số nguyên
//         } else {
//             // Xử lý lỗi
//             continue;
//         }

//         pos = line.find('|');
//         std::string yearStr = line.substr(0, pos);
//         line.erase(0, pos + 1);

//         if (!yearStr.empty() && std::all_of(yearStr.begin(), yearStr.end(), ::isdigit)) {
//             ngaymuon.year = stoi(yearStr);  // Chuyển đổi chuỗi thành số nguyên
//         } else {
//             // Xử lý lỗi
//             continue;
//         }

//         qDebug()<<"ngay muon :" <<ngaymuon.day<< "|" <<ngaymuon.month<<"|"<<ngaymuon.year;

//         if (line[0] == '|') {
//             // Nếu ký tự đầu tiên là '|', thì không có ngày trả
//             line.erase(0, 1); // Bỏ ký tự '|'
//             ngaytra.day = 0; // Khởi tạo ngày trả
//             ngaytra.month = 0;
//             ngaytra.year = 0;
//         } else {
//             // Ngày trả (dd/mm/yyyy)

//             pos = line.find('/');
//             std::string dayStr = line.substr(0, pos);
//             line.erase(0, pos + 1);

//             if (!dayStr.empty() && std::all_of(dayStr.begin(), dayStr.end(), ::isdigit)) {
//                 ngaytra.day = stoi(dayStr);  // Chuyển đổi chuỗi thành số nguyên
//             } else {
//                 // Xử lý lỗi, ví dụ bỏ qua dòng này hoặc báo lỗi
//                 continue;
//             }

//             pos = line.find('/');
//             std::string monthStr = line.substr(0, pos);
//             line.erase(0, pos + 1);

//             if (!monthStr.empty() && std::all_of(monthStr.begin(), monthStr.end(), ::isdigit)) {
//                 ngaytra.month = stoi(monthStr);  // Chuyển đổi chuỗi thành số nguyên
//             } else {
//                 // Xử lý lỗi
//                 continue;
//             }
//             pos = line.find('/');
//             if (!line.empty()) {
//                 ngaytra.year = stoi(line.substr(0, pos));  // Tách và lưu năm của ngày trả
//             } else {
//                 ngaytra.year = 0;  // Nếu không có năm trả, gán mặc định là 0 hoặc xử lý khác
//             }

//         }
//         qDebug()<<"ngay tra : "<<ngaytra.day<< "|" <<ngaytra.month<<"|"<<ngaytra.year<<"\n\n";

//         // pos = line.find(' ');
//         // songayquahan = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

//         if (ten.empty() || ho.empty() || masach.empty()) {
//             qDebug()<<"bo qua";
//             continue;
//         }
//         ThemSach();
//     }

//     file.close();

//     const int row_count = DemDocGiaQuaHan(danhsachquahan);
//     qDebug()<<row_count ;
//     // Tạo model cho table
//     QStandardItemModel* model = new QStandardItemModel(row_count, 7);

//     QString headers[7] = {
//         "Họ",
//         "Tên",
//         "Phái",
//         "Mã Sách",
//         "Ngày Mượn",
//         "Ngày Trả",
//         "Số Ngày Quá Hạn"
//     };

//     for (int i = 0; i < 7; i++) {
//         model->setHeaderData(i, Qt::Horizontal, headers[i]);
//     }

//     for (int i = 0; i < row_count; i++) {
//         DanhSachMUONTRA *danhsachmuontra = danhsachquahan->docGia->thong_tin.head_lsms;
//         danhsachquahan->soNgayQuaHan = SoNgayQuaHan(danhsachmuontra->data.NgayMuon, danhsachmuontra->data.NgayTra);
//         model->setItem(i, 0, new QStandardItem(QString::fromStdString(danhsachquahan->docGia->thong_tin.Ho)));
//         model->setItem(i, 1, new QStandardItem(QString::fromStdString(danhsachquahan->docGia->thong_tin.Ten)));

//         QString phaiString = (danhsachquahan->docGia->thong_tin.phai == Nam) ? "Nam" : "Nữ";
//         model->setItem(i, 2, new QStandardItem(phaiString));

//         model->setItem(i, 3, new QStandardItem(QString::fromStdString(danhsachmuontra->data.masach)));
//         QString ngayMuonString = QString::asprintf("%02d/%02d/%04d", danhsachmuontra->data.NgayMuon.day, danhsachmuontra->data.NgayMuon.month, danhsachmuontra->data.NgayMuon.year);
//         model->setItem(i, 4, new QStandardItem(ngayMuonString));

//         QString ngayTraString = (danhsachmuontra->data.NgayTra.day == 0) ? "Chưa trả" : QString::asprintf("%02d/%02d/%04d", danhsachmuontra->data.NgayTra.day, danhsachmuontra->data.NgayTra.month, danhsachmuontra->data.NgayTra.year);
//         model->setItem(i, 5, new QStandardItem(ngayTraString));

//         model->setItem(i, 6, new QStandardItem(QString::number(danhsachquahan->soNgayQuaHan)));
//         danhsachquahan = danhsachquahan->next;
//     }

//     // Gán model vào QTableView
//     tableView_danhsachquahan->setModel(model);
//     tableView_danhsachquahan->setColumnWidth(0,120);
//     tableView_danhsachquahan->setColumnWidth(1,120);
//     tableView_danhsachquahan->setColumnWidth(2,50);
//     tableView_danhsachquahan->setColumnWidth(3,200);
//     tableView_danhsachquahan->setColumnWidth(4,100);
//     tableView_danhsachquahan->setColumnWidth(5,100);
//     tableView_danhsachquahan->setColumnWidth(6,30);
// }


