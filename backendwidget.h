#ifndef BACKENDWIDGET_H
#define BACKENDWIDGET_H

#include <QWidget>

namespace Ui {
class BackendWidget;
}

class BackendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BackendWidget(QWidget *parent = nullptr);
    ~BackendWidget();

private:
    Ui::BackendWidget *ui;
};

#endif // BACKENDWIDGET_H
