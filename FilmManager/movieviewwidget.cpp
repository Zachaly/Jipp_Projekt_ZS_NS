#include "modifymoviedialog.h"
#include "movielistviewwidget.h"
#include "movieviewwidget.h"
#include "ui_movieviewwidget.h"

MovieViewWidget::MovieViewWidget(Movie& movie, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::MovieViewWidget),
    movie(movie)
{
    ui->setupUi(this);
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->modifyMovieButton, SIGNAL(clicked()), this, SLOT(modifyMovie()));
}

MovieViewWidget::~MovieViewWidget()
{
    delete ui;
}

void MovieViewWidget::modifyMovie()
{
    auto dialog = new ModifyMovieDialog(movie, this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void MovieViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new MovieListViewWidget((MainWindow*)parent()));
}
