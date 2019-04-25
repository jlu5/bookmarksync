#include "bookmarksync.h"
#include "ui_bookmarksync.h"

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    // Init KDE places code
    /*
    kdeList = ui->kdeFavouritesList;
    kdePlaces = new KFilePlacesModel(this);
    kdeFilterModel = new KDEPlaceFilterProxyModel(kdePlaces, this);
    kdeList->setModel(kdeFilterModel);

    // TODO: init GTK places code
    gtkList = ui->gtkFavouritesList;
    */
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
