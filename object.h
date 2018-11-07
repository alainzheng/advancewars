#ifndef OBJECT_H
#define OBJECT_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <QKeyEvent>
#include <QGraphicsItem>

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



///////////////// TERRAIN  ///////////////


class Terrain : public Object{

    int defense;

public:
    Terrain(int x, int y, int typeInit, int defenseInit);

    int getDefense();


};




class Building : public Terrain {

public:
    Building(int x, int y, int typeInit, int defenseInit);
};




class City : public Building {
    int cost;
public:
    City(int x, int y);

    void resetCost();

    void removeCost(int x);

};

class Factory : public Building {
public:
    Factory(int x, int y);

};

class Airport : public Building {
public:
    Airport(int x, int y);

};


////////////////////   UNIT     ////////////////

class Unit : public Object{

    int cost;
    int lifes;
    bool moved = false;
protected:
    int deplacement;
public:
    Unit(int x, int y, int costInit, int type = 0);

    int getLifes();

    int getCost();

    void setLifes(int newLifes);

    void raiseLife(int addLifes);

    void move(int depX, int depY);

    int getDeplacement();

    void setMoved(bool movedState);

    bool getMoved();
    void reset();

};


class Infantery : public Unit {
public:
    Infantery(int x, int y);


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

class Neotank : public Unit {
public:
    Neotank(int x, int y);
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

#endif // OBJECT_H
