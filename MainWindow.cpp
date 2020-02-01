#include "MainWindow.h"
#include <QFile>
#include <QByteArray>
#include <QImage>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QImageReader>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "EmbeddedImage.h"
#include "exif.h"
#include <stdio.h>
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <QTextBrowser>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColorSpace>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Window | Qt::X11BypassWindowManagerHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    //QTimer::singleShot(1000, this, SLOT(showFullScreen));
    //resize(1024, 768);
    displayLbl = new QLabel(this);
    //this->setStyleSheet("background-color: black;");
/*
    QFile f("/Users/dublin/Pictures/Ich/IMG_5098.CR2");
    if (!f.open(QIODevice::ReadOnly))
    {
        // failed while open
    }
    QString imagePath;
    EmbeddedImage *embImage = new EmbeddedImage("/Users/dublin/Pictures/Ich/IMG_5098.CR2");
    if (embImage->extractEmbeddedImage())
    {
        imagePath = embImage->embeddedImagePath();
    }
*/
    // 5184 x 3456
#if 0
    QByteArray arr = f.readAll();
    unsigned char *ImgData = (unsigned char*)&arr.data()[0];
    QImage theImage(ImgData, 5184, 3456, QImage::Format_RGB16);
    displayLbl->setPixmap(QPixmap::fromImage(theImage));
#endif
    QWidget *central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(this);
    QImageReader reader("/Users/dublin/Pictures/Ich/IMG_5098.CR2");
    //reader.setScaledSize(QSize(1024, 768));
    QImage raw = reader.read();
    QSize size = reader.size();
/*
    QPixmap pix;
    pix.load(imagePath);
    pix = pix.scaled(1024, 768, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    displayLbl->setPixmap(pix);
*/
    /*
    displayLbl->setPixmap(QPixmap::fromImage(raw).scaled(1024, 768, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    layout->addWidget(displayLbl);
    displayLbl->show();
    */

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();

    //if (raw.colorSpace().isValid()) {
        raw.convertToColorSpace(QColorSpace::SRgb);
    //}

    scene->addPixmap(QPixmap::fromImage(raw));
    view->setScene(scene);
    view->resize(1024, 768);
    view->setMaximumSize(QSize(1024, 768));
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    layout->addWidget(view);

    QTextBrowser *txtBrowser = new QTextBrowser(this);

#if 0
    // Read the JPEG file into a buffer
    FILE *fp = fopen("/Users/dublin/Pictures/Ich/IMG_5098.embedded.jpg", "rb");
    if (!fp) {
      printf("Can't open file.\n");
    }
    fseek(fp, 0, SEEK_END);
    unsigned long fsize = ftell(fp);
    rewind(fp);
    unsigned char *buf = new unsigned char[fsize];
    if (fread(buf, 1, fsize, fp) != fsize) {
      printf("Can't read file.\n");
      delete[] buf;
    }
    fclose(fp);

    // Parse EXIF
    easyexif::EXIFInfo result;
    int code = result.parseFrom(buf, fsize);
    delete[] buf;
    if (code) {
      printf("Error parsing EXIF: code %d\n", code);
    }
#endif

    Exiv2::Image::AutoPtr img = Exiv2::ImageFactory::open("/Users/dublin/Pictures/Ich/IMG_5098.CR2");
    img->readMetadata();

    Exiv2::ExifData &data = img->exifData();

    std::stringstream buf;
    Exiv2::ExifData::const_iterator end = data.end();
    for (Exiv2::ExifData::const_iterator i = data.begin(); i != end; ++i) {
        const char* tn = i->typeName();
        buf << std::setw(44) << std::setfill(' ') << std::left
                  << i->key() << " "
                  << "0x" << std::setw(4) << std::setfill('0') << std::right
                  << std::hex << i->tag() << " "
                  << std::setw(9) << std::setfill(' ') << std::left
                  << (tn ? tn : "Unknown") << " "
                  << std::dec << std::setw(3)
                  << std::setfill(' ') << std::right
                  << i->count() << "  "
                  << std::dec << i->value()
                  << "\n";
    }

    txtBrowser->setText(QString::fromStdString(buf.str()));
    layout->addWidget(txtBrowser);
    central->setLayout(layout);


    this->setCentralWidget(central);
}

MainWindow::~MainWindow()
{

}
