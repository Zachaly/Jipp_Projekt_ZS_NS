#include "addseriedialog.h"
#include "ui_addseriedialog.h"

AddSerieDialog::AddSerieDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddSerieDialog)
{
    ui->setupUi(this);
}

AddSerieDialog::~AddSerieDialog()
{
    delete ui;
}
