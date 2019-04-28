#ifndef BOOKMARKSYNCGTKBACKEND_H
#define BOOKMARKSYNCGTKBACKEND_H

#include "bookmarksyncbackend.h"
#include "placesitemmodel.h"
#include <QFileSystemWatcher>

class BookmarkSyncGTKBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncGTKBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Reimplemented functions
    QVector<Place> getPlaces() const;
    void addPlace(Place place);
    void addPlace(int index, Place place);
    void editPlace(int index, Place newData);
    void removePlace(int index);

protected:
    Place getPlaceAtIndex(const QModelIndex& index) const;

private:
    PlacesItemModel* model;
    QFileSystemWatcher* monitor;
    QString target;

    void loadPlaces();
    void writePlaces();

    void onFileChanged(const QString &path);
};

#endif // BOOKMARKSYNCGTKBACKEND_H
