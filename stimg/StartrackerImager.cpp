#include "StartrackerImager.h"

// We only want grey2bin linked witht this object, none others, so we include this here:
#include "../imglib/grey2bin.h"

itimerval timer;
stimg::stimg(char* theConfig, volatile pthread_mutex_t* mutex_signal, volatile timeval* global_timer, volatile bool* Stop) : myLogger("STIMG")
{
	// Set thread signal control pointer, signal mutex, and timer:
	stop = Stop;
	sigInData = mutex_signal;
	timer = global_timer;
	
	// Thread Synchronization Mutex Locks:
	pthread_mutex_init((pthread_mutex_t*)sigInData,NULL);
	pthread_mutex_lock((pthread_mutex_t*)sigInData);        // Set innitial state to locked (wait)
	
	// Monitor variable innitial conditions:
	inDataGood = false;
	// schedulerGood = false;
	commandGood = false;
	
	// Read config:
	myConfig.readfile(theConfig);

	// STIMG LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"CONSTRUCTOR: Startracker Processor");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure()!=0){
		myLogger.lw(ERROR,"STIMG not configured correctly!");
		exit(-1);
	}
	else{
		myLogger.lw(INFO,"STIMG correctly configured.");
	}
	
	// Lets take images:
	capture = false;
	seqcnt = 0;
	imgcnt = 0;
}

stimg::~stimg()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Destroy Sychronization Mutex Locks:
	pthread_mutex_destroy((pthread_mutex_t*)sigInData);
	
	myLogger.lw(INFO,"DESTRUCTOR: STIMG TERMINATED.");
	myLogger.close();
}

int stimg::configure()
{	
	// Get signal information:
	timeval temp;
	temp.tv_sec = atoi(myConfig["signal_sec"].c_str());
  	temp.tv_usec = atoi(myConfig["signal_usec"].c_str());
  	setTimer(temp);
  	
	// Get sleep times:
	commandSleep     = atoi(myConfig["command_sleep"].c_str());
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());
	// schedulerSleep   = atoi(myConfig["scheduler_sleep"].c_str());
	
	// Configure MIL Wrapper:
    if(MilWrapper.create(&myLogger) != 0)
    {
    	myLogger.lw(INFO,"CONFIG: Error creating mil wrapper.");
    	return -1;
    }
    	
    // Configure MIL Digitizer:
    if(MilDigitizer.create(MilWrapper.SysID, 
    					   myConfig["dig_DCF0"].c_str(), 
    					   myConfig["dig_DCF1"].c_str(),
    					   atoi(myConfig["dig_num0"].c_str()),
    					   atoi(myConfig["dig_num1"].c_str())))
    {
    	myLogger.lw(INFO,"CONFIG: Error configuring dig2.");
    	return -1;
    }
    
   /*
    if(MilDigitizer0.create(MilWrapper.SysID, myConfig["dig_DCF0"].c_str(), atoi(myConfig["dig_num0"].c_str())) != 0)
    {
    	myLogger.lw(INFO,"CONFIG: Error configuring dig 0.");
    	return -1;
    }
    if(MilDigitizer1.create(MilWrapper.SysID, myConfig["dig_DCF1"].c_str(), atoi(myConfig["dig_num1"].c_str())) != 0)
    {
    	myLogger.lw(INFO,"CONFIG: Error configuring dig 1.");
    	return -1;
    }
    */
    // Configure Mode:
    digMode = atoi(myConfig["dig_mode"].c_str());
    
    // Configure MIL Image Buffers:
    int xlen = atoi(myConfig["xpix_size"].c_str());
    int ylen = atoi(myConfig["ypix_size"].c_str());
	if(MilImage0.create(MilWrapper.SysID, xlen, ylen) != 0)
	{
    	myLogger.lw(INFO,"CONFIG: Error configuring img 0.");
    	return -1;
    }
	if(MilImage1.create(MilWrapper.SysID, xlen, ylen) != 0)
	{
    	myLogger.lw(INFO,"CONFIG: Error configuring img 1.");
    	return -1;
    }
		
	// Configure files:
	file_path[0] = "";
	file_path[0] += myConfig["file_dir0"];
	file_path[0] += "/";
	file_path[0] += myConfig["file_str"];
	
	file_path[1] = "";
	file_path[1] += myConfig["file_dir1"];
	file_path[1] += "/";
	file_path[1] += myConfig["file_str"];
	
	file_path[2] = "";
	file_path[2] += myConfig["file_dir2"];
	file_path[2] += "/";
	file_path[2] += myConfig["file_str"];
	
	// Configure scheduler:
	captureDuration = atoi(myConfig["capture_duration"].c_str());
	sleepDuration   = atoi(myConfig["sleep_duration"].c_str());
	
	// Get semid:
	semid = initSemaphores(STIMG_PATH,NUM_STIMG);
	
	return 0;
}

int stimg::run()
{
	itimerval tval;
	int rc=0;
	pthread_attr_t attr;
		
	myLogger.lw(INFO,"RUN: Starting STIMG Run...");
	
	// Setup a thread attribute:
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	
	// Setup and start the command thread:
	myLogger.lw(INFO,"RUN: Starting command thread");
	rc = pthread_create(&commandThread, &attr, stimg::command, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the inData thread:
	myLogger.lw(INFO,"RUN: Starting inData thread");
	rc = pthread_create(&inDataThread, &attr, stimg::inData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
		
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, stimg::monitor, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Begin execution by starting timer:
  	tval.it_interval.tv_sec = 0;
  	tval.it_interval.tv_usec = 0;
  	tval.it_value.tv_sec = 0; 
  	tval.it_value.tv_usec = 1;
  
  	///////// RESET TIMER ///////////////
	setitimer(ITIMER_REAL, &tval, NULL);
	/////////////////////////////////////
  
	pthread_attr_destroy(&attr);

	// Joining our threads until we are killed by a signal:
	rc = pthread_join(commandThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	rc = pthread_join(inDataThread, NULL);
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
	
	// Cleaning up:
	myLogger.lw(WARNING,"RUN: All threads have terminated. Dying gracefully.");
	
	return 0;
}

void* stimg::inData(void* arg)
{
	// Get global vars:
	stimg* ME = (stimg*) arg;
	Logger* logger = &(ME->myLogger);
	
	// Local vars:
	stringstream frame_name0;
	stringstream frame_name1;
	
	// Timers:
	#if DEBUG_MODE == TIMETEST
	timerStruct totalTimer;
	timerStruct grabtimer;
	#endif
	
	// Start:
	logger->lw(INFO,"IN: Starting up...");
	
	/*
	if(digSetSyncChannel(ME->MilDigitizer.ID, 0) == -1)
	{
		logger->lw(ERROR,"IN: Unable to sync digitizer to channel 0.");
	}
	*/
	
	while( 1 )
	{	
		//_______ WAIT FOR SIGNAL ________________
		pthread_mutex_lock((pthread_mutex_t*)ME->sigInData);
		//________________________________________
		
		//////// CHECK FOR TERMINATION ///////////
		if(*ME->stop) break;
		//////////////////////////////////////////
		
		/////////// KICK MONITOR ///////////////// 
		ME->inDataGood = true;
		//////////////////////////////////////////
		
		//////////// CAPTURE  ///////////////////
		ME->capture = (bool) getSemaphore(ME->semid, 1);
		//////////////////////////////////////////
		
		// Capture ON:
		if( ME->capture )
		{
			//////////// GET SEMS  ///////////////////
			ME->digMode = getSemaphore(ME->semid, 2);
			ME->file_path_index = getSemaphore(ME->semid, 3);
			if( ME->file_path_index < 0 || ME->file_path_index > 2 )
			{
				ME->file_path_index = 0;
				setSemaphore(ME->semid, 3, ME->file_path_index);
			}
			//////////////////////////////////////////
			
			// Start main timer:
			#if DEBUG_MODE == TIMETEST
			gettimeofday(&totalTimer.start, NULL);
			gettimeofday(&grabtimer.start,NULL);
			#endif
		
			// Grab image:
			if( (ME->digMode == 2) || (ME->digMode == 0) )
			{
				/*
				if(digSetDataChannel( ME->MilDigitizer.ID, 0) == -1)
				{
					logger->lw(ERROR,"IN: Unable to set digitizer to channel 0.");
					continue;
				}
				*/
				if( digGrab( ME->MilDigitizer.ID[0], ME->MilImage0.ID ) != 0 )
				{
					logger->lw(ERROR,"IN: Unable to grab image from channel 0.");
					continue;
				}
			}
			
			if( (ME->digMode == 2) || (ME->digMode == 1) )
			{
				/*
				if(digSetDataChannel( ME->MilDigitizer.ID, 1) == -1)
				{
					logger->lw(ERROR,"IN: Unable to set digitizer to channel 1.");
					continue;
				}
				*/
				if( digGrab( ME->MilDigitizer.ID[1], ME->MilImage1.ID ) != 0 )
				{
					logger->lw(ERROR,"IN: Unable to grab image from channel 1.");
					continue;
				}
			}
		
			#if DEBUG_MODE == TIMETEST
			gettimeofday(&grabtimer.stop,NULL);
			#endif
		
			// Set timestamp of image:
			gettimeofday(&ME->img.timestamp, NULL);
			
			// Save image:
			if( (ME->digMode == 2) || (ME->digMode == 0) )
			{
				frame_name0.str(""); frame_name0.clear();
				frame_name0 << ME->file_path[ME->file_path_index] << "_"
					<< ((long)ME->img.timestamp.tv_sec) << "_" 
					<< setw( 6 ) << setfill( '0' ) << ((long)ME->img.timestamp.tv_usec) << "_"
					<< setw( 5 ) << setfill( '0' ) << ME->seqcnt << "_" 
					<< setw( 5 ) << setfill( '0' ) << ME->imgcnt << "_"
					<< "0"
					<< ".dat";
				logger->lw(INFO,"IN: Saving image 0 to: %s",frame_name0.str().c_str());
				saveImg(ME->MilImage0.ID, frame_name0.str());
			}
			
			if( (ME->digMode == 2) || (ME->digMode == 1) )
			{
				frame_name1.str(""); frame_name1.clear();
				frame_name1 << ME->file_path[ME->file_path_index] << "_" 
					<< ((long)ME->img.timestamp.tv_sec) << "_" 
					<< setw( 6 ) << setfill( '0' ) << ((long)ME->img.timestamp.tv_usec) << "_"
					<< setw( 5 ) << setfill( '0' ) << ME->seqcnt << "_" 
					<< setw( 5 ) << setfill( '0' ) << ME->imgcnt << "_"
					<< "1"
					<< ".dat";
				// Save image:
				logger->lw(INFO,"IN: Saving image 1 to: %s",frame_name1.str().c_str());
				saveImg(ME->MilImage1.ID, frame_name1.str());
			}
		
			// Increment image counter:
			ME->imgcnt++;
			
			// Display timing results:
			#if DEBUG_MODE == TIMETEST
			// Set desired precision:
			cout.precision(10);
			cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
			cout << "Grab time: " << calcTime(&grabtimer) << endl;
			#endif
		}
		//////////////////////////////////////////
		
		//////////////////////////////////////////
		// Capture OFF:
		else
		{
			if( ME->imgcnt > 0 )
			{
				ME->imgcnt = 0;
				ME->seqcnt++;
			}
		}
		//////////////////////////////////////////
	}
	
	// Kill with grace:
	logger->lw(WARNING, "IN: Exiting...");
	return 0;
}

void* stimg::command(void* arg)
{
	// Get global vars:
	stimg* ME = (stimg*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");
	
	// Starting conditions:
	setSemaphore(ME->semid,1,0);              // capture off
	setSemaphore(ME->semid,2,ME->digMode);    // reset dig mode to whatever it was in the config file
	setSemaphore(ME->semid,3,0);              // set image store dir to zero by default
	ME->seqcnt = getSemaphore(ME->semid, 4);  // restore sequence count
	setSemaphore(ME->semid,5,0);              // reset image counter

	
	// Create command struct
	while( !(*ME->stop) )
	{
		// Kick monitor:
		ME->commandGood = true;
		
		// Update external semaphores:
		setSemaphore(ME->semid,4,ME->seqcnt);
		setSemaphore(ME->semid,5,ME->imgcnt);
		
		// Sleep:
 		usleep( ME->commandSleep );
	}
	
	// Kill with grace:
	logger->lw(WARNING, "CMD: Exiting...");
	return 0;
}

void* stimg::monitor(void* arg)
{
	// Get global vars:
	stimg* ME = (stimg*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"MONITOR: Starting up...");
	
	// Local vars:
	int thesemid;
	
	// Get semid:
	if( (thesemid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
    {
        logger->lw(WARNING, "Unable to grab semaphores (%s)", KICK_PATH);
    }
    else
    {
    	logger->lw(SPAM, "MONITOR: Got semid: %d",thesemid);
    }
		      
	while( !(*ME->stop) )
	{	
 		if( ME->inDataGood   &&
 			ME->commandGood  )
 		{
 			
 			logger->lw(DEBUG, "MONITOR: All threads running well... Kicking the dog.");
 			
 			if( (setSemaphore(thesemid,STIMG_KICK_SEM,1)) == -1)
 			{
 				logger->lw(ERROR, "MONITOR: Unable to set semaphore!");
 				if( ( thesemid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
		        {
		            logger->lw(ERROR, "Unable to grab semaphores (%s)", KICK_PATH);
		        }
 			}
 			else
 			{	
 				// Reset kicks:
 				ME->inDataGood = false;
 				ME->commandGood = false;
 			}
 		
 		}
 		else
 		{
 			logger->lw(SPAM, "MONITOR: Waiting for all threads to kick...");
 		}
 		
 		// Sleep:
 		usleep ( ME->monitorSleep );
	}
	
	// Kill with grace:
	logger->lw(WARNING, "MONITOR: Exiting...");
	return 0;
}

void stimg::setTimer(timeval newinterval)
{
	(*timer).tv_sec = newinterval.tv_sec;
  	(*timer).tv_usec = newinterval.tv_usec;
}
