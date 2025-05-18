#include "addpersondialog.h"
#include "peoplelistviewwidget.h"
#include "personviewwidget.h"
#include "startviewwidget.h"
#include "ui_peoplelistviewwidget.h"


PeopleListViewWidget::PeopleListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PeopleListViewWidget)
{
    ui->setupUi(this);
    connect(ui->personButton, SIGNAL(clicked()), this, SLOT(goToPerson()));
    connect(ui->addPersonButton, SIGNAL(clicked()), this, SLOT(addPerson()));
    connect(ui->goBackButton, SIGNAL(clicked()), this, SLOT(goBack()));
}

PeopleListViewWidget::~PeopleListViewWidget()
{
    delete ui;
}

void PeopleListViewWidget::goToPerson()
{
    auto person = Person();
    ((MainWindow*)parent())->changePage(new PersonViewWidget(person, (MainWindow*)parent()));
}

void PeopleListViewWidget::addPerson()
{
    auto dialog = new AddPersonDialog(this);
    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void PeopleListViewWidget::goBack()
{
    ((MainWindow*)parent())->changePage(new StartViewWidget((MainWindow*)parent()));
}
