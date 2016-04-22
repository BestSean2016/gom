TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += include

SOURCES += main.cpp

HEADERS += \
    includes/stderror-mql4.h \
    includes/mql4-def.h \
    include/mql4-def.h \
    include/stderror-mql4.h \
    include/StdLibErr.h
