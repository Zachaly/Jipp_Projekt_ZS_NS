#include "FilmManager_Domain/episode.h"
#include "FilmManager_Domain/personmanager.h"
#include "addepisodedialog.h"
#include "episodeviewwidget.h"
#include "modifyseriedialog.h"
#include "serielistviewwidget.h"
#include "serieviewwidget.h"
#include "ui_serieviewwidget.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serieStatus.h"
#include "FilmManager_Domain/episodemanager.h"

SerieViewWidget::SerieViewWidget(Serie& serie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieViewWidget),
    serie(serie)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifySeriesButton, SIGNAL(clicked()), this, SLOT(modifySeries()));
    connect(ui->addEpisodeButton, SIGNAL(clicked()), this, SLOT(addEpisode()));
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
    connect(dialog, &ModifySerieDialog::accepted, this, &SerieViewWidget::updateUi);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void SerieViewWidget::addEpisode()
{
    auto dialog = new AddEpisodeDialog(serie.getId(), (MainWindow*)parent());
    connect(dialog, &AddEpisodeDialog::accepted, this, &SerieViewWidget::updateUi);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void SerieViewWidget::updateUi()
{
    auto& creator = PersonManager::getPersonById(serie.getCreatorId());

    auto episodes = EpisodeManager::getEpisodes([this](Episode ep) {
        return ep.getSeriesId() == serie.getId();
    });

    ui->episodeList->clear();

    for(auto& ep : episodes){
        QString label = toQString(to_string(ep.getSeasonNumber()) + " " + to_string(ep.getEpisodeNumber()) + " " + ep.getTitle());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, toQString(ep.getId()));
        ui->episodeList->addItem(item);
    }

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
