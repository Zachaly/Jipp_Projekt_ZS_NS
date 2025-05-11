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

private:
    Ui::AddEpisodeDialog *ui;
    string serieId;
};

#endif // ADDEPISODEDIALOG_H
