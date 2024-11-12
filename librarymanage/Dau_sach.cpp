#include "Dau_sach.h"

DanhSachDauSach danh_sach_dau_sach;
DanhMucSach* danh_muc_sach;

int TimKiemViTriDauSach(string ma) {
    if(ma.size() < 13) return -1;

    if(ma.size() > 17) {// ma sach cua ISBN-13
        ma = ma.substr(0,17);
    }

    if (ma.size() == 17){
        if (ma.substr(13) == "0000") {// ma sach cua ISBN-10
            ma = ma.substr(0, 13);
        }
    }

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

    DanhMucSach* new_dms = new DanhMucSach(ma_sach, trang_thai, vi_tri);

    new_dms->next = head_dms;
    head_dms = new_dms;
}


string ChuyenVeChuThuong(string str) {
    for (size_t i = 0; i < str.size(); ++i) {
        str[i] = tolower(static_cast<unsigned char>(str[i]));
    }
    return str;
}

void ChenDauSachMoi(DauSach*& Dau_Sach_moi, const string& ten_sach) {

    int n = danh_sach_dau_sach.soluongdausach;
    int vi_tri_them = n;


    QString ten_sach_qt = QString::fromStdString(ten_sach);


    for (int i = 0; i < n; i++) {

        QString ten_sach_cur_qt = QString::fromStdString(danh_sach_dau_sach.node[i]->tensach);


        if (ten_sach_qt.localeAwareCompare(ten_sach_cur_qt) <= 0) {
            vi_tri_them = i;
            break;
        }
    }


    for (int i = n; i > vi_tri_them; i--) {
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i - 1];
    }

    danh_sach_dau_sach.node[vi_tri_them] = Dau_Sach_moi;
    danh_sach_dau_sach.node[vi_tri_them]->demsosach++;
}


void ThemDauSach(DanhSachDauSach &danh_sach_dau_sach,const string& I_S_B_N,const string& ten_sach,int so_trang,const string& tac_gia,int nam_sx,const string& the_loai,
                  int trang_thai,string &vi_tri,string ma_sach){

    int index_isbn = TimKiemViTriDauSach(I_S_B_N);

    if(index_isbn == -1){


        DauSach* new_DauSach = new DauSach(I_S_B_N,ten_sach,so_trang,tac_gia,nam_sx,the_loai);

        ThemDanhMucSach(new_DauSach->dms,trang_thai,vi_tri,I_S_B_N,new_DauSach->demsosach+1,ma_sach);

        ChenDauSachMoi(new_DauSach,ten_sach);
        danh_sach_dau_sach.soluongdausach++;

    }else {
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
    tableView_dausach->verticalHeader()->hide();

}

// Xóa comment thừa
void InTheoTenTimKiem(string key, QTableView* tableView_dausach, QStandardItemModel*& model) {
    if (model != nullptr) {
        // Xóa dữ liệu cũ
        model->clear(); // Xóa tất cả các dòng và cột
        delete model;   // Giải phóng bộ nhớ của model
        model = nullptr; // Đặt model về nullptr
    }

    int row_count = 0;
    model = new QStandardItemModel(0, 5);

    QString headers[5] = {
        "ISBN", "Tên sách", "Tác giả", "Năm xuất bản", "Thể loại",
    };
    for (int i = 0; i < 5; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    key = ChuyenVeChuThuong(key);
    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {
        string ten_sach = danh_sach_dau_sach.node[i]->tensach;
        ten_sach = ChuyenVeChuThuong(ten_sach);

        if (ten_sach.find(key) != std::string::npos) {
            model->insertRow(row_count);
            model->setItem(row_count, 0, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN)));
            model->setItem(row_count, 1, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach)));
            model->setItem(row_count, 2, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia)));
            model->setItem(row_count, 3, new QStandardItem(QString::number(danh_sach_dau_sach.node[i]->namsx)));
            model->setItem(row_count, 4, new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai)));

            // Đặt tiêu đề dọc thành giá trị `i`
            model->setHeaderData(row_count, Qt::Vertical, QString::number(i));

            row_count++;
        }
    }

    if (row_count == 0)  {
        model->clear();
        return;
    }

    tableView_dausach->setModel(model);
    tableView_dausach->resizeColumnsToContents();
}

void TimKiemTenSach(DanhSachDauSach &danh_sach_dau_sach, QTableView* tableView_dausach,QStandardItemModel*& model, string key) {

    // Neu nguoi dung nhap key
    if (!key.empty()) {
        InTheoTenTimKiem(key,tableView_dausach,model);
    } else {
        InToanBoDauSach(danh_sach_dau_sach,danh_sach_dau_sach.soluongdausach,tableView_dausach,model);
    }
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
        string Left_tensach = ChuyenVeChuThuong(Dau_sach_goc.node[L[i]]->tensach);
        string Right_tensach = ChuyenVeChuThuong(Dau_sach_goc.node[R[j]]->tensach);

        QString Left_theloai_qt = QString::fromStdString(Left_theloai);
        QString Right_theloai_qt = QString::fromStdString(Right_theloai);
        QString Left_tensach_qt = QString::fromStdString(Left_tensach);
        QString Right_tensach_qt = QString::fromStdString(Right_tensach);
        
        if (Left_theloai_qt.localeAwareCompare(Right_theloai_qt) < 0) {
            //node nao co the loai nho hon thi them vi tri index vao mang
            arr[k] = L[i];
            i++;
        }
        // Neu the loai giong nhau thi so sanh ten
        else if (Left_theloai_qt.localeAwareCompare(Right_theloai_qt) == 0 && Left_tensach_qt.localeAwareCompare(Right_tensach_qt) <= 0) {
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
    int so_luong_sach = danh_sach_dau_sach.soluongdausach;
    int* copy = new int[so_luong_sach](); // Cấp phát động mảng, mặc định phần tử = 0

    // Sao chép và sắp xếp danh sách đầu sách
    SaoChepDanhSach(danh_sach_dau_sach, copy);
    MergeSort(copy, 0, so_luong_sach - 1, danh_sach_dau_sach);

    // Tạo model cho table
    QStandardItemModel* model = new QStandardItemModel(so_luong_sach, 6);
    QString headers[6] = {
        "Thể loại",
        "Tên sách",
        "ISBN",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
    };

    for (int i = 0; i < 6; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[i]);
    }

    // Thiết lập dữ liệu và gộp ô theo thể loại
    string The_loai_hien_tai = "";
    int row_index = 0; // Biến để lưu chỉ số hàng hiện tại

    for (int i = 0; i < so_luong_sach; i++) {
        if (The_loai_hien_tai != danh_sach_dau_sach.node[copy[i]]->theloai) {

            // Tạo item thể loại với font chữ in đậm và nghiêng
            QStandardItem* Item_theloai = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->theloai));
            QFont font;
            font.setBold(true);   // In đậm
            font.setItalic(true); // Nghiêng
            Item_theloai->setFont(font);
            Item_theloai->setTextAlignment(Qt::AlignCenter); // Căn giữa thể loại

            model->setItem(row_index, 0, Item_theloai); // Thêm thể loại cột đầu tiên

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

        row_index++; // Tăng chỉ số hàng sau khi thêm sách
    }

    // Gán model vào tableView và thiết lập kích thước cột
    tableView_intheloai->setModel(model);
    tableView_intheloai->resizeColumnsToContents();

    // Ẩn cột thể loại
    tableView_intheloai->hideColumn(0);
    tableView_intheloai->verticalHeader()->hide();

    // Giải phóng bộ nhớ
    delete[] copy;
}


bool DayDauSach(DanhSachDauSach &danh_sach_dau_sach){
    if (danh_sach_dau_sach.soluongdausach >= MAXSACH){
        return true;
    }else{
        return false;
    };
}


void DocTuFileDauSach(DanhSachDauSach &danh_sach_dau_sach,QWidget* parent) {

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
}

void GhiDauSachVaoFile() {
    ofstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        qDebug() << "Không thể mở tệp Danh_sach_dau_sach.txt để ghi."; // Báo lỗi bằng dialog
        return;
    }

    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; ++i) {
        for (DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms; cur != nullptr; cur = cur->next) {
            DauSach* dau_sach = danh_sach_dau_sach.node[i];
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
//*** Thông báo lỗi bằng dialog
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

bool TonTaiMaSach(string ma_sach){
    int i = TimKiemViTriDauSach(ma_sach);
    if (i == -1) {return false;}
    for (DanhMucSach* cur = danh_sach_dau_sach.node[i]->dms;cur!=nullptr;cur=cur->next){
        if(cur->masach == ma_sach){
            return true;
        }
    }
    return false;
}
