#pragma once
#include "LinkedQueue.h"
#include "VIPTrucks.h"
#include "NormalTrucks.h"
#include "SpecialTrucks.h"
#include "NormalCargo.h"
#include "SpecialCargo.h"
#include "VIPCargo.h"
#include"UI.h"
#include "PriorityQueue.h"
#include "PreparationEvent.h"
#include "Time.h"
#include <iostream>
#include <fstream>
class Event;
class PreparationEvent;

class Company
{
	//Empty trucks
	LinkedQueue <VIPTrucks* > VT;
	LinkedQueue <SpecialTrucks* > ST;
	LinkedQueue <NormalTrucks*> NT;
	//Loading trucks
	VIPTrucks*  VTL;
	SpecialTrucks*  STL;
	NormalTrucks* NTL;
	//maintenace trucks
	LinkedQueue <VIPTrucks* > VTMain;
	LinkedQueue <SpecialTrucks* > STMain;
	LinkedQueue <NormalTrucks*> NTMain;
	//moving trucks
	PriorityQueue <VIPTrucks* > VTMov;
	PriorityQueue <SpecialTrucks* > STMov;
	PriorityQueue <NormalTrucks*> NTMov;


	
	//Waiting cargos
	LinkedQueue <NormalCargo*> WaitNormal;
	PriorityQueue<VIPCargo*> WaitVIP;
	LinkedQueue <SpecialCargo*> WaitSpecial;

	//moving cargos
	PriorityQueue<Cargo*> Movings;   //to be used in phase2 to arrange cargos according to Delivery Distance
 

	//only one queue for delivered to be able to arrange them according to CDT (required for output file) 
	LinkedQueue <Cargo*> Delveried;
	LinkedQueue <Event*> eptr;

	//for input & output files
	ifstream input;
	ofstream output;
	double ActiveTime;
	double UComp;


public:
	Company();
	bool availToLoadingNormal(Time t,NormalTrucks* N);
	bool availToLoadingVIP(Time t,VIPTrucks* V);
	bool availToLoadingSpecial(Time t,SpecialTrucks* S);
	void LoadVIP(Time t);//----->phase2
	void LoadNormal(Time t);//------>phase2
	void LoadSpecial(Time t);//----->phase2
	bool InsertVTtruck(int num, int numj, double s, int maintence, int Cap);
	bool InsertSTtruck(int num, int numj, double s, int maintence, int Cap);
	bool InsertNTtruck(int num, int numj, double s, int maintence, int Cap);
	bool InsertPEvent(PreparationEvent* p);


	//the functions below are used to move waiting cargos of each type to moving to delivered of same type
	//we could have made one queue for all moving and one queue for all waiting and we have to 
	//put after that each type in a seperate list to be able to print each type cargos together
	//as the sample of modes console 
	//for normal cargos
	bool waittoloadNcargos(Trucks *p);
	//for vip cargos
	bool waittoloadVcargos(Trucks *p);
	//for special cargos
	bool waittoloadScargos(Trucks*p);
	//for normal cargos
	

	//a function to move cargo from moving to delivered list if its move time plus CDT is the current time
	void movetodelCargo(Time t);
	//Move a truck
	void MoveaTruck(Time t);

	//Truck moving to avail or to checkup
	void Truckmovetoavailorcheckup(Time t);

	//Trucks checkup to avail
	void Truckchecktoavail(Time t);

	


	//the function below is to be used in Simulator Function to move cargo from each type to delivered
	void eachtypewaittodel();

	//the functions below used to set waiting cargos 
	bool setWaitN(NormalCargo* CN);
	bool setWaitS(SpecialCargo* SN);
	bool setWaitV(VIPCargo* VN);
	
	PriorityQueue<Cargo*>& GetMovings();



	//for reading info from input file
	void LoadInfo(string filename);
	void SaveInfo(Time t,string out ); //------> to be implemented in phase2
	//the function below is to seperate delivered cargos into their 3 types
	//to be able to print them seperately as required in modes console
	void Seperatedel(LinkedQueue <NormalCargo*>& N, LinkedQueue <SpecialCargo*>& S, LinkedQueue <VIPCargo*>& V);
	void seperateMov(PriorityQueue<NormalCargo*>& N, PriorityQueue<SpecialCargo*>&S, PriorityQueue<VIPCargo*>& V);
	//Getters for Cargos
	LinkedQueue<NormalCargo*>& GetWaitingNormal();  // To deal with Cargos in UI
	PriorityQueue<VIPCargo*>& GetWaitingVIP();
	LinkedQueue<SpecialCargo*>& GetWaitingSpecial();

	//Getters for Empty Trucks
	LinkedQueue<NormalTrucks*>& GetEmptyNormalTrucks();
	LinkedQueue<VIPTrucks*>& GetEmptyVIPTrucks();
	LinkedQueue<SpecialTrucks*>& GetEmptySpecialTrucks();


	//Getters for Maintence Trucks //implemented 22-5-2022
	LinkedQueue<NormalTrucks*>& GetMaintenceNormaTrucks();
	LinkedQueue<SpecialTrucks*>& GetMaintenceSpecialTrucks();      //Phase 2
	LinkedQueue<VIPTrucks*>& GetMaintenceVIPTrucks();
	//Getters for Maintence Trucks //implemented 22-5-2022
	NormalTrucks*& GetLoadingNormaTrucks();
	SpecialTrucks*& GetLoadingSpecialTrucks();      //Phase 2
	VIPTrucks*& GetLoadingVIPTrucks();
	int NormalLoadExist();
	int VIPLoadExist();
	int SpecialLoadExist();

	
	//Getters for Moving Cargos 
	
	//Getter for Delivered
	LinkedQueue<Cargo*>& GetDelivered();
	//Getters for Moving Trucks Queues
	PriorityQueue<NormalTrucks*>& GetMTNormal();
	PriorityQueue<SpecialTrucks*>& GetMTSpecial();
	PriorityQueue<VIPTrucks*>& GetMTVIP();

	void SimulatorFunction(string s,string out);
	


	
	//maybe changed
	void setActiveTime(double a);
	void setUtili(double u);


};

