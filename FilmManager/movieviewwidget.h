#ifndef MOVIEVIEWWIDGET_H
#define MOVIEVIEWWIDGET_H

#include "FilmManager_Domain/movie.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class MovieViewWidget;
}

class MovieViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovieViewWidget(Movie& movie, MainWindow *parent = nullptr);
    ~MovieViewWidget();

public Q_SLOTS:
    void modifyMovie();
    void goBack();

private:
    Ui::MovieViewWidget *ui;
    Movie& movie;
};

#endif // MOVIEVIEWWIDGET_H
