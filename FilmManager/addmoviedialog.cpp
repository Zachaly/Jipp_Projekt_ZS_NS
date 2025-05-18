#include "addmoviedialog.h"
#include "ui_addmoviedialog.h"

AddMovieDialog::AddMovieDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddMovieDialog)
{
    ui->setupUi(this);
}

AddMovieDialog::~AddMovieDialog()
{
    delete ui;
}
