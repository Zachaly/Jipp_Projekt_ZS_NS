#include "FilmManager_Domain/episode.h"
#include "FilmManager_Domain/personmanager.h"
#include "addepisodedialog.h"
#include "episodeviewwidget.h"
#include "modifyseriedialog.h"
#include "serielistviewwidget.h"
#include "serieviewwidget.h"
#include "ui_serieviewwidget.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serieStatus.h"
#include "FilmManager_Domain/episodemanager.h"

#include <QMessageBox>

SerieViewWidget::SerieViewWidget(Serie& serie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieViewWidget),
    serie(serie)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifySeriesButton, SIGNAL(clicked()), this, SLOT(modifySeries()));
    connect(ui->addEpisodeButton, SIGNAL(clicked()), this, SLOT(addEpisode()));
    connect(ui->episodeList ,&QListWidget::itemDoubleClicked,  this, &SerieViewWidget::goToEpisode);
    connect(ui->deleteEpisodeButton, &QPushButton::clicked, this, &SerieViewWidget::deleteSelectedEpisode);
    connect(ui->allEpisodesRadio, &QRadioButton::clicked, this, &SerieViewWidget::refreshEpisodes);
    connect(ui->watchedEpisodesRadio, &QRadioButton::clicked, this, &SerieViewWidget::refreshEpisodes);
    connect(ui->unwatchedEpisodesRadio, &QRadioButton::clicked, this, &SerieViewWidget::refreshEpisodes);

    connect(ui->episodeList, &QListWidget::itemSelectionChanged, [this]() {
        bool hasSelection = !ui->episodeList->selectedItems().isEmpty();
        ui->deleteEpisodeButton->setEnabled(hasSelection);
    });

    ui->episodeList->setStyleSheet(
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

    updateUi();
}

SerieViewWidget::~SerieViewWidget()
{
    delete ui;
}

void SerieViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new SerieListViewWidget((MainWindow*)parent()));
}

void SerieViewWidget::goToEpisode()
{
    auto id = fromQString(ui->episodeList->currentItem()->data(Qt::UserRole).toString());
    Episode& episode = EpisodeManager::getById(id);
    ((MainWindow*)parent())->changePage(new EpisodeViewWidget(episode, (MainWindow*)parent()));
}

QString SerieViewWidget::generateStarRating(double rating)
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

void SerieViewWidget::deleteSelectedEpisode()
{
    QListWidgetItem* selectedItem = ui->episodeList->currentItem();
    if (!selectedItem) {
        return;
    }

    QString episodeId = selectedItem->data(Qt::UserRole).toString();
    try {
        Episode& episode = EpisodeManager::getById(episodeId.toStdString());

        int ret = QMessageBox::question(this, "Usuń odcinek",
                                        QString("Czy na pewno chcesz usunąć odcinek \"%1\"?")
                                            .arg(QString::fromStdString(serie.getTitle())),
                                        QMessageBox::Yes | QMessageBox::No,
                                        QMessageBox::No);

        if (ret == QMessageBox::Yes) {
            EpisodeManager::removeEpisode(episodeId.toStdString());
            updateUi();
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć filmu: %1").arg(e.what()));
    }
}

void SerieViewWidget::refreshEpisodes()
{
    vector<Episode> episodes;

    string serieId = serie.getId();

    if(ui->allEpisodesRadio->isChecked())
    {
        episodes = EpisodeManager::getEpisodes([serieId](Episode e) { return e.getSeriesId() == serieId; });
    }
    else
    {
        bool watched = ui->watchedEpisodesRadio->isChecked();
        episodes = EpisodeManager::getEpisodes([watched, serieId](Episode e) { return e.getIsWatched() == watched && e.getSeriesId() == serieId;; });
    }

    ui->episodeList->clear();

    for(auto& ep : episodes){
        addEpisodeListItem(ep);
    }
}

QString SerieViewWidget::getGenreName(Genre genre)
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

QString SerieViewWidget::getStatusName(SerieStatus status)
{
    switch (status) {
    case SerieStatus::Cancelled: return "Anulowany";
    case SerieStatus::Ended: return "Zakończony";
    case SerieStatus::Ongoing: return "Trwający";
    default: return "Nieznany";
    }
}

void SerieViewWidget::addEpisodeListItem(const Episode &episode)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setFixedHeight(110);

    QHBoxLayout* mainLayout = new QHBoxLayout(itemWidget);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(15);

    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(5);

    QLabel* titleLabel = new QLabel();
    QString title = QString::fromStdString(episode.getTitle()).toUpper();
    titleLabel->setText(title);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #212529; margin-bottom: 5px;");

    QHBoxLayout* detailsLayout = new QHBoxLayout();
    detailsLayout->setSpacing(15);

    QLabel* yearLabel = new QLabel();
    yearLabel->setText(QString("rok: %1").arg(episode.getProductionYear()));
    yearLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    QLabel* numberLabel = new QLabel();
    yearLabel->setText(QString("nr odcinka: %1").arg(episode.getEpisodeNumber()));
    yearLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    QLabel* seasonLabel = new QLabel();
    yearLabel->setText(QString("sezon: %1").arg(episode.getSeasonNumber()));
    yearLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");

    detailsLayout->addWidget(yearLabel);
    detailsLayout->addWidget(numberLabel);
    detailsLayout->addWidget(seasonLabel);
    detailsLayout->addStretch();

    QLabel* directorLabel = new QLabel();
    try {
        Person& director = PersonManager::getPersonById(episode.getCreatorId());
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
    vector<string> actorIds = episode.getActorIds();
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

    int rating = static_cast<int>(round(episode.getMark()));
    if (rating < 1) rating = 1;
    if (rating > 10) rating = 10;

    QLabel* ratingLabel = new QLabel();
    ratingLabel->setText(QString("%1/10").arg(rating));
    ratingLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffc107; margin-right: 5px;");

    QLabel* starsLabel = new QLabel();
    starsLabel->setText(generateStarRating(episode.getMark()));
    starsLabel->setStyleSheet("font-size: 14px;");

    ratingLayout->addWidget(ratingLabel);
    ratingLayout->addWidget(starsLabel);

    QLabel* statusLabel = new QLabel();
    if (episode.getIsWatched()) {
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

    mainLayout->addLayout(infoLayout, 1);
    mainLayout->addLayout(rightLayout);

    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::UserRole, QString::fromStdString(episode.getId()));
    item->setSizeHint(itemWidget->sizeHint());

    ui->episodeList->addItem(item);
    ui->episodeList->setItemWidget(item, itemWidget);
}

void SerieViewWidget::modifySeries()
{
    auto dialog = new ModifySerieDialog(serie, this);
    connect(dialog, &ModifySerieDialog::accepted, this, &SerieViewWidget::updateUi);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void SerieViewWidget::addEpisode()
{
    auto dialog = new AddEpisodeDialog(serie.getId(), (MainWindow*)parent());
    connect(dialog, &AddEpisodeDialog::accepted, this, &SerieViewWidget::updateUi);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void SerieViewWidget::updateUi()
{
    auto& creator = PersonManager::getPersonById(serie.getCreatorId());

    refreshEpisodes();

    ui->creatorValueLabel->setText(toQString(creator.getFirstName() + " " + creator.getLastName()));
    ui->genreValueLabel->setText(getGenreName(serie.getGenre()));
    ui->isWatchedValueLabel->setText(serie.getIsWatched() ? "Tak" : "Nie");
    ui->markValueLabel->setText(toQString(to_string(serie.getMark())));
    ui->descriptionLabel->setText(toQString(serie.getDescription()));
    ui->titleLabel->setText(toQString(serie.getTitle()));
    ui->productionYearValueLabel->setText(toQString(to_string(serie.getProductionYear())));
    ui->seasonCountLabel->setText(toQString(to_string(serie.getSeasonCount())));
    ui->statusValueLabel->setText(getStatusName(serie.getStatus()));
}
