#pragma once
class Time
{
	int hour;
	int day;

public:
	void sethour(int h);
	void setday(int d);
	int gethour();
	int getday();
	bool operator > (Time t);
	Time operator - (Time t);
	bool operator == (Time t);


};

