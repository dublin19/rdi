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

unix {
    LIBS += -L/usr/local/lib -lexiv2
    INCLUDEPATH += /usr/local/include
}

win32 {
    # using home built exiv2 which is installed inside the program files folder
    INCLUDEPATH += $$quote("C:/Program Files (x86)/exiv2/include")
    LIBS += $$quote("C:/Program Files (x86)/exiv2/lib/libexiv2.dll.a")
}