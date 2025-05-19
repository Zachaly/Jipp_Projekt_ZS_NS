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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePage(QWidget* widget)
{
    auto prev = ui->contentWidget;
    ui->contentWidget = widget;
    prev->close();
    delete prev;
    ui->contentWidget->show();
}
