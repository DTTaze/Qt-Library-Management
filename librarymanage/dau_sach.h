#ifndef DAUSACH_H
#define DAUSACH_H
#define MAXSACH 10000

#include <iostream>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

#include <QString>
#include <QTextEdit>
#include <QObject>
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
#include <QHeaderView>
#include <QLocale>
using namespace std;

const int co_the_muon = 0;
const int da_duoc_muon = 1;
const int da_thanh_ly = 2;

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
    int SoLuongSachTrongDausach =0;
    string theloai;
    DanhMucSach* dms = nullptr;
    DauSach(){}
    DauSach(const string& I_S_B_N, const string& ten_sach, int so_trang,const string& tac_gia,int nam_sx, const string& the_loai)
        : ISBN(I_S_B_N), tensach(ten_sach), sotrang(so_trang), tacgia(tac_gia),namsx(nam_sx), theloai(the_loai) {
    }
};


struct DanhSachDauSach{
    int soluongdausach= 0;
    DauSach* node[MAXSACH] ;
    DanhSachDauSach(){}
};


extern DanhSachDauSach danh_sach_dau_sach;

bool TonTaiMaSachDaDuocMuonTrongDauSach(int index);

QString RemoveSpace(const QString &key);

QString CapitalizeWords(const QString& text);

void InToanBoDauSach(QTableWidget* tableWidget_dausach);

int TimKiemViTriDauSach(string ma);

DanhMucSach* TimDiaChiSachTrongDanhMucSach(string ma_sach);

bool TonTaiMaSach(string ma_sach);

DanhMucSach* DanhMucSachTrongDauSach(string ma_sach);

string ChuyenMaSachThanhTenSach(const string&  ma_sach);

bool DayDauSach();

void CapNhatTrangThaiSach(string ma_sach,int trang_thai);

//Hàm đọc và ghi file txt
void DocTuFileDauSach(QWidget* parent);
void GhiDauSachVaoFile();

//Chức năng thêm sách
bool MaISBNQTHopLe(QString i_s_b_n);
void TaoMaSach(string& ma_sach,int SoLuongSachTrongDausach);
void ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai, const string& vi_tri, const string &I_S_B_N,int SoLuongSachTrongDausach,string ma_sach);
void ChenDauSachMoi(DauSach*& Dau_Sach_moi,string& ten_sach);
void ThemDauSach(const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                int trang_thai,string &vi_tri,string ma_sach);

//Chức năng chỉnh sửa đầu sách
void LocKiTuISBNHopLe(const QString& text,QString& LocKiTu);
void LocKiTuTensachHopLe(const QString& text,string& valid_key);

//Chức năng in đầu sách theo thể loại
void SaoChepDanhSach( int* copy);
string ChuyenVeChuThuong(string str);
void Merge(int* arr, int left, int mid, int right);
void MergeSort(int* arr, int left, int right);
void InTheoTungTheLoai(QTableView* tableView_intheloai);


//Chức năng tìm tên sách
void TimKiemTenSach(QTableWidget* tableWidget_dausach, string key);
void InTheoTenTimKiem(string key, QTableWidget* tableWidget_dausach);

#endif
