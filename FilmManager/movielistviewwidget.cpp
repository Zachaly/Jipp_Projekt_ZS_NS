#include "FilmManager_Domain/movie.h"
#include "addmoviedialog.h"
#include "movielistviewwidget.h"
#include "movieviewwidget.h"
#include "startviewwidget.h"
#include "ui_movielistviewwidget.h"

MovieListViewWidget::MovieListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::MovieListViewWidget)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->listPlaceholderButton, SIGNAL(clicked()), this, SLOT(goToMovie()));
    connect(ui->addMovieButton, SIGNAL(clicked()), this, SLOT(addMovie()));
}

MovieListViewWidget::~MovieListViewWidget()
{
    delete ui;
}

void MovieListViewWidget::addMovie()
{
    auto dialog = new AddMovieDialog(this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MovieListViewWidget::goToMovie()
{
    Movie movie;
    ((MainWindow*)parent())->changePage(new MovieViewWidget(movie, (MainWindow*)parent()));
}

void MovieListViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new StartViewWidget((MainWindow*)parent()));
}
