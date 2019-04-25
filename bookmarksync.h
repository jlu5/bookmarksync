#ifndef BOOKMARKSYNCMAINWINDOW_H
#define BOOKMARKSYNCMAINWINDOW_H

#include "kdeplacefilterproxymodel.h"
#include "place.h"
#include "bookmarksyncbackend.h"

#include <KFilePlacesModel>
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
    void syncFrom(BookmarkSyncBackend* backend);
    void addPlaceAllExcept(BookmarkSyncBackend* backend, Place place);
    void removePlaceAllExcept(BookmarkSyncBackend* backend, Place place);

/*
public slots:
    void onKDEListClicked(QModelIndex idx);
*/
private:
    Ui::BookmarkSyncMainWindow* ui;

    KFilePlacesModel* kdePlaces;
    KDEPlaceFilterProxyModel* kdeFilterModel;
    //QListView* kdeList;
    //QListView* gtkList;
};

#endif // BOOKMARKSYNCMAINWINDOW_H

