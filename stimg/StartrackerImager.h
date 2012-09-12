
#ifndef _STIMG_H_
#define _STIMG_H_

#include "StartrackerImagerDefines.h"
#include <iostream>
#include <fstream>

using namespace std;

// Processor class:
class stimg
{
public:
	// Contructor:
	stimg(char* theConfig, volatile pthread_mutex_t* mutex_signal, volatile timeval* global_timer, volatile bool* Stop);
	~stimg();
	
	// Public functions:
	int run();
	int configure();
	
	// Loggers:
	Logger myLogger;

private:
	// Threads:
	static void* inData(void*);
	static void* command(void*);
	static void* monitor(void*);
	
	// Thread vars:
	pthread_t inDataThread;
	pthread_t monitorThread;
	pthread_t commandThread;
	
	// Private Shared Objects:
	configmap myConfig;
	MILWrapper MilWrapper;
	//MILDigitizer MilDigitizer;
	MILDigitizer2 MilDigitizer;
	//MILDigitizer MilDigitizer0;
	//MILDigitizer MilDigitizer1;
	int digMode;
	MILImage MilImage0;
	MILImage MilImage1;
	image img;
	int semid;
	
	// Functions:
	void setTimer(timeval newinterval);
	
	// Thread control vars:
	volatile bool* stop;
	bool inDataGood;
	bool commandGood;
	
	// Semaphores:
	bool capture; // 1 - capture on / off
	int seqcnt;   // 2 - image sequence number
	int imgcnt;   // 3 - image number within the current sequence
	
	// Sleep vars:
	int commandSleep; // us
	int monitorSleep; // us
	int schedulerSleep; // us
	
	// Scheduling vars:
	int captureDuration; // s
	int sleepDuration;   // s
	
	// Configurable vars:
	string file_path[3];
	int file_path_index;
	
	// Thread synchronization vars:
	volatile timeval* timer;
	volatile pthread_mutex_t* sigInData;
};

#endif  //_STIMG_H_
