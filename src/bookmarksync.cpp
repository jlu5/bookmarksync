// BookmarkSync: main program UI & sync logic

#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "bookmarksyncgtkbackend.h"
#include "bookmarksyncqtbackend.h"
#include "ui_bookmarksync.h"

#include <QDebug>
#include <QListView>
#include <QMessageBox>

BookmarkSync::BookmarkSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookmarkSyncMainWindow)
{
    ui->setupUi(this);

    const auto kdeBackend = new BookmarkSyncKDEBackend(this, ui->kdeBackendWidget);
    backends.insert("kde", kdeBackend);
    const auto gtkBackend = new BookmarkSyncGTKBackend(this, ui->gtkBackendWidget);
    backends.insert("gtk", gtkBackend);
    const auto qtBackend = new BookmarkSyncQtBackend(this, ui->qtBackendWidget);
    backends.insert("qt", qtBackend);

    QObject::connect(ui->actionAbout, &QAction::triggered, this, &BookmarkSync::about);
    QObject::connect(ui->actionAboutQt, &QAction::triggered, &QApplication::aboutQt);
}

BookmarkSync::~BookmarkSync()
{
    delete ui;
}

BookmarkSyncBackend* BookmarkSync::getBackend(QString name) const {
    return backends.value(name, nullptr);
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
