// PlaceEditDialog: Implements the Configure Place dialog for adding/editing GTK+ bookmarks

#ifndef PLACEEDITDIALOG_H
#define PLACEEDITDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QLineEdit>

namespace Ui {
class PlaceEditDialog;
}

class PlaceEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceEditDialog(QString& label, QUrl& target, QWidget *parent = nullptr);
    ~PlaceEditDialog() override;

private:
    Ui::PlaceEditDialog *ui;
    QString& label;
    QUrl& target;
    QLineEdit* nameInput;
    QLineEdit* targetInput;

    void savePlaceInfo();
    void onSelectButtonClicked();
    void done(int r) override;
};

#endif // PLACEEDITDIALOG_H
