CONFIG += console
CONFIG += c++11
QMAKE_CXXFLAGS += -m64
QMAKE_LFLAGS += -m64

SOURCES += \
    frameprocessor.cpp \
    trackingmanager.cpp \
    main.cpp \
    glmanager.cpp

HEADERS += \
    frameprocessor.h \
    trackingmanager.h \
    glmanager.h

#CONFIG += link_pkgconfig
#PKGCONFIG += opencv

INCLUDEPATH += /usr/local/include
LIBS += /usr/lib64/libglut.so.3.9.0 \
    /usr/local/lib/*.so \
    /usr/lib64/libGLU.so
