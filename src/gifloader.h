#ifndef GIFLOADER_H
#define GIFLOADER_H

#include <QObject>

class GifPlayer;
class GifLoaderPrivate;
class GifLoader : public QObject
{
    Q_OBJECT
public:
    static GifLoader* instance();

    void load(const QString& url, GifPlayer* player);

private slots:
    void onDownloaded();

private:
    explicit GifLoader(QObject *parent = 0);
    ~GifLoader();

    GifLoaderPrivate* d_ptr;
    Q_DISABLE_COPY(GifLoader)
};

#endif // GIFLOADER_H
