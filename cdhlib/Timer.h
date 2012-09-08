
#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/time.h>

using namespace std;

struct timerStruct
{
	timeval start;
	timeval stop;
};

double calcTime(timerStruct* timer);

#endif
