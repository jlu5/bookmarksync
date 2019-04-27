﻿#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "place.h"

BookmarkSyncKDEBackend::BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget) :
    BookmarkSyncBackend(syncParent, widget)
{

    model = new KFilePlacesModel(widget);
    filteredModel = new KDEPlaceFilterProxyModel(model, widget);
    listView = widget->listView;
    listView->setModel(filteredModel);
    QObject::connect(listView, &QListView::clicked, this, &BookmarkSyncKDEBackend::onItemClicked);
}


// Returns a list of places currently defined in this backend
QVector<Place> BookmarkSyncKDEBackend::getPlaces() {
    QVector<Place> items;
    int rows = filteredModel->rowCount();
    for (int i=0; i < rows; i++) {
        QModelIndex modelIndex = filteredModel->index(i, 0);

        if (modelIndex.isValid()) {
            QString name = modelIndex.data().toString();
            QUrl url = modelIndex.data(KFilePlacesModel::UrlRole).toUrl();
            items.append(Place{name, url});
        }
    }
    return items;
}

// Adds a place to this backend
void BookmarkSyncKDEBackend::addPlace(Place place) {
    QString iconName = KIO::iconNameForUrl(place.target);
    model->addPlace(place.label, place.target);
}

void BookmarkSyncKDEBackend::editPlace(int index, Place place) {
    // Get the index in the master unfiltered KDE places list
    QModelIndex realIndex = filteredModel->mapToSource(filteredModel->index(index, 0));
    QString iconName = KIO::iconNameForUrl(place.target);
    model->editPlace(realIndex, place.label, place.target, iconName);
}

// Removes a place from this backend
void BookmarkSyncKDEBackend::removePlace(Place place) {
    return;
}

// Returns a place instance given the model index
Place BookmarkSyncKDEBackend::getPlaceAtIndex(const QModelIndex& index) {
    QString label = index.data().toString();
    QUrl url = index.data(KFilePlacesModel::UrlRole).toUrl();
    return Place{label, url};
}

void BookmarkSyncKDEBackend::onItemClicked(const QModelIndex index) {
    qDebug() << "DEBUG BookmarkSyncKDEBackend getPlaces output: " << getPlaces();
}
