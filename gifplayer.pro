QT       += core gui network webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gifplayer
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
        src/testwidget.cpp \
        src/gifdownloader.cpp \
        src/gifloader.cpp \
        src/gifplayer.cpp \
        src/utils.cpp \
        src/site.cpp \
        src/hahasite.cpp \
        src/gifurlextractor.cpp \
        src/gifhouse.cpp

HEADERS  += src/mainwindow.h \
            src/testwidget.h \
            src/gifdownloader.h \
            src/gifloader.h \
            src/gifplayer.h \
            src/utils.h \
            src/site.h \
            src/hahasite.h \
            src/gifurlextractor.h \
            src/gifhouse.h

FORMS    += ui/mainwindow.ui \
            ui/testwidget.ui

RESOURCES += \
    images.qrc
