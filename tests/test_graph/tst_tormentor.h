#ifndef TST_TORMENTOR_H
#define TST_TORMENTOR_H
#define cases private Q_SLOTS
#define fields public
#define methods public Q_SLOTS
#define stage(a) void a()
#define test_kit(a) class a : public QObject
#define kit(a) void a::
#define has(a) a()

#include <QtTest>
#include <QCoreApplication>

#include "../../client/graph_component.h"

test_kit(tormentor)
{
    Q_OBJECT
cases:
    stage(data_test);
    stage(max_test);

fields:
    qint32 data;
    graph_component* graph;
    tormentor();
    ~tormentor();
};

#endif // TST_TORMENTOR_H
