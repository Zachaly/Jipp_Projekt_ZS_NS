#ifndef EPISODEVIEWWIDGET_H
#define EPISODEVIEWWIDGET_H

#include "FilmManager_Domain/episode.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class EpisodeViewWidget;
}

class EpisodeViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EpisodeViewWidget(Episode& episode, MainWindow *parent = nullptr);
    ~EpisodeViewWidget();

public Q_SLOTS:
    void goBack();
    void modifyEpisode();

private:
    Ui::EpisodeViewWidget *ui;
    Episode& episode;
};

#endif // EPISODEVIEWWIDGET_H
