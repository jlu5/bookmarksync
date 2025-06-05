// BackendWidget: widget for each bookmarks pane in the main window

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

    listView->setDragDropMode(QAbstractItemView::InternalMove);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setDragEnabled(true);
    listView->viewport()->setAcceptDrops(true);
    listView->setDropIndicatorShown(true);
}

BackendWidget::~BackendWidget()
{
    delete ui;
}
