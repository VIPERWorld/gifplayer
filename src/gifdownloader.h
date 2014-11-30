#ifndef GIFDOWNLOADER_H
#define GIFDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class GifDownloader : public QObject
{
    Q_OBJECT
public:
    explicit GifDownloader(QUrl imageUrl, const QString& saveDir, QObject *parent = 0);

    virtual ~GifDownloader();

    QString location() const;
    QString url() const;

public slots:
    void start();

signals:
    void downloaded();

private slots:

    void fileDownloaded(QNetworkReply* pReply);

private:
    QNetworkAccessManager* m_netMgr;
    QByteArray m_downloadedData;
    QString m_imageUrl;
    QString m_saveDir;

};

#endif // GIFDOWNLOADER_H
