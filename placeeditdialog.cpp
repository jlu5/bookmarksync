#include "placeeditdialog.h"
#include "ui_placeeditdialog.h"

PlaceEditDialog::PlaceEditDialog(QString& label, QUrl& target, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceEditDialog),
    label(label),
    target(target)
{
    ui->setupUi(this);
    // Preload our input fields with the given variables
    ui->nameInput->setText(label);
    ui->targetInput->setText(target.toString());

    QObject::connect(this, &QDialog::accepted, this, &PlaceEditDialog::savePlaceInfo);
}

PlaceEditDialog::~PlaceEditDialog()
{
    delete ui;
}

void PlaceEditDialog::savePlaceInfo() {
    // Saves place info into the target vars we were given
    label = ui->nameInput->text();
    target = QUrl::fromUserInput(ui->targetInput->text());
}
