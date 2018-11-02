#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
#include "object.h"
#include "player.h"
#

class Game
{
    vector<Building> buildings;
    vector<Terrain> terrains ;
    Player players[2];


public:
    Game();
    ~Game();

    void generateMap(string txt, vector<Terrain>& t, vector<Building>& b, vector<Building>& b1, vector<Building>& b2);
    vector<Building>& getBuildings();
    vector<Terrain>& getTerrains();
    int defenseType(int y);
    vector<string> split(string str, string sep);
    Player* getPlayers();

};

#endif // GAME_H
