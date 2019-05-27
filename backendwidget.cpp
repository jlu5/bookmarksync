#include "backendwidget.h"
#include "ui_backendwidget.h"

BackendWidget::BackendWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendWidget)
{
    ui->setupUi(this);

    // Export our widgets
    listView = ui->listView;
    addButton = ui->addButton;
    editButton = ui->editButton;
    removeButton = ui->removeButton;
    syncButton = ui->syncButton;
}

BackendWidget::~BackendWidget()
{
    delete ui;
}
