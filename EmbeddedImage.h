#ifndef EMBEDDED_IMAGE_H
#define EMBEDDED_IMAGE_H

#include <QString>
#include <QObject>

class EmbeddedImage : public QObject
{
    Q_OBJECT
public:
    explicit EmbeddedImage(const QString &_originalImagePath);

    bool extractEmbeddedImage();
    QString embeddedImagePath();
    QString originalImagePath();

private:
    QString m_originalImagePath;
    QString m_embeddedImagePath;
};

#endif // EMBEDDED_IMAGE_H
