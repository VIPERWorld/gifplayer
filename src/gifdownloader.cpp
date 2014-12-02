#include "gifdownloader.h"
#include "utils.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

GifDownloader::GifDownloader(QUrl imageUrl, const QString& saveDir, QObject *parent) :
    QObject(parent), m_imageUrl(imageUrl.toString()), m_saveDir(saveDir)
{

}

GifDownloader::~GifDownloader()
{

}

void GifDownloader::start()
{
    if (QFile::exists(location())) {
        emit downloaded();
        return;
    }

    QUrl url;
    url.setUrl(m_imageUrl);
    m_netMgr = new QNetworkAccessManager();
    connect(m_netMgr, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(url);
    m_netMgr->get(request);
}

void GifDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_downloadedData = pReply->readAll();
    pReply->deleteLater();

    QFile saveFile(location());
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qDebug() << __FUNCTION__ << "failed to open file for writing. ";
        return;
    }

    qDebug() << __FUNCTION__ << "finished loading. ";

    saveFile.write(m_downloadedData);
    saveFile.close();
    emit downloaded();
}

QString GifDownloader::location() const
{
    int slashPos = m_imageUrl.lastIndexOf('/');
    QString baseName = m_imageUrl.right(m_imageUrl.length() - slashPos);
    QString saveLoc;
    if (m_saveDir.endsWith("/") || m_saveDir.endsWith("\\"))
        saveLoc = m_saveDir + baseName;
    else
        saveLoc = m_saveDir + "/" + baseName;
    return saveLoc;
}

QString GifDownloader::url() const
{
    return m_imageUrl;
}
