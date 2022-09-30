#pragma once
#include "Time.h"
#include<iostream>
#include<fstream>
using namespace std;
class Company;
class Event
{
	Time etime;
	//char cargotype;         //maybe not a data member,revise  
protected:
	Company* M;  //Take care maybe changed,the justification for setter and getter that 
						   //all the events are at same company so it must be at base class 
				   //we have a problem that M is unknown identifier where we used Company C in UI and Company M in Event
public:
	Event(Company* c);
	void setTime(Time t);
	Time getTime();
	//void setcargotype(char c);
	//char getcargotype();
	virtual void Execute() = 0;
	virtual void LoadInfo(ifstream& in) = 0;
	//void setC(Company* c);//Take care maybe changed
	//Company* getC();//Take care maybe changed

};

