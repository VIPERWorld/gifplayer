#include "utils.h"

#include <QApplication>
#include <QDir>

namespace Utils
{

QString gifSaveDir()
{
    QString base = qApp->applicationDirPath();
    QString dir = base + "/" + "downloads";
    QDir saveDir;
    if (!saveDir.exists(dir))
        saveDir.mkdir(dir);
    return dir;
}

}
