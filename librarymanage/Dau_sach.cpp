#include "Dau_sach.h"

void TaoMaSach(string& ma_sach ,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri){
    int Khu_vuc = vi_tri[0] - 'A'; // khu A : 0 , B : 1 , ...

    if(danh_sach_dau_sach.demsachvitri[Khu_vuc] > 999) { // bat dau tu index 0 den 999 la 1000 cuon
        cout<<"Vi tri : "<<vi_tri<<" da day \n";
        Khu_vuc++;//neu da co 1000 cuon sach thi tang len khu tiep theo
    };

    int so_sach_trong_phan_khu = danh_sach_dau_sach.demsachvitri[Khu_vuc];

    int phan_khu = (so_sach_trong_phan_khu / 100) + 1;
    int index_sach = (so_sach_trong_phan_khu % 100) + 1;

    vi_tri += to_string(phan_khu);
    ma_sach = vi_tri + "-" + to_string(index_sach);

    danh_sach_dau_sach.demsachvitri[Khu_vuc]++;
}

DanhMucSach* ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,DanhSachDauSach &danh_sach_dau_sach, string& vi_tri) {

    //them vao dau danh sach sap xep theo ma sach
    string ma_sach;
    TaoMaSach(ma_sach,danh_sach_dau_sach,vi_tri);
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
};

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                 DanhMucSach* &head_dms, int trang_thai,string &vi_tri){

    if(danh_sach_dau_sach.demsach >= MAXSACH){
        cout<<"Day sach";
        return;
    };

    DanhMucSach* danh_muc_sach = ThemDanhMucSach(head_dms,trang_thai,danh_sach_dau_sach,vi_tri);


    int n = danh_sach_dau_sach.demsach;
    // cap phat bo nho cho sach moi voi con trỏ dms chi vao danh_muc_sach vua tao
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

DanhSachDauSach SaoChepDanhSach(DanhSachDauSach &Dau_sach_goc) {
    DanhSachDauSach copy;
    copy.demsach = Dau_sach_goc.demsach;

    for (int i = 0; i < Dau_sach_goc.demsach; i++) {
        DauSach* original_dau_sach = Dau_sach_goc.node[i];
        // Tạo một bản sao của DauSach goc voi pointer chỏ vao cung bo nho voi Dau sach goc
        DauSach* new_dau_sach = new DauSach(
            original_dau_sach->ISBN,
            original_dau_sach->tensach,
            original_dau_sach->sotrang,
            original_dau_sach->tacgia,
            original_dau_sach->namsx,
            original_dau_sach->theloai,
            original_dau_sach->dms
            );
        copy.node[i] = new_dau_sach;
    }

    return copy;
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

string ChuyenMaSachThanhTenSach(DanhSachDauSach &danh_sach_dau_sach,string ma_sach){
    int ket_qua;
    for (int i =0; i < danh_sach_dau_sach.demsach;i++){
        if (danh_sach_dau_sach.node[i]->dms->masach == ma_sach){
            ket_qua = i;
            break;
        }
    }
    return danh_sach_dau_sach.node[ket_qua]->tensach;
}

void Merge(DauSach** arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    DauSach** L = new DauSach*[n1];
    DauSach** R = new DauSach*[n2];


    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // Tr?n hai m?ng l?i theo th? t?
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // So sánh theloai tru?c
        if (L[i]->theloai < R[j]->theloai) {
            arr[k] = L[i];
            i++;
        }
        // N?u theloai gi?ng nhau, so sánh tensach
        else if (L[i]->theloai == R[j]->theloai && L[i]->tensach <= R[j]->tensach) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Sao chép các ph?n t? còn l?i c?a L[], n?u có
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sao chép các ph?n t? còn l?i c?a R[], n?u có
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Gi?i phóng b? nh? t?m th?i
    delete[] L;
    delete[] R;
}

void MergeSort(DauSach** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;


        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);


        Merge(arr, left, mid, right);
    }
}

//Su dung tham chieu nen phai tao ban sao roi xoa ban sao
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach,QTableView* tableView_intheloai){
    qDebug()<<"test1";
    DanhSachDauSach copy = SaoChepDanhSach(danh_sach_dau_sach);

    int so_luong_sach = copy.demsach;
    MergeSort(copy.node, 0, so_luong_sach - 1);

    const int row_count = copy.demsach;
    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(row_count,7);

    QString headers[7] = {
        "ISBN",
        "Tên sách",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Thể loại",
        "Vị trí"
    };

    for (int i = 0; i < 7; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    for (int i = 0; i < row_count; i++){
        model->setItem(i,0, new QStandardItem(QString::fromStdString(copy.node[i]->ISBN)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(copy.node[i]->tensach)));
        model->setItem(i, 2, new QStandardItem(QString::number(copy.node[i]->sotrang)));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(copy.node[i]->tacgia)));
        model->setItem(i, 4, new QStandardItem(QString::number(copy.node[i]->namsx)));
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(copy.node[i]->theloai)));
        model->setItem(i, 6, new QStandardItem(QString::fromStdString(copy.node[i]->dms->vitri)));
    }

    tableView_intheloai->setModel(model);

    qDebug()<<"test2";
    for (int i = 0; i < copy.demsach; i++) {
        delete copy.node[i];
    }
    qDebug()<<"test3";
}


void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,string key){

    int vi_tri_dau_tien = TimKiemNhiPhanTenSach(danh_sach_dau_sach,key);

    if (!key.empty() && vi_tri_dau_tien != -1){
        int i =0;
        for (i = vi_tri_dau_tien; i <danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->tensach.substr(0,key.size()) == key;i++);
        const int row_count = i - vi_tri_dau_tien;
        QStandardItemModel* model = new QStandardItemModel(row_count,7);

        QString headers[7] = {
            "ISBN",
            "Tên sách",
            "Tác giả",
            "Năm xuất bản",
            "Thể loại",
            "Mã sách",
            "Trạng thái"
        };

        for (int i = 0; i < 7; i++) {
            model->setHeaderData(i, Qt::Horizontal, headers[i]);
        }
        qDebug()<<row_count;
        for (int i = 0; i < row_count;i++ ){
            model->setItem(i,0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->ISBN)));
            model->setItem(i,1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->tensach)));
            model->setItem(i,2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->tacgia)));
            model->setItem(i,3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->namsx)));
            model->setItem(i,4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->theloai)));
            model->setItem(i,5, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->dms->masach)));
            model->setItem(i,6, new QStandardItem(QString::number(danh_sach_dau_sach.node[i+vi_tri_dau_tien]->dms->trangthai)));
        }

        tableView_dausach->setModel(model);

        for (int i = vi_tri_dau_tien; i <danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->tensach.substr(0,key.size()) == key;i++ ){
            cout << "- " << danh_sach_dau_sach.node[i]->tensach <<endl;
        }
    }else{
        int row_count = danh_sach_dau_sach.demsach;

        QStandardItemModel* model = new QStandardItemModel(row_count,7);

        QString headers[7] = {
            "ISBN",
            "Tên sách",
            "Tác giả",
            "Năm xuất bản",
            "Thể loại",
            "Mã sách",
            "Trạng thái"
        };

        for (int i = 0; i < 7; i++) {
            model->setHeaderData(i, Qt::Horizontal, headers[i]);
        }

        for (int i = vi_tri_dau_tien; i <danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[i]->tensach.substr(0,key.size()) == key;i++ ){
            model->setItem(i,0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
            model->setItem(i,1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
            model->setItem(i,2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
            model->setItem(i,3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
            model->setItem(i,4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));
            model->setItem(i,5, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->dms->masach)));
            model->setItem(i,6, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->dms->trangthai)));
        }

        tableView_dausach->setModel(model);
    }

}

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach,string vi_tri){
    int Khu_vuc = vi_tri[0] - 'A'; // khu A : 0 , B : 1 , ...,J : 9
    int so_sach_trong_phan_khu = danh_sach_dau_sach.demsachvitri[Khu_vuc];
    if (so_sach_trong_phan_khu > 999){
        cout<<"So sach trong vi tri : "<<vi_tri<< " da day, vui long nhap lai.\n";
        return true;
    }else{return false;};
};

void NhapDauSachMoi(DanhSachDauSach &danh_sach_dau_sach,
                    DanhMucSach* &head_dms){
    string I_S_B_N;string ten_sach;int so_trang;string tac_gia;int nam_sx;string the_loai;
    int trang_thai; string vi_tri;

    cout << "Nhap ISBN cua sach: \n";
    getline(cin, I_S_B_N);

    cout << "Nhap ten sach: \n";
    getline(cin, ten_sach);

    cout << "Nhap so trang: \n";
    cin >> so_trang;
    cin.ignore();

    cout << "Nhap tac gia: \n";
    getline(cin, tac_gia);

    cout << "Nhap nam san xuat: \n";
    cin >> nam_sx;
    cin.ignore();

    cout << "Nhap the loai: \n";
    getline(cin, the_loai);

    do{
        bool k_hop_le = true;
        do{
            cout << "Nhap vi tri (A - J): \n";
            getline(cin, vi_tri);

            if (vi_tri < "A" || vi_tri > "J" ) {
                cout << "vi tri khong hop le. Vui long nhap tu A den J." << endl;
                k_hop_le = false;
            }
        }while(!k_hop_le);

    }while(KiemTraDaySachKV(danh_sach_dau_sach,vi_tri));

    ThemDauSach(danh_sach_dau_sach,I_S_B_N,ten_sach,so_trang, tac_gia,nam_sx, the_loai,
                head_dms, 0,vi_tri);
    //ghi vao file
    ofstream file("Danh_sach_dau_sach.txt", ios::app); // Mo file che do append
    if (file.is_open()) {
        file << I_S_B_N << '|'
             << ten_sach << '|'
             << so_trang << '|'
             << tac_gia << '|'
             << nam_sx << '|'
             << the_loai << '|'
             << vi_tri << endl;
        file.close();
    } else {
        cout << "Khong the mo file de ghi!" << endl;
    }
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
        int sotrang = 0, namsx = 0;

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

        // Kiểm tra các trường hợp rỗng
        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue;
        }

        // Thêm đầu sách vào danh sách
        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia, namsx, theloai, head_dms, 0, vitri);
    }
    file.close();
    const int row_count = danh_sach_dau_sach.demsach;

    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(row_count, 7);

    QString headers[7] = {
        "ISBN",
        "Tên sách",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Thể loại",
        "Vị trí"
    };

    for (int i = 0; i < 7; i++) {
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
    }

    // Gán model vào QTableView
    tableView_dausach->setModel(model);
    tableView_dausach->setColumnWidth(0,120);
    tableView_dausach->setColumnWidth(1,200);
    tableView_dausach->setColumnWidth(2,50);
    tableView_dausach->setColumnWidth(3,100);
    tableView_dausach->setColumnWidth(4,50);
    tableView_dausach->setColumnWidth(5,100);
    tableView_dausach->setColumnWidth(6,30);

}

