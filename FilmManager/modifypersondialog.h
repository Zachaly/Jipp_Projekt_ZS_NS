#ifndef MODIFYPERSONDIALOG_H
#define MODIFYPERSONDIALOG_H

#include "FilmManager_Domain/person.h"
#include <QDialog>

namespace Ui {
class ModifyPersonDialog;
}

class ModifyPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPersonDialog(Person& person, QWidget *parent = nullptr);
    ~ModifyPersonDialog();

private slots:
    void accept() override;

private:
    Ui::ModifyPersonDialog *ui;
    Person& person;
    void adjustDayRange();
};

#endif // MODIFYPERSONDIALOG_H
