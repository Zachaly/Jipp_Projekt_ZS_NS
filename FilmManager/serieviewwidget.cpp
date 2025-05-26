#include "FilmManager_Domain/episode.h"
#include "FilmManager_Domain/personmanager.h"
#include "episodeviewwidget.h"
#include "modifyseriedialog.h"
#include "serielistviewwidget.h"
#include "serieviewwidget.h"
#include "ui_serieviewwidget.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serieStatus.h"

SerieViewWidget::SerieViewWidget(Serie& serie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieViewWidget),
    serie(serie)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifySeriesButton, SIGNAL(clicked()), this, SLOT(modifySeries()));
    updateUi();
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

void SerieViewWidget::updateUi()
{
    auto& creator = PersonManager::getPersonById(serie.getCreatorId());

    ui->creatorValueLabel->setText(toQString(creator.getFirstName() + " " + creator.getLastName()));
    ui->genreValueLabel->setText(toQString(getGenreString(serie.getGenre())));
    ui->isWatchedValueLabel->setText(toQString(serie.getIsWatched() ? "Yes" : "No"));
    ui->markValueLabel->setText(toQString(to_string(serie.getMark())));
    ui->descriptionLabel->setText(toQString(serie.getDescription()));
    ui->titleLabel->setText(toQString(serie.getTitle()));
    ui->productionYearValueLabel->setText(toQString(to_string(serie.getProductionYear())));
    ui->seasonCountLabel->setText(toQString(to_string(serie.getSeasonCount())));
    ui->statusValueLabel->setText(toQString(serieStatusString(serie.getStatus())));
}
