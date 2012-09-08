#include "StartrackerProcessor.h"

// Set mutex locks for shared status flags to default values:
pthread_mutex_t	imgStatusLock      = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	centListStatusLock = PTHREAD_MUTEX_INITIALIZER;
	
stpro::stpro(char* theConfig, volatile bool* stop) : myLogger("STPRO")
{
	// Set thread signal control pointer:
	STOP = stop;
	
	// Set monitor booleans to false:
	inDataGood   = false;
	procDataGood = false;
	outDataGood  = false;
	commandGood  = false;
	
	// Set writer booleans:
	writeToFile  = false;
	writeToPort  = false;
	
	// Set innitial values for image status flags:
	imgStatus.write = 0;
	imgStatus.wait  = 1;
	imgStatus.read  = 2;
	
	// Set innitial values for centroid list status flags:
	centListStatus.write = 0;
	centListStatus.wait  = 1;
	centListStatus.read  = 2;
	
	// Read config:
	myConfig.readfile(theConfig);

	// STPRO LOGGER:
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
		myLogger.lw(ERROR,"STPRO not configured correctly!");
		exit(-1);
	}
	else{
		myLogger.lw(INFO,"STPRO correctly configured.");
	}
}

stpro::~stpro()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Deallocate Memory:
	delete [] img;
	delete [] centList;
	centList = NULL;
	img = NULL;
	
	myLogger.lw(INFO,"DESTRUCTOR: STPRO TERMINATED.");
	myLogger.close();
}

int stpro::configure()
{
	// Get sleep times:
	inDataSleep      = atoi(myConfig["inData_sleep"].c_str());
	procDataSleep    = atoi(myConfig["procData_sleep"].c_str());
	outDataSleep     = atoi(myConfig["outData_sleep"].c_str());
	commandSleep     = atoi(myConfig["command_sleep"].c_str());
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());
	
	// Get image info:
	int xlen         = atoi(myConfig["xpix_size"].c_str());
	int ylen         = atoi(myConfig["ypix_size"].c_str());
	double xfov      = atof(myConfig["xfov"].c_str());
	double yfov      = atof(myConfig["yfov"].c_str());
	int maxStarCount = atoi(myConfig["max_star_count"].c_str());
	
	// Create image buffer:
	img = new image[3];
	for( int i = 0; i < 3; i++ )
	{
		if( img[i].create(xlen,ylen,xfov,yfov) != 0)
		{
			myLogger.lw(ERROR,"CONFIG: Failed to create image! (is FOV = 0?)");
			return -1;
		}
	}
	
	// Create centroid list buffer:
	centList = new centroidList[3];
	for( int i = 0; i < 3; i++ )
	{
		if( centList[i].create(maxStarCount) != 0)
		{
			myLogger.lw(ERROR,"CONFIG: Failed to create centroid list!");
			return -1;
		}
	}
		
	// Get file out info:
	writeToFile      = (bool) atoi(myConfig["write_to_file"].c_str());
	numdpperfile     = atoi(myConfig["numdpperfile"].c_str());
	writerData wData;
	wData.partsdir   = myConfig["partsdir"];
	wData.donedir    = myConfig["donedir"];
	wData.filestr    = myConfig["filestr"];
	
	// Configure writer object:
	if( myWriter.configure(wData,&myLogger) != 0 )
	{
		myLogger.lw(ERROR,"CONFIG: Failed to configure writer!");
		return -1;
	}
	
	// Get port out info:
	writeToPort      = (bool) atoi(myConfig["write_to_port"].c_str());
	portData pData;
	pData.port       = myConfig["port"];
	pData.baud       = atoi(myConfig["baud"].c_str());
	pData.outputType = atoi(myConfig["output_type"].c_str());
	
	// Configure port object:
	if( myPort.configure(pData,&myLogger) != 0 )
	{
		myLogger.lw(ERROR,"CONFIG: Failed to configure port!");
		return -1;
	}
	
	// Get processing info:
	centroidData cData;
	cData.bitres   			    = atoi(myConfig["bit_resolution"].c_str());
	cData.numsigma  		  	= atof(myConfig["num_sigma"].c_str());
	cData.minthresh 		    = atoi(myConfig["min_pix_per_star"].c_str());
	cData.maxthresh 		    = atoi(myConfig["max_pix_per_star"].c_str());
	cData.maxstars              = maxStarCount;
	cData.xlen                  = xlen;
	cData.ylen                  = ylen;
	cData.numpixelsinsubsample  = atoi(myConfig["median_subsample"].c_str());
	
	// Configure processor object:
	if( myProcessor.configure(cData,&myLogger) != 0)
	{
		myLogger.lw(ERROR,"CONFIG: Failed to create configure Centroid object. Check the config file!");
		return -1;
	}
	
	return 0;
}

int stpro::run()
{
	myLogger.lw(INFO,"RUN: Starting STPRO Run...");
	
	// Setup a thread attribute:
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	int rc=0;

	// Setup and start the command thread:
	myLogger.lw(INFO,"RUN: Starting command thread");
	rc = pthread_create(&commandThread, &attr, stpro::command, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the inData thread:
	myLogger.lw(INFO,"RUN: Starting inData thread");
	rc = pthread_create(&inDataThread, &attr, stpro::inData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Let inData finish a loading a dataset before starting procData:
	sleep(2);
	
	// Setup and start the processData thread:
	myLogger.lw(INFO,"RUN: Starting processData thread");
	rc = pthread_create(&procDataThread, &attr, stpro::procData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Let processData finish processing a dataset before starting outData:
	sleep(3);
	
	// Setup and start the outData thread:
	myLogger.lw(INFO,"RUN: Starting outData thread");
	rc = pthread_create(&outDataThread, &attr, stpro::outData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, stpro::monitor, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
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
	rc = pthread_join(procDataThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	rc = pthread_join(outDataThread, NULL);
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
	pthread_exit(NULL);
	exit(0);
}

void* stpro::inData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Create local vars:
 	int temp = -1;
	
	// Start:
	logger->lw(INFO,"IN: Starting up...");
	
	///////////////////////////////////////////
	///// Lock image status flag mutex:   /////
	pthread_mutex_lock(&imgStatusLock);
	
	// Set image pointers:
	temp = ME->imgStatus.wait;	
	ME->imgStatus.wait = ME->imgStatus.write; // Set the previously waiting image to writing status
	ME->imgStatus.write = temp;               // Set the previously writing image to waiting status
	
	#if DEBUG_MODE == 2
	logger->lw(SPAM,"inData: write   img: %d",ME->imgStatus.write);
	logger->lw(SPAM,"inData: waiting img: %d",ME->imgStatus.wait);
	#endif
	
	//////// Unlock status flag mutex: ////////
	pthread_mutex_unlock(&imgStatusLock);
	///////////////////////////////////////////

	while( !(*ME->STOP) )
	{	
		#if DEBUG_MODE == 1
		// Start time:
		gettimeofday(&ME->img[ME->imgStatus.write].testTimes.inTime.startTime, NULL);
		#endif
		
		// Kick monitor:
		ME->inDataGood = true;
		
		// Set timestamp of image:
		gettimeofday(&ME->img[ME->imgStatus.write].timestamp, NULL);
		
		// Set values of shared image struct:
		for(int i = 0; i < ME->img[ME->imgStatus.write].xlen; i++)
		{
			for(int j = 0; j < ME->img[ME->imgStatus.write].ylen; j++)
			{
				ME->img[ME->imgStatus.write].pixel[i][j].val = 2000;
			}
		}

		#if DEBUG_MODE == 1
		// End time:
		gettimeofday(&ME->img[ME->imgStatus.write].testTimes.inTime.endTime, NULL);
		#endif
		
		///////////////////////////////////////////
		///// Lock image status flag mutex:   /////
		pthread_mutex_lock(&imgStatusLock);
		
		// Set image pointers:
		temp = ME->imgStatus.wait;	
		ME->imgStatus.wait = ME->imgStatus.write; // Set the previously waiting image to writing status
		ME->imgStatus.write = temp;               // Set the previously writing image to waiting status
		
		#if DEBUG_MODE == 2
		logger->lw(SPAM,"inData: write   img: %d",ME->imgStatus.write);
		logger->lw(SPAM,"inData: waiting img: %d",ME->imgStatus.wait);
		#endif
		
		//////// Unlock status flag mutex: ////////
		pthread_mutex_unlock(&imgStatusLock);
		///////////////////////////////////////////
		
		// Sleep:
 		usleep ( ME->inDataSleep );
	}
	
	// Kill with grace:
	logger->lw(WARNING, "IN: Exiting...");
	return 0;
}

void* stpro::procData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger* logger = &(ME->myLogger);

	// Start:
	logger->lw(INFO,"PROC: Starting up...");

	// Create local vars:
 	int temp = -1;
 	
 	///////////////////////////////////////////
	/// Lock centroid status flag mutex:   ////
	pthread_mutex_lock(&centListStatusLock);
	
	// Set centroid list pointers:
	temp = ME->centListStatus.wait;	
	ME->centListStatus.wait = ME->centListStatus.write; // Set the previously written centList to wait status
	ME->centListStatus.write = temp;                    // Set the previously waiting centList to write status
	
	#if DEBUG_MODE == 2
	logger->lw(SPAM,"procData: write cent: %d",ME->centListStatus.write);
	logger->lw(SPAM,"procData: waiting cent: %d",ME->centListStatus.wait);
	#endif
	
	//////// Unlock status flag mutex: ////////
	pthread_mutex_unlock(&centListStatusLock);
	///////////////////////////////////////////
 	
	while( !(*ME->STOP) )
	{	
		// Kick monitor:
		ME->procDataGood = true;
		
		///////////////////////////////////////////
		///// Lock image status flag mutex:   /////
		pthread_mutex_lock(&imgStatusLock);
		
		// Set image pointers:
		temp = ME->imgStatus.wait;	
		ME->imgStatus.wait = ME->imgStatus.read; // Set the previously read image to wait status
		ME->imgStatus.read = temp;               // Set the previously wait image to read status
		
		#if DEBUG_MODE == 2
		logger->lw(SPAM,"procData: process img: %d",ME->imgStatus.read);
		logger->lw(SPAM,"procData: waiting img: %d",ME->imgStatus.wait);
		#endif
		
		//////// Unlock status flag mutex: ////////
		pthread_mutex_unlock(&imgStatusLock);
		///////////////////////////////////////////
		
		#if DEBUG_MODE == 1
		// Start time:
		gettimeofday(&ME->img[ME->imgStatus.read].testTimes.procTime.startTime, NULL);
		#endif
		
		////////////// For Testing Shared Variables /////////////////////////
		/*
		test = ME->img[ME->imgStatus.read].pixel[0][0].val;
		
		// Check for consistancy in the test data!:
		for(int i = 0; i < ME->xlen; i++)
		{
			for(int j = 0; j < ME->ylen; j++)
			{
				if(test != ME->img[ME->imgStatus.read].pixel[i][j].val)
					logger->lw(ERROR,"PROC: %d != %d",test,ME->img[ME->imgStatus.read].pixel[i][j].val);
			}
		}
		
		test = ((double)rand()/(double)RAND_MAX);
		
		// Copy timestamp from image to centroid list:
		ME->centList[ME->centListStatus.write].timestamp = ME->img[ME->imgStatus.read].timestamp;
		
		for(int i = 0; i < ME->centList[ME->centListStatus.write].numCentroids; i++)
		{
			ME->centList[ME->centListStatus.write].centroid[i].x = test;
		}
		*/
		///////////////////////////////////////////////////////////////////////
		
		// Process Data:
		ME->myProcessor.run( &ME->img[ME->imgStatus.read], &ME->centList[ME->centListStatus.write] );
		
		#if DEBUG_MODE == 1
		// End time:
		gettimeofday(&ME->centList[ME->centListStatus.write].testTimes.procTime.endTime, NULL);
		#endif
		
		///////////////////////////////////////////
		/// Lock centroid status flag mutex:   ////
		pthread_mutex_lock(&centListStatusLock);
		
		// Set centroid list pointers:
		temp = ME->centListStatus.wait;	
		ME->centListStatus.wait = ME->centListStatus.write; // Set the previously written centList to wait status
		ME->centListStatus.write = temp;                    // Set the previously waiting centList to write status
		
		#if DEBUG_MODE == 2
		logger->lw(SPAM,"procData: write cent: %d",ME->centListStatus.write);
		logger->lw(SPAM,"procData: waiting cent: %d",ME->centListStatus.wait);
		#endif
		
		//////// Unlock status flag mutex: ////////
		pthread_mutex_unlock(&centListStatusLock);
		///////////////////////////////////////////
		
		// Sleep:
 		usleep ( ME->procDataSleep );
	}
	
	// Kill with grace:
	logger->lw(WARNING, "PROC: Exiting...");
	return 0;
}

void* stpro::outData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger* logger = &(ME->myLogger);

	// Start:
	logger->lw(INFO,"OUT: Starting up...");
	
	// Create local vars:
	int temp = -1;
 	int dpremain = 0;
 	
	while( !(*ME->STOP) )
	{
		// Kick monitor:
		ME->outDataGood = true;
		
		///////////////////////////////////////////
		/// Lock centroid status flag mutex:   ////
		pthread_mutex_lock(&centListStatusLock);
		
		// Set centroid list pointers:
		temp = ME->centListStatus.wait;	
		ME->centListStatus.wait = ME->centListStatus.read; // Set the previously read centList to wait status
		ME->centListStatus.read = temp;                    // Set the previously waiting centList to read status
		
		#if DEBUG_MODE == 2
		logger->lw(SPAM,"outData: read cent: %d",ME->centListStatus.read);
		logger->lw(SPAM,"outData: waiting cent: %d",ME->centListStatus.wait);
		#endif
		
		//////// Unlock status flag mutex: ////////
		pthread_mutex_unlock(&centListStatusLock);
		///////////////////////////////////////////
		
		#if DEBUG_MODE == 1
		// Start time:
		gettimeofday(&ME->centList[ME->centListStatus.read].testTimes.outTime.startTime, NULL);
		#endif
		
		// Are we configured to write to files?:
		if( ME->writeToFile )
		{
			// Check if we have filled the file:
			if(dpremain <= 0)
			{
				// Close current file:
				ME->myWriter.closeFile();
		
				// Open a new file for writting:
				ME->myWriter.openFile();
			
				// Reset datapoints remaining:
				dpremain = ME->numdpperfile;
			}
		
			// Write timestamp to file:
			ME->myWriter.writeTimeStamp(ME->centList[ME->centListStatus.read].timestamp);
		
			// Write data to file:
			for(int i = 0; i < ME->centList[ME->centListStatus.read].numCentroids; i++)
			{
				ME->myWriter.writeData(ME->centList[ME->centListStatus.read].centroid[i].x);
				ME->myWriter.writeData(ME->centList[ME->centListStatus.read].centroid[i].y);
			}
	
			// Decrement datapoints remaining:
			dpremain--;
		}
		
		// Are we configured to write to ports?:
		if( ME->writeToPort )
		{
			// Is the port open?:
			if( ME->myPort.isOpen() )
			{
				// Write timestamp to port:
				ME->myPort.writeTimeStamp(ME->centList[ME->centListStatus.read].timestamp);
				
				// Write data to port:
				for(int i = 0; i < ME->centList[ME->centListStatus.read].numCentroids; i++)
				{
					ME->myPort.writeData(ME->centList[ME->centListStatus.read].centroid[i].x);
					ME->myPort.writeData(ME->centList[ME->centListStatus.read].centroid[i].y);
				}
			}
			else
			{
				// Open port:
				if( ME->myPort.openPort() != 0)
				{
					logger->lw(ERROR,"OUT: Port could not be opened!");
				}
				else
				{
					logger->lw(INFO,"OUT: Port opened.");
				}
			}
		
		}
		
		#if DEBUG_MODE == 1
		// End time:
		gettimeofday(&ME->centList[ME->centListStatus.read].testTimes.outTime.endTime, NULL);
		// Print Results:
		ME->centList[ME->centListStatus.read].testTimes.printTimes();
		#endif
		
		// Sleep:
 		usleep ( ME->outDataSleep );
 		
	}
	
	// Kill with grace:
	logger->lw(WARNING, "OUT: Exiting...");
	return 0;
}

void* stpro::command(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");

	while( !(*ME->STOP) )
	{
		// Kick monitor:
		ME->commandGood = true;
		
		// Sleep:
 		usleep ( ME->commandSleep );
	}
	
	// Kill with grace:
	logger->lw(WARNING, "CMD: Exiting...");
	return 0;
}

void* stpro::monitor(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"MONITOR: Starting up...");
	
	// Local vars:
	int semid;
	
	// Get semid:
	if( (semid = getSemaphoreID( SEMAPHORE_PATH, NUM_SEMAPHORES ) ) == -1)
    {
        logger->lw(WARNING, "Unable to grab semaphores (%s)", SEMAPHORE_PATH);
    }
    else
    {
    	logger->lw(SPAM, "MONITOR: Got semid: %d",semid);
    }
		      
	while( !(*ME->STOP) )
	{	
 		if( ME->inDataGood   &&
 			ME->procDataGood &&
 			ME->outDataGood  &&
 			ME->commandGood  )
 		{
 			
 			logger->lw(DEBUG, "MONITOR: All threads running well... Kicking the dog.");
 			
 			if( (setSemaphore(semid,STPRO_SEMAPHORE,1)) == -1)
 			{
 				logger->lw(ERROR, "MONITOR: Unable to set semaphore!");
 				if( ( semid = getSemaphoreID( SEMAPHORE_PATH, NUM_SEMAPHORES ) ) == -1)
		        {
		            logger->lw(ERROR, "Unable to grab semaphores (%s)", SEMAPHORE_PATH);
		        }
 			}
 			else
 			{	
 				// Reset kicks:
 				ME->inDataGood = false;
 				ME->procDataGood = false;
 				ME->outDataGood = false;
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

