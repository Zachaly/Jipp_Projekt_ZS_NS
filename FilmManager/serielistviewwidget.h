#ifndef SERIELISTVIEWWIDGET_H
#define SERIELISTVIEWWIDGET_H

#include "FilmManager_Domain/genre.h"
#include "FilmManager_Domain/serie.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class SerieListViewWidget;
}

class SerieListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerieListViewWidget(MainWindow *parent = nullptr);
    ~SerieListViewWidget();
public Q_SLOTS:
    void goBack();
    void goToSerie();
    void addSerie();
private:
    Ui::SerieListViewWidget *ui;
    void updateList();
    QString getGenreIcon(Genre genre);
    QString getGenreName(Genre genre);
    QString getStatusName(SerieStatus status);
    QString generateStarRating(double rating);
    void addSerieListItem(const Serie& serie);
    void deleteSelectedSerie();
    void modifySelectedSerie();
    void searchSeries();
};

#endif // SERIELISTVIEWWIDGET_H
