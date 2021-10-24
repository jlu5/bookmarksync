#include "bookmarksyncqtbackend.h"

#include <QFileDialog>
#include <QUrl>

BookmarkSyncQtBackend::BookmarkSyncQtBackend(BookmarkSync* parent, BackendWidget* widget) :
    BookmarkSyncBackend(parent, widget)
{
    model = new PlacesItemModel(this);
    listView->setModel(model);

    dialog = new QFileDialog(widget);
    loadPlaces();

    QObject::connect(widget->addButton, &QAbstractButton::clicked, this, &BookmarkSyncQtBackend::onAddButtonClicked);
    QObject::connect(widget->editButton, &QAbstractButton::clicked, this, &BookmarkSyncQtBackend::onEditButtonClicked);
    QObject::connect(widget->removeButton, &QAbstractButton::clicked, this, &BookmarkSyncQtBackend::onRemoveButtonClicked);
    QObject::connect(widget->syncButton, &QAbstractButton::clicked, this, &BookmarkSyncQtBackend::onSyncButtonClicked);
    QObject::connect(widget->listView, &QListView::doubleClicked, this, &BookmarkSyncQtBackend::onDoubleClicked);
}


void BookmarkSyncQtBackend::loadPlaces() {
    QList<QUrl> urls = dialog->sidebarUrls();
    QVector<Place> places;
    for (QUrl& url: urls) {
        // Looks like Qt does not support custom labels, so just use the basename
        // TODO: does this support non-local files?
        QString label = url.path().section("/", -1);
        places.append(Place{label, url});
    }
    model->replace(places);
}

void BookmarkSyncQtBackend::writePlaces() {
    QList<QUrl> urls;
    for (Place& place: model->getPlaces()) {
        urls.append(place.target);
    }
    dialog->setSidebarUrls(urls);
}

Place BookmarkSyncQtBackend::getPlaceAtIndex(const QModelIndex& index) const {
    return model->getPlace(index);
}

void BookmarkSyncQtBackend::addPlace(Place place) {
    addPlace(model->rowCount(), place);
}

void BookmarkSyncQtBackend::addPlace(int index, Place place) {
    model->addPlace(index, place);
    writePlaces();
}

void BookmarkSyncQtBackend::editPlace(int index, Place place) {
    model->editPlace(index, place);
    writePlaces();
}

void BookmarkSyncQtBackend::removePlace(int index) {
    model->removePlace(index);
    writePlaces();
}

QVector<Place> BookmarkSyncQtBackend::getPlaces() const {
    return model->getPlaces();
}

// Replaces all places in this backend with the given list
void BookmarkSyncQtBackend::replace(const QVector<Place>& places) {
    model->replace(places);
    writePlaces();
}
