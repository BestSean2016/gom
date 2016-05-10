TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ../include
LIBS += -lpthread -lta_lib

SOURCES += datagen.cpp \
    ../libgom/getopt.cpp \
    ../libgom/randomwalk.cpp \
    ../libgom/datetime.cpp \
    ../libgom/indicator.cpp \
    ../libgom/stdlib-mql4.cpp \
    ../libgom/AccountInfo.cpp \
    ../libgom/Checkup.cpp \
    ../libgom/Conversion.cpp \
    ../libgom/Math.cpp \
    ../libgom/string-ops.cpp \
    ../libgom/TimeSeries.cpp \
    ../libgom/Trading.cpp \
    ../libgom/mql4-data.cpp

HEADERS += \
    ../include/StdLibErr.h \
    ../include/mql4-def.h \
    ../include/stderror-mql4.h \
    ../include/libgom.h \
    ../include/datetime.h \
    ../include/AccountInfo.h \
    ../include/Checkup.h \
    ../include/Conversion.h \
    ../include/Math.h \
    ../include/stdlib-mql4.h \
    ../include/string-ops.h \
    ../include/Tradeing.h \
    ../include/indicator.h \
    ../include/mql4-data.h

