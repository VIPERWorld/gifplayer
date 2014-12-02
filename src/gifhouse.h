#ifndef GIFHOUSE_H
#define GIFHOUSE_H

#include <QStackedWidget>
#include <QUrl>

class GifPlayer;
class QHBoxLayout;
class GifHousePrivate;
class GifHouse : public QWidget
{
    Q_DECLARE_PRIVATE(GifHouse)
    Q_DISABLE_COPY(GifHouse)
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
    virtual QSize sizeHint() const;
    virtual void resizeEvent(QResizeEvent *);

private slots:
    void updatePlayer(int index);
    void onPlayerReleased();
    bool isValid(const QUrl& url);

private:
    GifHousePrivate* d_ptr;

};

#endif // GIFHOUSE_H
