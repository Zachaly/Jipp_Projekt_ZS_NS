#include "modifyseriedialog.h"
#include "ui_modifyseriedialog.h"

ModifySerieDialog::ModifySerieDialog(Serie& serie, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifySerieDialog),
    serie(serie)
{
    ui->setupUi(this);
}

ModifySerieDialog::~ModifySerieDialog()
{
    delete ui;
}
