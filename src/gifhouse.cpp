#include "gifhouse.h"
#include "gifplayer.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

GifHouse::GifHouse(QWidget *parent) :
    QScrollArea(parent)
{
    QWidget* widget = new QWidget(this);
    m_layout = new QHBoxLayout;
    widget->setLayout(m_layout);
    setWidget(widget);
    setAcceptDrops(true);
    setWidgetResizable(true);
    setContentsMargins(0,0,0,0);
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

void GifHouse::addUrl(const QUrl &url)
{
    if (m_urls.contains(url))
        return;

    GifPlayer* player = new GifPlayer(this);
    player->play(url.toLocalFile());
    m_layout->addWidget(player);
    m_players.append(player);
    m_urls.append(url);
}

void GifHouse::clear()
{
    qDeleteAll(m_players);
    m_players.clear();
}
