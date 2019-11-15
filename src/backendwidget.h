// BackendWidget: widget for each bookmarks pane in the main window

#ifndef BACKENDWIDGET_H
#define BACKENDWIDGET_H

#include <QWidget>
#include <QListView>
#include <QToolButton>

namespace Ui {
class BackendWidget;
}

class BackendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BackendWidget(QWidget *parent = nullptr);
    ~BackendWidget();
    QListView* listView;
    QToolButton *addButton, *editButton, *removeButton, *syncButton;

private:
    Ui::BackendWidget *ui;
};

#endif // BACKENDWIDGET_H
