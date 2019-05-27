#ifndef PLACESITEMMODELTEST_H
#define PLACESITEMMODELTEST_H

#include <QObject>
#include <QAbstractItemModelTester>
#include <QApplication>

#include "placesitemmodel.h"

class PlacesItemModelTest : public QObject
{
    Q_OBJECT
public:
    explicit PlacesItemModelTest(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PLACESITEMMODELTEST_H
