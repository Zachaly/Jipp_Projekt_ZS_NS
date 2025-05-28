#ifndef MOVIELISTVIEWWIDGET_H
#define MOVIELISTVIEWWIDGET_H

#include <QWidget>
#include <QIcon>
#include <vector>
#include "FilmManager_Domain/movie.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MovieListViewWidget; }
QT_END_NAMESPACE

class MovieListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovieListViewWidget(QWidget *parent = nullptr);
    ~MovieListViewWidget();

public slots:
    void searchMovies();
    void addNewMovie();
    void modifySelectedMovie();
    void removeSelectedMovie();
    void onMovieDoubleClicked();
    void goBack();

private slots:
    void onFilterChanged();

private:
    void setupConnections();
    void setupListWidget();
    void populateSearchComboBox();
    void displayMovies(const vector<Movie>& movies);
    void createMovieListItem(const Movie& movie);
    void updateMovieList();
    void refreshMovieList();
    void viewSelectedMovie();
    vector<Movie> getFilteredMovies();

    QString getGenreIcon(Genre genre);
    QString getGenreName(Genre genre);
    QString generateStarRating(double rating);

    Ui::MovieListViewWidget *ui;
    vector<Movie> currentMovies;
};

#endif // MOVIELISTVIEWWIDGET_H
