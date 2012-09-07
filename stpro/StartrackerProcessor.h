
#ifndef _STPRO_H_
#define _STPRO_H_

#include "StartrackerProcessorDefines.h"
#include "TriBuffer.h"
#include <iostream>
#include <fstream>

using namespace std;

// Processor class:
class stpro
{
public:
	// Contructor:
	stpro(char* theConfig, volatile pthread_mutex_t* mutex_signal, volatile timeval* global_timer, volatile bool* Stop);
	~stpro();
	
	// Public functions:
	int run();
	int configure();
	
	// Loggers:
	Logger myLogger;

private:
	// Threads:
	static void* inData(void*);
	static void* procData(void*);
/*	static void* outData(void*);  */
	static void* command(void*);
	static void* monitor(void*);
	
	// Thread vars:
	pthread_t inDataThread;
	pthread_t procDataThread;
/*	pthread_t outDataThread; */
	pthread_t monitorThread;
	pthread_t commandThread;
	
	// Private Shared Objects:
	configmap myConfig;
	DataWriter myWriter;
	PortInterface myPort;
	Centroid myProcessor;
	centroidList centList;
	TriBuffer ImageIndexer;
	MILWrapper MilWrapper;
	MILDigitizer MilDigitizer;
	MILImage MilImage;
	image* img;
	#if DEBUG_MODE == TIMETEST
	MILDisplay MilDisplay;   
	MILImage MilTestImage;
	timerStruct totalTimer[3];
	timerStruct lateTimer[3];                  
	#endif
	
	// Functions:
	void setTimer(timeval newinterval);
	int outputData(centroidList* centList);
	
	// Globally accessed vars:
	int dpremain;
	
	// Configurable vars:
	int numdpperfile;
	bool writeToFile;
	bool writeToPort;
	
	// Thread control vars:
	volatile bool* stop;
	bool inDataGood;
	bool procDataGood;
/*	bool outDataGood; */
	bool commandGood;
	
	// Sleep vars:
	int commandSleep;
	int monitorSleep;
	
	// Thread synchronization vars:
	volatile timeval* timer;
	pthread_mutex_t sigProcData;
	volatile pthread_mutex_t* sigInData;
	
	// Image vars:
	int xlen;
	int ylen;
};

#if DEBUG_MODE == TIMETEST
void printTimes(int num, timeval &startInput, timeval &startProcess, timeval &startOutput, timeval &stopAll);
double calcTime(timerStruct* timer);
int loadTestImage(MIL_ID testimage, unsigned short xpix, unsigned short ypix);
#endif


#endif  //_STPRO_H_
