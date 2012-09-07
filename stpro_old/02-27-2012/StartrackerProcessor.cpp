#include "StartrackerProcessor.h"
	
stpro::stpro(char* theConfig, volatile bool* Stop) : myLogger("STPRO")
{
	// Set thread signal control pointer:
	stop = Stop;
	
	// Innitialize Mutex Locks:
	pthread_mutex_init(&inData,NULL);
	pthread_mutex_init(&outFile,NULL);
	pthread_mutex_init(&outPort,NULL);
	
	// Set writer booleans:
	writeToFile  = false;
	writeToPort  = false;
	
	// Null any heap allocated vars:
	workerThread = NULL;
	workerGood = NULL;
	
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
	
	// Deallocate Memory:
	if( workerThread != NULL)
	{
		delete [] workerThread;
		workerThread = NULL;
	}
	
	if( workerGood != NULL)
	{
		delete [] workerGood;
		workerGood = NULL;
	}
	#if DEBUG_MODE == 1
	if(testImg != NULL)
	{
		delete testImg;
	}
	#endif
	
	pthread_mutex_destroy(&inData);
	pthread_mutex_destroy(&outFile);
	pthread_mutex_destroy(&outPort);
	
	myLogger.lw(INFO,"DESTRUCTOR: STPRO TERMINATED.");
	myLogger.close();
}

int stpro::configure()
{
	// Get thread info:
	numWorkers       = atoi(myConfig["num_workers"].c_str());
	workerThread     = new pthread_t[numWorkers];
	workerGood       = new bool[numWorkers];

	// Get sleep times:
	commandSleep     = atoi(myConfig["command_sleep"].c_str());
	monitorSleep     = atoi(myConfig["monitor_sleep"].c_str());
	
	// Get image info:
	xlen             = atoi(myConfig["xpix_size"].c_str());
	ylen             = atoi(myConfig["ypix_size"].c_str());
	xfov             = atof(myConfig["xfov"].c_str());
	yfov             = atof(myConfig["yfov"].c_str());
	maxStarCount     = atoi(myConfig["max_star_count"].c_str());
	
	// Get file out info:
	writeToFile      = (bool) atoi(myConfig["write_to_file"].c_str());
	numdpperfile     = atoi(myConfig["numdpperfile"].c_str());
	writerData wData;
	wData.partsdir   = myConfig["partsdir"];
	wData.donedir    = myConfig["donedir"];
	wData.filestr    = myConfig["filestr"];
	
	// Configure writer object:
	if( myWriter.configure(wData) != 0 )
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
	
	// Configure test image:
	#if DEBUG_MODE == 1
	testImg = new image;
	if (loadTestImage() < 0)
	{
		myLogger.lw(ERROR,"CONFIG: Failed to load test image. Check the image path!");
		return -1;
	}
	#endif
	
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
	
	// Setup and start all worker threads:
	workerStruct* workerData = NULL;
	workerData = new workerStruct[numWorkers];
	for(int i = 0; i < numWorkers; i++)
	{
		myLogger.lw(INFO,"Creating worker thread: %d",i);
		workerData[i].num = i;
		workerData[i].ME = this;
		rc = pthread_create(&workerThread[i], NULL, stpro::worker, (void *) &workerData[i]);
		if (rc)
		{
			myLogger.lw(ERROR,"WORKER %d: Bad return code from pthread_create() is %d\n", i, rc);
			exit(1);
		}
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

	for(int i = 0; i < numWorkers; i++)
	{
		rc = pthread_join(workerThread[i], NULL);
		if (rc)
		{
			myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
	}
	
	rc = pthread_join(monitorThread, NULL);
	if (rc)
	{
		myLogger.lw(ERROR,"RUN: return code from pthread_join() is %d\n", rc);
		exit(-1);
	}
	
	// Cleaning up:
	myLogger.lw(WARNING,"RUN: All threads have terminated. Dying gracefully.");
	if(workerData != NULL){ delete[] workerData; workerData = NULL; };
	
	return 0;
}

void* stpro::worker(void* arg)
{
	// Get global vars:
	int num = ((workerStruct*) arg)->num;
	stpro* ME = ((workerStruct*) arg)->ME;
	Logger *logger = &(ME->myLogger);
	
	// Stating up...
	logger->lw(INFO,"WORKER %d: Started.",num);
	
	// Construct image:
	image* img = new image;
	if(img->create(ME->xlen,ME->ylen,ME->xfov,ME->yfov) != 0)
	{
		logger->lw(ERROR,"WORKER %d: Failed to create image! (is FOV = 0?)",num);
		return 0;
	}

	// Construct centroid list:
	centroidList* centList = new centroidList;
	if(centList->create(ME->maxStarCount) != 0)
	{
		logger->lw(ERROR,"WORKER %d: Failed to create centroid list!",num);
		return 0;
	}
	
	#if DEBUG_MODE == 1
	// Timing defines:
	timeval startInput;
	timeval startProcess;
	timeval startOutput;
	timeval stopAll;
	#endif
	
	while( !(*ME->stop) )
	{
		// Kick monitor:
		ME->workerGood[num] = true;
		
		#if DEBUG_MODE == 1
		// Start Input:
		gettimeofday(&startInput, NULL);
		#endif
		
		///////////////////////// Grab image: //////////////////////////////////////////
		
		ME->inputData(img);

		////////////////////////////////////////////////////////////////////////////////
		
		#if DEBUG_MODE == 1
		// Start Process:
		gettimeofday(&startProcess, NULL);
		#endif
		
		///////////////////////// Process image: ///////////////////////////////////////
	
		ME->myProcessor.run( img, centList );
	
		////////////////////////////////////////////////////////////////////////////////
		
		#if DEBUG_MODE == 1
		// Start Output:
		gettimeofday(&startOutput, NULL);
		#endif
		
		///////////////////////// Output image: ////////////////////////////////////////
		
		ME->outputData(centList);
		
		////////////////////////////////////////////////////////////////////////////////
		
		#if DEBUG_MODE == 1
		// End Time:
		gettimeofday(&stopAll, NULL);
		// Print Results:
		ME->printTimes(num,startInput,startProcess,startOutput,stopAll);
		#endif
	}
	
	// Cleaning up:
	if(img != NULL)
	{
		delete img;
	}
	
	if(centList != NULL)
	{
		delete centList;
	}
	
	return 0;
}

void* stpro::command(void* arg)
{
	// Get global vars:
	stpro* ME = (stpro*) arg;
	Logger *logger = &(ME->myLogger);
	
	// Start:
	logger->lw(INFO,"CMD: Starting up...");
	
	// Create command struct
	commandData* cmd = new commandData[2];
	int totCmds = 0; //tracks total number of cmds to stpro
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
			if (sendResponse(cmd, 1, totCmds, response) > 1)
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
	bool allGood = false;
	
	// Get semid:
	if( (semid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
    {
        logger->lw(WARNING, "Unable to grab semaphores (%s)", KICK_PATH);
    }
    else
    {
    	logger->lw(SPAM, "MONITOR: Got semid: %d",semid);
    }
	
	// Set all booleans to false to start:
	for(int i = 0; i < ME->numWorkers; i ++)
	{
		ME->workerGood[i] = false;
	}
	ME->commandGood = false;
	
	// Check loop:   
	while( !(*ME->stop) )
	{	
 		// Reset:
 		allGood = true;
 		
 		// Check all threads:
 		for(int i = 0; i < ME->numWorkers; i ++)
 		{
 			if(!ME->workerGood[i])
 			{
 				allGood = false;
 				break;
 			}
 		}
 		
 		if(!ME->commandGood){ allGood = false; }
 		
 		// Kick:
 		if( allGood )
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
 				ME->commandGood = false;
 				
 				for(int i = 0; i < ME->numWorkers; i ++)
		 		{
		 			ME->workerGood[i] = false;
		 		}
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

int stpro::inputData(image* img)
{
	////////////// LOCK ///////////////////
	pthread_mutex_lock(&inData);
	///////////////////////////////////////
	
	// Set timestamp of image:
	gettimeofday(&img->timestamp, NULL);
	
	#if DEBUG_MODE == 1 //timing test
	// Copy over image to local copy as a simulation
	for (int i = 0; i < testImg->xlen; i++)
	{
		for (int j = 0; j < testImg->ylen; j++)
		{
			img->pixel[i][j].val = testImg->pixel[i][j].val;
		}
	}
	#else
	// Set values of shared image struct:
	for(int i = 0; i < img->xlen; i++)
	{
		for(int j = 0; j < img->ylen; j++)
		{
			img->pixel[i][j].val = 2000;
		}
	}
	#endif
	
	////////////// UNLOCK /////////////////
	pthread_mutex_unlock(&inData);
	///////////////////////////////////////
	
	return 0;
}

int stpro::outputData(centroidList* centList)
{
	// Are we configured to write to files?:
	if( writeToFile )
	{
		////////////// LOCK ///////////////////
		pthread_mutex_lock(&outFile);
		///////////////////////////////////////
		
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
		
		////////////// UNLOCK /////////////////
		pthread_mutex_unlock(&outFile);
		///////////////////////////////////////
	}
	
	// Are we configured to write to ports?:
	if( writeToPort )
	{
		////////////// LOCK ///////////////////
		pthread_mutex_lock(&outPort);
		///////////////////////////////////////
		
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
		
		////////////// UNLOCK /////////////////
		pthread_mutex_unlock(&outPort);
		///////////////////////////////////////

	}
	
	return 0;
}

#if DEBUG_MODE == 1
void stpro::printTimes(int num, timeval &startInput, timeval &startProcess, timeval &startOutput, timeval &stopAll)
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

int stpro::loadTestImage()
{
	/*if(testImg->create(2560,2160,5,7) != 0)
	{
		myLogger.lw(ERROR,"LOADTESTIMAGE: Failed to create test image.");
		return -1;
	}*/
	
	myLogger.lw(INFO,"LOADTESTIMAGE: It begins...");
	
	// Set sizes
	testImg->xlen = 2560;
	myLogger.lw(INFO,"LOADTESTIMAGE: xlen = %d",testImg->xlen);
	testImg->ylen = 2160;
	myLogger.lw(INFO,"LOADTESTIMAGE: Sizes set.");
	
	// Allocate memory
	testImg->pixel = new imgPixel*[testImg->xlen];
	for(int i = 0; i < testImg->xlen; i++)
	{
		testImg->pixel[i] = new imgPixel[testImg->ylen];
	}
	myLogger.lw(INFO,"LOADTESTIMAGE: Memory allocated.");
	
	// Innitialize all values to zero
	for(int i = 0; i < testImg->xlen; i++)
	{
		for(int j = 0; j < testImg->ylen; j++)
		{
			testImg->pixel[i][j].val = 0;
			testImg->pixel[i][j].flag = 0;
		}
	}
	myLogger.lw(INFO,"LOADTESTIMAGE: Values innitialized.");
	
	ifstream stream("/home/debug/big_image.txt");
	
	if (!stream) //not open
	{
		myLogger.lw(ERROR,"LOADTESTIMAGE: Error encountered while opening file.");
		return -1;
	}
	// Populate image
	for (int i = 0; i < testImg->xlen; i++)
	{
		for (int j = 0; j < testImg->ylen; j++)
		{
			if (stream.eof())
			{
				myLogger.lw(ERROR,"LOADTESTIMAGE: Invalid number of expected pixels (should be 5529600).");
				return -1;
			}
			stream >> testImg->pixel[i][j].val;
		}
	}
	return 0;
}
#endif
