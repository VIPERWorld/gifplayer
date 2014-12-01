#ifndef GIFURLEXTRACTOR_H
#define GIFURLEXTRACTOR_H

#include <QObject>
#include <QUrl>

class QWebFrame;
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

private slots:
    void onPageLoaded(bool load);

private:
    explicit GifUrlExtractor(QObject *parent = 0);

private:
    QUrl m_url;
    QWebFrame* m_webFrame;
};

#endif // GIFURLEXTRACTOR_H
