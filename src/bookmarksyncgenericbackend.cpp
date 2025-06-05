#include "bookmarksyncgenericbackend.h"

BookmarkSyncGenericBackend::BookmarkSyncGenericBackend(BookmarkSync* parent, BackendWidget* widget) :
    BookmarkSyncBackend(parent, widget)
{
    model = new PlacesItemModel(this);
    widget->listView->setModel(model);
}

Place BookmarkSyncGenericBackend::getPlaceAtIndex(const QModelIndex& index) const {
    return model->getPlace(index);
}

void BookmarkSyncGenericBackend::addPlace(Place place) {
    addPlace(model->rowCount(), place);
}

void BookmarkSyncGenericBackend::addPlace(int index, Place place) {
    model->addPlace(index, place);
    writePlaces();
}

void BookmarkSyncGenericBackend::editPlace(int index, Place place) {
    model->editPlace(index, place);
    writePlaces();
}

void BookmarkSyncGenericBackend::removePlace(int index) {
    model->removePlace(index);
    writePlaces();
}

QVector<Place> BookmarkSyncGenericBackend::getPlaces() const {
    return model->getPlaces();
}

void BookmarkSyncGenericBackend::replace(const QVector<Place>& places) {
    model->replace(places);
    writePlaces();
}
