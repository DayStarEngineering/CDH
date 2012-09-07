#include "Timer.h"

double calcTime(timerStruct* timer)
{
	return (double)(((timer->stop.tv_sec) + (((double)timer->stop.tv_usec)/1000000.0)) 
			- ((double)(timer->start.tv_sec) + (((double)timer->start.tv_usec)/1000000.0)));
}
