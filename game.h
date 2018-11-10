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


public:
    Game();
    ~Game();

    void generateMap();
    vector<Building*> getBuildings();
    vector<Terrain*> getTerrains();
    int defenseType(int y);
    vector<string> split(string str, string sep);
    Player getPlayer(int p);

};

#endif // GAME_H
