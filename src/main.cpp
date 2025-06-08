// main.cpp: program launcher

#include "bookmarksync.h"
#include <QApplication>
#include <QCommandLineParser>

static QString VERSION = "0.4.0-dev";

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("BookmarkSync");
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption syncFromBackend(QStringList() << "f" << "sync-from",
        QCoreApplication::translate("main", "CLI mode: sync from a particular backend (gtk, kde, qt)"));
    syncFromBackend.setValueName("backend");
    parser.addOption(syncFromBackend);

    parser.process(app);
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
        bookmarkSync.show();
        return app.exec();
    }

}
