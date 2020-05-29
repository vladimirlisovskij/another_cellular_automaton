QT += testlib
QT += core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tormentor.cpp \
    ../../client/panel_component.cpp \
    main.cpp

HEADERS += \
    ../../client/base_component.h \
    ../../client/panel_component.h \
    tst_tormentor.h
