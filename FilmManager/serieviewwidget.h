#ifndef SERIEVIEWWIDGET_H
#define SERIEVIEWWIDGET_H

#include "FilmManager_Domain/episode.h"
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
    void addEpisode();

private:
    Ui::SerieViewWidget *ui;
    Serie& serie;
    void updateUi();
    void addEpisodeListItem(const Episode& episode);
    void deleteSelectedEpisode();
    void refreshEpisodes();
};

#endif // SERIEVIEWWIDGET_H
