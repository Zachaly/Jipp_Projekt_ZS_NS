#ifndef PEOPLELISTVIEWWIDGET_H
#define PEOPLELISTVIEWWIDGET_H

#include "mainwindow.h"
#include "ui_peoplelistviewwidget.h"
#include <QWidget>

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

private:
    Ui::PeopleListViewWidget *ui;
};

#endif // PEOPLELISTVIEWWIDGET_H
