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
    int terrainChart [6][63];
    int terrainsDef [21][17];

public:
    Game();
    ~Game();


    Building* getBuildingAtPos(int posX,int posY){
        Building* build = nullptr;
        for(Building* building : buildings){
            if (building->getPosX()==posX && building->getPosY()==posY){
                build = building;
                break;
            }
        }
        return build;
    }

    Building* getBuildingAtPos(int posX,int posY,int player){
        Building* build = nullptr;
        for(Building* building : getPlayer(player)->getBuildings()){
            if (building->getPosX()==posX && building->getPosY()==posY){
                build = building;
                break;
            }
        }
        return build;
    }
    Terrain* getTerrainAtPos(int posX, int posY){
        Terrain* terr = nullptr;
        for(int p = 0; p<2;p++){
            for(Terrain* terrain : terrains){
                if (terrain->getPosX()==posX && terrain->getPosY()==posY){
                    terr = terrain;
                    break;
                }
            }
        }
        return terr;
    }
    Unit* getUnitAtPos(int posX, int posY, int player){
        Unit* uni = nullptr;
        for(Unit* unit : getPlayer(player)->getUnits()){
            if(unit->getPosX()==posX && unit->getPosY()==posY){
                uni = unit;
                break;
            }
        }
        return uni;
    }
    void initialiseDamageChart();
    void initialiseTerrainChart();
    void generateMap();
    void Combat(Unit *attackingUnit, Unit *defendingUnit);
    vector<Building*>& getBuildings();
    vector<Terrain*>const& getTerrains();
    int defenseType(int y);
    vector<string> split(string str, string sep);
    Player* getPlayer(int p);
    int &getTerrainsDef(int i, int j);



};

#endif // GAME_H
