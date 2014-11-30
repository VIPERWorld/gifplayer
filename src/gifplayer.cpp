#include "gifplayer.h"

#include <QMovie>
#include <QMouseEvent>
#include <QPainter>
#include <QToolButton>

static const QSize ButtonSize(40,40);
class GifPlayerPrivate
{
public:
    GifPlayerPrivate(): movie(nullptr), isPlaying(true),
        deleteButton(nullptr), playButton(nullptr) {}

    void drawMask(QPainter* painter);
    void layoutButtons();

    GifPlayer* q_ptr;
    QMovie* movie;

    QToolButton* deleteButton;
    QToolButton* playButton;

    bool isPlaying;
};

void GifPlayerPrivate::drawMask(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->setOpacity(0.7);
    painter->drawRect(q_ptr->rect());
    painter->restore();
}

void GifPlayerPrivate::layoutButtons()
{
    if (!deleteButton) {
        deleteButton = new QToolButton(q_ptr);
        deleteButton->setFixedSize(ButtonSize);
        deleteButton->setIconSize(ButtonSize);
        deleteButton->setAutoRaise(true);
        deleteButton->setIcon(QIcon(":/images/delete.png"));
        q_ptr->connect(deleteButton, SIGNAL(clicked()), q_ptr, SLOT(deleteLater()));
    }

    if (!playButton) {
        playButton = new QToolButton(q_ptr);
        playButton->setFixedSize(ButtonSize);
        playButton->setIcon(QIcon(":/images/play.png"));
        playButton->setIconSize(ButtonSize);
        playButton->setAutoRaise(true);
        q_ptr->connect(playButton, SIGNAL(clicked()), q_ptr, SLOT(play()));
    }

    if (isPlaying) {
        deleteButton->setVisible(false);
        playButton->setVisible(false);
    } else {
        deleteButton->setVisible(true);
        playButton->setVisible(true);

        const int extra = 10;
        // layout delete button
        QPoint topRight(q_ptr->width() - extra - deleteButton->width(), extra);
        deleteButton->move(topRight);

        // layout play button
        QPoint center(q_ptr->rect().center().x() - playButton->width() / 2,
                      q_ptr->rect().center().y() - playButton->height() / 2);
        playButton->move(center);

    }
}

GifPlayer::GifPlayer(QWidget *parent) :
    QLabel(parent)
{
    d_ptr = new GifPlayerPrivate;
    d_ptr->q_ptr = this;
}

GifPlayer::~GifPlayer()
{
    delete d_ptr;
}

void GifPlayer::play(const QString &file)
{
    if (d_ptr->movie == nullptr) {
        d_ptr->movie = new QMovie(this);
        connect(d_ptr->movie, SIGNAL(started()), this, SLOT(onMovieStarted()));
        setMovie(d_ptr->movie);
    }
    d_ptr->movie->setFileName(file);
    d_ptr->movie->start();
}

void GifPlayer::play()
{
    d_ptr->isPlaying = true;
    d_ptr->movie->setPaused(false);
    d_ptr->layoutButtons();
    update();
}

void GifPlayer::pause()
{
    d_ptr->movie->setPaused(true);
}

void GifPlayer::stop()
{
    d_ptr->movie->stop();
}

void GifPlayer::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        d_ptr->isPlaying = !d_ptr->isPlaying;
        if (d_ptr->isPlaying)
            play();
        else {
            pause();
            d_ptr->layoutButtons();
        }
    }
    update();
}

QSize GifPlayer::sizeHint() const
{
    if (d_ptr->movie)
        d_ptr->movie->scaledSize();
    return QSize(200, 200);
}

void GifPlayer::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QLabel::paintEvent(e);
    if (!d_ptr->isPlaying)
        d_ptr->drawMask(&painter);
}

void GifPlayer::resizeEvent(QResizeEvent *)
{
    d_ptr->layoutButtons();
}

void GifPlayer::onMovieStarted()
{
    if (d_ptr->movie->scaledSize().isValid())
        setFixedSize(d_ptr->movie->scaledSize());
}
