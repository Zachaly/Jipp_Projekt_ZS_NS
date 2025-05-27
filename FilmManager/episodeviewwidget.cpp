#include "episodeviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "modifyepisodedialog.h"
#include "serieviewwidget.h"
#include "ui_episodeviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"

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

    auto actors = PersonManager::getPeople([this](Person p) {
        for(auto id : episode.getActorIds()){
            if(id == p.getId())
            {
                return true;
            }
        }

        return false;
    });

    for(auto& a : actors)
    {
        QString label = toQString(a.getFirstName() + " " + a.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, toQString(a.getId()));
        ui->actorList->addItem(item);
    }
}
