**INFORMATION:** This thing now works on Windows together with MinGW-W64 (and Qt 5.12.7 LTS)! I am going to update this README as soon as I finish focus on my current work... If you want to experiment on your own checkout [this](https://github.com/FMeinicke/QtRaw/issues/1) and [this](https://github.com/Exiv2/exiv2/issues/1101) and have fun!

And by the way, also Canon CR3 is supported (except from exiv2 side, but I think we use a workaround with exiftool...)!

## What is this?

I do not think anyone is going to stumble upon this, but anyway if this possibly happen.. welcome!

RDI or RawImageDisplayer (yes, swapped the D and the I by accident) is a little testing application which tries to display a RAW image and the given EXIF metadata of it. It is not an application which goes into production, more like a playground which works and grow from time to time. Probably some of the things I try out here are going into my photo application later on...

Oh, and remember, something here laying around (such as files, codes and classes) could be possibly unused or were commented...

**WARNING:** Use on your own warranty! The application is really unstable and as stated a playground. Only use it if you really know what to do!

### Building

Before building RDI I should state that I work on macOS Catalina. This means this build guide heavily relies on macOS as platform itself whilst that I use [homebrew](https://brew.sh) to install and update most of my packages, so:

- [Qt 5.14.0](https://download.qt.io/) *(I strongly recommend exactly this version because it's my macOS install base, switching so LTS somewhat later)*
- [Homebrew](https://brew.sh) *(you could possibly manually build all these things, but thats not what I do in the moment)*
- [Git](https://git-scm.com) *(you could also use the Git which is shipped with macOS)*
- [Xcode Command Line Tools](http://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/) *(just install Qt and you get what you need)*

After that you should clone the repo with ``git clone https://github.com/dublin19/rdi.git``.

#### Building QtRaw with patches

[QtRaw](https://gitlab.com/mardy/qtraw) is a wonderful plugin which integrates [libraw](https://www.libraw.org) into Qt's ImageFormat ecosystem. To use QtRaw you'll need to manually build it.

```
brew install libraw
git clone https://gitlab.com/mardy/qtraw
cd qtraw
mkdir build
```

**Leave this terminal open!** Now you need to manually patch the ``src.pro``-file which can be found in the ``src``folder of the cloned ``qtraw``repository. Open it up with **any text editor BUT NOT with QtCreator!**

Replace it with the following content:

```
include(../common-config.pri)

TARGET  = qtraw
TEMPLATE = lib
CONFIG += plugin
DESTDIR = imageformats

#
#PKGCONFIG += \
#    libraw
#

INCLUDEPATH += /usr/local/include/libraw
LIBS += -L/usr/local/lib -lraw

LIBS += -lraw

HEADERS += \
    datastream.h \
    raw-io-handler.h
SOURCES += \
    datastream.cpp \
    main.cpp \
    raw-io-handler.cpp
OTHER_FILES += \
    raw.json

target.path += $$[QT_INSTALL_PLUGINS]/imageformats
INSTALLS += target


# For KDE, install a .desktop file with metadata about the loader
#kde_desktop.files = raw.desktop
#kde_desktop.path = $${INSTALL_KDEDIR}/share/kde4/services/qimageioplugins/
#INSTALLS += kde_desktop
```

After that get back to the opened terminal.

```
cd build
qmake ..
make
sudo make install
```

This should install QtRaw as a QtImageFormat-plugin and you can now use it in any application!

#### Installing exiv2

To install exiv2 you can just use homebrew.

```
brew install exiv2
```

Now you should be probably ready to go. But please read the next steps carefully.

#### Building RDI

I recommend opening up the ``rdi.pro``-file inside of QtCreator. It makes a lot of things easier.

After you've done that you could try build or run the app. What sometimes happen here is that you'll get an error message stating something like ``dyld: Symbols not found``. This can be simply fixed! Just go to the QtCreators "Projects" tab and click into the "Run" section. Then you need to uncheck ``Add build library search path to DYLD_LIBRARY_PATH and DYLD_FRAMEWORK_PATH``. If you've done that you should run something like ``Clear All`` and then rebuilding should work fine!

### License

As this is for testing purposes only, you can do whatever you want with it! Would be nice if you give credits...