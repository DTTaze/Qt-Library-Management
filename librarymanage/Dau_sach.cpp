#include "Dau_sach.h"

DanhSachDauSach danh_sach_dau_sach;
DanhMucSach* danh_muc_sach;

int TimKiemViTriDauSach(string ma) {// nhan ma isbn // ma sach
    if(ma.size() < 13) return -1;

    if(ma.size() > 17) {// ma sach cua ISBN-13
        ma = ma.substr(0,17);
    }

    if (ma.size() == 17){
        if (ma.substr(13) == "0000") {// ma sach cua ISBN-10
            ma = ma.substr(0, 13);
        }
    }
    // Tìm kiếm ISBN trong danh_sach_dau_sach
    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {
        if (danh_sach_dau_sach.node[i]->ISBN == ma) {
            return i;
        }
    }
    return -1;
}


void TaoMaSach(string& ma_sach, const string& I_S_B_N, int demsosach) {
    string isbn_full = I_S_B_N;

    // Kiểm tra nếu ISBN là loại 10 số
    if (isbn_full.size() == 13) {
        isbn_full += "0000"; // Thêm 4 số '0' vào cuối ISBN
    }

    // Gán mã sách bao gồm ISBN và số sách dưới dạng chuỗi
    ma_sach = isbn_full + "-" + to_string(demsosach);
}

void ThemDanhMucSach(DanhMucSach* &head_dms, int trang_thai,  const string& vi_tri, const string &I_S_B_N,int demsosach,string ma_sach) {
    // Tạo mã sách mới
    if (ma_sach == "") {
        TaoMaSach(ma_sach, I_S_B_N,demsosach);
    }
    // Tạo node mới với thông tin mã sách, trạng thái và vị trí
    DanhMucSach* new_dms = new DanhMucSach(ma_sach, trang_thai, vi_tri);
    // Thêm node mới vào đầu danh sách
    new_dms->next = head_dms;
    head_dms = new_dms;
}

void ChenDauSachMoi(DauSach*& Dau_Sach_moi,string ten_sach){
    //Mặc định chèn vào cuối
    int n = danh_sach_dau_sach.soluongdausach;
    int vi_tri_them = n;

    //Xác định vị trí chèn
    for (int i = 0; i < n ; i++){
        if (ten_sach <= danh_sach_dau_sach.node[i]->tensach){
            vi_tri_them = i;
            break;
        }
    }

    //Dời các sách phía sau 1 vị trí
    for (int i = n; i > vi_tri_them ; i--){
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i-1];
    }

    //Chèn sách vào vị trí tìm được
    danh_sach_dau_sach.node[vi_tri_them] = Dau_Sach_moi;
    //tăng số sách trong đầu sách lên 1
    danh_sach_dau_sach.node[vi_tri_them]->demsosach++;
}

//danh sach dau sach tham chieu mang, danh muc sach tham chieu con tro vi lien ket don
void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                  int trang_thai,string &vi_tri,string ma_sach){

    int index_isbn = TimKiemViTriDauSach(I_S_B_N);

    if(index_isbn == -1){//Nếu không tồn tại thì thêm đầu sách mới


        DauSach* new_DauSach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,nam_sx,the_loai);

        ThemDanhMucSach(new_DauSach->dms,trang_thai,vi_tri,I_S_B_N,new_DauSach->demsosach+1,ma_sach);

        ChenDauSachMoi(new_DauSach,ten_sach);

        //tăng đầu sách và số sách trong đầu sách lên 1
        danh_sach_dau_sach.soluongdausach++;

    }else {//Nếu tồn tại thì thêm vào đầu sách đã có với demsosach+1
        ThemDanhMucSach(danh_sach_dau_sach.node[index_isbn]->dms,trang_thai,vi_tri,I_S_B_N,danh_sach_dau_sach.node[index_isbn]->demsosach+1,ma_sach);
        danh_sach_dau_sach.node[index_isbn]->demsosach++;
    }
}

void InToanBoDauSach(DanhSachDauSach &danh_sach_dau_sach, int so_luong_sach, QTableView* tableView_dausach,QStandardItemModel*& model){

    if (model != nullptr ) {
        // Xóa dữ liệu cũ
        model->clear(); // Xóa tất cả các dòng và cột
        delete model;   // Giải phóng bộ nhớ của model
        model = nullptr; // Đặt model về nullptr
    }

    const int row_count = so_luong_sach;

    // Tạo model cho table
    model = new QStandardItemModel(row_count, 6);

    QString headers[6] = {
        "ISBN",
        "Tên sách",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Thể loại",
    };

    for (int i = 0; i < 6; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    for (int i = 0; i < row_count; i++) {
        model->setItem(i, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
        model->setItem(i, 2, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->sotrang)));
        model->setItem(i, 3, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
        model->setItem(i, 4, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
        model->setItem(i, 5, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));
    }

    // Gán model vào QTableView
    tableView_dausach->setModel(model);
    tableView_dausach->resizeColumnsToContents();
    tableView_dausach->setColumnWidth(1,300);
}

void ChuyenVeChuThuong(std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
}//static_cast<unsigned char> de cac ki tu am khong gay loi

void InTheoTenTimKiem(string key, QTableView* tableView_dausach,QStandardItemModel*& model){

    if (model != nullptr ) {
        // Xóa dữ liệu cũ
        model->clear(); // Xóa tất cả các dòng và cột
        delete model;   // Giải phóng bộ nhớ của model
        model = nullptr; // Đặt model về nullptr
    }

    int row_count = 0;
    model = new QStandardItemModel(0, 7);

    QString headers[7] = {
        "ISBN", "Tên sách", "Tác giả", "Năm xuất bản", "Thể loại", "Mã sách", "Trạng thái"
    };
    for (int i = 0; i < 7; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    ChuyenVeChuThuong(key);
    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {

        string ten_sach = danh_sach_dau_sach.node[i]->tensach;

        ChuyenVeChuThuong(ten_sach);

        if (ten_sach.find(key) != std::string::npos) {
            model->insertRow(row_count);
            model->setItem(row_count, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
            model->setItem(row_count, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
            model->setItem(row_count, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
            model->setItem(row_count, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
            model->setItem(row_count, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));

            int trangthai = danh_sach_dau_sach.node[i]->dms->trangthai;
            string trang_thai_std;


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

    if (row_count == 0)  {model->clear();return;}

    tableView_dausach->setModel(model);
    tableView_dausach->resizeColumnsToContents();

}

string ChuyenMaSachThanhTenSach(DanhSachDauSach &danh_sach_dau_sach,const string& ma_sach){
    int i = TimKiemViTriDauSach(ma_sach);
    if (i != -1){
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
    int n = Dau_sach_goc.soluongdausach;
    for (int i = 0; i < n;i++){
        copy[i]=i;
    }
}
void InTheoTungTheLoai(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_intheloai) {
    cout << "Bắt đầu in theo thể loại \n\n";
    int so_luong_sach = danh_sach_dau_sach.soluongdausach;
    int* copy = new int[so_luong_sach](); // Cấp phát động mảng, mặc định phần tử = 0

    // Sao chép và sắp xếp danh sách đầu sách
    SaoChepDanhSach(danh_sach_dau_sach, copy);
    MergeSort(copy, 0, so_luong_sach - 1, danh_sach_dau_sach);

    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(so_luong_sach, 7);
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

    // Thiết lập dữ liệu và gộp ô theo thể loại
    string The_loai_hien_tai = "";
    int row_index = 0; // Biến để lưu chỉ số hàng hiện tại

    for (int i = 0; i < so_luong_sach; i++) {
        if (The_loai_hien_tai != danh_sach_dau_sach.node[copy[i]]->theloai) {

            QStandardItem* Item_theloai = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->theloai));
            Item_theloai->setTextAlignment(Qt::AlignCenter);//canh giữa thể loại

            model->setItem(row_index, 0, Item_theloai);// Thêm thể loại cột đầu tiên

            tableView_intheloai->setSpan(row_index, 0, 1, 7); // Gộp toàn bộ 7 cột cho hàng thể loại mới

            The_loai_hien_tai = danh_sach_dau_sach.node[copy[i]]->theloai;
            row_index++;
        }

        // Thêm thông tin sách
        model->setItem(row_index, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tensach)));
        model->setItem(row_index, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->ISBN)));
        model->setItem(row_index, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->sotrang)));
        model->setItem(row_index, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tacgia)));
        model->setItem(row_index, 5, new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->namsx)));
        model->setItem(row_index, 6, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->dms->vitri)));

        row_index++; // Tăng chỉ số hàng sau khi thêm sách
    }

    // Gán model vào tableView và thiết lập kích thước cột
    tableView_intheloai->setModel(model);
    tableView_intheloai->resizeColumnsToContents();

    // Ẩn cột thể loại
    tableView_intheloai->hideColumn(0);

    // Giải phóng bộ nhớ
    delete[] copy;
}


void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,QStandardItemModel*& model, string key) {

    // Neu nguoi dung nhap key
    if (!key.empty()) {
        InTheoTenTimKiem(key,tableView_dausach,model);
    } else {
        InToanBoDauSach(danh_sach_dau_sach,danh_sach_dau_sach.soluongdausach,tableView_dausach,model);
    }
}

void ChenMaSachVaoTable(const string& ma_ISBN , QTableView* tableView_dausach,QStandardItemModel*& model,string key){

    if (model != nullptr ) {
        // Xóa dữ liệu cũ
        model->clear(); // Xóa tất cả các dòng và cột
        delete model;   // Giải phóng bộ nhớ của model
        model = nullptr; // Đặt model về nullptr
    }

    int row_count = 0;
    model = new QStandardItemModel(0, 7);

    QString headers[7] = {
        "ISBN", "Tên sách", "Tác giả", "Năm xuất bản", "Thể loại", "Mã sách", "Trạng thái"
    };
    for (int i = 0; i < 7; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    ChuyenVeChuThuong(key);
    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {

        string ten_sach = danh_sach_dau_sach.node[i]->tensach;

        ChuyenVeChuThuong(ten_sach);

        if (ten_sach.find(key) != std::string::npos) {
            model->insertRow(row_count);
            model->setItem(row_count, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
            model->setItem(row_count, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
            model->setItem(row_count, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
            model->setItem(row_count, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
            model->setItem(row_count, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));
            if (danh_sach_dau_sach.node[i]->ISBN == ma_ISBN){
                for(DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms; cur != nullptr; cur = cur->next){

                    int trangthai = cur->trangthai;
                    string trang_thai_std;


                    model->setItem(row_count, 5, new QStandardItem(QString::fromStdString(cur->masach)));
                    switch (trangthai){
                    case 0:trang_thai_std = "Có thể mượn";break;
                    case 1:trang_thai_std = "Đã được mượn";break;
                    case 2:trang_thai_std = "Đã thanh lý";break;
                    }

                    model->setItem(row_count, 6, new QStandardItem(QString::fromStdString(trang_thai_std)));
                    row_count++;
                }
            }else row_count++;
        }
    }

    tableView_dausach->setModel(model);
    tableView_dausach->resizeColumnsToContents();
}

bool KiemTraDaySachKV(DanhSachDauSach &danh_sach_dau_sach){
    if (danh_sach_dau_sach.soluongdausach > 9999){
        qDebug()<<"So sach da day\n";
        return true;
    }else{
        return false;
    };
}


void DocTuFile(DanhSachDauSach &danh_sach_dau_sach,QWidget* parent) {

    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        QMessageBox::warning(parent, "Lỗi", "Không thể mở file Danh_sach_dau_sach.txt");
        return;
    }

    string line;
    while (getline(file, line)) {
        string ISBN, tensach, tacgia, theloai, vitri, masach;
        int sotrang = 0, namsx = 0,trangthai= -1;

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

        pos = line.find('|');
        masach = line.substr(0, pos); line.erase(0, pos + 1);

        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty() || masach.empty()) {
            continue;
        }

        ThemDauSach(danh_sach_dau_sach, ISBN, tensach, sotrang, tacgia, namsx, theloai,trangthai, vitri,masach);
    }
    file.close();
    // for (int i = 0; i < danh_sach_dau_sach.soluongdausach;i++){
    //     for(DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms;cur != nullptr;cur=cur->next){
    //         qDebug()<<cur->masach;
    //     }
    // }
}

void InVaoTXT() {
    ofstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        qDebug() << "Không thể mở tệp Danh_sach_dau_sach.txt để ghi.";
        return;
    }

    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; ++i) {
        for (DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms; cur != nullptr; cur = cur->next) {
            DauSach* dau_sach = danh_sach_dau_sach.node[i];

            // Ghi thông tin đầu sách vào tệp
            file << dau_sach->ISBN << '|'
                 << dau_sach->tensach << '|'
                 << dau_sach->sotrang << '|'
                 << dau_sach->tacgia << '|'
                 << dau_sach->namsx << '|'
                 << dau_sach->theloai << '|'
                 << cur->vitri << '|'
                 << cur->trangthai << '|'
                 << cur->masach << endl;
        }
    }

    file.close();
}

void CapNhatTrangThaiSach(string ma_sach,int trang_thai){
    int i = TimKiemViTriDauSach(ma_sach);
    if (i == -1) {qDebug()<<"Không thể cập nhật trạng thái sách vì mã sách không hợp lệ.";return ;}
    for (DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms;cur!=nullptr;cur=cur->next){
        if(cur->masach == ma_sach){
            cur->trangthai = trang_thai;
            return;
        }
    }
}
bool TonTaiMaSachDS(string ma_sach){
    int i = TimKiemViTriDauSach(ma_sach);
    if (i == -1) {return false;}
    for (DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms;cur!=nullptr;cur=cur->next){
        if(cur->masach == ma_sach){
            return true;
        }
    }
    return false;
}
