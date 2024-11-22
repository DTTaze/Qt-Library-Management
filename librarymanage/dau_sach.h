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
    int SoLuongDanhMucSachTrongDausach = 0;
    string theloai;
    DanhMucSach* dms = nullptr;
    DauSach(){}
    DauSach(const DauSach& ds)
        : ISBN(ds.ISBN), tensach(ds.tensach), sotrang(ds.sotrang), tacgia(ds.tacgia),
        namsx(ds.namsx), SoLuongDanhMucSachTrongDausach(ds.SoLuongDanhMucSachTrongDausach),
        theloai(ds.theloai) {
        if (ds.dms != nullptr) {
            dms = new DanhMucSach(*ds.dms); // Sao chép DanhMucSach nếu cần
        }
    }
};


struct DanhSachDauSach{
    int soluongdausach= 0;
    DauSach* node[MAXSACH] ;
    DanhSachDauSach(){}
};


extern DanhSachDauSach danh_sach_dau_sach;

QString RemoveSpace(const QString &key);
QString CapitalizeWords(const QString& text);
void LocKiTuISBNHopLe(const QString& text,QString& LocKiTu);
bool MaISBNQTHopLe(QString i_s_b_n);
void LocKiTuTensachHopLe(const QString& text,string& valid_key);
bool DayDauSach();
bool TonTaiMaSachDaDuocMuonTrongDauSach(int index);
bool TonTaiMaSach(string ma_sach);

void InToanBoDauSach(QTableWidget* tableWidget_dausach);
string ChuyenVeChuThuong(string str);
void InTheoTenTimKiem(string key, QTableWidget* tableWidget_dausach);
void TimKiemTenSach(QTableWidget* tableWidget_dausach, string key);
void SaoChepDanhSach( int* copy);
void Merge(int* arr, int left, int mid, int right);
void MergeSort(int* arr, int left, int right);
void InTheoTungTheLoai(QTableView* tableView_intheloai);

void ChuyenThanhISBN(string& ma);
int TimKiemViTriDauSach(string ma);
bool TonTaiDauSach(int index);
string ChuyenMaSachThanhTenSach(const string&  ma_sach);
void ThemDauSach(DauSach& ds,int trang_thai,string vi_tri,string ma_sach);
void TaoMaSach(string& ma_sach,DauSach* ds);
void ThemDanhMucSach(DauSach*& ds, int trang_thai, const string& vi_tri,string ma_sach);
void NhapDauSach(int index_isbn,int trang_thai,string vi_tri,string ma_sach);
void ThemHoacNhapDauSach(DauSach ds,int trang_thai,string vi_tri,string ma_sach);

int SoSanhTiengViet(const QString& str1, const QString& str2);
void XacDinhViTriThem(const string &ten_sach,int &vi_tri_them);
void DoiViTriDauSachThem(int vi_tri_them);
void DoiViTriDauSachXoa(int index);
void ChenDauSachTheoThuTu(DauSach*& Dau_Sach_moi,string ten_sach,int &vi_tri_them);
void ChenDauSachSauKhiThayDoi(string ten_sach,int &index_hien_tai);
void XoaDauSach(int index);

DanhMucSach* TimDiaChiSachTrongDanhMucSach(string ma_sach);
void CapNhatTrangThaiSach(string ma_sach,int trang_thai);

void DocTuFileDauSach(QWidget* parent);
void GhiDauSachVaoFile();

#endif
