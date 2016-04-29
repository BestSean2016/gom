TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include
INCLUDEPATH += /home/sean/projects/googletest/googletest/include
LIBS += -L /home/sean/projects/googletest/build/build/googlemock/gtest -lgtest -lgtest_main -lpthread

SOURCES += \
    test-case-1.cpp \
    ../libgom/datetime.cpp \
    ../libgom/getopt.cpp \
    ../libgom/randomwalk.cpp

HEADERS += \
    /home/sean/projects/googletest/googletest/include/gtest/gtest.h
