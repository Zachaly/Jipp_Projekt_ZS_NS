#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <vector>
#include "FilmManager_Domain/movie.h"
#include "FilmManager_Domain/person.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class AddMovieDialog; }
QT_END_NAMESPACE

class AddMovieDialog : public QDialog
{
    Q_OBJECT

public:
    AddMovieDialog(QWidget *parent = nullptr);
    ~AddMovieDialog();

private slots:
    void onAccept();
    void updateRatingLabel(int value);

private:
    void populateDirectors();
    void populateActors();
    vector<string> getSelectedActors();

    Ui::AddMovieDialog *ui;
    vector<QCheckBox*> actorCheckBoxes;
};

#endif // ADDMOVIEDIALOG_H
