#ifndef COMMANDDATA_H     // Prevent duplicate definition
#define COMMANDDATA_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// Total Number of Process / Subsystem Defines:
#define TOT_PROC 9 // SSM Key
#define TOT_SS   1

// Process Defines & Keys:
#define ALL   0
#define STPRO 1
#define STCH  2
#define HSKPR 3
#define PDOG  4
#define DCOL  5
#define STIMG 6
#define SCHED 7
#define STCL  8
#define SSM   TOT_PROC

// Subsystem Defines
#define EPS   9

// CMD Defines:
#define STOP     0
#define START    1
#define STATUS   2
#define SET      3
#define GET      4
#define DATA     5
#define SHUTDOWN 99 // just for shutting down computer with sched

// Error Return Defines:
#define ERR_CMD_DNE             0xFFFFFFF0
#define ERR_INV_NUM_ARG         0xFFFFFFF1
#define ERR_INV_PROC_NAME       0xFFFFFFF2
#define ERR_INV_CMD_NAME        0xFFFFFFF3
#define ERR_SEM_DNE             0xFFFFFFF4
#define ERR_SEM_INIT			0xFFFFFFF5
#define ERR_SEM_GET			    0xFFFFFFF6
#define ERR_SEM_SET			    0xFFFFFFF7
#define ERR_MSGQ_SEND           0xFFFFFFF8
#define ERR_MSGQ_RECV           0xFFFFFFF9
#define ERR_CMD_TIMEOUT         0xFFFFFFFA
#define ERR_PORT_OPEN_ERROR     0xFFFFFFFB
#define ERR_PORT_WRITE_ERROR    0xFFFFFFFC
#define ERR_PORT_READ_ERROR     0xFFFFFFFD
#define ERR_MSG_OVERFLOW        0xFFFFFFFE
#define ERR_INV_SUBSYS_CMD		0xFFFFFFFF
#define ERR_LWR_BOUND			0xFFFFFFEF

class msg
{
	public:
	long mtype;
	int qid;
	int err;
};

class command
{
	public:
	unsigned char proc;
	unsigned char type;
	unsigned char arg1;
	unsigned short arg2;
};

// Max message length:
#define MAXLEN 1024

class response
{
	public:
	unsigned char msg[MAXLEN];
	unsigned short length;
	unsigned int ret;
};

class message : public msg
{
	public:
	command cmd;
	response rsp;
	
	const char* toString()
	{
		stringstream strm;
		
		strm << endl
			 << "--- MSG ---" << endl
			 << "mtype: " << mtype << endl
			 << "qid:   " << qid << endl
			 << "err:   " << err << endl
			 << "--- CMD ---" << endl
			 << "proc:  " << (unsigned int) cmd.proc << endl
			 << "type:  " << (unsigned int) cmd.type << endl
			 << "arg1:  " << (unsigned int) cmd.arg1 << endl
			 << "arg2:  " << (unsigned int) cmd.arg2 << endl
			 << "--- RSP ---" << endl
			 << "length: " << rsp.length << endl
			 << "msg:    ";
		
		if( rsp.length <= MAXLEN )
		{ 
			for( int i = 0; i < rsp.length; i++ )
			{
	 		     strm << "0x" << hex << (unsigned int) rsp.msg[i] << " ";
	 	    }
 	    }	

		strm << endl << "-----------" << endl;

		return strm.str().c_str();
	}
};

#endif
