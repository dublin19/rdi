QT += core gui widgets multimedia sql
TARGET = RawImageDisplayer
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp \
            MainWindow.cpp \
            EmbeddedImage.cpp \
            exif.cpp \
            imagepreview.cpp


HEADERS += MainWindow.h \
            EmbeddedImage.h \
            exif.h \
            imagepreview.h

LIBS += -L/usr/local/lib -lexiv2
INCLUDEPATH += /usr/local/include
