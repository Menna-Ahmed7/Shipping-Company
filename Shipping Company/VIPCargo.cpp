#include "VIPCargo.h"

int VIPCargo::getpriority()
{
    //priority queue is designed as the key 1 has higher priority than key 5 for example

   int n = 5*((getPT().getday() * 24) + getPT().gethour()) + 5* getDeliveryDist() + 5*getLoadt() - getCost();
   

    return n;


}
