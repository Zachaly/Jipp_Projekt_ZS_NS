#include "addseriedialog.h"
#include "FilmManager_Domain/serie.h"
#include "FilmManager_Domain/serieStatus.h"
#include "ui_addseriedialog.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/seriesmanager.h"

#include <QMessageBox>

AddSerieDialog::AddSerieDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddSerieDialog)
{
    ui->setupUi(this);

    ui->productionYearSpinBox->setRange(1900, 2025);
    ui->seasonCountSpinBox->setRange(1, 100);

    ui->markSlider->setRange(1, 10);

    auto updateMark = [this]() {
        auto valString = toQString(to_string(ui->markSlider->value()));
        ui->markValueLabel->setText(valString);
    };

    connect(ui->markSlider, QOverload<int>::of(&QSlider::valueChanged), this, updateMark);

    comboBoxIds = vector<string>();
    updateLists();
}

void AddSerieDialog::on_buttonBox_accepted()
{
    string title = fromQString(ui->titleEdit->text().trimmed());
    string description = fromQString(ui->descriptionTextEdit->toPlainText());
    int mark = ui->markSlider->value();
    bool isWatched = ui->watchedCheckBox->isChecked();

    if(title.empty() || description.empty())
    {
        QMessageBox::warning(this, "Incomplete", "Title and description are required.");
        return;
    }

    string creatorId = comboBoxIds[ui->creatorComboBox->currentIndex()];

    if(!ui->genreList->currentItem())
    {
        QMessageBox::warning(this, "Incomplete", "You must select genre.");
        return;
    }

    Genre genre = (Genre)ui->genreList->currentItem()->data(Qt::UserRole).toInt();

    int productionYear = ui->productionYearSpinBox->value();

    int seasonCount = ui->seasonCountSpinBox->value();

    if(!ui->statusList->currentItem())
    {
        QMessageBox::warning(this, "Incomplete", "You must select status.");
        return;
    }

    SerieStatus status = (SerieStatus)ui->statusList->currentItem()->data(Qt::UserRole).toInt();

    Serie serie = Serie(title, description, genre, creatorId, productionYear, mark, isWatched, status, seasonCount, vector<string>());

    SeriesManager::addSerie(serie);
    emit serieAdded();
    accept();
}

void AddSerieDialog::updateLists()
{
    auto creators = PersonManager::getPeople([](Person p) {
        return p.getIsDirector();
    });

    for(auto& creator : creators)
    {
        ui->creatorComboBox->addItem(toQString(creator.getFirstName() + " " + creator.getLastName()));
        comboBoxIds.push_back(creator.getId());
    }
    ui->creatorComboBox->setCurrentIndex(0);

    auto statuses = { Ongoing, Ended, Cancelled };

    for(auto status : statuses)
    {
        QString label = toQString(serieStatusString(status));
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, status);
        ui->statusList->addItem(item);
    }

    auto genres = { Adventure };

    for(auto genre : genres)
    {
        QString label = toQString(getGenreString(genre));
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, genre);
        ui->genreList->addItem(item);
    }
}

AddSerieDialog::~AddSerieDialog()
{
    delete ui;
}
