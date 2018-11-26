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
    ifstream file("terrain.txt");

    if(!file){
        qWarning() << "file not";
        return;
    }
    else{
        string line;
        int j = 0;
        while(getline(file,line)){
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
                    cout<<1;
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
                        Terrain* terrain = new Terrain(40*i,40*j,y,r);
                        terrains.push_back(terrain);
                    }
                }
            }
            j++;
        }
    }
}




Game::Game(){
    cout<<"new game"<<endl;

    Infantery* infan1 = new Infantery(0,0);
    Bazooka* bazook1 = new Bazooka(40,40);
    players[0].addUnit(infan1);
    players[0].addUnit(bazook1);
    players[0].setMoney(10000);

    Infantery* infan2 = new Infantery(400,400);
    Bazooka* bazook2 = new Bazooka(320,320);
    players[1].addUnit(infan2);
    players[1].addUnit(bazook2);
    players[1].setMoney(10000);
    generateMap();
}

Game::~Game(){
    cout<< "end game"<< endl;
    for (int p=0; p<2;p++){
        for (int i = 0; players[p].getBuildings().size()<i;){
            delete players[p].getBuildings()[i];
        }
    }
    for (int i = 0;getBuildings().size()<i;){
        delete getBuildings()[i];
    }
    for (int i = 0;getTerrains().size()<i;){
        delete getBuildings()[i];
    }
}


