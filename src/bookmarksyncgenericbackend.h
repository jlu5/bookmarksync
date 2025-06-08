// BookmarkSyncGenericBackend: generic backend using PlacesItemModel

#ifndef BOOKMARKSYNCGENERICBACKEND_H
#define BOOKMARKSYNCGENERICBACKEND_H

#include "bookmarksyncbackend.h"
#include "placesitemmodel.h"

class BookmarkSyncGenericBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncGenericBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Implemented functions
    QVector<Place> getPlaces() const;
    void addPlace(Place place);
    void addPlace(int index, Place place);
    void editPlace(int index, Place newData);
    void removePlace(int index);
    void replace(const QVector<Place>& places);

protected:
    Place getPlaceAtIndex(const QModelIndex& index) const;
    PlacesItemModel* model;
    virtual void loadPlaces() = 0;
    virtual void writePlaces() = 0;

private:
    void onFileChanged(const QString &path);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
};

#endif // BOOKMARKSYNCGENERICBACKEND_H
