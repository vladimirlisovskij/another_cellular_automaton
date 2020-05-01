#include "buts_component.h"

start_component::start_component(QString name, QWidget *parent)
    : BaseComponent(parent)
{
    QPushButton* but = new QPushButton(name, this);
    but->setFixedSize(15*7, 30);
    this->setFixedSize(15*7, 30);
    connect(but, &QPushButton::clicked, this, &start_component::ping);
}

void start_component::ping()
{
    QJsonObject res {{"type", "next"}};
    emit notify(res);
}

restart_component::restart_component(QString name, QWidget *parent)
    : BaseComponent(parent)
{
    QPushButton* but = new QPushButton(name, this);
    but->setFixedSize(15*7, 30);
    this->setFixedSize(15*7, 30);
    connect(but, &QPushButton::clicked, this, &restart_component::ping);
}

void restart_component::ping()
{
    QJsonObject res {{"type", "restart"}};
    emit notify(res);
}
