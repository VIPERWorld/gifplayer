#include "gifhouse.h"
#include "gifplayer.h"
#include "gifloader.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QScrollBar>

class GifHousePrivate
{
public:
    QStackedWidget* container;
    QScrollBar* scrollbar;
    QList<GifPlayer*> players;
    QList<QUrl> urls;
};

GifHouse::GifHouse(QWidget *parent) :
    QWidget(parent)
{
    d_ptr = new GifHousePrivate;
    d_ptr->container = new QStackedWidget(this);
    d_ptr->scrollbar = new QScrollBar(Qt::Horizontal, this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(d_ptr->container);
    layout->addWidget(d_ptr->scrollbar);
    d_ptr->scrollbar->hide();
    setLayout(layout);
    setAcceptDrops(true);
    setContentsMargins(0,0,0,0);

    connect(d_ptr->scrollbar, SIGNAL(valueChanged(int)), this, SLOT(updatePlayer(int)));
}

void GifHouse::dragEnterEvent(QDragEnterEvent* e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void GifHouse::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}

void GifHouse::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void GifHouse::dropEvent(QDropEvent *e)
{
    foreach (QUrl url, e->mimeData()->urls())
        addUrl(url);
    e->acceptProposedAction();
}

QSize GifHouse::sizeHint() const
{
    return QSize(400, 400);
}

void GifHouse::resizeEvent(QResizeEvent *)
{
//    foreach (GifPlayer* player, d_ptr->players)
//        player->resize(this->size());
}

void GifHouse::addUrl(const QUrl &url)
{
    if (!isValid(url) && d_ptr->urls.contains(url))
        return;

    GifPlayer* player = new GifPlayer(this);
    connect(player, SIGNAL(released()), this, SLOT(onPlayerReleased()));

    if (url.isLocalFile()) {
        player->play(url.toLocalFile());
    } else {
        GifLoader::instance()->load(url.toString(), player);
    }

    d_ptr->container->addWidget(player);
    d_ptr->players.append(player);
    d_ptr->urls.append(url);

    if (d_ptr->players.size() > 1) {
        d_ptr->scrollbar->show();
        d_ptr->scrollbar->setRange(0, d_ptr->players.size() - 1);
        d_ptr->scrollbar->setValue(d_ptr->players.size() - 1);
    }
}

void GifHouse::clear()
{
    qDeleteAll(d_ptr->players);
    d_ptr->players.clear();
    d_ptr->scrollbar->hide();
}

void GifHouse::updatePlayer(int index)
{
    d_ptr->container->setCurrentIndex(index);
}

void GifHouse::onPlayerReleased()
{
    GifPlayer* which = qobject_cast<GifPlayer*>(sender());
    d_ptr->players.removeAll(which);

    if (d_ptr->players.size() <= 1)
        d_ptr->scrollbar->hide();
    d_ptr->scrollbar->setMaximum(d_ptr->players.size() - 1);
}

bool GifHouse::isValid(const QUrl &url)
{
    return url.toString().contains("gif");
}
