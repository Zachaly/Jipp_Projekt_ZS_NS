#ifndef ADDSERIEDIALOG_H
#define ADDSERIEDIALOG_H

#include <QDialog>

namespace Ui {
class AddSerieDialog;
}

class AddSerieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSerieDialog(QWidget *parent = nullptr);
    ~AddSerieDialog();

signals:
    void serieAdded();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddSerieDialog *ui;
    void updateLists();
};

#endif // ADDSERIEDIALOG_H
