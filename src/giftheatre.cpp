#include "giftheatre.h"
#include "hahasite.h"
#include "gifhouse.h"
#include "gifurlextractor.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QToolButton>
#include <QThread>

GifTheatre::GifTheatre(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("Gif TV"));
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    m_site = new HaHaSite();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    m_toolbar = new QToolBar(this);
    m_house = new GifHouse(this);
    layout->addWidget(m_house);
    layout->addWidget(m_toolbar);

    QToolButton* prevButton = new QToolButton(this);
    prevButton->setAutoRaise(true);
    prevButton->setAutoRepeat(true);
    prevButton->setIcon(QIcon(":/images/prev.png"));
    QToolButton* nextButton = new QToolButton(this);
    nextButton->setIcon(QIcon(":/images/next.png"));
    nextButton->setAutoRaise(true);
    nextButton->setAutoRepeat(true);

    connect(prevButton, SIGNAL(clicked()), this, SLOT(showPreviousPage()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(showNextPage()));

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    m_toolbar->addWidget(spacerWidget);
    m_toolbar->addWidget(prevButton);
    m_toolbar->addWidget(nextButton);

    setLayout(layout);
}

GifTheatre::~GifTheatre()
{
    delete m_site;
}

void GifTheatre::showNextPage()
{
    QUrl url = m_site->next();
    fireupFetcher(url);
}

void GifTheatre::showPreviousPage()
{
    QUrl url = m_site->previous();
    fireupFetcher(url);
}

void GifTheatre::onUrlsReady(const QList<QString> &urls)
{
    foreach (const QString& url, urls)
        m_house->addUrl(QUrl(url));
}

void GifTheatre::fireupFetcher(const QUrl &url)
{
    GifUrlExtractor* extractor = new GifUrlExtractor();
    extractor->setUrl(url);
//    QThread* thread = new QThread();
//    extractor->moveToThread(thread);
//    connect(thread, SIGNAL(started()), extractor, SLOT(start()));
//    connect(extractor, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(extractor, SIGNAL(urlsReady(QList<QString>)), this, SLOT(onUrlsReady(QList<QString>)));
//    connect(extractor, SIGNAL(finished()), extractor, SLOT(deleteLater()));
//    thread->start();
    extractor->start();
}
