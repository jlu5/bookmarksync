#ifndef PLACEEDITDIALOG_H
#define PLACEEDITDIALOG_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class PlaceEditDialog;
}

class PlaceEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceEditDialog(QString& label, QUrl& target, QWidget *parent = nullptr);
    ~PlaceEditDialog();

private:
    Ui::PlaceEditDialog *ui;
    QString& label;
    QUrl& target;

    void savePlaceInfo();
};

#endif // PLACEEDITDIALOG_H
