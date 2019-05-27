#include "bookmarksync.h"
#include <QApplication>
#include <QCommandLineParser>

#include "placesitemmodeltest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("BookmarkSync");
    QCoreApplication::setApplicationVersion("0.1");

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
    w.show();

    return a.exec();
}
