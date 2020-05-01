#ifndef GRAPH_COMPONENT_H
#define GRAPH_COMPONENT_H

#include "base_component.h"

#include <QWidget>
#include <QLayout>
#include <QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <algorithm>

QT_CHARTS_USE_NAMESPACE

class graph_component_leaf : public QChartView
{
/*
    * Реализует вспомогательный виджет графика функций
*/
    Q_OBJECT
private:
    QVector<QColor> lines_colors_;
    QVector<QVector<qint32>>values_;
    QVector<QLineSeries*> lines_;
    QValueAxis* axisY_;
    void clear_lines ();

public:
    graph_component_leaf (QString name, QVector<QColor> lines_colors, QWidget *parent = nullptr);

public slots:
    void set_data (QVector<QPair<QColor,qint32>> data);
    void clear ();
    void remove (QColor mark);
};

class graph_component : public BaseComponent
{
/*
    * Реализует компонент отвечающий за отрисовку в переданных ему [panel_component_leaf]
*/
    Q_OBJECT
private:
    qint32 visible_ = 0;
    QVector<graph_component_leaf*> comps_;

public:
    graph_component(QVector<graph_component_leaf*> comps, QWidget* parent = nullptr);

public slots:
    void show (qint32 num);
    void set_data (QVector<QPair<QColor,QVector<qint32>>> data);
    void clear ();
    void remove (QColor mark);
};

#endif // GRAPH_COMPONENT_H
