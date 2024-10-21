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

string RemoveExtraSpaces(const string& key) {
    string valid_key;
    bool lastWasSpace = false;

    // Loại bỏ khoảng trắng ở đầu chuỗi
    size_t start = 0;
    while (start < key.length() && isspace(key[start])) {
        start++;
    }

    // Loại bỏ khoảng trắng ở cuối chuỗi
    size_t end = key.length();
    while (end > start && isspace(key[end - 1])) {
        end--;
    }

    // Lặp qua các ký tự trong chuỗi đã loại bỏ khoảng trắng
    for (size_t i = start; i < end; ++i) {
        char c = key[i];
        if (isspace(c)) {
            if (!lastWasSpace) {
                valid_key += ' '; // Thêm chỉ một khoảng trắng
                lastWasSpace = true;
            }
        } else {
            valid_key += c; // Thêm ký tự không phải khoảng trắng
            lastWasSpace = false;
        }
    }

    return valid_key;
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
    string tensachStd = tensach.toStdString();
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

    // Loại bỏ khoảng trắng thừa sau khi xác thực
    isbnStd = RemoveExtraSpaces(isbnStd);
    tensachStd = RemoveExtraSpaces(tensachStd);
    tacgiaStd = RemoveExtraSpaces(tacgiaStd);
    theloaiStd = RemoveExtraSpaces(theloaiStd);
    vitriStd = RemoveExtraSpaces(vitriStd);

    // Gọi hàm ThemDauSach với các tham số đã chuyển đổi
    ThemDauSach(danh_sach_dau_sach, isbnStd, tensachStd, sotrang, tacgiaStd, namsx, theloaiStd, danh_muc_sach, 0, vitriStd);

    // Hiển thị thông tin đã nhập
    QString infoMessage = QString("Thông tin đã nhập:\nISBN: %1\nTên sách: %2\nTác giả: %3\nThể loại: %4\nSố trang: %5\nNăm xuất bản: %6\nVị trí: %7")
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

