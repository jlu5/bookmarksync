#ifndef BOOKMARKSYNCKDEBACKEND_H
#define BOOKMARKSYNCKDEBACKEND_H

#include <bookmarksyncbackend.h>
#include "kdeplacefilterproxymodel.h"
#include "backendwidget.h"

#include <KFilePlacesModel>

class BookmarkSyncKDEBackend : public BookmarkSyncBackend
{
public:
    BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget);

    QVector<Place> getPlaces();
    void addPlace(Place place);
    void removePlace(Place place);

public slots:
    void onItemClicked(const QModelIndex index);

private:
    KFilePlacesModel* model;
    KDEPlaceFilterProxyModel* filteredModel;

};

#endif // BOOKMARKSYNCKDEBACKEND_H
