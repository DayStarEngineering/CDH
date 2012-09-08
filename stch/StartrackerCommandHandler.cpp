#include "StartrackerCommandHandler.h"

stch::stch(char* theConfig, volatile bool* Stop): myLogger("STCH"), myBus()
{
	// Set thread signal control pointer:
	stop = Stop;
	
	// Read config:
	myConfig.readfile(theConfig);
	
	// STPRO LOGGER:
	bool filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"CONSTRUCTOR: Startracker Command Handler");
	myLogger.lw(INFO,"CONSTRUCTOR: Starting Up...");
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"CONSTRUCTOR: Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	
	if(configure()!=0){
		myLogger.lw(ERROR,"STCH not configured correctly!");
		exit(-1);
	}
	else{
		myLogger.lw(INFO,"STCH correctly configured.");
	}
}

stch::~stch()
{
	myLogger.lw(INFO,"DESTRUCTOR: Cleaning up.");
	
	// Deallocate Memory:
	
	myLogger.lw(INFO,"DESTRUCTOR: STCH TERMINATED.");
	myLogger.close();
}

int stch::configure()
{
	portData thePortData;
	thePortData.baud       = atoi(myConfig["baud"].c_str());
	thePortData.outputType = atoi(myConfig["output_type"].c_str());
	thePortData.port       = myConfig["port"].c_str();
	
	if( myBus.configure(thePortData) != 0)
	{
		myLogger.lw(ERROR,"CONFIG: Error configuring and opening bus port!");
		return -1;
	}
	
	runSleep =  atoi(myConfig["run_sleep"].c_str());
	
	return 0;
}

int stch::run()
{
	myLogger.lw(INFO,"RUN: Starting STCH Run...");
	
	// Command Variables:
	commandData cmd;
	commandResp rsp; 
	unsigned int cmd_ret;
	int read_ret;
	
	// Spawn command thread... monitor thread??
	
	// Get semid from pdog:
	if( ( semid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
    {
        myLogger.lw(ERROR, "RUN: Unable to grab semaphores (%s)", PDOG_PATH);
    }
	
	while( !(*stop) )
	{	
		// Kick Watchdog:
		if( (setSemaphore(semid,STCH_KICK_SEM,1)) == -1)
		{
			myLogger.lw(ERROR, "RUN: Unable to set semaphore!");
			if( ( semid = getSemaphoreID( KICK_PATH, NUM_KICK ) ) == -1)
	        {
	            myLogger.lw(ERROR, "RUN: Unable to grab semaphores (%s)", PDOG_PATH);
	        }
		}
 			
		// Read from Port:
		if( (read_ret = myBus.readCommand(&cmd)) == 1)
		{
			myLogger.lw(INFO, "RUN: Command found. Executing: %x %x %x %x",cmd.proc,cmd.cmd,cmd.arg1,cmd.arg2);
			
			// Execute Command:
			cmd_ret = execute(&cmd,&rsp);
		
			// Output Response:
			if( myBus.writeResponse(&cmd,&rsp,cmd_ret) < 0)
			{
				myLogger.lw(ERROR, "RUN: Error Sending Response to BUS!");
			}
		}
		else if(read_ret == ((int) ERR_CMD_TIMEOUT) )
		{
			myLogger.lw(ERROR, "RUN: Port timed out!");
		}
		else if(read_ret == ((int) ERR_PORT_READ_ERROR) )
		{
			myLogger.lw(ERROR, "RUN: Port read error!");
		}
		else if(read_ret == 0)
		{	
			myLogger.lw(SPAM, "Nothing in port buffer...");
		}
		else
		{
			myLogger.lw(ERROR, "Unknown error occured!");
		}
		
		usleep(runSleep);
	}
	
	// Cleaning up:
	myLogger.lw(WARNING,"RUN: Dying gracefully.");
	return 0;
}

