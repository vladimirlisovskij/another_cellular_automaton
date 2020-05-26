#include "server.h"

server::server(QObject *parent)
    : QObject(parent)
    , _server(new QTcpServer(this))
{
    connect(_server, &QTcpServer::newConnection, this, &server::on_new_connection);
}

void server::on_new_connection()
{
    qDebug() << "Get new connection";
    QTcpSocket* soc = _server->nextPendingConnection();
    qint32 id = soc->socketDescriptor();
    socket_thread* socket_th = new socket_thread(id);
    connect(socket_th, &socket_thread::finished, socket_th, &socket_thread::deleteLater);
    socket_th->start();
}

void server::start(qint32 port)
{
    _server->listen(QHostAddress::Any, port);
    qDebug() << "Server start at port " << port;
}
