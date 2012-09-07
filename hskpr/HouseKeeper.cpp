#include "HouseKeeper.h"

hskpr::hskpr(const char* theConfig, volatile bool* Stop) : myLogger("HSKPR")
{
	// Set thread signal control pointer:
	stop = Stop;
	
	// Null any heap allocated vars:
	workerThread = NULL;
	workerGood = NULL;
	action = NULL;
	task = NULL;
	
	// Read config:
	myConfig.readfile(theConfig);
	
	// HSKPR LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)
	{
		myLogger.lw(INFO,"CONSTRUCTOR: File type is MULTIFILES");
	}
	else //!filetype
	{
		myLogger.lw(INFO,"CONSTRUCTOR: File type is SINGLEFILES");
	}
	myLogger.lw(INFO,"CONSTRUCTOR: House Keeper");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure() != 0)
	{
		myLogger.lw(ERROR,"HSKPR not configured correctly!");
		exit(-1);
	}
	else
	{
		myLogger.lw(INFO,"HSKPR correctly configured.");
	}
}

hskpr::~hskpr()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Deallocate Memory:
	if (workerThread != NULL)
	{
		delete [] workerThread;
		workerThread = NULL;
	}
	
	if (workerGood != NULL)
	{
		delete [] workerGood;
		workerGood = NULL;
	}
	
	if (action != NULL)
	{
		delete [] action;
		action = NULL;
	}
	
	if (task != NULL)
	{
		delete [] task;
		task = NULL;
	}
	
	myLogger.lw(INFO,"DESTRUCTOR: HSKPR TERMINATED.");
	myLogger.close();
}

int hskpr::configure()
{
	multimap<string,string>::iterator p;
	
	// Get thread info:
	numTasks         = atoi(myConfig["num_tasks"].c_str());
	numActions       = atoi(myConfig["num_actions"].c_str());
	workerThread     = new pthread_t[numTasks];
	workerGood       = new bool[numTasks];

	// Get sleep times:
	commandSleep     = atoi(myConfig["command_sleep"].c_str());
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());
	
	// Get action info:
	if (numActions <= 0)
		myLogger.lw(ERROR,"Invalid number of actions: %d",numActions);
	else
		myLogger.lw(INFO,"Reading %d actions.",numActions);
	action = new commandData[numActions];
	
	// Load all actions to an array of action structs:
	p = myConfig.find("action");
	int currNum;
	int ind = 0; //first action in conf file must be numbered zero!!
	
	if (p != myConfig.end())
	{
		do
		{
			// Terrible errors can occur if the first action in config file does
			// not correspond to an action# of 0
			// Possibly add a check that will determine if two actions have the
			// same action number -> bool array of length numActions
			sscanf((*p).second.c_str(),"%d %d %d %d %d",&currNum,
			  (unsigned int*)&action[ind].proc,(unsigned int*)&action[ind].cmd,
			  (unsigned int*)&action[ind].arg1,(unsigned int*)&action[ind].arg2);
			if (currNum >= numActions) exit(-1);
			myLogger.lw(DEBUG,"Action %d recorded as \"%d %d %d %d\"",ind,
			  action[ind].proc,action[ind].cmd,
			  action[ind].arg1,action[ind].arg2);
			++p;
			++ind;
		}
		while (p != myConfig.upper_bound("action"));
	}
	
	// Get task info:
	if (numTasks <= 0)
		myLogger.lw(ERROR,"Invalid number of tasks: %d",numTasks);
	else
		myLogger.lw(INFO,"Reading %d tasks.",numTasks);
	task = new taskStruct[numTasks];
	
	// Load all tasks to an array of task structs:
	p = myConfig.find("task");
	ind = 0; //first task in conf file must be numbered zero!!
	
	if (p != myConfig.end())
	{
		do
		{
			// Terrible errors can occur if the first task in config file does
			// not correspond to a task# of 0
			// Possibly add a check that will determine if two tasks have the
			// same task number -> bool array of length numTasks
			sscanf((*p).second.c_str(),"%d %hhu %hhu %u %u %u %u %u %u",&currNum,
			  &task[ind].cmd.proc,&task[ind].cmd.arg1,
			  &task[ind].lowVal,&task[ind].highVal,
			  &task[ind].slpCnt,&task[ind].failCnt,
			  &task[ind].lowActn,&task[ind].highActn);
			task[ind].cmd.cmd = GET;
			if (currNum >= numTasks) exit(-1);
			myLogger.lw(DEBUG,"Task %d recorded as \"%hhu %hhu %u %u %u %u %u %u\"",
			  ind,task[ind].cmd.proc,task[ind].cmd.arg1,
			  task[ind].lowVal,task[ind].highVal,
			  task[ind].slpCnt,task[ind].failCnt,
			  task[ind].lowActn,task[ind].highActn);
			++p;
			++ind;
		}
		while (p != myConfig.upper_bound("task"));
	}
	
	return 0;
}

int hskpr::run()
{
	myLogger.lw(INFO,"RUN: Starting HSKPR Run...");
	
	// Setup a thread attribute:
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc=0;
	
	// Setup and start the command thread:
	myLogger.lw(INFO,"RUN: Starting command thread");
	rc = pthread_create(&commandThread, &attr, hskpr::command, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, hskpr::monitor, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() - value is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start all worker threads:
	workerStruct* taskData = new workerStruct[numTasks];
	for (int i = 0; i < numTasks; i++)
	{
		myLogger.lw(INFO,"Creating worker thread: %d",i);
		taskData[i].tskNum = i;
		taskData[i].ME = this;
		rc = pthread_create(&workerThread[i], NULL, hskpr::worker, (void*) &taskData[i]);
		if (rc)
		{
			myLogger.lw(ERROR,"WORKER %d: Bad return code from pthread_create() - value is %d\n", i, rc);
			exit(-1);
		}
	}
	
	pthread_attr_destroy(&attr);
	
	// Joining our threads until we are killed by a signal:
	rc = pthread_join(commandThread, NULL);
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
	
	for (int i = 0; i < numTasks; i++)
	{
		rc = pthread_join(workerThread[i], NULL);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN: return code from pthread_join() - value is %d\n", rc);
			exit(-1);
		}
	}
	
	// Cleaning up:
	if (taskData != NULL)
	{
		delete [] taskData;
		taskData = NULL;
	}
	myLogger.lw(WARNING,"RUN: All threads have terminated. Dying gracefully.");
	return 0;
}

void* hskpr::worker(void* arg)
{
	// Get global vars from hskpr instance:
	int tskNum = ((workerStruct*) arg)->tskNum;
	hskpr* ME = ((workerStruct*) arg)->ME;
	Logger *logger = &(ME->myLogger);
	
	// Stating up...
	logger->lw(INFO,"WORKER %d: Started.",tskNum);
	
	// Initialize command response:
	commandResp rsp;
	rsp.length = 0;
	
	// Corresponding semaphore value:
	unsigned int semVal;
	
	// ALSO NEED TO GO IN COMMAND & STCL AND ADD CHECKS TO PREVENT SEM NUM OR
	// SEM VAL FROM BEING > 255
	
	// Loop unitl stop condition is reached:
	while (!(*ME->stop))
	{
		// Kick monitor:
		ME->workerGood[tskNum] = true;
		
		// Check specified semaphore:
		if ((semVal = execute(&ME->task[tskNum].cmd,&rsp)) > ERR_LWR_BOUND)
		{
			logger->lw(ERROR,"WORKER %d: Error returned from execute: %d.",tskNum,semVal);
		}
		else
		{
			// Determine if an action needs to be called:
			if ((semVal < (ME->task[tskNum].lowVal)) || (semVal > (ME->task[tskNum].highVal)))
			{
				// Execute the appropriate action:
				if (semVal > (ME->task[tskNum].highVal))
				{
					if (execute(&ME->action[ME->task[tskNum].highActn],&rsp) != 1)
					{
						logger->lw(ERROR,"WORKER %d: Could not execute action %d.",tskNum,ME->task[tskNum].highActn);
					}
				}
				else if (semVal < (ME->task[tskNum].lowVal))
				{
					if (execute(&ME->action[ME->task[tskNum].lowActn],&rsp) != 1)
					{
						logger->lw(ERROR,"WORKER %d: Could not execute action %d.",tskNum,ME->task[tskNum].lowActn);
					}
				}
				else
				{
					logger->lw(ERROR,"WORKER %d: WTF...couldn't detect which action to call.",tskNum);
				}
			}
		}
		
		// Sleep:
 		usleep(ME->task[tskNum].slpCnt);
	}
	
	// Kill with grace:
	logger->lw(WARNING,"WORKER %d: Exiting...",tskNum);
	return NULL;
}

void* hskpr::command(void* arg)
{
	// Get global vars:
	hskpr* ME = (hskpr*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");
	
	// Create command struct
	commandData* cmd = new commandData[2];
	int totCmds = 0; //tracks total number of cmds to hskpr
	cmd[0].proc = HSKPR;
	unsigned int ret;
	int response = 1;
	/*
	while( !(*ME->stop) )
	{
		// Kick monitor:
		ME->commandGood = true;
		
		// Check for a command on hskpr
		ret = isCommand(&cmd[0]);
		
		// EXECUTE COMMAND INTERNALLY
		
		// If seen, print out boolean test for expected sem# and val
		if (ret == 1)
		{
			if (sendResponse(cmd, 1, response) > 1)
			{
				logger->lw(FATAL,"CMD: Error returned from sendResponse().");
			}
		}
		else if (ret > 1)
		{
			logger->lw(FATAL,"CMD: Error returned from isCommand().");
		}
		
		// Sleep:
 		usleep(ME->commandSleep);
	}
	*/
	// Kill with grace:
	delete [] cmd;
	logger->lw(WARNING, "CMD: Exiting...");
	return NULL;
}

void* hskpr::monitor(void* arg)
{
	// Get global vars:
	hskpr* ME = (hskpr*) arg;
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
	for (int i = 0; i < ME->numTasks; i++)
	{
		ME->workerGood[i] = false;
	}
	ME->commandGood = false;
	
	// Check loop:   
	while ( !(*ME->stop) )
	{	
 		// Reset:
 		allGood = true;
 		
 		// Check all threads:
 		for (int i = 0; i < ME->numTasks; i++)
 		{
 			if (!ME->workerGood[i])
 			{
 				allGood = false;
 				break;
 			}
 		}
 		
 		if (!ME->commandGood)
 		{
 			allGood = false;
 		}
 		
 		// Kick:
 		if (allGood)
 		{
 			logger->lw(DEBUG,"MONITOR: All threads running well... Kicking the dog.");
 			
 			if ((setSemaphore(semid,HSKPR_KICK_SEM,1)) == -1)
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
 				
 				for (int i = 0; i < ME->numTasks; i++)
		 		{
		 			ME->workerGood[i] = false;
		 		}
		 	}
 		}
 		else
 		{
 			logger->lw(SPAM,"MONITOR: Waiting for all threads to kick...");
 		}
 		
 		// Sleep:
 		usleep (ME->monitorSleep);
	}
	
	// Kill with grace:
	logger->lw(WARNING,"MONITOR: Exiting...");
	return NULL;
}

