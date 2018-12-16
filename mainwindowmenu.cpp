#include "mainwindowmenu.h"
#include "mainwindow.h"

MainWindowMenu::MainWindowMenu() : QWidget()
{
    setFixedSize(350, 250);

    NewJ2 = new QPushButton("Joueur 1 vs Joueur 2", this);

    NewJ2->setToolTip("Joue contre un ami en local");
    NewJ2->setCursor(Qt::PointingHandCursor);
    NewJ2->move(92, 20);

    QObject::connect(NewJ2, SIGNAL(clicked()), this, SLOT(AfficherPage1()));

    NewIA = new QPushButton("Joueur 1 vs IA pathfind", this);

    NewIA->setToolTip("Joue contre l'ordinateur");
    NewIA->setCursor(Qt::PointingHandCursor);
    NewIA->move(83, 80);

    QObject::connect(NewIA, SIGNAL(clicked()), this, SLOT(AfficherPage2()));

    NewReseau = new QPushButton("Joueur 1 vs IA greedy", this);


    NewReseau->setToolTip("Jouer contre l'ordinateur");
    NewReseau->setCursor(Qt::PointingHandCursor);
    NewReseau->move(88, 140);

    QObject::connect(NewReseau, SIGNAL(clicked()), this, SLOT(AfficherPage3()));

    Quitter = new QPushButton("Quitter", this);

    Quitter->setToolTip("Quitte le programme");
    Quitter->setCursor(Qt::PointingHandCursor);
    Quitter->move(114, 200);

    QObject::connect(Quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

}

MainWindowMenu::~MainWindowMenu(){
    delete NewJ2;
    delete NewIA;
    delete NewReseau;
    delete Quitter;
}

void MainWindowMenu::AfficherPage1()
{
    MainWindow *fenetre = new MainWindow(0);
    fenetre->resize(1440,880);
    fenetre->setWindowTitle("Advance Wars MAK");
    fenetre->show();
    this->close();
}

void MainWindowMenu::AfficherPage2()
{
    MainWindow *fenetre = new MainWindow(1);
    fenetre->resize(1440,880);
    fenetre->setWindowTitle("Advance Wars MAK");
    fenetre->show();
    this->close();
}
void MainWindowMenu::AfficherPage3()
{
    MainWindow *fenetre = new MainWindow(2);
    fenetre->resize(1440,880);
    fenetre->setWindowTitle("Advance Wars MAK");
    fenetre->show();
    this->close();
}
