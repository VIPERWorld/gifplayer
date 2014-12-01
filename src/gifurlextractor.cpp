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

GifUrlExtractor* GifUrlExtractor::instance()
{
    static GifUrlExtractor _instan;
    return &_instan;
}

void GifUrlExtractor::setUrl(const QUrl& url)
{
    if (m_url != url) {
        m_url = url;
        m_webFrame->setUrl(m_url);
    }
}

void GifUrlExtractor::onPageLoaded(bool load)
{
//    if (!load)
//        return;

    QWebElement document = m_webFrame->documentElement();
    QWebElementCollection results = document.findAll("img[src=\"*.gif\"]");
    QList<QString> gifUrls;
    for (int i = 0; i < results.count(); ++i) {
        QWebElement element = results.at(i);
        qDebug() << element.toPlainText();
    }

    emit urlsReady(gifUrls);
}
