#include "Dau_sach.h"

DanhSachDauSach danh_sach_dau_sach;
DanhMucSach* danh_muc_sach;


void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach,const string &I_S_B_N,const string& vi_tri){
ma_sach = I_S_B_N + "-" + vi_tri ;
}


DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach,const string& vi_tri,const string &I_S_B_N) {

    //them vao dau danh sach sap xep theo ma sach
    string ma_sach = "";
    TaoMaSach(ma_sach,danh_sach_dau_sach,I_S_B_N,vi_tri);
    DanhMucSach* new_dms = new DanhMucSach(ma_sach,trang_thai,vi_tri);
    DanhMucSach* t = nullptr;
    DanhMucSach* s = head_dms;
    for ( ; s != nullptr && new_dms->masach > s->masach; t = s , s = s->next);
    if (t == nullptr){
        new_dms->next = head_dms;
        head_dms = new_dms;
    }else{
        new_dms->next = s;
        t->next = new_dms;
    }
    return new_dms;
}

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                 DanhMucSach* &head_dms, int trang_thai,string &vi_tri){

    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,danh_sach_dau_sach,vi_tri,I_S_B_N);

    int n = danh_sach_dau_sach.demsach;
    // cap phat bo nho cho sach moi voi con trá» dms chi vao danh_muc_sach vua tao
    DauSach* new_sach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,nam_sx,the_loai,danh_muc_sach);

    //mac dinh chen vao cuoi
    int vi_tri_them = n;
    //xac dinh vi tri chen
    for (int i = 0; i < n ; i++){
        if (ten_sach <= danh_sach_dau_sach.node[i]->tensach){
            vi_tri_them = i;
            break;
        }
    }

    //doi cac sach khac ra sau 1 vi tri
    for (int i = n; i > vi_tri_them ; i--){
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i-1];
    }
    //chen sach vao vi tri tim duoc
    danh_sach_dau_sach.node[vi_tri_them] = new_sach;
    //tang dem sach len 1
    danh_sach_dau_sach.demsach++;
}

void InFull(DanhSachDauSach &danh_sach_dau_sach, int so_luong_sach, QTableView* tableView_dausach){

    const int row_count = so_luong_sach;

    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(row_count, 9);

    QString headers[9] = {
        "ISBN",
        "Tên sách",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Thể loại",
        "Vị trí" ,
        "Mã sách" ,
        "Trạng Thái"
    };

    for (int i = 0; i < 9; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    for (int i = 0; i < row_count; i++) {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
        model->setItem(i, 2, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->sotrang)));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
        model->setItem(i, 4, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));
        model->setItem(i, 6, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->dms->vitri)));
        model->setItem(i, 7, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->dms->masach)));
        int trangthai = danh_sach_dau_sach.node[i]->dms->trangthai;
        string trang_thai_std;
        switch (trangthai){
        case 0:trang_thai_std = "Có thể mượn";break;
        case 1:trang_thai_std = "Đã được mượn";break;
        case 2:trang_thai_std = "Đã thanh lý";break;
        }
        model->setItem(i, 8, new QStandardItem(QString::fromStdString(trang_thai_std)));
    }

    // Gán model vào QTableView
    tableView_dausach->setModel(model);
    tableView_dausach->setColumnWidth(0,120);
    tableView_dausach->setColumnWidth(1,200);
    tableView_dausach->setColumnWidth(2,50);
    tableView_dausach->setColumnWidth(3,100);
    tableView_dausach->setColumnWidth(4,100);
    tableView_dausach->setColumnWidth(5,100);
    tableView_dausach->setColumnWidth(6,40);
    tableView_dausach->setColumnWidth(7,135);
    tableView_dausach->setColumnWidth(8,100);
}

void ChuyenVeChuThuong(std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
}//static_cast<unsigned char> de cac ki tu am khong gay loi

void InFullTheoTenSach(string key, QTableView* tableView_dausach){
    QStandardItemModel* model;
    int row_count = 0;
    model = new QStandardItemModel(0, 7);

    QString headers[7] = {
        "ISBN", "Tên sách", "Tác giả", "Năm xuất bản", "Thể loại", "Mã sách", "Trạng thái"
    };
    for (int i = 0; i < 7; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    ChuyenVeChuThuong(key);

    for (int i = 0; i < danh_sach_dau_sach.demsach; i++) {

        string ten_sach = danh_sach_dau_sach.node[i]->tensach;

        ChuyenVeChuThuong(ten_sach);

        if (ten_sach.find(key) != std::string::npos) {
            int trangthai = danh_sach_dau_sach.node[i]->dms->trangthai;
            string trang_thai_std;

            model->insertRow(row_count);
            model->setItem(row_count, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
            model->setItem(row_count, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
            model->setItem(row_count, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
            model->setItem(row_count, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
            model->setItem(row_count, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));
            model->setItem(row_count, 5, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->dms->masach)));
            switch (trangthai){
            case 0:trang_thai_std = "Có thể mượn";break;
            case 1:trang_thai_std = "Đã được mượn";break;
            case 2:trang_thai_std = "Đã thanh lý";break;
            }

            model->setItem(row_count, 6, new QStandardItem(QString::fromStdString(trang_thai_std)));
            row_count++;
        }
    }

    tableView_dausach->setModel(model);

    tableView_dausach->setColumnWidth(0, 120);
    tableView_dausach->setColumnWidth(1, 200);
    tableView_dausach->setColumnWidth(2, 100);
    tableView_dausach->setColumnWidth(3, 100);
    tableView_dausach->setColumnWidth(4, 100);
    tableView_dausach->setColumnWidth(5, 100);
    tableView_dausach->setColumnWidth(6, 100);

}

int TimKiemNhiPhanTenSach(DanhSachDauSach &danh_sach_dau_sach,string key){
    int left = 0;
    int right = danh_sach_dau_sach.demsach-1;
    int ket_qua = -1;

    while(left <= right){
        int mid = (left + right) /2;
        string tien_to = danh_sach_dau_sach.node[mid]->tensach.substr(0,key.size());

        if (tien_to == key) {
            ket_qua = mid;
            right = mid - 1;//doi right ve mid de xac dinh vi tri tien to dau tien
        } else if (tien_to < key) {//key ben phai
            left = mid + 1;
        } else {//key ben trai
            right = mid - 1;
        }
    }
    return ket_qua;
}

int TimKiemNhiPhanTheLoai(DanhSachDauSach &danh_sach_dau_sach,string key){
    int left = 0;
    int right = danh_sach_dau_sach.demsach-1;
    int ket_qua = -1;

    while(left <= right){
        int mid = (left + right) /2;

        if (danh_sach_dau_sach.node[mid]->theloai == key) {
            ket_qua = mid;
            right = mid - 1;//doi right ve mid de xac dinh vi tri tien to dau tien
        } else if (danh_sach_dau_sach.node[mid]->theloai < key) {//key ben phai
            left = mid + 1;
        } else {//key ben trai
            right = mid - 1;
        }
    }
    return ket_qua;
}

string ChuyenMaSachThanhTenSach(DanhSachDauSach &danh_sach_dau_sach,const string& ma_sach){
    string ma_ISBN = ma_sach.substr(0,17);
    int i = 0;
    for (; i < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->ISBN != ma_ISBN;i++);

    if (i < danh_sach_dau_sach.demsach){
        return danh_sach_dau_sach.node[i]->tensach;
    }else{
        return "";
    }
}

void Merge(int* arr, int left, int mid, int right,DanhSachDauSach &Dau_sach_goc) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    int* L = new int[n1];
    int* R = new int[n2];


    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // tron 2 mang lai theo thu tu
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // So sanh the loai truoc
        string Left_theloai = Dau_sach_goc.node[L[i]]->theloai;
        string Right_theloai = Dau_sach_goc.node[R[j]]->theloai;
        string Left_tensach = Dau_sach_goc.node[L[i]]->tensach;
        string Right_tensach = Dau_sach_goc.node[R[j]]->tensach;

        if (Left_theloai < Right_theloai) {
            //node nao co the loai nho hon thi them vi tri index vao mang
            arr[k] = L[i];
            i++;
        }
        // Neu the loai giong nhau thi so sanh ten
        else if (Left_theloai == Right_theloai && Left_tensach <= Right_tensach) {
            //node nao co ten sach nho hon thi them vi tri index vao mang
            arr[k] = L[i];
            i++;
        } else {
            // neu the loai hoac cung the loai nhung ten sach cua Right nho hon thi them vi tri index cua right vao mang
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Sao chep cac phan tu con lai cua L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sao chep cac phan tu con lai cua R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Giai phong bo nho
    delete[] L;
    delete[] R;
}

void MergeSort(int* arr, int left, int right,DanhSachDauSach &Dau_sach_goc) {
    if (left < right) {
        int mid = left + (right - left) / 2;


        MergeSort(arr, left, mid, Dau_sach_goc);
        MergeSort(arr, mid + 1, right, Dau_sach_goc);


        Merge(arr, left, mid, right,Dau_sach_goc);
    }
}

void SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc, int* copy) {
    cout<<"bat dau sao chep\n";
    int n = Dau_sach_goc.demsach;
    for (int i = 0; i < n;i++){
        copy[i]=i;
    }
    cout<<"ket thuc\n\n";
}

//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach,QTableView* tableView_intheloai){
    cout<<"bat dau in theo the loai \n\n";
    int so_luong_sach = danh_sach_dau_sach.demsach;
    int* copy = new int[so_luong_sach]();// cap phat dong mang, mac dinh phan tu = 0

    SaoChepDanhSach(danh_sach_dau_sach,copy);
    cout<<"bat dau sap xep \n";
    MergeSort(copy,0,so_luong_sach-1,danh_sach_dau_sach);
    cout<<"da sap xep xong";

    const int row_count = so_luong_sach;
    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(row_count,7);

    QString headers[7] = {
        "Thể loại",
        "Tên sách",
        "ISBN",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Vị trí"
    };

    for (int i = 0; i < 7; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    for (int i = 0; i < row_count; i++){
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->theloai)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tensach)));
        model->setItem(i, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->ISBN)));
        model->setItem(i, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->sotrang)));
        model->setItem(i, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tacgia)));
        model->setItem(i, 5, new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->namsx)));
        model->setItem(i, 6, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->dms->vitri)));
    }

    tableView_intheloai->setModel(model);

    delete[] copy;

}

void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach, string key) {
    QStandardItemModel* model;

    // Neu nguoi dung nhap key
    if (!key.empty()) {
        InFullTheoTenSach(key,tableView_dausach);
    } else {
        InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach,tableView_dausach);
    }



}

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach){
    if (danh_sach_dau_sach.demsach > 9999){
        cout<<"So sach da day\n";
        return true;
    }else{return false;};
}

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms, string I_S_B_N, string ten_sach, int so_trang, string tac_gia, int nam_sx, string the_loai, string vi_tri) {
    ThemDauSach(danh_sach_dau_sach, I_S_B_N, ten_sach, so_trang, tac_gia, nam_sx, the_loai, head_dms, 0, vi_tri);
}

void DocTuFile(DanhSachDauSach &danh_sach_dau_sach, DanhMucSach* &head_dms, QTableView* tableView_dausach, QWidget* parent) {

    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        QMessageBox::warning(parent, "Lỗi", "Không thể đọc file Danh_sach_dau_sach.txt");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string ISBN, tensach, tacgia, theloai, vitri;
        int sotrang = 0, namsx = 0,trangthai= -1;

        // Tách thông tin
        size_t pos = 0;

        pos = line.find('|');
        ISBN = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        tensach = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        sotrang = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        tacgia = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        namsx = stoi(line.substr(0, pos)); line.erase(0, pos + 1);

        pos = line.find('|');
        theloai = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        vitri = line.substr(0, pos); line.erase(0, pos + 1);

        pos = line.find('|');
        trangthai = stoi(line.substr(0, pos)); line.erase(0, pos + 1);
        // Kiểm tra các trường hợp rỗng
        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue;
        }

        // Thêm đầu sách vào danh sách
        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia, namsx, theloai, head_dms, trangthai, vitri);
    }
    file.close();

    InFull(danh_sach_dau_sach,danh_sach_dau_sach.demsach,tableView_dausach);
}
bool InVaoTXT(){
    ofstream file("Danh_sach_dau_sach.txt");
    if (file.is_open()) {
        for (int i = 0; i < danh_sach_dau_sach.demsach; ++i) {
            DauSach* dau_sach = danh_sach_dau_sach.node[i];

            file << dau_sach->ISBN << '|'
                 << dau_sach->tensach << '|'
                 << dau_sach->sotrang << '|'
                 << dau_sach->tacgia << '|'
                 << dau_sach->namsx << '|'
                 << dau_sach->theloai << '|'
                 << dau_sach->dms->trangthai;
            file << endl; // Kết thúc dòng thông tin của đầu sách
        }
        file.close();
            return true;
    } else {
        qDebug() << "Khong the mo file de ghi!" << "\n";
        return false;
    }
}

void CapNhatTrangThaiSach(string ma_sach,int trang_thai){
    qDebug()<<"Bắt đầu cập nhật trạng thái sách";
    string ma_ISBN = ma_sach.substr(0,17);
    int i = 0;
    for (; i < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->ISBN != ma_ISBN;i++);
    qDebug()<<"Index: "<<i;
    danh_sach_dau_sach.node[i]->dms->trangthai = trang_thai;
    qDebug()<<"Kết thúc cập nhật";
}
