#include "placeeditdialog.h"
#include "ui_placeeditdialog.h"

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
    targetInput->setText(target.toString());

    QObject::connect(this, &QDialog::accepted, this, &PlaceEditDialog::savePlaceInfo);
    QObject::connect(ui->selectButton, &QAbstractButton::clicked, this, &PlaceEditDialog::onSelectButtonClicked);
}

PlaceEditDialog::~PlaceEditDialog()
{
    delete ui;
}

void PlaceEditDialog::savePlaceInfo() {
    // Saves place info into the target vars we were given
    label = nameInput->text();
    target = QUrl::fromUserInput(targetInput->text());
}


// Verify that the inputed label and target are valid
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
    targetInput->setText(dir);
    savePlaceInfo();
}
