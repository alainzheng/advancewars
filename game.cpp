#include "game.h"
#include <vector>
#include "player.h"
#include "object.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <cmath>
using namespace std;



vector<Building*>& Game::getBuildings(){
    return buildings;
}

vector<Terrain*>const& Game::getTerrains(){
    return terrains;
}


vector<string> Game::split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current){
        arr.push_back(current);
        current=strtok(nullptr, sep.c_str());
    }
    return arr;
}

Player* Game::getPlayer(int p){
    return &players[p];
}

int &Game::getTerrainsType(int i, int j){
    return terrainsType[i][j];
}



void Game::generateMap(){

    QFile inputFile(":/images/PngAdvancedWar/terrain.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       for(int j = 0;!in.atEnd();j++){
          QString qline = in.readLine();
          string line = qline.toStdString();
          vector<string> x = split(line,",");
          int v = int(x.size());
          for(int i = 0; i < v; i++){
              int y = std::stoi(x[unsigned(i)]);
              terrainsType[i][j] = y;
              switch (y){
                  case 34:{
                      City* city = new City(40*i,40*j);
                      buildings.push_back(city);
                      City* cit = new City(40*i,40*j);
                      terrains.push_back(cit);
                      break;
                  }
                  case 35:{
                      Factory* factory = new Factory(40*i,40*j);
                      buildings.push_back(factory);
                      Factory* fact = new Factory(40*i,40*j);
                      terrains.push_back(fact);
                      break;
                  }
                  case 36:{
                      Airport* airport = new Airport(40*i,40*j);
                      //buildings.push_back(airport);
                      if(i<5){
                          players[0].addBuilding(airport);
                      }
                      else{
                          players[1].addBuilding(airport);
                      }
                      Airport* air = new Airport(40*i,40*j);
                      terrains.push_back(air);
                      break;
                  }
                  case 92:{
                      Factory* factory = new Factory(40*i,40*j);
                      players[0].addBuilding(factory);
                      Factory* fact = new Factory(40*i,40*j);
                      terrains.push_back(fact);
                      break;
                  }

                  case 123:{
                      Factory* factory = new Factory(40*i,40*j);
                      players[1].addBuilding(factory);
                      Factory* fact = new Factory(40*i,40*j);
                      terrains.push_back(fact);
                      break;
                  }
                  default:{
                      Terrain* terrain = new Terrain(40*i,40*j,y);
                      terrains.push_back(terrain);
                  }
              }
          }
       }
       inputFile.close();
    }
}

void Game::Combat(Unit *attackingUnit, Unit *defendingUnit){
    int px = defendingUnit->getPosX();
    int py = defendingUnit->getPosY();
    int damage=2;
    int def_terr = getTerrainChart(5,terrainsType[px/40][py/40]);
    if(defendingUnit->getMoveType()==4){
        def_terr=0;
    } // problem resolu division tronqué
    damage = int(floor(((damageChart[defendingUnit->getType()][attackingUnit->getType()] * (attackingUnit->getLifes()) * (100 - def_terr * defendingUnit->getLifes())+5000)/10000)));
    cout<<damageChart[defendingUnit->getType()][attackingUnit->getType()]<<endl;
    cout<<"att : "<< attackingUnit->getLifes() <<endl;
    cout<<"def : "<< defendingUnit->getLifes() <<endl;
    cout<< (100-def_terr*defendingUnit->getLifes()) << endl;
    cout<< (damageChart[defendingUnit->getType()][attackingUnit->getType()] * (attackingUnit->getLifes()) * (100 - def_terr * defendingUnit->getLifes()))<<endl;
    defendingUnit->setLifes(defendingUnit->getLifes() - damage);
    cout<<"damage equals "<< damage<<endl;
}


void Game::initialiseDamageChart(){
    QFile inputFile(":/PngAdvancedWar/damage.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       for(int j = 0;!in.atEnd();j++){
          QString qline = in.readLine();
          string line = qline.toStdString();
          vector<string> x = split(line,",");
          int v = int(x.size());
          for(int i = 0; i < v; i++){
            int y = std::stoi(x[unsigned(i)]);
            damageChart[i][j] = y;
          }
       }
       inputFile.close();
    }
}

void Game::initialiseTerrainChart(){
    QFile inputFile(":/PngAdvancedWar/terrainchart.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       for(int j = 0;!in.atEnd();j++){
          QString qline = in.readLine();
          string line = qline.toStdString();
          vector<string> x = split(line,",");
          int v = int(x.size());
          for(int i = 0; i < v; i++){
            int y = std::stoi(x[unsigned(i)]);
            terrainChart[i][j] = y;
          }
       }
       inputFile.close();
    }
}

int Game::getTerrainChart(int moveType,int x){
    if(x>100){
        return terrainChart[moveType+1][x-54];
    }
    else{
        return terrainChart[moveType+1][x-1];
    }
}

int Game::getDamageChart(int def,int att){
    return damageChart[def][att];
}

Game::Game(int gameType){
        cout<<"new game"<<endl;

    if(gameType==0){
        players[0].setMoney(10000);
        Infantry* infan1 = new Infantry(40,560);
        Bazooka* bazook1 = new Bazooka(80,600);
        players[0].addUnit(infan1);
        players[0].addUnit(bazook1);


        players[1].setMoney(10000);
        Infantry* infan2 = new Infantry(120,440);
        Bazooka* bazook2 = new Bazooka(160,400);
        players[1].addUnit(infan2);
        players[1].addUnit(bazook2);

    }
    else if(gameType==1){//ia pathfind

        players[0].setMoney(5000);
        Building* build = new City(760,40);
        buildings.push_back(build);

        players[1].setMoney(2000);
        Infantry* infan2 = new Infantry(0,600);
        players[1].addUnit(infan2);
    }

    else if(gameType==2){//ia pathfind

        players[0].setMoney(5000);

        players[1].setMoney(7000);
        Infantry* infan1 = new Infantry(0,600);
        Infantry* infan2 = new Infantry(40,600);
        Infantry* infan3 = new Infantry(80,600);
        Infantry* infan4 = new Infantry(0,560);
        Infantry* infan5 = new Infantry(40,560);
        Infantry* infan6 = new Infantry(0,520);
        players[1].addUnit(infan1);
        players[1].addUnit(infan2);
        players[1].addUnit(infan3);
        players[1].addUnit(infan4);
        players[1].addUnit(infan5);
        players[1].addUnit(infan6);

    }
    initialiseDamageChart();
    initialiseTerrainChart();
    generateMap();
}



Game::~Game(){
    cout<< "end game"<< endl;
    for (int p=0; p<2;p++){
        for (Building* building : players[p].getBuildings()){
            delete building;
        }
    }
    for (int p=0; p<2;p++){
        for (Unit* unit : players[p].getUnits()){
            delete unit;
        }
    }
    for (Building* building : getBuildings()){
        delete building;
    }
    for (Terrain* terrain : getTerrains()){
        delete terrain;
    }
}


Building *Game::getBuildingAtPos(int posX, int posY){
    Building* build = nullptr;
    for(Building* building : buildings){
        if (building->getPosX()==posX && building->getPosY()==posY){
            build = building;
            break;
        }
    }
    return build;
}

Building *Game::getBuildingAtPos(int posX, int posY, int player){
    Building* build = nullptr;
    for(Building* building : getPlayer(player)->getBuildings()){
        if (building->getPosX()==posX && building->getPosY()==posY){
            build = building;
            break;
        }
    }
    return build;
}

Terrain *Game::getTerrainAtPos(int posX, int posY){
    Terrain* terr = nullptr;
    for(int p = 0; p<2;p++){
        for(Terrain* terrain : terrains){
            if (terrain->getPosX()==posX && terrain->getPosY()==posY){
                terr = terrain;
                break;
            }
        }
    }
    return terr;
}

Unit *Game::getUnitAtPos(int posX, int posY, int player){
    Unit* uni = nullptr;
    for(Unit* unit : getPlayer(player)->getUnits()){
        if(unit->getPosX()==posX && unit->getPosY()==posY){
            uni = unit;
            break;
        }
    }
    return uni;
}



