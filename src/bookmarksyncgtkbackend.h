// BookmarkSyncGTKBackend: GTK+ bookmarks backend (via raw file access)

#ifndef BOOKMARKSYNCGTKBACKEND_H
#define BOOKMARKSYNCGTKBACKEND_H

#include "bookmarksyncbackend.h"
#include "bookmarksyncgenericbackend.h"
#include <QFileSystemWatcher>

class BookmarkSyncGTKBackend : public BookmarkSyncGenericBackend
{
public:
    BookmarkSyncGTKBackend(BookmarkSync* syncParent, BackendWidget* widget);
    void removePlace(int index) override;

protected:
    void loadPlaces() override;
    void writePlaces() override;

private:
    QFileSystemWatcher* monitor;
    QString target;

    void onFileChanged(const QString &path);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
};

#endif // BOOKMARKSYNCGTKBACKEND_H
