#ifndef OBJECT_H
#define OBJECT_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <string.h>


class Object{
protected:
    int posX;
    int posY;
    int type;



public:
    Object(int x , int y , int typeInit );
    ~Object();
    int getPosX();

    int getPosY();

    int getType();

    void setPosX(int newPosX);

    void setPosY(int newPosY);


};




////////////////////   UNIT     ////////////////

class Unit : public Object{

    int cost;
    int lifes; 

    bool moved = false;
    bool attacked = false;
    bool captureState = false;

    std::string name;

protected:
    int deplacement;
    int moveType;
public:

    Unit(int x, int y, int costInit, int type = 0);

    int getLifes();

    int getCost();

    bool getCaptureState();

    void setCaptureState(bool capture);
    std::string getName();

    void setName(std::string nameInit);

    void setLifes(int newLifes);

    void raiseLife(int addLifes);

    void move(int depX, int depY);

    int getDeplacement();

    void setHasMoved(bool movedState);

    bool getHasMoved();

    void setHasActed(bool attackedState);

    bool getHasActed();

    int getMoveType();

    void reset();

};


class Infantry : public Unit {
public:
    Infantry(int x, int y);


};

class Bazooka : public Unit {
public:
    Bazooka(int x, int y);

};

class Recon : public Unit {
public:
    Recon(int x, int y);
};

class AntiAir : public Unit {
public:
    AntiAir(int x, int y);
};

class Tank : public Unit {
public:
    Tank(int x, int y);
};

class MdTank : public Unit {
public:
    MdTank(int x, int y);
};

class MegaTank : public Unit {
public:
    MegaTank(int x, int y);
};

class NeoTank : public Unit {
public:
    NeoTank(int x, int y);
};

class BCopter : public Unit {
public:
    BCopter(int x, int y);
};

class Fighter : public Unit {
public:
    Fighter(int x, int y);
};

class Bomber : public Unit {
public:
    Bomber(int x, int y);
};



///////////////// TERRAIN  ///////////////


class Terrain : public Object{

    int defense;
    bool isCase = false;
    int movePoints = 0;

public:
    Terrain(int x, int y, int typeInit, int defenseInit);

    int getDefense();

    void setIsCase(bool isPossCase){
        isCase = isPossCase;
    }
    bool getIsCase(){
        return isCase;
    }
    void setMovePoints(int mp){
        movePoints = mp;
    }
    int getMovePoints(){
        return movePoints;
    }
};




class Building : public Terrain {
protected:
    bool hasMadeUnit = false;
public:
    Building(int x, int y, int typeInit, int defenseInit);
    virtual ~Building();
    void setHasMadeUnit(bool unitMade);
    bool getHasMadeUnit();
};




class City : public Building {
    int cost;
public:
    City(int x, int y);

    int getCost();

    void setCost(int x);

};

class Factory : public Building {
public:
    Factory(int x, int y);
    Unit* createNewUnit(std::string unitName);

};

class Airport : public Building {
public:
    Airport(int x, int y);
    Unit* createNewUnit(std::string unitName);
};

#endif // OBJECT_H
