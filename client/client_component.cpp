#include "client_component.h"

client_component::client_component(QHostAddress ip, qint32 port, QWidget *parent)
    : BaseComponent(parent)
    , _soc(new QTcpSocket(this))
    , _lab(new QLabel("Disconnected", this))
    , _but(new QPushButton("Connect!", this))
    , _ip(ip)
    , _port(port)
{
    this->setFixedSize(15*14, 25);
    this->setStyleSheet("background-color: red;");
    QHBoxLayout* lay = new QHBoxLayout;
    _lab->setFixedSize(15*7,25);
    _but->setFixedSize(15*7,25);
    lay->addWidget(_lab);
    lay->addWidget(_but);
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    this->setLayout(lay);
    _lab->setAlignment(Qt::AlignCenter);
    connect(_soc, &QTcpSocket::connected, this, &client_component::connected);
    connect(_soc, &QTcpSocket::disconnected, this, &client_component::disconnected);
    connect(_soc, &QTcpSocket::readyRead, this, &client_component::ready_read);
    connect(_but, &QPushButton::clicked, this, &client_component::start);
}

void client_component::write(QJsonObject data)
{
    if (!_soc->isOpen()) return;
    QString res = QString::fromUtf8(QJsonDocument(data).toJson());
    qDebug() << "\nWRITE";
    qDebug() << data;
    _soc->write(res.toUtf8());
    _soc->flush();
}

void client_component::start()
{
    _soc->disconnectFromHost();
    _soc->connectToHost(_ip, _port);
    if (!_soc->waitForConnected(300)) _soc->close();
}

void client_component::connected()
{
    _lab->setFixedSize(15*14,25);
    _but->hide();
    _lab->setText("Connected");
    this->setStyleSheet("background-color: green;");
}

void client_component::disconnected()
{
    _soc->close();
    _but->show();
    _lab->setText("Disconnected");
    _lab->setFixedSize(15*7,25);
    this->setStyleSheet("background-color: red;");
}

void client_component::ready_read()
{
    QByteArray data = _soc->readAll();
    QString temp = QString(data).toUtf8();
    _json += temp;
    if (_json.back() == '*')
    {
        _json.chop(1);
        QJsonDocument doc = QJsonDocument::fromJson(QString(_json).toUtf8());
        QJsonObject obj = doc.object();
        qDebug() << "\nREAD";
        qDebug() << obj;
        emit notify(obj);
        _json.clear();
    }
}
