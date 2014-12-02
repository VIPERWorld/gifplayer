#ifndef GIFHOUSE_H
#define GIFHOUSE_H

#include <QScrollArea>
#include <QUrl>

class GifPlayer;
class QHBoxLayout;
class GifHouse : public QScrollArea
{
    Q_OBJECT
public:
    explicit GifHouse(QWidget *parent = 0);

    void addUrl(const QUrl& url);
    void clear();

protected:
    virtual void dragEnterEvent(QDragEnterEvent* e);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dropEvent(QDropEvent *);

private:
    QHBoxLayout* m_layout;
    QList<GifPlayer*> m_players;
    QList<QUrl> m_urls;
};

#endif // GIFHOUSE_H
