#if !defined(_PROCESSWATCHDOG_H)
#define _PROCESSWATCHDOG_H

#include "../cdhlib/Logger.h"
#include "../cdhlib/SemaphoreWrapper.h"
#include "../configmap/configmap.h"
#include <map>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <set>
#include <sstream>
#include <time.h>
#include <errno.h>

#define PROCESS 0
#define SEMAPHORE 1
#define SEMTIMEOUT 2

struct Process
{
  char name[256];
  unsigned int check_type;
  int timeout;
  time_t update_time;
  unsigned int semaphore_number;
  string action;
};

class ProcessWatchdog
{
public:
	ProcessWatchdog(char* cfgFile, volatile bool* Stop);
	int run();
	Logger myLogger;
private:
	// Ints:
	int processes;
	int semid;
	int number_of_sem;
	int checkPeriod;
	
	// Objects:
  	Process* processList;
	configmap myConfig;
	
	// Kill bool:
	volatile bool* stop;
	
	// Functions:
	void processConfig();
	bool isRunning(char* name);
	void cleanup();
};

#endif  //_PROCESSWATCHDOG_H
