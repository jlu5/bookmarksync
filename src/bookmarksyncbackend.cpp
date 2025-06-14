#include "bookmarksyncbackend.h"
#include "bookmarksync.h"
#include "placeeditdialog.h"

#include <QStringList>
#include <QListView>
#include <QAction>

BookmarkSyncBackend::BookmarkSyncBackend(BookmarkSync* parent, BackendWidget* widget) :
    parent(parent), widget(widget)
{
    QObject::connect(widget->addButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onAddButtonClicked);
    QObject::connect(widget->editButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onEditButtonClicked);
    QObject::connect(widget->removeButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onRemoveButtonClicked);
    QObject::connect(widget->syncButton, &QAbstractButton::clicked, this, &BookmarkSyncBackend::onSyncButtonClicked);
    QObject::connect(widget->listView, &QListView::doubleClicked, this, &BookmarkSyncBackend::onDoubleClicked);
}

// BUTTON HANDLER: Add a new place to the list
void BookmarkSyncBackend::onAddButtonClicked() {
    QString label;
    QUrl url;

    PlaceEditDialog dialog(label, url);
    if (dialog.exec()) {
        qDebug() << "Made new place" << label << "," << url;
        QModelIndex current = widget->listView->currentIndex();
        addPlace(current.row(), Place{label, url});
    }
}

// BUTTON HANDLER: Edit the currently selected place
void BookmarkSyncBackend::onEditButtonClicked() {
    QModelIndex current = widget->listView->currentIndex();
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
    QModelIndex current = widget->listView->currentIndex();
    removePlace(current.row());
}

// BUTTON HANDLER: Begin sync from this backend
void BookmarkSyncBackend::onSyncButtonClicked() {
    parent->syncFrom(this);
}

// DOUBLE CLICK HANDLER: edit the selected place
void BookmarkSyncBackend::onDoubleClicked(const QModelIndex&) {
    this->onEditButtonClicked();
}
