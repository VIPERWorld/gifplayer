#ifndef GIFURLEXTRACTOR_H
#define GIFURLEXTRACTOR_H

#include <QObject>
#include <QUrl>

class Site;
class GifUrlExtractor : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(GifUrlExtractor)
public:
    static GifUrlExtractor* instance();
    void setUrl(const QUrl& url);

signals:
    void urlsReady(const QList<QString>& urls);

private:
    explicit GifUrlExtractor(QObject *parent = 0);
    void extract();

private:
    QUrl m_url;
};

#endif // GIFURLEXTRACTOR_H
