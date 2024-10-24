#ifndef DAUSACH_H
#define DAUSACH_H
#define MAXSACH 10000

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QDebug>
using namespace std;


struct DanhMucSach{
    string masach;
    int trangthai;
    string vitri;
    DanhMucSach* next= nullptr;
    DanhMucSach(const string &ma_sach, int trang_thai, const string &vi_tri)
        : masach(ma_sach), trangthai(trang_thai), vitri(vi_tri) {}
    DanhMucSach() : masach(""), trangthai(0), vitri("") {}
};

struct DauSach {
    string ISBN;
    string tensach;
    int sotrang;
    string tacgia;
    int namsx;
    string theloai;
    DanhMucSach* dms = nullptr;
    DauSach(){}
    DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai, DanhMucSach* ptr_dms)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai), dms(ptr_dms) {}
};


struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH] ;
    DanhSachDauSach(){}
};


extern DanhSachDauSach danh_sach_dau_sach;
extern DanhMucSach* danh_muc_sach;

void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);

void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                 DanhMucSach* &head_dms, int trang_thai,string &vi_tri);

void SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc, int* copy);

void InFull(DanhSachDauSach &danh_sach_dau_sach, int so_luong_sach, QTableView* tableView_dausach);

void InFullTheoTenSach(string key, QTableView* tableView_dausach);

int TimKiemNhiPhanTenSach(DanhSachDauSach &danh_sach_dau_sach,string key);

int TimKiemNhiPhanTheLoai(DanhSachDauSach &danh_sach_dau_sach,string key);

string ChuyenMaSachThanhTenSach(DanhSachDauSach &danh_sach_dau_sach,const string&  ma_sach);

void Merge(int* arr, int left, int mid, int right,DanhSachDauSach &Dau_sach_goc);

void MergeSort(int* arr, int left, int right,DanhSachDauSach &Dau_sach_goc);

void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach,QTableView* tableView_intheloai);

void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,string key);

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach);

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach,DanhMucSach* &head_dms,string I_S_B_N, string ten_sach,int so_trang,string tac_gia,int nam_sx,string the_loai,string vi_tri);

void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms,QTableView *tableView_dausach,QWidget* parent);

bool InVaoTXT();

void CapNhatTrangThaiSach(string ma_sach,int trang_thai);

#endif
