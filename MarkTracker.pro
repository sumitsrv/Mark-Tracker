CONFIG += console
CONFIG += c++11

SOURCES += main.cpp \
    frameprocessor.cpp \
    trackingmanager.cpp

HEADERS += \
    frameprocessor.h \
    trackingmanager.h

INCLUDEPATH += /usr/local/include/
LIBS += /usr/local/lib/*.so.2.4.8
