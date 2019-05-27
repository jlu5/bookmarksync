#ifndef BOOKMARKSYNCMAINWINDOW_H
#define BOOKMARKSYNCMAINWINDOW_H

#include "place.h"
#include "bookmarksyncbackend.h"
#include "backendwidget.h"

#include <QMainWindow>
#include <QDebug>
#include <QListView>

namespace Ui {
class BookmarkSyncMainWindow;
}

class BookmarkSync : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookmarkSync(QWidget* parent = nullptr);
    ~BookmarkSync();

    // Synchronization functions
    //bool isSyncReady();
    void syncFrom(BookmarkSyncBackend* backend);

private:
    Ui::BookmarkSyncMainWindow* ui;

    BackendWidget* kdeBackendWidget;
    BackendWidget* gtkBackendWidget;
    QVector<BookmarkSyncBackend*> backends;
};

#endif // BOOKMARKSYNCMAINWINDOW_H

