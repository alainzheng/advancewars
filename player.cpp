#include "player.h"
#include "object.h"
#include <iostream>
#include <vector>
using std::vector;
using std::string;


Player::Player(){
    std::cout<<"player created"<<std::endl;
}

Player::~Player(){
    std::cout<<"player destroyed"<<std::endl;
}


vector<Building> &Player::getBuildings(){
    return b;
}

void Player::setMoney(int newMoney){
    money = newMoney;
}

int &Player::getMoney(){
    return money;
}

vector<Unit> &Player::getUnits(){
    return u;
}

void Player::setTerrain(Building building){
    b.push_back(building);
}

void Player::setUnit(Unit unit){
    u.push_back(unit);
}


