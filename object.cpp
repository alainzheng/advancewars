#include "object.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

Object::Object(int x, int y, int typeInit){
    posX = x;
    posY = y;
    type = typeInit;
}


int Object::getPosX(){
    return posX;
}

int Object::getPosY(){
    return posY;
}

int Object::getType(){
    return type;
}

void Object::setPosX(int newPosX){
    this->posX = newPosX;
}

void Object::setPosY(int newPosY){
    this->posY=newPosY;
}

bool Object::getSelected(){
    return isSelected;
}

void Object::setSelected(bool selectState){
    this->isSelected = selectState;
}


//////////////////  TERRAIN ////////////////

Terrain::Terrain(int x, int y, int typeInit, int defenseInit) : Object(x,y,typeInit) {
    defense = defenseInit;
}

int Terrain::getDefense()
{return defense; }

Building::Building(int x, int y, int typeInit, int defenseInit) : Terrain(x,y, typeInit, defenseInit){
    cout <<"Construction d'un bâtiment ";
}

City::City(int x, int y) : Building(x, y, 1, 3){
    cout <<"ville"<< endl;
    cost=20;
}

void City::resetCost()
{cost=20; }

void City::removeCost(int x)
{cost=cost-x; }

Factory::Factory(int x, int y) : Building(x, y, 2, 3) {
    cout <<"usine"<< endl;
}

Airport::Airport(int x, int y) : Building(x, y, 3, 3) {
    cout <<"aéroport"<< endl;
}

/////////////////  UNIT ///////////////////


Unit::Unit(int x, int y, int costInit, int type) : Object(x,y,type){
    cout << "Construction d'une unité ";
    cost= costInit;
    lifes = 10;
    deplacement=3;
}

int Unit::getLifes()
{ return lifes; }

int Unit::getCost()
{ return cost; }

void Unit::setLifes(int newLifes)
{ lifes = newLifes; }

void Unit::raiseLife(int addLifes)
{lifes+=addLifes; }

void Unit::move(int depX, int depY){
    this->posX+=depX;
    this->posY+=depY;

}

int Unit::getDeplacement(){
    return deplacement;
}

void Unit::reset() {
    deplacement=0;
}


Infantery::Infantery(int x, int y) : Unit(x,y,1000) {
    deplacement=5;
    cout <<"d'infanterie"<< endl;
}

Bazooka::Bazooka(int x, int y) : Unit(x,y,3000) {
    deplacement=4;
    cout <<"bazooka"<< endl;
}

Recon::Recon(int x, int y) : Unit(x,y,4000) {
    cout <<"de reconnaissance"<< endl;
}

AntiAir::AntiAir(int x, int y) : Unit(x,y,8000) {
    cout <<"anti-aérienne"<< endl;
}

Tank::Tank(int x, int y) : Unit(x,y,7000) {
    cout <<"tank"<< endl;
}

MdTank::MdTank(int x, int y) : Unit(x,y,16000) {
    cout <<"Md.tank"<< endl;
}

MegaTank::MegaTank(int x, int y) : Unit(x,y,28000) {
    cout <<"mega tank"<< endl;
}

Neotank::Neotank(int x, int y) : Unit(x,y,22000) {
    cout <<"neotank"<< endl;
}

BCopter::BCopter(int x, int y) : Unit(x,y,9000) {
    cout <<"b-copter"<< endl;
}

Fighter::Fighter(int x, int y) : Unit(x,y,20000) {
    cout <<"fighter"<< endl;
}

Bomber::Bomber(int x, int y) : Unit(x,y,22000) {
    cout <<"bombardeur"<< endl;
}
