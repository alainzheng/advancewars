#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
#include "object.h"
#include "player.h"


class Game
{
    vector<Building*> buildings;
    vector<Terrain*> terrains ;
    Player players[2];
    int damageChart [11][11];

public:
    Game();
    ~Game();

    void initialiseDamageChart();
    void generateMap();
    void Combat(Unit *attackingUnit, Unit *defendingUnit);
    vector<Building*>& getBuildings();
    vector<Terrain*>const& getTerrains();
    int defenseType(int y);
    vector<string> split(string str, string sep);
    Player* getPlayer(int p);

};

#endif // GAME_H
