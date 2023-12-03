#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QWidget { background-color: rgb(62, 76, 139); }");
    MainWindow w;

    w.show();
    return a.exec();
}
