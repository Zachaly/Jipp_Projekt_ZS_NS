#ifndef ADDPERSONDIALOG_H
#define ADDPERSONDIALOG_H

#include <QDialog>
#include "FilmManager_Domain/personmanager.h"

namespace Ui {
class AddPersonDialog;
}

class AddPersonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonDialog(QWidget *parent = nullptr);
    ~AddPersonDialog();

signals:
    void personAdded();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPersonDialog *ui;
};

#endif // ADDPERSONDIALOG_H
