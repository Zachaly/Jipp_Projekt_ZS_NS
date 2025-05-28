#ifndef MOVIEVIEWWIDGET_H
#define MOVIEVIEWWIDGET_H

#include <QWidget>
#include "FilmManager_Domain/movie.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MovieViewWidget; }
QT_END_NAMESPACE

class MovieViewWidget : public QWidget
{
    Q_OBJECT

public:
    MovieViewWidget(QWidget *parent = nullptr);
    ~MovieViewWidget();

    void displayMovie(const Movie& movie);
    void clearDisplay();
    void goBack();

signals:
    void editMovieRequested(const string& movieId);

private slots:
    void editCurrentMovie();

private:
    void updateActorsList(const vector<string>& actorIds);
    void updateDirectorInfo(const string& directorId);

    Ui::MovieViewWidget *ui;
    string currentMovieId;
};

#endif // MOVIEVIEWWIDGET_H
