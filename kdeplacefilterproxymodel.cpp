#include "kdeplacefilterproxymodel.h"

KDEPlaceFilterProxyModel::KDEPlaceFilterProxyModel(KFilePlacesModel* sourceModel, QObject *parent)
    : QSortFilterProxyModel(parent) {
    setSourceModel(sourceModel);
}


// Filter function: returns true for places of type Place (local directories) and Remote (remote locations: SFTP, SMB, etc.)
// We are only interested in exporting these locations to GTK+.
bool KDEPlaceFilterProxyModel::filterAcceptsRow(
        int sourceRow, const QModelIndex &sourceParent) const {
    qDebug() << "Should we filter index " << sourceParent;

    KFilePlacesModel* source = static_cast<KFilePlacesModel*>(sourceModel());
    QModelIndex targetIndex = source->index(sourceRow, 0, sourceParent);
    KFilePlacesModel::GroupType groupType = source->groupType(targetIndex);
    return (groupType == KFilePlacesModel::GroupType::PlacesType
            || groupType == KFilePlacesModel::GroupType::RemoteType)
            && true; // todo check issystem tag
};
