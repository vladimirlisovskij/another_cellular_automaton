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

// add necessary includes here

test_kit(tormentor)
{
    Q_OBJECT
cases:
    stage(test_case1);

fields:
    tormentor();
    ~tormentor();
};

#endif // TST_TORMENTOR_H