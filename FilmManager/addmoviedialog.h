#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>

namespace Ui {
class AddMovieDialog;
}

class AddMovieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMovieDialog(QWidget *parent = nullptr);
    ~AddMovieDialog();

private:
    Ui::AddMovieDialog *ui;
};

#endif // ADDMOVIEDIALOG_H
