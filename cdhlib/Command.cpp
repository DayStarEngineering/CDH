#include "Command.h"

CommandWrapper::CommandWrapper(int proc)
{
	myqid = msgQueueWrapper.msgQueueCreate(proc);
	ssmqid = msgQueueWrapper.msgQueueCreate(SSM);
	mytid = syscall(SYS_gettid); // same as gettid() which is not implemented by glibc, provides unique thread/process id
}

CommandWrapper::~CommandWrapper(){}

message CommandWrapper::createMessage(char proc, char type, char arg1, short arg2)
{
	message msg;
	
	msg.qid = myqid;
	msg.mtype = mytid;
	msg.err = 0;
	msg.cmd.proc = proc;
	msg.cmd.type = type;
	msg.cmd.arg1 = arg1;
	msg.cmd.arg2 = arg2;
	msg.rsp.length = 0;
	
	return msg;
}

void CommandWrapper::execute(message* msg)
{	
	// Lets prevent seggies...
	msg->rsp.length = 0;
				
	// Subsystem or Process??
	if(msg->cmd.proc >= TOT_PROC) // Subsystem Block
	{
		msg->err = 0;
		msg->qid = myqid;   // make sure the message come back to by queue
		msg->mtype = mytid; // unique message type for each process / thread
		
		if(msg->cmd.type == STATUS || msg->cmd.type == GET || msg->cmd.type == SET || msg->cmd.type == DATA)
		{
			// cout << msg->toString() << endl;
			if( msgQueueWrapper.msgQueueSend(ssmqid, msg) == -1 )
			{
				msg->rsp.ret = ERR_MSGQ_SEND;
				return;
			}
			
			if( msgQueueWrapper.msgQueueReceive(myqid, msg->mtype, msg) == -1 )
			{
				msg->rsp.ret = ERR_MSGQ_RECV;
				return;
			}
			// cout << msg->toString() << endl;
		}
		else if(msg->cmd.type == STOP || msg->cmd.type == START) // Run start/stop script
		{
			char action[1024];

			// Read in config file:
			configmap myConfig;
			myConfig.readfile("/home/conf/commandlist.xml");
		
			// Form action string:
			sprintf(action,"cmd_%d_%d",(unsigned int)msg->cmd.proc,(unsigned int)msg->cmd.type);

			// Execute action string in config file:
			msg->rsp.ret = system(myConfig[action].c_str())/256;
		
			// Is error?
			if(msg->rsp.ret >= 0xF0)
				msg->rsp.ret = msg->rsp.ret | 0xFFFFFF00;
		}
		else if(msg->cmd.type == SHUTDOWN)
		{
			 system("/home/scripts/rctest.sh; shutdown -P now"); // disable code from starting up again next boot.. and shutdown
		}
		else
		{
			msg->rsp.ret = ERR_INV_CMD_NAME;
		}
	}
	else                        // Process Block
	{
		// Cmd Line or Sem Execute??
		if(msg->cmd.type == STOP || msg->cmd.type == START || msg->cmd.type == STATUS)
		{
			char action[1024];
		
			// Read in config file:
			configmap myConfig;
			myConfig.readfile("/home/conf/commandlist.xml");

			// Check process number:
			if(msg->cmd.proc >= TOT_PROC)
			{
				msg->rsp.ret = ERR_INV_PROC_NAME;
				return;
			}
		
			// Form action string:
			sprintf(action,"cmd_%d_%d",(unsigned int)msg->cmd.proc,(unsigned int)msg->cmd.type);

			// Execute action string in config file:
			msg->rsp.ret = system(myConfig[action].c_str())/256;
		
			// Is error?
			if(msg->rsp.ret >= 0xF0)
				msg->rsp.ret = msg->rsp.ret | 0xFFFFFF00;
		}
		else if(msg->cmd.type == GET || msg->cmd.type == SET)
		{
			int semid;
			const char* path;
			int num_of_sem;
			int ret;
		
			// Get SEMID Vars:
			switch(msg->cmd.proc)
			{
				case ALL:
					msg->rsp.ret = ERR_CMD_DNE;
					return;
				
				case STPRO:
					num_of_sem  = NUM_STPRO;
					path = STPRO_PATH;
					break;
				
				case STCH:
					num_of_sem  = NUM_STCH;
					path = STCH_PATH;
					break;
				
				case HSKPR:
					num_of_sem  = NUM_HSKPR;
					path = HSKPR_PATH;
					break;
				
				case PDOG:
					num_of_sem  = NUM_PDOG;
					path = PDOG_PATH;
					break;
				
				case DCOL:
					num_of_sem  = NUM_DCOL;
					path = DCOL_PATH;
					break;
					
				case STIMG:
					num_of_sem  = NUM_STIMG;
					path = STIMG_PATH;
					break;
				
				case SCHED:
					num_of_sem  = NUM_SCHED;
					path = SCHED_PATH;
					break;
				
				default:
					msg->rsp.ret = ERR_INV_PROC_NAME;
					return;
			}
			
			// Get SEMID:
			if( (semid = initSemaphores(path,num_of_sem)) == -1 )
			{
				msg->rsp.ret = ERR_SEM_INIT;
				return;
			}
		
			// Check sem #:
			if( msg->cmd.arg1 >= num_of_sem )
			{
				msg->rsp.ret = ERR_SEM_DNE;
				return;
			}
			
			if( msg->cmd.type == GET )
			{
				if( (ret = getSemaphore(semid, msg->cmd.arg1)) <= -1 )
				{
					msg->rsp.ret = ERR_SEM_GET;
					return;
				}
				msg->rsp.ret = ret;
			}
			else
			{
				// Send command:
				if( setSemaphore(semid, msg->cmd.arg1, msg->cmd.arg2) <= -1 )
				{
					msg->rsp.ret = ERR_SEM_SET;
					return;
				}
				else
				{
					// Increment command count:
					int cmd_cnt;
					if( ( cmd_cnt = getSemaphore(semid, 0) ) <= -1 )
					{
						msg->rsp.ret = ERR_SEM_GET;
						return;
					}
					if( setSemaphore(semid, 0, cmd_cnt + 1) <= -1 )
					{
						msg->rsp.ret = ERR_SEM_SET;
						return;
					}
					msg->rsp.ret = 1;
				}
			}
		}
		else
		{
			msg->rsp.ret = ERR_INV_CMD_NAME;
			return;
		} 	
	}
}
