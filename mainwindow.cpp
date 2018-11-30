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


#include <QPixmap>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)

{

    std::cout << "MainWindow created" << std::endl;
    ui->setupUi(this);
    g = new Game();

    initializeMap();// fait encore rien



    turnButton = new QPushButton("next turn",this);
    turnButton->setGeometry(860,60,120,40);
    /*QPixmap pixmap(":/images/PngAdvancedWar/1.png");
    QIcon ButtonIcon(pixmap);
    turnButton->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());
    */
    QObject::connect(turnButton,SIGNAL(clicked()),this,SLOT(nextTurnButton()));

}

MainWindow::~MainWindow(){
    std::cout<<"destructor of mainwindow called"<<std::endl;
    delete turnButton;
    delete ui;
    delete g;
}

void MainWindow::initializeMap(){
    //{"Infantry","Bazooka","Recon","Tank","MdTank","MegaTank","NeoTank","Bomber"};

    Finventary[0][0]= "Infantry";
    Finventary[1][0]= "Bazooka";
    Finventary[2][0]= "Recon";
    Finventary[3][0]= "Tank";
    Finventary[4][0]= "MdTank";
    Finventary[5][0]= "MegaTank";
    Finventary[6][0]= "NeoTank";
    Finventary[7][0]= "AntiAir";

    Finventary[0][1]= "1000";
    Finventary[1][1]= "3000";
    Finventary[2][1]= "4000";
    Finventary[3][1]= "7000";
    Finventary[4][1]= "16000";
    Finventary[5][1]= "28000";
    Finventary[6][1]= "22000";
    Finventary[7][1]= "8000";

    Ainventary[0][0]= "Bomber";
    Ainventary[1][0]= "BCopter";
    Ainventary[2][0]= "Fighter";

    Ainventary[0][1]= "22000";
    Ainventary[1][1]= "9000";
    Ainventary[2][1]= "20000";

    Actions[0] = "Attack";
    Actions[1] = "Take city";
    Actions[2] = "Return";



}

void MainWindow::nextTurnButton(){
    for(Unit* unit : g->getPlayer(turn%2)->getUnits()){
        unit->setHasMoved(false);
    }
    for(Building* building : g->getPlayer(turn%2)->getBuildings()){
        building->setHasMadeUnit(false);
    }
    g->getPlayer(turn%2)->setMoney(g->getPlayer(turn%2)->getMoney()+5000);
    indexP = -1;
    indexA = -1;
    indexB = -1;
    turn++;
    std::cout<<"Player " + std::to_string(1+turn%2) + ", turn "+ std::to_string(turn)<<std::endl;
    repaint();
}






void MainWindow::paintEvent(QPaintEvent* event){

    QPainter painter(this);

    // information de player

    painter.setPen(Qt::red);
    painter.setFont(QFont("times", 15,QFont::DemiBold,true));

    std::string player1 = "Player red 1 : "+std::to_string(g->getPlayer(0)->getMoney());
    char play1[player1.size() + 1];
    strcpy(play1,player1.c_str());
    painter.drawText(860,20,play1);

    painter.setPen(Qt::blue);
    painter.setFont(QFont("times", 15,QFont::DemiBold,true));

    std::string player2 = "Player blue 2 : "+std::to_string(g->getPlayer(1)->getMoney());
    char play2[player2.size() + 1];
    strcpy(play2,player2.c_str());
    painter.drawText(860,45,play2);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 15));
    std::string playTurn = "Player "+ std::to_string(1+turn%2) + " turn";
    char cPlayTurn[playTurn.size() + 1];
    strcpy(cPlayTurn,playTurn.c_str());
    painter.drawText(860,140,cPlayTurn);

    // dessine le terrain de base, la map

    for (Terrain* terrain : g->getTerrains()){
        int px = terrain->getPosX();
        int py = terrain->getPosY();
        QRectF target(px,py,objectSize,objectSize);
        string str = ":/images/PngAdvancedWar/1.png";
        std::string type = ":/images/PngAdvancedWar/"+std::to_string(terrain->getType())+".png";
        char cstr[type.size() + 1];
        strcpy(cstr,type.c_str());
        QImage image(cstr);
        painter.drawImage(target,image);
    }

    // dessine les building de game, neutre
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

    // dessine les batiments appartenant à player 1 et 2

    for(int p = 0; p<2; p++){
        for (Building* building : g->getPlayer(p)->getBuildings()){
            int px = building->getPosX();
            int py = building->getPosY();
            QRectF target(px,py,objectSize,objectSize);
            if(building->getType()==34){
                target = QRect(px,py-20,objectSize,objectSize+20);
            }

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

            // dessine les unités

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
                painter.drawImage(target,image);
            }
            string life = std::to_string(unit->getLifes());
            char cstr5[life.size() + 1];
            strcpy(cstr5,life.c_str());
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 9,QFont::Bold));
            painter.drawText(px+20,py+35,cstr5);
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 15));
        }

    }

    if(indexP == -1){
    // fait rien
    }

    // cas où on choisit un joueur

    else if (indexP == 0||indexP == 1){
         Unit* unit = g->getPlayer(indexP)->getUnits()[indexI];
         int dep = unit->getDeplacement();
         int px = unit->getPosX();
         int py = unit->getPosY();

         QRectF target(880,168,objectSize,objectSize);
         string color = "red";
         if(indexP==1){
             color = "blue";
         }
         std::string type = ":/images/PngAdvancedWar/"+unit->getName()+color+".png";
         char cstr[type.size() + 1];
         strcpy(cstr,type.c_str());
         QImage image(cstr);
         painter.drawImage(target,image);

         char cstr2[unit->getName().size() + 1];
         strcpy(cstr2,unit->getName().c_str());
         painter.drawText(950,228,cstr2);
         painter.drawText(880,228,"Type : ");

         char cstr3[std::to_string(unit->getLifes()).size() + 1];
         strcpy(cstr3,std::to_string(unit->getLifes()).c_str());
         painter.drawText(970,253,cstr3);
         painter.drawText(880,253,"Lifes : ");

         char cstr4[std::to_string(unit->getDeplacement()).size() + 1];
         strcpy(cstr4,std::to_string(unit->getDeplacement()).c_str());
         painter.drawText(1100,278,cstr4);
         painter.drawText(860,278,"Deplacement : ");


         // dessine les différents cas lorsque un player est choisi

         for (int i = 0; i<3;i++){
             painter.drawRect(880,320+i*40,3*objectSize,objectSize);
             char cstr6[Actions[i].size() + 1];
             strcpy(cstr6,Actions[i].c_str());
             painter.drawText(882,350+i*40,cstr6);
         }
         // montre la case où l'objet peut bouger, pas tenu compte du type de terrain !!!
        if(!unit->getHasMoved()){
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

    // choisit l'unité adverse
    else if(indexP == 2){
        for (int i = 0; i<3;i++){
            painter.drawRect(880,320+i*40,3*objectSize,objectSize);
            char cstr6[Actions[i].size() + 1];
            strcpy(cstr6,Actions[i].c_str());
            painter.drawText(882,350+i*40,cstr6);
        }

        int pxa = g->getPlayer(turn%2)->getUnits()[indexI]->getPosX();
        int pya = g->getPlayer(turn%2)->getUnits()[indexI]->getPosY();
        for(Unit* unit : g->getPlayer(1-turn%2)->getUnits()){
            int pxd = unit->getPosX();
            int pyd = unit->getPosY();
            std::cout<<pxa<<pya<<","<<pxd<<pyd<<std::endl;
            if (abs(pxd-pxa)<3*objectSize && abs(pyd-pya)<3*objectSize){

                painter.setBrush(QColor(255,0,0,63));
                if (turn%2==0){
                    painter.setBrush(QColor(0,0,255,63));
                }
                painter.drawRect(pxd,pyd,objectSize,objectSize);
            }
        }
    }

    // cas ou on choisit un building

    if(indexB == -1){

    }
    else if(indexB == 0||indexB == 1){
        int bType = g->getPlayer(indexB)->getBuildings()[indexI]->getType();
        painter.drawText(880,180,"Options : ");
        string color = "red";
        if (indexB==1){
            color = "blue";
        }
        if (bType==35){
            for (int i = 0; i<8;i++){
                painter.drawRect(880,200+i*40,objectSize,objectSize);
                QRectF target(880,200+i*40,objectSize,objectSize);
                std::string type = ":/images/PngAdvancedWar/"+Finventary[i][0]+color+".png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);

                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial", 12));

                char cstr2[Finventary[i][0].size() + 1];
                strcpy(cstr2,Finventary[i][0].c_str());
                painter.drawText(930,218+i*40,cstr2);

                char cstr3[Finventary[i][1].size() + 1];
                strcpy(cstr3,Finventary[i][1].c_str());
                painter.drawText(930,238+i*40,cstr3);
            }
        }
        else if(bType == 36){
            for (int i = 0; i<3;i++){
                painter.drawRect(880,200+i*40,objectSize,objectSize);
                QRectF target(880,200+i*40,objectSize,objectSize);
                std::string type = ":/images/PngAdvancedWar/"+Ainventary[i][0]+color+".png";
                char cstr[type.size() + 1];
                strcpy(cstr,type.c_str());
                QImage image(cstr);
                painter.drawImage(target,image);

                char cstr2[Ainventary[i][0].size() + 1];
                strcpy(cstr2,Ainventary[i][0].c_str());
                painter.drawText(930,218+i*40,cstr2);

                char cstr3[Ainventary[i][1].size() + 1];
                strcpy(cstr3,Ainventary[i][1].c_str());
                painter.drawText(930,238+i*40,cstr3);

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

    for (int i = 0; indexP==-1 && i < g->getPlayer(turn%2)->getUnits().size();i++){
        Unit* unit = g->getPlayer(turn%2)->getUnits()[i];
        int px = unit->getPosX();
        int py = unit->getPosY();
        if (px < clx && ((px+objectSize) > clx && py < cly && (py+objectSize) > cly)){
            indexI = i;
            indexP = turn%2;
            indexB = -1;
            std::cout << "Unit index "<< i <<" from player "<< indexP+1 <<" selected" << std::endl;
            break;
        }
        else{
        }
    }

    // selection d'une unité ennemi

    for (int i = 0; indexP==2 && i < g->getPlayer(1-turn%2)->getUnits().size();i++){
        Unit* unit = g->getPlayer(1-turn%2)->getUnits()[i];
        int px = unit->getPosX();
        int py = unit->getPosY();
        if (px < clx && (px+objectSize) > clx && py < cly && (py+objectSize) > cly){
            g->Combat(g->getPlayer(turn%2)->getUnits()[indexI], unit);
            indexI = -1;
            indexP = -1;
            indexA = -1;
            std::cout << "Enemy unit index "<< i <<" from player "<< 2-indexP <<" selected" << std::endl;
            break;
        }
        else{

        }
    }



    // selection d'un batiment de player

    for (int i=0; indexP==-1 && indexB==-1 && i < g->getPlayer(turn%2)->getBuildings().size() ;i++){
        Building* building = g->getPlayer(turn%2)->getBuildings()[i];
        int px = building->getPosX();
        int py = building->getPosY();
        if (!building->getHasMadeUnit() && px < clx && (px+objectSize) > clx && py < cly && (py+objectSize) > cly){
            indexI = i;
            indexB = turn%2;
            std::cout << "building index "<< i <<" from player "<< turn <<" selected" << std::endl;
        }
    }

        // Choix de l'action

    if (indexP==0 || indexP==1){
        if((880 < clx && (880+3*objectSize) > clx && 320 < cly && (320+3*objectSize) > cly)){
        indexA = ((cly-320)-(cly-320)%40)/40;
        }
        else{
        // déplacement
            Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
            int depx = abs((clx-clx%objectSize)-SelectedUnit->getPosX());
            int depy = abs((cly-cly%objectSize)-SelectedUnit->getPosY());
            bool cond1(depx == 0 && depy == 0);
            if(!SelectedUnit->getHasMoved() && !cond1 && abs(depx)+abs(depy) <= SelectedUnit->getDeplacement()*objectSize && clx<840){

                SelectedUnit->setPosX(clx-clx%objectSize);
                SelectedUnit->setPosY(cly-cly%objectSize);
                SelectedUnit->setHasMoved(true);
                indexP = -1;
                indexA = -1;
            }
            else if(abs(depx)+abs(depy)>SelectedUnit->getDeplacement()*objectSize && clx<840){

                indexP = -1;
                indexA = -1;
            }
        }
    }

                 // Actions de l'unit


    // attaquer
    if(indexA == 0){
        Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
        if(!SelectedUnit->getHasAttacked()&& indexP != 2){
            indexP = 2;
        }
        else if((880 < clx && (880+3*objectSize) > clx && 320+2*objectSize < cly && (320+3*objectSize) > cly)){

            indexP = -1;
            indexA = -1;
        }

    }
    //prendre une ville
    else if(indexA == 1){
        for(Building* building : g->getBuildings()){
            int bType = building->getType();
            if(bType == 34){
                int bx = building->getPosX();
                int by = building->getPosY();
                Unit* unit = g->getPlayer(indexP)->getUnits()[indexI];
                int ux = unit->getPosX();
                int uy = unit->getPosY();
                if (bx==ux && by==uy){
                    City* city = dynamic_cast<City*>(building);
                    // remarque, il faut supprimer l'element de g->getbuildings()
                    g->getPlayer(indexP)->addBuilding(city);

                }
            }
        }

    }

        // refresh action
    else if(indexA == 2){
        indexA = -1;
        indexP = -1;
    }



    //  Création de l'unit

    if (indexB == 0||indexB == 1){
        Building* building = g->getPlayer(indexB)->getBuildings()[indexI];
        int bType = building->getType();
        int px = building->getPosX();
        int py = building->getPosY();

        if(bType == 34){
            std::cout<< "building is a City"<<std::endl;
        }
        else if(bType == 35){
            std::cout<< "building is a factory"<<std::endl;
            if ((880 < clx && (880+objectSize) > clx && 200 < cly && (200+7*objectSize) > cly)){
                building->setHasMadeUnit(true);
                Factory* factory = dynamic_cast<Factory*>(building);
                int indexU = ((cly-200)-(cly-200)%40)/40;
                Unit* unit = factory->createNewUnit(Finventary[indexU][0]);
                g->getPlayer(turn%2)->addUnit(unit);
                indexB = -1;
            }
            else if (px < clx && (px+objectSize) > clx && py < cly && (py+objectSize) > cly){
            // do nothing
            }
            else{
                indexB = -1;
            }
        }
        else if(bType == 36){
            std::cout<< "building is an Airport"<<std::endl;
            if ((880 < clx && (880+objectSize) > clx && 200 < cly && (200+3*objectSize) > cly)){
                building->setHasMadeUnit(true);
                Airport* airport = dynamic_cast<Airport*>(building);
                int indexU = ((cly-200)-(cly-200)%40)/40;
                Unit* unit = airport->createNewUnit(Ainventary[indexU][0]);
                g->getPlayer(turn%2)->addUnit(unit);
                indexB = -1;
            }
            else if (px < clx && (px+objectSize) > clx && py < cly && (py+objectSize) > cly){
            // do nothing
            }
            else{
                indexB = -1;
            }
        }
    }
//    std::cout<<"indexA " + std::to_string(indexA)<<std::endl;
  //  std::cout<<"indexP " + std::to_string(indexP)<<std::endl;

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
        case Qt::Key_Space :
            nextTurnButton();
            break;
        }
    }
    repaint();
}



