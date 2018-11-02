#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include <QtWidgets/QPushButton>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Game g;
    int objectSize = 20;
    bool selected = false;
    int indexI = 0;
    int indexP = 0;
public:
    QPushButton *bouton1;
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
