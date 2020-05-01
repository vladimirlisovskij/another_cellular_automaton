#ifndef CLIENT_COMPONENT_H
#define CLIENT_COMPONENT_H

#include <QLabel>
#include <QPushButton>
#include <QTcpSocket>
#include <base_component.h>
#include <QHBoxLayout>
#include <qhostaddress.h>

class client_component : public BaseComponent
{
/*
    * Реализует копмонент отвечающий за связь с сервером
*/
public:
    client_component(QHostAddress ip, qint32 port, QWidget* parent = nullptr);
    void write(QJsonObject data);

private slots:
    void start();
    void connected();
    void disconnected();
    void ready_read();

private:
    QTcpSocket* _soc;
    QLabel* _lab;
    QPushButton* _but;
    QHostAddress _ip;
    qint32 _port;
    QString _json;
};

#endif // CLIENT_COMPONENT_H
