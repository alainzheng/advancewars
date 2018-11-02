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
    ifstream file(txt);
    cout<<"eroooo"<<endl;
    if(!file){
        cout<<"ereo";
        qWarning() << "file not";
        return;
    }
    else{
        string line;
        int j=0;
        int i;
        while(getline(file,line)){
            cout<<line;
            vector<string> x = split(line,",");
            int v = x.size();
            for(i = 0; i < v; i++){
                int y = std::stoi(x[i]);
                switch (y){
                    case 34: b.push_back(City(i,j));
                        break;
                    case 36: b.push_back(Airport(i,j));
                        break;
                    case 92: b1.push_back(Factory(i,j));
                        break;
                    case 123: b2.push_back(Factory(i,j));
                        break;
                    default: int r = defenseType(y);
                        t.push_back(Terrain(i,j,r,y));
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
    players[0].setUnit(infan1);
    players[1].setMoney(10000);
    Infantery infan2(300,300);
    players[1].setUnit(infan2);

    //generateMap("terrain.txt",terrains,buildings,player1.getBuildings(),player2.getBuildings());

}

Game::~Game(){
    cout<< "end game"<< endl;
    delete this;
}


