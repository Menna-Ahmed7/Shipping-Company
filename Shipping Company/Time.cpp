#include "Time.h"

void Time::sethour(int h)
{
	if (h >= 0 && h <= 23)
		hour = h;
}

void Time::setday(int d)
{
	if (d >= 0)
		day = d;
}

int Time::gethour()
{
	return hour;
}

int Time::getday()
{
	return day;
}

bool Time::operator>(Time t)
{
	if (day > t.getday())
		return true;
	else if (hour > t.gethour())
		return true;
	return false;


}

Time Time::operator-(Time t)
{
	Time result;
	result.setday(day - t.getday());
	result.sethour(hour - t.gethour());
	return result;
}

bool Time::operator==(Time t)
{
	return (getday()==t.getday() && gethour()==t.gethour());
}

