#include "EmbeddedImage.h"
#include <QFileInfo>
#include <QProcess>
#include <QStringList>
#include <QDir>
#include <QDebug>

EmbeddedImage::EmbeddedImage(const QString &_originalImagePath)
{
    QFileInfo fi(_originalImagePath);
    if (fi.exists())
    {
        m_originalImagePath = _originalImagePath;
    }
    else
    {
        // log
    }
}

bool EmbeddedImage::extractEmbeddedImage()
{
    QString ufrawExec = "/usr/local/bin/ufraw-batch";
    QStringList args;
    args.append(m_originalImagePath);
    args.append("--embedded-image");

    QFileInfo info(m_originalImagePath);
    QDir currentWorkDir = info.dir();
    m_embeddedImagePath = currentWorkDir.absolutePath() + "/" + info.baseName() + ".embedded.jpg";

    QFileInfo infoEmbed(m_embeddedImagePath);
    if (infoEmbed.exists())
        return true;

    QProcess *ufrawCall = new QProcess(this);
    ufrawCall->setProgram(ufrawExec);
    ufrawCall->setArguments(args);
    ufrawCall->start(ufrawExec, args);
    ufrawCall->waitForFinished();
    //QObject::connect(ufrawCall, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus) {
        //m_embeddedImagePath = currentWorkDir.absolutePath() + "/" + info.baseName() + ".embedded.jpg";
        return true;
    //});
}

QString EmbeddedImage::embeddedImagePath()
{
    return m_embeddedImagePath;
}

QString EmbeddedImage::originalImagePath()
{
    return m_originalImagePath;
}
