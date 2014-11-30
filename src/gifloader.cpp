#include "gifloader.h"
#include "gifdownloader.h"
#include "gifplayer.h"
#include "utils.h"

#include <QMap>
#include <QThread>
#include <QUrl>

class GifLoaderPrivate
{
public:
    typedef QMap<QString, GifPlayer*> UrlPlayerMap;
    UrlPlayerMap urlPlayerMap;
};

GifLoader::GifLoader(QObject *parent) :
    QObject(parent)
{
    d_ptr = new GifLoaderPrivate;
}

GifLoader::~GifLoader()
{
    delete d_ptr;
}

GifLoader* GifLoader::instance()
{
    static GifLoader instan_;
    return &instan_;
}

void GifLoader::load(const QString& url, GifPlayer* player)
{
    if (d_ptr->urlPlayerMap.contains(url))
        return;

    player->setToolTip(url);
    d_ptr->urlPlayerMap.insert(url, player);

    QUrl url_;
    url_.setUrl(url);

    if (url_.isLocalFile()) {
        player->play(url);
        return;
    }

    QThread* thread = new QThread();
    GifDownloader* downloader = new GifDownloader(url_, Utils::gifSaveDir());
    downloader->moveToThread(thread);
    connect(thread, SIGNAL(started()), downloader, SLOT(start()));
    connect(downloader, SIGNAL(downloaded()), this, SLOT(onDownloaded()));
    connect(downloader, SIGNAL(downloaded()), thread, SLOT(deleteLater()));
    thread->start();
}

void GifLoader::onDownloaded()
{
    GifDownloader* downloader = qobject_cast<GifDownloader*>(sender());
    const QString url = downloader->url();
    if (d_ptr->urlPlayerMap.contains(url)) {
        GifPlayer* player = d_ptr->urlPlayerMap.value(url);
        player->play(downloader->location());
        d_ptr->urlPlayerMap.remove(url);
    }

    downloader->deleteLater();
}
