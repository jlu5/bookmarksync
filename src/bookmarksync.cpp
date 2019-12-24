// BookmarkSync: main program UI & sync logic

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

    QObject::connect(ui->actionAbout, &QAction::triggered, this, &BookmarkSync::about);
    QObject::connect(ui->actionAboutQt, &QAction::triggered, &QApplication::aboutQt);
}

BookmarkSync::~BookmarkSync()
{
    delete ui;
}

void BookmarkSync::syncFrom(BookmarkSyncBackend* sourceBackend) {
    QVector<Place> places = sourceBackend->getPlaces();
    for (BookmarkSyncBackend*& backend: backends) {
        if (backend != sourceBackend) {
            backend->replace(places);
        }
    }
}

void BookmarkSync::about() {
    QString aboutText = tr("BookmarkSync is a simple utility that manages KDE and GTK+ bookmarks.\n"
                           "This is BookmarkSync v%1.").arg(QCoreApplication::applicationVersion());
    QMessageBox::about(this, tr("BookmarkSync"), aboutText);
}
