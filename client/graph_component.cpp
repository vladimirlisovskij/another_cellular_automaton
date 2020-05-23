#include "graph_component.h"

void graph_component_leaf::clear_lines()
{
    for (auto& i : lines_) i->clear();
}

graph_component_leaf::graph_component_leaf(QString name, QVector<QColor> lines_colors, QWidget *parent)
    : QChartView (parent)
    , lines_colors_ (lines_colors)
    , axisY_ (new QValueAxis)
{
    QChart* charts = new QChart;
    for (qint32 i = 0; i < lines_colors.size(); ++i)
    {
        lines_.push_back(new QLineSeries);
        lines_[i]->setColor(lines_colors[i]);
        QPen pen = lines_[i]->pen();
        pen.setWidth(10);
        lines_[i]->setPen(pen);
        charts->addSeries(lines_[i]);
        values_.push_back(QVector<qint32>{0});
    }
    axisY_->setRange(0, 100);
    charts->addAxis(axisY_, Qt::AlignLeft);
    charts->legend()->hide();
    charts->setTitle(name);
    this->setChart(charts);
    this->setFixedSize(15*30, 30*10);
}

void graph_component_leaf::set_data(QHash<QString,qint32> data)
{
    if (data.size())
    {
        clear_lines();
        for (auto i = data.begin(); i != data.end(); ++i)
        {
            qint32 line_index = lines_colors_.indexOf(QColor(i.key()));
            values_[line_index].push_back(i.value());
            if (values_[line_index].size() > 10) values_[line_index].pop_front();
        }
        QVector<qint32> temp;
        for (auto i : values_) temp.push_back(*std::max_element(i.begin(), i.end()));
        double max_value = *std::max_element(temp.begin(), temp.end()) + 10;
        for (qint32 i = 0; i < lines_colors_.size(); ++i)
        {
            for (auto j = 0; j < values_[i].size(); ++j) {
                lines_[i]->append(j/10.0, values_[i][j]/max_value);
            }
        }
        axisY_->setRange(0, max_value);
    }
}

void graph_component_leaf::clear()
{
    axisY_->setRange(0, 100);
    clear_lines();
    for (auto& i : values_)
    {
        i.clear();
        i.push_back(0);
    }
}

void graph_component_leaf::remove(QColor mark)
{
    lines_[lines_colors_.indexOf(mark)]->clear();
    values_[lines_colors_.indexOf(mark)].clear();
}

graph_component::graph_component(QVector<graph_component_leaf*> comps, QWidget *parent)
    : BaseComponent (parent)
    , comps_ (comps)
{
    QVBoxLayout* lay = new QVBoxLayout;
    for (auto& i : comps_)
    {
        lay->addWidget(i);
        i->hide();
    }
    comps[0]->show();
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    this->setLayout(lay);
    this->setFixedSize(15*30, 30*10);
}

void graph_component::show(qint32 num)
{
    comps_[visible_]->hide();
    comps_[num]->show();
    visible_ = num;
}

void graph_component::set_data(QHash<QString,QVector<qint32>> data)
{
    QVector<QHash<QString,qint32>> res;
    for (qint32 i = 0; i < comps_.size(); ++i) res.push_back(QHash<QString,qint32> {});
    for (auto i = data.begin(); i != data.end(); ++i)
        for (qint32 j = 0; j < comps_.size(); ++j)
            res[j].insert(i.key(), i.value()[j]);
    for (qint32 i = 0; i < comps_.size(); ++i) comps_[i]->set_data(res[i]);
}

void graph_component::clear()
{
    for (auto& i : comps_) i->clear();
}

void graph_component::remove(QColor mark)
{
    for (auto& i : comps_) i->remove(mark);
}
