#include "SubsystemMessenger.h"

ssm::ssm(char* theConfig, volatile bool* Stop): myLogger("SSM")
{
	
	// Set thread signal control pointer:
	stop = Stop;
	
	workerThread = NULL;
	
	// Read config:
	myConfig.readfile(theConfig);
	
	// DCOL LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"CONSTRUCTOR: Subsystem Messenger");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure() != 0)
	{
		myLogger.lw(ERROR,"SSM not configured correctly!");
		exit(-1);
	}
	else
	{
		myLogger.lw(INFO,"SSM correctly configured.");
	}
}

ssm::~ssm()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Deallocate Memory:
	if (workerThread != NULL)
	{
		delete [] workerThread;
		workerThread = NULL;
	}
	
	myLogger.lw(INFO,"DESTRUCTOR: SSM TERMINATED.");
	myLogger.close();
}

int ssm::configure()
{
	int ret;
	
	// Get thread info:
	numWorkers  = atoi(myConfig["num_threads"].c_str());
	workerThread = new pthread_t[numWorkers];
	workerGood = new bool[numWorkers];
	
	// Configure interface:
	portData thePortData;
	thePortData.baud = atoi(myConfig["baud"].c_str());
	thePortData.port = myConfig["port"];
	if( (ret = myInterface.configure(thePortData)) != 0) // eventually create an array of these for multiple subsystems. not needed now...
	{
		myLogger.lw(INFO,"CONFIGURE: Trouble configuring subsystem interface. Error %x", ret);
		return -1;
	}
	
	// Get sleep times:
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());

	return 0;
}

int ssm::run()
{
	myLogger.lw(INFO,"RUN: Starting DCOL Run...");
	
	// Setup a thread attribute:
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc=0;
	
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, ssm::monitor, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start all dataWorker threads:
	workerStruct* dataTemp = new workerStruct[numWorkers];
	for (int i = 0; i < numWorkers; i++)
	{
		myLogger.lw(INFO,"RUN: Creating dataWorker thread: %d",i);
		dataTemp[i].workerNum = i;
		dataTemp[i].ME = this;
		rc = pthread_create(&workerThread[i], NULL, ssm::worker, (void*) &dataTemp[i]);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN %d: Bad return code from pthread_create() - value is %d\n", i, rc);
			exit(-1);
		}
	}
	
	pthread_attr_destroy(&attr);
	
	// Joining our threads until we are killed by a signal:
	rc = pthread_join(monitorThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	
	for (int i = 0; i < numWorkers; i++)
	{
		rc = pthread_join(workerThread[i], NULL);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN: return code from pthread_join() - value is %d\n", rc);
			exit(-1);
		}
	}
	
	myLogger.lw(WARNING,"RUN: All threads have terminated. Dying gracefully.");
	
	// Cleaning up:
	if (dataTemp != NULL)
	{
		delete [] dataTemp;
		dataTemp = NULL;
	}
	
	return 0;
}

void* ssm::worker(void* arg)
{
	// Get global vars from dcol instance:
	int workerNum = ((workerStruct*) arg)->workerNum;
	ssm* ME = ((workerStruct*) arg)->ME;
	Logger* logger = &(ME->myLogger);
	
	// Defines:
	int ret;
	message msg;
	int qid = ME->msgQueueWrapper.msgQueueCreate(SSM);

	// Stating up...
	logger->lw(INFO,"WORKER %d: Started.",workerNum);
	
	while ( 1 )
	{
		// Wait for message:
		ret = ME->msgQueueWrapper.msgQueueReceive(qid,0,&msg);
		
		//logger->lw(SPAM,"WORKER %d: Message recieved: %d %s",workerNum,ret,msg.toString());
		
		// Message error?
		if (ret <= -1)
		{
			switch (msg.err)
			{
			case EFAULT:
				qid = ME->msgQueueWrapper.msgQueueCreate(SSM);
				continue;
			case EIDRM:
				qid = ME->msgQueueWrapper.msgQueueCreate(SSM);
				continue;
			case EINVAL:
				qid = ME->msgQueueWrapper.msgQueueCreate(SSM);
				continue;
			default:
				continue;
			}
			continue;			
		}
		
		// Kick monitor:
		ME->workerGood[workerNum] = true;
		
		// Foward message to subsystem:
		ME->myInterface.command(&msg);
		
		// Foward response to process:
		//logger->lw(SPAM,"WORKER %d: Sending response: %s",workerNum,msg.toString());
		if( (ret = ME->msgQueueWrapper.msgQueueSend(msg.qid, &msg)) <= -1 )
		{
			if(ret == -1)
			{
				logger->lw(ERROR, "WORKER %d: Error sending reply. Is the queue still there? qid = %d with errno = %s",workerNum, msg.qid,ME->printError(msg.err).c_str());
			}
			else
			{
				logger->lw(ERROR, "WORKER %d: Error Queue Gone",workerNum);
			}	
			continue;
		}
	}
	
	// Kill with grace:
	logger->lw(WARNING,"WORKER %d: Exiting...",workerNum);
	return NULL;
}

void* ssm::monitor(void* arg)
{
	// Get global vars:
	ssm* ME = (ssm*) arg;
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
	for (int i = 0; i < ME->numWorkers; i++)
	{
		ME->workerGood[i] = false;
	}

	// Check loop:   
	while ( !(*ME->stop) )
	{	
 		// Reset:
 		allGood = true;
 		
 		//logger->lw(SPAM,"MONITOR: Who kicked me?");
 		 				
 		// Check all threads:
 		for (int i = 0; i < ME->numWorkers; i++)
 		{
 			if (!ME->workerGood[i])
 			{
 				//logger->lw(WARNING,"MONITOR: DATAWORKER %d has not yet kicked.",i);
 				allGood = false;
 				break;
 			}
 		}
 		
 		// Kick:
 		if (allGood)
 		{
 			logger->lw(DEBUG,"MONITOR: All threads running well... Kicking the dog.");
 			
 			if ((setSemaphore(semid,SSM_KICK_SEM,1)) == -1)
 			{
 				logger->lw(ERROR,"MONITOR: Unable to set semaphore!");
 				if ((semid = getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
		        {
		            logger->lw(ERROR,"MONITOR: Unable to grab semaphores (%s)", KICK_PATH);
		        }
 			}
 			else
 			{		
 				for (int i = 0; i < ME->numWorkers; i++)
		 		{
		 			ME->workerGood[i] = false;
		 		}
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

string ssm::printError(int err)
{
	switch (err)
	{
	case EACCES:
		return string("EACCES");
		break;
	case EAGAIN:
		return string("EAGAIN");
		break;
	case EFAULT:
		return string("EFAULT");
		break;
	case EIDRM:
		return string("EIDRM");
		break;
	case EINTR:
		return string("EINTR");
		break;
	case EINVAL:
		return string("EINVAL");
		break;
	case ENOMEM:
		return string("ENOMEM");
		break;
	case E2BIG:
		return string("E2BIG");
		break;
	case ENOMSG:
		return string("ENOMSG");
		break;
	case EEXIST:
		return string("EEXIST");
		break;
	case ENOENT:
		return string("ENOENT");
		break;
	case ENOSPC:
		return string("ENOSPC");
		break;
	default:
		return string("Unknown error code");
	}
}
