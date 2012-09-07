#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "../cdhlib/Logger.h"
#include "../cdhlib/MsgQueueWrapper.h"
#include "../cdhlib/SubsystemInterface.h"
#include "../cdhlib/SemaphoreWrapper.h"
#include "../cdhlib/Command.h"
#include "../cdhlib/GlobalVar.h"
#include "../configmap/configmap.h"
#include <signal.h>
#include <string>

using namespace std;

struct schedEvent
{
	int num;
	int count;
	int sleep;
	command cmd;
};

class sched
{
public:
	sched(char* theConfig, volatile bool* Stop);
	~sched();
	int run();
	Logger myLogger;
	
private:
	// Configuration:
	configmap myConfig;
	int configure();
	
	// Global Vars:
	CommandWrapper commandWrapper;
	
	// Threads:
	int numEvents;
	schedEvent* event;
	
	// Thread control vars:
	volatile bool* stop;
	int semid;
	int sched_semid;
	int eventCounter;
	int currEvent;
	const char* eventCounterFname;
	const char* currEventFname;
	
	// Functions:
	int sched_sleep(int sleeptime);
};

#endif  //_SCHEDULER_H
