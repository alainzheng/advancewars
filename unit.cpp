#include "unit.h"
#include <iostream>


using namespace std;


class Unit : Object{

    int cost;
    int lifes;
protected:
    int deplacement;
public:
    Unit(int x, int y, int costInit, int type = 0) : Object(x,y,type){
        cout <<"Construction d'une unité ";
        cost= costInit;
        lifes = 10;
        deplacement=2;
    }

    int getLifes()
        { return lifes; }

    int getCost()
        { return cost; }

    void setLifes(int newLifes)
        { lifes = newLifes; }

    void raiseLife(int addLifes)
        {lifes+=addLifes; }

    void move(int x, int y){
        posX+=x;
        posY+=y;
        deplacement+=1;
    }

    void reset() {
        deplacement=0;
    }

};


class Infantery : public Unit {
public:
    Infantery(int x, int y) : Unit(x,y,1000) {
        cout <<"d'infanterie"<< endl;
    }

};

class Bazooka : public Unit {
public:
    Bazooka(int x, int y) : Unit(x,y,3000) {
        cout <<"bazooka"<< endl;
    }

};

class Recon : public Unit {
public:
    Recon(int x, int y) : Unit(x,y,4000) {
        cout <<"de reconnaissance"<< endl;
    }
};

class AntiAir : public Unit {
public:
    AntiAir(int x, int y) : Unit(x,y,8000) {
        cout <<"anti-aérienne"<< endl;
    }
};

class Tank : public Unit {
public:
    Tank(int x, int y) : Unit(x,y,7000) {
        cout <<"tank"<< endl;
    }
};

class MdTank : public Unit {
public:
    MdTank(int x, int y) : Unit(x,y,16000) {
        cout <<"Md.tank"<< endl;
    }
};

class MegaTank : public Unit {
public:
    MegaTank(int x, int y) : Unit(x,y,28000) {
        cout <<"mega tank"<< endl;
    }
};

class Neotank : public Unit {
public:
    Neotank(int x, int y) : Unit(x,y,22000) {
        cout <<"neotank"<< endl;
    }
};

class BCopter : public Unit {
public:
    BCopter(int x, int y) : Unit(x,y,9000) {
        cout <<"b-copter"<< endl;
    }
};

class Fighter : public Unit {
public:
    Fighter(int x, int y) : Unit(x,y,20000) {
        cout <<"fighter"<< endl;
    }
};

class Bomber : public Unit {
public:
    Bomber(int x, int y) : Unit(x,y,22000) {
        cout <<"bombardeur"<< endl;
    }
};
