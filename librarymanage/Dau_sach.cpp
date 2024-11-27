#include "Dau_sach.h"

DanhSachDauSach danh_sach_dau_sach;

QString RemoveSpace(const QString &key) {
    QString valid_key;
    bool lastWasSpace = false;

    for (QChar c : key) {
        if (c.isLetter() ) {
            valid_key += c;
            lastWasSpace = false;
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                valid_key += ' ';
                lastWasSpace = true;
            }
        }
    }

    return valid_key;
}

QString CapitalizeWords(const QString& text) {
    QString result;
    bool isNewWord = true;

    for (int i = 0; i < text.length(); ++i) {
        QChar c = text[i];

        if (c.isLetter()) {
            if (isNewWord) {
                c = c.toUpper();
                isNewWord = false;
            }
        } else {
            isNewWord = true;
        }

        result += c;
    }

    return result;
}

void LocKiTuISBNHopLe(const QString& text,QString& LocKiTu){
    for (int i = 0; i < text.length(); ++i) {
        if (text[i].isDigit() || text[i] == '-') {
            LocKiTu.append(text[i]);
        }
    }
}

bool MaISBNQTHopLe(QString i_s_b_n){
    int Dash_Count = i_s_b_n.count('-');
    return ((i_s_b_n.length() == 13 && Dash_Count == 3) || (i_s_b_n.length() == 17 && Dash_Count == 4)) ? true : false;
}

void LocKiTuTensachHopLe(const QString& text,string& valid_key){
    QString key;
    bool lastWasSpace = false;

    for (QChar c : text) {
        if (c.isLetter() || c.isDigit() || c.isPunct() || c.isSymbol()) {
            key += c;
            lastWasSpace = false;
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                key += ' ';
                lastWasSpace = true;
            }
        }
    }

    valid_key = key.toStdString();
    valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));
}

bool DayDauSach() {
    return danh_sach_dau_sach.soluongdausach >= MAXSACH ? true : false;
}

bool TonTaiMaSachDaDuocMuonTrongDauSach(int index){
    for (DanhMucSach* current = danh_sach_dau_sach.node[index]->dms; current != nullptr; current = current->next){
        if(current->trangthai == da_duoc_muon){
            return true;
        }
    }
    return false;
}

void InToanBoDauSach(QTableWidget* tableWidget_dausach) {
    int so_luong_sach = danh_sach_dau_sach.soluongdausach;

    tableWidget_dausach->clearContents();
    tableWidget_dausach->setRowCount(so_luong_sach);
    tableWidget_dausach->setColumnCount(6);

    QString headers[6] = {
        "ISBN",
        "Tên sách",
        "Số trang",
        "Tác giả",
        "Năm xuất bản",
        "Thể loại",
    };

    for (int i = 0; i < 6; i++) {
        tableWidget_dausach->setHorizontalHeaderItem(i, new QTableWidgetItem(headers[i]));
    }

    for (int i = 0; i < so_luong_sach; i++) {
        QTableWidgetItem* isbnItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN));
        QTableWidgetItem* tenSachItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach));
        QTableWidgetItem* soTrangItem = new QTableWidgetItem(QString::number(danh_sach_dau_sach.node[i]->sotrang));
        QTableWidgetItem* tacGiaItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia));
        QTableWidgetItem* namSXItem = new QTableWidgetItem(QString::number(danh_sach_dau_sach.node[i]->namsx));
        QTableWidgetItem* theLoaiItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai));

        tableWidget_dausach->setItem(i, 0, isbnItem);
        tableWidget_dausach->setItem(i, 1, tenSachItem);
        tableWidget_dausach->setItem(i, 2, soTrangItem);
        tableWidget_dausach->setItem(i, 3, tacGiaItem);
        tableWidget_dausach->setItem(i, 4, namSXItem);
        tableWidget_dausach->setItem(i, 5, theLoaiItem);

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        tableWidget_dausach->setVerticalHeaderItem(i, item);

    }

    tableWidget_dausach->resizeColumnsToContents();
    tableWidget_dausach->setColumnWidth(1, 300);
    tableWidget_dausach->verticalHeader()->hide();
    tableWidget_dausach->horizontalHeader()->setStretchLastSection(true);
}

string ChuyenVeChuThuong(std::string str) {
    // Chuỗi ký tự in hoa
    string upper = "ÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐÉÈẺẼẸÊẾỀỂỄỆÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰÍÌỈĨỊÝỲỶỸỴ";
    // Chuỗi ký tự thường tương ứng
    string lower = "áàảãạăắằẳẵặâấầẩẫậđéèẻẽẹêếềểễệóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữựíìỉĩịýỳỷỹỵ";

    for (size_t i = 0; i < str.size(); ++i) {
        size_t pos = upper.find(str[i]);
        if (pos != std::string::npos) {
            str[i] = lower[pos];
        } else {
            str[i] = tolower(static_cast<unsigned char>(str[i]));
        }
    }
    return str;
}

void InTheoTenTimKiem(string key, QTableWidget* tableWidget_dausach) {
    tableWidget_dausach->clearContents();
    tableWidget_dausach->setRowCount(0);
    tableWidget_dausach->setColumnCount(5);

    QString headers[5] = {
        "ISBN", "Tên sách", "Tác giả", "Năm xuất bản", "Thể loại",
    };
    for (int i = 0; i < 5; i++) {
        tableWidget_dausach->setHorizontalHeaderItem(i, new QTableWidgetItem(headers[i]));
    }

    key = ChuyenVeChuThuong(key);
    int row_count = 0;

    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {
        string ten_sach = danh_sach_dau_sach.node[i]->tensach;
        ten_sach = ChuyenVeChuThuong(ten_sach);

        if (ten_sach.find(key) != std::string::npos) {
            tableWidget_dausach->insertRow(row_count);

            QTableWidgetItem* isbnItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->ISBN));
            QTableWidgetItem* tenSachItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tensach));
            QTableWidgetItem* tacGiaItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->tacgia));
            QTableWidgetItem* namSXItem = new QTableWidgetItem(QString::number(danh_sach_dau_sach.node[i]->namsx));
            QTableWidgetItem* theLoaiItem = new QTableWidgetItem(QString::fromStdString(danh_sach_dau_sach.node[i]->theloai));

            tableWidget_dausach->setItem(row_count, 0, isbnItem);
            tableWidget_dausach->setItem(row_count, 1, tenSachItem);
            tableWidget_dausach->setItem(row_count, 2, tacGiaItem);
            tableWidget_dausach->setItem(row_count, 3, namSXItem);
            tableWidget_dausach->setItem(row_count, 4, theLoaiItem);

            QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
            tableWidget_dausach->setVerticalHeaderItem(row_count, item);

            isbnItem->setFlags(isbnItem->flags() & ~Qt::ItemIsEditable);

            row_count++;
        }
    }

    if (row_count == 0) {
        tableWidget_dausach->clearContents();
        tableWidget_dausach->setRowCount(0);
        return;
    }

    tableWidget_dausach->resizeColumnsToContents();
    tableWidget_dausach->horizontalHeader()->setStretchLastSection(true);
}

void TimKiemTenSach(QTableWidget* tableWidget_dausach, string key) {
    if (!key.empty()) {
        InTheoTenTimKiem(key,tableWidget_dausach);
    } else {
        InToanBoDauSach(tableWidget_dausach);
    }
}

void SaoChepDanhSach( int* copy) {
    int n = danh_sach_dau_sach.soluongdausach;
    for (int i = 0; i < n;i++){
        copy[i]=i;
    }
}

void Merge(int* arr, int left, int mid, int right) {
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

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        string Left_theloai = danh_sach_dau_sach.node[L[i]]->theloai;
        string Right_theloai = danh_sach_dau_sach.node[R[j]]->theloai;
        string Left_tensach = ChuyenVeChuThuong(danh_sach_dau_sach.node[L[i]]->tensach);
        string Right_tensach = ChuyenVeChuThuong(danh_sach_dau_sach.node[R[j]]->tensach);

        QString Left_theloai_qt = QString::fromStdString(Left_theloai);
        QString Right_theloai_qt = QString::fromStdString(Right_theloai);
        QString Left_tensach_qt = QString::fromStdString(Left_tensach);
        QString Right_tensach_qt = QString::fromStdString(Right_tensach);

        if (SoSanhTiengViet(Left_theloai_qt,Right_theloai_qt) < 0) {
            arr[k] = L[i];
            i++;
        }
        else if (SoSanhTiengViet(Left_theloai_qt,Right_theloai_qt) == 0 && SoSanhTiengViet(Left_tensach_qt,Right_tensach_qt) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void MergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

void InTheoTungTheLoai(QTableView* tableView_intheloai) {
    int so_luong_sach = danh_sach_dau_sach.soluongdausach;
    int* copy = new int[so_luong_sach]();

    SaoChepDanhSach(copy);
    MergeSort(copy, 0, so_luong_sach - 1);

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

    string The_loai_hien_tai = "";
    int row_index = 0;

    for (int i = 0; i < so_luong_sach; i++) {
        if (The_loai_hien_tai != danh_sach_dau_sach.node[copy[i]]->theloai) {

            QStandardItem* Item_theloai = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->theloai));
            QFont font;
            font.setBold(true);
            font.setItalic(true);
            Item_theloai->setFont(font);

            Item_theloai->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            model->setItem(row_index, 0, Item_theloai);

            tableView_intheloai->setSpan(row_index, 0, 1, 7);

            The_loai_hien_tai = danh_sach_dau_sach.node[copy[i]]->theloai;
            row_index++;
        }

        QStandardItem* item_tensach = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tensach));
        item_tensach->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        model->setItem(row_index, 1, item_tensach);

        QStandardItem* item_isbn = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->ISBN));
        item_isbn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        model->setItem(row_index, 2, item_isbn);

        QStandardItem* item_sotrang = new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->sotrang));
        item_sotrang->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        model->setItem(row_index, 3, item_sotrang);

        QStandardItem* item_tacgia = new QStandardItem(QString::fromStdString(danh_sach_dau_sach.node[copy[i]]->tacgia));
        item_tacgia->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        model->setItem(row_index, 4, item_tacgia);

        QStandardItem* item_namsx = new QStandardItem(QString::number(danh_sach_dau_sach.node[copy[i]]->namsx));
        item_namsx->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        model->setItem(row_index, 5, item_namsx);

        row_index++;
    }

    tableView_intheloai->setModel(model);
    tableView_intheloai->resizeColumnsToContents();

    tableView_intheloai->hideColumn(0);
    tableView_intheloai->verticalHeader()->hide();

    delete[] copy;
}

void ChuyenThanhISBN(string& ma){
    if(ma.size() > 17) {
        ma = ma.substr(0,17);
    }

    if (ma.size() == 17){
        if (ma.substr(13) == "0000") {
            ma = ma.substr(0, 13);
        }
    }
}

int TimKiemViTriDauSach(string ma) {
    if(ma.size() < 13) return -1;

    ChuyenThanhISBN(ma);

    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {
        if (danh_sach_dau_sach.node[i]->ISBN == ma) {
            return i;
        }
    }
    return -1;
}

int SoSanhTiengViet(const QString &s1, const QString &s2) {
    QString alphabet = "aáàảãạăắằẳẵặâấầẩẫậAÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬbBcCdđDĐeéèẻẽẹêếềểễệEÉÈẺẼẸÊẾỀỂỄỆfFgGhHiíìỉĩịIÍÌỈĨỊjJkKlLmMnNoóòỏõọôốồổỗộơờớởỡợOÓÒỎÕỌÔỐỒỔỖỘƠỜỚỞỠỢpPqQrRsStTuúùủũụưứừửữựUÚÙỦŨỤƯỨỪỬỮỰvVwWxXyýỳỷỹỵYYỲỶỸỴzZ!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    int len = (s1.length() < s2.length()) ? s1.length() : s2.length();

    for (int i = 0; i < len; ++i) {
        QChar c1 = s1[i];
        QChar c2 = s2[i];

        int rank1 = alphabet.indexOf(c1);
        int rank2 = alphabet.indexOf(c2);

        if (rank1 != rank2) {
            return (rank1 < rank2) ? -1 : 1;
        }
    }

    if (s1.length() < s2.length()) {
        return -1;
    } else if (s1.length() > s2.length()) {
        return 1;
    } else {
        return 0;
    }
}

bool TonTaiDauSach(int index){
    return ( index == -1 ) ? false:true;
}

string ChuyenMaSachThanhTenSach(const string&  ma_sach){
    int i = TimKiemViTriDauSach(ma_sach);
    if (TonTaiDauSach(i)){
        return danh_sach_dau_sach.node[i]->tensach;
    }else{
        return "";
    }
}

void TaoMaSach(string& ma_sach, DauSach* ds) {
    string isbn_full = ds->ISBN;

    if (isbn_full.size() == 13) {
        isbn_full += "0000";
    }
    ma_sach = isbn_full + "-" + to_string(ds->SoLuongDanhMucSachTrongDausach+1);
}

void ThemDanhMucSach(DauSach*& ds, int trang_thai, const string& vi_tri,string ma_sach) {
    if (ma_sach == "") {
        TaoMaSach(ma_sach,ds);
    }

    DanhMucSach* new_dms = new DanhMucSach(ma_sach, trang_thai, vi_tri);

    new_dms->next = ds->dms;
    ds->dms = new_dms;
}

void NhapDauSach(int index_isbn,int trang_thai,string vi_tri,string ma_sach){
    ThemDanhMucSach(danh_sach_dau_sach.node[index_isbn],trang_thai,vi_tri,ma_sach);
    danh_sach_dau_sach.node[index_isbn]->SoLuongDanhMucSachTrongDausach++;
}

void XacDinhViTriThem(const string &ten_sach, int &vi_tri_them) {
    QString ten_sach_qt = QString::fromStdString(ten_sach);

    for (int i = 0; i < danh_sach_dau_sach.soluongdausach; i++) {
        QString ten_sach_cur_qt = QString::fromStdString(danh_sach_dau_sach.node[i]->tensach);

        if (SoSanhTiengViet(ten_sach_qt,ten_sach_cur_qt) < 0) {
            vi_tri_them = i;
            break;
        }
    }
}

void DoiViTriDauSachThem(int vi_tri_them){
    for (int i = danh_sach_dau_sach.soluongdausach; i > vi_tri_them; i--) {
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i - 1];
    }
    danh_sach_dau_sach.soluongdausach++;
}

void ChenDauSachTheoThuTu(DauSach*& Dau_Sach_moi,string ten_sach,int &vi_tri_them){
    int n = danh_sach_dau_sach.soluongdausach;
    vi_tri_them = n ;
    XacDinhViTriThem(ten_sach,vi_tri_them);
    DoiViTriDauSachThem(vi_tri_them);
    danh_sach_dau_sach.node[vi_tri_them] = Dau_Sach_moi;
}

void ThemDauSach(DauSach& ds,int trang_thai,string vi_tri,string ma_sach){
    DauSach* new_DauSach = new DauSach(ds);
    ThemDanhMucSach(new_DauSach,trang_thai,vi_tri,ma_sach);
    new_DauSach->SoLuongDanhMucSachTrongDausach++;
    int vi_tri_them;
    ChenDauSachTheoThuTu(new_DauSach,new_DauSach->tensach,vi_tri_them);
}

void ThemHoacNhapDauSach(DauSach ds,int trang_thai,string vi_tri,string ma_sach){
    int index_isbn = TimKiemViTriDauSach(ds.ISBN);

    if(!TonTaiDauSach(index_isbn)){
        ThemDauSach(ds,trang_thai,vi_tri,ma_sach);
    }else {
        NhapDauSach(index_isbn,trang_thai,vi_tri,ma_sach);
    }
}

void ChenDauSachSauKhiThayDoi(string ten_sach,int &index_hien_tai){
    DauSach* temp_ds = danh_sach_dau_sach.node[index_hien_tai];
    DoiViTriDauSachXoa(index_hien_tai);
    ChenDauSachTheoThuTu(temp_ds,ten_sach,index_hien_tai);

}

void DoiViTriDauSachXoa(int index){
    for (int i = index; i < danh_sach_dau_sach.soluongdausach - 1; i++) {
        danh_sach_dau_sach.node[i] = danh_sach_dau_sach.node[i + 1];
    }
    danh_sach_dau_sach.soluongdausach--;
}

void XoaDauSach(int index){
    delete danh_sach_dau_sach.node[index];
    DoiViTriDauSachXoa(index);
}

DanhMucSach* TimDiaChiSachTrongDanhMucSach(string maSach) {
    int vitri = TimKiemViTriDauSach(maSach);
    if (!TonTaiDauSach) {
        QString mes; mes+="Không tồn tại đầu sách có mã" + QString::fromStdString(maSach);
        QMessageBox::critical(nullptr,"Lỗi",mes);
        return nullptr;
    }

    for (DanhMucSach* current = danh_sach_dau_sach.node[vitri]->dms ; current != nullptr; current = current->next) {
        if (current->masach == maSach) return current;
    }
    return nullptr;
}

bool TonTaiMaSach(string ma_sach){
    return TimDiaChiSachTrongDanhMucSach(ma_sach) != nullptr ? true : false;
}

void CapNhatTrangThaiSach(string ma_sach,int trang_thai){
    DanhMucSach* dms = TimDiaChiSachTrongDanhMucSach(ma_sach);
    dms->trangthai = trang_thai;
}

void DocTuFileDauSach() {
    ifstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file Danh_sach_dau_sach.txt");
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
        if (masach.empty()) masach = "";

        if (ISBN.empty() || tensach.empty() || tacgia.empty() || theloai.empty() || vitri.empty()) {
            continue;
        }

        DauSach ds;
        ds.ISBN = ISBN;
        ds.tensach = tensach;
        ds.sotrang = sotrang;
        ds.tacgia = tacgia;
        ds.namsx = namsx;
        ds.theloai = theloai;
        ThemHoacNhapDauSach(ds,trangthai, vitri,masach);
    }
    file.close();
}

void GhiDauSachVaoFile() {
    ofstream file("Danh_sach_dau_sach.txt");
    if (!file.is_open()) {
        QMessageBox::critical(nullptr,"Lỗi","Không thể mở tệp Danh_sach_dau_sach.txt để ghi.");
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




















