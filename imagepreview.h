#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>

class ImagePreview : public QWidget
{
    Q_OBJECT
public:
    ImagePreview(QWidget *parent = nullptr);

    QPixmap &loadImage(QString fromFilePath);

    void resizeImagePreview();

    void setBgColor();

    void clear();

    QScrollArea *scrollArea;

protected:
    QLabel *imgLabel;
    QPixmap prevPixmap;

};

#endif // IMAGEPREVIEW_H
