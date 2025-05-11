#include "modifypersondialog.h"
#include "peoplelistviewwidget.h"
#include "personviewwidget.h"
#include "ui_personviewwidget.h"

PersonViewWidget::PersonViewWidget(Person& person, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PersonViewWidget),
    person(person)
{
    ui->setupUi(this);
    connect(ui->modifyPersonButton, SIGNAL(clicked()), this, SLOT(modifyPerson()));
    connect(ui->goBackButton, SIGNAL(clicked()),this, SLOT(goBack()));
}

PersonViewWidget::~PersonViewWidget()
{
    delete ui;
}

void PersonViewWidget::modifyPerson()
{
    auto dialog = new ModifyPersonDialog(person, this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void PersonViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new PeopleListViewWidget((MainWindow*)parent()));
}
