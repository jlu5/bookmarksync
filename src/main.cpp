// main.cpp: program launcher

#include "bookmarksync.h"
#include <QApplication>
#include <QCommandLineParser>

#include "placesitemmodeltest.h"

// Tentative icon... we should really find our own
static QString ICON_NAME = "view-list";
static QString VERSION = "0.2.0";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BookmarkSync");
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription("BookmarkSync");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption runTests(QStringList() << "test-models",
                QCoreApplication::translate("main", "Runs tests for internal models instead of main application"));
    parser.addOption(runTests);

    parser.process(a);

    if (parser.isSet(runTests)) {
        PlacesItemModelTest t;
        return 0;
    }
    BookmarkSync w;
    w.setWindowIcon(QIcon::fromTheme(ICON_NAME));
    w.show();

    return a.exec();
}
