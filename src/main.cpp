#include "mainwindow.h"
#include "testwidget.h"
#include "gifurlextractor.h"
#include "gifhouse.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GifHouse w;
    w.show();
//    GifUrlExtractor::instance()->setUrl(QUrl("http://www.haha.mx/good/day/1"));
    return a.exec();
}
