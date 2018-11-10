#include "game.h"
#include <vector>
#include "player.h"
#include "object.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <QDebug>


using namespace std;



vector<Building*> Game::getBuildings(){
    return buildings;
}

vector<Terrain*> Game::getTerrains(){
    return terrains;
}

int Game::defenseType(int y){
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

Player Game::getPlayer(int p){
    return players[p];
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
                switch (y){

                    case 34:{
                        City* city = new City(20*i,20*j);
                        buildings.push_back(city);
                        break;}
                    case 35:{
                        Factory* factory = new Factory(20*i,20*j);
                        buildings.push_back(factory);
                        break;}
                    case 36:{
                        Airport* airport = new Airport(20*i,20*j);
                        buildings.push_back(airport);
                        break;}
                    case 92:{
                    cout<<1;
                        Factory* factory = new Factory(20*i,20*j);
                        players[0].setTerrain(factory);
                        break;}

                    case 123:{
                        Factory* factory = new Factory(20*i,20*j);
                        players[1].setTerrain(factory);
                        break;}
                    default:{
                        int r = defenseType(y);
                        Terrain* terrain = new Terrain(20*i,20*j,y,r);
                        terrains.push_back(terrain);}
                }
            }
            j++;
        }
    }
}




Game::Game(){
    cout<<"new game"<<endl;
    players[0].setMoney(10000);
    Infantery* infan1 = new Infantery(0,0);
    Bazooka* bazook1 = new Bazooka(20,20);
    players[0].setUnit(infan1);
    players[0].setUnit(bazook1);

    players[1].setMoney(10000);
    Infantery* infan2 = new Infantery(300,300);
    Bazooka* bazook2 = new Bazooka(320,320);
    players[1].setUnit(infan2);
    players[1].setUnit(bazook2);

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

    delete this;
}


