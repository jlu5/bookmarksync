// BookmarkSync: main program UI & sync logic

#ifndef BOOKMARKSYNCMAINWINDOW_H
#define BOOKMARKSYNCMAINWINDOW_H

#include "place.h"
#include "bookmarksyncbackend.h"
#include "backendwidget.h"

#include <QMainWindow>

namespace Ui {
class BookmarkSyncMainWindow;
}

class BookmarkSync : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookmarkSync(QWidget* parent = nullptr);
    ~BookmarkSync();

    BookmarkSyncBackend* getBackend(QString name) const;

    void syncFrom(BookmarkSyncBackend* backend);

protected:
    void about();

private:
    Ui::BookmarkSyncMainWindow* ui;

    QMap<QString, BookmarkSyncBackend*> backends;
};

#endif // BOOKMARKSYNCMAINWINDOW_H

