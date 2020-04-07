// ********************************************************************
// Содержит в себе набор графиков и возможности переключения между ними
// ********************************************************************

#ifndef SUPER_CHART_H
#define SUPER_CHART_H

#include <QWidget>
#include <graph.h>

class super_chart : public QWidget
{
    Q_OBJECT
public:
    explicit super_chart(QVector<QColor>, QWidget *parent = nullptr);

public slots:
    void set_data (QVector<QPair<QColor,QVector<qint32>>>);
    void clear ();
    void set_visible (qint32);

private:
    qint32 visible = 0;
    QVector<graph*> charts;
};

#endif // SUPER_CHART_H
