#include <QObject>
#include <QCoreApplication>
#include <server.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    server main_serv;
    main_serv.start(4242);
    return a.exec();
}
