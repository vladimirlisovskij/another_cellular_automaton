#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <socket_thread.h>

class server : public QObject
{
/*
    * Реализует сервер
*/
    Q_OBJECT
public:
    explicit server(QObject* parent = nullptr);

public slots:
    void on_new_connection();
    void start(qint32 port);

private:
    QTcpServer* _server;
};

#endif // SERVER_H
