#include "modifypersondialog.h"
#include "ui_modifypersondialog.h"
#include <QMessageBox>
#include <QString>


ModifyPersonDialog::ModifyPersonDialog(Person& person, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyPersonDialog),
    person(person)
{
    ui->setupUi(this);
    ui->firstNameEdit->setText(QString::fromStdString(person.getFirstName()));
    ui->lastNameEdit->setText(QString::fromStdString(person.getLastName()));

    ui->yearSpin->setRange(1900, 2025);
    ui->yearSpin->setValue(person.getBirthYear());

    ui->monthSpin->setRange(1, 12);
    ui->monthSpin->setValue(person.getBirthMonth());

    ui->daySpin->setRange(1, 31);
    ui->daySpin->setValue(person.getBirthDay());


    connect(ui->monthSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &ModifyPersonDialog::adjustDayRange);
    connect(ui->yearSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &ModifyPersonDialog::adjustDayRange);
    adjustDayRange();

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &ModifyPersonDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &ModifyPersonDialog::reject);

    ui->directorCheckBox->setChecked(person.getIsDirector());
    ui->actorCheckBox->setChecked(person.getIsActor());
}


ModifyPersonDialog::~ModifyPersonDialog()
{
    delete ui;
}

void ModifyPersonDialog::adjustDayRange()
{
    int month = ui->monthSpin->value();
    int year = ui->yearSpin->value();
    int maxDays = 31;

    if (month == 4 || month == 6 || month == 9 || month == 11)
        maxDays = 30;
    else if (month == 2)
        maxDays = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;

    ui->daySpin->setMaximum(maxDays);
    if (ui->daySpin->value() > maxDays)
        ui->daySpin->setValue(maxDays);
}

void ModifyPersonDialog::accept()
{
    QString fn = ui->firstNameEdit->text().trimmed();
    QString ln = ui->lastNameEdit->text().trimmed();

    if (fn.isEmpty() || ln.isEmpty()) {
        QMessageBox::warning(this, "Incomplete", "First name and last name are required.");
        return;
    }

    bool isActor = ui->actorCheckBox->isChecked();
    bool isDirector = ui->directorCheckBox->isChecked();

    if(!isActor && !isDirector)
    {
        QMessageBox::warning(this, "Incomplete", "Person has to be either actor or director.");
        return;
    }

    try {
        person.setFirstName(fn.toStdString());
        person.setLastName(ln.toStdString());
        person.setBirthYear(ui->yearSpin->value());
        person.setBirthMonth(ui->monthSpin->value());
        person.setBirthDay(ui->daySpin->value());
        person.setIsActor(isActor);
        person.setIsDirector(isDirector);

        QDialog::accept();
    } catch (const std::invalid_argument& e) {
        QMessageBox::warning(this, "Error", QString("Invalid input: %1").arg(e.what()));
    }
}
