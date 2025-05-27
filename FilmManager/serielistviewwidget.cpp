#include "serielistviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "addseriedialog.h"
#include "serieviewwidget.h"
#include "startviewwidget.h"
#include "ui_serielistviewwidget.h"
#include "FilmManager_Domain/seriesmanager.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"

SerieListViewWidget::SerieListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieListViewWidget)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->addSerieButton, SIGNAL(clicked()), this, SLOT(addSerie()));
    connect(ui->serieList ,&QListWidget::itemDoubleClicked,  this, &SerieListViewWidget::goToSerie);

    auto noDirectors = PersonManager::getPeople([](Person p) { return p.getIsDirector(); }).empty();

    ui->addSerieButton->setDisabled(noDirectors);

    updateList();
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
    auto* dialog = new AddSerieDialog(this);
    connect(dialog, &AddSerieDialog::accepted, this, &SerieListViewWidget::updateList);

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void SerieListViewWidget::updateList()
{
    ui->serieList->clear();
    for(auto& s : SeriesManager::getSeries())
    {
        QString label = toQString(s.getTitle());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, toQString(s.getId()));
        ui->serieList->addItem(item);
    }
}
