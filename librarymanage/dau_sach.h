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
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidget>
#include <QStringListModel>
#include <QDir>
#include <QDebug>
#include <QCheckBox>
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
    int demsosach =0;
    string theloai;
    DanhMucSach* dms = nullptr;
    DauSach(){}
    DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai) {
    }
};


struct DanhSachDauSach{
    int demsach= 0;
    DauSach* node[MAXSACH] ;
    DanhSachDauSach(){}
};


extern DanhSachDauSach danh_sach_dau_sach;


//Hàm in danh sách đầu sách mặc định
void InFull(DanhSachDauSach &danh_sach_dau_sach, int so_luong_sach, QTableView* tableView_dausach,QStandardItemModel*& model);

//Hàm tìm kiếm vị trí của mã isbn trong danh sách
int TimKiemIndexDauSach(string ma_isbn);

//Hàm xác định mã sách có tồn tại trong đầu sách
bool TonTaiMaSachDS(string ma_sach);

//Hàm chuyển từ mã sách thành tên sách
string ChuyenMaSachThanhTenSach(DanhSachDauSach &danh_sach_dau_sach,const string&  ma_sach);

//Hàm kiểm tra sách đã đầy
bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach);

void ChuyenVeChuThuong(std::string& str);

//Hàm cập nhật trạng thái của sách
void CapNhatTrangThaiSach(string ma_sach,int trang_thai);

//Hàm đọc và ghi file txt
void DocTuFile(DanhSachDauSach &danh_sach_dau_sach,QWidget* parent);
void InVaoTXT();

//Chức năng thêm sách
void TaoMaSach(string& ma_sach,int demsosach);
void ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai, const string& vi_tri, const string &I_S_B_N,int demsosach,string ma_sach);
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                 int trang_thai,string &vi_tri,string ma_sach);

//Chức năng in đầu sách theo thể loại
void SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc, int* copy);
void Merge(int* arr, int left, int mid, int right,DanhSachDauSach &Dau_sach_goc);
void MergeSort(int* arr, int left, int right,DanhSachDauSach &Dau_sach_goc);
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach,QTableView* tableView_intheloai);


//Chức năng tìm tên sách
void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,QStandardItemModel*& model,string key);
void InFullTheoTenSach(string key, QTableView* tableView_dausach,QStandardItemModel*& model);
void ChenMaSachVaoTable(const string& ma_ISBN ,int cur_row, QTableView* tableView_dausach,QStandardItemModel*& model,string key);

#endif
