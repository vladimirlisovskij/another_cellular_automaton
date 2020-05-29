QT += testlib
QT += core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../../client/buts_component.cpp \
    main.cpp \
    tst_torment.cpp

HEADERS += \
    ../../client/base_component.h \
    ../../client/buts_component.h \
    tst_torment.h
