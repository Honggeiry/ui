#include "mainwindow.h"
#include <QApplication>
#include <QColor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet("QWidget { background-color: rgb(127, 139, 172); }");

    MainWindow w;

    w.show();
    return a.exec();
}
