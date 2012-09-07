#include "StartrackerProcessor.h"

// We only want grey2bin linked witht this object, none others, so we include this here:
#include "../imglib/grey2bin.h"

itimerval timer;
stpro::stpro(char* theConfig, volatile pthread_mutex_t* mutex_signal, volatile timeval* global_timer, volatile bool* Stop) : myLogger("STPRO")
{
	// Set thread signal control pointer, signal mutex, and timer:
	stop = Stop;
	sigInData = mutex_signal;
	timer = global_timer;
	
	// Thread Synchronization Mutex Locks:
	pthread_mutex_init(&sigProcData,NULL);
	pthread_mutex_init((pthread_mutex_t*)sigInData,NULL);
	pthread_mutex_lock(&sigProcData);                       // Set innitial state to locked (wait)
	pthread_mutex_lock((pthread_mutex_t*)sigInData);        // Set innitial state to locked (wait)
	
	// Monitor variable innitial conditions:
	inDataGood = false;
	procDataGood = false;
/*	outDataGood = false; */
	commandGood = false;
	
	// Set writer booleans:
	writeToFile  = false;
	writeToPort  = false;
	
	// Allocate images:
	img = new image[3];
	
	// Read config:
	myConfig.readfile(theConfig);

	// Write var:
	dpremain = 0;
	
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
	
	// Destroy Sychronization Mutex Locks:
	pthread_mutex_destroy(&sigProcData);
	pthread_mutex_destroy((pthread_mutex_t*)sigInData);
	
	if( img!= NULL)
	{
		delete[] img;
	}
	
	myLogger.lw(INFO,"DESTRUCTOR: STPRO TERMINATED.");
	myLogger.close();
}

int stpro::configure()
{	
	// Get signal information:
	timeval temp;
	temp.tv_sec = atoi(myConfig["signal_sec"].c_str());
  	temp.tv_usec = atoi(myConfig["signal_usec"].c_str());
  	setTimer(temp);
  	
	// Get sleep times:
	commandSleep     = atoi(myConfig["command_sleep"].c_str());
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());
	
	// Configure MIL Wrapper:
    if(MilWrapper.create(&myLogger) != 0)
    	return -1;
    	
    // Configure MIL Digitizer:
    if(MilDigitizer.create(MilWrapper.SysID, myConfig["dig_DCF"].c_str()) != 0)
    	return -1;
    
    // Configure MIL Image Buffers:
    xlen = atoi(myConfig["xpix_size"].c_str());
    ylen = atoi(myConfig["ypix_size"].c_str());
	if(MilImage.create(MilWrapper.SysID, xlen, ylen) != 0)
		return -1;
	
	#if DEBUG_MODE == TIMETEST
	// Configure MIL Display:
	MilDisplay.create(MilWrapper.SysID);
	if(MilTestImage.create(MilWrapper.SysID, xlen, ylen) != 0)
		return -1;	            
	#endif
	
	// Create daystar image buffers:
	for(int i = 0; i < 3; i++ )
	{
		if(img[i].create(xlen,ylen) != 0)
			return -1;
	}
	
	// Get file out info:
	writeToFile      = (bool) atoi(myConfig["write_to_file"].c_str());
	numdpperfile     = atoi(myConfig["numdpperfile"].c_str());
	writerData wData;
	wData.partsdir   = myConfig["partsdir"];
	wData.donedir    = myConfig["donedir"];
	wData.filestr    = myConfig["filestr"];
	calibrationData calData;
	calData.numSensors = 0;
	
	// Configure writer object:
	if( myWriter.configure(wData,calData) != 0 )
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
	if( myPort.configure(pData) != 0 )
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
	cData.maxstars              = atoi(myConfig["max_star_count"].c_str());
	cData.maxstars2return       = atoi(myConfig["max_star_to_return"].c_str());
	cData.xlen                  = xlen;
	cData.ylen                  = ylen;
	cData.fovX                  = atof(myConfig["xfov"].c_str());
	cData.fovY                  = atof(myConfig["yfov"].c_str());
	cData.numpixelsinsubsample  = atoi(myConfig["median_subsample"].c_str());
	
	// Configure processor object:
	if( myProcessor.configure(cData) != 0)
	{
		myLogger.lw(ERROR,"CONFIG: Failed to create configure Centroid object. Check the config file!");
		return -1;
	}
	
	// Create centroid list object:
	if(centList.create(atoi(myConfig["max_star_to_return"].c_str())) != 0)
	{
		myLogger.lw(ERROR,"CONFIG: Failed to create centroid list!");
		return -1;
	}
	
	#if DEBUG_MODE == TIMETEST
	// Configure test image:
	if (loadImg(MilTestImage.ID, myConfig["test_image"]) == -1 )
	{
		myLogger.lw(ERROR,"CONFIG: Failed to load test image. Check the image path!");
		return -1;
	}
	cout << "loaded image" << endl;
	#endif
	return 0;
}

int stpro::run()
{
	itimerval tval;
	int rc=0;
	pthread_attr_t attr;
		
	myLogger.lw(INFO,"RUN: Starting STPRO Run...");
	
	// Setup a thread attribute:
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	
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
	
	// Setup and start the processData thread:
	myLogger.lw(INFO,"RUN: Starting processData thread");
	rc = pthread_create(&procDataThread, &attr, stpro::procData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	
	// Setup and start the outData thread:
	/*
	myLogger.lw(INFO,"RUN: Starting outData thread");
	rc = pthread_create(&outDataThread, &attr, stpro::outData, (void *)this);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: Bad return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
	*/
		
	// Setup and start the monitor thread:
	myLogger.lw(INFO,"RUN: Starting monitor thread");
	rc = pthread_create(&monitorThread, &attr, stpro::monitor, (void *)this);
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
	rc = pthread_join(procDataThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
/*	rc = pthread_join(outDataThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	} */
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

void* stpro::inData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger* logger = &(ME->myLogger);
	TriBuffer* imageIndexer = &(ME->ImageIndexer);
	
	// Setup Indexer:
	int imgBufID = imageIndexer->join();
	int imgIndex = imageIndexer->swap(imgBufID);
	
	// Timers:
	#if DEBUG_MODE == TIMETEST
	timerStruct grabtimer;
	timerStruct copytimer;
	#endif
	
	// Start:
	logger->lw(INFO,"IN: Starting up...");
	
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
		
		// Start main timer:
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&ME->totalTimer[imgIndex].start, NULL);
		gettimeofday(&grabtimer.start,NULL);
		#endif
		
		// Grab Image:
		if( digGrab( ME->MilDigitizer.ID, ME->MilImage.ID ) != 0 )
		{
			
			logger->lw(ERROR,"IN: Unable to grab image from digitizer.");
			
			// continue;
		}
		
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&grabtimer.stop,NULL);
		#endif
		
		// Set timestamp of image:
		gettimeofday(&ME->img[imgIndex].timestamp, NULL);
		
		// Copy MIL Buffer into DayStar Image Buffer:
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&copytimer.start, NULL);
		#endif
		
		#if DEBUG_MODE == TIMETEST
		// For testing with test image:
		if( copyImg( ME->MilTestImage.ID, &ME->img[imgIndex] ) == -1)
		{
			logger->lw(ERROR,"IN: Unable to copy image from MIL to test image.");
			continue;
		}
		
		#else
		// For flight:
		if( copyImg( ME->MilImage.ID, &ME->img[imgIndex] ) == -1)
		{
			logger->lw(ERROR,"IN: Unable to copy image from MIL to daystar image.");
			continue;
		}
		#endif
		
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&copytimer.stop, NULL);
		#endif
		
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&ME->lateTimer[imgIndex].start, NULL);
		#endif
		
		////// RELEASE IMAGE FOR PROCESSING //////
		#if DEBUG_MODE == MEMTEST
		cout << "IN: releasing index " << imgIndex << endl;
		#endif
		imgIndex = imageIndexer->swap(imgBufID);
		#if DEBUG_MODE == MEMTEST
		cout << "IN: grabbing index " << imgIndex << endl;
		#endif
		//////////////////////////////////////////
		
		//^^^^^^^ SIGNAL PROCESS DATA ^^^^^^^^^^^^
		pthread_mutex_trylock(&ME->sigProcData); // Make sure mutex is locked before we unlock it!
		pthread_mutex_unlock(&ME->sigProcData);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		
		
		// Display timing results:
		#if DEBUG_MODE == TIMETEST
		// Set desired precision:
		cout.precision(10);
		cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
		cout << "Grab time: " << calcTime(&grabtimer) << endl;
		cout << "Copy time: " << calcTime(&copytimer) << endl;
		#endif
	}
	
	// Signal Process Data one last time so that it is killed gracefully:
	//^^^^^^^ SIGNAL PROCESS DATA ^^^^^^^^^^^^
	pthread_mutex_trylock(&ME->sigProcData); // Make sure mutex is locked before we unlock it!
	pthread_mutex_unlock(&ME->sigProcData);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
		
	// Kill with grace:
	logger->lw(WARNING, "IN: Exiting...");
	return 0;
}

void* stpro::procData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger* logger = &(ME->myLogger);
	TriBuffer* imageIndexer = &(ME->ImageIndexer);
    
	// Setup Indexer:
	int imgBufID = imageIndexer->join();
	int imgIndex = imageIndexer->swap(imgBufID);
	
	// Timers:
	#if DEBUG_MODE == TIMETEST
	timerStruct g2btimer;
	timerStruct proctimer;
	timerStruct outtimer;
	#endif
	
	// Start:
	logger->lw(INFO,"PROC: Starting up...");
 	
	while( 1 )
	{	
		///////// RESET PROCESSOR ////////////////
		ME->myProcessor.resetFlags();
		//////////////////////////////////////////
		
		//_______ WAIT FOR SIGNAL ________________
		pthread_mutex_lock(&ME->sigProcData);
		//________________________________________
		
		//////// CHECK FOR TERMINATION ///////////
		if(*ME->stop) break;
		//////////////////////////////////////////
		
		/////////// KICK MONITOR ///////////////// 
		ME->procDataGood = true;
		//////////////////////////////////////////
		
		//////// GRAB IMAGE FOR PROCESSING ///////
		#if DEBUG_MODE == MEMTEST
		cout << "PROC: releasing index " << imgIndex << endl;
		#endif
		imgIndex = imageIndexer->swap(imgBufID);
		#if DEBUG_MODE == MEMTEST
		cout << "PROC: grabbing index " << imgIndex << endl;
		#endif
		//////////////////////////////////////////
		
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&ME->lateTimer[imgIndex].stop, NULL);
		#endif
		
		///////// PROCESS IMAGE //////////////////
		// Convert from graycode to binary:
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&g2btimer.start, NULL);
		#endif
		grey2bin(&(ME->img[imgIndex]));
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&g2btimer.stop, NULL);
		#endif
		
		// Centroid image:
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&proctimer.start, NULL);
		#endif
		if( ME->myProcessor.run(&(ME->img[imgIndex]), &(ME->centList)) == -1)
		{
			logger->lw(WARNING, "PROC: Processing image was unsuccessful.");
			continue;
		}
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&proctimer.stop, NULL);
		#endif
		//////////////////////////////////////////
		
		/////////// OUTPUT DATA //////////////////
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&outtimer.start, NULL);
		#endif
		if( ME->outputData(&(ME->centList)) == -1 )
		{
			logger->lw(ERROR, "PROC: Outputing data was unsuccessful.");
			// continue;
		}
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&outtimer.stop, NULL);
		#endif
		//////////////////////////////////////////
		
		// Start main timer:
		#if DEBUG_MODE == TIMETEST
		gettimeofday(&ME->totalTimer[imgIndex].stop,NULL);
		#endif
		
		// Display timing results:
		#if DEBUG_MODE == TIMETEST
		// Set desired precision:
		cout.precision(10);
		cout << "Latency time: " << calcTime(&ME->lateTimer[imgIndex]) << endl;
		cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
		cout << "G2B time: " << calcTime(&g2btimer) << endl;
		cout << "Proc time: " << calcTime(&proctimer) << endl;
		cout << "Out time: " << calcTime(&outtimer) << endl;
		cout << "Total time: " << calcTime(&ME->totalTimer[imgIndex]) << endl;
		#endif
	}
	
	// Kill with grace:
	logger->lw(WARNING, "PROC: Exiting...");
	return 0;
}

/*
void* stpro::outData(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger* logger = &(ME->myLogger);

	// Start:
	logger->lw(INFO,"OUT: Starting up...");
	
	// Create local vars:
	//int temp = -1;
 	//int dpremain = 0;
 	
	while( 1 )
	{
	
		//////// CHECK FOR TERMINATION ///////////
		if(*ME->stop) break;
		//////////////////////////////////////////
		
		/////////// KICK MONITOR ///////////////// 
		ME->outDataGood = true;
		//////////////////////////////////////////

	}
	
	// Kill with grace:
	logger->lw(WARNING, "OUT: Exiting...");
	return 0;
}
*/

void* stpro::command(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");
	
	// Create command struct
	commandData* cmd = new commandData[2];
	cmd[0].proc = STPRO;
	unsigned int ret;
	int response = 1;
	
	while( !(*ME->stop) )
	{
		// Kick monitor:
		ME->commandGood = true;
		
		// Check for a command on stpro
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
 		usleep( ME->commandSleep );
	}
	
	// Kill with grace:
	delete [] cmd;
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
	if( (semid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
    {
        logger->lw(WARNING, "Unable to grab semaphores (%s)", KICK_PATH);
    }
    else
    {
    	logger->lw(SPAM, "MONITOR: Got semid: %d",semid);
    }
		      
	while( !(*ME->stop) )
	{	
 		if( ME->inDataGood   &&
 			ME->procDataGood &&
 		/*	ME->outDataGood  && */
 			ME->commandGood  )
 		{
 			
 			logger->lw(DEBUG, "MONITOR: All threads running well... Kicking the dog.");
 			
 			if( (setSemaphore(semid,STPRO_KICK_SEM,1)) == -1)
 			{
 				logger->lw(ERROR, "MONITOR: Unable to set semaphore!");
 				if( ( semid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
		        {
		            logger->lw(ERROR, "Unable to grab semaphores (%s)", KICK_PATH);
		        }
 			}
 			else
 			{	
 				// Reset kicks:
 				ME->inDataGood = false;
 				ME->procDataGood = false;
 			/*	ME->outDataGood = false; */
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

int stpro::outputData(centroidList* centList)
{
	// Are we configured to write to files?:
	if( writeToFile )
	{	
		// Check if we have filled the file:
		if(dpremain <= 0)
		{
			// Close current file:
			myWriter.closeFile();
	
			// Open a new file for writting:
			myWriter.openFile();
		
			// Reset datapoints remaining:
			dpremain = numdpperfile;
		}
	
		// Write timestamp to file:
		myWriter.writeTimeStamp(centList->timestamp);
	
		// Write data to file:
		for(int i = 0; i < centList->numCentroids; i++)
		{
			myWriter.writeData(centList->centroid[i].x);
			myWriter.writeData(centList->centroid[i].y);
		}

		// Decrement datapoints remaining:
		dpremain--;
	}
	
	// Are we configured to write to ports?:
	if( writeToPort )
	{	
		// Is the port open?:
		if( myPort.isOpen() )
		{
			// Write timestamp to port:
			myPort.writeTimeStamp(centList->timestamp);
			
			// Write data to port:
			for(int i = 0; i < centList->numCentroids; i++)
			{
				myPort.writeData(centList->centroid[i].x);
				myPort.writeData(centList->centroid[i].y);
			}
		}
		else
		{
			// Open port:
			if( myPort.openPort() != 0)
			{
				myLogger.lw(ERROR,"OUTDATA: Port could not be opened!");
			}
			else
			{
				myLogger.lw(INFO,"OUTDATA: Port opened.");
			}
		}
	}
	
	return 0;
}

void stpro::setTimer(timeval newinterval)
{
	(*timer).tv_sec = newinterval.tv_sec;
  	(*timer).tv_usec = newinterval.tv_usec;
}

#if DEBUG_MODE == TIMETEST
void printTimes(int num, timeval &startInput, timeval &startProcess, timeval &startOutput, timeval &stopAll)
{
	// Set desired precision:
    cout.precision(10);
    cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
    
    // Thread number:
    cout << num << " ";
    
	// inTime:
	cout << ((double)(startProcess.tv_sec) + (((double)startProcess.tv_usec)/1000000.0)) -
			((double)(startInput.tv_sec) + (((double)startInput.tv_usec)/1000000.0))
		 << " ";
		 
	// procTime:
	cout << ((double)(startOutput.tv_sec) + (((double)startOutput.tv_usec)/1000000.0)) -
			((double)(startProcess.tv_sec) + (((double)startProcess.tv_usec)/1000000.0))
		 << " ";
	
	// outTime:
	cout << ((double)(stopAll.tv_sec) + (((double)stopAll.tv_usec)/1000000.0)) -
			((double)(startOutput.tv_sec) + (((double)startOutput.tv_usec)/1000000.0))
		 << " ";
	
	// Total Run Time:
	cout << ((double)(stopAll.tv_sec) + (((double)stopAll.tv_usec)/1000000.0)) -
			((double)(startInput.tv_sec) + (((double)startInput.tv_usec)/1000000.0))
		 << endl;
}

int loadTestImage(MIL_ID testimage, unsigned short xpix, unsigned short ypix)
{
	unsigned short temp;
	
	ifstream stream("/home/debug/big_image.txt");
	
	if (!stream) //not open
	{
		cout << "LOADTESTIMAGE: error loading file" << endl;
		return -1;
	}
	
	/*
	myLogger.lw(INFO,"LOADTESTIMAGE: Display empty buffer.");
	autoscaleDisp(MilDisplay.ID);
	dispImg(MilDisplay.ID,MilTestImage.ID);
	sleep(3);
	clearDisp(MilDisplay.ID);
	*/
	
	// Populate image
	for (int i = 0; i < xpix; i++)
	{
		for (int j = 0; j < ypix; j++)
		{
			if (stream.eof())
			{
				cout << "LOADTESTIMAGE: Invalid number of expected pixels (should be 5529600)." << endl;
				return -1;
			}
			
			stream >> temp;
			putPixel(testimage, i, j, &temp);
		}
	}
	
	/*
	myLogger.lw(INFO,"LOADTESTIMAGE: Show filled buffer.");
	dispImg(MilDisplay.ID,MilTestImage.ID);
	sleep(5);
	clearDisp(MilDisplay.ID);
	*/
	
	return 0;
}
#endif
