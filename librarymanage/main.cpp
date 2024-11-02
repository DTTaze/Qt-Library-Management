#include "librarymanagementsystem.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LibraryManagementSystem w;
    w.show();
    return a.exec();
}
