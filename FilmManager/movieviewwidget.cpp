#include "modifymoviedialog.h"
#include "movielistviewwidget.h"
#include "movieviewwidget.h"
#include "ui_movieviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/moviemanager.h"
#include <QApplication>
#include "mainwindow.h"
#include <QWidget>

using namespace std;

MovieViewWidget::MovieViewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovieViewWidget)
{
    ui->setupUi(this);
    clearDisplay();

    connect(ui->editButton, &QPushButton::clicked, this, &MovieViewWidget::editCurrentMovie);
    connect(ui->backButton, &QPushButton::clicked, this, &MovieViewWidget::goBack);
}

MovieViewWidget::~MovieViewWidget()
{
    delete ui;
}

void MovieViewWidget::displayMovie(const Movie& movie)
{
    currentMovieId = movie.getId();

    ui->titleLabel->setText(QString::fromStdString(movie.getTitle()));
    ui->yearLabel->setText(QString::number(movie.getProductionYear()));
    ui->lengthLabel->setText(QString("%1 minut").arg(movie.getLength()));

    QStringList genres = {"Adventure", "Action", "Comedy", "Drama", "Horror", "Romance", "Sci-Fi", "Thriller", "Historical"};
    int genreIndex = static_cast<int>(movie.getGenre());
    if (genreIndex >= 0 && genreIndex < genres.size()) {
        ui->genreLabel->setText(genres[genreIndex]);
    } else {
        ui->genreLabel->setText("Nieznany");
    }

    QString ratingText = QString("%1/10 ").arg(movie.getMark());
    int filledStars = movie.getMark();

    QString starColor;
    if (movie.getMark() >= 8) starColor = "color: gold;";
    else if (movie.getMark() >= 6) starColor = "color: orange;";
    else if (movie.getMark() >= 4) starColor = "color: yellow;";
    else starColor = "color: gray;";

    for (int i = 0; i < filledStars; ++i) {
        ratingText += QString("<span style='%1'>★</span>").arg(starColor);
    }
    for (int i = filledStars; i < 10; ++i) {
        ratingText += "<span style='color: lightgray;'>☆</span>";
    }
    ui->ratingLabel->setText(ratingText);

    if (movie.getIsWatched()) {
        ui->watchedLabel->setText("Obejrzany ✓");
        ui->watchedLabel->setStyleSheet("color: green; font-weight: bold;");
    } else {
        ui->watchedLabel->setText("Nieobejrzany");
        ui->watchedLabel->setStyleSheet("color: red;");
    }


    updateDirectorInfo(movie.getCreatorId());

    ui->descriptionText->setPlainText(QString::fromStdString(movie.getDescription()));

    updateActorsList(movie.getActorIds());

    ui->editButton->setEnabled(true);
}

void MovieViewWidget::clearDisplay()
{
    currentMovieId.clear();

    ui->titleLabel->setText("Brak wybranego filmu");
    ui->yearLabel->setText("-");
    ui->lengthLabel->setText("-");
    ui->genreLabel->setText("-");
    ui->ratingLabel->setText("-");
    ui->watchedLabel->setText("-");
    ui->watchedLabel->setStyleSheet("");

    ui->directorLabel->setText("Brak informacji");
    ui->descriptionText->clear();
    ui->actorsLabel->setText("Brak informacji");

    ui->editButton->setEnabled(false);
}

void MovieViewWidget::updateActorsList(const vector<string>& actorIds)
{
    if (actorIds.empty()) {
        ui->actorsLabel->setText("Brak informacji o obsadzie");
        return;
    }

    QStringList actorNames;
    for (const auto& actorId : actorIds) {
        Person& person = PersonManager::getPersonById(actorId);
        if (!person.getId().empty()) {
            QString fullName = QString("%1 %2")
            .arg(QString::fromStdString(person.getFirstName()))
                .arg(QString::fromStdString(person.getLastName()));
            actorNames.append(fullName);
        }
    }

    if (actorNames.isEmpty()) {
        ui->actorsLabel->setText("Brak informacji o obsadzie");
    } else {
        ui->actorsLabel->setText(actorNames.join(", "));
    }
}

void MovieViewWidget::updateDirectorInfo(const string& directorId)
{
    if (directorId.empty()) {
        ui->directorLabel->setText("Brak informacji o reżyserze");
        return;
    }

    Person& director = PersonManager::getPersonById(directorId);
    if (!director.getId().empty()) {
        QString directorInfo = QString("%1 %2")
        .arg(QString::fromStdString(director.getFirstName()))
            .arg(QString::fromStdString(director.getLastName()));


        if (director.getBirthYear() > 0) {
            directorInfo += QString(" (ur. %1)").arg(director.getBirthYear());
        }

        ui->directorLabel->setText(directorInfo);
    } else {
        ui->directorLabel->setText("Brak informacji o reżyserze");
    }
}

void MovieViewWidget::editCurrentMovie()
{
    if (!currentMovieId.empty()) {
        Movie& movie = MovieManager::getMovieById(currentMovieId);
        if (!movie.getId().empty()) {
            ModifyMovieDialog dialog(movie, this);
            if (dialog.exec() == QDialog::Accepted) {
                Movie modifiedMovie = dialog.getModifiedMovie();
                MovieManager::updateMovie(modifiedMovie);
                displayMovie(modifiedMovie);
            }
        }
    }
}

void MovieViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new MovieListViewWidget((MainWindow*)parent()));
}
