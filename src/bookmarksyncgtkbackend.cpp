#include "bookmarksyncgtkbackend.h"

#include <QStandardPaths>
#include <QDir>
#include <QDebug>

BookmarkSyncGTKBackend::BookmarkSyncGTKBackend(BookmarkSync* syncParent, BackendWidget* widget) :
    BookmarkSyncGenericBackend(syncParent, widget)
{
    // Try to load ~/.config/gtk-3.0/bookmarks
    QDir targetFolder = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (targetFolder.mkpath("gtk-3.0")) {
        qDebug() << "Created .config/gtk-3.0 under" << targetFolder;
    };
    target = targetFolder.filePath("gtk-3.0/bookmarks");
    // TODO: make sure target is actually readable
    monitor = new QFileSystemWatcher();
    monitor->addPath(target);

    QObject::connect(monitor, &QFileSystemWatcher::fileChanged, this, &BookmarkSyncGTKBackend::onFileChanged);
    loadPlaces();
    QObject::connect(model, &PlacesItemModel::rowsRemoved, this, &BookmarkSyncGTKBackend::onRowsRemoved);
}

void BookmarkSyncGTKBackend::onFileChanged(const QString &) {
    qDebug() << "Got file changed!" << monitor->files();
    monitor->addPath(target); // Why is this needed?
    loadPlaces();
}

void BookmarkSyncGTKBackend::removePlace(int index) {
    model->removePlace(index);
    // writePlaces() will be called by onRowsRemoved handler
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
        in.setEncoding(QStringConverter::Utf8);

        while(!in.atEnd()) {
            QString decoded = in.readLine();
            QString target = decoded.section(" ", 0, 0); // split on first space
            QString label = decoded.section(" ", 1);
            if (label.isEmpty()) {
                // Label can be empty, in which case we use the target folder name
                label = target.section("/", -1);
                // Unescape any URL-encoded characters such as spaces
                label = QUrl::fromPercentEncoding(label.toUtf8());
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
