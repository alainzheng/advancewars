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

    ui->setupUi(this);
    g = new Game();

    //bouton1 = new QPushButton("texte dans le bouton",this);
   // bouton1->setGeometry(100,300,150,40);
    //QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));

    std::cout << "MainWindow created" << std::endl;

    //label = new QLabel(this);
    //label->setText("next Player turn "+ QString::number(turn+1));
    //label->setGeometry(0,380,100,20);
}

MainWindow::~MainWindow(){
    std::cout<<"destructor of mainwindow called"<<std::endl;
    delete bouton1;
    delete ui;
    delete g;
    delete this;
}

void MainWindow::boutonclic(){
    std::cout<<"hello"<<std::endl;
}
void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    std::cout<<g->getTerrains().size()<<std::endl;
    std::cout<<g->getBuildings().size()<<std::endl;
    std::cout<<g->getPlayer(0).getUnits().size()<<std::endl;


    for (int i = 0; g->getTerrains().size()>i;i++){
        Terrain* terrain = g->getTerrains()[i];
        int px = terrain->getPosX();
        int py = terrain->getPosY();
        QRectF target(px,py,objectSize,objectSize);
        std::string type = ":/images/PngAdvancedWar/"+std::to_string(terrain->getType())+".PNG";
        char cstr[type.size() + 1];
        strcpy(cstr,type.c_str());
        QImage image(cstr);
        painter.drawImage(target,image);
    }

    for (int i = 0; g->getBuildings().size()>i;i++){
        Building* building = g->getBuildings()[i];
        int px = building->getPosX();
        int py = building->getPosY();
        QRectF target(px,py,objectSize,objectSize);
        std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType())+".PNG";
        char cstr[type.size() + 1];
        strcpy(cstr,type.c_str());
        QImage image(cstr);
        painter.drawImage(target,image);
    }

    for(int p = 0; p<2; p++){
        for (int i = 0; g->getPlayer(p).getBuildings().size()>i; i++){
            Building* building = g->getPlayer(p).getBuildings()[i];
            int px = building->getPosX();
            int py = building->getPosY();
            QRectF target(px,py,objectSize,objectSize);

            if (p==0){
                std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType()+4)+".PNG";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);
            }
            else{
                std::string type = ":/images/PngAdvancedWar/"+std::to_string(building->getType()+9)+".PNG";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);
            }
        }
    }

    for(int p = 0; p<2; p++){
        for (int i = 0; g->getPlayer(p).getUnits().size()>i;i++){
            Unit* unit = g->getPlayer(p).getUnits()[i];
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (p==0){
                QRectF target(px,py,objectSize,objectSize);
                std::string type = ":/images/PngAdvancedWar/"+unit->getName()+"red.png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                std::cout<<type<<std::endl;
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

    switch(indexP){

        case -1:
            break;

        case 2:
 /*           bouton1->setText("new infantery red : 1000");
            bouton1->setGeometry(0,360,100,40);
            QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));
            std::cout<<"bouton case 2"<< std::endl;
            indexP = -1;
   */     break;

        case 3:
     /*       bouton1->setText("new infantery blue : 1000");
            bouton1->setGeometry(120,360,100,40);
            QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(boutonclic()));
            std::cout<<"bouton case 3"<< std::endl;
            indexP = -1;
       */ break;

        default:
            Unit* unit=g->getPlayer(indexP).getUnits()[indexI];
            int dep=unit->getDeplacement();
            int px = unit->getPosX();
            int py = unit->getPosY();
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


    /*
    QRectF target(0,0, width(), height());
    QRectF source(15, 15, 16, 16);
    QImage image(":/../../sprites.png");
    painter.drawImage(target, image, source);
    QGraphicsScene scene;
    QGraphicsItem *item;
    QPixmap image;
        image.load(":/../../sprites.png", 0, Qt::AutoColor);
        item = scene.addPixmap(image);*/


void MainWindow::mousePressEvent(QMouseEvent *event){
    // object selected
    int clx = event->x();
    int cly = event->y();

    for (int p=0;indexP==-1 && p<2;p++){
        for (int i = 0; g->getPlayer(p).getUnits().size()>i;i++){
            Unit* unit = g->getPlayer(p).getUnits()[i];
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (!unit->getMoved() && (px<clx && (px+20)>clx && py<cly && (py+20)>cly)){
                indexI = i;
                indexP = p;
                std::cout << "Unit index "<< i <<" from player "<< p+1<<" selected" << std::endl;
                break;
            }
            else{
            }
        }
    }

    for (int i=0; indexP==-1 && g->getPlayer(turn%2).getBuildings().size()>i ;i++){
        Building* building = g->getPlayer(turn%2).getBuildings()[i];
        int px = building->getPosX();
        int py = building->getPosY();
        if ((px<clx && (px+20)>clx && py<cly && (py+20)>cly)){
            indexI = i;
            indexP = 2+turn%2;
            std::cout << "building index "<< i <<" from player "<< turn+1<<" selected" << std::endl;
            break;
        }
    }
    // marche tres bien, limite le nombre de case(deplacement) a n avec depx+depy<=n*20

    if(indexP==0 ||indexP==1){
        Unit* SelectedUnit = g->getPlayer(indexP).getUnits()[indexI];
        int depx = abs((clx-clx%20)-SelectedUnit->getPosX());
        int depy = abs((cly-cly%20)-SelectedUnit->getPosY());
        bool cond1(depx == 0 && depy == 0);
        if(!cond1 && abs(depx)+abs(depy)<=SelectedUnit->getDeplacement()*20 && turn%2==indexP){
            SelectedUnit->setPosX(clx-clx%20);
            SelectedUnit->setPosY(cly-cly%20);
            SelectedUnit->setMoved(true);
            movedUnits++;
            if (movedUnits == g->getPlayer(indexP).getUnits().size()){
                movedUnits = 0;
                turn++;
                label->setText("next Player turn "+ QString::number(turn+1));
                //label->setGeometry(0,380,100,20);
                for(int i = 0; g->getPlayer(indexP).getUnits().size()>i; i++){
                    g->getPlayer(indexP).getUnits()[i]->setMoved(false);
                }
                std::cout<<"next is turn "<<turn+1<<std::endl;
            }
            indexP=-1;
        }
        else if(abs(depx)+abs(depy)>SelectedUnit->getDeplacement()*20){
            indexP = -1;
        }
    }

    else if (indexP == 2||indexP == 3){
        if (indexP%2==turn%2){
            Building* building = g->getPlayer(indexP-2).getBuildings()[indexI];
            int bType = building->getType();
            if(bType == 1){
                std::cout<< "building is a City"<<std::endl;
            }
            else if(bType == 2){
                std::cout<< "building is a factory"<<std::endl;
            }
            else if(bType == 3){
                std::cout<< "building is an Airport"<<std::endl;
            }
        }
    }
    repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    std::cout << event->key() << std::endl;
    // seulement pour le curseur, le menu et les choix
    if (indexP!=-1){
        Unit* SelectedUnit = g->getPlayer(indexP).getUnits()[indexI];
        int dep = 20;
        switch(event->key()){
        case Qt::Key_D :
            SelectedUnit->move(dep,0);
            break;
        case Qt::Key_Q :
            SelectedUnit->move(-dep,0);
            break;
        case Qt::Key_Z :
            SelectedUnit->move(0,-dep);
            break;
        case Qt::Key_S :
            SelectedUnit->move(0,dep);
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
