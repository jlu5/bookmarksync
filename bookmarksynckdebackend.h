#ifndef BOOKMARKSYNCKDEBACKEND_H
#define BOOKMARKSYNCKDEBACKEND_H

#include <bookmarksyncbackend.h>
#include "kdeplacefilterproxymodel.h"
#include "backendwidget.h"
#include "kio/global.h"

#include <KFilePlacesModel>
#include <KFilePlaceEditDialog>

class BookmarkSyncKDEBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Reimplemented functions
    QVector<Place> getPlaces();
    void addPlace(Place place);
    void editPlace(int index, Place newData);
    void removePlace(Place place);
    void onEditButtonClicked();

public slots:
    void onItemClicked(const QModelIndex index);

private:    
    KFilePlacesModel* model;
    KDEPlaceFilterProxyModel* filteredModel;

};

#endif // BOOKMARKSYNCKDEBACKEND_H
