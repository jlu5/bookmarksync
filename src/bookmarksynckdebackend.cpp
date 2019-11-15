// BookmarkSyncKDEBackend: KDE bookmarks backend (via KFilePlacesModel)

#include "bookmarksync.h"
#include "bookmarksynckdebackend.h"
#include "place.h"

BookmarkSyncKDEBackend::BookmarkSyncKDEBackend(BookmarkSync* syncParent, BackendWidget* widget) :
    BookmarkSyncBackend(syncParent, widget)
{

    model = new KFilePlacesModel(widget);
    filteredModel = new KDEPlaceFilterProxyModel(model, widget);
    listView->setModel(filteredModel);

    QObject::connect(widget->addButton, &QAbstractButton::clicked, this, &BookmarkSyncKDEBackend::onAddButtonClicked);
    QObject::connect(widget->editButton, &QAbstractButton::clicked, this, &BookmarkSyncKDEBackend::onEditButtonClicked);
    QObject::connect(widget->removeButton, &QAbstractButton::clicked, this, &BookmarkSyncKDEBackend::onRemoveButtonClicked);
    QObject::connect(widget->syncButton, &QAbstractButton::clicked, this, &BookmarkSyncKDEBackend::onSyncButtonClicked);
}


// Returns a list of places currently defined in this backend
QVector<Place> BookmarkSyncKDEBackend::getPlaces() const {
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

// Returns a place instance given the model index
Place BookmarkSyncKDEBackend::getPlaceAtIndex(const QModelIndex& index) const {
    QString label = index.data().toString();
    QUrl url = index.data(KFilePlacesModel::UrlRole).toUrl();
    return Place{label, url};
}

// Adds a place to this backend
void BookmarkSyncKDEBackend::addPlace(Place place) {
    model->addPlace(place.label, place.target, KIO::iconNameForUrl(place.target));
}

void BookmarkSyncKDEBackend::addPlace(int index, Place place) {
    QModelIndex realIndex = filteredModel->mapToSource(filteredModel->index(index, 0));
    model->addPlace(place.label, place.target, KIO::iconNameForUrl(place.target), "BookmarkSync", realIndex);
}

void BookmarkSyncKDEBackend::editPlace(int index, Place place) {
    // Get the index in the master unfiltered KDE places list
    QModelIndex realIndex = filteredModel->mapToSource(filteredModel->index(index, 0));
    model->editPlace(realIndex, place.label, place.target, KIO::iconNameForUrl(place.target));
}


/*
 KFilePlaceEditDialog::KFilePlaceEditDialog 	( 	bool  	allowGlobal,
        const QUrl &  	url,
        const QString &  	label,
        const QString &  	icon,
        bool  	isAddingNewPlace,
        bool  	appLocal = true,
        int  	iconSize = KIconLoader::SizeMedium,
        QWidget *  	parent = nullptr
    )
*/
// Overridden add handler to use KFilePlaceEditDialog
void BookmarkSyncKDEBackend::onAddButtonClicked() {
    QModelIndex current = listView->currentIndex();
    QString label;
    QUrl url;
    QString iconName = "folder";
    bool appLocal = false;

    bool result = KFilePlaceEditDialog::getInformation(false, url, label, iconName, true, appLocal, 32, parent);
    if (result) {
        qDebug() << "Made new place" << label << "," << url;
        QModelIndex realCurrentIndex = filteredModel->mapToSource(current);
        model->addPlace(label, url, iconName, "BookmarkSync", realCurrentIndex);
    }
}


// Overridden edit handler to use KFilePlaceEditDialog
void BookmarkSyncKDEBackend::onEditButtonClicked() {
    QModelIndex current = listView->currentIndex();

    QString label = current.data().toString();
    QUrl url = current.data(KFilePlacesModel::UrlRole).toUrl();
    QString iconName;
    bool appLocal = false;
    qDebug() << "Current item is" << current.row() << "with" << label << url;

    bool result = KFilePlaceEditDialog::getInformation(false, url, label, iconName, false, appLocal, 32, parent);
    if (result) {
        qDebug() << "Edited place:" << label << "," << url;
        QModelIndex realIndex = filteredModel->mapToSource(current);
        model->editPlace(realIndex, label, url, iconName);
    }
}

// Removes a place from this backend
void BookmarkSyncKDEBackend::removePlace(int index) {
    QModelIndex realIndex = filteredModel->mapToSource(filteredModel->index(index, 0));
    model->removePlace(realIndex);
}

// Replaces all places in this backend with the given list
void BookmarkSyncKDEBackend::replace(const QVector<Place>& places) {
    while (filteredModel->rowCount() > 0) {
        removePlace(0);
    }
    for (const Place& place: places) {
        addPlace(place);
    }
}
