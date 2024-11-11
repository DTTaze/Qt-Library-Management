#ifndef THE_DOC_GIA_H
#define THE_DOC_GIA_H
#include "Dau_sach.h"
#include "Muon_tra.h"
#define SOLUONGMATHETOIDA 10000

using namespace std;

struct DanhSachMUONTRA;

enum Phai{Nam,Nu};

enum TrangThaiCuaThe{Dang_Hoat_Dong,Khoa};


struct The_Doc_Gia {
    unsigned int MATHE;
    string Ho;
    string Ten;
    TrangThaiCuaThe TrangThai;
    Phai phai;
    DanhSachMUONTRA* head_lsms = nullptr;
};


struct Danh_Sach_The_Doc_Gia {
    The_Doc_Gia thong_tin;
    Danh_Sach_The_Doc_Gia* ptr_left = nullptr;
    Danh_Sach_The_Doc_Gia* ptr_right = nullptr;
    Danh_Sach_The_Doc_Gia(){}
    Danh_Sach_The_Doc_Gia(const The_Doc_Gia& thong_tin_the_doc_gia)
    {
        thong_tin.MATHE = thong_tin_the_doc_gia.MATHE;
        thong_tin.Ho = thong_tin_the_doc_gia.Ho;
        thong_tin.Ten = thong_tin_the_doc_gia.Ten;
        thong_tin.TrangThai = thong_tin_the_doc_gia.TrangThai;
        thong_tin.phai = thong_tin_the_doc_gia.phai;
        thong_tin.head_lsms = thong_tin_the_doc_gia.head_lsms;
    }
};

struct Danh_Sach_Theo_Ten
{
    string ten;
    Danh_Sach_The_Doc_Gia* PTR = nullptr;
    Danh_Sach_Theo_Ten* next = nullptr;
};

extern Danh_Sach_The_Doc_Gia* root;

// Mảng thẻ
void taoDanhSachMaThe(int start, int end);
int layMaThe();
void docFileMaThe();
void ghiMaTheVaoFile();

// thêm / xóa / hiệu chỉnh thông tin thẻ độc giả.
void Them_Doc_Gia(Danh_Sach_The_Doc_Gia* &root, const The_Doc_Gia& thong_tin_the_doc_gia);
void Xoa_Truong_Hop_Co_Hai_Cay_Con(Danh_Sach_The_Doc_Gia*& r);
void Xoa_Doc_Gia(Danh_Sach_The_Doc_Gia* &r, const int& ma_the_doc_gia);
Danh_Sach_The_Doc_Gia* Tim_Kiem(Danh_Sach_The_Doc_Gia* root, const int& mathe);
void Cap_Nhat_Thong_Tin_Doc_Gia(int maThe, const string& field, const string& newValue);
void capNhatTrangThaiThe(Danh_Sach_The_Doc_Gia* docGia);

// In danh sách độc giả theo tên
void themVaoCoThuTuDanhSachTheDocGiaTheoTen(Danh_Sach_The_Doc_Gia* docgia);
void taoDanhSachTheoTen(Danh_Sach_The_Doc_Gia* root);
void xoaDanhSachTheoTen();
void inDanhSachTheDocGiaTheoTen(QTableWidget* tableWidget);

// Hàm đọc và ghi thông tin
void docFileThongTinTheDocGia(QTableWidget* tableWidget);
void ghiThongTinTheDocGia();

// Hàm chèn thông tin vào table
void themTheDocGiaVaoBang(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* docGia);
void inDanhSachTheDocGiaTheoMaSo(QTableWidget* tableWidget, Danh_Sach_The_Doc_Gia* root );
#endif
