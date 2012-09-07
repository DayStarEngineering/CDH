#include "DataCollector.h"

dcol::dcol(char* theConfig, volatile bool* Stop): myLogger("DCOL")
{
	
	// Set thread signal control pointer:
	stop = Stop;
	
	dataThread = NULL;
	// paramThread = NULL;
	dataGood = NULL;
	// paramGood = NULL;
	dcolTask = NULL;
	// pcolTask = NULL;
	
	// Initialize timer RW mutex:
	pthread_rwlock_init(&timerLock, NULL);
	
	// Read config:
	myConfig.readfile(theConfig);
	
	// DCOL LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"CONSTRUCTOR: Data Collector");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure() != 0)
	{
		myLogger.lw(ERROR,"DCOL not configured correctly!");
		exit(-1);
	}
	else
	{
		myLogger.lw(INFO,"DCOL correctly configured.");
	}
}

dcol::~dcol()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Destroy timer RW mutex:
	pthread_rwlock_destroy(&timerLock);
	
	// Deallocate Memory:
	if (dataThread != NULL)
	{
		delete [] dataThread;
		dataThread = NULL;
	}
	/*
	if (paramThread != NULL)
	{
		delete [] paramThread;
		paramThread = NULL;
	}
	*/
	if (dataGood != NULL)
	{
		delete [] dataGood;
		dataGood = NULL;
	}
	/*
	if (paramGood != NULL)
	{
		delete [] paramGood;
		paramGood = NULL;
	}
	*/
	if (dcolTask != NULL)
	{
		delete [] dcolTask;
		dcolTask = NULL;
	}
	
	/*
	if (pcolTask != NULL)
	{
		delete [] pcolTask;
		pcolTask = NULL;
	}
	*/
	
	myLogger.lw(INFO,"DESTRUCTOR: DCOL TERMINATED.");
	myLogger.close();
}

int dcol::configure()
{
	// Initialize calibration data:
	// Temperature sensors in AVR buffer 4:
	/*
	double tempSensors[NUM_TEMP_SENSORS][2] = {
	//							location			slope (V/degC)  intercept (V)
	{0.00610,1.89850},	// 1	CMOS Bottom Half	0.00610			1.89850
	{0.00680,1.82610},	// 2	CMOS Top Half		0.00680			1.82610
	{0.01990,1.39520},	// 3	Hinge				0.01990			1.39520
	{0.01900,1.41000},	// 4	Beam				0.01900			1.41000
	{0.01950,1.40140},	// 5	28->12 V Converter	0.01950			1.40140
	{0.02100,1.37370},	// 6	EPS Converter		0.02100			1.37370
	{0.01870,1.41860},	// 7	Frame Grabber?		0.01870			1.41860
	{0.01890,1.41230}};	// 8	CDH Processor		0.01890			1.41230
	*/
	
	multimap<string,string>::iterator p;
	
	// Get thread info:
	numDcol         = atoi(myConfig["num_dcol"].c_str());
	dataThread      = new pthread_t[numDcol];
	dataGood        = new bool[numDcol];
	//numPcol         = atoi(myConfig["num_pcol"].c_str());
	//paramThread     = new pthread_t[numPcol];
	//paramGood       = new bool[numPcol];
	
	// Get sleep times:
	commandSleep       = atoi(myConfig["command_sleep"].c_str());
	monitorSleep       = atoi(myConfig["monitor_sleep"].c_str());
	timerSleep		   = atoi(myConfig["timer_sleep"].c_str());
	timerResetInterval = atoi(myConfig["timer_reset_interval"].c_str());
	
	// Get timer reset command:
	timerResetMsg.cmd.proc = EPS;
	timerResetMsg.cmd.type = SET;
	timerResetMsg.cmd.arg1 = atoi(myConfig["timer_param"].c_str());
	timerResetMsg.cmd.arg2 = atoi(myConfig["timer_val"].c_str());
	
	// Data writing info:
	string partsdir = myConfig["partsdir"];
	string donedir  = myConfig["donedir"];
	
	// Move everything in parts to done to start:
	int ret;
	string moveStr = "mv " + partsdir + "/* " + donedir;
	(void) (ret = system(moveStr.c_str()));
	
	// Get data collector info:
	if (numDcol <= 0)
	{
		myLogger.lw(ERROR,"CONFIG: Invalid number of dcol: %d",numDcol);
		return -1;
	}
	else
	{
		myLogger.lw(INFO,"CONFIG: Reading %d dcol.",numDcol);
	}
	dcolTask = new dataStruct[numDcol];
	
	// Load all data collectors to an array of task structs:
	p = myConfig.find("dcol");
	int ind = 0;
	int currNum = 0;
	char buffer[MAXLEN];
	//int tempBinaryMode;
	writerData tempWriteData;
	//calibrationData tempCalibrationData;
	//tempCalibrationData.slope = NULL;
	//tempCalibrationData.intercept = NULL;
	parserData tempParseData;
	if (p != myConfig.end())
	{
		do
		{
			sscanf((*p).second.c_str(),"%d %hhu %hu %d %d %d %s %d",
			  &currNum,
			  &dcolTask[ind].msg.cmd.arg1,
			  &dcolTask[ind].msg.cmd.arg2,
			  &tempParseData.vvlen,
			  &tempParseData.bpv,
			  &dcolTask[ind].numdpperfile,
			  (char*)&buffer,
			  &dcolTask[ind].slpCnt);
			
			// Error check:
			if (currNum >= numDcol) exit(-1);
			
			// Fill dcol message:
			dcolTask[ind].msg.cmd.proc = EPS;
			dcolTask[ind].msg.cmd.type = DATA;
			
			// Configure Writer:
			/*
			if (tempBinaryMode == 1)
				tempWriteData.binaryMode = true;
			else if (tempBinaryMode == 0)
				tempWriteData.binaryMode = false;
			else
			{
				// Set to binary as default and log as a warning:
				tempWriteData.binaryMode = true;
				myLogger.lw(WARNING,"CONFIG: dcol task %d did not indicate binary input for binaryMode.",ind);
			}
			*/
			tempWriteData.partsdir = partsdir;
			tempWriteData.donedir = donedir;
			tempWriteData.filestr = buffer;
			
			/*
			if (dcolTask[ind].cmd.arg1 == 4) //buffer 4 is temp sensors
			{
				if (tempCalibrationData.numSensors == NUM_TEMP_SENSORS)
				{
					tempCalibrationData.slope = new double[NUM_TEMP_SENSORS];
					tempCalibrationData.intercept = new double[NUM_TEMP_SENSORS];
					
					for (int i = 0; i < NUM_TEMP_SENSORS; i++)
					{
						tempCalibrationData.slope[i] = tempSensors[i][0];
						tempCalibrationData.intercept[i] = tempSensors[i][1];
					}
					myLogger.lw(INFO,"CONFIG: Temp sensors calibrated.");
					
					// Configure writer:
					//dcolTask[ind].myWriter.configure(tempWriteData,tempCalibrationData);
					
					// Deallocate Memory:
					//if (tempCalibration.slope != NULL)
					//{
					//	delete [] tempCalibration.slope;
					//	tempCalibration.slope = NULL;
					//}
					//if (tempCalibration.intercept != NULL)
					//{
					//	delete [] tempCalibration.intercept;
					//	tempCalibration.intercept = NULL;
					//}
					
				}
				else
				{
					tempCalibrationData.numSensors = 0;
					myLogger.lw(ERROR,"CONFIG: Invalid number of temp sensors indicated.");
					
					// Configure writer:
					//dcolTask[ind].myWriter.configure(tempWriteData,tempCalibrationData);
				}
			}*/
			if( dcolTask[ind].myWriter.configure(tempWriteData/*,tempCalibrationData*/) == -1)
			{
				myLogger.lw(ERROR,"CONFIG: Writer not configured properly.");
				return -1;
			}
			
			// Configure Parser:
			tempParseData.max_dp = dcolTask[ind].msg.cmd.arg2;
			if( dcolTask[ind].myParser.configure(tempParseData) == -1)
			{
				myLogger.lw(ERROR,"CONFIG: Writer not configured properly.");
				return -1;
			}
			 
			// Print config:
			myLogger.lw(DEBUG,"CONFIG: Task %d recorded as message: %svvlen: %hhu bpv: %hhu numdpperfile: %d filestr: %s sleepcnt: %d",
			  ind,
			  dcolTask[ind].msg.toString(),
			  tempParseData.vvlen,
			  tempParseData.bpv,
			  dcolTask[ind].numdpperfile,
			  tempWriteData.filestr.c_str(),
			  dcolTask[ind].slpCnt);
			
			++p;
			++ind;
		}
		while (p != myConfig.upper_bound("dcol"));
	}
	
	// Get param collector info:
	/*
	if (numPcol <= 0)
		myLogger.lw(ERROR,"CONFIG: Invalid number of pcol: %d",numPcol);
	else
		myLogger.lw(INFO,"CONFIG: Reading %d pcol.",numPcol);
	pcolTask = new paramStruct[numPcol];
	
	// Load all param collectors to an array of task structs:
	p = myConfig.find("pcol");
	ind = 0;
	
	if (p != myConfig.end())
	{
		do
		{
			sscanf((*p).second.c_str(),"%d %hhu %hhu %hhu %d",
			  &pcolTask[ind].tskNum,
			  &pcolTask[ind].ss_msg.cmd.arg1,
			  &pcolTask[ind].sem_msg.cmd.arg1,
			  &pcolTask[ind].slpCnt);
			
			pcolTask[ind].ss_msg.cmd.proc = EPS;
			pcolTask[ind].ss_msg.cmd.type = GET;
			pcolTask[ind].ss_msg.cmd.arg2 = 0xFFFF;
			
			pcolTask[ind].sem_msg.cmd.proc = DCOL;
			pcolTask[ind].sem_msg.cmd.type = SET;
			pcolTask[ind].sem_msg.cmd.arg2 = 0xFFFF;
			
			if (pcolTask[ind].tskNum >= numPcol) exit(-1);
			 
			// Print config:
			myLogger.lw(DEBUG,"CONFIG: Task %d recorded as ss_msg: %s\n sem_msg: %s\n sleep: %d",
			  pcolTask[ind].tskNum,
			  pcolTask[ind].ss_msg.toString(),
			  pcolTask[ind].sem_msg.toString(),
			  pcolTask[ind].slpCnt);
			
			++p;
			++ind;
		}
		while (p != myConfig.upper_bound("pcol"));
	}
	*/

	return 0;
}

int dcol::run()
{
	myLogger.lw(INFO,"RUN: Starting DCOL Run...");
	
	// Setup a thread attribute:
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc=0;
	
	// Setup and start the timer thread:
	myLogger.lw(INFO,"RUN: Starting timer thread");
	rc = pthread_create(&timerThread, &attr, dcol::timer, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Give timer a second to get up and running:
	usleep(1000000);
	
	// Setup and start the command thread:
	myLogger.lw(INFO,"RUN: Starting command thread");
	rc = pthread_create(&commandThread, &attr, dcol::command, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, dcol::monitor, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start all dataWorker threads:
	workerStruct* dataTemp = NULL;
	dataTemp = new workerStruct[numDcol];
	for (int i = 0; i < numDcol; i++)
	{
		myLogger.lw(INFO,"RUN: Creating dataWorker thread: %d",i);
		dataTemp[i].tskNum = i;
		dataTemp[i].ME = this;
		rc = pthread_create(&dataThread[i], NULL, dcol::dataWorker, (void*) &dataTemp[i]);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN %d: Bad return code from pthread_create() - value is %d\n", i, rc);
			exit(-1);
		}
	}
	
	// Setup and start all paramWorker threads:
	/*
	workerStruct* paramTemp = NULL;
	paramTemp = new workerStruct[numPcol];
	for (int i = 0; i < numPcol; i++)
	{
		myLogger.lw(INFO,"RUN: Creating paramWorker thread: %d",i);
		paramTemp[i].tskNum = i;
		paramTemp[i].ME = this;
		rc = pthread_create(&paramThread[i], NULL, dcol::paramWorker, (void*) &paramTemp[i]);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN %d: Bad return code from pthread_create() - value is %d\n", i, rc);
			exit(-1);
		}
	}
	*/
	
	pthread_attr_destroy(&attr);
	
	// Joining our threads until we are killed by a signal:
	rc = pthread_join(commandThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	
	rc = pthread_join(timerThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	
	rc = pthread_join(monitorThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	
	for (int i = 0; i < numDcol; i++)
	{
		rc = pthread_join(dataThread[i], NULL);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN: return code from pthread_join() - value is %d\n", rc);
			exit(-1);
		}
	}
	
	/*
	for (int i = 0; i < numPcol; i++)
	{
		rc = pthread_join(paramThread[i], NULL);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN: return code from pthread_join() - value is %d\n", rc);
			exit(-1);
		}
	}
	*/
	
	// Cleaning up:
	if (dataTemp != NULL)
	{
		delete [] dataTemp;
		dataTemp = NULL;
	}
	
	/*
	if (paramTemp != NULL)
	{
		delete [] paramTemp;
		paramTemp = NULL;
	}
	*/
	
	myLogger.lw(WARNING,"RUN: All threads have terminated. Dying gracefully.");
	
	return 0;
}

void* dcol::dataWorker(void* arg)
{
	// Get global vars from dcol instance:
	int tskNum = ((workerStruct*) arg)->tskNum;
	dcol* ME = ((workerStruct*) arg)->ME;
	Logger* logger = &(ME->myLogger);
	dataStruct* myTask = &(ME->dcolTask[tskNum]);
	message* msg = &(myTask->msg);
	
	// Local vars:
	CommandWrapper commandWrapper(DCOL);
	unsigned int dpremain = 0;
	unsigned char numdp;
	int ret;
	
	// Time vars:
	timeval prevTime, currTime;
	
	// Stating up...
	logger->lw(INFO,"DATAWORKER %d: Started.",tskNum);
	
	// Grab copy of the initial system time:
	pthread_rwlock_rdlock(&(ME->timerLock));
	prevTime = ME->time;
	pthread_rwlock_unlock(&(ME->timerLock));
	
	while (!(*ME->stop))
	{	
		// Check if we have filled the file:
		if (dpremain == 0)
		{
			logger->lw(INFO,"DATAWORKER %d: File is full. Opening new one.",tskNum);
			
			// Close current file:
			myTask->myWriter.closeFile();
			
			// Open a new file for writting:
			myTask->myWriter.openFile();
		
			// Reset datapoints remaining:
			dpremain = myTask->numdpperfile;
		}
		
		// Change requested data points to match data points remaining:
		if (dpremain < msg->cmd.arg2)
		{
			numdp = dpremain;
		}
		else
		{
			numdp = msg->cmd.arg2;
		}
		
		logger->lw(INFO,"DATAWORKER %d: Still needs to collect %d data points. Requesting %d.",tskNum,dpremain,numdp);
		
		// Request data from subsystem:
		logger->lw(INFO,"DATAWORKER %d: sending: %s",tskNum,msg->toString());		
		commandWrapper.execute(msg);
		if(msg->rsp.ret != 1)
		{
			logger->lw(ERROR,"DATAWORKER %d: Subsystem returned with error %x",tskNum, msg->rsp.ret);
			
			// Sleep and continue:
 			if( ME->worker_sleep(myTask->slpCnt, tskNum) == -1 )
 				break;
 				
 			continue;
		}
		//logger->lw(INFO,"DATAWORKER %d: %d bytes recieved: %s",tskNum,msg->rsp.length,msg->toString());		
		
		// Grab copy of the current system time:
		pthread_rwlock_rdlock(&(ME->timerLock));
		currTime = ME->time;
		pthread_rwlock_unlock(&(ME->timerLock));
		
		// Parse Data:
		if( ( ret = myTask->myParser.parseData(prevTime, currTime, (unsigned char*) &(msg->rsp.msg), msg->rsp.length) ) == -1)
		{
			// Log error:
			logger->lw(ERROR,"DATAWORKER %d: Error returned from parseData().",tskNum);
			
			// Sleep and continue:
 			if( ME->worker_sleep(myTask->slpCnt, tskNum) == -1 )
 				break;
 				
 			continue;
		}

		// Decrease DP remaining by the number of DP found in parseData()
		dpremain -= ret;	
		logger->lw(INFO,"DATAWORKER %d: Parsed %d datapoints successfully. Writing data to file.",tskNum,ret,dpremain);		
		
		// Write data to file:
		myTask->myWriter.writeDataSet(&(myTask->myParser));
		
		// Sleep:
 		if( ME->worker_sleep(myTask->slpCnt, tskNum) == -1 )
 			break;
	}
	
	// Kill with grace:
	logger->lw(WARNING,"DATAWORKER %d: Exiting...",tskNum);
	return NULL;
}

int dcol::worker_sleep(int sleeptime, int tskNum)
{
	// Timers:
	timeval currTime;
	timeval sleepStartTime;
	gettimeofday(&currTime, NULL);
	sleepStartTime = currTime;
	
	myLogger.lw(SPAM,"SLEEP %d: Taking a nap for %d seconds", tskNum, sleeptime );
	
	do
	{
		// Checking for signal:
		if(*stop)
			return -1;
			
		// Kick monitor:
		//myLogger.lw(SPAM,"SLEEP %d: Kicking monitor",tskNum);
		dataGood[tskNum] = true;
		
		//myLogger.lw(SPAM,"SLEEP %d: Sleeping for %d more seconds.", tskNum, sleeptime - (currTime.tv_sec - sleepStartTime.tv_sec) );

		// Sleep:
 		usleep(1000000);
 		
 		// Get the current time:
		gettimeofday(&currTime, NULL);
	} while( ((currTime.tv_sec - sleepStartTime.tv_sec) < sleeptime) || (sleeptime == -1)  );
	
	return 0;
}

/*
void* dcol::paramWorker(void* arg)
{
	// Get global vars from dcol instance:
	int tskNum = ((workerStruct*) arg)->tskNum;
	dcol* ME = ((workerStruct*) arg)->ME;
	Logger* logger = &(ME->myLogger);
	paramStruct* myTask = &(ME->pcolTask[tskNum]);
	message* msg = &(myTask->msg);
	
	// Local vars:
	CommandWrapper commandWrapper(DCOL);
	unsigned short theParam;
	
	// Stating up...
	logger->lw(INFO,"PARAMWORKER %d: Started.",tskNum);
	
	while (!(*ME->stop))
	{
		// Kick monitor:
		logger->lw(SPAM,"PARAMWORKER %d: Kicking monitor.",tskNum);
		ME->paramGood[tskNum] = true;
		
		// Request param from subsystem:
		commandWrapper.execute(msg);
		if(msg->rsp.ret != 1)
		{
			logger->lw(ERROR,"DATAWORKER %d: Subsystem returned with error %x",tskNum, msg->rsp.ret);
			
			// Sleep and continue:
 			usleep(myTask->slpCnt);
 			continue;
		}
		
		// Parse parameter:
		if (parseParam(theParam, (unsigned char*) &(msg->rsp.msg), msg->rsp.length) == -1)
		{
			// Log error:
			logger->lw(ERROR,"PARAMWORKER %d: Error returned from parseParam()",tskNum);
			
			// Sleep and continue:
 			usleep(myTask->slpCnt);
 			continue;
		}

		// Store the parameter to the approriate semaphore:
		commandWrapper.execute(msg);
		if(msg->rsp.ret != 1)
		{
			logger->lw(ERROR,"DATAWORKER %d: Setting dcol sem returned with error %x",tskNum, msg->rsp.ret);
			
			// Sleep and continue:
 			usleep(myTask->slpCnt);
 			continue;
		}
		
		// Sleep:
 		usleep(myTask->slpCnt);
	}
	
	// Kill with grace:
	logger->lw(WARNING,"PARAMWORKER %d: Exiting...",tskNum);
	return NULL;
}
*/
void* dcol::timer(void* arg)
{
	// Get global vars:
	dcol* ME = (dcol*) arg;
	Logger* logger = &(ME->myLogger);
	message* msg = &(ME->timerResetMsg);
	
	// Start:
	logger->lw(INFO,"TMR: Starting up...");
	
	// Local Vars:
	CommandWrapper commandWrapper(DCOL);
	int time_since_reset;
	
	// Timers:
	timeval currTime;
	timeval lastResetTime;
	lastResetTime.tv_sec = 0; // send a reset right away
		
	while( !(*ME->stop) )
	{
		// Kick monitor:
		logger->lw(SPAM,"TMR: Kicking monitor.");
		ME->timerGood = true;
		
		// Get the current time:
		gettimeofday(&currTime, NULL);
		time_since_reset = currTime.tv_sec - lastResetTime.tv_sec;
		
		// Reset timer yet?
		//logger->lw(INFO,"TMR: Time since last reset: %d s, Reset when %d s is reached.",time_since_reset,ME->timerResetInterval);
		if ( time_since_reset >= ME->timerResetInterval)
		{	
			// Send timer reset command to subsystem:
			commandWrapper.execute(msg);
			if(msg->rsp.ret != 1)
			{
				logger->lw(ERROR,"TMR: Reseting subsystem timer returned with error %x", msg->rsp.ret);
			}
			else
			{
				// Set the new system time with protection:
				pthread_rwlock_wrlock(&(ME->timerLock));
				gettimeofday(&(ME->time), NULL);
				pthread_rwlock_unlock(&(ME->timerLock));
				logger->lw(SPAM,"TMR: Timer reset successful. Subsystem time is now counting from %d.",ME->time.tv_sec);
								
				// Reset total sleep count on a successful time reset:
				lastResetTime = currTime;
			}
		}

		// Sleep:
 		usleep(ME->timerSleep);
	}
	
	// Kill with grace:
	logger->lw(WARNING, "TMR: Exiting...");
	return NULL;
}

void* dcol::command(void* arg)
{
	// Get global vars:
	dcol* ME = (dcol*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");
	
	// Configure semaphore wrapper:
	//int	semid = initSemaphores(DCOL_PATH,NUM_DCOL);
	
	// Starting conditions:
	//setSemaphore(semid,1,0);              // capture off
	//ME->seqcnt = getSemaphore(semid, 2);  // restore sequence count
	//setSemaphore(semid,2,0);              // reset image counter
	
	// Create command struct
	while( !(*ME->stop) )
	{
		// Kick monitor:
		ME->commandGood = true;
		
		// Update internal semaphores:
		//ME->capture = (bool) getSemaphore(semid, 1);
		
		// Update external semaphores:
		//setSemaphore(semid,2,ME->seqcnt);
		//setSemaphore(semid,3,ME->imgcnt);
		
		// Sleep:
 		usleep( ME->commandSleep );
	}
	
	logger->lw(WARNING, "CMD: Exiting...");
	return 0;
}

void* dcol::monitor(void* arg)
{
	// Get global vars:
	dcol* ME = (dcol*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"MONITOR: Starting up...");
	
	// Local vars:
	int semid;
	bool allGood = false;
	
	// Get semid:
	if ((semid = getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
    {
        logger->lw(WARNING,"MONITOR: Unable to grab semaphores (%s)", KICK_PATH);
    }
    else
    {
    	logger->lw(SPAM,"MONITOR: Got semid: %d",semid);
    }
	
	// Set all booleans to false to start:
	for (int i = 0; i < ME->numDcol; i++)
	{
		ME->dataGood[i] = false;
	}
	/*
	for (int i = 0; i < ME->numPcol; i++)
	{
		ME->paramGood[i] = false;
	}
	*/
	ME->commandGood = false;
	ME->timerGood = false;
	
	// Check loop:   
	while ( !(*ME->stop) )
	{	
 		// Reset:
 		allGood = true;
 		
 		//logger->lw(SPAM,"MONITOR: Who kicked me?");
 		 				
 		// Check all threads:
 		for (int i = 0; i < ME->numDcol; i++)
 		{
 			if (!ME->dataGood[i])
 			{
 				//logger->lw(WARNING,"MONITOR: DATAWORKER %d has not yet kicked.",i);
 				allGood = false;
 				break;
 			}
 		}
 		/*
 		for (int i = 0; i < ME->numPcol; i++)
 		{
 			if (!ME->paramGood[i])
 			{
 				logger->lw(WARNING,"MONITOR: PARAMWORKER %d has not yet kicked.",i);
 				allGood = false;
 				break;
 			}
 		}
 		*/
 		if (!ME->commandGood)
 		{
 			//logger->lw(WARNING,"MONITOR: COMMAND has not yet kicked.");
 			allGood = false;
 		}
 		
 		if (!ME->timerGood)
 		{
 			//logger->lw(WARNING,"MONITOR: TIMER has not yet kicked.");
 			allGood = false;
 		}
 		
 		// Kick:
 		if (allGood)
 		{
 			logger->lw(DEBUG,"MONITOR: All threads running well... Kicking the dog.");
 			
 			if ((setSemaphore(semid,DCOL_KICK_SEM,1)) == -1)
 			{
 				logger->lw(ERROR,"MONITOR: Unable to set semaphore!");
 				if ((semid = getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
		        {
		            logger->lw(ERROR,"MONITOR: Unable to grab semaphores (%s)", KICK_PATH);
		        }
 			}
 			else
 			{	
 				// Reset kicks:
 				ME->commandGood = false;
 				ME->timerGood = false;
 				
 				for (int i = 0; i < ME->numDcol; i++)
		 		{
		 			ME->dataGood[i] = false;
		 		}
		 		/*
		 		for (int i = 0; i < ME->numPcol; i++)
		 		{
		 			ME->paramGood[i] = false;
		 		}
		 		*/
		 	}
 		}
 		else
 		{
 			logger->lw(WARNING,"MONITOR: Waiting for all threads to kick...");
 		}
 		
 		// Sleep:
 		usleep (ME->monitorSleep);
	}
	
	// Kill with grace:
	logger->lw(WARNING,"MONITOR: Exiting...");
	return NULL;
}
