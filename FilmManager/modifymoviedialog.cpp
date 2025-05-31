#include "modifymoviedialog.h"
#include "ui_modifymoviedialog.h"
#include "FilmManager_Domain/moviemanager.h"
#include "FilmManager_Domain/personmanager.h"
#include <QMessageBox>

ModifyMovieDialog::ModifyMovieDialog(const Movie& movie, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyMovieDialog)
    , originalMovie(movie)
{
    ui->setupUi(this);

    populateDirectors();
    populateActors();
    loadMovieData();

    setWindowTitle("Modyfikuj film");
    setModal(true);
    resize(500, 700);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ModifyMovieDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->ratingSlider, &QSlider::valueChanged, this, &ModifyMovieDialog::updateRatingLabel);

    ui->ratingLabel->setText(QString::number(ui->ratingSlider->value()));
}

ModifyMovieDialog::~ModifyMovieDialog()
{
    delete ui;
}

void ModifyMovieDialog::populateDirectors()
{
    ui->directorComboBox->clear();

    for (const auto& person : PersonManager::getPeople([](Person p) { return p.getIsDirector(); })) {
        QString displayName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
        .arg(QString::fromStdString(person.getLastName()));
        ui->directorComboBox->addItem(displayName, QString::fromStdString(person.getId()));
    }
}

void ModifyMovieDialog::populateActors()
{
    for (auto* checkBox : actorCheckBoxes) {
        delete checkBox;
    }
    actorCheckBoxes.clear();

    for (const auto& person : PersonManager::getPeople([](Person p) { return p.getIsActor(); })) {
        QString displayName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
        .arg(QString::fromStdString(person.getLastName()));
        QCheckBox* checkBox = new QCheckBox(displayName, this);
        checkBox->setProperty("personId", QString::fromStdString(person.getId()));

        for(auto id : originalMovie.getActorIds())
        {
            if(id == person.getId())
            {
                checkBox->setChecked(true);
            }
        }
        actorCheckBoxes.push_back(checkBox);
        ui->actorsLayout->addWidget(checkBox);
    }
}

void ModifyMovieDialog::loadMovieData()
{
    ui->titleLineEdit->setText(QString::fromStdString(originalMovie.getTitle()));
    ui->yearSpinBox->setValue(originalMovie.getProductionYear());
    ui->lengthSpinBox->setValue(originalMovie.getLength());
    ui->genreComboBox->setCurrentIndex(static_cast<int>(originalMovie.getGenre()));
    ui->descriptionTextEdit->setPlainText(QString::fromStdString(originalMovie.getDescription()));
    ui->ratingSlider->setValue(originalMovie.getMark());
    ui->watchedCheckBox->setChecked(originalMovie.getIsWatched());

    for (int i = 0; i < ui->directorComboBox->count(); ++i) {
        if (ui->directorComboBox->itemData(i).toString().toStdString() == originalMovie.getCreatorId()) {
            ui->directorComboBox->setCurrentIndex(i);
            break;
        }
    }

    std::vector<std::string> movieActors = originalMovie.getActorIds();
    for (auto* checkBox : actorCheckBoxes) {
        std::string personId = checkBox->property("personId").toString().toStdString();
        bool isSelected = std::find(movieActors.begin(), movieActors.end(), personId) != movieActors.end();
        checkBox->setChecked(isSelected);
    }
}

std::vector<std::string> ModifyMovieDialog::getSelectedActors()
{
    std::vector<std::string> selectedActors;

    for (auto* checkBox : actorCheckBoxes) {
        if (checkBox->isChecked()) {
            selectedActors.push_back(checkBox->property("personId").toString().toStdString());
        }
    }

    return selectedActors;
}

void ModifyMovieDialog::onAccept()
{
    if (ui->titleLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Tytuł filmu nie może być pusty!");
        return;
    }

    if (ui->directorComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Błąd", "Musisz wybrać reżysera!");
        return;
    }

    accept();
}

Movie ModifyMovieDialog::getModifiedMovie() const
{
    std::string title = ui->titleLineEdit->text().toStdString();
    std::string description = ui->descriptionTextEdit->toPlainText().toStdString();
    int year = ui->yearSpinBox->value();
    int length = ui->lengthSpinBox->value();
    int rating = ui->ratingSlider->value();
    bool watched = ui->watchedCheckBox->isChecked();

    Genre genre = static_cast<Genre>(ui->genreComboBox->currentIndex());
    std::string directorId = ui->directorComboBox->currentData().toString().toStdString();

    std::vector<std::string> selectedActors;
    for (auto* checkBox : actorCheckBoxes) {
        if (checkBox->isChecked()) {
            selectedActors.push_back(checkBox->property("personId").toString().toStdString());
        }
    }

    return Movie(originalMovie.getId(), title, description, genre, directorId, year, rating, watched, length, selectedActors);
}

void ModifyMovieDialog::updateRatingLabel(int value)
{
    ui->ratingLabel->setText(QString::number(value));
}
