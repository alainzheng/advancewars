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
#include "object.h"
#include <string>
#include <cstring>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)

{

    std::cout << "MainWindow created" << std::endl;
    ui->setupUi(this);
    g = new Game();

    initializeMap();

    turnButton = new QPushButton("next turn",this);
    turnButton->setGeometry(860,60,120,30);
    QObject::connect(turnButton,SIGNAL(clicked()),this,SLOT(nextTurnButton()));

}

MainWindow::~MainWindow(){
    std::cout<<"destructor of mainwindow called"<<std::endl;
    delete turnButton;
    delete ui;
    delete g;
}

void MainWindow::initializeMap(){

}

void MainWindow::nextTurnButton(){
    for(Unit* unit : g->getPlayer(turn%2)->getUnits()){
        unit->setMoved(false);
    }
    turn++;
    std::cout<<"Player " + std::to_string(1+turn%2) + ", turn "+ std::to_string(turn)<<std::endl;
    repaint();
}




void MainWindow::paintEvent(QPaintEvent* event){

    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 15));
    std::string playTurn = "Player "+ std::to_string(1+turn%2) + " turn";
    char cPlayTurn[playTurn.size() + 1];
    strcpy(cPlayTurn,playTurn.c_str());
    painter.drawText(860,140,cPlayTurn);


    for (Terrain* terrain : g->getTerrains()){
        int px = terrain->getPosX();
        int py = terrain->getPosY();
        QRectF target(px,py,objectSize,objectSize);
        std::string type = ":/images/PngAdvancedWar/"+std::to_string(terrain->getType())+".png";
        char cstr[type.size() + 1];
        strcpy(cstr,type.c_str());
        QImage image(cstr);
        painter.drawImage(target,image);
    }

    for (Building* building : g->getBuildings()){
        int px = building->getPosX();
        int py = building->getPosY();
        QRectF target(px,py-20,objectSize,objectSize+20);
        if (building->getType()==26){
            target = QRect(px,py,objectSize,objectSize);
        }
        std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType())+".png";
        char cstr[type.size() + 1];
        strcpy(cstr,type.c_str());
        QImage image(cstr);
        painter.drawImage(target,image);
    }

    for(int p = 0; p<2; p++){
        for (Building* building : g->getPlayer(p)->getBuildings()){
            int px = building->getPosX();
            int py = building->getPosY();
            QRectF target(px,py,objectSize,objectSize);

            if (p==0){
                std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType()+4)+".png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);
            }
            else{
                std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType()+9)+".png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);
            }
        }
    }

    for(int p = 0; p<2; p++){
        for (Unit* unit : g->getPlayer(p)->getUnits()){
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (p==0){
                QRectF target(px,py,objectSize,objectSize);
                std::string type = ":/images/PngAdvancedWar/"+unit->getName()+"red.png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);
            }

            else{
                QRectF target(px,py,objectSize,objectSize);
                std::string type = ":/images/PngAdvancedWar/"+unit->getName()+"blue.png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);            }
        }
    }

    if(indexP==-1){
    }
    else if(indexP == 2){
    }
    else if(indexP == 3){
    }
    else if (indexP == 0||indexP == 1){
        // montre la case où l'objet peut bouger, pas tenu compte du type de terrain !!!
         Unit* unit = g->getPlayer(indexP)->getUnits()[indexI];

         int dep = unit->getDeplacement();
         int px = unit->getPosX();
         int py = unit->getPosY();
         for(int a = px-dep*objectSize; a<=px+objectSize*dep;a+=objectSize){
             for(int b = py-dep*objectSize; b<=py+objectSize*dep;b+=objectSize){
                 bool condx = px==a;
                 bool condy = py==b;
                 bool condxy = condx && condy;
                 if (abs(a-px)+abs(b-py)<=dep*objectSize && !condxy){
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
    }


}



/*                        TOUCHE SOURIS   */


void MainWindow::mousePressEvent(QMouseEvent *event){
    // object selected
    int clx = event->x();
    int cly = event->y();

    // selection d'un unit de player

    for (int p=0;indexP==-1 && p<2;p++){
        for (int i = 0; i < g->getPlayer(p)->getUnits().size();i++){
            Unit* unit = g->getPlayer(p)->getUnits()[i];
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (turn%2==p && !unit->getMoved() && px < clx && ((px+objectSize) > clx && py < cly && (py+objectSize) > cly)){
                indexI = i;
                indexP = p;
                std::cout << "Unit index "<< i <<" from player "<< p+1 <<" selected" << std::endl;
                break;
            }
            else{
            }
        }
    }

    // selection d'un batiment de player

    for (int i=0; indexP==-1 && i < g->getPlayer(turn%2)->getBuildings().size() ;i++){
        Building* building = g->getPlayer(turn%2)->getBuildings()[i];
        int px = building->getPosX();
        int py = building->getPosY();
        if ((px < clx && (px+objectSize) > clx && py < cly && (py+objectSize) > cly)){
            indexI = i;
            indexP = 2 + turn%2;
            std::cout << "building index "<< i <<" from player "<< turn <<" selected" << std::endl;
            break;
        }
    }

    // Mouvement de l'unit

    if(indexP==0 || indexP==1){
        Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
        int depx = abs((clx-clx%objectSize)-SelectedUnit->getPosX());
        int depy = abs((cly-cly%objectSize)-SelectedUnit->getPosY());
        bool cond1(depx == 0 && depy == 0);
        if(!cond1 && abs(depx)+abs(depy) <= SelectedUnit->getDeplacement()*objectSize && turn%2==indexP){
            SelectedUnit->setPosX(clx-clx%objectSize);
            SelectedUnit->setPosY(cly-cly%objectSize);
            SelectedUnit->setMoved(true);
            indexP = -1;
        }
        else if(abs(depx)+abs(depy)>SelectedUnit->getDeplacement()*objectSize){
            indexP = -1;
        }

    }

    else if (indexP == 2||indexP == 3){
        Building* building = g->getPlayer(indexP-2)->getBuildings()[indexI];
        int bType = building->getType();
        if(bType == 34){
            std::cout<< "building is a City"<<std::endl;
        }
        else if(bType == 35){
            std::cout<< "building is a factory"<<std::endl;
            Factory* factory = dynamic_cast<Factory*>(building);
            g->getPlayer(indexP-2)->addUnit(factory->createNewUnit("Bazooka"));
        }
        else if(bType == 36){
            std::cout<< "building is an Airport"<<std::endl;
        }
        indexP = -1;
    }

    repaint();
}


/*                 TOUCHES CLAVIER        */


void MainWindow::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    // seulement pour le curseur, le menu et les choix
    if (indexP!=-1){
        switch(event->key()){
            case Qt::Key_U :
            indexP=-1;
            std::cout<<"undo selected"<<std::endl;
            break;
        }
    }
    repaint();
}

