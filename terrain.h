#ifndef TERRAIN_H
#define TERRAIN_H
#include "object.h"
#include <iostream>
using namespace std;



class Terrain : Object{

    int defense;

public:
    Terrain(int x, int y, int typeInit, int defenseInit) : Object(x,y,typeInit) {
        defense = defenseInit;
    }

    int getDefense()
        {return defense; }


};

class Building : public Terrain {

public:
    Building(int x, int y, int typeInit, int defenseInit) : Terrain(x,y, typeInit, defenseInit){
        cout <<"Construction d'un bâtiment ";
    }
};

class City : public Building {
    int cost;
public:
    City(int x, int y) : Building(x, y, 1, 3){
        cout <<"ville"<< endl;
        cost=20;
    }

    void resetCost()
        {cost=20; }

    void removeCost(int x)
            {cost=cost-x; }

};

class Factory : public Building {
public:
    Factory(int x, int y) : Building(x, y, 2, 3) {
        cout <<"usine"<< endl;
    }

};

class Airport : public Building {
public:
    Airport(int x, int y) : Building(x, y, 3, 3) {
        cout <<"aéroport"<< endl;
    }

};


#endif // TERRAIN_H
