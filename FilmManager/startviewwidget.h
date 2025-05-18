#ifndef STARTVIEWWIDGET_H
#define STARTVIEWWIDGET_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class StartViewWidget;
}

class StartViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartViewWidget(MainWindow *parent = nullptr);
    ~StartViewWidget();

public Q_SLOTS:
    void goToPeople();
    void goToMovies();
    void goToSeries();
private:
    Ui::StartViewWidget *ui;
};

#endif // STARTVIEWWIDGET_H
