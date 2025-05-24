#include "modifypersondialog.h"
#include "peoplelistviewwidget.h"
#include "personviewwidget.h"
#include "ui_personviewwidget.h"

using namespace std;

#include <QString>
#include <QMessageBox>

PersonViewWidget::PersonViewWidget(Person& person, MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::PersonViewWidget),
    person(person)
{
    ui->setupUi(this);
    connect(ui->modifyButton, &QPushButton::clicked, this, &PersonViewWidget::modifyPerson);
    connect(ui->goBackButton, &QPushButton::clicked, this, &PersonViewWidget::goBack);

    updateUi();
}

PersonViewWidget::~PersonViewWidget()
{
    delete ui;
}

void PersonViewWidget::updateUi()
{
    string full = person.getFirstName() + " " + person.getLastName();
    ui->personNameLabel->setText(QString::fromStdString(full));

    QString birthDate = QString("%1-%2-%3")
                            .arg(person.getBirthYear())
                            .arg(person.getBirthMonth(), 2, 10, QChar('0'))
                            .arg(person.getBirthDay(),   2, 10, QChar('0'));

    ui->birthDateLabel->setText(birthDate);

    string role = "";

    if(person.getIsDirector())
    {
        role += "Director ";
    }
    if(person.getIsActor())
    {
        role += "Actor";
    }

    ui->personRoleLabel->setText(QString::fromStdString(role));
}

void PersonViewWidget::modifyPerson()
{
    ModifyPersonDialog dialog(person, this);

    if (dialog.exec() == QDialog::Accepted) {
        updateUi();
        QMessageBox::information(this, "Success", "Person information updated successfully.");
    }
}
void PersonViewWidget::goBack()
{
    MainWindow *mw = qobject_cast<MainWindow*>(parent());
    if (mw) {
        mw->changePage(new PeopleListViewWidget(mw));
    }
}
