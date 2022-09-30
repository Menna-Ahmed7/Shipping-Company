#pragma once
#include "Event.h"
#include "Cargo.h"
#include "Company.h"
class PreparationEvent : public Event
{
	float cargodata[4]; //data member to store cargo data as we read cargo data before making the cargo itself
					   //in Execute so we have to store it, float and not int because distance in km is included in this data
	char cargotype;
public:
	PreparationEvent(Company* c);
	virtual void Execute();
	virtual void LoadInfo(ifstream& in);
	void setcargotype(char c);
	char getcargotype();
	void setcargodata(float k[]);//fuunction to keep cargo data read from input file to use it when
								//we make the object    
	float* getcargodata();       // function to return read cargo data to be used in making object

};

