#include "placesitemmodeltest.h"
#include <QLoggingCategory>

PlacesItemModelTest::PlacesItemModelTest(QObject *parent) : QObject(parent)
{
    QLoggingCategory::setFilterRules(QStringLiteral("qt.modeltest=true"));
    PlacesItemModel* model = new PlacesItemModel(this);
    new QAbstractItemModelTester(model, QAbstractItemModelTester::FailureReportingMode::Fatal);
}
