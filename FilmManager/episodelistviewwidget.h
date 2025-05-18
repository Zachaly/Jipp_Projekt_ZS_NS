#ifndef EPISODELISTVIEWWIDGET_H
#define EPISODELISTVIEWWIDGET_H

#include "FilmManager_Domain/serie.h"
#include "mainwindow.h"

#include <QWidget>
#include <string>

using namespace std;

namespace Ui {
class EpisodeListViewWidget;
}

class EpisodeListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EpisodeListViewWidget(Serie& serie, MainWindow *parent = nullptr);
    ~EpisodeListViewWidget();
public Q_SLOTS:
    void goBack();
    void goToEpisode();
    void addEpisode();
private:
    Ui::EpisodeListViewWidget *ui;
    Serie& serie;
};

#endif // EPISODELISTVIEWWIDGET_H
