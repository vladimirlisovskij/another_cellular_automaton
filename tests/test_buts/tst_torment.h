#ifndef TST_TORMENT_H
#define TST_TORMENT_H
#define cases private Q_SLOTS
#define fields public
#define methods public Q_SLOTS
#define stage(a) void a()
#define test_kit(a) class a : public QObject
#define kit(a) void a::
#define has(a) a()

#include <QtTest>
#include <QCoreApplication>

#include "../../client/buts_component.h"

test_kit(torment)
{
    Q_OBJECT

cases:
    stage(clicked_test);
    stage(stop_test);

fields:
    start_component* but;
    QJsonObject last_call;
    torment();
    ~torment();

methods:
    void call(QJsonObject);
};

#endif // TST_TORMENT_H
