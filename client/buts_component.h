#ifndef BUTS_COMPONENT_H
#define BUTS_COMPONENT_H

#include <base_component.h>
#include <QPushButton>

class start_component : public BaseComponent
{
/*
    * Реализует кнопку старта
*/
public:
    start_component(QString name, QWidget* parent = nullptr);

public slots:
    void ping ();
};

class restart_component : public BaseComponent
{
/*
    * Реализует кнопку сброса
*/
public:
    restart_component(QString name, QWidget* parent = nullptr);

public slots:
    void ping ();
};

#endif // BUTS_COMPONENT_H
