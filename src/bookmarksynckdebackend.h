// BookmarkSyncKDEBackend: KDE bookmarks backend (via KFilePlacesModel)

#ifndef BOOKMARKSYNCKDEBACKEND_H
#define BOOKMARKSYNCKDEBACKEND_H

#include "bookmarksyncbackend.h"
#include "kdeplacefilterproxymodel.h"

class BookmarkSyncKDEBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Implemented functions
    QVector<Place> getPlaces() const override;
    void addPlace(Place place) override;
    void addPlace(int index, Place place) override;
    void editPlace(int index, Place newData) override;
    void removePlace(int index) override;
    void replace(const QVector<Place>& places) override;

    // Reimplemented from BookmarkSyncBackend to use native KFilePlaceEditDialog
    void onAddButtonClicked() override;
    void onEditButtonClicked() override;

protected:
    Place getPlaceAtIndex(const QModelIndex& index) const override;

private:
    KFilePlacesModel* model;
    KDEPlaceFilterProxyModel* filteredModel;

};

#endif // BOOKMARKSYNCKDEBACKEND_H
