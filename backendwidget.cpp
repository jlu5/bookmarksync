#include "backendwidget.h"
#include "ui_backendwidget.h"

BackendWidget::BackendWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackendWidget)
{
    ui->setupUi(this);
    listView = ui->listView;
}

BackendWidget::~BackendWidget()
{
    delete ui;
}
