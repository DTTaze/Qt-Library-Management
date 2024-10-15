#ifndef NGAY_H
#define NGAY_H

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
};

bool operator == (const Date &d1, const Date &d2);

bool laNamNhuan(int year);

bool KiemTraNgayThangNam(Date NgayThangNam);

bool isNumber(const string &str);

void NhapNgayThangNam(Date &nhap_ngay_thang_nam);


void NgayTraDuKien(Date Ngay_muon);

Date NgayMuon() ;

Date NgayTraThucTe();

int DemSoNgay(Date ngay_muon, Date ngay_tra) ;

void InManHinhNgayThangNam(Date ngay_thang_nam);

#endif
