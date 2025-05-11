#include "peoplelistviewwidget.h"
#include "startviewwidget.h"
#include "ui_startviewwidget.h"

StartViewWidget::StartViewWidget(MainWindow *parent)
    : QWidget(parent)
    , ui(new Ui::StartViewWidget)
{
    ui->setupUi(this);
    connect(ui->peopleButton, SIGNAL(clicked()), this, SLOT(peopleButton_clicked()));
}

StartViewWidget::~StartViewWidget()
{
    delete ui;
}

void StartViewWidget::peopleButton_clicked()
{
    ((MainWindow*)parent())->changePage(new PeopleListViewWidget((MainWindow*)parent()));
}
