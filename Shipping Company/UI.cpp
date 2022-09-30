#include "UI.h"
#include "LinkedQueue.h"
#include"NormalCargo.h"
#include"SpecialCargo.h"
#include"VIPCargo.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
ostream& operator << (ostream& output, NormalCargo& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}
ostream& operator << (ostream& output, SpecialCargo& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}
ostream& operator << (ostream& output, VIPCargo& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}
ostream& operator << (ostream& output, VIPTrucks& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}
ostream& operator << (ostream& output, NormalTrucks& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}
ostream& operator << (ostream& output, SpecialTrucks& c)    // this function is to deal with ids in UI
{
	output << c.getid();
	return output;

}

void nprint(LinkedQueue <NormalCargo*> nc)
{
	LinkedQueue <NormalCargo*> temp;
	NormalCargo* n;

	while (!nc.isEmpty())
	{

		nc.dequeue(n);
		cout << n->getid();
		if (!nc.isEmpty())
			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		nc.enqueue(n);
	}


}
void sprint(LinkedQueue <SpecialCargo*> nc)
{
	LinkedQueue <SpecialCargo*> temp;
	SpecialCargo* n;

	while (!nc.isEmpty())
	{
		nc.dequeue(n);
		cout << n->getid();
		if (!nc.isEmpty())
			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		nc.enqueue(n);
	}


}
void vprint(LinkedQueue <VIPCargo*> nc)
{
	LinkedQueue <VIPCargo*> temp;
	VIPCargo* n;

	while (!nc.isEmpty())
	{
		nc.dequeue(n);
		cout << n->getid();
		if (!nc.isEmpty())
			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		nc.enqueue(n);
	}


}

void vprint(PriorityQueue <VIPCargo*> nc)
{
	PriorityQueue <VIPCargo*> temp;
	VIPCargo* n;
	int f;
	while (!nc.isEmpty())
	{
		nc.dequeue(n);
		cout << n->getid();
		if (!nc.isEmpty())
			cout << ",";
		f = n->GetCDT().getday() * 24 + n->GetCDT().gethour();
		temp.enqueue(n, f);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		f = n->GetCDT().getday() * 24 + n->GetCDT().gethour();
		nc.enqueue(n, f);
	}


}
void vtprint(LinkedQueue<VIPTrucks*>& v)
{
	LinkedQueue<VIPTrucks*> temp;
	VIPTrucks* n;

	while (!v.isEmpty())
	{
		v.dequeue(n);
		cout << n->getid();
		if (!v.isEmpty())
			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		v.enqueue(n);
	}

}
void ntprint(LinkedQueue<NormalTrucks*>& v)
{
	LinkedQueue<NormalTrucks*> temp;
	NormalTrucks* n;

	while (!v.isEmpty())
	{
		v.dequeue(n);
		cout << n->getid();
		if (!v.isEmpty())



			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		v.enqueue(n);
	}

}
void stprint(LinkedQueue<SpecialTrucks*>& v)
{
	LinkedQueue<SpecialTrucks*> temp;
	SpecialTrucks* n;

	while (!v.isEmpty())
	{
		v.dequeue(n);
		cout << n->getid();
		if (!v.isEmpty())
			cout << ",";
		temp.enqueue(n);

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		v.enqueue(n);
	}

}
void printCargos(PriorityQueue<Cargo*>& c)
{
	PriorityQueue<Cargo*> temp;
	Cargo* n;

	while (!c.isEmpty())
	{
		c.dequeue(n);
		cout << n->getid();
		if (!c.isEmpty())
			cout << ",";
		temp.enqueue(n, n->getDeliveryDist());

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		c.enqueue(n, n->getDeliveryDist());
	}

}




UI::UI(Company* c)
{
	if (c)
		C = c;

}

void UI::Showinfo(int day, int hour)   //it will be called at the end of the iteration of the for loop
{
	//in this function we are gonna get the queues of Company using getters to print them all



	if (currentmode == modes::interactive || currentmode == modes::stepbystep)
	{
		char key;
		int WaitingCargosNum; //number of waiting cargos
		int EmptyTruckNum, MovingCargosNum; //number of empty trucks and moving cargos
		//the queues below are used for getters of queues of company
		LinkedQueue<NormalCargo*>& waitNormalCargo = C->GetWaitingNormal();
		PriorityQueue<VIPCargo*>& waitVIPCargo = C->GetWaitingVIP();
		LinkedQueue<SpecialCargo*>& waitSpecialCargo = C->GetWaitingSpecial();
		LinkedQueue<NormalTrucks*>& EmptyTrucksNormal = C->GetEmptyNormalTrucks();
		LinkedQueue<VIPTrucks*>& EmptyTrucksVIP = C->GetEmptyVIPTrucks();
		LinkedQueue<SpecialTrucks*>& EmptyTrucksSpecail = C->GetEmptySpecialTrucks();
		//the queues below are used to seperate delivered queue into its different types to print them seperately
		LinkedQueue<NormalCargo*>Normaldelivered;
		LinkedQueue<VIPCargo*>VIPdelivered;
		LinkedQueue<SpecialCargo*>Specialdelivered;
		int loadingTruck = 0;
		int MaintenceTrucks = 0;



		cout << "Current Time (Day:Hour):" << day << ':' << hour << endl;

		WaitingCargosNum = C->GetWaitingNormal().getCount() + C->GetWaitingSpecial().getCount() + C->GetWaitingVIP().getcount();

		cout << WaitingCargosNum << " Waiting Cargos: " << '[';
		nprint(waitNormalCargo);
		cout << "]  (";
		sprint(waitSpecialCargo);
		cout << ")  {";
		vprint(waitVIPCargo);
		cout << "} " << endl;

		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		loadingTruck = C->NormalLoadExist() + C->VIPLoadExist() + C->SpecialLoadExist();


		cout << loadingTruck << " Loading Trucks :";
		if (C->GetLoadingNormaTrucks())
		{
			cout << C->GetLoadingNormaTrucks()->getid() << "[";
			printCargos(C->GetLoadingNormaTrucks()->GetCargos());
			cout << "]  ";
		}
		if (C->GetLoadingSpecialTrucks())
		{
			cout << C->GetLoadingSpecialTrucks()->getid() << "(";
			printCargos(C->GetLoadingSpecialTrucks()->GetCargos());
			cout << ")   ";
		}
		if (C->GetLoadingVIPTrucks())
		{
			cout << C->GetLoadingVIPTrucks()->getid() << "{";
			printCargos(C->GetLoadingVIPTrucks()->GetCargos());
			cout << "}";
		}

		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		//int MovTruc = 0;
		//MovTruc = C->GetMTNormal().getcount() + C->GetMTVIP().getcount() + C->GetMTSpecial().getcount();
		MovingCargosNum = C->GetMovings().getcount();
		cout << MovingCargosNum << " Moving Cargos: ";
		NormalTrucks* n;
		SpecialTrucks* s;
		VIPTrucks* v;
		PriorityQueue <NormalTrucks*> tempnt1;
		PriorityQueue <SpecialTrucks*> tempst1;
		PriorityQueue <VIPTrucks*> tempvt1;
		NormalTrucks* n2;
		SpecialTrucks* s2;
		VIPTrucks* v2;
		
		while (!C->GetMTNormal().isEmpty())
		{
			
			C->GetMTNormal().dequeue(n);
			tempnt1.enqueue(n, n->getDeliveryInterval() + n->getMT().getday() * 24 + n->getMT().gethour());
			cout << n->getid()<<"[ ";
			printCargos(n->GetCargos());
			cout << "]";
			

		}
		while (!C->GetMTSpecial().isEmpty())
		{
			
			C->GetMTSpecial().dequeue(s);
			tempst1.enqueue(s, s->getDeliveryInterval() + s->getMT().getday() * 24 + s->getMT().gethour());
			cout << s->getid() << "( ";
			printCargos(s->GetCargos());
			cout << ")";


		}
		while (!C->GetMTVIP().isEmpty())
		{
			
			C->GetMTVIP().dequeue(v);
			tempvt1.enqueue(v, v->getDeliveryInterval() + v->getMT().getday() * 24 + v->getMT().gethour());
			cout <<v->getid() << "{ ";
			printCargos(v->GetCargos());
			cout << "}";


		}
		

		cout << endl;
		
		while (!tempnt1.isEmpty())
		{
			tempnt1.dequeue(n2);
			C->GetMTNormal().enqueue(n2, n2->getDeliveryInterval() + n2->getMT().getday() * 24 + n2->getMT().gethour());
		}
		while (!tempvt1.isEmpty())
		{
			tempvt1.dequeue(v2);
			C->GetMTVIP().enqueue(v2, v2->getDeliveryInterval() + v2->getMT().getday() * 24 + v2->getMT().gethour());
		}
		while (!tempst1.isEmpty())
		{
			tempst1.dequeue(s2);
			C->GetMTSpecial().enqueue(s2, s2->getDeliveryInterval() + s2->getMT().getday() * 24 + s2->getMT().gethour());
		}



		
		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		EmptyTruckNum = C->GetEmptyNormalTrucks().getCount() + C->GetEmptySpecialTrucks().getCount() + C->GetEmptyVIPTrucks().getCount();
		cout << EmptyTruckNum << " Empty Trucks: [";
		ntprint(EmptyTrucksNormal);
		cout << "] (";
		stprint(EmptyTrucksSpecail);
		cout << ") {";
		vtprint(EmptyTrucksVIP);
		cout << "} " << endl;
		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		
		NormalCargo* temp1;
		VIPCargo* temp2;
		SpecialCargo* temp3;
		MovingCargosNum = C->GetMovings().getcount();
		
		MaintenceTrucks = C->GetMaintenceNormaTrucks().getCount() + C->GetMaintenceSpecialTrucks().getCount() + C->GetMaintenceVIPTrucks().getCount();

		cout << MaintenceTrucks << " In-Checkup Trucks : [";
		ntprint(C->GetMaintenceNormaTrucks());
		cout << "] (";
		stprint(C->GetMaintenceSpecialTrucks());
		cout << ") {";
		vtprint(C->GetMaintenceVIPTrucks());
		cout << "} " << endl;

		cout << "-----------------------------------------------------------------------------------------------------" << endl;
		cout << C->GetDelivered().getCount() << " Delivered Cargos: ";
		C->Seperatedel(Normaldelivered, Specialdelivered, VIPdelivered); //seperating delivered cargos into its different types
		cout << "[";
		nprint(Normaldelivered);
		cout << "] (";
		sprint(Specialdelivered);
		cout << ") {";
		vprint(VIPdelivered);
		cout << "} " << endl;


		if (currentmode == modes::stepbystep)
		{
			Sleep(1000);

			return;
		}
		else if (currentmode == modes::interactive)
		{
			cin.get();
		}


	}


}
void UI::silentmode()
{
	if (currentmode == modes::silent)
	{

		cout << "Silent Mode " << endl;
		cout << "Simulation Starts..." << endl;
		cout << "Simulation ends, Output file created" << endl;
		// the following line will be updated with the manager function 
		//--------------

	}
}

void UI::choosemode()      //When we create an obj of Class UI we must pass it to the simulation func by reference 
{
	int mode;

	cout << " Choose mode :Press " << endl;
	cout << "0 for Interactive mode " << endl;
	cout << "1 for Step by Step mode " << endl;
	cout << "2 for Silent mode " << endl;
	cin >> mode;
	if (mode == 0)
	{

		currentmode = modes::interactive;

	}
	else if (mode == 1)
	{

		currentmode = modes::stepbystep;

	}
	else if (mode == 2)
	{
		currentmode = modes::silent;
		silentmode();
	}

}


