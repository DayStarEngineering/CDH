#ifndef _DATACOLLECTOR_H_
#define _DATACOLLECTOR_H_

#include "../cdhlib/Logger.h"
#include "../cdhlib/Command.h"
#include "../cdhlib/DataWriter.h"
#include "../cdhlib/DataParser.h"
#include "../configmap/configmap.h"
#include <signal.h>

#define NUM_TEMP_SENSORS 8

using namespace std;

struct dataStruct
{
	message msg;
	DataWriter myWriter;
	DataParser myParser;
	int numdpperfile;
	int slpCnt;
};

/*
struct paramStruct
{
	message ss_msg;
	message sem_msg;
	int slpCnt;
};
*/

class dcol
{
public:
	dcol(char* theConfig, volatile bool* Stop);
	~dcol();
	int run();
	Logger myLogger;
private:
	// Calibration Data:
	
	// Temperature sensors in AVR buffer 4:
	//double tempSensors[NUM_TEMP_SENSORS][2];// = {
	//							location			slope (V/degC)  intercept (V)
	//{0.00610,1.89850},	// 1	CMOS Bottom Half	0.00610			1.89850
	//{0.00680,1.82610},	// 2	CMOS Top Half		0.00680			1.82610
	//{0.01990,1.39520},	// 3	Hinge				0.01990			1.39520
	//{0.01900,1.41000},	// 4	Beam				0.01900			1.41000
	//{0.01950,1.40140},	// 5	28->12 V Converter	0.01950			1.40140
	//{0.02100,1.37370},	// 6	EPS Converter		0.02100			1.37370
	//{0.01870,1.41860},	// 7	Frame Grabber?		0.01870			1.41860
	//{0.01890,1.41230}};	// 8	CDH Processor		0.01890			1.41230
	
	// Configuration:
	configmap myConfig;
	int configure();
	
	// Global Vars:
	int numDcol;
	//int numPcol;
	dataStruct* dcolTask;
	//paramStruct* pcolTask;
	SubsystemInterface myInterface;
	
	// Timer control vars:
	timeval time;
	message timerResetMsg;
	pthread_rwlock_t timerLock;
	
	// Threads:
	static void* dataWorker(void*);
	//static void* paramWorker(void*);
	static void* command(void*);
	static void* monitor(void*);
	static void* timer(void*);
	pthread_t monitorThread;
	pthread_t timerThread;
	pthread_t commandThread;
	pthread_t* dataThread;
	//pthread_t* paramThread;
	
	// Thread control vars:
	volatile bool* stop;
	bool commandGood;
	bool timerGood;
	bool* dataGood;
	//bool* paramGood;
	int commandSleep;
	int monitorSleep;
	int timerSleep;
	int timerResetInterval;
	
	// Functions:
	int worker_sleep(int sleeptime, int tskNum);
};

struct workerStruct
{
	dcol* ME;
	int tskNum;
};

#endif  //_DATACOLLECTOR_H
