#ifndef ADDEPISODEDIALOG_H
#define ADDEPISODEDIALOG_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class AddEpisodeDialog;
}

class AddEpisodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEpisodeDialog(string serieId, QWidget *parent = nullptr);
    ~AddEpisodeDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddEpisodeDialog *ui;
    string serieId;
    void loadLists();
};

#endif // ADDEPISODEDIALOG_H
