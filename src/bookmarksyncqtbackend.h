// BookmarkSyncQtBackend: Qt bookmarks backend

#ifndef BOOKMARKSYNCQTBACKEND_H
#define BOOKMARKSYNCQTBACKEND_H

#include "bookmarksyncbackend.h"
#include "bookmarksyncgenericbackend.h"

class BookmarkSyncQtBackend : public BookmarkSyncGenericBackend
{
public:
    BookmarkSyncQtBackend(BookmarkSync* syncParent, BackendWidget* widget);

protected:
    void loadPlaces() override;
    void writePlaces() override;

};

#endif // BOOKMARKSYNCQTBACKEND_H
