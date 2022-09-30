#pragma once
#include "Trucks.h"
class NormalTrucks :public Trucks
{
	int TruckCap;
	//static double Speed;

public:
	void setTruckCap(int TC);
	int getTruckCap();
	//static void setSpeed(double v);
	//static double getSpeed();


	double NormalTruckUti(Time current);
};

