#ifndef MODIFYMOVIEDIALOG_H
#define MODIFYMOVIEDIALOG_H

#include "FilmManager_Domain/movie.h"
#include <QDialog>

namespace Ui {
class ModifyMovieDialog;
}

class ModifyMovieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyMovieDialog(Movie& movie, QWidget *parent = nullptr);
    ~ModifyMovieDialog();

private:
    Ui::ModifyMovieDialog *ui;
    Movie& movie;
};

#endif // MODIFYMOVIEDIALOG_H
