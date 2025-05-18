#include "modifypersondialog.h"
#include "ui_modifypersondialog.h"

ModifyPersonDialog::ModifyPersonDialog(Person& person, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyPersonDialog),
    person(person)
{
    ui->setupUi(this);
}

ModifyPersonDialog::~ModifyPersonDialog()
{
    delete ui;
}
