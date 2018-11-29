#include "mainwindow.h"
#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1180,780);
    w.setWindowTitle("Advance Wars MAK");
    w.show();


    return a.exec();
}
