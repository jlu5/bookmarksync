#include "bookmarksyncmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookmarkSyncMainWindow w;
    w.show();

    return a.exec();
}
