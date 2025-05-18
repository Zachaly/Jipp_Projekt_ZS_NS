#ifndef MOVIELISTVIEWWIDGET_H
#define MOVIELISTVIEWWIDGET_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class MovieListViewWidget;
}

class MovieListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovieListViewWidget(MainWindow *parent = nullptr);
    ~MovieListViewWidget();

public Q_SLOTS:
    void addMovie();
    void goToMovie();
    void goBack();

private:
    Ui::MovieListViewWidget *ui;
};

#endif // MOVIELISTVIEWWIDGET_H
