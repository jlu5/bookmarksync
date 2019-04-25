#include "bookmarksync.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookmarkSync w;
    w.show();

    return a.exec();
}
