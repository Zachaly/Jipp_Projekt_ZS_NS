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

private:
    Ui::AddSerieDialog *ui;
};

#endif // ADDSERIEDIALOG_H
