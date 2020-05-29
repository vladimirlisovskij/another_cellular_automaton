QT += testlib
QT += core gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_tormentor.cpp \
    main.cpp

HEADERS += \
    tst_tormentor.h
