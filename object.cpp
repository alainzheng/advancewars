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

Object::~Object(){
    cout<<"object end"<<endl;
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


//////////////////  TERRAIN ////////////////

Terrain::Terrain(int x, int y, int typeInit, int defenseInit) : Object(x,y,typeInit) {
    defense = defenseInit;
    this->type = typeInit;
}

int Terrain::getDefense()
{return defense; }

Building::Building(int x, int y, int typeInit, int defenseInit) : Terrain(x,y, typeInit, defenseInit){
    cout <<"Construction d'un bâtiment ";
    this->type = typeInit;
}

City::City(int x, int y) : Building(x, y, 34, 3){
    cout <<"ville"<< endl;
    this->type = 34;
    cost=20;
}

void City::resetCost()
{cost=20; }

void City::removeCost(int x)
{cost=cost-x; }

Factory::Factory(int x, int y) : Building(x, y, 35, 3) {
    this->type = 35;
    cout <<"usine"<< endl;
}

Airport::Airport(int x, int y) : Building(x, y, 36, 3) {
    this->type = 36;
    cout <<"aéroport"<< endl;
}

/////////////////  UNIT ///////////////////


Unit::Unit(int x, int y, int costInit, int type) : Object(x,y,type){
    cout << "Construction d'une unité ";
    cost= costInit;
    lifes = 10;
    deplacement=3;
    this->type = type;
    name = "";
}

int Unit::getLifes()
{ return lifes; }

int Unit::getCost()
{ return cost; }

string Unit::getName(){
    return name;
}

void Unit::setName(string nameInit){
    this->name = nameInit;
}

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

void Unit::setMoved(bool movedState){
    moved = movedState;
}

bool Unit::getMoved(){
    return moved;
}

void Unit::reset() {
    deplacement=0;
}


Infantery::Infantery(int x, int y) : Unit(x,y,1000) {
    deplacement=3;
    cout <<"d'infanterie"<< endl;
    this->type = 0;
    setName("Infantry");

}

Bazooka::Bazooka(int x, int y) : Unit(x,y,3000) {
    deplacement=5;
    this->type = 1;
    setName("Bazooka");
    cout <<"bazooka"<< endl;
}

Recon::Recon(int x, int y) : Unit(x,y,4000) {
    this->type = 2;
    setName("Recon");
    cout <<"de reconnaissance"<< endl;
}

AntiAir::AntiAir(int x, int y) : Unit(x,y,8000) {
    this->type = 3;
    setName("AntiAir");
    cout <<"anti-aérienne"<< endl;
}

Tank::Tank(int x, int y) : Unit(x,y,7000) {
    this->type = 4;
    setName("Tank");
    cout <<"tank"<< endl;
}

MdTank::MdTank(int x, int y) : Unit(x,y,16000) {
    this->type = 5;
    setName("MdTank");
    cout <<"Md.tank"<< endl;
}

MegaTank::MegaTank(int x, int y) : Unit(x,y,28000) {
    this->type = 6;
    setName("MegaTank");
    cout <<"mega tank"<< endl;
}

NeoTank::NeoTank(int x, int y) : Unit(x,y,22000) {
    this->type = 7;
    setName("NeoTank");
    cout <<"neotank"<< endl;
}

BCopter::BCopter(int x, int y) : Unit(x,y,9000) {
    this->type = 8;
    setName("BCopter");
    cout <<"b-copter"<< endl;
}

Fighter::Fighter(int x, int y) : Unit(x,y,20000) {
    this->type = 9;
    setName("Fighter");
    cout <<"fighter"<< endl;
}

Bomber::Bomber(int x, int y) : Unit(x,y,22000) {
    this->type = 10;
    setName("Bomber");
    cout <<"bombardeur"<< endl;
}
