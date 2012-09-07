#ifndef _STARTRACKERCOMMANDHANDLER_H_
#define _STARTRACKERCOMMANDHANDLER_H_

#include "../cdhlib/Logger.h"
#include "../cdhlib/Command.h"
#include "../cdhlib/BusInterface.h"
#include "../configmap/configmap.h"
#include <signal.h>
#include <stdio.h>

using namespace std;

class stch
{
public:
	stch(char* theConfig, volatile bool* Stop);
	~stch();
	int run();
	Logger myLogger;
	
private:
	// Configuration:
	configmap myConfig;
	int configure();
		
	// Communication Vars:
	BusInterface myBus;
	int semid;
	
	// Control Vars:
	int runSleep;
	volatile bool* stop;
};



#endif  //_STARTRACKERCOMMANDHANDLER_H
