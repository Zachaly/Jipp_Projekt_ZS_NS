#ifndef PEOPLELISTVIEWWIDGET_H
#define PEOPLELISTVIEWWIDGET_H

#include "mainwindow.h"

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

public Q_SLOTS:
    void goToPerson();
    void addPerson();
    void goBack();

private:
    Ui::PeopleListViewWidget *ui;
};

#endif // PEOPLELISTVIEWWIDGET_H
