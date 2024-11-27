#ifndef MUON_TRA_H
#define MUON_TRA_H
#include <ctime>
#include "ngay.h"
#include "dau_sach.h"
#include "queue.h"
struct The_Doc_Gia;
struct Danh_Sach_The_Doc_Gia;
using namespace std;

const int Chua_Tra = 0;
const int Da_Tra = 1;
const int Mat_Sach = 2;
int TrangThai(Date ngay_muon, Date ngay_tra) ;

struct MUONTRA {
    string masach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai;

    MUONTRA() : masach(""), NgayMuon(), NgayTra(), trangthai(0) {}

    MUONTRA(string ma, const Date &ngayMuon, const Date &ngayTra, int trangthai) : masach(ma), NgayMuon(ngayMuon), NgayTra(ngayTra), trangthai(trangthai)
    {}

    void capNhatTrangThaiMuonTra(const Date &ngayTra) {
        NgayTra = ngayTra;
        trangthai = TrangThai(NgayMuon, NgayTra);
    }
};

struct DanhSachMUONTRA {
    MUONTRA data;
    DanhSachMUONTRA *next = nullptr;
    DanhSachMUONTRA(const MUONTRA &muontra) : data(muontra), next(nullptr) {}
    DanhSachMUONTRA(){}
};

struct SachMuon {
    string masach;
    int demsoluotmuon = 0;
};

struct danhSachDocGiaMuonQuaHan {
    pair<Danh_Sach_The_Doc_Gia*, DanhSachMUONTRA*> value;
    danhSachDocGiaMuonQuaHan* next = nullptr;
};


//----------------------------------------------------------------Hàm liên quan mượn sách-----------------------------------------------------------------------------------------------

void ThemSachVaoLichSuMuonSach(DanhSachMUONTRA * &head, string ma,int trangthai, const Date &ngayMuon, const Date &ngayTra);

bool chuaTraSach(DanhSachMUONTRA *temp);

int DemSoSachDangMuon(DanhSachMUONTRA *demsach);

bool CoSachMuonQuaHan(DanhSachMUONTRA *head);

bool DocGiaDangMuonSachNay(Danh_Sach_The_Doc_Gia *doc_gia, string maSach) ;

bool SachDaDuocMuonHoacThanhLy(string ma_sach) ;

bool KiemTraVaInRaLoiKhiMuonSach(int maThe, string maSach);

void MuonSach(const int &maThe, const string& maSach);
//----------------------------------------------------------------Hàm liên quan trả sách-----------------------------------------------------------------------------------------------
void TraSach(const unsigned int& ma_the, const string& ma_sach);
//-----------------------------------------------------------------Mất Sách--------------------------------------------------------------
void ChuaDenSach(int mathe, string masach);

void DaDenSach(int mathe, string masach);

bool SachChuaTra(DanhSachMUONTRA *sach_mat, string masach);

bool SachChuaTraHoacMatSach(DanhSachMUONTRA *sach_mat, string masach);
//----------------------------------------------------------------Bảng top 10 sách được mượn nhiều nhất--------------------------------------------------------------------------------
void Top10QuyenSachNhieuLuotMuonNhat(int &SoLuongSach, SachMuon DanhSachSachMuon[], QTableWidget *tableWidget) ;

void MergeSachMuon(SachMuon* arr, int left, int mid, int right) ;

void MergeSortSachMuon(SachMuon* arr, int left, int right);

void CapNhatSoLuotMuon (int &SoLuongSach, string ma_sach, SachMuon DanhSachSachMuon[]) ;

void CapNhatSoLuotMuonTuDanhSachLichSuMuonTra(int &SoLuongSach, SachMuon DanhSachSachMuon [], DanhSachMUONTRA *danh_sach_muon_tra);

int TimViTriMaSachTrongDanhSachSachMuon(int &SoLuongSach, SachMuon DanhSachSachMuon[], string maSach);

void NhapThongTinVaoTop10(int &SoLuongSach, SachMuon DanhSachSachMuon[], Danh_Sach_The_Doc_Gia *root);
//----------------------------------------------------------------Bảng danh sách độc giả mượn quá hạn--------------------------------------------------------------------------------------------------
void inDanhSachDocGiaMuonQuaHan(QTableWidget *tableWidget, Danh_Sach_The_Doc_Gia *root) ;

void chenCoThuTuVaoDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan*& head, danhSachDocGiaMuonQuaHan* current);

void DuyetCayDeLayDocGiaQuaHan(danhSachDocGiaMuonQuaHan*& head, Danh_Sach_The_Doc_Gia* p) ;

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan (Danh_Sach_The_Doc_Gia* root);

void GiaiPhongDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan* head);
#endif
