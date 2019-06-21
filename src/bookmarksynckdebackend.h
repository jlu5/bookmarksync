#ifndef BOOKMARKSYNCKDEBACKEND_H
#define BOOKMARKSYNCKDEBACKEND_H

#include "bookmarksyncbackend.h"
#include "kdeplacefilterproxymodel.h"
#include "kio/global.h"

#include <KFilePlacesModel>
#include <KFilePlaceEditDialog>

class BookmarkSyncKDEBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Implemented functions
    QVector<Place> getPlaces() const;
    void addPlace(Place place);
    void addPlace(int index, Place place);
    void editPlace(int index, Place newData);
    void removePlace(int index);
    void replace(const QVector<Place>& places);

    // Overridden
    void onAddButtonClicked();
    void onEditButtonClicked();

protected:
    Place getPlaceAtIndex(const QModelIndex& index) const;

private:    
    KFilePlacesModel* model;
    KDEPlaceFilterProxyModel* filteredModel;

};

#endif // BOOKMARKSYNCKDEBACKEND_H