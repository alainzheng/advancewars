#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include <QtWidgets/QPushButton>
#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPoint point;
    Game* g=nullptr;
    int objectSize = 40;
    int init = 0;
    int indexI = 0;
    int indexP = -1;
    int indexB = -1;
    int indexA = -1;
    int turn = 0;
    string Finventary[8][2];
    string Ainventary[3][2];
    string Actions[5];

public:    
    QPushButton *turnButton;
    QPushButton *unitButton;
    QLabel *label;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void pointSetPos(int px, int py);
    void initializeMap();
    void recPossibleCases(int x, int y, int dep,int moveType);
    void initPossibleCases();
    void iaPathFind();


    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void nextTurnButton();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
