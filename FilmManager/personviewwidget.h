#ifndef PERSONVIEWWIDGET_H
#define PERSONVIEWWIDGET_H

#include "FilmManager_Domain/person.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class PersonViewWidget;
}

class PersonViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonViewWidget(Person &person, MainWindow *parent = nullptr);
    ~PersonViewWidget();

public Q_SLOTS:
    void modifyPerson();
    void goBack();

private:
    Ui::PersonViewWidget *ui;
    Person& person;
};

#endif // PERSONVIEWWIDGET_H
