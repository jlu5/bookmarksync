#ifndef BOOKMARKSYNCBACKEND_H
#define BOOKMARKSYNCBACKEND_H

#include "place.h"
#include "backendwidget.h"
#include "placeeditdialog.h"

#include <QStringList>
#include <QListView>
#include <QAction>

class BookmarkSync; // forward declaration

class BookmarkSyncBackend : public QObject
{
    Q_OBJECT

public:
    BookmarkSyncBackend(BookmarkSync* syncParent, BackendWidget* widget);

    // Returns a list of places currently defined in this backend
    virtual QVector<Place> getPlaces() = 0;

    // Adds a place to this backend
    virtual void addPlace(Place place) = 0;

    // Updates the place at "index" to newData
    virtual void editPlace(int index, Place newData) = 0;

    // Removes a place from this backend
    virtual void removePlace(Place place) = 0;

    //TODO
    //virtual void rearrange(?);

protected:
    BookmarkSync* parent;
    BackendWidget* widget;
    QListView* listView;

    virtual Place getPlaceAtIndex(const QModelIndex& index) = 0;

    // Signal handlers
    void onAdd(Place place);
    void onRemove(Place place);

    // BUTTON HANDLER: Add a new place to the list
    void onAddButtonClicked();

    // BUTTON HANDLER: Edit the currently selected place
    void onEditButtonClicked();

    // BUTTON HANDLER: Remove the currently selected place
    void onRemoveButtonClicked();

    // TODO
    // void onRearrange(?)
};

#endif // BOOKMARKSYNCBACKEND_H
