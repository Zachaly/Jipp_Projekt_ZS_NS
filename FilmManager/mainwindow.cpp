#include "mainwindow.h"
#include "peoplelistviewwidget.h"
#include "ui_mainwindow.h"
#include "startviewwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->contentWidget = new StartViewWidget(this);
    ui->contentWidget->setParent(this); // Ensure proper parenting
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(QWidget* widget)
{
    if (ui->contentWidget) {
        ui->contentWidget->hide();
        ui->contentWidget->deleteLater();
    }
    ui->contentWidget = widget;
    ui->contentWidget->setParent(this);
    ui->contentWidget->show();
}
