#include "FilmManager_Domain/episode.h"
#include "episodeviewwidget.h"
#include "modifyseriedialog.h"
#include "serielistviewwidget.h"
#include "serieviewwidget.h"
#include "ui_serieviewwidget.h"

SerieViewWidget::SerieViewWidget(Serie& serie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieViewWidget),
    serie(serie)
{
    ui->setupUi(this);
    connect(ui->episodeListMockButton, SIGNAL(clicked()), this, SLOT(goToEpisode()));
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifySeriesButton, SIGNAL(clicked()), this, SLOT(modifySeries()));
}

SerieViewWidget::~SerieViewWidget()
{
    delete ui;
}

void SerieViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new SerieListViewWidget((MainWindow*)parent()));
}

void SerieViewWidget::goToEpisode()
{
    Episode episode;
    ((MainWindow*)parent())->changePage(new EpisodeViewWidget(episode, (MainWindow*)parent()));
}

void SerieViewWidget::modifySeries()
{
    auto dialog = new ModifySerieDialog(serie, this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
