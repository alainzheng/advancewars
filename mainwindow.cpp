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
#include "ia.h"

#include <QPixmap>



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)

{

    point = QPoint(0,0);
    std::cout << "MainWindow created" << std::endl;
    ui->setupUi(this);
    g = new Game(0);

    initializeMap(); // fait encore rien



    turnButton = new QPushButton("(N)ext turn",this);
    turnButton->setGeometry(40,700,160,100);
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

void MainWindow::pointSetPos(int px, int py){
    point.setX(px);
    point.setY(py);
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
    Actions[1] = "Capt";
    Actions[2] = "Fusion";
    Actions[3] = "Wait";
    Actions[4] = "Return";




}

void MainWindow::recPossibleCases(int x, int y, int dep, int moveType){// x et y en forme (x-x%40)/40 // ajouter le terrain defCase si plus petit alors on change de route
    //std::cout<<"x " << x<<";y " << y<<";dep " << dep<<" mt " << moveType<<std::endl;

    if(x>0 && dep-g->getTerrainChart(moveType,g->getTerrainsDef(x-1,y))>=0 && g->getTerrainChart(moveType,g->getTerrainsDef(x-1,y))!=0){
        Terrain* terrain = g->getTerrains()[y*21+x-1];
        int mp = dep-g->getTerrainChart(moveType,g->getTerrainsDef(x-1,y));
        terrain->setIsCase(true);
        if(mp > terrain->getMovePoints()){
            terrain->setMovePoints(mp);
            recPossibleCases(x-1,y,mp,moveType);

        }
    }
    if(x<20 && dep-g->getTerrainChart(moveType,g->getTerrainsDef(x+1,y))>=0 && g->getTerrainChart(moveType,g->getTerrainsDef(x+1,y))!=0){
        Terrain* terrain = g->getTerrains()[y*21+x+1];
        int mp = dep-g->getTerrainChart(moveType,g->getTerrainsDef(x+1,y));
        terrain->setIsCase(true);
        if(mp > terrain->getMovePoints()){
            terrain->setMovePoints(mp);
            recPossibleCases(x+1,y,mp,moveType);
        }
    }
    if(y>0 && dep-g->getTerrainChart(moveType,g->getTerrainsDef(x,y-1))>=0 && g->getTerrainChart(moveType,g->getTerrainsDef(x,y-1))!=0){
        Terrain* terrain = g->getTerrains()[(y-1)*21+x];
        int mp = dep-g->getTerrainChart(moveType,g->getTerrainsDef(x,y-1));
        terrain->setIsCase(true);
        if(mp > terrain->getMovePoints()){
            terrain->setMovePoints(mp);
            recPossibleCases(x,y-1,mp,moveType);
        }
    }
    if(y<16 && dep-g->getTerrainChart(moveType,g->getTerrainsDef(x,y+1))>=0 && g->getTerrainChart(moveType,g->getTerrainsDef(x,y+1))!=0){
        Terrain* terrain = g->getTerrains()[(y+1)*21+x];
        int mp = dep-g->getTerrainChart(moveType,g->getTerrainsDef(x,y+1));
        terrain->setIsCase(true);
        if(mp > terrain->getMovePoints()){
            terrain->setMovePoints(mp);
            recPossibleCases(x,y+1,mp,moveType);
        }
    }
}

void MainWindow::initPossibleCases()
{
    for(Terrain* terrain : g->getTerrains()){
        terrain->setIsCase(false);
        terrain->setMovePoints(0);
    }
}

void MainWindow::iaPathFind(){
    //
    Unit* unit = g->getPlayer(1)->getUnits()[0];// player 1 jeu
}



void MainWindow::nextTurnButton(){
    IA* ia = static_cast<IA*>(g->getPlayer(1-turn%2));
    if(ia && ia->getiaType()==0){ //pathfind
        iaPathFind();
    }
    else{
        for(Unit* unit : g->getPlayer(turn%2)->getUnits()){
            unit->setHasMoved(false);
            unit->setHasActed(false);
        }
        //joueur finissant son tour
        for(Building* building : g->getPlayer(turn%2)->getBuildings()){
            building->setHasMadeUnit(false);
        }
        // joueur commencant son tour
        for(Building* building : g->getPlayer(1-turn%2)->getBuildings()){
            g->getPlayer(1-turn%2)->setMoney(g->getPlayer(1-turn%2)->getMoney()+1000);
            Unit* unit = g->getUnitAtPos(building->getPosX(),building->getPosY(),1-turn%2);
            if(unit && unit->getLifes()<10){
                unit->setLifes(unit->getLifes()+2);
                g->getPlayer(1-turn%2)->setMoney(g->getPlayer(1-turn%2)->getMoney()-(unit->getCost()/10));
            }
        }
    }
    indexP = -1;
    indexA = -1;
    indexB = -1;
    turn++;
    repaint();
}




/*                         PAINT EVENT       */




void MainWindow::paintEvent(QPaintEvent* event){

    QPainter painter(this);
    painter.fillRect(0,0,1480,880,Qt::Dense4Pattern);
    // information de player

    painter.setPen(Qt::red);
    painter.setFont(QFont("times", 15,QFont::DemiBold,true));
    painter.drawText(860,35,QString::fromStdString("Player 1 : "+std::to_string(g->getPlayer(0)->getMoney())));
    painter.drawText(860,65,QString::fromStdString("Units : "+std::to_string(g->getPlayer(0)->getUnits().size())));
    painter.drawText(860,95,QString::fromStdString("Buildings : "+std::to_string(g->getPlayer(0)->getBuildings().size())));

    painter.setPen(Qt::blue);
    painter.drawText(1160,35,QString::fromStdString("Player 2 : "+std::to_string(g->getPlayer(1)->getMoney())));
    painter.drawText(1160,65,QString::fromStdString("Units : "+std::to_string(g->getPlayer(1)->getUnits().size())));
    painter.drawText(1160,95,QString::fromStdString("Buildings : "+std::to_string(g->getPlayer(1)->getBuildings().size())));

    if(turn%2==0){painter.setPen(Qt::red);}
    painter.drawText(220,730,QString::fromStdString("Player "+ std::to_string(1+turn%2) + " plays, turn " + std::to_string((int) round(0.5+turn/2))));

    painter.setPen(Qt::black);
    painter.setFont(QFont("New Times", 20));
    painter.drawText(220,770,QString::fromStdString("(J) Select "));
    painter.drawText(220,810,QString::fromStdString("(K) Undo "));

    // dessine le terrain de base, la map
    for(int i = 0; i<21;i++){
        for(int j= 0;j<17;j++){
            QRectF target(i*objectSize,j*objectSize,objectSize,objectSize);
            QImage image(QString::fromStdString(":/images/PngAdvancedWar/1.png"));
            painter.drawImage(target,image);
        }
    }

    for (Terrain* terrain : g->getTerrains()){
        int px = terrain->getPosX();
        int py = terrain->getPosY();
        QRectF target(px,py,objectSize,objectSize);
        QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+std::to_string(terrain->getType())+".png"));
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
        QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+std::to_string(building->getType())+".png"));
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
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+std::to_string(building->getType()+4)+".png"));
                painter.drawImage(target,image);
            }
            else{
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+std::to_string(building->getType()+9)+".png"));
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
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+unit->getName()+"red.png"));
                painter.drawImage(target,image);
            }

            else{
                QRectF target(px,py,objectSize,objectSize);
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+unit->getName()+"blue.png"));
                painter.drawImage(target,image);
            }
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 9,QFont::Bold));
            painter.drawText(px+20,py+35,QString::fromStdString(std::to_string(unit->getLifes())));

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

         // caracteristique unit
         QRectF target(860,125,1.3*objectSize,1.3*objectSize);
         string color = indexP == 0 ? "red" : "blue";
         QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+unit->getName()+color+".png"));
         painter.drawImage(target,image);
         painter.drawText(970,210,QString::fromStdString(unit->getName()));
         painter.drawText(860,210,"Type : ");

         painter.drawText(970,235,QString::fromStdString(std::to_string(unit->getLifes())));
         painter.drawText(860,235,"Lifes : ");

         painter.drawText(1060,260,QString::fromStdString(std::to_string(unit->getDeplacement())));
         painter.drawText(860,260,"Deplacement : ");


         // facultatif, donne info de la ville sous l'unit
         Building* building = g->getBuildingAtPos(px,py);
         if (building) {
             QRectF target(1180,125,1.3*objectSize,1.3*(objectSize+20));
             QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+std::to_string(building->getType())+".png"));
             painter.drawImage(target,image);
             City* city = dynamic_cast<City*>(building);
             if(city){
                 painter.drawText(1180,235,QString::fromStdString("City capt : " + std::to_string(city->getCost())));
                 painter.drawText(1180,270,QString::fromStdString("Def : "+ std::to_string(city->getDefense())));
             }
             else{
                 painter.drawText(1180,270,QString::fromStdString("Def : "+ std::to_string(building->getDefense())));
             }
        }
         // dessine les différents cas lorsque un player est choisi
        if(indexP!=-1){
            for (int i = 0; i<5;i++){
             painter.drawRect(880,320+i*40,objectSize,objectSize);
             painter.drawText(935,350+i*40,QString::fromStdString(Actions[i]));
            }
            painter.drawText(880,305,QString::fromStdString("Menu (M)"));
        }
         // montre la case où l'objet peut bouger, pas tenu compte du type de terrain !!!

        painter.setBrush(QColor(255,0,0,63));
        if(indexP==1){painter.setBrush(QColor(0,0,255,63));}


        if(!unit->getHasMoved() && !unit->getHasActed() && indexA!=2){
            for(Terrain* terrain : g->getTerrains()){
                if(terrain->getIsCase()){
                    painter.drawRect(terrain->getPosX(),terrain->getPosY(),objectSize,objectSize);
                }
            }
        }
        // cas specifique de la fusion
        else if(indexA==2){
            painter.setBrush(QColor(255,0,0,63));
            if (turn%2==1){
                painter.setBrush(QColor(0,0,255,63));
            }
            for(Unit* otherunit : g->getPlayer(indexP)->getUnits()){
                if(otherunit != unit && otherunit->getType() == unit->getType()){
                    if(abs(otherunit->getPosX()-px)+abs(otherunit->getPosY()-py)<=objectSize)
                    painter.drawRect(otherunit->getPosX(),otherunit->getPosY(),objectSize,objectSize);
                }
            }
        }
    }

    // choisit l'unité adverse, cas de l'attaque

    else if(indexP == 2){
        for (int i = 0; i<5;i++){
            painter.drawRect(880,320+i*40,objectSize,objectSize);
            painter.drawText(935,350+i*40,QString::fromStdString(Actions[i]));
        }
        painter.drawText(880,305,QString::fromStdString("Menu (M)"));
        int attackingpx = g->getPlayer(turn%2)->getUnits()[indexI]->getPosX();
        int attackingpy = g->getPlayer(turn%2)->getUnits()[indexI]->getPosY();
        for(Unit* unit : g->getPlayer(1-turn%2)->getUnits()){
            int defendingpx = unit->getPosX();
            int defendingpy = unit->getPosY();
            if(abs(defendingpx-attackingpx)+abs(defendingpy-attackingpy)<=objectSize){
                painter.setBrush(QColor(255,0,0,63));
                if (turn%2==0){
                    painter.setBrush(QColor(0,0,255,63));
                }
                painter.drawRect(defendingpx,defendingpy,objectSize,objectSize);
            }
        }
    }


    // cas ou on choisit un building

    if(indexB == -1){
        //rien
    }
    else if(indexB == 0||indexB == 1){
        Building* building = g->getPlayer(indexB)->getBuildings()[indexI];
        int bType = building->getType();
        painter.drawText(880,180,"Options : ");
        string color = indexB==0 ? "red" : "blue";
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 12));

        if(bType==34){
            City* city = dynamic_cast<City*>(building);
            painter.drawRect(1120,200,objectSize,objectSize+20);
            QRectF target(1120,200,objectSize,objectSize+20);
            QImage image(QString::fromStdString(":/images/PngAdvancedWar/34.png"));
            painter.drawImage(target,image);
            painter.drawText(1180,235,QString::fromStdString("City cap : " + std::to_string(city->getCost())));
            painter.drawText(1180,270,QString::fromStdString("Def : "+ std::to_string(city->getDefense())));
        }
        else if (bType==35){
            for (int i = 0; i<8;i++){
                painter.drawRect(880,320+i*40,objectSize,objectSize);
                QRectF target(880,320+i*40,objectSize,objectSize);
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+Finventary[i][0]+color+".png"));
                painter.drawImage(target,image);
                painter.drawText(930,338+i*40,QString::fromStdString(Finventary[i][0]));
                painter.drawText(930,358+i*40,QString::fromStdString(Finventary[i][1]));
            }
            painter.drawText(880,305,QString::fromStdString("Menu (M)"));
        }
        else if(bType == 36){
            for (int i = 0; i<3;i++){
                painter.drawRect(880,320+i*40,objectSize,objectSize);
                QRectF target(880,320+i*40,objectSize,objectSize);
                QImage image(QString::fromStdString(":/images/PngAdvancedWar/"+Ainventary[i][0]+color+".png"));
                painter.drawImage(target,image);
                painter.drawText(930,338+i*40,QString::fromStdString(Ainventary[i][0]));
                painter.drawText(930,358+i*40,QString::fromStdString(Ainventary[i][1]));
            }
            painter.drawText(880,305,QString::fromStdString("Menu (M)"));
        }
    }
    // donner le cost de city
    for (Building* building : g->getBuildings()){
        int px = building->getPosX();
        int py = building->getPosY();
        City* city = dynamic_cast<City*>(building);
        if(city){
            painter.setPen(Qt::yellow);
            painter.setFont(QFont("Arial", 10,QFont::Bold));
            painter.drawText(px+20,py+15,QString::fromStdString(std::to_string(city->getCost())));
        }
    }
    for(int p = 0; p<2;p++){
        for (Building* building : g->getPlayer(p)->getBuildings()){
            int px = building->getPosX();
            int py = building->getPosY();
            City* city = dynamic_cast<City*>(building);
            if(city){
                painter.setPen(Qt::yellow);
                painter.setFont(QFont("Arial", 10,QFont::Bold));
                painter.drawText(px+20,py+15,QString::fromStdString(std::to_string(city->getCost())));
            }
        }
    }
    painter.setBrush(QColor(0,0,0,50));
    painter.setPen(Qt::red);
    painter.drawRect(point.x(),point.y(),objectSize,objectSize);
    painter.setPen(Qt::black);
}








/*                        TOUCHE SOURIS   */







void MainWindow::mousePressEvent(QMouseEvent *event){
    // object selected
    int clx = event->x();
    int cly = event->y();
    //std::cout<<"x "<<clx<<" y "<<cly<<std::endl;
    if(clx<840 && cly<680){
        pointSetPos(clx-clx%objectSize,cly-cly%objectSize);
    }

    // selection d'un unité
    for(int p = 0; indexP==-1 && p<2;p++){
        for (int i = 0; i < g->getPlayer(p)->getUnits().size();i++){
            Unit* unit = g->getPlayer(p)->getUnits()[i];
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){

                indexI = i;
                indexP = p;
                indexB = -1;
                if(!unit->getHasMoved()){
                    initPossibleCases();
                    recPossibleCases((px-px%objectSize)/objectSize,(py-py%objectSize)/objectSize,unit->getDeplacement(),unit->getMoveType());
                }
                std::cout << "Unit index "<< i <<" from player "<< indexP+1 <<" selected" << std::endl;
                break;
            }
        }
    }


    // selection d'une unité ennemi pour attaquer
    if(indexP==2){
        Unit* attackingUnit = g->getPlayer(turn%2)->getUnits()[indexI];
        for (int i = 0; !attackingUnit->getHasActed() && i < g->getPlayer(1-turn%2)->getUnits().size();i++){
            Unit* unit = g->getPlayer(1-turn%2)->getUnits()[i];
            int px = unit->getPosX();
            int py = unit->getPosY();
            if (px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){
                if(abs(attackingUnit->getPosX()-px)+abs(attackingUnit->getPosY()-py)<=objectSize){
                    g->Combat(attackingUnit, unit);              // premier combat
                    attackingUnit->setHasActed(true);
                    attackingUnit->setHasMoved(true);
                    if (unit->getLifes()<=0){ // elimine l'unit adverse
                        // le cas ou si le joueur meurt, la ville se remet à 20.
                        if(unit->getCaptureState()){
                            unit->setCaptureState(false);
                            Building* building = g->getBuildingAtPos(px,py);
                            if(!building){
                                building = g->getBuildingAtPos(unit->getPosX(),unit->getPosY(),turn%2);
                            }
                            if (building && building->getType()==34){
                                City* city = dynamic_cast<City*>(building);
                                city->setCost(20);
                            }

                        }
                        g->getPlayer(1-turn%2)->getUnits().erase(g->getPlayer(1-turn%2)->getUnits().begin()+i);
                        delete unit;
                    }
                    else{                                          //deuxieme combat, defense
                        g->Combat(unit,attackingUnit);
                        if (attackingUnit->getLifes()<=0){ // elimine l'unit adverse
                            // le cas ou si le joueur meurt, la ville se remet à 20.
                            if(attackingUnit->getCaptureState()){
                                attackingUnit->setCaptureState(false);
                                Building* building = g->getBuildingAtPos(px,py);
                                if(!building){
                                    building = g->getBuildingAtPos(unit->getPosX(),unit->getPosY(),1-turn%2);
                                }
                                if (building && building->getType()==34){
                                    City* city = dynamic_cast<City*>(building);
                                    city->setCost(20);
                                }
                            }
                            g->getPlayer(turn%2)->getUnits().erase(g->getPlayer(turn%2)->getUnits().begin()+indexI);
                            delete attackingUnit;
                        }

                    }
                    indexI = -1;
                    indexP = -1;
                    indexA = -1;
                    std::cout << "Enemy unit index "<< i <<" from player "<< 2-turn%2 <<" selected" << std::endl;
                    break;
                }
            }
        }
    }


    // selection d'un batiment de player

    for (int i=0; indexP==-1 && indexA==-1 && indexB==-1 && i < g->getPlayer(turn%2)->getBuildings().size() ;i++){
        Building* building = g->getPlayer(turn%2)->getBuildings()[i];
        int px = building->getPosX();
        int py = building->getPosY();
        if (!building->getHasMadeUnit() && px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){
            indexI = i;
            indexB = turn%2;
            std::cout << "building index "<< i <<" from player "<< turn <<" selected" << std::endl;
            break;
        }
    }




        // Choix de l'action si unit du player du turn choisi


    if (indexP == 0 || indexP == 1){

        if(indexP == turn%2 && 880 <= clx && 880+objectSize > clx && 320 <= cly && 320+5*objectSize > cly){
            indexA = ((cly-320)-(cly-320)%40)/40;
            if(indexA == 2){
                Unit* unit = g->getPlayer(indexP)->getUnits()[indexI];
                pointSetPos(unit->getPosX(),unit->getPosY());
            }
            initPossibleCases();

        }
        else if(clx<840 && cly<680){    // déplacement ou rien
            Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
            if(!SelectedUnit->getHasMoved() && !SelectedUnit->getHasActed()){
                int px = clx-clx%objectSize;  // prochaine position
                int py = cly-cly%objectSize;
                int sx = SelectedUnit->getPosX();  // position actuelle
                int sy = SelectedUnit->getPosY();
                int depx = abs(px-sx);
                int depy = abs(py-sy);
                bool cond1(depx == 0 && depy == 0);// condition de selection de l'unit
                if(indexA!=2 && indexP==turn%2 && !cond1 && g->getTerrainAtPos(px,py)->getIsCase()){
                    Unit* unit = g->getUnitAtPos(px,py,0);
                    Unit* unit2 = g->getUnitAtPos(px,py,1);
                    if(!unit && !unit2){
                        if(SelectedUnit->getCaptureState()){
                            SelectedUnit->setCaptureState(false);
                            Building* building = g->getBuildingAtPos(sx,sy);
                            if (building && building->getType()==34){
                                City* city = dynamic_cast<City*>(building);
                                city->setCost(20);
                            }
                        }
                        SelectedUnit->setPosX(px);
                        SelectedUnit->setPosY(py);
                        SelectedUnit->setHasMoved(true);
                    }
                    indexP = -1;
                    indexA = -1;
                }
            }
        }
        // cas ou p=2 et on veut annuler l'action par exemple parce que unit enemy pas selectionné
        else if(880 <= clx && 880+objectSize > clx && 320+4*objectSize <= cly && 320+5*objectSize > cly){
            Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
            indexP = -1;
            indexA = -1;
            pointSetPos(SelectedUnit->getPosX(),SelectedUnit->getPosY());
        }
    }

                 // ACTIONS DE L'UNIT



    if(indexA == -1){
        //do nothing, permet de passer tout les else if
    }

        // attaquer
    else if(indexA == 0){
        Unit* SelectedUnit = g->getPlayer(turn%2)->getUnits()[indexI];
        if(!SelectedUnit->getHasActed() && indexP != 2){
            indexP = 2;
            pointSetPos(SelectedUnit->getPosX(),SelectedUnit->getPosY());
        }
        // cas ou p=2 et on veut annuler l'action par exemple parce que unit enemy pas selectionné
        else if((880 <= clx && 880+objectSize > clx && 320+4*objectSize <= cly && 320+5*objectSize > cly)){
            indexP = -1;
            indexA = -1;
            pointSetPos(SelectedUnit->getPosX(),SelectedUnit->getPosY());
        }
    }


        //prendre une ville
    else if(indexA == 1){
        Unit* unit = g->getPlayer(indexP)->getUnits()[indexI];
        Building* building = g->getBuildingAtPos(unit->getPosX(),unit->getPosY());
        bool buildFromPlayer(false);
        if(!building){
            building = g->getBuildingAtPos(unit->getPosX(),unit->getPosY(),1-turn%2);
            buildFromPlayer = true;
        }
        if(building && building->getType()==34){
            bool cond(unit->getName()== "Infantry" || unit->getName()== "Bazooka");
            if (!unit->getHasActed() && cond){
                unit->setCaptureState(true);
                unit->setHasActed(true);
                City* city = dynamic_cast<City*>(building);
                city->setCost(city->getCost()-unit->getLifes());
                std::cout<<buildFromPlayer<<std::endl;
                if (city->getCost()<=0){
                    unit->setCaptureState(false);
                    if(buildFromPlayer){
                        int index = std::distance(g->getPlayer(1-turn%2)->getBuildings().begin(), std::find(g->getPlayer(1-turn%2)->getBuildings().begin(), g->getPlayer(1-turn%2)->getBuildings().end(), building));
                        g->getPlayer(1-turn%2)->getBuildings().erase(g->getPlayer(1-turn%2)->getBuildings().begin()+index);
                        g->getPlayer(indexP)->addBuilding(city);
                        city->setCost(20);
                    }
                    else{
                        int index = std::distance(g->getBuildings().begin(), std::find(g->getBuildings().begin(), g->getBuildings().end(), building));
                        g->getBuildings().erase(g->getBuildings().begin()+index);
                        g->getPlayer(indexP)->addBuilding(city);
                        city->setCost(20);
                    }
                }
            }
        }
        indexA = -1;
        indexI = -1;
        indexP = -1;
        pointSetPos(unit->getPosX(),unit->getPosY());
    }

    // fusion de unit

    else if(indexA == 2){
        Unit* selectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
        int px = selectedUnit->getPosX();
        int py = selectedUnit->getPosY();
        if (clx<840 && !selectedUnit->getHasActed()){ // condition pour appuyer sur fusion
            for(int i = 0; g->getPlayer(indexP)->getUnits().size()>i;i++){
                Unit* selectedUnit2 = g->getPlayer(indexP)->getUnits()[i];
                if (selectedUnit != selectedUnit2 && selectedUnit->getType() == selectedUnit2->getType() && selectedUnit2->getPosX()==clx-clx%objectSize && selectedUnit2->getPosY()==cly-cly%objectSize){
                    bool condPos(abs(selectedUnit2->getPosX()-px)+abs(selectedUnit2->getPosY()-py)<=objectSize);
                    bool condlif(selectedUnit->getLifes() < 10 || selectedUnit2->getLifes()<10);
                    if (condPos && condlif){
                        std::cout<<"fusion test3"<<std::endl;
                        if(selectedUnit->getCaptureState()){
                            selectedUnit->setCaptureState(false);
                            Building* building = g->getBuildingAtPos(px,py);
                            if (building && building->getType()==34){
                                City* city = dynamic_cast<City*>(building);
                                city->setCost(20);
                            }
                        }
                        selectedUnit->setLifes(selectedUnit->getLifes()+selectedUnit2->getLifes());
                        selectedUnit->setHasActed(true);
                        delete selectedUnit2;
                        g->getPlayer(indexP)->getUnits().erase(g->getPlayer(indexP)->getUnits().begin()+i);
                        indexA = -1;
                        indexP = -1;
                        indexI = -1;
                        break;
                    }
                }
            }
        }
    }

    // wait turn

    else if(indexA == 3){
        Unit* SelectedUnit = g->getPlayer(indexP)->getUnits()[indexI];
        SelectedUnit->setHasMoved(true);
        SelectedUnit->setHasActed(true);
        pointSetPos(SelectedUnit->getPosX(),SelectedUnit->getPosY());
        indexA = -1;
        indexP = -1;
        initPossibleCases();
    }

    // refresh action pas obligé
    else if(indexA == 4){

        indexA = -1;
        indexP = -1;
        pointSetPos(g->getPlayer(turn%2)->getUnits()[indexI]->getPosX(),g->getPlayer(turn%2)->getUnits()[indexI]->getPosY());
        initPossibleCases();
    }


/////////////// BUILDING

    //  Création de l'unit

    if (indexB == 0||indexB == 1){
        Building* building = g->getPlayer(indexB)->getBuildings()[indexI];
        int bType = building->getType();
        int px = building->getPosX();
        int py = building->getPosY();

        if(bType == 34){
            std::cout<< "building is a City"<<std::endl;
            if (px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){
            // do nothing
                // utile pour choisir le batiment
            }
            else{
                indexB = -1;
            }
        }
        else if(bType == 35){
            std::cout<< "building is a factory"<<std::endl;
            if ((880 <= clx && 880+objectSize > clx && 320 <= cly && 320+7*objectSize > cly)){
                int indexU = ((cly-320)-(cly-320)%40)/40;
                if (g->getPlayer(indexB)->getMoney() >= std::stoi(Finventary[indexU][1])){
                    Factory* factory = dynamic_cast<Factory*>(building);
                    Unit* unit = factory->createNewUnit(Finventary[indexU][0]);
                    building->setHasMadeUnit(true);
                    g->getPlayer(indexB)->addUnit(unit);
                    pointSetPos(unit->getPosX(),unit->getPosY());
                    indexB = -1;
                }
                else{
                    std::cout<<"not enough money"<<std::endl;
                }
            }
            else if (px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){
            // do nothing
                // utile pour choisir le batiment
            }
            else{
                indexB = -1;
            }
        }
        else if(bType == 36){
            std::cout<< "building is an Airport"<<std::endl;
            if ((880 <= clx && 880+objectSize > clx && 320 <= cly && 320+3*objectSize > cly)){
                int indexU = ((cly-320)-(cly-320)%40)/40;
                if(g->getPlayer(indexB)->getMoney() >= std::stoi(Ainventary[indexU][1])){
                    Airport* airport = dynamic_cast<Airport*>(building);
                    building->setHasMadeUnit(true);
                    Unit* unit = airport->createNewUnit(Ainventary[indexU][0]);
                    g->getPlayer(indexB)->addUnit(unit);
                    pointSetPos(unit->getPosX(),unit->getPosY());
                    indexB = -1;
                }
                else{
                    std::cout<<"not enough money"<<std::endl;
                }
            }
            else if (px <= clx && px+objectSize > clx && py <= cly && py+objectSize > cly){
            // do nothing
            }
            else{
                indexB = -1;
            }
        }
    }

    repaint();
}



/*                 TOUCHES CLAVIER        */


void MainWindow::keyPressEvent(QKeyEvent *event){
    //std::cout << event->key() << std::endl;
    // seulement pour le curseur, le menu et les choix
    switch(event->key()){
        case Qt::Key_N :
            nextTurnButton();

            break;
        case Qt::Key_K ://undo
        if(point.x()==880){
            if(indexB!=-1){
                Building* build = g->getPlayer(turn%2)->getBuildings()[indexI];
                pointSetPos(build->getPosX(),build->getPosY());
            }
            else if(indexP!=-1 && indexP!=2 && indexP == turn%2){
                Unit* unit = g->getPlayer(turn%2)->getUnits()[indexI];
                pointSetPos(unit->getPosX(),unit->getPosY());
            }
            else{
                pointSetPos(0,0);
            }
        }
            indexP = -1;
            indexA = -1;
            indexB = -1;
            std::cout<<"undo selected"<<std::endl;
            break;
        case Qt::Key_M :{
        if(point.x()==880){
            if(indexB!=-1){
                Building* build = g->getPlayer(turn%2)->getBuildings()[indexI];
                pointSetPos(build->getPosX(),build->getPosY());
            }
            else if(indexP!=-1 && indexP!=2 && indexP == turn%2){
                Unit* unit = g->getPlayer(turn%2)->getUnits()[indexI];
                pointSetPos(unit->getPosX(),unit->getPosY());
            }
            else{
                pointSetPos(0,0);
            }
        }
        else if(indexP!=-1 && indexP!=2){
            pointSetPos(880,320);
        }
        else if(indexB!=-1){
            pointSetPos(880,320);
        }
            break;
        }
        case Qt::Key_J :{
            QMouseEvent* mouseEvent = new QMouseEvent(QEvent::GraphicsSceneMousePress,point, Qt::NoButton,Qt::NoButton,Qt::NoModifier);
            mousePressEvent(mouseEvent);
            delete mouseEvent;
        break;
        }
        case Qt::Key_Z:
        if(point.y()>0 && point.x()<=800){
            point.setY(point.y()-40);
        }
        else if(point.x()==880){
            if(point.y()>320){
                point.setY(point.y()-40);
            }
        }
            break;
        case Qt::Key_S:
        if(point.y()<640 && point.x()<=800){
            point.setY(point.y()+40);
        }
        else if(point.x()==880){
            if(indexB!=-1){
                int btype = g->getPlayer(indexB)->getBuildings()[indexI]->getType();
                if(btype==35){
                    if(point.y()<320+40*7){
                        point.setY(point.y()+40);
                    }
                }
                else if(btype==36){
                    if(point.y()<320+80){
                        point.setY(point.y()+40);
                    }
                }
            }
            else if(indexP!=-1 &&indexP!=2){
                if(point.y()<480){
                    point.setY(point.y()+40);
                }
            }
        }
        break;
        case Qt::Key_D:
        if(point.x()>=0 && point.x()<800){
            point.setX(point.x()+40);
        }
        break;
        case Qt::Key_Q:
        if(point.x()>0 && point.x()<=800){
            point.setX(point.x()-40);
        }
        break;
    }
    repaint();
}


