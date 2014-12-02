#ifndef GIFTHEATRE_H
#define GIFTHEATRE_H

#include <QWidget>

class QToolBar;
class GifHouse;
class Site;
class GifTheatre : public QWidget
{
    Q_OBJECT
public:
    explicit GifTheatre(QWidget *parent = 0);
    ~GifTheatre();

private slots:
    void showNextPage();
    void showPreviousPage();
    void onUrlsReady(const QList<QString>& urls);

private:
    void fireupFetcher(const QUrl& url);

private:
    Site* m_site;
    GifHouse* m_house;
    QToolBar* m_toolbar;
};

#endif // GIFTHEATRE_H
