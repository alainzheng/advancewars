#include "mainwindowmenu.h"
#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowMenu w;
    w.resize(1480,880);
    w.setWindowTitle("Advance Wars Menu");
    w.show();


    return a.exec();
}
