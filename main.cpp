#include "mainwindow.h"
#include <QApplication>

#include "SmolesManager.h"

int main(int argc, char *argv[])
{
    SmolesManager smoles_manager;
    // TODO: Now connect the user's gui interactions with the functions of the manager.

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
