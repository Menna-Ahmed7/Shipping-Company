#pragma once

#include "Trucks.h"
class VIPTrucks :public Trucks
{
	int TruckCap;
	//static double Speed;
public:
	void setTruckCap(int TC);
	int getTruckCap();
	//static void setSpeed(double v);
	//static double getSpeed();
	double VIPTruckUti(Time current);

};

