#include "modifyepisodedialog.h"
#include "ui_modifyepisodedialog.h"

ModifyEpisodeDialog::ModifyEpisodeDialog(Episode& episode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyEpisodeDialog),
    episode(episode)
{
    ui->setupUi(this);
}

ModifyEpisodeDialog::~ModifyEpisodeDialog()
{
    delete ui;
}
