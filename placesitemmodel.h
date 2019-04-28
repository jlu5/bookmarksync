#ifndef PLACESITEMMODEL_H
#define PLACESITEMMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include "place.h"

class PlacesItemModel : public QAbstractListModel
{
public:
    PlacesItemModel(QObject *parent = nullptr);

    // Implemented from QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add a place
    void addPlace(int index, Place place);

    // Updates the place at "index" to newData
    void editPlace(int index, Place newData);

    // Removes a place from this backend
    void removePlace(int index);

    // Overwrite the existing model with the list of places
    void replace(const QVector<Place>& places);

    Place getPlace(const QModelIndex& index);
    QVector<Place> getPlaces() const;

private:
    QVector<Place> places;
};

#endif // PLACESITEMMODEL_H
