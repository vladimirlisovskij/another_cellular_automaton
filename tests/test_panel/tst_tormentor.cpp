#include "tst_tormentor.h"

kit (tormentor) has (test_case1)
{
    for (qint32 i = 0; i < 100; ++i) panel->comps_[i]->val_->setValue(i);
    panel->get_data();
    QJsonObject obj;
    for (qint32 i = 0; i < 100; ++i) obj[QString::number(i)] = i;
    QCOMPARE(last_call, obj);
}

tormentor::tormentor()
{
    QVector<QString> list;
    list.reserve(100);
    for (qint32 i = 0; i < 100; ++i) list.push_back(QString::number(i));
    QVector<panel_component_leaf*> leafs;
    leafs.reserve(100);
    for (auto i : list) leafs.push_back(new panel_component_leaf(i, 0, 100));
    panel = new panel_component(leafs, "123");
    connect(panel, &panel_component::notify, this, &tormentor::write);
}

tormentor::~tormentor()
{
    delete panel;
}

void tormentor::write(QJsonObject data)
{
    last_call = data;
}
