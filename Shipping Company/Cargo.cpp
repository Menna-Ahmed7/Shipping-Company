
#include "Cargo.h"
#include"Trucks.h"


//TODO 











void Cargo::setid(int i)
{
	if (i > 0)
		ID = i;


}

int Cargo::getid()
{
	return ID;
}


void Cargo::setPT(Time p)
{

	PT.setday(p.getday());
	PT.sethour(p.gethour());

}

Time Cargo::getPT()
{
	return PT;
}

void Cargo::setcMT(Time m)
{
	MT.setday(m.getday());
	MT.sethour(m.gethour());
}

Time Cargo::getcMT()
{
	return MT;
}

void Cargo::setWT(Time w)
{
	WT.setday(w.getday());
	WT.sethour(w.gethour());
}

void Cargo::setLoadt(int l)
{
	if (l > 0)
		Loadtime = l;
}

int Cargo::getLoadt()
{
	return Loadtime;
}

void Cargo::setconstLoadt(int l)
{
	constloadt = l;
}

int Cargo::getconstLoadt()
{
	return constloadt;
}

void Cargo::setDeliveryDist(double d)
{
	if (d > 0)
		DeliveryDist = d;
}

double Cargo::getDeliveryDist()
{
	return DeliveryDist;
}

void Cargo::setCost(double c)
{
	if (c > 0)
		Cost = c;
}

double Cargo::getCost()
{
	return Cost;
}

void Cargo::SetTruck(Trucks* T)
{
	if (T)
		p = T;
}

Trucks* Cargo::GetTruck()
{
	return p;
}

Time Cargo::GetCDT()
{
	Time t;
	if (p)
	{
		int n = (getcMT().getday()*24 + getcMT().gethour() + (DeliveryDist / p->getspeed()) + Loadtime);//here it is unloadtime 


		t.setday(n / 24);
		t.sethour(n % 24);

	}
	else 
	{
		t.setday(0);
		t.sethour(0);

	}
	return t;
}
int Cargo::getPriorityCDT()
{
	return GetCDT().getday()*24 +GetCDT().gethour();
}

Time Cargo::getWT()
{

	return WT;
}

Cargo::~Cargo()
{
}
