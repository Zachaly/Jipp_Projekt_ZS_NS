#include "modifymoviedialog.h"
#include "ui_modifymoviedialog.h"

ModifyMovieDialog::ModifyMovieDialog(Movie& movie, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyMovieDialog),
    movie(movie)
{
    ui->setupUi(this);
}

ModifyMovieDialog::~ModifyMovieDialog()
{
    delete ui;
}
