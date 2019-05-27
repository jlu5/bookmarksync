#include <QAbstractItemModelTester>
#include <placesitemmodel.h>

class BackendModelTest {
    Q_OBJECT
public:
    BackendModelTest();
};

BackendModelTest::BackendModelTest() {
    PlacesItemModel* model = new PlacesItemModel();
    new QAbstractItemModelTester(model, QAbstractItemModelTester::FailureReportingMode::Warning, this);
}
