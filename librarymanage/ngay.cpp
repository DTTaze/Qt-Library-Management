#include "ngay.h"

bool laNamNhuan(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int ngayTrongThang(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && laNamNhuan(year)) {
        return 29;
    }
    return days[month - 1];
}

bool KiemTraNgayThangNam(Date NgayThangNam) {

    if (NgayThangNam.year < 1 || NgayThangNam.month < 1 || (NgayThangNam.month > 12) ||
        NgayThangNam.day < 1 || NgayThangNam.day > ngayTrongThang(NgayThangNam.month, NgayThangNam.year)) {
        return false;
    }
        return true;
}

Date NgayMuon() {
    Date ngay_muon;
    time_t now = time(0);
    tm *ngay_muon_thuc_te = localtime(&now);
    ngay_muon.day = ngay_muon_thuc_te->tm_mday;
    ngay_muon.month = ngay_muon_thuc_te->tm_mon + 1;
    ngay_muon.year = ngay_muon_thuc_te->tm_year + 1900;
    return ngay_muon;
}

Date NgayHomNay() {
    Date ngayhomnay;
    time_t now = time(0);
    tm *Ngay_thuc_te = localtime(&now);
    ngayhomnay.day = Ngay_thuc_te->tm_mday;
    ngayhomnay.month = Ngay_thuc_te->tm_mon + 1;
    ngayhomnay.year = Ngay_thuc_te->tm_year + 1900;
    return ngayhomnay;
}

int DemSoNgay(Date ngay_muon, Date ngay_tra) {
    if(ngay_tra.day == 0) ngay_tra = NgayHomNay();
    int days1 = 0, days2 = 0;
    for (int y = 1; y < ngay_muon.year; y++) {
        days1 += laNamNhuan(y) ? 366 : 365;
    }
    for (int m = 1; m < ngay_muon.month; m++) {
        days1 += ngayTrongThang(m, ngay_muon.year);
    }
    days1 += ngay_muon.day;

    for (int y = 1; y < ngay_tra.year; y++) {
        days2 += laNamNhuan(y) ? 366 : 365;
    }
    for (int m = 1; m < ngay_tra.month; m++) {
        days2 += ngayTrongThang(m, ngay_tra.year);
    }
    days2 += ngay_tra.day;

    return days2 - days1;
}

int SoNgayQuaHan(Date ngay_muon, Date ngay_tra) {
    if(DemSoNgay(ngay_muon, ngay_tra) >7) return DemSoNgay(ngay_muon, ngay_tra) - 7;
    return 0;
}

string ChuyenDateSangString(Date Ngay) {
    if(Ngay.day == 0 || Ngay.month == 0 || Ngay.year == 0) return "";
    string ngay = to_string(Ngay.day)+'/'+to_string(Ngay.month)+'/'+to_string(Ngay.year);
    return ngay;
}

Date ChuyenStringSangDate(string nhap_ngaythangnam) {
    string ngay, thang, nam;
    Date nhap_ngay_thang_nam;
    size_t vitri1 = nhap_ngaythangnam.find('/');
    size_t vitri2 = nhap_ngaythangnam.find('/', vitri1 + 1);

    if (vitri1 == string::npos || vitri2 == string::npos) {
        cout << "Lỗi: Chuỗi ngày tháng không hợp lệ" << endl; // thông báo lỗi bằng dialog
        return nhap_ngay_thang_nam;
    }

    ngay = nhap_ngaythangnam.substr(0, vitri1);
    thang = nhap_ngaythangnam.substr(vitri1 + 1, vitri2 - vitri1 - 1);
    nam = nhap_ngaythangnam.substr(vitri2 + 1);

    nhap_ngay_thang_nam.day = stoi(ngay);
    nhap_ngay_thang_nam.month = stoi(thang);
    nhap_ngay_thang_nam.year = stoi(nam);

    // Kiểm tra giá trị ngày, tháng, năm hợp lệ
    if (nhap_ngay_thang_nam.day <= 0 || nhap_ngay_thang_nam.day > 31) {
        cout << "Lỗi: Ngày không hợp lệ" << endl;
        return Date();
    }
    if (nhap_ngay_thang_nam.month <= 0 || nhap_ngay_thang_nam.month > 12) {
        cout << "Lỗi: Tháng không hợp lệ" << endl;
        return Date();
    }
    if (nhap_ngay_thang_nam.year < 1900 || (nhap_ngay_thang_nam.year > 2100) ) {
        cout << "Lỗi: Năm không hợp lệ" << endl;
        return Date();
    }

    return nhap_ngay_thang_nam;
}

