#include "themdausach.h"
#include "ui_themdausach.h"

themdausach::themdausach( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::themdausach)
{
    ui->setupUi(this);
}

themdausach::~themdausach()
{
    delete ui;
}

bool KiemTraKiTuDacBiet(const string& key) {
    string specialChars = "@*()<>!?^&%$#";

    for (char c : key) {
        for (char special : specialChars) {
            if (c == special) {
                return true; // Nếu ký tự đặc biệt tồn tại, trả về true
            }
        }
    }
    return false; // Nếu không có ký tự đặc biệt nào, trả về false
}

string CapitalizeWords(const string& text) {
    string result;
    bool isNewWord = true; // Kiem tra co pha ki tu dau tien cua tu

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];

        // Kiem tra co phai chu cai khong
        if (isalpha(c)) {
            if (isNewWord) {//kiem tra co phai tu dau tien
                c = toupper(c); // Chuyen ky tu dau tien thanh in hoa
                isNewWord = false; // danh dau da qua ki tu dau
            }
        } else {
            isNewWord = true; // khong phai chu cai thi lam moi
        }

        result += c; //Them vao chuoi
    }

    return result;
}

string RemoveSpace(const QString &text){
    string key = text.toStdString();

    string valid_key;
    bool lastWasSpace = false;

    for (char c : key) {
        if (isalnum(c)) {
            valid_key += c; // Thêm ký tự hợp lệ (chữ hoặc số) vào valid_key
            lastWasSpace = false; // Reset trạng thái lastWasSpace
        } else if (isspace(c)) {
            if (!lastWasSpace) {
                valid_key += ' '; // Thêm một dấu cách nếu không phải là dấu cách trước đó
                lastWasSpace = true; // Đánh dấu rằng dấu cách đã được thêm
            }
        }
        // Nếu là ký tự đặc biệt, không thêm vào valid_key, tức là xóa ký tự đặc biệt
    }

    // Cập nhật lại giá trị cho key
    key = valid_key;

    // Xóa khoảng trắng ở đầu
    key.erase(0, key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu
    return key;
}

void themdausach::on_pushButton_clicked() {

    // Lấy dữ liệu từ các ô input và combobox
    QString ISBN = ui->lineEdit_ISBN->text().simplified();
    QString tensach = ui->lineEdit_tensach->text().simplified();
    QString tacgia = ui->lineEdit_tacgia->text().simplified();
    QString theloai = ui->lineEdit_theloai->text().simplified();
    QString vitri = ui->comboBox_vitri->currentText().simplified(); // Dữ liệu từ QComboBox
    int sotrang = ui->spinBox_sotrang->value();
    int namsx = ui->spinBox_namsb->value();

    // Chuyển đổi sang string
    string isbnStd = ISBN.toStdString();
    std::string tensachStd = CapitalizeWords(tensach.toStdString()); // Chuyển đổi tên sách
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();
    string vitriStd = vitri.toStdString(); // Chuyển đổi từ QComboBox

    // Mảng đầu vào và mảng thông báo lỗi
    string inputs[] = {isbnStd, tensachStd, tacgiaStd, theloaiStd, vitriStd};
    string tenloi[] = {"ISBN", "Tên sách", "Tác giả", "Thể loại", "Vị trí"};
    QString messages[] = {
        "Bạn chưa điền ISBN.",
        "Bạn chưa điền tên sách.",
        "Bạn chưa điền tên tác giả.",
        "Bạn chưa điền thể loại.",
        "Bạn chưa điền vị trí."
    };

    // Kiểm tra các trường bắt buộc
    for (int i = 0; i < 5; ++i) {
        if (inputs[i].empty()) {
            QMessageBox::warning(this, "Lỗi", messages[i]);
            return;
        }
        if (KiemTraKiTuDacBiet(inputs[i])) {
            QMessageBox::warning(this, "Lỗi", QString("%1 chứa ký tự đặc biệt không hợp lệ.").arg(QString::fromStdString(tenloi[i])));
            return;
        }
    }

    // Kiểm tra số trang phải lớn hơn 0
    if (sotrang <= 0) {
        QMessageBox::warning(this, "Lỗi", "Số trang phải lớn hơn 0.");
        return;
    }

    // Kiểm tra năm xuất bản phải lớn hơn 0
    if (namsx <= 0) {
        QMessageBox::warning(this, "Lỗi", "Năm xuất bản không hợp lệ.");
        return;
    }

    // Gọi hàm thêm đầu sách với các tham số đã chuyển đổi
    ThemDauSach(danh_sach_dau_sach, isbnStd, tensachStd, sotrang, tacgiaStd, namsx, theloaiStd, danh_muc_sach, 0, vitriStd);

    // Tìm mã sách từ danh mục sách
    int index = 0;
    for (; index < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[index]->ISBN != isbnStd; index++);

    string ma_sach = danh_sach_dau_sach.node[index]->dms->masach;

    // Hiển thị thông tin đã nhập
    QString infoMessage = QString("Thông tin đã nhập:\nISBN: %1\nTên sách: %2\nTác giả: %3\nThể loại: %4\nSố trang: %5\nNăm xuất bản: %6\nVị trí: %7\nTrạng Thái: Cho mượn được\nMã sách: %8")
                              .arg(QString::fromStdString(isbnStd))
                              .arg(QString::fromStdString(tensachStd))
                              .arg(QString::fromStdString(tacgiaStd))
                              .arg(QString::fromStdString(theloaiStd))
                              .arg(sotrang)
                              .arg(namsx)
                              .arg(QString::fromStdString(vitriStd))
                              .arg(QString::fromStdString(ma_sach));

    QMessageBox::information(this, "Thông tin đã nhập", infoMessage);

    // Đóng hộp thoại sau khi thêm thành công
    accept();
}


void themdausach::on_pushButton_2_clicked()
{
    close();
}


void themdausach::on_spinBox_namsb_valueChanged(int arg1)
{
    // Lay nam hien tai
    std::time_t now = std::time(0);
    std::tm *localTime = std::localtime(&now);
    int currentYear = localTime->tm_year + 1900; // Nam hien tai
    qDebug() << "Current Year: " << currentYear;
    qDebug() << "SpinBox Value: " << ui->spinBox_namsb->value();
    qDebug() << "arg1: "<<arg1;
    // Kiểm tra xem năm nhập vào có lớn hơn năm hiện tại không
    if (arg1 > currentYear) {
        // Nếu lớn hơn năm hiện tại, thông báo và đặt lại giá trị
        QMessageBox::warning(this, "Lỗi", "Năm không hợp lệ! Vui lòng nhập lại.");

        // Đặt lại giá trị cho QSpinBox về năm hiện tại
        ui->spinBox_namsb->setValue(currentYear);
    }
}


void themdausach::on_lineEdit_ISBN_textChanged(const QString &text)
{
    QString LocKiTu; // Chuỗi để lưu trữ các ký tự hợp lệ

    // Lọc ra các ký tự là chữ số
    for (int i = 0; i < text.length(); ++i) {
        if (text[i].isDigit() || text[i] == '-') {
            LocKiTu.append(text[i]); // Thêm ký tự hợp lệ vào LocKiTu
        }
    }

    // Cập nhật lại nội dung của lineEdit với các ký tự hợp lệ
    ui->lineEdit_ISBN->setText(LocKiTu);
    ui->lineEdit_ISBN->setCursorPosition(LocKiTu.length()); // Đặt lại con trỏ

    // Nếu không có ký tự nào, đặt lại màu về mặc định
    if (LocKiTu.length() == 0) {
        ui->lineEdit_ISBN->setStyleSheet(""); // Đặt lại màu về mặc định
    } else if (LocKiTu.length() == 10 || LocKiTu.length() == 13) {
        ui->lineEdit_ISBN->setStyleSheet("background-color: lightgreen;");
    } else {
        ui->lineEdit_ISBN->setStyleSheet("background-color: lightcoral;");
    }

}


void themdausach::on_lineEdit_tensach_textChanged(const QString &text) {
    string key = text.toStdString();
    string valid_key;
    bool lastWasSpace = false;
    bool isNewWord = true; // Để đánh dấu ký tự đầu của từ mới

    // Các ký tự hợp lệ bao gồm dấu nháy đơn, dấu chấm, dấu phẩy, và dấu hai chấm
    string specialChars = "'.,:";

    for (char c : key) {
        // Xử lý khoảng trắng, bỏ qua khoảng trắng thừa
        if (isspace(c)) {
            if (!lastWasSpace) {
                valid_key += ' '; // Thêm một dấu cách nếu trước đó không phải là dấu cách
                lastWasSpace = true;
                isNewWord = true; // Đánh dấu rằng ký tự tiếp theo sẽ là đầu từ mới
            }
        }
        // Xử lý ký tự chữ và số, và các ký tự đặc biệt hợp lệ
        else if (isalnum(c) || specialChars.find(c) != string::npos) {
            // Nếu là ký tự đầu tiên của từ mới, chuyển thành in hoa
            if (isNewWord && isalpha(c)) {
                valid_key += toupper(c);
                isNewWord = false; // Đã xử lý ký tự đầu của từ
            } else {
                valid_key += c; // Thêm ký tự hợp lệ
            }
            lastWasSpace = false; // Không còn khoảng trắng
        }
    }

    // Loại bỏ khoảng trắng đầu và cuối
    valid_key.erase(0, valid_key.find_first_not_of(" ")); // Loại bỏ khoảng trắng đầu

    // Cập nhật lại tên sách vào QLineEdit
    ui->lineEdit_tensach->setText(QString::fromStdString(valid_key));

    // In ra thông báo (có thể sử dụng logging thay vì cout trong ứng dụng GUI)
    cout << "Ten sach da duoc cap nhat: " << valid_key << endl;

    // Nếu key rỗng, không cần cập nhật
    if (valid_key.empty()) {
        cout << "Ten sach rong." << endl;
    }
}



void themdausach::on_lineEdit_theloai_textChanged(const QString &text)
{
    string key =  RemoveSpace(text);
    key = CapitalizeWords(key);
    ui->lineEdit_theloai->setText(QString::fromStdString(key));

    cout << "The loai da duoc cap nhat: " << key << endl;

    // Nếu key rỗng, không cần cập nhật
    if (key.empty()) {
        cout << "The loai rong." << endl;
    }
}

void themdausach::on_comboBox_vitri_currentTextChanged(const QString &text)
{
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

    cout << "Vi tri da duoc cap nhat: " << key << endl;

    // Nếu key rỗng, không cần cập nhật
    if (key.empty()) {
        cout << "Vi tri rong." << endl;
    }
}


void themdausach::on_spinBox_sotrang_valueChanged(int arg1)
{

}


void themdausach::on_lineEdit_tacgia_textChanged(const QString &text)
{
    string key =  RemoveSpace(text);
    key =CapitalizeWords(key);

    ui->lineEdit_tacgia->setText(QString::fromStdString(key));

    cout << "Tac gia da duoc cap nhat: " << key << endl;

    // Nếu key rỗng, không cần cập nhật
    if (key.empty()) {
        cout << "Tac gia rong." << endl;
    }
}

