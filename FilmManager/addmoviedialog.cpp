#include "addmoviedialog.h"
#include "ui_addmoviedialog.h"
#include "FilmManager_Domain/moviemanager.h"
#include "FilmManager_Domain/personmanager.h"
#include <QMessageBox>
using namespace std;

AddMovieDialog::AddMovieDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddMovieDialog)
{
    ui->setupUi(this);

    populateDirectors();
    populateActors();

    setWindowTitle("Dodaj nowy film");
    setModal(true);
    resize(500, 700);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddMovieDialog::onAccept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->ratingSlider, &QSlider::valueChanged, this, &AddMovieDialog::updateRatingLabel);

    ui->ratingLabel->setText(QString::number(ui->ratingSlider->value()));
}

AddMovieDialog::~AddMovieDialog()
{
    delete ui;
}

void AddMovieDialog::populateDirectors()
{
    ui->directorComboBox->clear();

    for (const auto& person : PersonManager::getPeople([](Person p) { return p.getIsDirector(); })) {
        QString displayName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
        .arg(QString::fromStdString(person.getLastName()));
        ui->directorComboBox->addItem(displayName, QString::fromStdString(person.getId()));
    }
}

void AddMovieDialog::populateActors()
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

        actorCheckBoxes.push_back(checkBox);
        ui->actorsLayout->addWidget(checkBox);
    }
}

vector<string> AddMovieDialog::getSelectedActors()
{
    vector<string> selectedActors;

    for (auto* checkBox : actorCheckBoxes) {
        if (checkBox->isChecked()) {
            selectedActors.push_back(checkBox->property("personId").toString().toStdString());
        }
    }

    return selectedActors;
}

void AddMovieDialog::onAccept()
{
    if (ui->titleLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Błąd", "Tytuł filmu nie może być pusty!");
        return;
    }

    if (ui->directorComboBox->currentIndex() == -1) {
        QMessageBox::warning(this, "Błąd", "Musisz wybrać reżysera!");
        return;
    }

    string title = ui->titleLineEdit->text().toStdString();
    string description = ui->descriptionTextEdit->toPlainText().toStdString();
    int year = ui->yearSpinBox->value();
    int length = ui->lengthSpinBox->value();
    int rating = ui->ratingSlider->value();
    bool watched = ui->watchedCheckBox->isChecked();

    Genre genre = static_cast<Genre>(ui->genreComboBox->currentIndex());

    string directorId = ui->directorComboBox->currentData().toString().toStdString();

    vector<string> selectedActors = getSelectedActors();

    Movie newMovie(title, description, genre, directorId, year, rating, watched, length, selectedActors);

    MovieManager::addMovie(newMovie);

    accept();
}

void AddMovieDialog::updateRatingLabel(int value)
{
    ui->ratingLabel->setText(QString::number(value));
}
