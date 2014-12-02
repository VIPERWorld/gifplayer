#include "gifurlextractor.h"

#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>

GifUrlExtractor::GifUrlExtractor(QObject *parent) :
    QObject(parent)
{
    QWebPage* page = new QWebPage(this);
    m_webFrame = page->mainFrame();
    connect(m_webFrame, SIGNAL(loadFinished(bool)), this, SLOT(onPageLoaded(bool)));
}

void GifUrlExtractor::setUrl(const QUrl& url)
{
    if (m_url != url) {
        m_url = url;
    }
}

void GifUrlExtractor::start()
{
    m_webFrame->setUrl(m_url);
}

void GifUrlExtractor::onPageLoaded(bool load)
{
//    if (!load)
//        return;
    qDebug() << "load: " << load;

    QWebElement document = m_webFrame->documentElement();
    QWebElementCollection results = document.findAll("img[src$=\".gif\"]");
    QList<QString> gifUrls;
    for (int i = 0; i < results.count(); ++i) {
        QWebElement element = results.at(i);
        gifUrls.append(extractLink(element.toOuterXml()));
    }

    emit urlsReady(gifUrls);
    emit finished();
}

QString GifUrlExtractor::extractLink(const QString &rawStr)
{
    int startPos = rawStr.indexOf("http:");
    int endPos = rawStr.indexOf("gif");
    QString url = rawStr.mid(startPos, endPos - startPos + 3);
    url.replace("small", "middle");
    return url;
}
