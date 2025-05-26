#ifndef SERIEVIEWWIDGET_H
#define SERIEVIEWWIDGET_H

#include "FilmManager_Domain/serie.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class SerieViewWidget;
}

class SerieViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerieViewWidget(Serie& serie, MainWindow *parent = nullptr);
    ~SerieViewWidget();
public Q_SLOTS:
    void goBack();
    void goToEpisode();
    void modifySeries();

private:
    Ui::SerieViewWidget *ui;
    Serie& serie;
    void updateUi();
};

#endif // SERIEVIEWWIDGET_H
