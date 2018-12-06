#include "game.h"
#include <vector>
#include "player.h"
#include "object.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <QDebug>

using namespace std;



vector<Building*>const& Game::getBuildings(){
    return buildings;
}

vector<Terrain*> Game::getTerrains(){
    return terrains;
}

int Game::defenseType(int y){
    //    ajouter le type de defense en fonction du map type
    return 0;
}

vector<string> Game::split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

Player* Game::getPlayer(int p){
    return &players[p];
}




void Game::generateMap(){

    QFile inputFile(":/images/PngAdvancedWar/terrain.txt");
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       int j = 0;
       for(int j = 0;!in.atEnd();j++){
          QString qline = in.readLine();
          string line = qline.toStdString();
          vector<string> x = split(line,",");
          int v = x.size();
          for(int i = 0; i < v; i++){
              int y = std::stoi(x[i]);
              int r = defenseType(1);
              Terrain* terrain = new Terrain(40*i,40*j,1,r);
              terrains.push_back(terrain);
              switch (y){

                  case 34:{
                      City* city = new City(40*i,40*j);
                      buildings.push_back(city);
                      break;
                  }
                  case 35:{
                      Factory* factory = new Factory(40*i,40*j);
                      buildings.push_back(factory);
                      break;
                  }
                  case 36:{
                      Airport* airport = new Airport(40*i,40*j);
                      buildings.push_back(airport);
                      break;
                  }
                  case 92:{
                      Factory* factory = new Factory(40*i,40*j);
                      players[0].addBuilding(factory);
                      break;
                  }

                  case 123:{
                      Factory* factory = new Factory(40*i,40*j);
                      players[1].addBuilding(factory);
                      break;
                  }
                  default:{
                      int r = defenseType(y);
                      terrains.push_back(new Terrain(40*i,40*j,y,r));
                  }
              }
          }
       }
       inputFile.close();
    }
}

void Game::Combat(Unit *attackingUnit, Unit *defendingUnit){
    defendingUnit->setLifes(defendingUnit->getLifes()-attackingUnit->getDamage());
    /*if (defendingUnit->getLifes()<=0){
        cout<<"unit destroyed"<<endl;
        delete defendingUnit;
    }*/
}




Game::Game(){
    cout<<"new game"<<endl;

    players[0].setMoney(30000);
    Infantry* infan1 = new Infantry(40,80);
    Bazooka* bazook1 = new Bazooka(40,40);
    players[0].addUnit(infan1);
    players[0].addUnit(bazook1);


    players[1].setMoney(30000);
    Infantry* infan2 = new Infantry(240,240);
    Bazooka* bazook2 = new Bazooka(120,120);
    players[1].addUnit(infan2);
    players[1].addUnit(bazook2);

    Airport* airport = new Airport(200,200);
    players[0].addBuilding(airport);

    Airport* airport2 = new Airport(240,240);
    players[1].addBuilding(airport2);

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


