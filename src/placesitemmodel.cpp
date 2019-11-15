// PlacesItemModel: Qt item model that holds an array of Places

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
        case Qt::EditRole:  // Define EditRole to be the place target
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
        case Qt::DecorationRole: {
            // Stub decoration role changes so that drag and drop does not abort
            return true;
        }
        case Qt::EditRole:
            p.target = value.toUrl();
            emit dataChanged(index, index, QVector<int>(Qt::EditRole));
            return true;
        default:
            return false; // not a modifiable field
    }
}

Qt::DropActions PlacesItemModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::ItemFlags PlacesItemModel::flags(const QModelIndex &index) const {
    if (index.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
    } else {
        return Qt::ItemIsDropEnabled;
    }
}

bool PlacesItemModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row+count-1);
    while (count-- > 0) {
        places.insert(row, Place{"", QUrl()});
    }
    endInsertRows();
    return true;
}

bool PlacesItemModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row+count-1);
    while (count-- > 0) {
        places.remove(row);
    }
    endRemoveRows();
    return true;
}

// Adds a place to this backend
void PlacesItemModel::addPlace(int index, Place place) {
    if (insertRow(index)) {
        QModelIndex realIndex = this->index(index);
        setData(realIndex, place.label, Qt::DisplayRole);
        setData(realIndex, place.target, Qt::EditRole);
    }
}

void PlacesItemModel::editPlace(int index, Place place) {
    QModelIndex realIndex = this->index(index);
    setData(realIndex, place.label, Qt::DisplayRole);
    setData(realIndex, place.target, Qt::EditRole);
    places[index] = place;
}

// Removes a place from this backend
void PlacesItemModel::removePlace(int index) {
    removeRow(index);
}

// Overwrite the existing model with the list of places
void PlacesItemModel::replace(const QVector<Place>& newPlaces) {
    beginResetModel();
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
