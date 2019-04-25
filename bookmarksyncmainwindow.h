#ifndef BOOKMARKSYNCMAINWINDOW_H
#define BOOKMARKSYNCMAINWINDOW_H

#include <KFilePlacesModel>
#include <QMainWindow>
#include <QDebug>
#include <QListView>

namespace Ui {
class BookmarkSyncMainWindow;
}

class BookmarkSyncMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookmarkSyncMainWindow(QWidget *parent = nullptr);
    ~BookmarkSyncMainWindow();

public slots:
    void onKDEListClicked(QModelIndex idx);

private:
    Ui::BookmarkSyncMainWindow *ui;

    KFilePlacesModel* kdePlaces;
    QListView* kdeList;
    QListView* gtkList;
};

#endif // BOOKMARKSYNCMAINWINDOW_H
