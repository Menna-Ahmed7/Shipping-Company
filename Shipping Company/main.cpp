#include"Company.h"
#include<iostream>
using namespace std;
int main()
{
	Company C;
	cout << "Please Enter the name of the input file " << endl;
	string s, o;
	cin >> s;
	cout << "Please Enter the name of the output file " << endl;
	cin >> o;
	C.SimulatorFunction(s,o);
	


	return 0;
}