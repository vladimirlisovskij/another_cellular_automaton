QT += testlib
QT += core gui widgets charts
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tormentor.cpp \
    ../../client/graph_component.cpp \
    main.cpp

HEADERS += \
    ../../client/base_component.h \
    ../../client/graph_component.h \
    tst_tormentor.h
