#ifndef PEOPLELISTVIEWWIDGET_H
#define PEOPLELISTVIEWWIDGET_H

#include "mainwindow.h"
#include "FilmManager_Domain/person.h"
#include <QWidget>
#include <vector>

using namespace std;

namespace Ui {
class PeopleListViewWidget;
}

class PeopleListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PeopleListViewWidget(MainWindow *parent = nullptr);
    ~PeopleListViewWidget();

private slots:
    void goToPerson();
    void addPerson();
    void goBack();
    void refreshPeopleList();
    void onFilterChanged();
    void onSelectionChanged();
    void removeSelectedPerson();

private:
    void setupConnections();
    void setupListWidget();
    void displayPeople(const vector<Person>& people);
    void createPersonListItem(const Person& person);
    void updatePeopleList();
    vector<Person> getFilteredPeople();
    QString getRoleIcon(const Person& person);
    QString getRoleText(const Person& person);

    Ui::PeopleListViewWidget *ui;
    vector<Person> currentPeople;
};

#endif // PEOPLELISTVIEWWIDGET_H
