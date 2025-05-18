#include "addepisodedialog.h"
#include "ui_addepisodedialog.h"

AddEpisodeDialog::AddEpisodeDialog(string serieId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEpisodeDialog),
    serieId(serieId)
{
    ui->setupUi(this);
}

AddEpisodeDialog::~AddEpisodeDialog()
{
    delete ui;
}
