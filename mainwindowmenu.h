#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>

class MainWindowMenu : public QWidget
{
    Q_OBJECT
public:
    MainWindowMenu();
    ~MainWindowMenu();
public slots:
    void AfficherPage1();
    void AfficherPage2();
    void AfficherPage3();

private:
    QPushButton *NewJ2;
    QPushButton *NewIA;
    QPushButton *NewReseau;
    QPushButton *Quitter;

};

#endif
