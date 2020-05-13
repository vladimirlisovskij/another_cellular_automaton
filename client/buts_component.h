#ifndef BUTS_COMPONENT_H
#define BUTS_COMPONENT_H

#include <base_component.h>
#include <QPushButton>
#include <QTimer>

class start_component : public BaseComponent
{
/*
    * Реализует кнопку старта
*/
public:
    start_component(QString name1, QString name2, QWidget* parent = nullptr);

private:
    QString _name1;
    QString _name2;
    bool _is_run;
    QPushButton* _but;
    QTimer* _timer;

public slots:
    void start_stop();

private slots:
    void ping ();
};

class restart_component : public BaseComponent
{
/*
    * Реализует кнопку сброса
*/
public:
    restart_component(QString name, QWidget* parent = nullptr);

private slots:
    void ping ();
};

#endif // BUTS_COMPONENT_H
