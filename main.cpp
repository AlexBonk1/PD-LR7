#include "mainwindow.h"

#include <QApplication>

int main(
    int argc, char *argv[])
{
    QApplication a(argc, argv);
    ActionManager actionManager(&a);
    MainWindow w(&actionManager);
    w.show();
    return a.exec();
}
