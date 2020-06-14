#include "tst_tormentor.h"

kit (tormentor) has (data_test)
{
    for (auto i : graph->comps_) {
        for (auto j : i->values_) {
            QCOMPARE(j.front(), data-10);
            QCOMPARE(j.last(), data-1);
        }
    }
}

kit (tormentor) has (max_test) {
    qint32 max = graph->comps_[0]->axisY_->max();
    QCOMPARE(max, data+9);
}

tormentor::tormentor()
{
    const QVector<QColor> free_colors ({Qt::red, Qt::blue, Qt::magenta, Qt::yellow});
    QVector<graph_component_leaf*> graph_leafs;
    QString name = "123";
    for (qint32 i = 0; i < 4; ++i)
        graph_leafs.push_back
                (new graph_component_leaf(name, free_colors));
    graph = new graph_component(graph_leafs);

    data = 100;
    for (qint32 i = 0; i < data; ++i) {
        QHash<QString,QVector<qint32>> graph_data;
        for (auto j : free_colors) {
            graph_data.insert(j.name(), QVector<qint32>{i,i,i,i});
        }
        graph->set_data(graph_data);
    }

}

tormentor::~tormentor()
{
    delete graph;
}
