#include "modifyseriedialog.h"
#include "ui_modifyseriedialog.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serieStatus.h"

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
        auto valString = toQString(to_string(ui->markSlider->value()));
        ui->markValueLabel->setText(valString);
    };

    connect(ui->markSlider, QOverload<int>::of(&QSlider::valueChanged), this, updateMark);

    updateMark();

    ui->descriptionTextEdit->setText(toQString(serie.getDescription()));
    ui->titleEdit->setText(toQString(serie.getTitle()));
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
    string title = fromQString(ui->titleEdit->text().trimmed());
    string description = fromQString(ui->descriptionTextEdit->toPlainText());
    int mark = ui->markSlider->sliderPosition();
    bool isWatched = ui->watchedCheckBox->isChecked();

    string creatorId = fromQString(ui->creatorList->currentItem()->data(Qt::UserRole).toString());

    Genre genre = (Genre)ui->genreList->currentItem()->data(Qt::UserRole).toInt();

    int productionYear = ui->productionYearSpinBox->value();

    int seasonCount = ui->seasonCountSpinBox->value();

    SerieStatus status = (SerieStatus)ui->statusList->currentItem()->data(Qt::UserRole).toInt();

    serie.setTitle(title);
    serie.setDescription(description);
    serie.setMark(mark);
    serie.setIsWatched(isWatched);
    serie.setCreatorId(creatorId);
    serie.setGenre(genre);
    serie.setProductionYear(productionYear);
    serie.setSeasonCount(seasonCount);
    serie.setStatus(status);

    emit serieUpdated();
    accept();
}

void ModifySerieDialog::updateLists()
{
    auto creators = PersonManager::getPeople([](Person p) {
        return p.getIsDirector();
    });

    for(auto creator : creators)
    {
        QString label = toQString(creator.getFirstName() + " " + creator.getLastName());
        auto* item = new QListWidgetItem(label);
        if(creator.getId() == serie.getCreatorId())
        {
            item->setSelected(true);
        }
        item->setData(Qt::UserRole, toQString(creator.getId()));
        ui->creatorList->addItem(item);
    }

    auto statuses = { Ongoing, Ended, Cancelled };

    for(auto status : statuses)
    {
        QString label = toQString(serieStatusString(status));
        auto* item = new QListWidgetItem(label);
        if(status == serie.getStatus())
        {
            item->setSelected(true);
        }
        item->setData(Qt::UserRole, status);
        ui->statusList->addItem(item);
    }

    auto genres = { Adventure };

    for(auto genre : genres)
    {
        QString label = toQString(getGenreString(genre));
        auto* item = new QListWidgetItem(label);
        if(genre == serie.getGenre())
        {
            item->setSelected(true);
        }
        item->setData(Qt::UserRole, genre);
        ui->genreList->addItem(item);
    }
}
