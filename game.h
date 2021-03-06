#ifndef GAME_H
#define GAME_H
#include <vector>
#include <iostream>
#include <string>
#include "object.h"
#include "player.h"


class Game{
    vector<Building*> buildings;
    vector<Terrain*> terrains ;
    Player players[2];
    int damageChart [11][11];
    int terrainChart [7][63];
    int terrainsType [21][17];

public:
    Game(int gameType);

    ~Game();

    Building* getBuildingAtPos(int posX,int posY);

    Building* getBuildingAtPos(int posX,int posY,int player);

    Terrain* getTerrainAtPos(int posX, int posY);

    Unit* getUnitAtPos(int posX, int posY, int player);

    void initialiseDamageChart();

    void initialiseTerrainChart();

    int getTerrainChart(int moveType,int x);

    int getDamageChart(int def,int att);

    void generateMap();

    void Combat(Unit *attackingUnit, Unit *defendingUnit);

    vector<Building*>& getBuildings();

    vector<Terrain*>const& getTerrains();

    vector<string> split(string str, string sep);

    Player* getPlayer(int p);

    int &getTerrainsType(int i, int j);

};

#endif // GAME_H
