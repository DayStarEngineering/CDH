
#ifndef _STPRO_H_
#define _STPRO_H_

#include "StartrackerProcessorData.h"
#include "Centroid.h"

using namespace std;

class stpro
{
public:
	// Contructor:
	stpro(char* theConfig, volatile bool* stop);
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
	static void* outData(void*);
	static void* command(void*);
	static void* monitor(void*);
	
	// Thread vars:
	pthread_t inDataThread;
	pthread_t procDataThread;
	pthread_t outDataThread;
	pthread_t monitorThread;
	pthread_t commandThread;
	
	// Functions:
	
	// Private Objects:
	configmap myConfig;
	DataWriter myWriter;
	PortInterface myPort;
	Centroid myProcessor;
	
	// Globally accessed vars:
	image* img;
	centroidList* centList;
	
	// Configurable vars:	
	int numdpperfile;
	bool writeToFile;
	bool writeToPort;
	
	// Thread control vars:
	volatile bool* STOP;
	status imgStatus;
	status centListStatus;
	
	// Thread vars:
	bool inDataGood;
	bool procDataGood;
	bool outDataGood;
	bool commandGood;
	int inDataSleep;
	int procDataSleep;
	int outDataSleep;
	int commandSleep;
	int monitorSleep;
};

#endif  //_STPRO_H_
