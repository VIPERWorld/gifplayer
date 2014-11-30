#include "hahasite.h"

static const int MaxPage = 55;
HaHaSite::HaHaSite() : m_currIndex(0)
{
}

QUrl HaHaSite::home() const
{
    return QUrl("http://www.haha.mx/");
}

QUrl HaHaSite::next()
{
    if (++m_currIndex > MaxPage)
        m_currIndex = MaxPage;
    return QUrl(QString("http://www.haha.mx/good/day/%1").arg(m_currIndex));
}

QUrl HaHaSite::previous()
{
    if (--m_currIndex <= 0)
        m_currIndex = 1;
    return QUrl(QString("http://www.haha.mx/good/day/%1").arg(m_currIndex));
}
