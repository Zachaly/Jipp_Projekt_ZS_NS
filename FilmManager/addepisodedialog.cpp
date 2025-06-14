#include "addepisodedialog.h"
#include "FilmManager_Domain/episode.h"
#include "FilmManager_Domain/episodemanager.h"
#include "ui_addepisodedialog.h"
#include "FilmManager_Domain/serie.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/seriesmanager.h"

#include <QMessageBox>

AddEpisodeDialog::AddEpisodeDialog(string serieId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEpisodeDialog),
    serieId(serieId)
{
    ui->setupUi(this);

    Serie& s = SeriesManager::getById(serieId);

    ui->seasonSpinBox->setRange(1, s.getSeasonCount());
    ui->numberSpinBox->setRange(1, 200);
    ui->markSlider->setRange(1, 10);
    ui->productionYearSpinBox->setRange(1900, 2025);
    setWindowTitle("Dodaj nowy odcinek");

    auto updateMark = [this]() {
        auto valString = QString::fromStdString(to_string(ui->markSlider->value()));
        ui->markValueLabel->setText(valString);
    };

    connect(ui->markSlider, QOverload<int>::of(&QSlider::valueChanged), this, updateMark);

    loadLists();
}

AddEpisodeDialog::~AddEpisodeDialog()
{
    delete ui;
}

void AddEpisodeDialog::on_buttonBox_accepted()
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

    Episode ep = Episode(title, description, (Genre)0, directorId, productionYear, mark, isWatched, length, number, seasonNumber, serieId, actorIds);

    EpisodeManager::addEpisode(ep);

    accept();
}

void AddEpisodeDialog::loadLists()
{
    auto directors = PersonManager::getPeople([](Person p) {
        return p.getIsDirector();
    });

    auto actors = PersonManager::getPeople([](Person p) {
        return p.getIsActor();
    });

    for(auto& d : directors){
        ui->directorComboBox->addItem(QString::fromStdString(d.getFirstName() + " " + d.getLastName()), QString::fromStdString(d.getId()));
    }
    ui->directorComboBox->setCurrentIndex(0);

    for(auto& a : actors)
    {
        QString label = QString::fromStdString(a.getFirstName() + " " + a.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, QString::fromStdString(a.getId()));
        item->setCheckState(Qt::CheckState::Unchecked);
        ui->actorList->addItem(item);
    }
}
