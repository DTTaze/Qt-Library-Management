#ifndef MUON_TRA_H
#define MUON_TRA_H
#include <ctime>
#include "ngay.h"
#include "dau_sach.h"
#include "queue.h"
struct The_Doc_Gia;
struct Danh_Sach_The_Doc_Gia;
using namespace std;
enum DenSach {daden, chuaden};

const int Chua_Tra = 0;
const int Da_Tra = 1;
const int Mat_Sach = 2;
int TrangThai(Date ngay_muon, Date ngay_tra) ;

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
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

bool TrangThaiMUONTRADaTraChua(DanhSachMUONTRA *temp);

//----------------------------------------------------------------Hàm liên quan mượn sách-----------------------------------------------------------------------------------------------
void ThemSachVaoLichSuMuonSach(DanhSachMUONTRA * &head, string ma,int trangthai, const Date &ngayMuon, const Date &ngayTra);

void MuonSach(const int &maThe, const string& maSach);

int DemSoSachDangMuon(DanhSachMUONTRA *demsach);

bool MuonSachQuaHan(DanhSachMUONTRA *head);

bool KiemTraVaInRaLoiKhiMuonSach(string maSach, DanhMucSach* danhmucsach, Danh_Sach_The_Doc_Gia *doc_gia);

//----------------------------------------------------------------Hàm liên quan trả sách-----------------------------------------------------------------------------------------------
void TraSach(const unsigned int& ma_the, const string& ma_sach);
//----------------------------------------------------------------Bảng top 10 sách được mượn nhiều nhất--------------------------------------------------------------------------------
void MergeSachMuon(SachMuon* arr, int left, int mid, int right) ;

void MergeSortSachMuon(SachMuon* arr, int left, int right);

void CapNhatSoLuotMuonTuDanhSachLichSuMuonTra(int &SoLuongSach, SachMuon DanhSachSachMuon [], DanhSachMUONTRA *danh_sach_muon_tra);

void Top10QuyenSachNhieuLuotMuonNhat(int &SoLuongSach, SachMuon DanhSachSachMuon[], DanhSachMUONTRA * danh_sach_muon_tra, QTableView *tableView) ;

int TimViTriMaSachTrongDanhSachSachMuon(int &SoLuongSach, SachMuon DanhSachSachMuon[], string maSach);

void CapNhatSoLuotMuon (int &SoLuongSach, string ma_sach, SachMuon DanhSachSachMuon[]) ;

void DatLaiSoLuotMuon(int &SoLuongSach, SachMuon DanhSachSachMuon[]);

void NhapThongTinVaoTop10(int &SoLuongSach, SachMuon DanhSachSachMuon[], QTableView *tableView, Danh_Sach_The_Doc_Gia *root);
//----------------------------------------------------------------Bảng danh sách độc giả mượn quá hạn--------------------------------------------------------------------------------------------------

void chenCoThuTuVaoDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan*& head, danhSachDocGiaMuonQuaHan* current);

void DuyetCayDeLayDocGiaQuaHan(danhSachDocGiaMuonQuaHan*& head, Danh_Sach_The_Doc_Gia* p) ;

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan (Danh_Sach_The_Doc_Gia* root);

void GiaiPhongDanhSachDocGiaMuonQuaHan(danhSachDocGiaMuonQuaHan* head);

void inDanhSachDocGiaMuonQuaHan(QTableView *tableView, Danh_Sach_The_Doc_Gia *root) ;

//-----------------------------------------------------------------Mất Sách-----------------------------------------------

void ChuaDenSach(int mathe, string masach);

void DaDenSach(int mathe, string masach);
#endif
