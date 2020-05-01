#ifndef TABLE_COMPONENT_H
#define TABLE_COMPONENT_H

#include"base_component.h"

#include <QTableWidget>
#include <QHeaderView>

class table_component : public BaseComponent
{
/*
    * Реализует таблицу со статистикой
*/
public:
    enum ans {SWITCH, REMOVE};
    struct row {
        QColor color;
        QVector<qint32> stats;
    };
    table_component(QVector<QColor> colors, QVector<QString> labels, QWidget* parent = nullptr);

public slots:
    void clear ();
    void set_data (row data);

private slots:
    void clicked_row (QTableWidgetItem*);

private:
    const qint32 size_;
    QVector<QColor> colors_;
    QTableWidget* table_;

};

#endif // TABLE_COMPONENT_H
