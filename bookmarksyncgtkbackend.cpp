#include "bookmarksyncbackend.h"
#include "bookmarksyncgtkbackend.h"

#include <QStandardPaths>
#include <QDir>
#include <QDebug>

BookmarkSyncGTKBackend::BookmarkSyncGTKBackend(BookmarkSync* syncParent, BackendWidget* widget) :
    BookmarkSyncBackend(syncParent, widget)
{
    model = new PlacesItemModel(this);
    listView->setModel(model);
    // Try to load ~/.config/gtk-3.0/bookmarks
    QDir targetFolder = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    target = targetFolder.relativeFilePath("gtk-3.0/bookmarks");
    // TODO: make sure target is actually readable
    monitor = new QFileSystemWatcher(QStringList(target));

    QObject::connect(monitor, &QFileSystemWatcher::fileChanged, this, &BookmarkSyncGTKBackend::onFileChanged);
}

void BookmarkSyncGTKBackend::onFileChanged(const QString &path) {
    qDebug() << "Got file changed!";
}

void loadPlaces() {
    // TODO
}

// Returns a place instance given the model index
Place BookmarkSyncGTKBackend::getPlaceAtIndex(const QModelIndex& index) const {
    return model->getPlace(index);
}

// Adds a place to this backend
void BookmarkSyncGTKBackend::addPlace(Place place) {
    addPlace(model->rowCount(), place);
}
void BookmarkSyncGTKBackend::addPlace(int index, Place place) {
    model->addPlace(index, place);
}

// Edits the place at index
void BookmarkSyncGTKBackend::editPlace(int index, Place place) {
    model->editPlace(index, place);
}

// Removes a place from this backend
void BookmarkSyncGTKBackend::removePlace(int index) {
    model->removePlace(index);
}

QVector<Place> BookmarkSyncGTKBackend::getPlaces() const {
    return model->getPlaces();
}

