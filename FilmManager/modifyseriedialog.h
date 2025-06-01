#ifndef MODIFYSERIEDIALOG_H
#define MODIFYSERIEDIALOG_H

#include "FilmManager_Domain/serie.h"
#include <QDialog>

namespace Ui {
class ModifySerieDialog;
}

class ModifySerieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySerieDialog(Serie& serie, QWidget *parent = nullptr);
    ~ModifySerieDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ModifySerieDialog *ui;
    Serie& serie;
    void updateLists();
};

#endif // MODIFYSERIEDIALOG_H
