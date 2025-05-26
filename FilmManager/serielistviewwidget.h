#ifndef SERIELISTVIEWWIDGET_H
#define SERIELISTVIEWWIDGET_H

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
};

#endif // SERIELISTVIEWWIDGET_H
