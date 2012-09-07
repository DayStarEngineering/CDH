#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "../cdhlib/Command.h"

using namespace std;

void help();
int testArguments(int argc, int actual);
void printOutput(message* msg);

int human = 0;

/*
 * Executes the STCL program.  Parses the command line arguments, and executes.
 */
int main(int argc, char** argv)
{
	int semid;
	message msg;
	CommandWrapper commandWrapper(STCL);
	
	// Initialize Values:
	msg.cmd.proc = 0xFF;
	msg.cmd.type = 0xFF;
	msg.cmd.arg1 = 0xFF;
	msg.cmd.arg2 = 0xFFFF;
	msg.rsp.length = 0;

	// Kick the watchdog
	if((semid=getSemaphoreID(KICK_PATH,NUM_KICK)) == -1)
	{
		// cout << "Error getting watchdog sem." << endl;
	} 
	if (setSemaphore(semid,STCL_KICK_SEM,1) == -1)
    {
        // cout << "Error kicking watchdog." << endl;
    }
		
	// Incorrect arguments, so print help statement:
	if ((argc>=2)&&(strcmp(argv[1],"-h")==0))
	{
		human = 1;
	}
	if (argc<2+human) help();
	
	if (argc<3+human)
	{
		msg.rsp.ret = ERR_INV_NUM_ARG;
		
		if (human)
		{
			cout << "Invalid number of arguments. Must have at least 2!" << endl;
			cout << "'stcl -h' for help!" << endl;
		}
		
		goto OUTPUT;
	}

	// Parse Process:
	if (strcmp(argv[1+human],"all")==0)
	{
		msg.cmd.proc = ALL;
	}
	else if (strcmp(argv[1+human],"stpro")==0)
	{
		msg.cmd.proc = STPRO;
	}
	else if (strcmp(argv[1+human],"stimg")==0)
	{
		msg.cmd.proc = STIMG;
	}
	else if (strcmp(argv[1+human],"stch")==0)
	{
		msg.cmd.proc = STCH;
	}
	else if (strcmp(argv[1+human],"hskpr")==0)
	{
		msg.cmd.proc = HSKPR;
	}
	else if (strcmp(argv[1+human],"pdog")==0)
	{
		msg.cmd.proc = PDOG;
	}
	else if (strcmp(argv[1+human],"dcol")==0)
	{
		msg.cmd.proc = DCOL;
	}
	else if (strcmp(argv[1+human],"stimg")==0)
	{
		msg.cmd.proc = STIMG;
	}
	else if (strcmp(argv[1+human],"sched")==0)
	{
		msg.cmd.proc = SCHED;
	}
	else if (strcmp(argv[1+human],"eps")==0)
	{
		msg.cmd.proc = EPS;
	}
	else
	{
		msg.rsp.ret = ERR_INV_PROC_NAME;
		
		if (human)
		{
			cout << "Invalid argument (" << argv[1+human] << "), must be a valid process name." << endl;
			cout << "'stcl -h' for help!" << endl;
		}
		
		goto OUTPUT;
	}
	
	// Parse Command and Arguments:
	if (strcmp(argv[2+human],"stop")==0)
	{
		if(testArguments(argc,3+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = STOP;
	}
	else if (strcmp(argv[2+human],"start")==0)
	{
		if(testArguments(argc,3+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = START;
	}
	else if (strcmp(argv[2+human],"status")==0)
	{
		if(testArguments(argc,3+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = STATUS;
	}
	else if (strcmp(argv[2+human],"set")==0)
	{
		if(testArguments(argc,5+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = SET;
		msg.cmd.arg1 = atoi(argv[3+human]);
		msg.cmd.arg2 = atoi(argv[4+human]);
	}
	else if (strcmp(argv[2+human],"get")==0)
	{
		if(testArguments(argc,4+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = GET;
		msg.cmd.arg1 = atoi(argv[3+human]);
	}
	else if (strcmp(argv[2+human],"data")==0)
	{
		if(testArguments(argc,5+human)!=0)
		{
			msg.rsp.ret = ERR_INV_NUM_ARG;
			goto OUTPUT;
		}
		
		msg.cmd.type = DATA;
		msg.cmd.arg1 = atoi(argv[3+human]);
		msg.cmd.arg2 = atoi(argv[4+human]);
	}
	else
	{
		msg.rsp.ret = ERR_INV_CMD_NAME;
		
		if (human)
		{
			cout << "Invalid argument (" << argv[2+human] << "), must be a valid command type." << endl;
			cout << "'stcl -h' for help!" << endl;
		}
		
		goto OUTPUT;
	}
			 
	// Everything has now been parsed and checked. Time to execute!
	commandWrapper.execute(&msg);
	
	// GOTO HERE ON ERROR:
	OUTPUT:
	
	// Print the response:
	printOutput(&msg);
	return 0;
}

// Prints out a detailed help statement for when the user doesn't know how to use the program.
void help()
{
	cout << endl
	<< "Usage: stcl <-h> PROCESS/SUBSYSTEM COMMAND [ARG1 [ARG2]]"<<endl
	<< "  stcl: Startracker Commandline Client"<<endl
	<< endl
	<< "Options:"<<endl
	<< "  -h                 Format result and error messages for humans, else machine (hex) response"<<endl
	<< "  PROCESS/SUBSYSTEM  A lowercase string indicating the process name"<<endl
	<< "  COMMAND            A lowercase string indicating the command type"<<endl
	<< "  ARG1               If applicable, the semaphore number"<<endl
	<< "  ARG2               If applicable, the semaphore value"<<endl
	<< endl
	<< "PROCESS or SUBSYSTEM Names:"<<endl
	<< "  all    (all prcocesses)"<<endl
	<< "  stpro  (star tracker processor)"<<endl
	<< "  stimg  (star tracker imager)"<<endl
	<< "  stch   (star tracker command handler)"<<endl
	<< "  hskpr  (house keeper)"<<endl
	<< "  pdog   (process watchdog)"<<endl
	<< "  dcol   (data collector)"<<endl
	<< "  sched  (scheduler)" << endl
	<< "  eps    (EPS subsystem)"<<endl
	<< endl
	<< "COMMAND Names:"<<endl
	<< "  stop   (end process)"<<endl
	<< "  start  (start process)"<<endl
	<< "  status (process / subsystem status)"<<endl
	<< "  set    (set process semaphore / subsystem par to value)"<<endl
	<< "  get    (get process semaphore / subsystem par value)"<<endl
	<< "  data   (get data from subsystem buffer)"<<endl
	<< endl
	<< "Error Returns:"<<endl
	<< "  -----------------------------------------"<<endl
	<< "  Value (hex)_|__________Meaning___________"<<endl
	<< "  0xFFFFFFF0  | Command does not exist"<<endl
	<< "  0xFFFFFFF1  | Invalid number of arguments"<<endl
	<< "  0xFFFFFFF2  | Invalid PROCESS/SUBSYSTEM name"<<endl
	<< "  0xFFFFFFF3  | Invalid COMMAND name"<<endl
	<< "  0xFFFFFFF4  | Semaphore does not exist"<<endl
	<< "  0xFFFFFFF5  | Semaphore init error"<<endl
	<< "  0xFFFFFFF6  | Semaphore get failure"<<endl
	<< "  0xFFFFFFF7  | Semaphore set failure"<<endl
	<< "  0xFFFFFFF8  | Message queue send failure"<<endl
	<< "  0xFFFFFFF9  | Message queue receive failure"<<endl
	<< "  0xFFFFFFFA  | Command timed out"<<endl
	<< "  0xFFFFFFFB  | Port Open Error"<<endl
	<< "  0xFFFFFFFC  | Port Write Error"<<endl
	<< "  0xFFFFFFFD  | Port Read Error"<<endl
	<< "  0xFFFFFFFE  | Message Overflow Error"<<endl
	<< "  0xFFFFFFFF  | Subsystem command not recognized"<<endl
	<< "  -----------------------------------------"<<endl
	<< endl
	<< "Example Calls: "<<endl
	<< " ---------------------------------------------------------------"<<endl
	<< " _stcl_|_PROCESS/SUBSYSTEM_|___COMMAND___|___ARG1____|___ARG2___"<<endl
	<< "  stcl |       all         |  start/stop |    --     |    --    "<<endl
	<< "  stcl |      stpro        |  start/stop |    --     |    --    "<<endl
	<< "  stcl |    stpro/eps      |    status   |    --     |    --    "<<endl
	<< "  stcl |    stpro/eps      |     set     | sem#/par# |    val   "<<endl
	<< "  stcl |    stpro/eps      |     get     | sem#/par# |    --    "<<endl
	<< "  stcl |       eps         |    data     |   buff#   |  # of DP "<<endl
	<< " ---------------------------------------------------------------"<<endl
	<< " Commands [status], [set], [get] cannot be run on [all] processes"<<endl
	<< " Example above uses [stpro], but any process name is valid"<<endl
	<< " All string inputs MUST be lowercase"<<endl
	<< " Values for ARG1 and ARG2 MUST be in the range [0, 255]"<<endl
	<< " Values must be given where specified"<<endl
	<< endl;
	
	exit(1);
}

// Tests length of arguements:
int testArguments(int argc,int actual)
{
	if (argc!=actual)
	{
		if (human)
		{
			cout << "Incorrect number of arguments. Got " << argc << ". Expected " << actual << "." << endl;
		}
		
		return -1;
	}
	
	return 0;
}

// Prints output in human / non-human mode:
void printOutput(message* msg)
{
	if (human)
	{
		cout << "Machine Response: " << "{ "
		     << "0x" << setw( 2 ) << setfill( '0' ) << hex << 0xFF      << ", " 
			 << "0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.proc & 0xFF) << ", " 
			 << "0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.type  & 0xFF) << ", " 
			 << "0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg1 & 0xFF) << ", " 
			 << "0x" << setw( 4 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg2 & 0xFFFF) << ", " 
			 << "0x" << setw( 8 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.ret  & 0xFFFFFFFF) << ", ";
		if(msg->rsp.length > 0)
	    {
	    	cout << "0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned short)msg->rsp.length & 0xFFFF) << ", ";
	    	cout << "0x";
	    	for(int i = 0; i < msg->rsp.length; i++)
	    	{
	    		cout << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.msg[i] & 0xFF);
	    	}
	    	cout << ", ";
	    }
	    cout << " 0x" << 0xFF << " }" << endl;
	    
		cout << "Sent Command:     "                     << endl
		     << "     Process -> 0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.proc & 0xFF)
		     << "        (" << dec << ((unsigned int)msg->cmd.proc & 0xFF) << ") " << endl
		     << "     Command -> 0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.type  & 0xFF)
		     << "        (" << dec << ((unsigned int)msg->cmd.type & 0xFF) << ") " << endl
		     << "     Arg 1   -> 0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg1 & 0xFF)
		     << "        (" << dec << ((unsigned int)msg->cmd.arg1 & 0xFF) << ") " << endl
		     << "     Arg 2   -> 0x" << setw( 4 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg2 & 0xFFFF)
		     << "      (" << dec << ((unsigned int)msg->cmd.arg2 & 0xFFFF) << ") " << endl
		     << "Response:         "                     << endl
		     << "     Return  -> 0x" << setw( 8 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.ret  & 0xFFFFFFFF) 
		     << "  (" << dec << ((unsigned int)msg->rsp.ret & 0xFFFFFFFF) << ") " << endl; 
		if(msg->rsp.length > 0)
	    {
	    	cout << "     Msg Len -> 0x" << setw( 2 ) << setfill( '0' ) << hex << ((unsigned short)msg->rsp.length & 0xFFFF);
	    	cout << "        (" << dec << ((unsigned short)msg->rsp.length & 0xFFFF) << ") " << endl;
	    	cout << "     Message -> 0x";
	    	for(int i = 0; i < msg->rsp.length; i++)
	    	{
	    		cout << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.msg[i] & 0xFF);
	    	}
	    	if (msg->rsp.length < 3)
	    	{
	    		unsigned short temp = 0;
	    		for (int i = 0; i < msg->rsp.length; i++)
	    		{
					temp |= (unsigned short) ((msg->rsp.msg[i] << (msg->rsp.length-i-1)*8) & 0xFFFF);
				}
				if (msg->rsp.length == 1)
				{
					cout << "        (" << dec << ((unsigned int) temp) << ")";
				}
				else if (msg->rsp.length == 2)
				{
					cout << "      (" << dec << ((unsigned int) temp) << ")";
				}
			}
	    	cout << endl;
	    }
	}
	else
	{
		cout << hex << 0xFF 
			 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.proc & 0xFF)
			 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.type  & 0xFF)
			 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg1 & 0xFF)
			 << setw( 4 ) << setfill( '0' ) << hex << ((unsigned int)msg->cmd.arg2 & 0xFFFF)
			 << setw( 8 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.ret  & 0xFFFFFFFF);
	    if(msg->rsp.length > 0)
	    {
	    	cout << setw( 2 ) << setfill( '0' ) << hex << ((unsigned short)msg->rsp.length & 0xFFFF);
	    	for(int i = 0; i < msg->rsp.length; i++)
	    	{
	    		cout << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)msg->rsp.msg[i] & 0xFF);
	    	}
	    }
		cout << 0xFF << endl;
	}
}

