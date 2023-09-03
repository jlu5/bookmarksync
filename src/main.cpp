// main.cpp: program launcher

#include "bookmarksync.h"
#include <QApplication>
#include <QCommandLineParser>

#include "placesitemmodeltest.h"

// Tentative icon... we should really find our own
static QString ICON_NAME = "view-list";
static QString VERSION = "0.3.0";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("BookmarkSync");
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption runTests(QStringList() << "test-models",
                QCoreApplication::translate("main", "Runs tests for internal models instead of main application"));
    parser.addOption(runTests);

    QCommandLineOption syncFromBackend(QStringList() << "f" << "sync-from",
        QCoreApplication::translate("main", "CLI mode: sync from a particular backend (gtk, kde, qt)"));
    syncFromBackend.setValueName("backend");
    parser.addOption(syncFromBackend);

    parser.process(app);

    if (parser.isSet(runTests)) {
        PlacesItemModelTest t;
        return 0;
    }
    BookmarkSync bookmarkSync;

    const QString & syncFromBackendName = parser.value(syncFromBackend).toLower();
    if (!syncFromBackendName.isEmpty()) {
        // CLI mode
        BookmarkSyncBackend* backend = bookmarkSync.getBackend(syncFromBackendName);
        if (!backend) {
            qCritical("Unknown backend: %s", qUtf8Printable(syncFromBackendName));
            return 1;
        }
        qInfo("Running sync from %s backend", qUtf8Printable(syncFromBackendName));
        bookmarkSync.syncFrom(backend);
        return 0;
    } else {
        bookmarkSync.setWindowIcon(QIcon::fromTheme(ICON_NAME));
        bookmarkSync.show();
        return app.exec();
    }

}
