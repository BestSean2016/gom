TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include

SOURCES += \
    test-case-1.cpp \
    ../libgom/datetime.cpp \
    ../libgom/getopt.cpp \
    ../libgom/randomwalk.cpp

HEADERS += \
    catch.hpp
