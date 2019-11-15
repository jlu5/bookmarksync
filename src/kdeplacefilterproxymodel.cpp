// KDEPlaceFilterProxyModel: KIO Places filter proxy to only show local directories and remote locations

#include "kdeplacefilterproxymodel.h"

KDEPlaceFilterProxyModel::KDEPlaceFilterProxyModel(KFilePlacesModel* sourceModel, QObject *parent)
    : QSortFilterProxyModel(parent) {
    setSourceModel(sourceModel);
}


// Filter function: returns true for non-System places of type Place (local directories) and Remote (remote locations: SFTP, SMB, etc.)
// Only these are we interested in exporting to GTK+.
bool KDEPlaceFilterProxyModel::filterAcceptsRow(
        int sourceRow, const QModelIndex &sourceParent) const {
    KFilePlacesModel* source = static_cast<KFilePlacesModel*>(sourceModel());

    QModelIndex targetIndex = source->index(sourceRow, 0, sourceParent);

    KFilePlacesModel::GroupType groupType = source->groupType(targetIndex);
    KBookmark bookmark = source->bookmarkForIndex(targetIndex);
    return (groupType == KFilePlacesModel::GroupType::PlacesType
            || groupType == KFilePlacesModel::GroupType::RemoteType)
            && bookmark.metaDataItem("isSystemItem") != "true";
};
