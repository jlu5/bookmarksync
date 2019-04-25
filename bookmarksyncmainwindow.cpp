#include "bookmarksyncmainwindow.h"
#include "ui_bookmarksyncmainwindow.h"

BookmarkSyncMainWindow::BookmarkSyncMainWindow(QWidget *parent) :
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

BookmarkSyncMainWindow::~BookmarkSyncMainWindow()
{
    delete ui;
}

void BookmarkSyncMainWindow::onKDEListClicked(QModelIndex idx) {
    qDebug() << "selected place with URL " << kdePlaces->url(idx);
}
