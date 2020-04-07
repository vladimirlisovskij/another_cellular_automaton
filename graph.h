// **************************
// Позволяет рисовать графики
// **************************

#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QLayout>
#include <QValueAxis>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <algorithm>

QT_CHARTS_USE_NAMESPACE

class graph : public QChartView
{
    Q_OBJECT
public:
    graph(QString, QVector<QColor>, QWidget *parent = nullptr);

public slots:
    void clear ();
    void del_line (QColor);
    void set_data (QVector<QPair<QColor,qint32>>);

private:
    const QVector<QColor> free_colors;
    QVector<QVector<qint32>> values;
    QValueAxis *axisY;
    qint32 iter = 1;
    QVector<QLineSeries*> lines;
    QChart* charts;
    void clear_lines ();

};

#endif // GRAPH_H
