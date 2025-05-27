#ifndef MODIFYEPISODEDIALOG_H
#define MODIFYEPISODEDIALOG_H

#include "FilmManager_Domain/episode.h"
#include <QDialog>

namespace Ui {
class ModifyEpisodeDialog;
}

class ModifyEpisodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyEpisodeDialog(Episode& episode, QWidget *parent = nullptr);
    ~ModifyEpisodeDialog();
private slots:
    void on_buttonBox_accepted();
signals:
    void episodeUpdated();
private:
    Ui::ModifyEpisodeDialog *ui;
    Episode& episode;
    void loadData();
    vector<string> comboBoxIds;
};

#endif // MODIFYEPISODEDIALOG_H
