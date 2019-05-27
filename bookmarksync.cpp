#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "bookmarksyncgtkbackend.h"
#include "ui_bookmarksync.h"

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    kdeBackendWidget = ui->kdeBackendWidget;
    gtkBackendWidget = ui->gtkBackendWidget;
    backends.append(new BookmarkSyncKDEBackend(this, kdeBackendWidget));
    backends.append(new BookmarkSyncGTKBackend(this, gtkBackendWidget));
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
