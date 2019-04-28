#include "placesitemmodel.h"
#include "kio/global.h"

#include <QDebug>
#include <QIcon>

PlacesItemModel::PlacesItemModel(QObject *parent) : QAbstractListModel(parent)
{
}

int PlacesItemModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;  // No items have children
    }
    return places.size();
}

QVariant PlacesItemModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant(); // dummy invalid value
    }
    Place p = places[index.row()];
    switch (role) {
        case Qt::DisplayRole:  // Display the Place label
            return p.label;
        case Qt::DecorationRole: { // And an appropriate icon
            QString iconName = KIO::iconNameForUrl(p.target);
            return QIcon::fromTheme(iconName);
        }
        case Qt::UserRole:  // Define UserRole to be the place target
            return p.target;
        default:
            return QVariant();
    }
}
bool PlacesItemModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid()) {
        return false;
    }
    Place& p = places[index.row()];
    switch (role) {
        case Qt::DisplayRole:
            p.label = value.toString();
            emit dataChanged(index, index, QVector<int>(Qt::DisplayRole));
            return true;
        case Qt::UserRole:
            p.target = value.toUrl();
            emit dataChanged(index, index, QVector<int>(Qt::UserRole));
            return true;
        default:
            return false; // not a modifiable field
    }
}

Qt::ItemFlags PlacesItemModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = Qt::ItemNeverHasChildren | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.isValid()) {
        return flags | Qt::ItemIsDragEnabled | Qt::ItemIsEditable;
    } else {
        return flags | Qt::ItemIsDropEnabled;
    }
}

/*
static QString internalMimetype(const PlacesItemModel* const m) {
    return "application/x-bookmarksync-internal-" + QString::number(reinterpret_cast<long>(m));
}
*/

// Adds a place to this backend
void PlacesItemModel::addPlace(int index, Place place) {
    if (insertRow(index)) {
        QModelIndex realIndex = this->index(index);
        setData(realIndex, place.label, Qt::DisplayRole);
        setData(realIndex, place.target, Qt::UserRole);
        places.insert(index, place);
    }
}

void PlacesItemModel::editPlace(int index, Place place) {
    QModelIndex realIndex = this->index(index);
    setData(realIndex, place.label, Qt::DisplayRole);
    setData(realIndex, place.target, Qt::UserRole);
    places[index] = place;
}

// Removes a place from this backend
void PlacesItemModel::removePlace(int index) {
    removeRow(index);
    places.remove(index);
}

// Overwrite the existing model with the list of places
void PlacesItemModel::replace(const QVector<Place>& newPlaces) {
    beginResetModel();
    qDebug() << "resetting model?";
    places.clear();
    places = newPlaces; // copy places into our internal state
    endResetModel();
}

Place PlacesItemModel::getPlace(const QModelIndex& index) {
    return places[index.row()];
}

QVector<Place> PlacesItemModel::getPlaces() const {
    return places;
}
