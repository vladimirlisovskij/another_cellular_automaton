#include "tst_torment.h"

kit (torment) has (write_read_test)
{
    obj = {{"type","test"},{"type","test"},{"type","test"},
           {"type","test"},{"type","test"},{"type","test"},
           {"type","test"},{"type","test"},{"type","test"},
           {"type","test"},{"type","test"},{"type","test"},
           {"type","test"},{"type","test"},{"type","test"},
           {"type","test"},{"type","test"},{"type","test"}};
    this->start();
    QThread::sleep(3);
    this->quit();
    QCOMPARE(readed, obj);
}


tst_serv::tst_serv() : QThread(nullptr)
{
}

void tst_serv::run()
{
    serv = new QTcpServer;
    connect(serv, &QTcpServer::newConnection, this, &tst_serv::on_connect, Qt::DirectConnection);
    connect(this, &QThread::quit, serv, &QTcpServer::deleteLater);
    serv->listen(QHostAddress::Any, 4242);
    exec();
}

void tst_serv::on_connect()
{
    is_con = true;
    soc = serv->nextPendingConnection();
    connect(soc, &QTcpSocket::readyRead, this, &tst_serv::on_read, Qt::DirectConnection);
}

void tst_serv::on_read()
{
    QString data = soc->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    last_call =  doc.object();
    QString str = doc.toJson(QJsonDocument::Compact);
    for (auto i : str) soc->write(QString(i).toUtf8());
    soc->write("*");
    soc->flush();
}

torment::torment()
    : serv (new tst_serv)
{
    serv->start();
    QThread::sleep(1);
}

torment::~torment()
{
    serv->quit();
    delete cli;
    delete serv;
}

void torment::on_read(QJsonObject data)
{
    readed = data;
}

void torment::run()
{
    cli = new client_component (QHostAddress("127.0.0.1"), 4242);
    connect(cli, &client_component::notify, this, &torment::on_read, Qt::DirectConnection);
    connect(this, &torment::quit, cli, &client_component::deleteLater);
    cli->start();
    cli->write(obj);
    exec();
}
