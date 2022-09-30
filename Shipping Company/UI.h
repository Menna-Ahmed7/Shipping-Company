#pragma once


#include "Company.h"
#include "VIPTrucks.h"
#include "NormalTrucks.h"
#include "SpecialTrucks.h"
#include "PreparationEvent.h"
#include<iostream>
using namespace std;
enum class  modes { interactive, stepbystep, silent };
//interactive   0
//Step by step 1
//silent 2
using namespace std;
class UI
{
public:
	Company* C;
	modes currentmode;


public:
	UI(Company* c);
	void Showinfo(int day, int hour);         // for interactive and step by step modes
	void silentmode();
	void choosemode();



};

