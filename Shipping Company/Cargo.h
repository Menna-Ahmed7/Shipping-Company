#pragma once
#include "Time.h"
#include<iostream>
class Trucks;
class Cargo
{
	Time PT;
	Time WT;
	Time MT;
	int Loadtime;
	double DeliveryDist;
	int ID;
	double Cost;
	Trucks* p;
	int constloadt;
public:
	// same implementation ,correct not pure virtual
	void setPT(Time p);
	Time getPT();
	void setcMT(Time m);
	Time getcMT();
	void setWT(Time w);
	Time getWT();
	void setLoadt(int l);
	int getLoadt();
	void setconstLoadt(int l);
	int getconstLoadt();
	void setDeliveryDist(double d);
	double getDeliveryDist();
	void setCost(double c);
	double getCost();
	void setid(int i);
	int getid();
	void SetTruck(Trucks* T);
	Trucks* GetTruck();
	Time GetCDT();
	int getPriorityCDT();
////The input and output files , a function should be added here
	virtual ~Cargo();
};

