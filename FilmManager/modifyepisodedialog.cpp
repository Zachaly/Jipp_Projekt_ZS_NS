#include "modifyepisodedialog.h"
#include "FilmManager_Domain/serie.h"
#include "ui_modifyepisodedialog.h"
#include "FilmManager_Domain/seriesmanager.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/episodemanager.h"

#include <QMessageBox>

ModifyEpisodeDialog::ModifyEpisodeDialog(Episode& episode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyEpisodeDialog),
    episode(episode)
{
    ui->setupUi(this);
    Serie& s = SeriesManager::getById(episode.getSeriesId());

    ui->seasonSpinBox->setRange(1, s.getSeasonCount());
    ui->numberSpinBox->setRange(1, 200);
    ui->markSlider->setRange(1, 10);
    ui->productionYearSpinBox->setRange(1900, 2025);

    auto updateMark = [this]() {
        auto valString = QString::fromStdString(to_string(ui->markSlider->value()));
        ui->markValueLabel->setText(valString);
    };

    connect(ui->markSlider, QOverload<int>::of(&QSlider::valueChanged), this, updateMark);

    loadData();
}

ModifyEpisodeDialog::~ModifyEpisodeDialog()
{
    delete ui;
}

void ModifyEpisodeDialog::on_buttonBox_accepted()
{
    string title = ui->titleEdit->text().toStdString();
    string description = ui->descriptionEdit->toPlainText().toStdString();
    if(title.empty() || description.empty())
    {
        QMessageBox::warning(this, "Incomplete", "Title and description are required.");
        return;
    }
    string directorId = ui->directorComboBox->currentData().toString().toStdString();
    int productionYear = ui->productionYearSpinBox->value();
    int mark = ui->markSlider->value();
    bool isWatched = ui->watchedCheckBox->isChecked();
    int length = ui->lengthSpinBox->value();
    int number = ui->numberSpinBox->value();
    int seasonNumber = ui->seasonSpinBox->value();

    vector<string> actorIds;

    for(int i = 0; i < ui->actorList->count(); i++)
    {
        auto* item = ui->actorList->item(i);
        if(item->checkState() == Qt::Checked)
        {
            actorIds.push_back(item->data(Qt::UserRole).toString().toStdString());
        }
    }

    if(actorIds.empty())
    {
        QMessageBox::warning(this, "Incomplete", "You must select at least 1 actor.");
        return;
    }

    episode.setTitle(title);
    episode.setDescription(description);
    episode.setCreatorId(directorId);
    episode.setProductionYear(productionYear);
    episode.setMark(mark);
    episode.setIsWatched(isWatched);
    episode.setLength(length);
    episode.setEpisodeNumber(number);
    episode.setSeasonNumber(seasonNumber);
    episode.setActorIds(actorIds);

    EpisodeManager::saveToFile();

    accept();
}

void ModifyEpisodeDialog::loadData()
{
    auto directors = PersonManager::getPeople([](Person p) {
        return p.getIsDirector();
    });

    auto actors = PersonManager::getPeople([](Person p) {
        return p.getIsActor();
    });

    int i = 0;
    for(auto& d : directors){
        ui->directorComboBox->addItem(QString::fromStdString(d.getFirstName() + " " + d.getLastName()), QString::fromStdString(d.getId()));
        if(d.getId() == episode.getCreatorId())
        {
            ui->directorComboBox->setCurrentIndex(i);
        }
        i++;
    }

    for(auto& a : actors)
    {
        QString label = QString::fromStdString(a.getFirstName() + " " + a.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, QString::fromStdString(a.getId()));
        item->setCheckState(Qt::Unchecked);
        for(auto id : episode.getActorIds())
        {
            if(id == a.getId())
            {
                item->setCheckState(Qt::Checked);
                break;
            }
        }
        ui->actorList->addItem(item);
    }

    ui->titleEdit->setText(QString::fromStdString(episode.getTitle()));
    ui->descriptionEdit->setText(QString::fromStdString(episode.getDescription()));
    ui->markSlider->setValue(episode.getMark());
    ui->seasonSpinBox->setValue(episode.getSeasonNumber());
    ui->numberSpinBox->setValue(episode.getEpisodeNumber());
    ui->productionYearSpinBox->setValue(episode.getProductionYear());
    ui->lengthSpinBox->setValue(episode.getLength());
    ui->watchedCheckBox->setChecked(episode.getIsWatched());
}
