#ifndef BOOKMARKSYNCBACKEND_H
#define BOOKMARKSYNCBACKEND_H

#include "place.h"

#include <QStringList>
#include <QListView>

class BookmarkSync; // forward declaration

class BookmarkSyncBackend : public QObject
{
    Q_OBJECT

public:
    BookmarkSyncBackend(BookmarkSync* syncParent, QListView* widget);

    // Returns a list of places currently defined in this backend
    virtual QVector<Place> getPlaces() = 0;

    // Adds a place to this backend
    virtual void addPlace(Place place) = 0;

    // Removes a place from this backend
    virtual void removePlace(Place place) = 0;

    //TODO
    //virtual void rearrange(?);

protected:
    BookmarkSync* parent;
    QListView* widget;

    // Signal handlers
    void onAdd(Place place);
    void onRemove(Place place);

    // TODO
    // void onRearrange(?)
};

#endif // BOOKMARKSYNCBACKEND_H
