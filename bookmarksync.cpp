#include "bookmarksync.h"
#include "ui_bookmarksync.h"

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    // Init KDE places widget
    kdeList = ui->kdeFavouritesList;
    kdePlaces = new KFilePlacesModel(this);
    kdeList->setModel(kdePlaces);

    // TODO: init GTK places widget
    gtkList = ui->gtkFavouritesList;
}

BookmarkSync::~BookmarkSync()
{
    delete ui;
}

void BookmarkSync::onKDEListClicked(QModelIndex idx) {
    qDebug() << "selected place with URL " << kdePlaces->url(idx);
}
