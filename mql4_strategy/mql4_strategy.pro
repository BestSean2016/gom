TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include

SOURCES += main.cpp \
    MACD_Sample.cpp

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
    ../include/Tradeing.h

