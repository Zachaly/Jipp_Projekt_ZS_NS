#include "episodelistviewwidget.h"
#include "FilmManager_Domain/episode.h"
#include "addepisodedialog.h"
#include "episodeviewwidget.h"
#include "serieviewwidget.h"
#include "ui_episodelistviewwidget.h"

EpisodeListViewWidget::EpisodeListViewWidget(Serie& serie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::EpisodeListViewWidget),
    serie(serie)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->addEpisodeButton, SIGNAL(clicked()), this, SLOT(addEpisode()));
    connect(ui->listMockButton, SIGNAL(clicked()), this, SLOT(goToEpisode()));
}

EpisodeListViewWidget::~EpisodeListViewWidget()
{
    delete ui;
}

void EpisodeListViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new SerieViewWidget(serie, (MainWindow*)parent()));
}

void EpisodeListViewWidget::goToEpisode()
{
    Episode episode;
    ((MainWindow*)parent())->changePage(new EpisodeViewWidget(episode, (MainWindow*)parent()));
}

void EpisodeListViewWidget::addEpisode()
{
    auto dialog = new AddEpisodeDialog(((Entry*)&serie)->getId(), this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
