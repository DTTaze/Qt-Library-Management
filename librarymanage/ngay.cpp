#include "ngay.h"

bool operator == (const Date &d1, const Date &d2) {
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool laNamNhuan(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool KiemTraNgayThangNam(Date NgayThangNam) {

    if (NgayThangNam.year <= 0 ||NgayThangNam.year >2024|| NgayThangNam.month <= 0 || NgayThangNam.month > 12) return false;

    int soNgayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (laNamNhuan(NgayThangNam.year)) soNgayTrongThang[1] = 29;

    return NgayThangNam.day > 0 && NgayThangNam.day <= soNgayTrongThang[NgayThangNam.month - 1];
}

bool isNumber(const string &str) {
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

void NhapNgayThangNam(Date &nhap_ngay_thang_nam) {
    string nhap_ngaythangnam, ngay, thang, nam;
    cout << "Nhap ngay thang nam (DD/MM/YYYY): ";
    getline(cin, nhap_ngaythangnam);

    size_t vitri1 = nhap_ngaythangnam.find('/');
    size_t vitri2 = nhap_ngaythangnam.find('/', vitri1 + 1);

    if (vitri1 == string::npos || vitri2 == string::npos) {
        cout << "Dinh dang ngay thang nam khong hop le!" << endl;
        return;
    }

    ngay = nhap_ngaythangnam.substr(0, vitri1);
    thang = nhap_ngaythangnam.substr(vitri1 + 1, vitri2 - vitri1 - 1);
    nam = nhap_ngaythangnam.substr(vitri2 + 1);

    if (!isNumber(ngay) || !isNumber(thang) || !isNumber(nam)) {
        cout << "Loi: Ngay, thang, nam phai la so nguyen!" << endl;
        return;
    }

    nhap_ngay_thang_nam.day = stoi(ngay);
    nhap_ngay_thang_nam.month = stoi(thang);
    nhap_ngay_thang_nam.year = stoi(nam);

    if (!KiemTraNgayThangNam(nhap_ngay_thang_nam)) {
        cout << "Loi: Ngay thang nam khong hop le!" << endl;
    }
}


void NgayTraDuKien(Date Ngay_muon) {
    tm Ngay_du_kien;
    Ngay_du_kien.tm_mday = Ngay_muon.day + 7;
    Ngay_du_kien.tm_mon = Ngay_muon.month;
    Ngay_du_kien.tm_year = Ngay_muon.year;
    time_t time = mktime(&Ngay_du_kien);
    cout<<Ngay_du_kien.tm_mday<<"/"<<Ngay_du_kien.tm_mon<<"/"<<Ngay_du_kien.tm_year<<endl;
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

Date NgayTraThucTe(){
    int luachon = 1;
    Date ngay_tra_thuc_te;
    while(luachon!=0) {
        cout<<"nhap tuy chon: 1. ngay tra la hom nay       2. ngay tra la ngay khac       0.thoat ra"<<endl;
        cout<<"lua chon: ";
        cin>>luachon;

        cin.ignore();

        if(luachon == 1) {
            time_t now = time(0);
            tm *Ngay_thuc_te = localtime(&now);
            ngay_tra_thuc_te.day = Ngay_thuc_te->tm_mday;
            ngay_tra_thuc_te.month = Ngay_thuc_te->tm_mon + 1;
            ngay_tra_thuc_te.year = Ngay_thuc_te->tm_year + 1900;
            cout<<"Da luu ngay tra!"<<endl;
            break;
        } else if(luachon == 2) {

            NhapNgayThangNam(ngay_tra_thuc_te);
            if(KiemTraNgayThangNam(ngay_tra_thuc_te) == false) {cout<<"ban da lam sai, vui long nhap lai!";}
            else {break;}
        } else if(luachon == 0) ;
        else {cout<<"khong hop le, vui long nhap lai";}
    }
    return ngay_tra_thuc_te;
}

int DemSoNgay(Date ngay_muon, Date ngay_tra) {

    tm ngaymuon = {0}, ngaytra = {0};
    ngaymuon.tm_mday = ngay_muon.day;
    ngaymuon.tm_mon = ngay_muon.month - 1;
    ngaymuon.tm_year = ngay_muon.year - 1900;

    ngaytra.tm_mday = ngay_tra.day;
    ngaytra.tm_mon = ngay_tra.month - 1;
    ngaytra.tm_year = ngay_tra.year - 1900;

    time_t ngaymuon1 = mktime(&ngaymuon);
    time_t ngaytra1 = mktime(&ngaytra);

    // Đảm bảo ngày trả phải sau ngày mượn
    if (ngaymuon1 == -1 || ngaytra1 == -1) {
        cout << "Lỗi: Ngày mượn hoặc ngày trả không hợp lệ!" << endl;
        return -1;
    }
    if (ngaytra1 < ngaymuon1) {
        cout << "Ngay tra phai sau ngay muon!" << endl;
        return -1;
    }

    double sogiay = difftime(ngaytra1, ngaymuon1);
    int songay = sogiay / (60 * 60 * 24);
    return songay;
}

int SoNgayQuaHan(Date ngay_muon, Date ngay_tra) {
    if(DemSoNgay(ngay_muon, ngay_tra) >7) return DemSoNgay(ngay_muon, ngay_tra) - 7;
    return 0;
}

void InManHinhNgayThangNam(Date ngay_thang_nam) {
    cout<<ngay_thang_nam.day<<"/"<<ngay_thang_nam.month<<"/"<<ngay_thang_nam.year<<endl;
}


// int main () {
//     Date muonsach, trasach;
//     int luachon = 1;
//     while(luachon != 0) {
//         cout<<"Nhap tuy chon: 1. muon sach          2. tra sach         3. da nhap xong, in ra thong tin        0. thoat chuong trinh"<<endl;
//         cout<<"lua chon: ";
//         cin>>luachon;

//         if(luachon == 1) {
//             muonsach = NgayMuon();
//             cout<<"neu muon hom nay, ngay tra du kien cua ban la: ";
//             NgayTraDuKien (muonsach);
//         }
//         else if(luachon == 2) {
//             if(muonsach.day == 0) {
//                 cout<<"Quyen sach nay chua muon, vui long chon tuy chon khac!"<<endl;
//             }
//             else trasach = NgayTraThucTe();
//         }
//         else if (luachon == 3) {
//             if(muonsach.day == 0) {
//                 cout<<"chua co thong tin!"<<endl;

//             } else {
//                 cout<<"Ngay muon: "; InManHinhNgayThangNam(muonsach);
//                 cout<<"Ngay tra du kien: "; NgayTraDuKien(muonsach);
//                 cout<<"Ngay tra thuc te: "; InManHinhNgayThangNam(trasach);
//                 break;
//             }
//         }
//         else if (luachon == 0) return 0;
//         else {cout<<"khong hop le, vui long nhap lai"<<endl;}
//     }
//     return 0;
// }
