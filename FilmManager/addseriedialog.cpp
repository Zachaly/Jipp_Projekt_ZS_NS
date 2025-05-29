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

    setWindowTitle("Dodaj nowy serial");

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

    string creatorId = ui->creatorComboBox->currentData().toString().toStdString();

    Genre genre = static_cast<Genre>(ui->genreComboBox->currentIndex());

    int productionYear = ui->productionYearSpinBox->value();

    int seasonCount = ui->seasonCountSpinBox->value();

    SerieStatus status = static_cast<SerieStatus>(ui->statusComboBox->currentIndex());

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
        ui->creatorComboBox->addItem(toQString(creator.getFirstName() + " " + creator.getLastName()), QString::fromStdString(creator.getId()));
        comboBoxIds.push_back(creator.getId());
    }
    ui->creatorComboBox->setCurrentIndex(0);

    auto statuses = { Ongoing, Ended, Cancelled };

    for(auto status : statuses)
    {
        ui->statusComboBox->addItem(QString::fromStdString(serieStatusString(status)), status);
    }
}

AddSerieDialog::~AddSerieDialog()
{
    delete ui;
}
