TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include

SOURCES += main.cpp \
    MACD_Sample.cpp \
    ../libgom/AccountInfo.cpp \
    ../libgom/Checkup.cpp \
    ../libgom/Conversion.cpp \
    ../libgom/datetime.cpp \
    ../libgom/getopt.cpp \
    ../libgom/indicator.cpp \
    ../libgom/Math.cpp \
    ../libgom/randomwalk.cpp \
    ../libgom/stdlib-mql4.cpp \
    ../libgom/string-ops.cpp \
    ../libgom/TimeSeries.cpp \
    ../libgom/Trading.cpp \
    ../libgom/mql4-data.cpp

HEADERS += \
    ../include/datetime.h \
    ../include/libgom.h \
    ../include/mql4-def.h \
    ../include/stderror-mql4.h \
    ../include/stdlib-mql4.h \
    ../include/AccountInfo.h \
    ../include/Checkup.h \
    ../include/Conversion.h \
    ../include/Math.h \
    ../include/string-ops.h \
    ../include/Tradeing.h \
    ../include/indicator.h

