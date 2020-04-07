#include "super_chart.h"

super_chart::super_chart(QVector<QColor> data, QWidget *parent)
    : QWidget (parent)
{
    QVector<QString> labs {"Number", "Speed", "Endurance", "Vitality", "Max vitality"};
    QVBoxLayout* lay = new QVBoxLayout;
    for (qint32 i = 0; i < 5; ++i)
    {
        charts.push_back(new graph(labs[i], data, this));
        if (i) charts[i]->hide();
        lay->addWidget(charts[i]);
    }
    lay->setContentsMargins(0,0,0,0);
    lay->setSpacing(0);
    this->setLayout(lay);
    this->setFixedSize(15*30, 30*10);
}

void super_chart::set_data(QVector<QPair<QColor,QVector<qint32>>> data)
{
    QVector<QVector<QPair<QColor,qint32>>> res;
    for (qint32 i = 0; i < 5; ++i) res.push_back(QVector<QPair<QColor,qint32>> {});
    for (auto i : data) for (qint32 j = 0; j < 5; ++j) res[j].push_back(QPair<QColor,qint32>{i.first, i.second[j+1]});
    for (qint32 i = 0; i < 5; ++i) charts[i]->set_data(res[i]);
}

void super_chart::clear()
{
    for (auto& i : charts) i->clear();
}

void super_chart::set_visible(qint32 i)
{
    charts[visible]->hide();
    charts[i]->show();
    visible = i;
}


