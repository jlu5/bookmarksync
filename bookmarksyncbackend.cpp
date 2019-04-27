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

void BookmarkSyncBackend::onAddButtonClicked() {
    QString label;
    QUrl url;

    PlaceEditDialog dialog(label, url);
    if (dialog.exec()) {
        qDebug() << "Made new place" << label << "," << url;
        addPlace(Place{label, url});
    }
}

void BookmarkSyncBackend::onEditButtonClicked() {

}

void BookmarkSyncBackend::onRemoveButtonClicked() {

}
