#include "bookmarksyncbackend.h"
#include "bookmarksync.h"

BookmarkSyncBackend::BookmarkSyncBackend(BookmarkSync* parent, BackendWidget* widget) :
    parent(parent), widget(widget)
{
    qDebug() << "Binding buttons...";
    QObject::connect(widget->addButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onAddButtonClicked);
    QObject::connect(widget->editButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onEditButtonClicked);
    QObject::connect(widget->removeButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onRemoveButtonClicked);
}

void BookmarkSyncBackend::onAdd(Place place) {
    parent->addPlaceAllExcept(this, place);
}

void BookmarkSyncBackend::onRemove(Place place) {
    parent->removePlaceAllExcept(this, place);
}

// BUTTON HANDLER: Add a new place to the list
void BookmarkSyncBackend::onAddButtonClicked() {
    QString label;
    QUrl url;

    PlaceEditDialog dialog(label, url);
    if (dialog.exec()) {
        qDebug() << "Made new place" << label << "," << url;
        addPlace(Place{label, url});
    }
}

// BUTTON HANDLER: Edit the currently selected place
void BookmarkSyncBackend::onEditButtonClicked() {
    QModelIndex current = listView->currentIndex();
    Place place = getPlaceAtIndex(current);

    qDebug() << "Current item has index" << current.row() << ":" << place.label << place.target;

    // Here, we can just modify the struct in place
    PlaceEditDialog dialog(place.label, place.target);
    if (dialog.exec()) {
        qDebug() << "Edited place" << place.label << "," << place.target;
        editPlace(current.row(), place);
    }
}

// BUTTON HANDLER: Remove the currently selected place
void BookmarkSyncBackend::onRemoveButtonClicked() {
    QModelIndex current = listView->currentIndex();
    removePlace(current.row());
}
