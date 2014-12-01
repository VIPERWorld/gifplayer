#include "gifurlextractor.h"

GifUrlExtractor::GifUrlExtractor(QObject *parent) :
    QObject(parent)
{
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
        extract();
    }
}

void GifUrlExtractor::extract()
{

}


