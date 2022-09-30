#pragma once
#include "PriorityQueue.h"
class Cargo;
#include "Time.h"
class Trucks
{
	double Speed;

	int MaintenceTime;
	int num;//actual journeys covered until now
	double DI;//delivery interval
	Time MT;
	int numj;

	int ID;
	static int count;
	PriorityQueue<Cargo*> Cargos;
	int tDC;
	int N;
public:
	Trucks();    // for the ID for Trucks          
	void setnum(int n);
	int getnum();
	int getid();
	void setnumj(int n);
	int getnumj();
	void setMaintenceTime(int MT);
	int getMaintenceTime();
	void setspeed(double sp);
	double getspeed();
	void setDeliveryInterval();
	void setWTforCargos();
	double getDeliveryInterval();            
	void addCargo(Cargo* c);
	void RemoveCargo(Cargo* c);
	void setMT(Time m);
	Time getMT();
	void settDc(int t);
	int gettDC();
	void setN(int n);
	int getN();
	
	double getActiveTime();
	PriorityQueue<Cargo*>& GetCargos();

};

