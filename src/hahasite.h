#ifndef HAHASITE_H
#define HAHASITE_H

#include "site.h"

class HaHaSite : public Site
{
public:
    HaHaSite();

    QUrl home() const;
    QUrl next();
    QUrl previous();

private:
    int m_currIndex;
};

#endif // HAHASITE_H
