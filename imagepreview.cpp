#include "imagepreview.h"
#include <QScrollBar>
#include <QHBoxLayout>
#include <QImageReader>

ImagePreview::ImagePreview(QWidget *parent) : QWidget(parent)
{
    imgLabel = new QLabel;
    imgLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setContentsMargins(0, 0, 0, 0);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->verticalScrollBar()->blockSignals(true);
    scrollArea->horizontalScrollBar()->blockSignals(true);
    scrollArea->setFrameStyle(0);
    scrollArea->setWidget(imgLabel);
    scrollArea->setWidgetResizable(true);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(scrollArea);

    this->setBgColor();

    this->setLayout(layout);
}

QPixmap& ImagePreview::loadImage(QString fromFilePath)
{
    QImageReader reader(fromFilePath);
    if (reader.size().isValid()) {
        QSize resize = reader.size();
        resize.scale(QSize(imgLabel->width(), imgLabel->height()), Qt::KeepAspectRatio);
        QImage previewImage;
        reader.read(&previewImage);
        prevPixmap = QPixmap::fromImage(previewImage);
    }

    imgLabel->setPixmap(prevPixmap);
    this->resizeImagePreview();
    return prevPixmap;
}

void ImagePreview::clear()
{
    imgLabel->clear();
}

void ImagePreview::resizeImagePreview()
{
    const QPixmap *pixmap = imgLabel->pixmap();
    if (!pixmap)
        return;

    QSize prevSizePixmap = pixmap->size();
    if (prevSizePixmap.width() > scrollArea->width() || prevSizePixmap.height() > scrollArea->height()) {
        prevSizePixmap.scale(scrollArea->width(), scrollArea->height(), Qt::KeepAspectRatio);
    }

    imgLabel->setFixedSize(prevSizePixmap);
    imgLabel->adjustSize();
}

void ImagePreview::setBgColor()
{
    //
}
