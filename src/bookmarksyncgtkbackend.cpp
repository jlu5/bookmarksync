// BookmarkSyncGTKBackend: GTK+ bookmarks backend (via raw file access)

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

    QObject::connect(widget->addButton, &QAbstractButton::clicked, this, &BookmarkSyncGTKBackend::onAddButtonClicked);
    QObject::connect(widget->editButton, &QAbstractButton::clicked, this, &BookmarkSyncGTKBackend::onEditButtonClicked);
    QObject::connect(widget->removeButton, &QAbstractButton::clicked, this, &BookmarkSyncGTKBackend::onRemoveButtonClicked);
    QObject::connect(widget->syncButton, &QAbstractButton::clicked, this, &BookmarkSyncGTKBackend::onSyncButtonClicked);
    QObject::connect(model, &PlacesItemModel::rowsRemoved, this, &BookmarkSyncGTKBackend::onRowsRemoved);
}

void BookmarkSyncGTKBackend::onFileChanged(const QString &) {
    qDebug() << "Got file changed!" << monitor->files();
    monitor->addPath(target); // Why is this needed?
    loadPlaces();
}

/* Remove handler: write the places after doing an internal move via drag and drop
 * An internal move consists of insertRow, setData (data copy), and then removeRow in that order.
 * For some reason custom signals sent from dropEvent() trigger before the remove, causing the outputted places list
 * to be incorrect. Meanwhile, QListView::indexesMoved does not seem to trigger from an internal move, and
 * moveRows is not used here per https://forum.qt.io/topic/90560/qtreeview-qabstractitemmodel-and-internal-move
 */
void BookmarkSyncGTKBackend::onRowsRemoved(const QModelIndex&, int, int) {
    writePlaces();
}

void BookmarkSyncGTKBackend::loadPlaces() {
    QFile file(target, this);
    QVector<Place> places;
    qDebug() << "try to open " << target;
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        // We use UTF8 on linux, right?
        in.setCodec("UTF-8");

        while(!in.atEnd()) {
            QString decoded = in.readLine();
            QString target = decoded.section(" ", 0, 0); // split on first space
            QString label = decoded.section(" ", 1);
            if (label.isEmpty()) {
                // Label can be empty, in which case we use the target folder name
                label = target.section("/", -1);
            }
            //qDebug() << "Read place with target" << target << ", label" << label;
            places.append(Place{label, target});
        }

        file.close();
        model->replace(places);
    }
}

void BookmarkSyncGTKBackend::writePlaces() {
    monitor->removePath(target); // So that we don't get triggered by our own writes
    QFile file(target);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        for (const Place& place: getPlaces()) {
            out << place.target.toEncoded() << " " << place.label << '\n';
        }
    }
    monitor->addPath(target);
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
    writePlaces();
}

// Edits the place at index
void BookmarkSyncGTKBackend::editPlace(int index, Place place) {
    model->editPlace(index, place);
    writePlaces();
}

// Removes a place from this backend
void BookmarkSyncGTKBackend::removePlace(int index) {
    model->removePlace(index);
    // writePlaces() will be called by onRowsRemoved handler
}

QVector<Place> BookmarkSyncGTKBackend::getPlaces() const {
    return model->getPlaces();
}

// Replaces all places in this backend with the given list
void BookmarkSyncGTKBackend::replace(const QVector<Place>& places) {
    model->replace(places);
    writePlaces();
}
