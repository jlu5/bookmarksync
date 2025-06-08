// BookmarkSyncBackend: base class for bookmarks backends

#ifndef BOOKMARKSYNCBACKEND_H
#define BOOKMARKSYNCBACKEND_H

#include "place.h"
#include "backendwidget.h"

class BookmarkSync; // forward declaration

class BookmarkSyncBackend : public QObject
{
    Q_OBJECT

public:
    BookmarkSyncBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Returns a list of places currently defined in this backend
    virtual QVector<Place> getPlaces() const = 0;

    // Adds a place to this backend as the last entry
    virtual void addPlace(Place place) = 0;
    // Adds a place to this backend after the given index
    virtual void addPlace(int index, Place place) = 0;

    // Updates the place at "index" to newData
    virtual void editPlace(int index, Place newData) = 0;

    // Removes a place from this backend
    virtual void removePlace(int index) = 0;

    // Replaces all places in this backend with the given list
    virtual void replace(const QVector<Place>& places) = 0;

protected:
    BookmarkSync* parent;
    BackendWidget* widget;

    virtual Place getPlaceAtIndex(const QModelIndex& index) const = 0;

    // BUTTON HANDLER: Add a new place to the list
    virtual void onAddButtonClicked();

    // BUTTON HANDLER: Edit the currently selected place
    virtual void onEditButtonClicked();

    // BUTTON HANDLER: Remove the currently selected place
    virtual void onRemoveButtonClicked();

    // BUTTON HANDLER: Begin sync from this backend
    virtual void onSyncButtonClicked();

    // LISTVIEW DOUBLE CLICK HANDLER: edit the selected place. By default this will just call onEditButtonClicked()
    virtual void onDoubleClicked(const QModelIndex& index);
};

#endif // BOOKMARKSYNCBACKEND_H
