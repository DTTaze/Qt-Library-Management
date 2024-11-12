#include "themdausach.h"
#include "ui_themdausach.h"

themdausach::themdausach( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::themdausach)
{
    ui->setupUi(this);
    KhoaNhapDauSach();
}

themdausach::~themdausach()
{
    delete ui;
}

void themdausach::KhoaNhapDauSach(){
    ui->lineEdit_tacgia->setReadOnly(true);
    ui->lineEdit_tensach->setReadOnly(true);
    ui->lineEdit_theloai->setReadOnly(true);
    ui->comboBox_vitri->setEnabled(false);
    ui->spinBox_namsb->setReadOnly(true);
    ui->spinBox_sotrang->setReadOnly(true);
}

void themdausach::MoKhoaNhapDauSach(){
    ui->lineEdit_tacgia->setReadOnly(false);
    ui->lineEdit_tensach->setReadOnly(false);
    ui->lineEdit_theloai->setReadOnly(false);
    ui->comboBox_vitri->setEnabled(true);
    ui->spinBox_namsb->setReadOnly(false);
    ui->spinBox_sotrang->setReadOnly(false);
}

bool themdausach::ThemMaISBNQTHopLe(QString i_s_b_n){
    int Dash_Count = i_s_b_n.count('-');
    return ((i_s_b_n.length() == 13 && Dash_Count == 3) || (i_s_b_n.length() == 17 && Dash_Count == 4)) ? true : false;
}

QString themdausach::CapitalizeWords(const QString& text) {
    QString result;
    bool isNewWord = true;

    for (int i = 0; i < text.length(); ++i) {
        QChar c = text[i];

        if (c.isLetter()) {
            if (isNewWord) {
                c = c.toUpper();  // Chuyển thành chữ in hoa
                isNewWord = false;
            }
        } else {
            isNewWord = true; // Đánh dấu bắt đầu từ mới khi gặp ký tự không phải chữ cái
        }

        result += c; // Thêm ký tự vào chuỗi kết quả
    }

    return result;
}



QString themdausach::RemoveSpace(const QString &key) {
    QString valid_key;
    bool lastWasSpace = false;

    for (QChar c : key) {
        if (c.isLetter() ) {
            valid_key += c; // Thêm ký tự hợp lệ (chữ hoặc số) vào valid_key
            lastWasSpace = false; // Reset trạng thái lastWasSpace
        } else if (c.isSpace()) {
            if (!lastWasSpace) {
                valid_key += ' '; // Thêm một dấu cách nếu không phải là dấu cách trước đó
                lastWasSpace = true; // Đánh dấu rằng dấu cách đã được thêm
            }
        }
        // Nếu là ký tự đặc biệt, không thêm vào valid_key, tức là xóa ký tự đặc biệt
    }

    return valid_key;
}

void themdausach::on_pushButton_clicked() {
    // Lấy dữ liệu từ các ô input và combobox
    QString ISBN = ui->lineEdit_ISBN->text().simplified();
    QString tensach = ui->lineEdit_tensach->text().simplified();
    QString tacgia = ui->lineEdit_tacgia->text().simplified();
    QString theloai = ui->lineEdit_theloai->text().simplified();
    QString vitri = ui->comboBox_vitri->currentText().simplified();
    int sotrang = ui->spinBox_sotrang->value();
    int namsx = ui->spinBox_namsb->value();
    int soluong = ui->spinBox_soluong->value();

    // Chuyển đổi sang string
    string isbnStd = ISBN.toStdString();
    string tensachStd = tensach.toStdString();
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();
    string vitriStd = vitri.toStdString();

    // Biến lưu trữ thông báo lỗi
    QString errorMessage;

    // Kiểm tra từng điều kiện và thêm lỗi vào errorMessage nếu có
    if (ISBN.isEmpty()) {
        errorMessage += "Bạn chưa điền ISBN.\n";
    } else if (int i = TimKiemViTriDauSach(isbnStd) != -1) {
        QMessageBox::warning(this,"Cảnh báo", "Mã đã tồn tại.");
        return;
    } else if (!ThemMaISBNQTHopLe(ISBN)) {
        QMessageBox::warning(this,"Cảnh báo", "Mã không hợp lệ.");
        return;
    }

    QString messages[] = {
        "Bạn chưa điền tên sách.\n",
        "Bạn chưa điền tên tác giả.\n",
        "Bạn chưa điền thể loại.\n",
        "Bạn chưa điền vị trí.\n"
    };
    string inputs[] = {tensachStd, tacgiaStd, theloaiStd, vitriStd};

    for (int i = 0; i < 4; ++i) {
        if (inputs[i].empty()) {
            errorMessage += messages[i];
        }
    }

    if (sotrang <= 0) {
        errorMessage += "Số trang phải lớn hơn 0.\n";
    }

    if (namsx <= 0) {
        errorMessage += "Năm xuất bản không hợp lệ.\n";
    }

    // Nếu có lỗi, hiển thị thông báo và thoát hàm
    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", errorMessage);
        return;
    }

    for (int i = 0; i < soluong; i++) {
        ThemDauSach(danh_sach_dau_sach, isbnStd, tensachStd, sotrang, tacgiaStd, namsx, theloaiStd, co_the_muon, vitriStd, "");
    }

    // Hiển thị thông tin đã nhập
    QString infoMessage = QString("Thông tin đã nhập:\nISBN: %1\nTên sách: %2\nTác giả: %3\nThể loại: %4\nSố trang: %5\nNăm xuất bản: %6\nVị trí: %7\nTrạng Thái: Cho mượn được")
                              .arg(QString::fromStdString(isbnStd))
                              .arg(QString::fromStdString(tensachStd))
                              .arg(QString::fromStdString(tacgiaStd))
                              .arg(QString::fromStdString(theloaiStd))
                              .arg(sotrang)
                              .arg(namsx)
                              .arg(QString::fromStdString(vitriStd));

    QMessageBox::information(this, "Thông tin đã nhập", infoMessage);

    // Đóng hộp thoại sau khi thêm thành công
    accept();
}


void themdausach::on_pushButton_2_clicked()
{
    close();
}

void themdausach::on_lineEdit_ISBN_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString LocKiTu; // Chuỗi để lưu trữ các ký tự hợp lệ
        int cursorPosition = ui->lineEdit_ISBN->cursorPosition(); // Ghi nhớ vị trí con trỏ
        // Lọc ra các ký tự là chữ số
        for (int i = 0; i < text.length(); ++i) {
            if (text[i].isDigit() || text[i] == '-') {
                LocKiTu.append(text[i]); // Thêm ký tự hợp lệ vào LocKiTu
            }
        }

        // Cập nhật lại nội dung của lineEdit với các ký tự hợp lệ
        ui->lineEdit_ISBN->setText(LocKiTu);

        // Thiết lập lại vị trí con trỏ
        if (cursorPosition < LocKiTu.length()) {
            ui->lineEdit_ISBN->setCursorPosition(cursorPosition);
        } else {
            ui->lineEdit_ISBN->setCursorPosition(LocKiTu.length());
        }

        if (LocKiTu.length() == 0){
            ui->lineEdit_ISBN->setStyleSheet("");
        }else if (ThemMaISBNQTHopLe(LocKiTu)) {
            string ma_isbn_hople = LocKiTu.toStdString();
            int index = TimKiemViTriDauSach(ma_isbn_hople);
            if (index == -1){
                ui->lineEdit_ISBN->setStyleSheet("background-color: lightgreen;");
                MoKhoaNhapDauSach();
            }else{
                ui->lineEdit_ISBN->setStyleSheet("background-color: lightcoral;");
                KhoaNhapDauSach();
            }
        } else {
            ui->lineEdit_ISBN->setStyleSheet("background-color: lightcoral;");
            KhoaNhapDauSach();
        }
    }else{
        ui->lineEdit_ISBN->setStyleSheet("");
    }
}

void themdausach::on_spinBox_namsb_valueChanged(int arg1)
{
    if(arg1 != 0){
        // Lay nam hien tai
        std::time_t now = std::time(0);
        std::tm *localTime = std::localtime(&now);
        int currentYear = localTime->tm_year + 1900; // Nam hien tai
        // Kiểm tra xem năm nhập vào có lớn hơn năm hiện tại không
        if (arg1 > currentYear) {
            // Nếu lớn hơn năm hiện tại, thông báo và đặt lại giá trị
            QMessageBox::warning(this, "Lỗi", "Năm không hợp lệ! Vui lòng nhập lại.");

            // Đặt lại giá trị cho QSpinBox về năm hiện tại
            ui->spinBox_namsb->setValue(currentYear);
        }
    }
}


void themdausach::on_lineEdit_tensach_textChanged(const QString &text) {
    if(!text.isEmpty()){
        QString key;
        bool lastWasSpace = false; // Kiểm tra xem ký tự trước có phải là khoảng trắng không
        int cursorPosition = ui->lineEdit_tensach->cursorPosition(); // Lưu vị trí con trỏ

        for (QChar c : text) {
            if (c.isLetter() || c.isDigit() || c.isPunct() || c.isSymbol()) {
                key += c; // Thêm ký tự hợp lệ vào key
                lastWasSpace = false; // Reset trạng thái lastWasSpace
            } else if (c.isSpace()) {
                if (!lastWasSpace) {
                    key += ' '; // Thêm một dấu cách nếu không phải là dấu cách trước đó
                    lastWasSpace = true; // Đánh dấu rằng dấu cách đã được thêm
                }
            }
        }

        // Xóa khoảng trắng ở đầu
        string valid_key = key.toStdString();
        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r"));

        // Cập nhật lại tên sách vào QLineEdit
        ui->lineEdit_tensach->setText(QString::fromStdString(valid_key));

        // Đặt lại vị trí con trỏ
        if (cursorPosition < valid_key.length()) {
            ui->lineEdit_tensach->setCursorPosition(cursorPosition);
        } else {
            ui->lineEdit_tensach->setCursorPosition(valid_key.length());
        }
    }
}





void themdausach::on_lineEdit_theloai_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString key = RemoveSpace(text);
        key = CapitalizeWords(key);
        string valid_key = key.toStdString();

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu
        // Cập nhật lại tên thể loại vào QLineEdit
        ui->lineEdit_theloai->setText(QString::fromStdString(valid_key));
    }
}


void themdausach::on_comboBox_vitri_currentTextChanged(const QString &text)
{
    if(!text.isEmpty()){
        string key = text.toStdString();

        // Chỉ cho phép một ký tự
        if (key.length() > 1) {
            key = key.substr(0, 1); // Giới hạn chỉ lấy ký tự đầu tiên
        }

        // Kiểm tra nếu ký tự là a-z hoặc A-Z
        if (!key.empty() && (isalpha(key[0]))) {
            // Chuyển ký tự thành in hoa
            key[0] = toupper(key[0]); // Chuyển đổi ký tự thành chữ in hoa
        } else {
            key.clear(); // Nếu không phải là chữ cái a-z hoặc A-Z, xóa key
        }

        // Cập nhật lại giá trị trong lineEdit
        ui->comboBox_vitri->setCurrentText(QString::fromStdString(key));

        //qDebug() << "Vi tri da duoc cap nhat: " << key;

        // Nếu key rỗng, không cần cập nhật
        // if (key.empty()) {
        //     //qDebug() << "Vi tri rong.";
        // }
    }
}



void themdausach::on_lineEdit_tacgia_textChanged(const QString &text)
{
    if(!text.isEmpty()){
        QString key = RemoveSpace(text);
        key = CapitalizeWords(key);
        string valid_key = key.toStdString();

        valid_key.erase(0, valid_key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu
        // Cập nhật lại tên thể loại vào QLineEdit
        ui->lineEdit_tacgia->setText(QString::fromStdString(valid_key));
    }
}


