#ifndef MUON_TRA_H
#define MUON_TRA_H
#include <iostream>
#include <ctime>
#include <fstream>
#include "ngay.h"
#include "dau_sach.h"
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidget>
struct The_Doc_Gia;
struct Danh_Sach_The_Doc_Gia;
using namespace std;

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn, 
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách 
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

int TrangThai(Date ngay_muon, Date ngay_tra) ;

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
    string masach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai;

    MUONTRA() : masach(""), NgayMuon(), NgayTra(), trangthai(0) {}

    MUONTRA(string ma, const Date &ngayMuon, const Date &ngayTra) : masach(ma), NgayMuon(ngayMuon), NgayTra(ngayTra)
    { trangthai = TrangThai(NgayMuon, NgayTra);}

    bool operator==(const MUONTRA &other) const {
        return masach == other.masach &&
               NgayMuon == other.NgayMuon &&
               NgayTra == other.NgayTra;
    }
};

struct DanhSachMUONTRA { // danh sach cac quyen sach da hoac dang muon
    MUONTRA data;
    DanhSachMUONTRA *next = nullptr;
    DanhSachMUONTRA(const MUONTRA &muontra) : data(muontra), next(nullptr) {}
    DanhSachMUONTRA(){}
};

struct SachMuon {
    string masach;
    int demsoluotmuon = 0;
};

extern SachMuon DanhSachSachMuon[MAXSACH];

extern int SoLuongSach;

extern DanhSachMUONTRA* danh_sach_muon_tra;

int TimViTriMaSach(string maSach);

void CapNhatSoLuotMuon (string ma_sach) ;

int DemSoSachDangMuon(DanhSachMUONTRA *demsach) ;

void ThemSach (DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) ;

bool Empty(DanhSachMUONTRA * First);

int XoaSachDauTien (DanhSachMUONTRA *&First);


int XoaSachSauSachP(DanhSachMUONTRA * p);

int XoaSachTheoThongTin(DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra) ;

// void InManHinhDSSach(Danh_Sach_The_Doc_Gia * head) ;

void InManHinhDSSachDangMuon(Danh_Sach_The_Doc_Gia *head);

void ThemSachVaoLSMS(DanhSachMUONTRA * &sach, string ma, const Date &ngayMuon, const Date &ngayTra) ;

void MuonSach (Danh_Sach_The_Doc_Gia *doc_gia) ;

void TraSach (Danh_Sach_The_Doc_Gia doc_gia, string ma_sach) ;

void DanhSachSachDocGiaMuon(Danh_Sach_The_Doc_Gia doc_gia) ;

void ChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, The_Doc_Gia* docGia, DanhSachMUONTRA* currentMuonTra);

void KiemTraVaChenDocGiaQuaHan(DanhSachMUONTRA*& danh_sach_lich_su_muon_tra, The_Doc_Gia* docGia) ;

void Them_lich_su_sach(Danh_Sach_The_Doc_Gia* the_doc_gia, DanhSachMUONTRA *&danh_sach_muon_tra, string ma_sach, string ngay_muon, string ngay_tra);

void Them_Vao_QTableWidget_danhsachmuontra(QTableWidget* tableWidget, const The_Doc_Gia& docGia, DanhSachMUONTRA *&danh_sach_lich_su_muon_tra);
void Them_Cay_Vao_QTableWidget_danhsachquahan(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root, DanhSachMUONTRA *danh_sach_lich_su_muon_tra);
void Top10QuyenSachNhieuLuotMuonNhat() ;

void SapXepTheoThoiGianQuaHan(DanhSachMUONTRA *&head);

DanhSachMUONTRA *DanhSachQuaHan ();

string TimKiemTenDocGia (Danh_Sach_The_Doc_Gia *root, string ma_sach);

void InDocGiaQuaHan(Danh_Sach_The_Doc_Gia * root) ;
#endif
