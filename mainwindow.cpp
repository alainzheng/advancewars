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
#include <QString>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)

{

    ui->setupUi(this);
    g = new Game();

    //bouton1 = new QPushButton("texte dans le bouton",this);
    //bouton1->setGeometry(100,300,150,40);
    //QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));
    std::cout << "MainWindow created" << std::endl;
    label = new QLabel(this);
    label->setText("next Player turn "+ QString::number(turn+1));
    label->setGeometry(0,380,100,20);
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
    QImage image(":/image/sprites.png");
    for (int i = 0; g->getTerrains().size()>i;i++){
        Terrain &terrain = g->getTerrains()[i];
        int px = terrain.getPosX();
        int py = terrain.getPosY();

        painter.fillRect(px,py,objectSize,objectSize,Qt::black);
    }
    for (int i = 0; g->getBuildings().size()>i;i++){
        Building &building = g->getBuildings()[i];
        int px = building.getPosX();
        int py = building.getPosY();
        painter.fillRect(px+4,py+4,objectSize-8,objectSize-8,Qt::white);
    }

    for(int p = 0; p<2; p++){
        for (int i = 0; g->getPlayers()[p].getBuildings().size()>i; i++){
            Building &building = g->getPlayers()[p].getBuildings()[i];
            int px = building.getPosX();
            int py = building.getPosY();
            if (p==0){


                painter.fillRect(px,py,objectSize,objectSize,Qt::magenta);
            }
            else{
                painter.fillRect(px,py,objectSize,objectSize,Qt::darkGreen);
            }
        }
    }
    for(int p = 0; p<2; p++){
        for (int i = 0; g->getPlayers()[p].getUnits().size()>i;i++){
            Unit &unit = g->getPlayers()[p].getUnits()[i];
            int px = unit.getPosX();
            int py = unit.getPosY();
            if (p==0){
                QRectF target(px,py,objectSize,objectSize);
                ///QRectF source(188, 312, 16, 16);///map
                QRectF source(238, 204, 16, 16);///player
                painter.drawImage(target, image, source);
            }
            else{
                QRectF target(px,py,objectSize,objectSize);
                ///QRectF source(188, 312, 16, 16);///map
                QRectF source(238, 204, 16, 16);///player
                painter.drawImage(target, image, source);
            }    
        }
    }

    switch(indexP){
        case -1:
            break;
        case 2:
            bouton1 = new QPushButton("texte dans le bouton",this);
            bouton1->setGeometry(0,0,150,40);
            //QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));
            std::cout<<"hello";
            break;

        default:
            Unit &unit=g->getPlayers()[indexP].getUnits()[indexI];
            int dep=unit.getDeplacement();
            int px = unit.getPosX();
            int py = unit.getPosY();
            for(int a = px-dep*20; a<=px+20*dep;a+=20){
                for(int b = py-dep*20; b<=py+20*dep;b+=20){
                    //std::cout<<"a = "<<a-px<< " et b = "<<b-py<<std::endl;
                    bool condx = px==a;          // condition (px==a&&py==b) marchait pas dans le if
                    bool condy = py==b;
                    bool condxy = condx && condy;
                    if (abs(a-px)+abs(b-py)<=dep*20 && !condxy){
                        if(indexP==0){
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

            break;
        }

}






void MainWindow::mousePressEvent(QMouseEvent *event){
    // object selected
    int clx = event->x();
    int cly = event->y();

    for (int p=0; p<2 && indexP==-1;p++){
        for (int i = 0; g->getPlayers()[p].getUnits().size()>i;i++){
            Unit &unit = g->getPlayers()[p].getUnits()[i];
            int px = unit.getPosX();
            int py = unit.getPosY();
            if ((px<clx && (px+20)>clx && py<cly && (py+20)>cly)&&!unit.getMoved()){
                indexI = i;
                indexP = p;
                std::cout << "Unit index "<< i <<" from player "<< p+1<<" selected" << std::endl;
                break;
            }
            else{
            }
        }
    }
    for (int i=0; indexP=-1 && g->getPlayers()[turn%2].getBuildings().size()>i ;i++){

    }

    // marche tres bien, limite le nombre de case(deplacement) a n avec depx+depy<=n*20

    if(indexP==0 ||indexP==1){
        Unit &SelectedUnit = g->getPlayers()[indexP].getUnits()[indexI];
        int depx = abs((clx-clx%20)-SelectedUnit.getPosX());
        int depy = abs((cly-cly%20)-SelectedUnit.getPosY());
        bool cond1(depx == 0 && depy == 0);
        if(!cond1 && abs(depx)+abs(depy)<=SelectedUnit.getDeplacement()*20 && turn%2==indexP){
            SelectedUnit.setPosX(clx-clx%20);
            SelectedUnit.setPosY(cly-cly%20);
            SelectedUnit.setMoved(true);
            movedUnits++;
            if (movedUnits==g->getPlayers()[indexP].getUnits().size()){
                movedUnits = 0;
                turn++;
                label->setText("next Player turn "+ QString::number(turn+1));
                //label->setGeometry(0,380,100,20);
                for(int i = 0; g->getPlayers()[indexP].getUnits().size()>i; i++){
                    g->getPlayers()[indexP].getUnits()[i].setMoved(false);
                }
                std::cout<<"next is turn "<<turn+1<<std::endl;
            }

            indexP=-1;
        }
        else if(abs(depx)+abs(depy)>SelectedUnit.getDeplacement()*20){
            indexP = -1;
        }
    }
    repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    if (indexP!=-1){
        Unit &SelectedUnit = g->getPlayers()[indexP].getUnits()[indexI];
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
            indexP=-1;
            std::cout<<"undo selected"<<std::endl;
            break;
        }
    }
    repaint();
    //    update();
}
