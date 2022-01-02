// BookmarkSyncQtBackend: Qt bookmarks backend

#ifndef BOOKMARKSYNCQTBACKEND_H
#define BOOKMARKSYNCQTBACKEND_H

#include "bookmarksyncbackend.h"
#include "placesitemmodel.h"

class BookmarkSyncQtBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncQtBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Implemented functions
    QVector<Place> getPlaces() const;
    void addPlace(Place place);
    void addPlace(int index, Place place);
    void editPlace(int index, Place newData);
    void removePlace(int index);
    void replace(const QVector<Place>& places);

protected:
    Place getPlaceAtIndex(const QModelIndex& index) const;

private:
    void loadPlaces();
    void writePlaces();
    PlacesItemModel* model;
};

#endif // BOOKMARKSYNCQTBACKEND_H
