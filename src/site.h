#ifndef SITE_H
#define SITE_H

#include <QUrl>

class Site
{
public:
    Site();

    virtual QUrl home() const = 0;
    virtual QUrl next() = 0;
    virtual QUrl previous() = 0;
};

#endif // SITE_H
