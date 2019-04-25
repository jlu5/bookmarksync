#include "bookmarksyncbackend.h"
#include "bookmarksync.h"

BookmarkSyncBackend::BookmarkSyncBackend(BookmarkSync* parent, QListView* widget) :
    parent(parent), widget(widget)
{
}

void BookmarkSyncBackend::onAdd(Place place) {
    parent->addPlaceAllExcept(this, place);
}

void BookmarkSyncBackend::onRemove(Place place) {
    parent->removePlaceAllExcept(this, place);
}
