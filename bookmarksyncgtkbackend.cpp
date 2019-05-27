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
    monitor->addPath(target); // XXX Why is this needed?
    loadPlaces();
}

void BookmarkSyncGTKBackend::loadPlaces() {
    QFile file(target, this);
    QVector<Place> newPlaces;
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
            newPlaces.append(Place{label, target});
        }
        //model->replace(places);
        in.seek(0);
        QString currentPlacesText = in.readAll();
        file.close();
        // Compute a diff between the old and new places lists; this function will update the model as needed
        computeDiff(currentPlacesText, newPlaces);
        lastPlaces = currentPlacesText;
    }
}

/* Computes a diff between the old and new GTK places files, and updates the model accordingly. */
void BookmarkSyncGTKBackend::computeDiff(const QString& newPlacesText, const QVector<Place>& newPlaces) {
    if (lastPlaces.isEmpty()) {
        model->replace(newPlaces);
        return;
    }
    diff_match_patch dmp;
    const auto &tmp = dmp.diff_linesToChars(lastPlaces.toStdWString(), newPlacesText.toStdWString());
    std::wstring lineText1 = std::get<0>(tmp);
    std::wstring lineText2 = std::get<1>(tmp);
    const auto& lineArray = std::get<2>(tmp);

    std::list<Diff> result = dmp.diff_main(lineText1, lineText2);
    dmp.diff_charsToLines(result, lineArray);

    int placeIdx = 0;
    auto lastParts = lastPlaces.split('\n');
    for (Diff& diff: result) {
        qDebug() << diff.operation << QString::fromStdWString(diff.text);
        qDebug() << "Our last: " << lastParts[placeIdx];
        if (QString::fromStdWString(diff.text).trimmed() != lastParts[placeIdx]) {\
            qDebug() << "Skipping place " << placeIdx << " " << model->getPlace(placeIdx);
            placeIdx++;
        }
        //int newIdx = dmp.diff_xIndex(result, placeIdx);
        switch (diff.operation) {
            case DELETE:
                //qDebug() << "compareDiff: remove place " << idx << " " << model->getPlace(idx);
                model->removePlace(placeIdx);
                placeIdx--;
                break;
            case INSERT:
                placeIdx++;
                //qDebug() << "compareDiff: add place " << idx << " " << model->getPlace(idx);
                model->addPlace(placeIdx, newPlaces[placeIdx]);
                break;
            default:
                placeIdx++;
                break;
        }
    }

    /*
    std::list<Diff>::const_iterator iterator;
    int idx = 0;
    int realIdx = 0;
    for (iterator = result.begin(); iterator != result.end(); ++iterator) {
        const Diff& diff = *iterator;
        qDebug() << diff.operation << QString::fromStdWString(diff.text);
        switch (diff.operation) {
            case DELETE:
                //qDebug() << "compareDiff: remove place " << idx << " " << model->getPlace(idx);
                model->removePlace(idx);
                idx--;
                break;
            case INSERT:
                idx++;
                //qDebug() << "compareDiff: add place " << idx << " " << model->getPlace(idx);
                model->addPlace(idx, newPlaces[realIdx]);
                break;
            default:
                idx++;
                break;
        }
        realIdx++;
    }*/
}

void BookmarkSyncGTKBackend::writePlaces() {
    return; // STUB

    QFile file(target);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        for (const Place& place: getPlaces()) {
            out << place.target.toEncoded() << " " << place.label << '\n';
        }
    }
    // don't need to explicitly refresh here, our file monitor should catch it
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
    writePlaces();
}

QVector<Place> BookmarkSyncGTKBackend::getPlaces() const {
    return model->getPlaces();
}

