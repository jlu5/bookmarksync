#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "ui_bookmarksync.h"

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    kdeList = ui->kdeFavouritesList;
    gtkList = ui->gtkFavouritesList;
    backends.append(new BookmarkSyncKDEBackend(this, kdeList));
}

BookmarkSync::~BookmarkSync()
{
    delete ui;
}

void BookmarkSync::syncFrom(BookmarkSyncBackend* sourceBackend) {
    return; //stub
}
void BookmarkSync::addPlaceAllExcept(BookmarkSyncBackend* backend, Place place) {
    return; //stub
}
void BookmarkSync::removePlaceAllExcept(BookmarkSyncBackend* backend, Place place) {
    return; //stub
}

/*
void BookmarkSync::onKDEListClicked(QModelIndex idx) {
    qDebug() << "selected place with URL " << kdePlaces->url(idx);
}
*/
