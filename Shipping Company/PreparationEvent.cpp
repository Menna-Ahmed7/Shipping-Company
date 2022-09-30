#include "PreparationEvent.h"
#include "NormalCargo.h"
#include"SpecialCargo.h"
#include"VIPCargo.h"
#include "Event.h"



PreparationEvent::PreparationEvent(Company* c) :Event(c)
{
}

void PreparationEvent::Execute()
{
	float* k = getcargodata();


	char ch = getcargotype();
	SpecialCargo* SC;
	VIPCargo* VC;
	NormalCargo* NC;
	if (ch == 'S')
	{
		SC = new SpecialCargo;
		SC->setid(k[0]);
		SC->setDeliveryDist(k[1]);
		SC->setLoadt(k[2]);
		SC->setconstLoadt(k[2]);
		SC->setCost(k[3]);
		SC->setPT(getTime());
		M->setWaitS(SC);

	}
	else if (ch == 'V')
	{
		VC = new VIPCargo;
		VC->setid(k[0]);
		VC->setDeliveryDist(k[1]);
		VC->setconstLoadt(k[2]);
		VC->setLoadt(k[2]);
		VC->setCost(k[3]);
		VC->setPT(getTime());
		M->setWaitV(VC);
	}
	else if (ch == 'N')
	{
		NC = new NormalCargo;
		NC->setid(k[0]);
		NC->setDeliveryDist(k[1]);
		NC->setLoadt(k[2]);
		NC->setconstLoadt(k[2]);
		NC->setCost(k[3]);
		NC->setPT(getTime());
		M->setWaitN(NC);
	}



}

void PreparationEvent::LoadInfo(ifstream& in)
{
	char c;
	int l, f;
	float k[4];
	in >> c;
	setcargotype(c);
	Time T;
	in >> l;
	T.setday(l);

	in.ignore();

	in >> f;
	T.sethour(f);
	setTime(T);
	//this numbers are the input of user about cargo info
	for (int j = 0; j < 4; j++)
		in >> k[j];
	setcargodata(k);


}

void PreparationEvent::setcargotype(char c)
{
	if (c == 'N' || c == 'S' || c == 'V')
		cargotype = c;

}

char PreparationEvent::getcargotype()
{
	return cargotype;
}

void PreparationEvent::setcargodata(float k[])
{
	for (int i = 0; i < 4; i++)
		cargodata[i] = k[i];
}

float* PreparationEvent::getcargodata()
{
	return cargodata;
}
