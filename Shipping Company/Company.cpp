#include "Company.h"
#include "VIPTrucks.h"
#include"NormalTrucks.h"
#include"SpecialTrucks.h"
#include"Event.h"
#include"PreparationEvent.h"

Company::Company()
{
    ActiveTime = 0;
    UComp = 0;
}

bool Company::availToLoadingNormal(Time t, NormalTrucks* N)//time t is the current simulation time
                                                          //which we will use to calculate MT  
{
    if (!NTL)
    {
        NT.dequeue(N);
        NTL = N;

        return true;

    }
    else return false;
}

bool Company::availToLoadingVIP(Time t, VIPTrucks* V)
{
    if (!VTL)
    {
        VT.dequeue(V);
        VTL = V;

        return true;
    }
    else return false;
}

bool Company::availToLoadingSpecial(Time t, SpecialTrucks* S)
{
    if (!STL) {
        ST.dequeue(S);
        STL = S;

        return true;
    }
    else return false;
}

void Company::LoadVIP(Time t)//t is current time
{
    VIPTrucks* V;
    NormalTrucks* N;
    SpecialTrucks* S;
    VIPCargo* v;
    Cargo* c;
    PriorityQueue<Cargo*> temp;
    if (!VT.isEmpty())
    {

        VT.peek(V);
        if (WaitVIP.getcount() >= V->getTruckCap())
        {
            if (availToLoadingVIP(t, V))
            {
                for (int i = 0; i < V->getTruckCap(); i++)
                {

                    waittoloadVcargos(V);

                }
                V->setMT(t);
                V->setDeliveryInterval();
                while (!V->GetCargos().isEmpty())
                {
                    V->GetCargos().dequeue(c);
                    temp.enqueue(c, c->getDeliveryDist());
                    c->setcMT(V->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(c);
                    V->GetCargos().enqueue(c,c->getDeliveryDist());

                }


            }
        }




    }
    else if (!NT.isEmpty())
    {
        NT.peek(N);
        if (WaitVIP.getcount() >= N->getTruckCap())
        {
            if (availToLoadingNormal(t, N))
            {
                for (int i = 0; i < N->getTruckCap(); i++)
                {

                    waittoloadVcargos(N);


                }
                N->setMT(t);
                N->setDeliveryInterval();
                while (!N->GetCargos().isEmpty())
                {
                    N->GetCargos().dequeue(c);
                    temp.enqueue(c, c->getDeliveryDist());
                    c->setcMT(N->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(c);
                    N->GetCargos().enqueue(c, c->getDeliveryDist());

                }


            }
        }

    }
    else if (!ST.isEmpty())
    {
        ST.peek(S);
        if (WaitVIP.getcount() >= S->getTruckCap())
        {
            if (availToLoadingSpecial(t, S))
            {
                for (int i = 0; i < S->getTruckCap(); i++)
                {

                    waittoloadVcargos(S);

                }

                S->setMT(t);
                S->setDeliveryInterval();
                while (!S->GetCargos().isEmpty())
                {
                    S->GetCargos().dequeue(c);
                    temp.enqueue(c, c->getDeliveryDist());
                    c->setcMT(S->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(c);
                    S->GetCargos().enqueue(c, c->getDeliveryDist());

                }

            }
        }

    }


}

void Company::LoadNormal(Time t)
{
    NormalTrucks* p;
    NT.peek(p);
    NormalCargo* c;
    VIPTrucks* p2;
    Cargo* l;
    PriorityQueue<Cargo*> temp;
    if (!NT.isEmpty())
    {
        NT.peek(p);
        if (WaitNormal.getCount() >= p->getTruckCap())
        {
            if (availToLoadingNormal(t, p))
            {
                for (int i = 0; i < p->getTruckCap(); i++)
                {

                    waittoloadNcargos(p);


                }
                p->setMT(t);
                p->setDeliveryInterval();
                while (!p->GetCargos().isEmpty())
                {
                    p->GetCargos().dequeue(l);
                    temp.enqueue(l, l->getDeliveryDist());
                    l->setcMT(p->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(l);
                    p->GetCargos().enqueue(l, l->getDeliveryDist());

                }


            }
        }

    }
    // reaching this line means that there is NOT Normal Trucks So we have to assign it to VIP Trucks
    else if (!VT.isEmpty())
    {
        VT.peek(p2);
        if (WaitNormal.getCount() >= p2->getTruckCap())
        {
            if (availToLoadingVIP(t, p2))
            {
                for (int i = 0; i < p2->getTruckCap(); i++)
                {

                    waittoloadNcargos(p2);

                }
                p2->setMT(t);
                p2->setDeliveryInterval();
                while (!p2->GetCargos().isEmpty())
                {
                    p2->GetCargos().dequeue(l);
                    temp.enqueue(l, l->getDeliveryDist());
                    l->setcMT(p2->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(l);
                    p2->GetCargos().enqueue(l, l->getDeliveryDist());

                }


            }
        }

    }

    //reaching this line means there is NO suitable Trucks for Normal Cargos

}
void Company::LoadSpecial(Time t)
{
    SpecialTrucks* S;
    SpecialCargo* s;
    Cargo* c;
    PriorityQueue<Cargo*>temp;
    if (!ST.isEmpty())
    {
        ST.peek(S);
        if (WaitSpecial.getCount() >= S->getTruckCap())
        {
            if (availToLoadingSpecial(t, S))
            {
                for (int i = 0; i < S->getTruckCap(); i++)
                {

                    waittoloadScargos(S);

                }

                S->setMT(t);
                S->setDeliveryInterval();
                while (!S->GetCargos().isEmpty())
                {
                    S->GetCargos().dequeue(c);
                    temp.enqueue(c, c->getDeliveryDist());
                    c->setcMT(S->getMT());

                }
                while (!temp.isEmpty())
                {
                    temp.dequeue(c);
                    S->GetCargos().enqueue(c, c->getDeliveryDist());

                }


            }
        }

    }

}
bool Company::InsertVTtruck(int num, int numj, double s, int maintence, int Cap)
{
    for (int i = 0; i < num; i++)
    {

        VIPTrucks* V = new VIPTrucks;
        if (!V)
            return false;
        VT.enqueue(V);
        V->setnumj(numj);
        V->setspeed(s);
        V->setMaintenceTime(maintence);
        V->setTruckCap(Cap);

    }

    return true;
}

bool Company::InsertSTtruck(int num, int numj, double s, int maintence, int Cap)
{
    for (int i = 0; i < num; i++)
    {

        SpecialTrucks* S = new SpecialTrucks;
        if (!S)
            return false;
        ST.enqueue(S);
        S->setnumj(numj);
        S->setspeed(s);
        S->setMaintenceTime(maintence);
        S->setTruckCap(Cap);
    }
    return true;
}

bool Company::InsertNTtruck(int num, int numj, double s, int maintence, int Cap)
{
    for (int i = 0; i < num; i++)
    {

        NormalTrucks* N = new NormalTrucks;
        if (!N)
            return false;
        NT.enqueue(N);
        N->setnumj(numj);
        N->setspeed(s);
        N->setMaintenceTime(maintence);
        N->setTruckCap(Cap);
    }
    return true;
}

bool Company::waittoloadNcargos(Trucks* p)
{

    if (!WaitNormal.isEmpty())
    {
        NormalCargo* x;
        WaitNormal.dequeue(x);
        x->SetTruck(p);
        p->addCargo(x);
        p->settDc(p->gettDC() + 1);
        return true;



    }


    return false;

}

/*bool Company::movetodelNcargos()
{

    if(!MovingNormal.isEmpty())
    {
        NormalCargo* x = nullptr;
        MovingNormal.remove(x);
        DelNormal.enqueue(x);
        return true;



    }


    return false;
}*/

bool Company::waittoloadVcargos(Trucks* p)
{

    if (!WaitVIP.isEmpty())
    {
        VIPCargo* x;
        WaitVIP.dequeue(x);
        x->SetTruck(p);
        p->addCargo(x);
        p->settDc(p->gettDC() + 1);

        return true;



    }


    return false;
}

/*bool Company::movetodelVcargos()
{
    if (!MovingVIP.isEmpty())
    {
        VIPCargo* x;
        MovingVIP.remove(x);
        DelVIP.enqueue(x);
        return true;

    }
    return false;
}*/

bool Company::waittoloadScargos(Trucks* p)
{

    if (!WaitSpecial.isEmpty())
    {
        SpecialCargo* x;
        WaitSpecial.dequeue(x);
        x->SetTruck(p);
        p->addCargo(x);
        p->settDc(p->gettDC() + 1);

        return true;



    }

    return false;
}




void Company::movetodelCargo(Time t)//t is current time
{

    VIPTrucks* v;
    NormalTrucks* n;
    SpecialTrucks* s;
    Cargo* c;
    PriorityQueue<VIPTrucks*> tempv;
    PriorityQueue<NormalTrucks*> tempn;
    PriorityQueue<SpecialTrucks*> temps;
    PriorityQueue<Cargo*> tempc;
    PriorityQueue<Cargo*>tempo;
    PriorityQueue<Cargo*>tempcar;
    Cargo* ct;
    Cargo* ctemp;
    while (!Movings.isEmpty())
    {
        Movings.dequeue(c);
        if (t.getday() == c->GetCDT().getday() && t.gethour() == c->GetCDT().gethour())//if CDT of a cargo is reached
        {
           
            Delveried.enqueue(c);
            //below we are searching for this cargo inside the trucks
            
            //searching for cargo inside VIP moving trucks
            while (!VTMov.isEmpty())
            {
                VTMov.dequeue(v);
                tempv.enqueue(v, v->getMT().getday() * 24 + v->getMT().gethour() + v->getDeliveryInterval());//Moving trucks is arranged according to MT and Delivery Interval
                //serach for cargo inside this truck
                v->RemoveCargo(c);
                

            }
            //reaching this line means we never found it in moving vip trucks so we are going to search for it in 
            //moving special trucks and moving normal trucks
            while (!tempv.isEmpty())
            {
                tempv.dequeue(v);
                VTMov.enqueue(v, v->getMT().getday() * 24 + v->getMT().gethour() + v->getDeliveryInterval());

            }
            
            
            //searching inside special moving trucks
            while (!STMov.isEmpty())
            {
                STMov.dequeue(s);
                temps.enqueue(s, s->getMT().getday() * 24 + s->getMT().gethour() + s->getDeliveryInterval());
                s->RemoveCargo(c);
               
            }
            while (!temps.isEmpty())
            {
                temps.dequeue(s);
                STMov.enqueue(s, s->getMT().getday() * 24 + s->getMT().gethour() + s->getDeliveryInterval());

            }

            //searching inside normal moving trucks
            while (!NTMov.isEmpty())
            {
                NTMov.dequeue(n);
                tempn.enqueue(n, n->getMT().getday() * 24 +n->getMT().gethour() + n->getDeliveryInterval());
                n->RemoveCargo(c);
              

            }
            while (!tempn.isEmpty())
            {
                tempn.dequeue(n);
                NTMov.enqueue(n, n->getMT().getday() * 24 + n->getMT().gethour() + n->getDeliveryInterval());

            }





        }
        else
        {
            tempo.enqueue(c, c->getPriorityCDT());
        }
 



    }

    while (!tempo.isEmpty())
    {
        tempo.dequeue(c);
        Movings.enqueue(c, c->getPriorityCDT());
    }



}

void Company::MoveaTruck(Time t)
{
    SpecialCargo* s;
    NormalCargo* n;
    VIPCargo* v;
    PriorityQueue<Cargo*> temp;
    Cargo* c;
    if (VTL)
    {// Move time is not setted yet 
        if (VTL->getMT().gethour() <= t.gethour() && VTL->getMT().getday() == t.getday())
        {
            //VTL->setMT(t);
            VTL->setWTforCargos();

            int num = 0;
            int inc_load = 0;



            while (!VTL->GetCargos().isEmpty())
            {
                VTL->GetCargos().dequeue(c);
                n = dynamic_cast<NormalCargo*>(c);
                s = dynamic_cast<SpecialCargo*>(c);
                v = dynamic_cast<VIPCargo*>(c);
                if (n)
                {
                    num += n->getLoadt();
                    n->setLoadt(n->getLoadt() + inc_load);
                    inc_load = n->getLoadt();
                    temp.enqueue(n,n->getDeliveryDist());
                   Movings.enqueue(n,n->getPriorityCDT());


                }
                else if (s)
                {
                    num += s->getLoadt();
                    s->setLoadt(s->getLoadt() + inc_load);
                    inc_load = s->getLoadt();
                    temp.enqueue(s, s->getDeliveryDist());
                    Movings.enqueue(s, s->getPriorityCDT());


                }
                else if (v)
                {
                    num += v->getLoadt();
                    v->setLoadt(v->getLoadt() + inc_load);
                    inc_load = v->getLoadt();
                    temp.enqueue(v,v->getDeliveryDist());
                    Movings.enqueue(v, v->getPriorityCDT());


                }

            }

            while (!temp.isEmpty())
            {
                temp.dequeue(c);
                VTL->addCargo(c);


            }


            VTL->setnum(VTL->getnum() + 1);
            VTL->setN(VTL->getN() + 1);
            VTMov.enqueue(VTL, VTL->getMT().getday() * 24 + VTL->getMT().gethour() + VTL->getDeliveryInterval());
            this->setActiveTime(VTL->getActiveTime());
            this->setUtili(VTL->VIPTruckUti(t));
            VTL = nullptr;

        }


    }
    if (STL)
    {


        if (STL->getMT().gethour() <= t.gethour() && STL->getMT().getday() == t.getday())
        {
            STL->setWTforCargos();
            int num1 = 0;
            int inc_load1 = 0;
            while (!STL->GetCargos().isEmpty())
            {


                STL->GetCargos().dequeue(c);
                n = dynamic_cast<NormalCargo*>(c);
                s = dynamic_cast<SpecialCargo*>(c);
                v = dynamic_cast<VIPCargo*>(c);
                if (n)
                {
                    num1 += n->getLoadt();
                    n->setLoadt(n->getLoadt() + inc_load1);
                    inc_load1 = n->getLoadt();
                    temp.enqueue(n, n->getDeliveryDist());
                    Movings.enqueue(n, n->getPriorityCDT());


                }
                else if (s)
                {
                    num1 += s->getLoadt();
                    s->setLoadt(s->getLoadt() + inc_load1);
                    inc_load1 = s->getLoadt();
                    temp.enqueue(s, s->getDeliveryDist());
                    Movings.enqueue(s, s->getPriorityCDT());


                }
                else if (v)
                {
                    num1 += v->getLoadt();
                    v->setLoadt(v->getLoadt() + inc_load1);
                    inc_load1 = v->getLoadt();
                    temp.enqueue(v, v->getDeliveryDist());
                    Movings.enqueue(v, v->getPriorityCDT());


                }

            }

            while (!temp.isEmpty())
            {

                temp.dequeue(c);
                STL->addCargo(c);


            }
            STL->setnum(STL->getnum() + 1);
            STL->setN(STL->getN() + 1);
            STMov.enqueue(STL, STL->getMT().getday() * 24 + STL->getMT().gethour() + STL->getDeliveryInterval());
            this->setActiveTime(STL->getActiveTime());
            this->setUtili(STL->SpecialTruckUti(t));
            STL = nullptr;

        }


    }
    if (NTL)
    {
        if (NTL->getMT().gethour() <= t.gethour() && NTL->getMT().getday() == t.getday())
        {
            NTL->setWTforCargos();
            int num2 = 0;
            int inc_load2 = 0;
            while (!NTL->GetCargos().isEmpty())
            {

                NTL->GetCargos().dequeue(c);
                n = dynamic_cast<NormalCargo*>(c);
                s = dynamic_cast<SpecialCargo*>(c);
                v = dynamic_cast<VIPCargo*>(c);
                if (n)
                {
                    num2 += n->getLoadt();
                    n->setLoadt(n->getLoadt() + inc_load2);
                    inc_load2 = n->getLoadt();
                    temp.enqueue(n, n->getDeliveryDist());
                    Movings.enqueue(n, n->getPriorityCDT());


                }
                else if (s)
                {
                    num2 += s->getLoadt();
                    s->setLoadt(s->getLoadt() + inc_load2);
                    inc_load2 = s->getLoadt();
                    temp.enqueue(s, s->getDeliveryDist());
                    Movings.enqueue(s, s->getPriorityCDT());


                }
                else if (v)
                {
                    num2 += v->getLoadt();
                    v->setLoadt(v->getLoadt() + inc_load2);
                    inc_load2 = v->getLoadt();
                    temp.enqueue(v, v->getDeliveryDist());
                   Movings.enqueue(v, v->getPriorityCDT());


                }

            }

            while (!temp.isEmpty())
            {
                temp.dequeue(c);
                NTL->addCargo(c);


            }
            NTL->setnum(NTL->getnum() + 1);
            NTL->setN(NTL->getN() + 1);
            NTMov.enqueue(NTL, NTL->getMT().getday() * 24 + NTL->getMT().gethour() + NTL->getDeliveryInterval());
            this->setActiveTime(NTL->getActiveTime());
            this->setUtili(NTL->NormalTruckUti(t));
            NTL = nullptr;

        }


    }

}



void Company::Truckmovetoavailorcheckup(Time t)
{
    VIPTrucks* v;
    NormalTrucks* n;
    SpecialTrucks* s;
    while (!VTMov.isEmpty())
    {
        VTMov.dequeue(v);
        int tm = v->getMT().getday() * 24 + v->getMT().gethour() + v->getDeliveryInterval();
        //current time the truck has ended its journey

        if ((t.getday() == tm / 24) && (t.gethour() == tm % 24))
        {

            if (v->getnum() == v->getnumj())
            {
                VTMain.enqueue(v);

            }
            else
            {
                VT.enqueue(v);

            }

        }
        else {
            VTMov.enqueue(v, tm); //didn't finish its journey yet
            break;
        }
    }

    while (!STMov.isEmpty())
    {
        STMov.dequeue(s);
        int ts = s->getMT().getday() * 24 + s->getMT().gethour() + s->getDeliveryInterval();
        //current time the truck has ended its journey
        if ((t.getday() == ts / 24) && (t.gethour() == ts % 24))
        {
            if (s->getnum() == s->getnumj())
            {
                STMain.enqueue(s);

            }
            else
            {
                ST.enqueue(s);

            }

        }
        else {
            STMov.enqueue(s, ts); //didn't finish its journey yet
            break;
        }
    }

    while (!NTMov.isEmpty())
    {
        NTMov.dequeue(n);
        int tn = n->getMT().getday() * 24 + n->getMT().gethour() + n->getDeliveryInterval();
        //current time the truck has ended its journey
        if ((t.getday() == tn / 24) && (t.gethour() == tn % 24))
        {
            if (n->getnum() == n->getnumj())
            {
                NTMain.enqueue(n);

            }
            else
            {
                NT.enqueue(n);

            }

        }
        else {
            NTMov.enqueue(n, tn); //didn't finish its journey yet
            break;
        }
    }














}

void Company::Truckchecktoavail(Time t)
{


    VIPTrucks* v;
    NormalTrucks* n;
    SpecialTrucks* s;
    while (!VTMain.isEmpty())
    {
        VTMain.peek(v);
        int tm = v->getMT().getday() * 24 + v->getMT().gethour() +v->getDeliveryInterval()+ v->getMaintenceTime();
        //at current time truck has finished maintenance
        if ((t.getday() == tm / 24) && (t.gethour() == tm % 24))
        {
            VTMain.dequeue(v);
            VT.enqueue(v);
            v->setnum(0);
        }
        else {

            break;
        }
    }

    while (!STMain.isEmpty())
    {
        STMain.peek(s);
        int ts = s->getMT().getday() * 24 + s->getMT().gethour() + s->getDeliveryInterval() + s->getMaintenceTime();
        //at current time truck has finished maintenance
        if ((t.getday() == ts / 24) && (t.gethour() == ts % 24))
        {
            STMain.dequeue(s);
            ST.enqueue(s);
            s->setnum(0);
        }
        else {

            break;
        }
    }

    while (!NTMain.isEmpty())
    {
        NTMain.peek(n);
        int tn = n->getMT().getday() * 24 + n->getMT().gethour() + n->getDeliveryInterval() + n->getMaintenceTime();
        //at current time truck has finished maintenance
        if ((t.getday() == tn / 24) && (t.gethour() == tn % 24))
        {
            NTMain.dequeue(n);
            NT.enqueue(n);
            n->setnum(0);
        }
        else {

            break;
        }
    }


}




void Company::eachtypewaittodel()
{
    int n;
    if (!WaitVIP.isEmpty())
    {
        VIPCargo* z;
        WaitVIP.dequeue(z);

        Delveried.enqueue(z);


    }
    if (!WaitSpecial.isEmpty())
    {
        SpecialCargo* x;
        WaitSpecial.dequeue(x);
        Delveried.enqueue(x);
    }
    if (!WaitNormal.isEmpty())
    {
        NormalCargo* y;
        WaitNormal.dequeue(y);
        Delveried.enqueue(y);
    }
}






bool Company::setWaitN(NormalCargo* CN)
{
    if (CN)
    {
        WaitNormal.enqueue(CN);
        return true;
    }
    return false;
}

bool Company::setWaitS(SpecialCargo* SN)
{
    if (SN)
    {
        WaitSpecial.enqueue(SN);
        return true;
    }
    return false;
}

bool Company::setWaitV(VIPCargo* VN)
{

    if (VN)
    {
        WaitVIP.enqueue(VN, VN->getpriority());
        return true;
    }
    return false;
}

PriorityQueue<Cargo*>& Company::GetMovings()
{
    // TODO: insert return statement here
    return Movings;
}



void Company::LoadInfo(string filename)
{
    int n[13];
    input.open(filename);

    if (input.is_open())
    {
        for (int i = 0; i < 13; i++)
            input >> n[i];

        InsertNTtruck(n[0], n[9], n[3], n[12], n[6]);
        InsertSTtruck(n[1], n[10], n[4], n[12], n[7]);
        InsertVTtruck(n[2], n[11], n[5], n[12], n[8]);

    }

    int n1;
    input >> n1;
    for (int i = 0; i < n1; i++)
    {
        char m;
        input >> m;
        if (m == 'R')
        {
            PreparationEvent* pe = new PreparationEvent(this);
            InsertPEvent(pe);
            pe->LoadInfo(input);


        }

    }




}

void Company::SaveInfo(Time t, string out)
{
    LinkedQueue <Cargo*>temp;
    LinkedQueue <VIPTrucks* > VTtemp;
    LinkedQueue <SpecialTrucks* > STtemp;
    LinkedQueue <NormalTrucks*> NTtemp;
    PriorityQueue <VIPTrucks* > VTMovtemp;
    PriorityQueue <SpecialTrucks* > STMovtemp;
    PriorityQueue <NormalTrucks*> NTMovtemp;
    LinkedQueue<NormalTrucks*> NTm;
    LinkedQueue<VIPTrucks*> VTm;
    LinkedQueue<SpecialTrucks*> STm;
    Cargo* c;
    int d = 0, h = 0;
    output.open(out, ios::out);
    if (output.is_open())
    {
        output << "CDT" << "   " << "ID" << "   " << "PT" << "   " << "WT" << "   " << "TID" << endl;
        while (!Delveried.isEmpty())
        {

            Delveried.dequeue(c);
            temp.enqueue(c);
            output << c->GetCDT().getday() << ":" << c->GetCDT().gethour() << "   ";
            output << c->getid() << "   " << c->getPT().getday() << ":" << c->getPT().gethour() << "   ";
            output << c->getWT().getday() << ":" << c->getWT().gethour() << "   ";

            //the remaining is trucks id 
            output << c->GetTruck()->getid() << endl;
            d += c->getWT().getday();
            h += c->getWT().gethour();


        }
        while (!temp.isEmpty())
        {

            temp.dequeue(c);
            Delveried.enqueue(c);


        }
        LinkedQueue<SpecialCargo*> s;
        LinkedQueue <NormalCargo*> n;
        LinkedQueue <VIPCargo*> v;
        Seperatedel(n, s, v);
        cout << endl;
        int num = s.getCount() + n.getCount() + v.getCount();
        output << "Cargos: " << num << " [N: " << n.getCount();
        output << ", S: " << s.getCount() << ", V: " << v.getCount() << "]" << endl;
        d = d + h / 24;
        h = h % 24;
        int no = 1;
        if (num > 0)
        {
            no = (d * 24 + h) / num;
        }
        output << "Cargo Avg Wait =" << no / 24 << ":" << no % 24 << endl;
        int numv = VT.getCount() + VTMov.getcount() + VTMain.getCount();
        int numn = NT.getCount() + NTMov.getcount() + NTMain.getCount();
        int nums = ST.getCount() + STMov.getcount() + STMain.getCount();
        if (VTL != NULL)
            numv++;
        if (NTL != NULL)
            numn++;
        if (STL != NULL)
            nums++;
        int NumOfTrucks = numv + numn + nums;
        int Tsm = t.gethour() + t.getday() * 24;
        double AvgActivetime = ((ActiveTime / (NumOfTrucks * Tsm))) * 100;
        double utilization = (ActiveTime / (NumOfTrucks * Tsm)) * 100;
        output << "Trucks: " << NumOfTrucks << "[N: " << numn << ", S:" << nums << ", V: " << numv << "]" << endl;
        output << "Avg Active time =" << AvgActivetime << "%" << endl;
        output << "Avg utilization =" << utilization << "%" << endl;
    }
}





void Company::Seperatedel(LinkedQueue<NormalCargo*>& N, LinkedQueue<SpecialCargo*>& S, LinkedQueue<VIPCargo*>& V)
{
    NormalCargo* n;
    SpecialCargo* s;
    VIPCargo* v;
    Cargo* temp;
    LinkedQueue <Cargo*>tempq;
    int f;

    while (!Delveried.isEmpty())
    {
        Delveried.dequeue(temp);
        tempq.enqueue(temp);
        n = dynamic_cast<NormalCargo*>(temp);
        s = dynamic_cast<SpecialCargo*> (temp);
        v = dynamic_cast<VIPCargo*> (temp);
        if (n)
            N.enqueue(n);
        else if (s)
            S.enqueue(s);
        else if (v)
            V.enqueue(v);
    }
    while (!tempq.isEmpty())
    {

        tempq.dequeue(temp);

        Delveried.enqueue(temp);
    }



}

void Company::seperateMov(PriorityQueue<NormalCargo*>& N, PriorityQueue<SpecialCargo*>& S, PriorityQueue<VIPCargo*>& V)
{
    NormalCargo* n;
    SpecialCargo* s;
    VIPCargo* v;
    Cargo* temp;
    PriorityQueue <Cargo*>tempq;
    int f;

    while (!Movings.isEmpty())
    {
        Movings.dequeue(temp);
        tempq.enqueue(temp, temp->getPriorityCDT());
        n = dynamic_cast<NormalCargo*>(temp);
        s = dynamic_cast<SpecialCargo*> (temp);
        v = dynamic_cast<VIPCargo*> (temp);
        if (n)
            N.enqueue(n, n->getPriorityCDT());
        else if (s)
            S.enqueue(s, s->getPriorityCDT());
        else if (v)
            V.enqueue(v, v->getPriorityCDT());
    }
    while (!tempq.isEmpty())
    {

        tempq.dequeue(temp);

        Movings.enqueue(temp, temp->getPriorityCDT());
    }


}

LinkedQueue<NormalCargo*>& Company::GetWaitingNormal()
{
    return WaitNormal;
}

PriorityQueue<VIPCargo*>& Company::GetWaitingVIP()
{

    return WaitVIP;
}

LinkedQueue<SpecialCargo*>& Company::GetWaitingSpecial()
{

    return WaitSpecial;
}

LinkedQueue<NormalTrucks*>& Company::GetEmptyNormalTrucks()
{

    return NT;
}

LinkedQueue<VIPTrucks*>& Company::GetEmptyVIPTrucks()
{

    return VT;
}

LinkedQueue<SpecialTrucks*>& Company::GetEmptySpecialTrucks()
{

    return ST;
}



LinkedQueue<Cargo*>& Company::GetDelivered()
{

    return Delveried;
}
PriorityQueue<NormalTrucks*>& Company::GetMTNormal()
{
    return NTMov;
}
PriorityQueue<SpecialTrucks*>& Company::GetMTSpecial()
{
    return STMov;
}
PriorityQueue<VIPTrucks*>& Company::GetMTVIP()
{
    return VTMov;
}
void Company::SimulatorFunction(string s,string out)
{
    UI userInterface(this);
    userInterface.choosemode();
    cin.get();
    bool f = true;
    Event* e;
    LoadInfo(s);
    Time current;
    for (int day = 0; f; day++)
    {
        for (int hour = 0; (hour < 24) && f; hour++)
        {

            current.setday(day);
            current.sethour(hour);
            while (!eptr.isEmpty())
            {

                eptr.peek(e);
                if ((e->getTime().getday() == day) && (e->getTime().gethour() == hour))
                {
                    eptr.dequeue(e);
                    if (hour >= 5 && hour <= 23)
                    {

                        e->Execute();


                    }

                }
                else break; // to increment timestep to reach time of events 
            }
            if (hour >= 5 && hour <= 23)
            {



                LoadVIP(current);
                LoadNormal(current);
                LoadSpecial(current);



                MoveaTruck(current);

            }



            movetodelCargo(current);
            Truckmovetoavailorcheckup(current);
            Truckchecktoavail(current);


            //picking one cargo from each cargo type and move it to its moving cargo list
           // waittomoveVcargos(); //for VIP cargo
          //  waittomoveNcargos(); //for normal cargo
          //  waittomoveScargos(); //for special cargo


            //each 5 timesteps move a cargo  of each type from moving cargo lists to delivered list
            //if we reached end of the day move it immediately the next day


            // Printing all info to interface(calling UI function)

            userInterface.Showinfo(day, hour);

            //to stop when there are no more events and delivered isn't empty but all waiting and moving are empty
            //then all cargos are at delivered lists
            f = !(eptr.isEmpty()  && WaitNormal.isEmpty() && WaitSpecial.isEmpty() && WaitVIP.isEmpty()
                && VTMov.isEmpty() && NTMov.isEmpty() && STMov.isEmpty() && VTMain.isEmpty()
                && NTMain.isEmpty() && STMain.isEmpty() && !VTL && !STL && !NTL);



        }


    }
    LinkedQueue<NormalCargo*>Normaldelivered;
    LinkedQueue<VIPCargo*>VIPdelivered;
    LinkedQueue<SpecialCargo*>Specialdelivered;

    this->Seperatedel(Normaldelivered, Specialdelivered, VIPdelivered);
    if (eptr.isEmpty())
        SaveInfo(current,out);



}

void Company::setActiveTime(double a)
{
    ActiveTime = ActiveTime + a;
}

void Company::setUtili(double u)
{

    UComp = UComp + u;
}








/*char Company::gettype(Cargo* c)
{
    NormalCargo* n;
    SpecialCargo* s;
    VIPCargo* v;
    n = dynamic_cast<NormalCargo*>(c);
    s = dynamic_cast<SpecialCargo*> (c);
    v = dynamic_cast<VIPCargo*> (c);
    if (n)
        return 'N';
    else if (s)
        return 'S';
    else if (v)
        return 'V';



}*/








bool Company::InsertPEvent(PreparationEvent* p)
{
    /*for (int i = 0; i < num; i++)
    {

        Event* E = new Event;
        if (!E)
            return false;
        eptr.push(E);

    }*/
    if (p != nullptr)
    {
        eptr.enqueue(p);
        return true;
    }


    return false;

}
LinkedQueue<NormalTrucks*>& Company::GetMaintenceNormaTrucks()
{
    // TODO: insert return statement here
    return NTMain;
}

LinkedQueue<SpecialTrucks*>& Company::GetMaintenceSpecialTrucks()
{
    // TODO: insert return statement here
    return STMain;
}

LinkedQueue<VIPTrucks*>& Company::GetMaintenceVIPTrucks()
{
    // TODO: insert return statement here
    return VTMain;
}

NormalTrucks*& Company::GetLoadingNormaTrucks()
{
    // TODO: insert return statement here
    return NTL;
}

SpecialTrucks*& Company::GetLoadingSpecialTrucks()
{
    // TODO: insert return statement here
    return STL;
}

VIPTrucks*& Company::GetLoadingVIPTrucks()
{
    // TODO: insert return statement here
    return VTL;
}

int Company::NormalLoadExist()
{
    if (NTL)
    {
        return 1;
    }
    else return 0;
}

int Company::VIPLoadExist()
{
    if (VTL)
    {
        return 1;
    }
    else return 0;
}

int Company::SpecialLoadExist()
{
    if (STL)
    {
        return 1;
    }
    else return 0;
}













