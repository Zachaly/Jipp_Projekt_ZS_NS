#include "modifyseriedialog.h"
#include "ui_modifyseriedialog.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serieStatus.h"
#include "FilmManager_Domain/seriesmanager.h"

#include <QMessageBox>

ModifySerieDialog::ModifySerieDialog(Serie& serie, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifySerieDialog),
    serie(serie)
{
    ui->setupUi(this);
    ui->productionYearSpinBox->setRange(1900, 2025);
    ui->seasonCountSpinBox->setRange(1, 100);

    ui->markSlider->setRange(1, 10);

    auto updateMark = [this]() {
        auto valString = QString::fromStdString(to_string(ui->markSlider->value()));
        ui->markValueLabel->setText(valString);
    };

    connect(ui->markSlider, QOverload<int>::of(&QSlider::valueChanged), this, updateMark);

    updateMark();

    ui->descriptionTextEdit->setText(QString::fromStdString(serie.getDescription()));
    ui->titleEdit->setText(QString::fromStdString(serie.getTitle()));
    ui->markSlider->setValue(serie.getMark());
    ui->productionYearSpinBox->setValue(serie.getProductionYear());
    ui->watchedCheckBox->setChecked(serie.getIsWatched());

    updateLists();
}

ModifySerieDialog::~ModifySerieDialog()
{
    delete ui;
}

void ModifySerieDialog::on_buttonBox_accepted()
{
    string title = ui->titleEdit->text().trimmed().toStdString();
    string description = ui->descriptionTextEdit->toPlainText().toStdString();
    int mark = ui->markSlider->value();
    bool isWatched = ui->watchedCheckBox->isChecked();

    if(title.empty() || description.empty())
    {
        QMessageBox::warning(this, "Incomplete", "Title and description are required.");
        return;
    }

    string creatorId = ui->creatorComboBox->currentData().toString().toStdString();

    Genre genre = static_cast<Genre>(ui->genreComboBox->currentIndex());

    int productionYear = ui->productionYearSpinBox->value();

    int seasonCount = ui->seasonCountSpinBox->value();

    SerieStatus status = static_cast<SerieStatus>(ui->statusComboBox->currentIndex());

    serie.setTitle(title);
    serie.setDescription(description);
    serie.setMark(mark);
    serie.setIsWatched(isWatched);
    serie.setCreatorId(creatorId);
    serie.setGenre(genre);
    serie.setProductionYear(productionYear);
    serie.setSeasonCount(seasonCount);
    serie.setStatus(status);

    SeriesManager::saveToFile();

    accept();
}

void ModifySerieDialog::updateLists()
{
    auto creators = PersonManager::getPeople([](Person p) {
        return p.getIsDirector();
    });

    int i = 0;
    for(auto creator : creators)
    {
        ui->creatorComboBox->addItem(QString::fromStdString(creator.getFirstName() + " " + creator.getLastName()), QString::fromStdString(creator.getId()));
        if(creator.getId() == serie.getCreatorId())
        {
            ui->creatorComboBox->setCurrentIndex(i);
        }
        i++;
    }

    auto statuses = { Ongoing, Ended, Cancelled };
    i = 0;
    for(auto status : statuses)
    {
        ui->statusComboBox->addItem(QString::fromStdString(serieStatusString(status)), status);
        if(status == serie.getStatus())
        {
            ui->statusComboBox->setCurrentIndex(i);
        }
        i++;
    }

    ui->genreComboBox->setCurrentIndex(static_cast<int>(serie.getGenre()));
}
