#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "ui_bookmarksync.h"

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    kdeBackendWidget = ui->kdeBackendWidget;
    gtkBackendWidget = ui->gtkBackendWidget;
    backends.append(new BookmarkSyncKDEBackend(this, kdeBackendWidget));
}

BookmarkSync::~BookmarkSync()
{
    delete ui;
}

bool BookmarkSync::isSyncReady() {
    return false; // stub
}

void BookmarkSync::syncFrom(BookmarkSyncBackend* sourceBackend) {
    return; //stub
}
void BookmarkSync::addPlaceAllExcept(BookmarkSyncBackend* backend, int index, Place place) {
    return; //stub
}
void BookmarkSync::removePlaceAllExcept(BookmarkSyncBackend* backend, int index) {
    return; //stub
}
