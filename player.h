#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "object.h"
using std::vector;
using std::string;

class Player{
    int money = 0;
    vector<Building*> b;
    vector<Unit*> u;
    string name;
public :
    Player();
    ~Player();
    vector<Building*> getBuildings();
    void setMoney(int newMoney);
    int& getMoney();
    vector<Unit*> getUnits();
    void setTerrain(Building *building);
    void setUnit(Unit *unit);

};


#endif // PLAYER_H
