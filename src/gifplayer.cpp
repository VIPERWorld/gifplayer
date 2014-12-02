#include "gifplayer.h"

#include <QMovie>
#include <QMouseEvent>
#include <QPainter>
#include <QToolButton>

#include <QProgressIndicator.h>

static const QSize ButtonSize(30,30);
static const QSize IndicatorSize(60,60);
class GifPlayerPrivate
{
public:
    GifPlayerPrivate(): movie(nullptr), isPlaying(true), pgsIndicator(nullptr),
        deleteButton(nullptr), playButton(nullptr) {}

    void drawMask(QPainter* painter);
    void layoutButtons();
    void layoutPgsIndicator();
    void deletePgsIndicator();

    GifPlayer* q_ptr;
    QMovie* movie;
    QProgressIndicator* pgsIndicator;

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
        q_ptr->connect(deleteButton, SIGNAL(clicked()), q_ptr, SIGNAL(released()));
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

void GifPlayerPrivate::layoutPgsIndicator()
{
    if (!pgsIndicator) {
        pgsIndicator = new QProgressIndicator(q_ptr);
        pgsIndicator->setFixedSize(IndicatorSize);
    }

    QPoint movePot(q_ptr->rect().center().x() - pgsIndicator->width() / 2,
                   q_ptr->rect().center().y() - pgsIndicator->height() / 2);
    pgsIndicator->move(movePot);
    pgsIndicator->startAnimation();
}

void GifPlayerPrivate::deletePgsIndicator()
{
    if (pgsIndicator) {
        delete pgsIndicator;
        pgsIndicator = nullptr;
    }

}

GifPlayer::GifPlayer(QWidget *parent) :
    QLabel(parent)
{
    d_ptr = new GifPlayerPrivate;
    d_ptr->q_ptr = this;
    setContentsMargins(0, 0, 0, 0);
//    d_ptr->layoutPgsIndicator();
}

GifPlayer::~GifPlayer()
{
    delete d_ptr;
}

void GifPlayer::play(const QString &file)
{
//    if (QFile::exists(file))
//        d_ptr->deletePgsIndicator();

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
    if (d_ptr->movie) {
        d_ptr->isPlaying = true;
        d_ptr->movie->setPaused(false);
        d_ptr->layoutButtons();
        update();
    }
}

void GifPlayer::pause()
{
    if (d_ptr->movie)
        d_ptr->movie->setPaused(true);
}

void GifPlayer::stop()
{
    if (d_ptr->movie)
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

    if (!d_ptr->movie)
        d_ptr->layoutPgsIndicator();

//    if (d_ptr->movie)
//        d_ptr->movie->setScaledSize(size());
}

void GifPlayer::onMovieStarted()
{
    if (d_ptr->movie->scaledSize().isValid())
        setFixedSize(d_ptr->movie->scaledSize());
}

void GifPlayer::onMovieStateChanged(QMovie::MovieState state)
{
    if (state == QMovie::Running)
        d_ptr->deletePgsIndicator();
}
