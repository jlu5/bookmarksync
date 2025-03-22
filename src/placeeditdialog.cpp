// PlaceEditDialog: Implements the Configure Place dialog for adding/editing GTK+ bookmarks

#include "placeeditdialog.h"
#include "ui_placeeditdialog.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

PlaceEditDialog::PlaceEditDialog(QString& label, QUrl& target, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceEditDialog),
    label(label),
    target(target)
{
    ui->setupUi(this);
    nameInput = ui->nameInput;
    targetInput = ui->targetInput;

    // Preload our input fields with the given variables
    nameInput->setText(label);

    // Decode file:/// URIs
    if (target.isLocalFile() && target.host().isEmpty()) {
        targetInput->setText(target.toLocalFile());
    } else {
        targetInput->setText(target.toString());
    }

    QObject::connect(this, &QDialog::accepted, this, &PlaceEditDialog::savePlaceInfo);
    QObject::connect(ui->selectButton, &QAbstractButton::clicked, this, &PlaceEditDialog::onSelectButtonClicked);
}

PlaceEditDialog::~PlaceEditDialog()
{
    delete ui;
}

void PlaceEditDialog::savePlaceInfo() {
    // Save place info into the target vars we were given
    target = QUrl::fromUserInput(targetInput->text());
    label = nameInput->text();
}


// Verify that the inputted label and target are valid
void PlaceEditDialog::done(int r)
{
    if (r == QDialog::Accepted &&
            (nameInput->text().isEmpty() || targetInput->text().isEmpty())) {
        QMessageBox::critical(this, tr("Configure Place Error"),
                              tr("Place name and target must not be empty."));
    }
    else {
        QDialog::done(r);
        return;
    }
}


void PlaceEditDialog::onSelectButtonClicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        targetInput->setText(dir);
        savePlaceInfo();
    }
}
