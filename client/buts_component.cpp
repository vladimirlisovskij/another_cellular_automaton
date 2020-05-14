#include "buts_component.h"

start_component::start_component(QString name1, QString name2, QWidget *parent)
    : BaseComponent(parent)
    , _name1(name1)
    , _name2(name2)
    , _is_run(false)
    , _but(new QPushButton(_name1, this))
{
    _but->setFixedSize(128, 30);
    this->setFixedSize(128, 30);
    connect(_but, &QPushButton::clicked, this, &start_component::start_stop);
}

void start_component::stop()
{
    _is_run = false;
    _but->setText(_name1);
    QJsonObject res {{"type", "stop"}};
    emit notify(res);
}

void start_component::start_stop()
{
    _is_run = !_is_run;
    _but->setText(_is_run ? _name2 : _name1);
    QJsonObject res {{"type", (_is_run ? "start" : "stop")}};
    emit notify(res);
}

restart_component::restart_component(QString name, QWidget *parent)
    : BaseComponent(parent)
{
    QPushButton* but = new QPushButton(name, this);
    but->setFixedSize(128, 30);
    this->setFixedSize(128, 30);
    connect(but, &QPushButton::clicked, this, &restart_component::ping);
}

void restart_component::ping()
{
    QJsonObject res {{"type", "restart"}};
    emit notify(res);
}
