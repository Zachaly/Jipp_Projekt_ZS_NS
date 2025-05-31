#include "addpersondialog.h"
#include "peoplelistviewwidget.h"
#include "displayhelpers.h"
#include "personviewwidget.h"
#include "startviewwidget.h"
#include "ui_peoplelistviewwidget.h"
#include "FilmManager_Domain/personmanager.h"
#include "FilmManager_Domain/qstringhelpers.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

PeopleListViewWidget::PeopleListViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PeopleListViewWidget)
{
    ui->setupUi(this);
    setupConnections();
    setupListWidget();
    refreshPeopleList();
}

PeopleListViewWidget::~PeopleListViewWidget()
{
    delete ui;
}

void PeopleListViewWidget::setupConnections()
{
    connect(ui->goBackButton, &QPushButton::clicked, this, &PeopleListViewWidget::goBack);
    connect(ui->addPersonButton, &QPushButton::clicked, this, &PeopleListViewWidget::addPerson);
    connect(ui->removeButton, &QPushButton::clicked, this, &PeopleListViewWidget::removeSelectedPerson);
    connect(ui->peopleListWidget, &QListWidget::itemDoubleClicked, this, &PeopleListViewWidget::goToPerson);
    connect(ui->peopleListWidget, &QListWidget::itemSelectionChanged, this, &PeopleListViewWidget::onSelectionChanged);
    connect(ui->directorsCheckBox, &QCheckBox::checkStateChanged, this, &PeopleListViewWidget::onFilterChanged);
    connect(ui->actorsCheckBox, &QCheckBox::checkStateChanged, this, &PeopleListViewWidget::onFilterChanged);
}

void PeopleListViewWidget::setupListWidget()
{
    ui->peopleListWidget->setStyleSheet(
        "QListWidget {"
        "    outline: none;"
        "    border: 2px solid #dee2e6;"
        "    border-radius: 8px;"
        "    background-color: white;"
        "    selection-background-color: #e6f3ff;"
        "}"
        "QListWidget::item {"
        "    padding: 0px;"
        "    border-bottom: 1px solid #eee;"
        "    min-height: 100px;"
        "    margin: 2px;"
        "    border-radius: 6px;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #e6f3ff;"
        "    border: 2px solid #007bff;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #f8f9fa;"
        "    border: 1px solid #dee2e6;"
        "}"
        "QListWidget::item:selected:hover {"
        "    background-color: #cce7ff;"
        "    border: 2px solid #0056b3;"
        "}"
        );
}

void PeopleListViewWidget::createPersonListItem(const Person& person)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setFixedHeight(90);

    QHBoxLayout* mainLayout = new QHBoxLayout(itemWidget);
    mainLayout->setContentsMargins(15, 10, 15, 10);
    mainLayout->setSpacing(15);


    QLabel* roleIconLabel = new QLabel();
    roleIconLabel->setText(getRoleIcon(person));
    roleIconLabel->setStyleSheet("font-size: 28px; color: #007bff;");
    roleIconLabel->setFixedSize(50, 50);
    roleIconLabel->setAlignment(Qt::AlignCenter);
    roleIconLabel->setStyleSheet(roleIconLabel->styleSheet() +
                                 "background-color: #f0f8ff; border-radius: 25px; border: 2px solid #007bff;");


    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(5);


    QLabel* nameLabel = new QLabel();
    QString fullName = QString("%1 %2")
                           .arg(QString::fromStdString(person.getFirstName()))
                           .arg(QString::fromStdString(person.getLastName()));
    nameLabel->setText(fullName.toUpper());
    nameLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #212529; margin-bottom: 5px;");

    QLabel* roleLabel = new QLabel();
    roleLabel->setText(QString("rola: %1").arg(getRoleText(person)));
    roleLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: normal;");


    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(roleLabel);
    infoLayout->addStretch();


    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);


    QLabel* statusLabel = new QLabel();
    if (person.getIsDirector() && person.getIsActor()) {
        statusLabel->setText("🌟 Multitalent");
        statusLabel->setStyleSheet("font-size: 12px; color: #dc3545; font-weight: bold; "
                                   "background-color: #f8d7da; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #f5c6cb;");
    } else if (person.getIsDirector()) {
        statusLabel->setText("🎬 Reżyser");
        statusLabel->setStyleSheet("font-size: 12px; color: #856404; font-weight: bold; "
                                   "background-color: #fff3cd; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #ffeaa7;");
    } else if (person.getIsActor()) {
        statusLabel->setText("🎭 Aktor");
        statusLabel->setStyleSheet("font-size: 12px; color: #155724; font-weight: bold; "
                                   "background-color: #d4edda; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #c3e6cb;");
    } else {
        statusLabel->setText("👤 Osoba");
        statusLabel->setStyleSheet("font-size: 12px; color: #6c757d; font-weight: bold; "
                                   "background-color: #f8f9fa; padding: 4px 8px; border-radius: 12px; "
                                   "border: 1px solid #dee2e6;");
    }
    statusLabel->setAlignment(Qt::AlignRight);

    rightLayout->addWidget(statusLabel);
    rightLayout->addStretch();

    mainLayout->addWidget(roleIconLabel);
    mainLayout->addLayout(infoLayout, 1);
    mainLayout->addLayout(rightLayout);

    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::UserRole, QString::fromStdString(person.getId()));
    item->setSizeHint(itemWidget->sizeHint());

    ui->peopleListWidget->addItem(item);
    ui->peopleListWidget->setItemWidget(item, itemWidget);
}

void PeopleListViewWidget::displayPeople(const vector<Person>& people)
{
    ui->peopleListWidget->clear();
    currentPeople = people;

    for (const auto& person : people) {
        createPersonListItem(person);
    }
}

void PeopleListViewWidget::updatePeopleList()
{
    vector<Person> filteredPeople = getFilteredPeople();
    displayPeople(filteredPeople);
}

vector<Person> PeopleListViewWidget::getFilteredPeople()
{
    const bool directors = ui->directorsCheckBox->isChecked();
    const bool actors = ui->actorsCheckBox->isChecked();

    vector<Person> result;

    if (directors && actors) {
        result = PersonManager::getPeople();
    } else if (directors) {
        result = PersonManager::getPeople([](Person p) {
            return p.getIsDirector();
        });
    } else if (actors) {
        result = PersonManager::getPeople([](Person p) {
            return p.getIsActor();
        });
    }

    return result;
}

void PeopleListViewWidget::refreshPeopleList()
{
    updatePeopleList();
}

void PeopleListViewWidget::onFilterChanged()
{
    updatePeopleList();
}

void PeopleListViewWidget::goToPerson()
{
    auto* item = ui->peopleListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Brak wyboru", "Proszę wybrać osobę z listy.");
        return;
    }

    std::string id = item->data(Qt::UserRole).toString().toStdString();
    try {
        Person& p = PersonManager::getPersonById(id);
        auto* editView = new PersonViewWidget(p, qobject_cast<MainWindow*>(parent()));
        qobject_cast<MainWindow*>(parent())->changePage(editView);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Błąd", QString("Nie można znaleźć osoby: %1").arg(e.what()));
    }
}

void PeopleListViewWidget::addPerson()
{
    auto* dlg = new AddPersonDialog(this);
    connect(dlg, &AddPersonDialog::accepted, this, &PeopleListViewWidget::refreshPeopleList);
    connect(dlg, &AddPersonDialog::rejected, this, [this]() {
        QMessageBox::information(this, "Info", "Dodawanie osoby anulowane.");
    });
    dlg->exec();
    delete dlg;
}
void PeopleListViewWidget::onSelectionChanged()
{
    bool hasSelection = ui->peopleListWidget->currentItem() != nullptr;
    ui->removeButton->setEnabled(hasSelection);
}

void PeopleListViewWidget::removeSelectedPerson()
{
    auto* item = ui->peopleListWidget->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Brak wyboru", "Proszę wybrać osobę do usunięcia.");
        return;
    }

    std::string id = item->data(Qt::UserRole).toString().toStdString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie",
                                  "Czy na pewno chcesz usunąć wybraną osobę?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            PersonManager::removePerson(id);
            refreshPeopleList();
            QMessageBox::information(this, "Sukces", "Osoba została usunięta.");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Błąd", QString("Nie udało się usunąć osoby: %1").arg(e.what()));
        }
    }
}

void PeopleListViewWidget::goBack()
{
    auto* mw = qobject_cast<MainWindow*>(parent());
    if (mw) {
        mw->changePage(new StartViewWidget(mw));
    }
}
