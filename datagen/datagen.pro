TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ../include

SOURCES += datagen.cpp \
    ../libgom/getopt.cpp \
    ../libgom/randomwalk.cpp \
    ../libgom/datetime.cpp

HEADERS += \
    ../include/StdLibErr.h \
    ../include/mql4-def.h \
    ../include/stderror-mql4.h \
    ../include/libgom.h \
    ../include/datetime.h

