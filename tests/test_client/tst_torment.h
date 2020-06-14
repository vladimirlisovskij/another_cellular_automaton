#ifndef TST_TORMENT_H
#define TST_TORMENT_H
#define cases private Q_SLOTS
#define fields public
#define methods public Q_SLOTS
#define stage(a) void a()
#define test_kit(a) class a : public QThread
#define kit(a) void a::
#define has(a) a()

#include <QtTest>
#include <QCoreApplication>
#include <QTcpServer>

#include "../../client/client_component.h"

class tst_serv : public QThread
{
    Q_OBJECT

public:
    tst_serv();
    bool is_con = false;
    QTcpSocket* soc;
    QJsonObject last_call;
    QTcpServer* serv;

private:
    void run() override;

private slots:
    void on_connect();
    void on_read();
};

test_kit(torment)
{
    Q_OBJECT

signals:
    void noty (QJsonObject);

fields:
    client_component* cli;
    tst_serv* serv;
    QJsonObject readed;
    QJsonObject obj;
    torment();
    ~torment();

methods:
    void on_read(QJsonObject);
    void run() override;

cases:
    stage(write_read_test);
};

#endif // TST_TORMENT_H
