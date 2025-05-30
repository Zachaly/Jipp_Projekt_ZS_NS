#include "movielistviewwidget.h"
#include "ui_movielistviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/moviemanager.h"
#include "addmoviedialog.h"
#include "modifymoviedialog.h"
#include "movieviewwidget.h"
#include "startviewwidget.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <algorithm>

using namespace std;

MovieListViewWidget::MovieListViewWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MovieListViewWidget)
{
    ui->setupUi(this);
    setupConnections();
    setupListWidget();
    populateSearchComboBox();
    refreshMovieList();
}

MovieListViewWidget::~MovieListViewWidget()
{
    delete ui;
}

void MovieListViewWidget::setupConnections()
{
    connect(ui->allMoviesRadio, &QRadioButton::clicked, this, &MovieListViewWidget::onFilterChanged);
    connect(ui->watchedMoviesRadio, &QRadioButton::clicked, this, &MovieListViewWidget::onFilterChanged);
    connect(ui->unwatchedMoviesRadio, &QRadioButton::clicked, this, &MovieListViewWidget::onFilterChanged);

    connect(ui->movieListWidget, &QListWidget::itemSelectionChanged, [this]() {
        bool hasSelection = !ui->movieListWidget->selectedItems().isEmpty();
        ui->modifyButton->setEnabled(hasSelection);
        ui->removeButton->setEnabled(hasSelection);
    });
}

void MovieListViewWidget::setupListWidget()
{
    ui->movieListWidget->setStyleSheet(
        "QListWidget {"
        "    outline: none;"
        "    border: 2px solid #dee2e6;"
        "    border-radius: 8px;"
        "    background-color: white;"
        "    selection-background-color: #e6f3ff;"
        "}"
        "QListWidget::item {"
        "    padding: 0px;"
        "    border-bottom: 1px solid #eee;"
        "    min-height: 120px;"
        "    margin: 2px;"
        "    border-radius: 6px;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #e6f3ff;"
        "    border: 2px solid #007bff;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "}"
        "QListWidget::item:selected:hover {"
        "    background-color: #cce7ff;"
        "    border: 2px solid #0056b3;"
        "}"
        );
}

void MovieListViewWidget::populateSearchComboBox()
{
    ui->searchTypeComboBox->clear();
    ui->searchTypeComboBox->addItem("Tytule", "title");
    ui->searchTypeComboBox->addItem("Reżyserze", "director");
    ui->searchTypeComboBox->addItem("Aktorze", "actor");
    ui->searchTypeComboBox->addItem("Gatunku", "genre");
    ui->searchTypeComboBox->addItem("Roku produkcji", "year");
}

QString MovieListViewWidget::getGenreIcon(Genre genre)
{
    switch (genre) {
    case Genre::Action: return "⚔️";
    case Genre::Adventure: return "🗺️";
    case Genre::Comedy: return "😄";
    case Genre::Drama: return "🎭";
    case Genre::Horror: return "👻";
    case Genre::Romance: return "💕";
    case Genre::SciFi: return "🚀";
    case Genre::Thriller: return "🔪";
    case Genre::Historical: return "🏛️";
    default: return "🎬";
    }
}

QString MovieListViewWidget::getGenreName(Genre genre)
{
    switch (genre) {
    case Genre::Action: return "Akcja";
    case Genre::Adventure: return "Przygodowy";
    case Genre::Comedy: return "Komedia";
    case Genre::Drama: return "Dramat";
    case Genre::Horror: return "Horror";
    case Genre::Romance: return "Romans";
    case Genre::SciFi: return "Sci-Fi";
    case Genre::Thriller: return "Thriller";
    case Genre::Historical: return "Historyczny";
    default: return "Nieznany";
    }
}

QString MovieListViewWidget::generateStarRating(double rating)
{
    int fullRating = static_cast<int>(round(rating));
    if (fullRating < 1) fullRating = 1;
    if (fullRating > 10) fullRating = 10;

    QString stars;
    for (int i = 0; i < fullRating; ++i) {
        stars += "⭐";
    }

    return stars;
}

void MovieListViewWidget::createMovieListItem(const Movie& movie)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setFixedHeight(110);

    QHBoxLayout* mainLayout = new QHBoxLayout(itemWidget);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(15);

    QLabel* genreIconLabel = new QLabel();
    genreIconLabel->setText(getGenreIcon(movie.getGenre()));
    genreIconLabel->setStyleSheet("font-size: 32px; color: #007bff;");
    genreIconLabel->setFixedSize(50, 50);
    genreIconLabel->setAlignment(Qt::AlignCenter);
    genreIconLabel->setStyleSheet(genreIconLabel->styleSheet() +
                                  "background-color: #f0f8ff; border-radius: 25px; border: 2px solid #007bff;");

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(5);

    QLabel* titleLabel = new QLabel();
    QString title = QString::fromStdString(movie.getTitle()).toUpper();
    titleLabel->setText(title);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #212529; margin-bottom: 5px;");

    QHBoxLayout* detailsLayout = new QHBoxLayout();
    detailsLayout->setSpacing(15);

    QLabel* genreLabel = new QLabel();
    genreLabel->setText(QString("gatunek: %1").arg(getGenreName(movie.getGenre())));
    genreLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    QLabel* yearLabel = new QLabel();
    yearLabel->setText(QString("rok: %1").arg(movie.getProductionYear()));
    yearLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    detailsLayout->addWidget(genreLabel);
    detailsLayout->addWidget(yearLabel);
    detailsLayout->addStretch();

    QLabel* directorLabel = new QLabel();
    try {
        Person& director = PersonManager::getPersonById(movie.getCreatorId());
        QString directorName = QString("%1 %2")
                                   .arg(QString::fromStdString(director.getFirstName()))
                                   .arg(QString::fromStdString(director.getLastName()));
        directorLabel->setText(QString("reżyser: %1").arg(directorName));
    } catch (...) {
        directorLabel->setText("reżyser: Nieznany");
    }
    directorLabel->setStyleSheet("font-size: 12px; color: #495057; font-weight: normal;");

    QLabel* actorsLabel = new QLabel();
    QString actorsText = "obsada: ";
    vector<string> actorIds = movie.getActorIds();
    int displayedActors = 0;

    for (const string& actorId : actorIds) {
        if (displayedActors >= 2) break;

        try {
            Person& actor = PersonManager::getPersonById(actorId);
            if (displayedActors > 0) actorsText += " / ";
            actorsText += QString("%1 %2")
                              .arg(QString::fromStdString(actor.getFirstName()))
                              .arg(QString::fromStdString(actor.getLastName()));
            displayedActors++;
        } catch (...) {
            // Skip invalid actor IDs
        }
    }

    if (displayedActors == 0) {
        actorsText += "Nieznana";
    }

    actorsLabel->setText(actorsText);
    actorsLabel->setStyleSheet("font-size: 12px; color: #495057; font-weight: normal;");

    infoLayout->addWidget(titleLabel);
    infoLayout->addLayout(detailsLayout);
    infoLayout->addWidget(directorLabel);
    infoLayout->addWidget(actorsLabel);
    infoLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    QHBoxLayout* ratingLayout = new QHBoxLayout();
    ratingLayout->setAlignment(Qt::AlignRight);

    int rating = static_cast<int>(round(movie.getMark()));
    if (rating < 1) rating = 1;
    if (rating > 10) rating = 10;

    QLabel* ratingLabel = new QLabel();
    ratingLabel->setText(QString("%1/10").arg(rating));
    ratingLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffc107; margin-right: 5px;");

    QLabel* starsLabel = new QLabel();
    starsLabel->setText(generateStarRating(movie.getMark()));
    starsLabel->setStyleSheet("font-size: 14px;");

    ratingLayout->addWidget(ratingLabel);
    ratingLayout->addWidget(starsLabel);

    QLabel* statusLabel = new QLabel();
    if (movie.getIsWatched()) {
        statusLabel->setText("✅ Obejrzany");
        statusLabel->setStyleSheet("font-size: 12px; color: #28a745; font-weight: bold; "
                                   "background-color: #d4edda; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #c3e6cb;");
    } else {
        statusLabel->setText("⏸️ Do obejrzenia");
        statusLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: bold; "
                                   "background-color: #f8f9fa; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #dee2e6;");
    }
    statusLabel->setAlignment(Qt::AlignRight);

    rightLayout->addLayout(ratingLayout);
    rightLayout->addWidget(statusLabel);
    rightLayout->addStretch();

    mainLayout->addWidget(genreIconLabel);
    mainLayout->addLayout(infoLayout, 1);
    mainLayout->addLayout(rightLayout);

    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::UserRole, QString::fromStdString(movie.getId()));
    item->setSizeHint(itemWidget->sizeHint());

    ui->movieListWidget->addItem(item);
    ui->movieListWidget->setItemWidget(item, itemWidget);
}

void MovieListViewWidget::displayMovies(const std::vector<Movie>& movies)
{
    ui->movieListWidget->clear();
    currentMovies = movies;

    for (const auto& movie : movies) {
        createMovieListItem(movie);
    }
}

void MovieListViewWidget::updateMovieList()
{
    vector<Movie> filteredMovies = getFilteredMovies();
    displayMovies(filteredMovies);
}

vector<Movie> MovieListViewWidget::getFilteredMovies()
{
    vector<Movie> result;

    if (ui->watchedMoviesRadio->isChecked()) {
        result = MovieManager::filterByWatched(true);
    } else if (ui->unwatchedMoviesRadio->isChecked()) {
        result = MovieManager::filterByWatched(false);
    } else {
        result = MovieManager::getAllMovies();
    }

    return result;
}

void MovieListViewWidget::searchMovies()
{
    QString searchText = ui->searchLineEdit->text().trimmed();
    QString searchType = ui->searchTypeComboBox->currentData().toString();

    vector<Movie> searchResults;

    if (searchText.isEmpty()) {
        searchResults = getFilteredMovies();
    } else {
        if (searchType == "title") {
            searchResults = MovieManager::filterByTitle(searchText.toStdString());
        } else if (searchType == "director") {
            string directorId;
            vector<Person> people = PersonManager::getPeople();
            for (const auto& person : people) {
                QString fullName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
                .arg(QString::fromStdString(person.getLastName()));
                if (fullName.toLower().contains(searchText.toLower())) {
                    directorId = person.getId();
                    break;
                }
            }
            if (!directorId.empty()) {
                searchResults = MovieManager::filterByDirector(directorId);
            }
        } else if (searchType == "actor") {
            string actorId;
            vector<Person> people = PersonManager::getPeople();
            for (const auto& person : people) {
                QString fullName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
                .arg(QString::fromStdString(person.getLastName()));
                if (fullName.toLower().contains(searchText.toLower())) {
                    actorId = person.getId();
                    break;
                }
            }
            if (!actorId.empty()) {
                searchResults = MovieManager::filterByActor(actorId);
            }
        } else if (searchType == "genre") {
            QStringList genres = {"Adventure", "Action", "Comedy", "Drama", "Horror", "Romance", "Sci-Fi", "Thriller", "Historical"};
            for (int i = 0; i < genres.size(); ++i) {
                if (genres[i].toLower().contains(searchText.toLower())) {
                    searchResults = MovieManager::filterByGenre(static_cast<Genre>(i));
                    break;
                }
            }
        } else if (searchType == "year") {
            bool ok;
            int year = searchText.toInt(&ok);
            if (ok) {
                searchResults = MovieManager::filterByYear(year);
            }
        }

        if (ui->watchedMoviesRadio->isChecked()) {
            searchResults.erase(remove_if(searchResults.begin(), searchResults.end(),
                                          [](const Movie& m) { return !m.getIsWatched(); }),
                                searchResults.end());
        } else if (ui->unwatchedMoviesRadio->isChecked()) {
            searchResults.erase(remove_if(searchResults.begin(), searchResults.end(),
                                          [](const Movie& m) { return m.getIsWatched(); }),
                                searchResults.end());
        }
    }

    displayMovies(searchResults);
}

void MovieListViewWidget::addNewMovie()
{
    AddMovieDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshMovieList();
    }
}

void MovieListViewWidget::modifySelectedMovie()
{
    QListWidgetItem* selectedItem = ui->movieListWidget->currentItem();
    if (!selectedItem) {
        return;
    }

    QString movieId = selectedItem->data(Qt::UserRole).toString();
    try {
        Movie& movie = MovieManager::getMovieById(movieId.toStdString());

        ModifyMovieDialog dialog(movie, this);
        if (dialog.exec() == QDialog::Accepted) {
            Movie modifiedMovie = dialog.getModifiedMovie();
            MovieManager::updateMovie(movieId.toStdString(), modifiedMovie);
            refreshMovieList();
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
    }
}

void MovieListViewWidget::viewSelectedMovie()
{
    QListWidgetItem* selectedItem = ui->movieListWidget->currentItem();
    if (!selectedItem) {
        return;
    }

    QString movieId = selectedItem->data(Qt::UserRole).toString();
    try {
        Movie& movie = MovieManager::getMovieById(movieId.toStdString());

        MovieViewWidget* movieViewWidget = new MovieViewWidget((MainWindow*)parent());
        movieViewWidget->displayMovie(movie);

        connect(movieViewWidget, &MovieViewWidget::editMovieRequested,
                this, [this](const std::string& movieId) {

                    try {
                        Movie& movie = MovieManager::getMovieById(movieId);
                        ModifyMovieDialog dialog(movie, this);
                        if (dialog.exec() == QDialog::Accepted) {
                            Movie modifiedMovie = dialog.getModifiedMovie();
                            MovieManager::updateMovie(movieId, modifiedMovie);
                            refreshMovieList();
                        }
                    } catch (const std::exception& e) {
                        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
                    }
                });

        ((MainWindow*)parent())->changePage(movieViewWidget);

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
    }
}

void MovieListViewWidget::removeSelectedMovie()
{
    QListWidgetItem* selectedItem = ui->movieListWidget->currentItem();
    if (!selectedItem) {
        return;
    }

    QString movieId = selectedItem->data(Qt::UserRole).toString();
    try {
        Movie& movie = MovieManager::getMovieById(movieId.toStdString());

        int ret = QMessageBox::question(this, "Usuń film",
                                        QString("Czy na pewno chcesz usunąć film \"%1\"?")
                                            .arg(QString::fromStdString(movie.getTitle())),
                                        QMessageBox::Yes | QMessageBox::No,
                                        QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            MovieManager::removeMovie(movieId.toStdString());
            refreshMovieList();
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
    }
}

void MovieListViewWidget::onFilterChanged()
{
    updateMovieList();
}

void MovieListViewWidget::onMovieDoubleClicked()
{
    viewSelectedMovie();
}

void MovieListViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new StartViewWidget((MainWindow*)parent()));
}

void MovieListViewWidget::refreshMovieList()
{
    updateMovieList();
}
