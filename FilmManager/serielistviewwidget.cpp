#include "serielistviewwidget.h"
#include "FilmManager_Domain/serie.h"
#include "addseriedialog.h"
#include "serieviewwidget.h"
#include "startviewwidget.h"
#include "ui_serielistviewwidget.h"

SerieListViewWidget::SerieListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::SerieListViewWidget)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->listMockButton, SIGNAL(clicked()), this, SLOT(goToSerie()));
    connect(ui->addSerieButton, SIGNAL(clicked()), this, SLOT(addSerie()));
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
    Serie serie;
    ((MainWindow*)parent())->changePage(new SerieViewWidget(serie, (MainWindow*)parent()));
}

void SerieListViewWidget::addSerie()
{
    auto dialog = new AddSerieDialog(this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}
