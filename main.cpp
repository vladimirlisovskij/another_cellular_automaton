#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w (60, 60);  // размеры поля
    w.show();
    return a.exec();
}
