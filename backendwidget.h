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
    QToolButton* addButton;
    QToolButton* editButton;
    QToolButton* removeButton;

private:
    Ui::BackendWidget *ui;
};

#endif // BACKENDWIDGET_H
