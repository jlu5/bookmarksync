#ifndef BOOKMARKSYNCBACKEND_H
#define BOOKMARKSYNCBACKEND_H

#include "place.h"

#include <QStringList>
#include <QListView>

class BookmarkSync; // forward declaration

class BookmarkSyncBackend
{
public:
    BookmarkSyncBackend(BookmarkSync* syncParent, QListView* widget);
    virtual ~BookmarkSyncBackend() = 0;

    // Returns a list of places currently defined in this backend
    virtual QStringList getPlaces() = 0;

    // Adds a place to this backend
    virtual void addPlace(Place place) = 0;

    // Removes a place from this backend
    virtual void removePlace(Place place) = 0;

    //TODO
    //virtual void rearrange(?);

    // Signal handlers
    void onAdd(Place place);
    void onRemove(Place place);

    // TODO
    // void onRearrange(?)

protected:
    BookmarkSync* parent;
    QListView* widget;
};

#endif // BOOKMARKSYNCBACKEND_H
