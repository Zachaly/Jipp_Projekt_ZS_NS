#include "serielistviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "addseriedialog.h"
#include "modifyseriedialog.h"
#include "serieviewwidget.h"
#include "startviewwidget.h"
#include "ui_serielistviewwidget.h"
#include "FilmManager_Domain/seriesmanager.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"

#include <QLabel>
#include <QMessageBox>

SerieListViewWidget::SerieListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieListViewWidget)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->addSerieButton, SIGNAL(clicked()), this, SLOT(addSerie()));
    connect(ui->serieList, &QListWidget::itemDoubleClicked,  this, &SerieListViewWidget::goToSerie);
    connect(ui->modifyButton, &QPushButton::clicked, this, &SerieListViewWidget::modifySelectedSerie);
    connect(ui->deleteButton, &QPushButton::clicked, this, &SerieListViewWidget::deleteSelectedSerie);

    connect(ui->allSeriesRadio, &QRadioButton::clicked, this, &SerieListViewWidget::updateList);
    connect(ui->watchedSeriesRadio, &QRadioButton::clicked, this, &SerieListViewWidget::updateList);
    connect(ui->unwatchedSeriesRadio, &QRadioButton::clicked, this, &SerieListViewWidget::updateList);
    connect(ui->searchButton, &QPushButton::clicked, this, &SerieListViewWidget::searchSeries);

    auto noDirectors = PersonManager::getPeople([](Person p) { return p.getIsDirector(); }).empty();

    ui->addSerieButton->setDisabled(noDirectors);

    connect(ui->serieList, &QListWidget::itemSelectionChanged, [this]() {
        bool hasSelection = !ui->serieList->selectedItems().isEmpty();
        ui->modifyButton->setEnabled(hasSelection);
        ui->deleteButton->setEnabled(hasSelection);
    });

    ui->serieList->setStyleSheet(
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

    ui->searchTypeComboBox->clear();
    ui->searchTypeComboBox->addItem("Tytule", "title");
    ui->searchTypeComboBox->addItem("Twórcy", "creator");
    ui->searchTypeComboBox->addItem("Gatunku", "genre");
    ui->searchTypeComboBox->addItem("Roku produkcji", "year");

    updateList();
}

QString SerieListViewWidget::getGenreIcon(Genre genre)
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

void SerieListViewWidget::searchSeries()
{
    QString searchText = ui->searchLineEdit->text().trimmed();
    QString searchType = ui->searchTypeComboBox->currentData().toString();

    vector<Serie> searchResults;

    if (searchText.isEmpty()) {
        if(ui->allSeriesRadio->isChecked())
        {
            searchResults = SeriesManager::getSeries();
        }
        else if(ui->watchedSeriesRadio->isChecked())
        {
            searchResults = SeriesManager::getSeries([](Serie s) { return s.getIsWatched(); });
        }
        else
        {
            searchResults = SeriesManager::getSeries([](Serie s) { return !s.getIsWatched(); });
        }
    } else {
        if (searchType == "title") {
            string title = searchText.toStdString();
            searchResults = SeriesManager::getSeries([title](Serie s) {
                string lowerTitle = title;
                transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(),
                               [](unsigned char c){ return std::tolower(c); });

                std::string serieTitle = s.getTitle();
                std::transform(serieTitle.begin(), serieTitle.end(), serieTitle.begin(),
                               [](unsigned char c){ return std::tolower(c); });

                return serieTitle.find(lowerTitle) != std::string::npos;
            });
        }
        else if (searchType == "creator") {
            string creatorId;
            vector<Person> people = PersonManager::getPeople();
            for (const auto& person : people) {
                QString fullName = QString("%1 %2").arg(QString::fromStdString(person.getFirstName()))
                .arg(QString::fromStdString(person.getLastName()));
                if (fullName.toLower().contains(searchText.toLower())) {
                    creatorId = person.getId();
                    break;
                }
            }
            if (!creatorId.empty()) {
                searchResults = SeriesManager::getSeries([creatorId](Serie s) {
                    return creatorId == s.getCreatorId();
                });
            }
        }
        else if (searchType == "genre") {
            QStringList genres = {"Adventure", "Action", "Comedy", "Drama", "Horror", "Romance", "Sci-Fi", "Thriller", "Historical"};
            for (int i = 0; i < genres.size(); ++i) {
                if (genres[i].toLower().contains(searchText.toLower())) {
                    auto genre = static_cast<Genre>(i);
                    searchResults = SeriesManager::getSeries([genre](Serie s) { return s.getGenre() == genre; });
                    break;
                }
            }
        }
        else if (searchType == "year") {
            bool ok;
            int year = searchText.toInt(&ok);
            if (ok) {
                searchResults = SeriesManager::getSeries([year](Serie s) {
                    return s.getProductionYear() == year;
                });
            };
        }
    }

    ui->serieList->clear();

    for(auto& s : searchResults)
    {
        addSerieListItem(s);
    }
}

QString SerieListViewWidget::getGenreName(Genre genre)
{
    switch (genre) {
    //case Genre::Action: return "Akcja";
    case Genre::Adventure: return "Przygodowy";
    //case Genre::Comedy: return "Komedia";
    //case Genre::Drama: return "Dramat";
    //case Genre::Horror: return "Horror";
    //case Genre::Romance: return "Romans";
    //case Genre::SciFi: return "Sci-Fi";
    //case Genre::Thriller: return "Thriller";
    //case Genre::Historical: return "Historyczny";
    default: return "Nieznany";
    }
}

QString SerieListViewWidget::getStatusName(SerieStatus status)
{
    switch (status) {
    case SerieStatus::Cancelled: return "Anulowany";
    case SerieStatus::Ended: return "Zakończony";
    case SerieStatus::Ongoing: return "Trwający";
    default: return "Nieznany";
    }
}

QString SerieListViewWidget::generateStarRating(double rating)
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

void SerieListViewWidget::addSerieListItem(const Serie& serie)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setFixedHeight(110);

    QHBoxLayout* mainLayout = new QHBoxLayout(itemWidget);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(15);

    QLabel* genreIconLabel = new QLabel();
    genreIconLabel->setText(getGenreIcon(serie.getGenre()));
    genreIconLabel->setStyleSheet("font-size: 32px; color: #007bff;");
    genreIconLabel->setFixedSize(50, 50);
    genreIconLabel->setAlignment(Qt::AlignCenter);
    genreIconLabel->setStyleSheet(genreIconLabel->styleSheet() +
                                  "background-color: #f0f8ff; border-radius: 25px; border: 2px solid #007bff;");

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(5);

    QLabel* titleLabel = new QLabel();
    QString title = QString::fromStdString(serie.getTitle()).toUpper();
    titleLabel->setText(title);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #212529; margin-bottom: 5px;");

    QHBoxLayout* detailsLayout = new QHBoxLayout();
    detailsLayout->setSpacing(15);

    QLabel* genreLabel = new QLabel();
    genreLabel->setText(QString("gatunek: %1").arg(getGenreName(serie.getGenre())));
    genreLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    QLabel* yearLabel = new QLabel();
    yearLabel->setText(QString("rok: %1").arg(serie.getProductionYear()));
    yearLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    auto* statusLabel = new QLabel();

    statusLabel->setText(QString("status: %1").arg(getStatusName(serie.getStatus())));
    statusLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    detailsLayout->addWidget(genreLabel);
    detailsLayout->addWidget(yearLabel);
    detailsLayout->addWidget(statusLabel);
    detailsLayout->addStretch();

    QLabel* directorLabel = new QLabel();
    try {
        Person& director = PersonManager::getPersonById(serie.getCreatorId());
        QString directorName = QString("%1 %2")
                                   .arg(QString::fromStdString(director.getFirstName()))
                                   .arg(QString::fromStdString(director.getLastName()));
        directorLabel->setText(QString("twórca: %1").arg(directorName));
    } catch (...) {
        directorLabel->setText("twórca: Nieznany");
    }
    directorLabel->setStyleSheet("font-size: 12px; color: #495057; font-weight: normal;");

    auto* seasonLabel = new QLabel();

    seasonLabel->setText(QString("sezony: %1").arg(to_string(serie.getSeasonCount())));
    seasonLabel->setStyleSheet("font-size: 12px; color: #495057; font-weight: normal;");

    infoLayout->addWidget(titleLabel);
    infoLayout->addLayout(detailsLayout);
    infoLayout->addWidget(directorLabel);
    infoLayout->addWidget(seasonLabel);
    infoLayout->addStretch();

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);

    QHBoxLayout* ratingLayout = new QHBoxLayout();
    ratingLayout->setAlignment(Qt::AlignRight);

    int rating = static_cast<int>(round(serie.getMark()));
    if (rating < 1) rating = 1;
    if (rating > 10) rating = 10;

    QLabel* ratingLabel = new QLabel();
    ratingLabel->setText(QString("%1/10").arg(rating));
    ratingLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffc107; margin-right: 5px;");

    QLabel* starsLabel = new QLabel();
    starsLabel->setText(generateStarRating(serie.getMark()));
    starsLabel->setStyleSheet("font-size: 14px;");

    ratingLayout->addWidget(ratingLabel);
    ratingLayout->addWidget(starsLabel);

    QLabel* watchedLabel = new QLabel();
    if (serie.getIsWatched()) {
        watchedLabel->setText("✅ Obejrzany");
        watchedLabel->setStyleSheet("font-size: 12px; color: #28a745; font-weight: bold; "
                                   "background-color: #d4edda; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #c3e6cb;");
    } else {
        watchedLabel->setText("⏸️ Do obejrzenia");
        watchedLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: bold; "
                                   "background-color: #f8f9fa; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #dee2e6;");
    }
    watchedLabel->setAlignment(Qt::AlignRight);

    rightLayout->addLayout(ratingLayout);
    rightLayout->addWidget(statusLabel);
    rightLayout->addStretch();

    mainLayout->addWidget(genreIconLabel);
    mainLayout->addLayout(infoLayout, 1);
    mainLayout->addLayout(rightLayout);

    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::UserRole, QString::fromStdString(serie.getId()));
    item->setSizeHint(itemWidget->sizeHint());

    ui->serieList->addItem(item);
    ui->serieList->setItemWidget(item, itemWidget);
}

void SerieListViewWidget::deleteSelectedSerie()
{
    QListWidgetItem* selectedItem = ui->serieList->currentItem();
    if (!selectedItem) {
        return;
    }

    QString serieId = selectedItem->data(Qt::UserRole).toString();
    try {
        Serie& serie = SeriesManager::getById(serieId.toStdString());

        int ret = QMessageBox::question(this, "Usuń serial",
                                        QString("Czy na pewno chcesz usunąć serial \"%1\"?")
                                            .arg(QString::fromStdString(serie.getTitle())),
                                        QMessageBox::Yes | QMessageBox::No,
                                        QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            SeriesManager::removeSerie(serieId.toStdString());
            updateList();
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć serialu: %1").arg(e.what()));
    }
}

void SerieListViewWidget::modifySelectedSerie()
{
    QListWidgetItem* selectedItem = ui->serieList->currentItem();
    if (!selectedItem) {
        return;
    }

    QString serieId = selectedItem->data(Qt::UserRole).toString();
    try {
        Serie& movie = SeriesManager::getById(serieId.toStdString());

        ModifySerieDialog dialog(movie, this);
        if (dialog.exec() == QDialog::Accepted) {
            updateList();
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
    }
}

SerieListViewWidget::~SerieListViewWidget()
{
    delete ui;
}

void SerieListViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new StartViewWidget((MainWindow*)parent()));
}

void SerieListViewWidget::goToSerie()
{
    auto id = fromQString(ui->serieList->currentItem()->data(Qt::UserRole).toString());

    Serie& serie = SeriesManager::getById(id);
    ((MainWindow*)parent())->changePage(new SerieViewWidget(serie, (MainWindow*)parent()));
}

void SerieListViewWidget::addSerie()
{
    auto dialog = AddSerieDialog(this);
    if(dialog.exec() == QDialog::Accepted)
    {
        updateList();
    }
}

void SerieListViewWidget::updateList()
{
    ui->serieList->clear();

    vector<Serie> series;

    if(ui->allSeriesRadio->isChecked())
    {
        series = SeriesManager::getSeries();
    }
    else if(ui->watchedSeriesRadio->isChecked()){
        series = SeriesManager::getSeries([](Serie s) { return s.getIsWatched(); });
    }
    else {
        series = SeriesManager::getSeries([](Serie s) { return !s.getIsWatched(); });
    }


    for(auto& s : series)
    {
        addSerieListItem(s);
    }
}
