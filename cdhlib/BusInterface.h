// BusInterface.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef BUSINTERFACE_H     // Prevent duplicate definition
#define BUSINTERFACE_H

//Include:
#include "PortInterface.h"
#include "GlobalLock.h"
#include "CommandData.h"
#include <iomanip>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Defines:
#define HEAD "DAY@"
#define TAIL ":STR"
#define HEADLEN 4 // bytes
#define TAILLEN 4 // bytes
#define CMDLEN  4 // bytes

// Timeout params:
#define TIMEOUT_SLP 100000
#define TIMEOUT_CNT 10

using namespace std;

class BusInterface
{
    public:
	// Constructor:
	BusInterface();

	// Deconstructor:
	~BusInterface();
	
	// Functions:
	int configure(portData thePortData);
	int readCommand(commandData* cmd);
	int writeResponse(commandData* cmd,commandResp* rsp, unsigned int &ret);
    
    private:
    // Vars:
    PortInterface myPort;
    
    // Functions:
    string formASCIIResponse(commandData* cmd,commandResp* rsp, unsigned int &ret);
	void formHexResponse(char* toSendBack, int &length, commandData* cmd,commandResp* rsp, unsigned int &ret);
	int parseCommand(unsigned char* msg, int length);
};

#endif
