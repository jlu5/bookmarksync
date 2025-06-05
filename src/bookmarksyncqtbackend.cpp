// BookmarkSyncGTKBackend: Qt bookmarks backend (via QFileDialog)

#include "bookmarksyncqtbackend.h"

#include <QFileDialog>
#include <QUrl>

BookmarkSyncQtBackend::BookmarkSyncQtBackend(BookmarkSync* parent, BackendWidget* widget) :
    BookmarkSyncGenericBackend(parent, widget)
{
    loadPlaces();
}

void BookmarkSyncQtBackend::loadPlaces() {
    QFileDialog* dialog = new QFileDialog(widget);
    // Have to explicitly use the built-in Qt dialog for this to get populated
    // see https://github.com/qt/qtbase/blob/91534587314791f0d6ad7866308e0d22e2794fc9/src/widgets/dialogs/qfiledialog.cpp#L436
    dialog->setOption(QFileDialog::DontUseNativeDialog);

    QList<QUrl> urls = dialog->sidebarUrls();
    QVector<Place> places;
    for (QUrl& url: urls) {
        // Looks like Qt does not support custom labels, so just use the basename
        QString label = url.path().section("/", -1);
        places.append(Place{label, url});
    }
    model->replace(places);
    delete dialog;
}

void BookmarkSyncQtBackend::writePlaces() {
    QFileDialog* dialog = new QFileDialog(widget);
    dialog->setOption(QFileDialog::DontUseNativeDialog);

    QList<QUrl> urls;
    for (Place& place: model->getPlaces()) {
        urls.append(place.target);
    }
    dialog->setSidebarUrls(urls);
    delete dialog;
    loadPlaces(); // refresh our local view, in case there is any mismatch
}
