#ifndef _HOUSEKEEPER_H_
#define _HOUSEKEEPER_H_

#include "../cdhlib/Logger.h"
//#include "../cdhlib/SemaphoreWrapper.h"
//#include "../cdhlib/DataWriter.h"
//#include "../cdhlib/PortInterface.h"
#include "../cdhlib/Command.h"
#include "../configmap/configmap.h"
#include <signal.h>
#include <map>
//#include <iostream>
//#include <fstream>

using namespace std;

struct taskStruct
{
	commandData cmd;
	//int proc; // why not just use a commandData struct here instead of proc and sem... that way you just pass that to execute??
	//int sem;
	unsigned int slpCnt;
	unsigned int highVal;
	unsigned int lowVal;
	unsigned int failCnt;
	unsigned int highActn;
	unsigned int lowActn;
};

class hskpr
{
public:
	// Contructor:
	hskpr(const char* theConfig, volatile bool* Stop);
	~hskpr();
	
	// Public functions:
	int run();
	
	// Loggers:
	Logger myLogger;
	
private:
	// Configuration:
	configmap myConfig;
	int configure();
	
	//DataWriter myWriter;
	//PortInterface myPort;
	
	// Globally accessed vars:
	int numTasks;
	int numActions;
	commandData* action;
	taskStruct* task;
	
	// Threads:
	static void* worker(void*);
	static void* command(void*);
	static void* monitor(void*);
	pthread_t monitorThread;
	pthread_t commandThread;
	pthread_t* workerThread;
	
	// Thread control vars:
	volatile bool* stop;
	bool commandGood;
	bool* workerGood;
	int commandSleep;
	int monitorSleep;
	//pthread_mutex_t inData;
	//pthread_mutex_t outFile;
	//pthread_mutex_t outPort;
	
	// Functions:
	
};

struct workerStruct
{
	hskpr* ME;
	int tskNum;
};

#endif  //_HOUSEKEEPER_H
