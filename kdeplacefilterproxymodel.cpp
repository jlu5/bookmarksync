#include "kdeplacefilterproxymodel.h"

KDEPlaceFilterProxyModel::KDEPlaceFilterProxyModel(QObject *parent, KFilePlacesModel* source)
    : QSortFilterProxyModel(parent), source(source) {
}


// Filter function: returns true for places of type Place (local directories) and Remote (remote locations: SFTP, SMB, etc.)
// We are only interested in exporting these locations to GTK+.
bool KDEPlaceFilterProxyModel::filterAcceptsRow(
        int, const QModelIndex &sourceParent) const {
    KFilePlacesModel::GroupType groupType = source->groupType(sourceParent);
    return groupType == KFilePlacesModel::GroupType::PlacesType
            || groupType == KFilePlacesModel::GroupType::RemoteType;
};
