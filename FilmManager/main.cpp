#include "mainwindow.h"
#include "FilmManager_Domain/personmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PersonManager::loadFromFile();
    app.setApplicationName("Film & Series Manager");
    app.setApplicationVersion("1.0");
    MainWindow w;
    w.show();
    return app.exec();
}
