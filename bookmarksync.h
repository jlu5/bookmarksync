#ifndef BOOKMARKSYNCMAINWINDOW_H
#define BOOKMARKSYNCMAINWINDOW_H

#include "kdeplacefilterproxymodel.h"
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

public slots:
    void onKDEListClicked(QModelIndex idx);

private:
    Ui::BookmarkSyncMainWindow* ui;

    KFilePlacesModel* kdePlaces;
    QListView* kdeList;
    QListView* gtkList;
};

#endif // BOOKMARKSYNCMAINWINDOW_H
