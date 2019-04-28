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
    target = targetFolder.filePath("gtk-3.0/bookmarks");
    qDebug() << "targetFolder" << targetFolder << "target" << target;
    // TODO: make sure target is actually readable
    monitor = new QFileSystemWatcher();
    monitor->addPath(target);

    QObject::connect(monitor, &QFileSystemWatcher::fileChanged, this, &BookmarkSyncGTKBackend::onFileChanged);
    loadPlaces();
}

void BookmarkSyncGTKBackend::onFileChanged(const QString &) {
    qDebug() << "Got file changed!" << monitor->files();
    monitor->addPath(target); // Why is this needed?
    loadPlaces();
}

void BookmarkSyncGTKBackend::loadPlaces() {
    QFile file(target, this);
    QVector<Place> places;
    qDebug() << "try to open " << target;
    if (file.open(QIODevice::ReadOnly)) {
        QList<QByteArray> lines = file.readAll().split('\n');
        qDebug() << "OK reading all lines from " << target;
        for (const QByteArray& line: lines) {
            if (line.isEmpty()) {
                continue;
            }
            // We use UTF8 on linux, right?
            QString decoded = QString::fromUtf8(line);
            QString target = decoded.section(" ", 0, 0); // split on first space
            QString label = decoded.section(" ", 1);
            if (label.isEmpty()) {
                // Label can be empty, in which case we use the target folder name
                label = target.section("/", -1);
            }
            //qDebug() << "Read place with target" << target << ", label" << label;
            places.append(Place{label, target});
        }
        qDebug() << "Calling model->replace";
        model->replace(places);
    }
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

