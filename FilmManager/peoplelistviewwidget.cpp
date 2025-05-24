#include "addpersondialog.h"
#include "peoplelistviewwidget.h"
#include "personviewwidget.h"
#include "startviewwidget.h"
#include "ui_peoplelistviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"

#include <QMessageBox>
#include <QListWidgetItem>


PeopleListViewWidget::PeopleListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PeopleListViewWidget)
{
    ui->setupUi(this);

    ui->directorsCheckBox->setChecked(true);
    ui->actorsCheckBox->setChecked(true);

    connect(ui->goBackButton,    &QPushButton::clicked,            this, &PeopleListViewWidget::goBack);
    connect(ui->addPersonButton, &QPushButton::clicked,            this, &PeopleListViewWidget::addPerson);
    connect(ui->peopleListWidget,&QListWidget::itemDoubleClicked,  this, &PeopleListViewWidget::goToPerson);
    connect(ui->directorsCheckBox, &QCheckBox::checkStateChanged, this, &PeopleListViewWidget::refreshPeopleList);
    connect(ui->actorsCheckBox, &QCheckBox::checkStateChanged, this, &PeopleListViewWidget::refreshPeopleList);

    refreshPeopleList();
}

PeopleListViewWidget::~PeopleListViewWidget()
{
    delete ui;
}

void PeopleListViewWidget::refreshPeopleList()
{
    ui->peopleListWidget->clear();

    const bool directors = ui->directorsCheckBox->isChecked();
    const bool actors = ui->actorsCheckBox->isChecked();

    vector<Person> data;

    if(directors && actors)
    {
        data = PersonManager::getPeople();
    }
    else if(directors)
    {
        data = PersonManager::getPeople([](Person p){
            return p.getIsDirector();
        });
    }
    else if(actors)
    {
        data = PersonManager::getPeople([](Person p){
            return p.getIsActor();
        });
    }

    for (const auto& p : data) {

        string role = "";

        if(p.getIsDirector())
        {
            role += "Director ";
        }
        if(p.getIsActor())
        {
            role += "Actor ";
        }

        QString label = toQString(role + p.getFirstName() + " " + p.getLastName());
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
    connect(dlg, &AddPersonDialog::accepted, this, &PeopleListViewWidget::refreshPeopleList);
    connect(dlg, &AddPersonDialog::rejected, this, [this]() {
        QMessageBox::information(this, "Info", "Adding person canceled.");
    });

    dlg->exec();
    delete dlg;
}

void PeopleListViewWidget::goBack()
{
    auto* mw = qobject_cast<MainWindow*>(parent());
    if (mw) {
        mw->changePage(new StartViewWidget(mw));
    }
}
