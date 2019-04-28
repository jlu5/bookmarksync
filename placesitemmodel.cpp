#include "placesitemmodel.h"
#include "kio/global.h"

PlacesItemModel::PlacesItemModel(QObject *parent) : QAbstractListModel(parent)
{
}

int PlacesItemModel::rowCount(const QModelIndex&) const {
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
        case Qt::DecorationRole: // And an appropriate icon
            return KIO::iconNameForUrl(p.target);
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

// Adds a place to this backend
void PlacesItemModel::addPlace(int index, Place place) {
    if (insertRow(index)) {
        QModelIndex realIndex = this->index(index);
        setData(realIndex, place.label, Qt::DisplayRole);
        setData(realIndex, place.target, Qt::UserRole);
    }
}

void PlacesItemModel::editPlace(int index, Place place) {
    QModelIndex realIndex = this->index(index);
    setData(realIndex, place.label, Qt::DisplayRole);
    setData(realIndex, place.target, Qt::UserRole);
}

// Removes a place from this backend
void PlacesItemModel::removePlace(int index) {
    removeRow(index);
}

// Overwrite the existing model with the list of places
void PlacesItemModel::replace(const QVector<Place>& places) {
    beginResetModel();
    this->places = places; // copy places into our internal state
    endResetModel();
}

Place PlacesItemModel::getPlace(const QModelIndex& index) {
    return places[index.row()];
}

QVector<Place> PlacesItemModel::getPlaces() const {
    return places;
}
