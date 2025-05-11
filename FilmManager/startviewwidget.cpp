#include "movielistviewwidget.h"
#include "peoplelistviewwidget.h"
#include "startviewwidget.h"
#include "ui_startviewwidget.h"

StartViewWidget::StartViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::StartViewWidget)
{
    ui->setupUi(this);
    connect(ui->peopleButton, SIGNAL(clicked()), this, SLOT(goToPeople()));
    connect(ui->moviesButton, SIGNAL(clicked()), this, SLOT(goToMovies()));
    connect(ui->seriesButton, SIGNAL(clicked()), this, SLOT(goToSeries()));
}

StartViewWidget::~StartViewWidget()
{
    delete ui;
}

void StartViewWidget::goToPeople()
{
    ((MainWindow*)parent())->changePage(new PeopleListViewWidget((MainWindow*)parent()));
}

void StartViewWidget::goToMovies()
{
    ((MainWindow*)parent())->changePage(new MovieListViewWidget((MainWindow*)parent()));
}

void StartViewWidget::goToSeries()
{

}
