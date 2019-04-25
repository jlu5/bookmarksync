#ifndef NONSYSTEMPLACEFILTERPROXYMODEL_H
#define NONSYSTEMPLACEFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <KFilePlacesModel>

class KDEPlaceFilterProxyModel : public QSortFilterProxyModel
{
public:
    KDEPlaceFilterProxyModel(QObject* parent = nullptr, KFilePlacesModel* source = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    KFilePlacesModel* source;
};

#endif // NONSYSTEMPLACEFILTERPROXYMODEL_H
