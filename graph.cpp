#include "graph.h"

graph::graph(QString name, QVector<QColor> colors, QWidget *parent)
    : QChartView(parent)
    , free_colors (colors)
    , axisY (new QValueAxis)
    , charts (new QChart)
{
    for (qint32 i = 0; i < free_colors.size(); ++i)
    {
        lines.push_back(new QLineSeries);
        lines[i]->setColor(free_colors[i]);
        QPen pen = lines[i]->pen();
        pen.setWidth(10);
        lines[i]->setPen(pen);
        charts->addSeries(lines[i]);
        values.push_back(QVector<qint32>{});
    }
    axisY->setRange(0, 100);
    charts->addAxis(axisY, Qt::AlignLeft);
    charts->legend()->hide();
    charts->setTitle(name);
    this->setChart(charts);
    this->setFixedSize(15*30, 30*10);
}

void graph::clear()
{
    axisY->setRange(0, 100);
    iter = 1;
    clear_lines();
    for (auto& i : values) i.clear();
}

void graph::del_line(QColor i)
{
    lines[free_colors.indexOf(i)]->clear();
}

void graph::set_data(QVector<QPair<QColor,qint32>> data)
{
    if (data.size())
    {
        clear_lines();
        for (auto i: data)
        {
            values[free_colors.indexOf(i.first)].push_back(i.second);
            if (iter > 10) values[free_colors.indexOf(i.first)].pop_front();
        }
        QVector<qint32> temp;
        for (auto i : values) temp.push_back(*std::max_element(i.begin(), i.end()));
        double max_value = *std::max_element(temp.begin(), temp.end()) + 10;
        for (qint32 i = 0; i < free_colors.size(); ++i)
        {
            for (auto j = 0; j < values[i].size(); ++j) {
                lines[i]->append(j/10.0, values[i][j]/max_value);
            }
        }
        axisY->setRange(0, max_value);
        ++iter;
    }
}

void graph::clear_lines()
{
    for (auto& i : lines) i->clear();
}
