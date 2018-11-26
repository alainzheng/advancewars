#include "mainwindow.h"
#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1080,680);
    w.setWindowTitle("Advance Wars MAK");
    w.show();


    return a.exec();
}
