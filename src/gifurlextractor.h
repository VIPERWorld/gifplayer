#ifndef GIFURLEXTRACTOR_H
#define GIFURLEXTRACTOR_H

#include <QObject>

class GifUrlExtractor : public QObject
{
    Q_OBJECT
public:
    explicit GifUrlExtractor(QObject *parent = 0);

signals:
    void urlsReady(const QList<QString>& urls);

};

#endif // GIFURLEXTRACTOR_H
