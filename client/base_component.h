#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class BaseComponent : public QWidget{
/*
    * Базовый класс компонентов имеющих графическую оболочку
*/
    Q_OBJECT
public:
    explicit BaseComponent (QWidget* parent = nullptr) : QWidget(parent) {};

signals:
    void notify (QJsonObject);
};

#endif // BASECOMPONENT_H
