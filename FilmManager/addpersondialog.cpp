#include "addpersondialog.h"
#include "ui_addpersondialog.h"
#include <QMessageBox>
#include <QSpinBox>
#include "FilmManager_Domain/qstringhelpers.h"

AddPersonDialog::AddPersonDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPersonDialog)
{
    ui->setupUi(this);

    ui->yearSpin->setRange(1900, 2023);
    ui->yearSpin->setValue(1990);

    ui->monthSpin->setRange(1, 12);
    ui->monthSpin->setValue(1);

    ui->daySpin->setRange(1, 31);
    ui->daySpin->setValue(1);

    auto adjustDays = [this]() {
        int m = ui->monthSpin->value();
        int y = ui->yearSpin->value();
        int maxD = 31;
        if (m==4||m==6||m==9||m==11) maxD=30;
        else if (m==2) {
            bool leap = (y%4==0 && y%100!=0) || (y%400==0);
            maxD = leap ? 29 : 28;
        }
        ui->daySpin->setMaximum(maxD);
        if (ui->daySpin->value() > maxD)
            ui->daySpin->setValue(maxD);
    };
    connect(ui->monthSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, adjustDays);
    connect(ui->yearSpin,  QOverload<int>::of(&QSpinBox::valueChanged), this, adjustDays);
    adjustDays();
    }


AddPersonDialog::~AddPersonDialog()
{
    delete ui;
}

void AddPersonDialog::on_buttonBox_accepted()
{
    QString fnQ = ui->firstNameEdit->text().trimmed();
    QString lnQ = ui->lastNameEdit->text().trimmed();
    int y = ui->yearSpin->value();
    int m = ui->monthSpin->value();
    int d = ui->daySpin->value();

    if (fnQ.isEmpty() || lnQ.isEmpty()) {
        QMessageBox::warning(this, "Incomplete", "First name and last name are required.");
        return;
    }

    try {
        PersonManager::addPerson(fromQString(fnQ),
                                 fromQString(lnQ),
                                 y, m, d);
        emit personAdded();
        accept();
    }
    catch (const std::invalid_argument& e) {
        QMessageBox::warning(this, "Error", QString("Cannot add person: %1").arg(e.what()));
    }
}
