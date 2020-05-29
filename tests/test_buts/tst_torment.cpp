#include "tst_torment.h"

kit (torment) has (clicked_test)
{
    bool temp = true;
    QJsonObject obj1 {{"type", "start"}};
    QJsonObject obj2 {{"type", "stop"}};
    for (int i = 0; i < 10; ++i) {
        QTest::mouseClick(but->_but, Qt::LeftButton);
        QCOMPARE(but->_is_run, temp);
        QCOMPARE(last_call, temp ? obj1 : obj2);
        temp = !temp;
    }
}

kit (torment) has (stop_test)
{
    QJsonObject obj {{"type", "stop"}};
    for (qint32 i = 0; i < 10; ++i) {
        for (int j = 0; j < i; ++j) QTest::mouseClick(but->_but, Qt::LeftButton);
        but->stop();
        QCOMPARE(but->_is_run, false);
        QCOMPARE(last_call, obj);
    }
}




torment::torment()
    : but(new start_component("start", "stop"))
{
    connect(but, &start_component::notify, this, &torment::call);
}

torment::~torment()
{
    delete but;
}

void torment::call(QJsonObject data)
{
    this->last_call = data;
}
