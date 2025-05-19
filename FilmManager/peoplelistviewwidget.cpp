#include "addpersondialog.h"
#include "peoplelistviewwidget.h"
#include "personviewwidget.h"
#include "startviewwidget.h"
#include "ui_peoplelistviewwidget.h"
#include "FilmManager_Domain/personmanager.h"

#include <QMessageBox>
#include <QListWidgetItem>


PeopleListViewWidget::PeopleListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PeopleListViewWidget)
{
    ui->setupUi(this);

    connect(ui->goBackButton,    &QPushButton::clicked,            this, &PeopleListViewWidget::goBack);
    connect(ui->addPersonButton, &QPushButton::clicked,            this, &PeopleListViewWidget::addPerson);
    connect(ui->peopleListWidget,&QListWidget::itemDoubleClicked,  this, &PeopleListViewWidget::goToPerson);

    refreshPeopleList();
}

PeopleListViewWidget::~PeopleListViewWidget()
{
    delete ui;
}

void PeopleListViewWidget::refreshPeopleList()
{
    ui->peopleListWidget->clear();

    for (const auto& p : PersonManager::getPeople()) {
        QString label = toQString(p.getFirstName() + " " + p.getLastName());
        auto* item = new QListWidgetItem(label);
        item->setData(Qt::UserRole, toQString(p.getId()));
        ui->peopleListWidget->addItem(item);
    }
}

void PeopleListViewWidget::goToPerson()
{
    auto* item = ui->peopleListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "No Selection", "Please select a person from the list.");
        return;
    }

    std::string id = fromQString(item->data(Qt::UserRole).toString());
    Person& p = PersonManager::getPersonById(id);


    auto* editView = new PersonViewWidget(p, qobject_cast<MainWindow*>(parent()));
    qobject_cast<MainWindow*>(parent())->changePage(editView);
}

void PeopleListViewWidget::addPerson()
{
    auto* dlg = new AddPersonDialog(this);
    connect(dlg, &AddPersonDialog::personAdded,
            this, &PeopleListViewWidget::refreshPeopleList);

    if (dlg->exec() == QDialog::Accepted) {
        QMessageBox::information(this, "Success", "Person added successfully.");
    }
    delete dlg;
}

void PeopleListViewWidget::goBack()
{
    auto* mw = qobject_cast<MainWindow*>(parent());
    if (mw) {
        mw->changePage(new StartViewWidget(mw));
    }
}
