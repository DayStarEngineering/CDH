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
	playFname = myConfig["play_fname"].c_str();
	eventCounterFname = myConfig["event_counter_fname"].c_str();
	currEventFname = myConfig["curr_event_fname"].c_str();
	timeSleptFname = myConfig["time_slept_fname"].c_str();
	
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
	int temp = getGV(playFname);
	if( temp <= 0 )
	{
		play = false;
		if( setGV(playFname, (int) play) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event counter to global var at %s",playFname);	
		}
	}
	else
	{
		play = (bool) temp;
	}
	
	currEvent = getGV(currEventFname);
	if( (currEvent < 0) || (currEvent >= numEvents) )
	{
		currEvent = -1;
		if( setGV(currEventFname, currEvent) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event to global var at %s",currEventFname);	
		}
	}
	else
	
	eventCounter = getGV(eventCounterFname);
	if( (eventCounter < 0) )
	{
		eventCounter = 0;
		if( setGV(eventCounterFname, eventCounter) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event counter to global var at %s",eventCounterFname);	
		}
	}
	
	timeSlept = getGV(timeSleptFname);
	if( (timeSlept < 0) )
	{
		timeSlept = 0;
		if( setGV(timeSleptFname, timeSlept) == -1 )
		{
			myLogger.lw(ERROR,"RUN: Error setting current event counter to global var at %s",timeSleptFname);	
		}
	}
	
	myLogger.lw(INFO,"RUN: Restored current event as %d, count %d, timeslept %d, play %d",currEvent,eventCounter,timeSlept,(int) play);	
	
	// Update semaphores:
	setSemaphore(sched_semid,1,(int) play);
	setSemaphore(sched_semid,2,currEvent);
	setSemaphore(sched_semid,3,eventCounter);
	setSemaphore(sched_semid,4,timeSlept);
 	
 	int presleep = 0;
 	if( currEvent > 0 )
 	{
 		presleep = event[currEvent].sleep;
 	}
 	
 	// Sleep initially and wait for play, or advance when the next event is scheduled.
	if(sched_sleep(presleep) == -1)
	{
		myLogger.lw(INFO,"RUN: Schedule terminated. Dying gracefully.");
		return 0;
	}
 	currEvent++;
	
	for(; currEvent < numEvents; currEvent++)
	{	
		// Update semaphore & file:
		setGV(currEventFname, currEvent);
		setSemaphore(sched_semid,2,currEvent);
		
		// Form message
		msg.cmd = event[currEvent].cmd;
		myLogger.lw(INFO,"RUN: Starting event %d. Run %d time(s): %s",event[currEvent].num,event[currEvent].count,msg.toString());
		
		eventCounter = 0;
		while( (eventCounter < event[currEvent].count) || (event[currEvent].count == -1) )
		{
			// Update semaphore & file:
			setGV(eventCounterFname, eventCounter);
			setSemaphore(sched_semid,3,eventCounter);
			
			myLogger.lw(INFO,"RUN: Running event %d. Count %d of %d.",event[currEvent].num,eventCounter + 1,event[currEvent].count);
			
			// Run command up to 5 times if failures occure:
			for( int numTrys = 0; numTrys < 5; numTrys++ )
			{
				commandWrapper.execute(&msg);
				if(msg.rsp.ret != 1)
				{
					myLogger.lw(ERROR,"RUN: Event %d returned with error %x on try %d. Sleeping 1 second and trying again.",event[currEvent].num, numTrys, msg.rsp.ret);
					usleep(1000000);
				}
				else
				{
					myLogger.lw(INFO,"RUN: Event %d successful on try %d.",event[currEvent].num, numTrys);
					break; // command success, go to sleepy time.
				}
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
	int prevTimeSlept = 0;
	int currTimeSlept = 0;
	
	// Figure out how long to sleep:
	//int time2sleep = sleeptime;	
	/*if( sleeptime != -1 )
	{
		time2sleep = sleeptime - timeSlept;
	}*/
	prevTimeSlept = timeSlept;
	
	myLogger.lw(SPAM,"SLEEP: Taking a nap for sleeptime: %d  - timeslept: %d = %d seconds. Play = %d.", sleeptime, timeSlept, sleeptime - timeSlept, (int) play );
	
	// Get time:
	gettimeofday(&currTime, NULL);
	sleepStartTime = currTime;
	do
	{
		// Checking for signal:
		if(*stop)
			return -1;
		
		myLogger.lw(SPAM,"SLEEP: Play = %d, Sleeping for %d more seconds.", (int) play, sleeptime - timeSlept );
		
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

		// Sleep:
 		usleep(1000000);
 		
 		// See if we are in pause or play mode:
 		play = (bool) getSemaphore(sched_semid,1);
 		setGV(playFname, (int) play);
		
		// Calculate amount of time slept so far if we are not paused:
		if( play )
		{
			// Get the current time:
			gettimeofday(&currTime, NULL);
			currTimeSlept = (currTime.tv_sec - sleepStartTime.tv_sec);
			timeSlept = prevTimeSlept + currTimeSlept;
			setGV(timeSleptFname, timeSlept);
			setSemaphore(sched_semid,4,timeSlept);
		}
		else
		{
			// Store previous time:
			prevTimeSlept = timeSlept;
			
			// Reset the sleep start time until we are in play mode again:
			gettimeofday(&sleepStartTime, NULL);
		}
		
	} while( (timeSlept < sleeptime) || (sleeptime == -1) || !play );
	
	// Reset time slept to zero:
	timeSlept = 0;
	setGV(timeSleptFname, timeSlept);
	
	return 0;
}
