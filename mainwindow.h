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
    Game *g=nullptr;
    int objectSize = 20;
    int indexI = 0;
    int indexP = -1;
    int turn = 0;
    int movedUnits = 0;
public:
    QPushButton *bouton1;
    QLabel *label;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void boutonclic();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
