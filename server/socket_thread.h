#ifndef SOCKET_THREAD_H
#define SOCKET_THREAD_H

#include<QObject>
#include<QTcpSocket>
#include<QThread>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<logic_component.h>

class socket_thread : public QThread
{
/*
    * Реализует класс отвечающий за связь с клиентом
    * Выполняется в отдельном потоке
*/
    Q_OBJECT
public:
    explicit socket_thread(qint32 socket_id, QObject *parent = nullptr);

signals:
    void is_finished(qint32 id);

private slots:
    void write(QJsonObject data);
    void read_data();

private:
    void run() override;
    const int _socket_id;
    QTcpSocket* _soc;
    logic_component* _logic;
    QString _type;

};

#endif // SOCKET_THREAD_H
