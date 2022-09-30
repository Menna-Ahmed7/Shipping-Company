#include "SpecialTrucks.h"
void SpecialTrucks::setTruckCap(int TC)
{
	if (TC > 0)
		TruckCap = TC;
}

int SpecialTrucks::getTruckCap()
{
	return TruckCap;
}

double SpecialTrucks::SpecialTruckUti(Time current)
{
	double Uti = 0;
	if (getN() == 0)
		return 0;
	int tSim = current.gethour() + current.getday() * 24;
	Uti = (getActiveTime() / tSim);
	return Uti;
}
