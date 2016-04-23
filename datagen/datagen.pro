TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ../include

SOURCES += datagen.cpp \
    ../libgom/getopt.cpp \
    ../libgom/randomwalk.cpp

HEADERS += \
    includes/stderror-mql4.h \
    includes/mql4-def.h \
    include/mql4-def.h \
    include/stderror-mql4.h \
    include/StdLibErr.h \
    ../include/StdLibErr.h \
    ../include/mql4-def.h \
    ../include/stderror-mql4.h \
    ../include/libgom.h

