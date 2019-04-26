#ifndef NONSYSTEMPLACEFILTERPROXYMODEL_H
#define NONSYSTEMPLACEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <KFilePlacesModel>
#include <QDebug>

class KDEPlaceFilterProxyModel : public QSortFilterProxyModel
{
public:
    KDEPlaceFilterProxyModel(KFilePlacesModel* sourceModel, QObject* parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

};

#endif // NONSYSTEMPLACEFILTERPROXYMODEL_H
