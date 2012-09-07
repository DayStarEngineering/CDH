#include "Scheduler.h"

sched::sched(char* theConfig, volatile bool* Stop): myLogger("SCHED"), commandWrapper(SCHED)
{
	
	// Set thread signal control pointer:
	stop = Stop;
	
	// Read config:
	myConfig.readfile(theConfig);
	
	// DCOL LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"CONSTRUCTOR: Scheduler");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure() != 0)
	{
		myLogger.lw(ERROR,"SCHED not configured correctly!");
		exit(-1);
	}
	else
	{
		myLogger.lw(INFO,"SCHED correctly configured.");
	}
}

sched::~sched()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	myLogger.lw(INFO,"DESTRUCTOR: SCHED TERMINATED.");
	myLogger.close();
}

int sched::configure()
{
	multimap<string,string>::iterator p,p2;
		
	// How many events are there:
	p = myConfig.find("event");
	p2 = myConfig.find("event");
	int ind = 0;
	if (p != myConfig.end())
	{
		do
		{
			++ind;
			++p;
		}
		while (p != myConfig.upper_bound("event"));
	}
	
	numEvents  = ind;
	if(numEvents <= 0)
	{
		myLogger.lw(ERROR,"CONFIG: Invalid number of events: %d, exiting...", numEvents);
		return -1;
	}
	else
	{
		myLogger.lw(INFO,"CONFIG: Creating space for %d events.", numEvents);
	}
	event = new schedEvent[numEvents];
	
	// Load all events:
	ind = 0;
	message tmpmsg;
	tmpmsg.rsp.length = 0;
	if (p2 != myConfig.end())
	{
		do
		{
			sscanf((*p2).second.c_str(),"%hhu %hhu %hhu  %hu %d %d",
			  &event[ind].cmd.proc,
			  &event[ind].cmd.type,
			  &event[ind].cmd.arg1,
			  &event[ind].cmd.arg2,
			  &event[ind].count,
			  &event[ind].sleep);

			// Error check:
			//if (event[ind].num != ind){ myLogger.lw(ERROR,"CONFIG: Improperly numbered task."); exit(-1); }

			// Print config:
			event[ind].num = ind;
			tmpmsg.cmd = event[ind].cmd;
			myLogger.lw(DEBUG,"CONFIG: Task %d, run %d time(s), sleep %d seconds, message: %s",
			  event[ind].num,
			  event[ind].count,
			  event[ind].sleep,
			  tmpmsg.toString());
			
			++p2;
			++ind;
		}
		while (p2 != myConfig.upper_bound("event"));
	}
	
	// Get location of globale variable files:
	eventCounterFname = myConfig["event_counter_fname"].c_str();
	currEventFname = myConfig["curr_event_fname"].c_str();
	
	// Get semid:
	if( (sched_semid = initSemaphores(SCHED_PATH,NUM_SCHED)) == -1 )
	{
		myLogger.lw(WARNING,"CONFIG: Unable to grab semaphores (%s)", SCHED_PATH);
	}

	if( (semid = getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
    {
        myLogger.lw(WARNING,"CONFIG: Unable to grab semaphores (%s)", KICK_PATH);
    }
    else
    {
    	myLogger.lw(SPAM,"CONFIG: Got semid: %d",semid);
    }
    
	return 0;
}

int sched::run()
{
	myLogger.lw(INFO,"RUN: Starting SCHED Run...");
	message msg;
	
	// Starting conditions:
	currEvent = getGV(currEventFname);
	if( (currEvent < 0) || (currEvent >= numEvents) )
	{
		currEvent = 0;
		if( setGV(currEventFname, currEvent) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event to global var at %s",currEventFname);	
		}
	}
	
	eventCounter = getGV(eventCounterFname);
	if( (eventCounter < 0) )
	{
		eventCounter = 0;
		if( setGV(eventCounterFname, eventCounter) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event counter to global var at %s",eventCounterFname);	
		}
	}

	myLogger.lw(INFO,"RUN: Restored current event as %d, count %d",currEvent,eventCounter);	
	
	// Update semaphores:
	setSemaphore(sched_semid,1,currEvent);
	setSemaphore(sched_semid,2,eventCounter);
	
	for(; currEvent < numEvents; currEvent++)
	{	
		// Update semaphore & file:
		setGV(currEventFname, currEvent);
		setSemaphore(sched_semid,1,currEvent);
		
		// Form message
		msg.cmd = event[currEvent].cmd;
		myLogger.lw(INFO,"RUN: Starting event %d. Run %d time(s): %s",event[currEvent].num,event[currEvent].count,msg.toString());
		
		eventCounter = 0;
		while( (eventCounter < event[currEvent].count) || (event[currEvent].count == -1) )
		{
			// Update semaphore & file:
			setGV(eventCounterFname, eventCounter);
			setSemaphore(sched_semid,2,eventCounter);
			myLogger.lw(INFO,"RUN: Running event %d. Count %d of %d.",event[currEvent].num,eventCounter + 1,event[currEvent].count);
			
			// Run command:
			commandWrapper.execute(&msg);
			if(msg.rsp.ret != 1)
			{
				myLogger.lw(ERROR,"RUN: Event %d returned with error %x",event[currEvent].num, msg.rsp.ret);
			}
			
			if(sched_sleep(event[currEvent].sleep) == -1)
			{
				myLogger.lw(INFO,"RUN: Schedule terminated. Dying gracefully.");
				return 0;
			}
			
			// Increment to next event:	
			eventCounter++;
		}
	}
	
	myLogger.lw(INFO,"RUN: Schedule completed. Dying gracefully.");
	
	return 0;
}

int sched::sched_sleep(int sleeptime)
{
	// Timers:
	timeval currTime;
	timeval sleepStartTime;
	gettimeofday(&currTime, NULL);
	sleepStartTime = currTime;
	//int temp;
	
	myLogger.lw(SPAM,"SLEEP: Taking a nap for %d seconds", sleeptime );
	
	do
	{
		// Checking for signal:
		if(*stop)
			return -1;
		
		//myLogger.lw(SPAM,"SLEEP: Sleeping for %d more seconds.", sleeptime - (currTime.tv_sec - sleepStartTime.tv_sec) );
		
		// Kick pdog:
		//myLogger.lw(SPAM,"SLEEP: Kicking pdog.");
		if ((setSemaphore(semid,SCHED_KICK_SEM,1)) == -1)
		{
			myLogger.lw(ERROR,"SLEEP: Unable to set semaphore!");
			if ((semid = getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
	        {
	            myLogger.lw(ERROR,"SLEEP: Unable to grab semaphores (%s)", KICK_PATH);
	        }
		}
		
		// See if we got a command:
		/*
		temp = getSemaphore(sched_semid, 1);
		if( (temp >= 0) && (temp < numEvents) )
			currEvent = temp;
		temp = getSemaphore(sched_semid, 2);
		if( (eventCounter >= 0) )
			eventCounter = temp;
		*/
		
		// Sleep:
 		usleep(1000000);
 		
 		// Get the current time:
		gettimeofday(&currTime, NULL);
	} while( ((currTime.tv_sec - sleepStartTime.tv_sec) < sleeptime) || (sleeptime == -1)  );
	
	return 0;
}
