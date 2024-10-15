#ifndef DAUSACH_H
#define DAUSACH_H
#define MAXSACH 10000

#include <QObject>
#include <QString>
#include <QTextEdit>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <QMessageBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QStandardPaths>

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
    DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai, DanhMucSach* ptr_dms)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai), dms(ptr_dms) {}
};

struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH];
    int demsachvitri[10]={0};
};

void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);
DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri);
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                 DanhMucSach* &head_dms, int trang_thai,string &vi_tri);
DanhSachDauSach SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc);
int TimKiemNhiPhanTenSach(DanhSachDauSach &danh_sach_dau_sach,string key);
int TimKiemNhiPhanTheLoai(DanhSachDauSach &danh_sach_dau_sach,string key);
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach,QTableView* tableView_intheloai);
void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,string key);
bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach,DanhMucSach* &head_dms,string vi_tri);
void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach,
                    DanhMucSach* &head_dms);//can sua doi de phu hop voi qt
void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms,QTableView *tableView_dausach,QWidget* parent);




#endif
