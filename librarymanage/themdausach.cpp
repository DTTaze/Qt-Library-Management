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

string CapitalizeWords(const string& str) {
    string result;
    bool isNewWord = true; // Kiem tra co pha ki tu dau tien cua tu

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];

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

void themdausach::on_pushButton_clicked() {

    QString ISBN = ui->lineEdit_ISBN->text().simplified();
    QString tensach = ui->lineEdit_tensach->text().simplified();
    QString tacgia = ui->lineEdit_tacgia->text().simplified();
    QString theloai = ui->lineEdit_theloai->text().simplified();
    QString vitri = ui->lineEdit_vitri->text().simplified();
    int sotrang = ui->spinBox_sotrang->value();
    int namsx = ui->spinBox_namsb->value();

    // chuyen sang string
    string isbnStd = ISBN.toStdString();
    std::string tensachStd = CapitalizeWords(tensach.toStdString()); // Chuyển đổi tên sách
    string tacgiaStd = tacgia.toStdString();
    string theloaiStd = theloai.toStdString();
    string vitriStd = vitri.toStdString();

    // Mang dau vao va mang thong bao
    string inputs[] = {isbnStd, tensachStd, tacgiaStd, theloaiStd, vitriStd};
    string tenloi[] = {"ISBN","Tên sách", "Tác giả", "Thể loại", "Vị trí"};
    QString messages[] = {
        "Bạn chưa điền ISBN.",
        "Bạn chưa điền tên sách.",
        "Bạn chưa điền tên tác giả.",
        "Bạn chưa điền thể loại.",
        "Bạn chưa điền vị trí."
    };

    // Kiem tra
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

    if (sotrang <= 0) {
        QMessageBox::warning(this, "Lỗi", "Số trang phải lớn hơn 0.");
        return;
    }

    if (namsx <= 0) {
        QMessageBox::warning(this, "Lỗi", "Năm xuất bản không hợp lệ.");
        return;
    }

    // Gọi hàm ThemDauSach với các tham số đã chuyển đổi
    ThemDauSach(danh_sach_dau_sach, isbnStd, tensachStd, sotrang, tacgiaStd, namsx, theloaiStd, danh_muc_sach, 0, vitriStd);
    int index =0;
    for(; index < danh_sach_dau_sach.demsach && danh_sach_dau_sach.node[index]->ISBN != isbnStd;index++);

    string ma_sach = danh_sach_dau_sach.node[index]->dms->masach;
    // Hiển thị thông tin đã nhập
    QString infoMessage = QString("Thông tin đã nhập:\nISBN: %1\nTên sách: %2\nTác giả: %3\nThể loại: %4\nSố trang: %5\nNăm xuất bản: %6\nVị trí: %7\nTrạng Thái: Cho mượn được\n Mã sách: %8")
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
    // Chuyển đổi QString sang string
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

    // Xóa khoảng trắng ở đầu và cuối chuỗi
    key.erase(0, key.find_first_not_of(" \t\n\r")); // xóa khoảng trắng đầu

    // Cập nhật lại tên sách vào QLineEdit
    ui->lineEdit_tensach->setText(QString::fromStdString(key));

    // In ra thông báo (có thể sử dụng logging thay vì cout trong ứng dụng GUI)
    cout << "Ten sach da duoc cap nhat: " << key << endl;

    // Nếu key rỗng, không cần cập nhật
    if (key.empty()) {
        cout << "Ten sach rong." << endl;
    }
}



