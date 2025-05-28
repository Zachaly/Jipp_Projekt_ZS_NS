#ifndef MODIFYMOVIEDIALOG_H
#define MODIFYMOVIEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <vector>
#include "FilmManager_Domain/movie.h"
#include "FilmManager_Domain/person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ModifyMovieDialog; }
QT_END_NAMESPACE

class ModifyMovieDialog : public QDialog
{
    Q_OBJECT

public:
    ModifyMovieDialog(const Movie& movie, QWidget *parent = nullptr);
    ~ModifyMovieDialog();

    Movie getModifiedMovie() const;

private slots:
    void onAccept();
    void updateRatingLabel(int value);

private:
    void populateDirectors();
    void populateActors();
    void loadMovieData();
    std::vector<std::string> getSelectedActors();

    Ui::ModifyMovieDialog *ui;
    Movie originalMovie;
    std::vector<QCheckBox*> actorCheckBoxes;
};

#endif // MODIFYMOVIEDIALOG_H
