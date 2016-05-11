TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include
INCLUDEPATH += /home/sean/projects/googletest/googletest/include

LIBS += -L /home/sean/projects/googletest/build/build/googlemock/gtest -lgtest -lgtest_main -lpthread -lta_lib

SOURCES += \
    test-case-1.cpp \
    ../libgom/getopt.cpp \
    ../libgom/indicator.cpp \
    ../libgom/mql4-data.cpp \
    ../libgom/datetime.cpp \
    ../libgom/Trading.cpp

HEADERS += \
    /home/sean/projects/googletest/googletest/include/gtest/gtest.h \
    ../include/Tradeing.h \
    ../include/AccountInfo.h \
    ../include/Checkup.h \
    ../include/Conversion.h \
    ../include/datetime.h \
    ../include/indicator.h \
    ../include/libgom.h \
    ../include/Math.h \
    ../include/mql4-data.h \
    ../include/mql4-def.h \
    ../include/stderror-mql4.h \
    ../include/stdlib-mql4.h \
    ../include/string-ops.h
