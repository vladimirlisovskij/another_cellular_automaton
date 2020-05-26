#ifndef SCREEN_COMPONENT_H
#define SCREEN_COMPONENT_H

#include"base_component.h"

#include <QTableWidget>
#include <QHeaderView>

class screen_component : public BaseComponent
{
/*
    * Реализует компонент, отвечающий за отрисовку игрового поля
    * Используется двойная буферизация
*/
private:
    const qint32 width;
    const qint32 height;
    QTableWidget* first_buf;
    QTableWidget* second_buf;

public:
    screen_component (qint32 width, qint32 height, QWidget* parent = nullptr);

public slots:
    void set_data (const QHash<QPair<qint32,qint32>,QPair<QColor,QString>>& data);
};

#endif // SCREEN_COMPONENT_H
