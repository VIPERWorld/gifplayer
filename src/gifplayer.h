#ifndef GIFPLAYER_H
#define GIFPLAYER_H

#include <QLabel>
#include <QMovie>

class GifPlayerPrivate;
class GifPlayer : public QLabel
{
    Q_OBJECT
public:
    explicit GifPlayer(QWidget *parent = 0);
    ~GifPlayer();

public slots:
    void play(const QString& file);
    void play();
    void pause();
    void stop();

protected:
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual QSize sizeHint() const;
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

private slots:
    void onMovieStarted();
    void onMovieStateChanged(QMovie::MovieState state);

private:
    GifPlayerPrivate* d_ptr;
    Q_DISABLE_COPY(GifPlayer)
};

#endif // GIFPLAYER_H
