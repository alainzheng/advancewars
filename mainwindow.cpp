#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include <QtWidgets/QPushButton>
#include <iostream>
#include <QPixmap>
#include "game.h"
#include <QImage>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    //bouton1 = new QPushButton("texte dans le bouton",this);
    //bouton1->setGeometry(100,300,150,40);
    //QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));
    std::cout << "MainWindow created" << std::endl;
}

MainWindow::~MainWindow(){
    //delete bouton1;
    delete ui;
}

void MainWindow::boutonclic(){
    std::cout<<"hello"<<std::endl;
}
void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    for (int i = 0; i*objectSize < 480; i++){
        for(int j = 0; j*objectSize < 400; j++){
            painter.drawRect(i*objectSize,j*objectSize,objectSize,objectSize);
        }
    }
    for(int p = 0; p<2; p++){
        for (int i = 0; g.getPlayers()[p].getUnits().size()>i;i++){
            Unit &unit = g.getPlayers()[p].getUnits()[i];
            int px = unit.getPosX();
            int py = unit.getPosY();
            if (p==0){
                painter.fillRect(px,py,objectSize,objectSize,Qt::red);
                painter.fillRect(px+4,py+4,objectSize-8,objectSize-8,Qt::yellow);
            }
            else{
                painter.fillRect(px,py,objectSize,objectSize,Qt::blue);
                painter.fillRect(px+4,py+4,objectSize-8,objectSize-8,Qt::darkCyan);
            }
            if (unit.getSelected()){
                int dep = unit.getDeplacement();

                for(int a = px-dep*20; a<=px+20*dep;a+=20){
                    for(int b = py-dep*20; b<=py+20*dep;b+=20){
                        //std::cout<<"a = "<<a-px<< " et b = "<<b-py<<std::endl;
                        bool condx = px==a;          // condition (px==a&&py==b) marchait pas dans le if
                        bool condy = py==b;
                        bool condxy = condx && condy;
                        if (abs(a-px)+abs(b-py)<=dep*20 && !condxy){
                            if(p==0){
                                painter.setBrush(QColor(255,0,0,63));
                                painter.drawRect(a,b,objectSize,objectSize);
                            }
                            else{
                                painter.setBrush(QColor(0,0,255,63));
                                painter.drawRect(a,b,objectSize,objectSize);
                            }
                        }
                    }
                }
            }

        }
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event){
    // object selected
    int clx = event->x();
    int cly = event->y();

    for (int p=0; p<2 && !selected;p++){
        for (int i = 0; g.getPlayers()[p].getUnits().size()>i && !selected;i++){
            Unit &unit = g.getPlayers()[p].getUnits()[i];
            int px = unit.getPosX();
            int py = unit.getPosY();
            if (px<clx && (px+20)>clx && py<cly && (py+20)>cly){
                unit.setSelected(true);
                selected = true;
                indexI = i;
                indexP = p;
                std::cout << "Unit index "<< i <<" from player "<< p+1<<" selected" << std::endl;
            }
            else{
                std::cout<< "NO object selected"<< std::endl;
                selected = false;
            }
        }
    }
    // marche tres bien, limite le nombre de case(deplacement) a n avec depx+depy<=n*20

    if(selected){
        Unit &SelectedUnit = g.getPlayers()[indexP].getUnits()[indexI];
        int depx = abs((clx-clx%20)-SelectedUnit.getPosX());
        int depy = abs((cly-cly%20)-SelectedUnit.getPosY());
        if(!(depx == 0 && depy == 0) && abs(depx)+abs(depy)<=SelectedUnit.getDeplacement()*20){
            SelectedUnit.setPosX(clx-clx%20);
            SelectedUnit.setPosY(cly-cly%20);
            SelectedUnit.setSelected(false);
            selected = false;
        }
        else if(abs(depx)+abs(depy)>SelectedUnit.getDeplacement()*20){
            selected = false;
            SelectedUnit.setSelected(false);
        }
    }
    repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    if (selected){
        Unit &SelectedUnit = g.getPlayers()[indexP].getUnits()[indexI];
        int dep = 20;
        switch(event->key()){
        case Qt::Key_D :
            SelectedUnit.move(dep,0);
            break;
        case Qt::Key_Q :
            SelectedUnit.move(-dep,0);
            break;
        case Qt::Key_Z :
            SelectedUnit.move(0,-dep);
            break;
        case Qt::Key_S :
            SelectedUnit.move(0,dep);
            break;
        case Qt::Key_U : //undo
            selected = false;
            SelectedUnit.setSelected(false);
            std::cout<<"undo selected"<<std::endl;
            break;
        }
    }
    repaint();
    //    update();
}
