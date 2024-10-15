#include "librarymanagementsystem.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibraryManagementSystem w;
    w.show();
    w.setFixedSize(1000, 750);  // Đặt kích thước cố định cho cửa sổ (800x600)
    return a.exec();
}
