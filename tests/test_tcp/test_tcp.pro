QT += testlib
QT += core gui widgets network
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_torment.cpp \
    ../../client/client_component.cpp \
    main.cpp

HEADERS += \
    ../../client/base_component.h \
    ../../client/client_component.h \
    tst_torment.h
