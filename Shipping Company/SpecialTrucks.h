#pragma once
#include "Trucks.h"
class SpecialTrucks :public Trucks
{
	int TruckCap;
	//static double Speed;
public:
	void setTruckCap(int TC);
	int getTruckCap();
	//static void setSpeed(double v);
	//static double getSpeed();
	double SpecialTruckUti(Time current);
};

