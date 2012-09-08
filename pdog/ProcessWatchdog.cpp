#include "ProcessWatchdog.h"

ProcessWatchdog::ProcessWatchdog(char* cfgFile, volatile bool* Stop): myLogger("pdog")
{
	stop = Stop;
	
	string key,value;
	processList = NULL;
	
	myConfig.readfile(cfgFile);
	bool filetype;
	filetype=(memcmp(myConfig["logmult"].c_str(),"MULTIFILES",10)==0);
	myLogger.setmaxlen(atoi(myConfig["logsize"].c_str()) KB,filetype);
	myLogger.setlim(atoi(myConfig["loglevel"].c_str()));
	myLogger.lw(INFO,"Process Watchdog Inited");
	myLogger.lw(INFO,"Starting Up...");
	myLogger.open(myConfig["logfile"].c_str());
	myLogger.lw(INFO,"Limiting log to %d size",atoi(myConfig["logsize"].c_str()) KB);
	if(filetype)myLogger.lw(INFO,"file type is MULTIFILES");
	if(!filetype)myLogger.lw(INFO,"file type is SINGLEFILES");
	myLogger.lw(INFO,"Limiting log messages to verbosity level %d and lower.",atoi(myConfig["loglevel"].c_str()));
	processConfig();
	myLogger.lw(INFO,"Watching %d processes",processes);
	myLogger.lw(INFO,"Init Complete.");
}

void ProcessWatchdog::processConfig()
{

	char tmp[10];
	char buffer[1024];
	multimap<string,string>::iterator p;
		
	// Determine the number of actions to configure:
	int numacts = atoi(myConfig["numacts"].c_str());
	if (numacts <= 0)
		myLogger.lw(ERROR,"Invalid # of actions: %d",numacts);
	else
		myLogger.lw(INFO,"Reading %d actions.",numacts);
	string* actList = new string[numacts];

	//Load all the actions to an action array of strings
	p = myConfig.find("action");
	int aread = 0;
	int tempnum = 0;
	if (p != myConfig.end())
	{
		do
		{
			sscanf((*p).second.c_str(),"%d %s",&tempnum,buffer);
			if (tempnum > numacts) exit(-1);
			actList[tempnum] = (*p).second.substr((*p).second.find(buffer,0));
			myLogger.lw(DEBUG,"Action %d recorded as \"%s\"",tempnum,actList[tempnum].c_str());
			++aread;
			++p;
		}
		while (p != myConfig.upper_bound("action"));
	}
	
	// Determine number of processes:
	processes = atoi(myConfig["numprocs"].c_str());
	if (processes<1||processes>500)
		myLogger.lw(FATAL,"Bad numprocesses != [1..500]. numcols=%d",processes);
	else
		myLogger.lw(INFO,"Processing config for %d watchdogs.",processes);
	processList = new Process[processes];

	p = myConfig.find("process");
	int pread = 0;
	tempnum = 0;
	int actnum = 0;
	myLogger.lw(INFO,"Parsing process list.");
	if (p != myConfig.end())
	{
		do
		{
			sscanf(
			    (*p).second.c_str(),
			    "%d %s %d %d %s %d",
			    &tempnum,
			    (char*)&processList[tempnum].name,
			    &processList[tempnum].semaphore_number,
			    &processList[tempnum].timeout,
		            (char*)&tmp,
			    &actnum
			    );
			    
			myLogger.lw(SPAM, "Processesed %d line", tempnum);
			if (tempnum >= processes)
			  {
			    myLogger.lw(ERROR,"Too many process lines");
			  }
			myLogger.lw(SPAM, "Check %d",strncmp(tmp,"SEMAPHORE",9));
			if (strncmp(tmp,"SEMAPHORE",9)==0)
			  {
			    processList[tempnum].check_type = SEMAPHORE;
			  }
			else if (strncmp(tmp,"PROCESS",7)==0)
			  {
			    processList[tempnum].check_type = PROCESS;
			  }
			else if (strncmp(tmp,"SEMTIMEOUT",10)==0)
			  {
			    processList[tempnum].check_type = SEMTIMEOUT;
			  }
			else
			  {
			    processList[tempnum].check_type = PROCESS;
			  }
			
			// Store action:
			processList[tempnum].action = actList[actnum];
			
			myLogger.lw(DEBUG,"Watchdog %d configured.",tempnum);
			++pread;
			//myLogger.lw(DEBUG,"Watchdog %d configured.",tempnum);
			myLogger.lw(SPAM,"ACTION %s",processList[tempnum].action.c_str());
			//myLogger.lw(SPAM,"Process %d has Name %s SEMID %d TIMEOUT %d CHECK %d ACTION %s",tempnum,processList[tempnum].name,processList[tempnum].semaphore_number,processList[tempnum].timeout,processList[tempnum].check_type,processList[tempnum].action);
			++p;
			++tempnum;
			
		}
		while (p != myConfig.upper_bound("process"));
	}

	myLogger.lw(SPAM,"Process Table initilized");
	checkPeriod = atoi(myConfig["chktime"].c_str());
	myLogger.lw(INFO,"Waiting for %d seconds between checks",checkPeriod);
	
	// Release memory:
	delete[] actList;
	actList = NULL;
}

int ProcessWatchdog::run()
{
	int val;
  	time_t cur_time,time_diff;
  	int i;
	bool flag = true;
	string kill;

	// Get the semid for the watchdog:
	if((this->semid=initSemaphores(KICK_PATH, NUM_KICK)) == -1)
	{
		myLogger.lw(ERROR, "Unable to create semaphores (%s,%d) (%s)","semkey",NUM_KICK, strerror(errno));
		if(system("touch /tmp/pdog.sem")!=0)
		{
			myLogger.lw(ERROR,"Semaphore cannot be made.");
		}
		else
		{
			myLogger.lw(INFO,"Semaphore File Created");
			if((semid=initSemaphores(KICK_PATH, NUM_KICK)) == -1)
			{
				myLogger.lw(ERROR,"Unable to create Semaphores");
			}
		}
	}

	myLogger.lw(SPAM, "Got semid=%d",semid);

	for(i=0; i<processes; i++)
	{
		if(setSemaphore(semid,processList[i].semaphore_number,0)==-1)
		{
			myLogger.lw(ERROR, "Unable to set semaphore %d (%s)",processList[i].semaphore_number,strerror(errno));
		}
		processList[i].update_time = time(NULL);
	}

	myLogger.lw(SPAM, "Created %d semaphores",NUM_KICK);
	
	// While still alive...
	while (!(*stop))
	{
		// Loop through processes to check:
		for (i = 0;i<processes;i++)
		{
			// Process type:
			if (processList[i].check_type == PROCESS)
			{
				if (!isRunning(processList[i].name)) 	//see if they are running
				{
					myLogger.lw(ERROR,"Process %s is not running, exec: %s",processList[i].name,processList[i].action.c_str());
					pclose(popen(processList[i].action.c_str(),"r"));
				}
				else
					myLogger.lw(SPAM,"Process %s is running.",processList[i].name);
			}
			
			// Semaphore type:
			else if (processList[i].check_type == SEMAPHORE)
			{
				//myLogger.lw(SPAM,"Checking %d",processList[i].semaphore_number);
				if((val=getSemaphore(semid,processList[i].semaphore_number)) == -1)
				{
			  		myLogger.lw(ERROR,"Unable to check semaphore %d (%s)",processList[i].semaphore_number,strerror(errno));
				}
			 	//myLogger.lw(SPAM,"val=%d",val);
				
				// Process kicked...
			  	if (val == 1)
				{
					if (setSemaphore(semid,processList[i].semaphore_number,0)==-1)
					{
						myLogger.lw(ERROR,"Unable to set semaphore %d (%s)",processList[i].semaphore_number,strerror(errno));
					}
					else
					{
						myLogger.lw(SPAM,"Process %s is kicking.",processList[i].name);
						processList[i].update_time = time(NULL);
					}
				}
				
				// Process not kicked...
			  	else
				{
			  		cur_time = time(NULL);
			  		
			  		// Timeout:
			  		if((time_diff=difftime(cur_time,processList[i].update_time)) > processList[i].timeout)
					{
				  		//Process timeout
						kill = "killall -9 ";
						kill += processList[i].name;
						myLogger.lw(ERROR,"Process %s is not responding, Kill: %s",processList[i].name,kill.c_str());
						sleep(1);
						pclose(popen(kill.c_str(),"r"));
						myLogger.lw(ERROR,"Process %s is not responding, exec: %s",processList[i].name,processList[i].action.c_str());
						pclose(popen(processList[i].action.c_str(),"r"));
						processList[i].update_time = time(NULL);
						continue;
					}
			  		
			  		myLogger.lw(SPAM,"Timediff=%d",time_diff);
				}

				// Check process list...
				if (!isRunning(processList[i].name)) 	//see if they are running
				{
					myLogger.lw(ERROR,"Process %s is not running, exec: %s",processList[i].name,processList[i].action.c_str());
					pclose(popen(processList[i].action.c_str(),"r"));
				}
				else
					myLogger.lw(SPAM,"Process %s is running.",processList[i].name);

				}
				
		  	// Semtimeout:
		  	else if (processList[i].check_type == SEMTIMEOUT)
		  	{
				// Check kick:
				if((val=getSemaphore(semid,processList[i].semaphore_number)) == -1)
				{
					//Error checking the semaphore
					myLogger.lw(ERROR,"Unable to check semaphore %d (%s)",processList[i].semaphore_number,strerror(errno));
				}
				myLogger.lw(SPAM,"val=%d",val);
				
				// Process kicked...
				if (val == 1)
				{
			  		if (setSemaphore(semid,processList[i].semaphore_number,0)==-1)
					{
				  		myLogger.lw(ERROR,"Unable to set semaphore %d (%s)",processList[i].semaphore_number,strerror(errno));
					}
				  	else
					{
						myLogger.lw(DEBUG,"%s has been executed",processList[i].name);
					}
					processList[i].update_time = time(NULL);
					flag=true;
				}
			
				// Process has not kicked...
				else
				{
					cur_time = time(NULL);
				
					// Check timeout:
					if(((time_diff=difftime(cur_time,processList[i].update_time)) > processList[i].timeout) && isRunning(processList[i].name) && flag)
					{
						myLogger.lw(ERROR,"Process %s is not responding after %d sec, Kill: %s",processList[i].name,processList[i].timeout,processList[i].action.c_str());
						pclose(popen(processList[i].action.c_str(),"r"));
						continue;
					}
				
					// Check process list:
				  	if(!isRunning(processList[i].name))
					{
						myLogger.lw(DEBUG,"Reset Process timeout flag");
						flag=false;
					}
				  	
				  	myLogger.lw(SPAM,"Timediff=%d",time_diff);
				}
			}
		}
		
		// Sleep:
		myLogger.lw(SPAM,"Taking a nap");
		sleep(checkPeriod);
	}
	
	cleanup();
	return 0;
}

#define BUFSIZE 1024

bool ProcessWatchdog::isRunning(char* name)
{
	bool ret_val = false;
	string command;
	FILE *output;
	char buf[BUFSIZ];
	command = "ps | grep ";
	command += name;
	command += " | grep -v grep";
	output = popen(command.c_str(),"r");
	if (output != NULL)
	{
		while (fgets(buf, BUFSIZ, output) != NULL)
		{
			ret_val=true;
			break;
		}
	}
	pclose(output);
	return ret_val;
}

void ProcessWatchdog::cleanup()
{	
	myLogger.lw(WARNING,"Caught a signal. Terminating gracefully.");

	if((semid=getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
	{
		myLogger.lw(ERROR,"Unable to get semaphore id for deletion (%s)",strerror(errno));
	}
	
	if(deleteSemaphores(semid)==-1)
	{
		myLogger.lw(ERROR,"Unable to delete semaphores (%s)", strerror(errno));
	}
	else
	{
		myLogger.lw(INFO,"Deleting %d semaphores",NUM_KICK);
	}
	
	
	if(processList != NULL)
	{
		myLogger.lw(INFO,"Cleaning up...");
		delete[] processList;
		processList = NULL;
	}
	else
	{
		myLogger.lw(INFO,"Nothing to clean up...");
	}
	
	myLogger.lw(INFO,"Exiting...");
	myLogger.close();
}
