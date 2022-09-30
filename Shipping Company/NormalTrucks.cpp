#include "NormalTrucks.h"
void NormalTrucks::setTruckCap(int TC)
{
	if (TC > 0)
		TruckCap = TC;
}

int NormalTrucks::getTruckCap()
{
	return TruckCap;
}

double NormalTrucks::NormalTruckUti(Time current)
{
	float Uti = 0;
	if (getN() == 0)
		return 0;

	int tSim = current.gethour() + current.getday() * 24;
	Uti =  (getActiveTime() / tSim);
	return Uti;
}
