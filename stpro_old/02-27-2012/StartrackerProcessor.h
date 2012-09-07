
#ifndef _STPRO_H_
#define _STPRO_H_

#include "StartrackerProcessorData.h"
#include "Centroid.h"
#include <iostream>
#include <fstream>

using namespace std;

// Processor class:
class stpro
{
public:
	// Contructor:
	stpro(char* theConfig, volatile bool* Stop);
	~stpro();
	
	// Public functions:
	int run();
	int configure();
	
	// Loggers:
	Logger myLogger;

private:
	// Threads:
	static void* worker(void*);
	static void* command(void*);
	static void* monitor(void*);
	pthread_t monitorThread;
	pthread_t commandThread;
	pthread_t* workerThread;
	
	// Functions:
	int inputData(image* img);
	int outputData(centroidList* centList);
	#if DEBUG_MODE == 1
	void printTimes(int num, timeval &startInput, timeval &startProcess, timeval &startOutput, timeval &stopAll);
	int loadTestImage();
	#endif
	
	// Private Objects:
	configmap myConfig;
	DataWriter myWriter;
	PortInterface myPort;
	Centroid myProcessor;
	
	// Globally accessed vars:
	int numWorkers;
	int dpremain;
	
	// Configurable vars:
	int numdpperfile;
	bool writeToFile;
	bool writeToPort;
	
	// Thread control vars:
	volatile bool* stop;
	bool commandGood;
	bool* workerGood;
	int commandSleep;
	int monitorSleep;
	pthread_mutex_t inData;
	pthread_mutex_t outFile;
	pthread_mutex_t outPort;
	
	// Image vars:
	#if DEBUG_MODE == 1 //timing test
	image* testImg;
	#endif
	int xlen;
	int ylen;
	double xfov;  
	double yfov;
	int maxStarCount;
};

struct workerStruct
{
	stpro* ME;
	int num;
};

#endif  //_STPRO_H_
