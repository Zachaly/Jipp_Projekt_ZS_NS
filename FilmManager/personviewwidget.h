#ifndef PERSONVIEWWIDGET_H
#define PERSONVIEWWIDGET_H

#include "FilmManager_Domain/person.h"
#include "mainwindow.h"
#include "ui_personviewwidget.h"
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

private slots:
    void modifyPerson();
    void goBack();

private:
    Ui::PersonViewWidget *ui;
    Person& person;
    void updateUi();
};

#endif // PERSONVIEWWIDGET_H
