QT += testlib
QT -= gui
QT += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_history_test_class_serverfunctions.cpp \
    ../server/serverfunctions.cpp \
    ../server/database.cpp


HEADERS += \
    ../server/database.h \
    ../server/serverfunctions.h

${QT_LIBRARIES}
${QT_QTTEST_LIBRARY}
