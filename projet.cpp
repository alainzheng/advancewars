#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

class Object{
protected:
	int posx;
	int posy;
	int type;
public:
	Object( int x, int y, int typeInit){
		posx=x;
		posy=y;
		type=typeInit;
	}
	
	int getposx(){
		return posx; 
	}
		
	int getposy(){ 
		return posy; 
	}
	
	int gettype()
		{return type; }
};

class Unit : Object{
	
	int cost;
	int lifes;
protected:
	int deplacement;
public:
	Unit(int x, int y, int type, int costInit) : Object(x,y,type){
		cout <<"Construction d'une unité ";
		cost= costInit;
		lifes = 10;
		deplacement=2;
	}
	
	int getlifes()
		{ return lifes; }
			
	int getcost()
		{ return cost; }
		
	void setlifes(int newLifes)
		{ lifes = newLifes; }

	void raiselife(int addlifes)
		{lifes+=addlifes; }
	
	void move(int x, int y){
		posx+=x;
		posy+=y;
		deplacement+=1;
	}
	
	void reset() {
		deplacement=0;
	}

};

/*           $$$$$$$     TERRAIN    $$$$$$$$$$        */


class Terrain : Object{
	
	int defense;

public: 
	Terrain(int x, int y, int typeInit, int defenseInit) : Object(x,y,typeInit) {
		defense = defenseInit;
	}
	
	int getdefense()
		{return defense; }
	

};

class Building : public Terrain {
	
public:
	Building(int x, int y, int typeInit, int defenseInit) : Terrain(x,y, typeInit, defenseInit){
		cout <<"Construction d'un bâtiment ";
	}
};

class City : public Building {
	int cost;
public: 
	City(int x, int y) : Building(x, y, 1, 3){
		cout <<"ville"<< endl;
		cost=20;
	}
	
	void resetcost()
		{cost=20; }
	
	void removecost(int x)
			{cost=cost-x; }

};

class Factory : public Building {
public: 
	Factory(int x, int y) : Building(x, y, 2, 3) {
		cout <<"usine"<< endl;
	}

};

class Airport : public Building {
public: 
	Airport(int x, int y) : Building(x, y, 3, 3) {
		cout <<"aéroport"<< endl;
	}

};



/*      $$$$$$$$        LES UNITTTTTTTS    $$$$$$$$          */
 
 
 
class Infantery : public Unit {
public:	
	Infantery(int x, int y) : Unit(x,y,1,1000) {
		cout <<"d'infanterie"<< endl;
	}
	
};

class Bazooka : public Unit {
public:	
	Bazooka(int x, int y) : Unit(x,y,2,3000) {
		cout <<"bazooka"<< endl;
	}
	
};

class Recon : public Unit {
public:	
	Recon(int x, int y) : Unit(x,y,3,4000) {
		cout <<"de reconnaissance"<< endl;
	}
};

class AntiAir : public Unit {
public:	
	AntiAir(int x, int y) : Unit(x,y,4,8000) {
		cout <<"anti-aérienne"<< endl;
	}
};

class Tank : public Unit {
public:	
	Tank(int x, int y) : Unit(x,y,5,7000) {
		cout <<"tank"<< endl;
	}
};

class MdTank : public Unit {
public:	
	MdTank(int x, int y) : Unit(x,y,6,16000) {
		cout <<"Md.tank"<< endl;
	}
};

class MegaTank : public Unit {
public:	
	MegaTank(int x, int y) : Unit(x,y,7,28000) {
		cout <<"mega tank"<< endl;
	}
};

class Neotank : public Unit {
public:	
	Neotank(int x, int y) : Unit(x,y,8,22000) {
		cout <<"neotank"<< endl;
	}
};

class BCopter : public Unit {
public:	
	BCopter(int x, int y) : Unit(x,y,10,9000) {
		cout <<"b-copter"<< endl;
	}
};

class Fighter : public Unit {
public:	
	Fighter(int x, int y) : Unit(x,y,9,20000) {
		cout <<"fighter"<< endl;
	}
};

class Bomber : public Unit {
public:	
	Bomber(int x, int y) : Unit(x,y,11,22000) {
		cout <<"bombardeur"<< endl;
	}
};


// fonction qui separe en virgule

vector<string> split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
};

class Player {
	int money;
	vector<Building> b;
	vector<Unit> u;
public : 
	Player(int moneyInit){
		money=moneyInit;
	}
	
	vector<Building>& getBuildings(){
		return b;
	}
	
	int& getMoney(){
		return money;
	}
	
	vector<Unit>& getUnits(){
		return u;
	}
	
};

class Game {
	int caseX;
	int caseY;
	vector<Terrain> t;
	vector<Building> b;
	
public: 
	Game(){
		caseX=0;
		caseY=0;
	}
	
	vector<Terrain>& getTerrain(){
		return t;
	}
	
	vector<Building>& getBuildings(){
		return b;
	}
	
	int& getcasex(){
		return caseX;
	}
	
	int& getcasey(){
		return caseY;
	}
};

int defenseType(int y){
	return 0;
};

void generateMap(string txt,vector<Terrain>& t,vector<Building>& b,vector<Building>& b1,vector<Building>& b2){
	ifstream file(txt.c_str());
	string line;
	int i;
	int j=0;
	
	while(getline(file,line)){
		vector<string> x = split(line,",");
		int v = x.size();
		
		for(i=0;i < v;i++){
			int y = std::stoi(x[i]);
			switch (y){
				case 34: b.push_back(City(i,j));
					break;
				case 36: b.push_back(Airport(i,j));
					break;
				case 92: b1.push_back(Factory(i,j));
					break;
				case 123: b2.push_back(Factory(i,j));
					break;
				default: int r = defenseType(y);
					t.push_back(Terrain(i,j,r,y));
			}
		} 
		j++;
	}
};



int main(){
	Player player1=Player(10000);
	Player player2=Player(10000);
	Game g;
	generatemap("terrain.txt",g.getTerrain(),g.getBuildings(),player1.getBuildings(),player2.getBuildings());
	Player& tour = player1;
	cout<< "hello world "<< &player1 << " " <<&tour<<endl;
	
	
	//for(i=0;i<a.size();i++){
//		if(a[i].getposx()==x || a[i].getposy()==y){
//			result=a[i];
//			break;
			
//		}
//}	
//Player& tour, Player& other, int& x, int& y
//int i; 
//vector<Unit>& a= tour.getunits();
//player1, player2, g.getcasex(), g.getcasey());
	
	//players dans game?
	
	return 0;
};

