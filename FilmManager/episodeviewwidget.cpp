#include "episodeviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "modifyepisodedialog.h"
#include "serieviewwidget.h"
#include "ui_episodeviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
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
    ui->directorValueLabel->setText(QString::fromStdString(director.getFirstName() + " " + director.getLastName()));
    ui->descriptionLabel->setText(QString::fromStdString(episode.getDescription()));
    ui->titleLabel->setText(QString::fromStdString(episode.getTitle()));
    ui->markValueLabel->setText(QString::fromStdString(to_string(episode.getMark())));
    ui->seasonValueLabel->setText(QString::fromStdString(to_string(episode.getSeasonNumber())));
    ui->numberValueLabel->setText(QString::fromStdString(to_string(episode.getEpisodeNumber())));
    ui->lengthValueLabel->setText(QString::fromStdString(to_string(episode.getLength())));
    ui->productionYearValueLabel->setText(QString::fromStdString(to_string(episode.getProductionYear())));
    ui->watchedValueLabel->setText(QString::fromStdString(episode.getIsWatched() ? "Yes" : "No"));

    vector<Person> actors;

    for(auto id : episode.getActorIds())
    {
        actors.push_back(PersonManager::getPersonById(id));
    }

    ui->actorList->clear();
    for(auto& a : actors)
    {
        QString label = QString::fromStdString(a.getFirstName() + " " + a.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, QString::fromStdString(a.getId()));
        ui->actorList->addItem(item);
    }
}
