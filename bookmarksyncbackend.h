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
    virtual QVector<Place> getPlaces() const = 0;

    // Adds a place to this backend
    virtual void addPlace(Place place) = 0;
    virtual void addPlace(int index, Place place) = 0;

    // Updates the place at "index" to newData
    virtual void editPlace(int index, Place newData) = 0;

    // Removes a place from this backend
    virtual void removePlace(int index) = 0;

    // TODO: Moves a place from sourceIndex to targetIndex
    //virtual void rearrange(int sourceIndex, int targetIndex) = 0;

protected:
    BookmarkSync* parent;
    BackendWidget* widget;
    QListView* listView;

    virtual Place getPlaceAtIndex(const QModelIndex& index) const = 0;

    // Abstract signal handlers
    void onAdd(int index, Place place);
    void onRemove(int index);
    void onEdit(int index, Place place);
    void onRearrange(int sourceIndex, int targetIndex);

    // BUTTON HANDLER: Add a new place to the list
    void onAddButtonClicked();

    // BUTTON HANDLER: Edit the currently selected place
    void onEditButtonClicked();

    // BUTTON HANDLER: Remove the currently selected place
    void onRemoveButtonClicked();

    // DEBUG
    void onItemClicked(const QModelIndex& index);
    /*
    // LIST VIEW HANDLER: handles row additions
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    // LIST VIEW HANDLER: handles row modifications
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    // LIST VIEW HANDLER: handles rows being deleted
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
    // LIST VIEW HANDLER: handles rows being rearranged
    void onRowsMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
    */
};

#endif // BOOKMARKSYNCBACKEND_H
