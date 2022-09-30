#include "Event.h"

Event::Event(Company* c)
{
	M = c;
}

void Event::setTime(Time t)
{
	etime.setday(t.getday());
	etime.sethour(t.gethour());


}

Time Event::getTime()
{
	return etime;
}




