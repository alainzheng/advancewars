#include "game.h"
#include <vector>
#include "player.h"
#include "object.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <QDebug>


using namespace std;



vector<Building> &Game::getBuildings(){
    return buildings;
}

vector<Terrain> &Game::getTerrains(){
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

Player *Game::getPlayers(){
    return players;
}




void Game::generateMap(string txt,vector<Terrain>& t,vector<Building>& b,vector<Building>& b1,vector<Building>& b2){
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
                    case 34: b.push_back(City(20*i,20*j));
                        break;
                    case 36: b.push_back(Airport(20*i,20*j));
                        break;
                    case 92: b1.push_back(Factory(20*i,20*j));
                        break;
                    case 123: b2.push_back(Factory(20*i,20*j));
                        break;
                    default: int r = defenseType(y);
                        t.push_back(Terrain(20*i,20*j,r,y));

                /*                    case 34:
                        City *city = new City(20*i,20*j);
                        b.push_back(city);
                        break;
                    case 36:
                        Airport *airport = new Airport(20*i,20*j);
                        b.push_back(airport);
                        break;
                    case 92:
                        Factory *factory = new Factory(20*i,20*j);
                        b1.push_back(factory);
                        break;
                    case 123:
                        Factory *factory2 = new Factory(20*i,20*j);
                        b2.push_back(factory2);
                        break;
                    default:
                        int r = defenseType(y);
                        Terrain *terrain = new Terrain(20*i,20*j,r,y);
                        t.push_back(terrain);*/

                }
            }
            j++;
        }
    }
}




Game::Game(){
    cout<<"new game"<<endl;
    players[0].setMoney(10000);
    Infantery infan1(0,0);
    Bazooka bazook1(20,20);
    players[0].setUnit(infan1);
    players[0].setUnit(bazook1);
    players[1].setMoney(10000);
    Infantery infan2(300,300);
    Bazooka bazook2(320,320);
    players[1].setUnit(infan2);
    players[1].setUnit(bazook2);


    generateMap("terrain.txt",terrains,buildings,players[0].getBuildings(),players[1].getBuildings());

}

Game::~Game(){
    cout<< "end game"<< endl;
    delete this;
}


