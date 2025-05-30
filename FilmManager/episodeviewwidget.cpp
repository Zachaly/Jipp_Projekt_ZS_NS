#include "episodeviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "modifyepisodedialog.h"
#include "serieviewwidget.h"
#include "ui_episodeviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/seriesmanager.h"

EpisodeViewWidget::EpisodeViewWidget(Episode& episode, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::EpisodeViewWidget),
    episode(episode)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifyEpisodeButton, SIGNAL(clicked()), this, SLOT(modifyEpisode()));

    updateUi();
}

EpisodeViewWidget::~EpisodeViewWidget()
{
    delete ui;
}

void EpisodeViewWidget::goBack()
{
    Serie& serie = SeriesManager::getById(episode.getSeriesId());
    ((MainWindow*)parent())->changePage(new SerieViewWidget(serie, (MainWindow*)parent()));
}

void EpisodeViewWidget::modifyEpisode()
{
    auto dialog = new ModifyEpisodeDialog(episode);
    connect(dialog, &ModifyEpisodeDialog::accepted, this, &EpisodeViewWidget::updateUi);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void EpisodeViewWidget::updateUi()
{
    auto director = PersonManager::getPersonById(episode.getCreatorId());
    ui->directorValueLabel->setText(toQString(director.getFirstName() + " " + director.getLastName()));
    ui->descriptionLabel->setText(toQString(episode.getDescription()));
    ui->titleLabel->setText(toQString(episode.getTitle()));
    ui->markValueLabel->setText(toQString(to_string(episode.getMark())));
    ui->seasonValueLabel->setText(toQString(to_string(episode.getSeasonNumber())));
    ui->numberValueLabel->setText(toQString(to_string(episode.getEpisodeNumber())));
    ui->lengthValueLabel->setText(toQString(to_string(episode.getLength())));
    ui->productionYearValueLabel->setText(toQString(to_string(episode.getProductionYear())));
    ui->watchedValueLabel->setText(toQString(episode.getIsWatched() ? "Yes" : "No"));

    vector<Person> actors;

    for(auto id : episode.getActorIds())
    {
        actors.push_back(PersonManager::getPersonById(id));
    }

    ui->actorList->clear();
    for(auto& a : actors)
    {
        QString label = toQString(a.getFirstName() + " " + a.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, toQString(a.getId()));
        ui->actorList->addItem(item);
    }
}
