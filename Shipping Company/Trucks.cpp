#include "Trucks.h"
#include "SpecialCargo.h"
#include "NormalCargo.h"
#include "VIPCargo.h"
int Trucks::count = 0;

Trucks::Trucks()
{
	count++;
	num = 0;
	ID = count;
	tDC =0;
	N = 0;

}

void Trucks::setnum(int n)
{
	num = n;
}

int Trucks::getnum()
{
	return num;
}


double Trucks::getActiveTime()
{
	double Active = 0;
	Cargo* c;
	PriorityQueue<Cargo*>temp;
	double maxdist = 0;
	double SumofUnLoad = 0;
	//Cargo* temp2 = NULL;
	while (!Cargos.isEmpty())
	{
		Cargos.dequeue(c);
		maxdist = c->getDeliveryDist();
		
		temp.enqueue(c, c->getDeliveryDist());
		SumofUnLoad = SumofUnLoad + c->getconstLoadt();
	}
	while (!temp.isEmpty())
	{
		temp.dequeue(c);
		Cargos.enqueue(c, c->getDeliveryDist());
	}
	
	
		Active = SumofUnLoad * 2 + maxdist / this->getspeed();
	
	return Active;
}






int Trucks::getid()
{
	return ID;
}

void Trucks::setnumj(int n)
{
	if (n >= 0)
		numj = n;

}

int Trucks::getnumj()
{
	return numj;
}


void Trucks::setMaintenceTime(int MT)
{
	if (MT > 0)
		MaintenceTime = MT;
}


int Trucks::getMaintenceTime()
{
	return MaintenceTime;
}

void Trucks::setspeed(double sp)
{
	if (sp >= 0)
		Speed = sp;
}

double Trucks::getspeed()
{

	return Speed;
}

void Trucks::setDeliveryInterval()
{
		PriorityQueue<Cargo*> temp;
		Cargo* c;
		double maxdist = -1;
		double SumofUnLoad = 0;
		while (!Cargos.isEmpty())
		{
			Cargos.dequeue(c);
			SumofUnLoad = SumofUnLoad + c->getLoadt();
			temp.enqueue(c, c->getDeliveryDist());
			if (c->getDeliveryDist()>maxdist)
			maxdist = c->getDeliveryDist();
		}
		while (!temp.isEmpty())
		{
			temp.dequeue(c);
			Cargos.enqueue(c, c->getDeliveryDist());
		}
	
		//The time to get back is the time taken from furthest place so we multiply the first term by two
		DI = 2 * (maxdist / this->getspeed()) + SumofUnLoad;
		
}

void Trucks::setWTforCargos()
{
	Cargo* c;
	PriorityQueue <Cargo*> temp;
	while (!Cargos.isEmpty())
	{
		Cargos.dequeue(c);
		temp.enqueue(c, c->getDeliveryDist());
		c->setWT(this->getMT() - c->getPT());


	}
	while (!temp.isEmpty())
	{
		temp.dequeue(c);
		Cargos.enqueue(c, c->getDeliveryDist());


	}


}





double Trucks::getDeliveryInterval()
{
	return DI;

}


Time Trucks::getMT()
{
	return MT;
}
void Trucks::addCargo(Cargo* c)
{

	Cargos.enqueue(c, c->getDeliveryDist());
	c->SetTruck(this);


}
void Trucks::RemoveCargo(Cargo* c)
{
	PriorityQueue<Cargo*> temp;
	Cargo* n;
	while (!Cargos.isEmpty())
	{
		Cargos.dequeue(n);
		if (c != n)
		{
			temp.enqueue(n, n->getDeliveryDist());
		}

	}
	while (!temp.isEmpty())
	{
		temp.dequeue(n);
		Cargos.enqueue(n, n->getDeliveryDist());

	}



}
void Trucks::setMT(Time m)
{
	PriorityQueue <Cargo*> temp;
	Cargo* c;

	int t=0;
	while (!Cargos.isEmpty())
	{
		Cargos.dequeue(c);
		temp.enqueue(c, c->getDeliveryDist());
		t += c->getLoadt();



	}
	while (!temp.isEmpty())
	{
		temp.dequeue(c);
		Cargos.enqueue(c, c->getDeliveryDist());

	}


	
	Time tv;
	if (23 - m.gethour() < t)
	{
		tv.sethour((m.gethour() + t + 5) % 24);
		tv.setday(((m.getday()*24)+ m.gethour() + t + 5)/24);
	}
	else
	{

		tv.sethour((m.gethour() + t ) % 24);
		tv.setday(m.getday() + (m.gethour() + t) / 24);
	}
	
	MT = tv;
}
void Trucks::settDc(int t)
{
	tDC = t;
}

int Trucks::gettDC()
{
	return tDC;
}

void Trucks::setN(int n)
{
	N = n;
}

int Trucks::getN()
{
	return N;
}

PriorityQueue<Cargo*>& Trucks::GetCargos()
{
	// TODO: insert return statement here
	return Cargos;
}



