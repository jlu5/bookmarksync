// Place: holds data for a bookmarks entry

#ifndef PLACE_H
#define PLACE_H

#include <QString>
#include <QUrl>

struct Place {
    QString label;
    QUrl target;

    // Allow implicit conversion to QString, for debugging purposes
    operator QString() const {
        return "Place(" + label + " => " + target.toString() + ")";
    }
};

#endif // PLACE_H
