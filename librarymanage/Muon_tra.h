#ifndef MUON_TRA_H
#define MUON_TRA_H
#include <iostream>
#include <ctime>
#include <fstream>
#include "ngay.h"
#include "dau_sach.h"
#include "queue.h"
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidget>
#include <QTableView>
#include <QStringListModel>
#include <QLineEdit>
struct The_Doc_Gia;
struct Danh_Sach_The_Doc_Gia;
using namespace std;
enum DenSach {daden, chuaden};

/*f. Mượn sách : nhập vào mã thẻ độc giả, chương trình sẽ liệt kê các sách mà độc giả đang mượn. Mỗi độc giả chỉ được mượn tối đa 3 cuốn,
không cho mượn khi giữ 1 sách quá hạn (7 ngày)
g. Trả sách
h. Liệt kê danh sách các mã sách, tên sách mà 1 độc giả có số thẻ X đang mượn
i. In danh sách độc giả mượn sách quá hạn theo thứ tự thời gian quá hạn giảm dần
j. In 10 sách có số lượt mượn nhiều nhất.*/

const int Chua_Tra = 0;
const int Da_Tra = 1;
const int Mat_Sach = 2;

int TrangThai(Date ngay_muon, Date ngay_tra);

struct MUONTRA { // thong tin quyen sach doc gia da va dang muon
    string masach;
    Date NgayMuon;
    Date NgayTra;
    int trangthai;

    MUONTRA() : masach(""), NgayMuon(), NgayTra(), trangthai(0) {}

    MUONTRA(string ma, const Date &ngayMuon, const Date &ngayTra) : masach(ma), NgayMuon(ngayMuon), NgayTra(ngayTra)
    { trangthai = TrangThai(NgayMuon, NgayTra);}

    void setNgayTra(const Date &ngayTra) {
        NgayTra = ngayTra;
        trangthai = TrangThai(NgayMuon, NgayTra);
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

struct danhSachDocGiaMuonQuaHan {
    pair<Danh_Sach_The_Doc_Gia*, DanhSachMUONTRA*> value;
    danhSachDocGiaMuonQuaHan* next = nullptr;
};


extern SachMuon DanhSachSachMuon[MAXSACH];

extern int SoLuongSach; //*

void ThemSach(DanhSachMUONTRA * &head, string ma, const Date &ngayMuon, const Date &ngayTra);
//----------------------------------------------------------------Hàm liên quan mượn sách-----------------------------------------------------------------------------------------------
void MuonSach(const int &maThe, const string& maSach);

int DemSoSachDangMuon(DanhSachMUONTRA *demsach);
//----------------------------------------------------------------Hàm liên quan trả sách-----------------------------------------------------------------------------------------------
void TraSach(const unsigned int& ma_the, const string& ma_sach);
//----------------------------------------------------------------Bảng top 10 sách được mượn nhiều nhất--------------------------------------------------------------------------------
void MergeSachMuon(int* arr, int left, int mid, int right) ;

void MergeSortSachMuon(int* arr, int left, int right);

void SaoChepDanhSachSachMuon( int* copy);

void CapNhatTuDanhSachMUONTRA (DanhSachMUONTRA *danh_sach_muon_tra);

void Top10QuyenSachNhieuLuotMuonNhat(DanhSachMUONTRA * danh_sach_muon_tra, QTableView* tableView) ;

int TimViTriMaSach(string maSach);

void CapNhatSoLuotMuon (string ma_sach) ;

void DatLaiSoLuotMuon();

void NhapThongTinVaoTop10(QTableView *tableView, Danh_Sach_The_Doc_Gia * root);
//----------------------------------------------------------------Bảng độc giả quá hạn--------------------------------------------------------------------------------------------------

void InsertOder(danhSachDocGiaMuonQuaHan*& head, danhSachDocGiaMuonQuaHan* current);

danhSachDocGiaMuonQuaHan* layDanhSachDocGiaMuonQuaHan (Danh_Sach_The_Doc_Gia* root);

void inDanhSachDocGiaMuonQuaHan(QTableView *tableView, Danh_Sach_The_Doc_Gia *root) ;

#endif
