#ifndef _SUBSYSTEMMESSENGER_H_
#define _SUBSYSTEMMESSENGER_H_

#include "../cdhlib/Logger.h"
#include "../cdhlib/MsgQueueWrapper.h"
#include "../cdhlib/SubsystemInterface.h"
#include "../cdhlib/SemaphoreWrapper.h"
#include "../configmap/configmap.h"
#include <signal.h>
#include <string>

using namespace std;

class ssm
{
public:
	ssm(char* theConfig, volatile bool* Stop);
	~ssm();
	int run();
	Logger myLogger;
private:
	// Configuration:
	configmap myConfig;
	int configure();
	
	// Global Vars:
	SubsystemInterface myInterface; // make a configurable array eventually
	MsgQueueWrapper msgQueueWrapper;
	
	// Threads:
	int numWorkers;
	static void* worker(void*);
	static void* monitor(void*);
	pthread_t* workerThread;
	pthread_t monitorThread;
	
	// Thread control vars:
	volatile bool* stop;
	bool* workerGood;
	int monitorSleep;
	
	// Functions:
	string printError(int err);
};

struct workerStruct
{
	ssm* ME;
	int workerNum;
};

#endif  //_SUBSYSTEMMESSENGER_H
