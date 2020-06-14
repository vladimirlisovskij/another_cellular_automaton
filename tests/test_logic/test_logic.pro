QT += testlib
QT += core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tormentor.cpp \
    ../../server/logic_component.cpp \
    main.cpp

HEADERS += \
    ../../server/logic_component.h \
    tst_tormentor.h
