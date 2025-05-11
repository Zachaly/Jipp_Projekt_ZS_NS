#include "episodeviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "modifyepisodedialog.h"
#include "serieviewwidget.h"
#include "ui_episodeviewwidget.h"

EpisodeViewWidget::EpisodeViewWidget(Episode& episode, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::EpisodeViewWidget),
    episode(episode)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifyEpisodeButton, SIGNAL(clicked()), this, SLOT(modifyEpisode()));
}

EpisodeViewWidget::~EpisodeViewWidget()
{
    delete ui;
}

void EpisodeViewWidget::goBack()
{
    Serie serie; // mock, load serie with id from episode
    ((MainWindow*)parent())->changePage(new SerieViewWidget(serie, (MainWindow*)parent()));
}

void EpisodeViewWidget::modifyEpisode()
{
    auto dialog = new ModifyEpisodeDialog(episode);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
