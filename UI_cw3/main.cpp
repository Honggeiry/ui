#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QWidget { background-color: #A9A9A9; }");
    MainWindow w;

    w.show();
    return a.exec();
}
