#ifndef NGAY_H
#define NGAY_H

#include <iostream>
#include <ctime>
#include <string>
#include <QDebug>

using namespace std;

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
    bool operator==(const Date& other) const {
        return (day == other.day && month == other.month && year == other.year);
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator<(const Date& other) const {
        if (year < other.year) return true;
        if (year > other.year) return false;
        if (month < other.month) return true;
        if (month > other.month) return false;
        return day < other.day;
    }

    bool operator>(const Date& other) const {
        return other < *this;
    }

    bool operator<=(const Date& other) const {
        return !(*this > other);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }
};

bool laNamNhuan(int year);

int ngayTrongThang(int month, int year);

bool KiemTraNgayThangNam(Date NgayThangNam);

Date NgayMuon() ;

Date NgayHomNay() ;

int DemSoNgay(Date ngay_muon, Date ngay_tra) ;

int SoNgayQuaHan(Date ngay_muon, Date ngay_tra);

string ChuyenDateSangString(Date Ngay);

Date ChuyenStringSangDate(string nhap_ngaythangnam);

#endif
