// SubsystemInterface.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef SUBSYSTEMINTERFACE_H     // Prevent duplicate definition
#define SUBSYSTEMINTERFACE_H

//Include:
#include "PortInterface.h"
#include "GlobalLock.h"
#include "CommandData.h"
#include <iomanip>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

using namespace std;

// Port headers and tails:
#define HEAD "DAY@"
#define HEADLEN 4 // bytes
#define CMDLEN  4 // bytes
#define LENLEN  2 // bytes
#define TIMEOUT_SLEEP 10000

class SubsystemInterface
{
    public:
	// Constructor:
	SubsystemInterface();

	// Deconstructor:
	~SubsystemInterface();
	
	// Functions:
	int configure(portData myData);
	/*
	int status(response* resp);
	int getData(response* resp, unsigned char buffernum, unsigned short numdp);
	int getPar(response* resp, unsigned char parnum);
	int setPar(response* resp, unsigned char parnum, unsigned short value);
    */
    // Lower level functions:
    void command(message* msg);
    //int command(response* resp, unsigned char type, unsigned char arg0, unsigned char arg1, unsigned char arg2);
    
    private:
    // Vars:
    PortInterface myPort;
    pthread_mutex_t myLock;
};

#endif
