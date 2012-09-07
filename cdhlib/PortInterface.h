// PortInterface.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef PORTINTERFACE_H     // Prevent duplicate definition
#define PORTINTERFACE_H

//Include:
#include "GlobalLock.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <stropts.h>
#include <istream>
#include <fstream>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <termios.h>
#include <sstream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Definition of port output types:
//#define ASCII 0
//#define HEX 1

// Debug:
#define DEBUG_PORT 0

using namespace std;

struct portData
{
	string port;
	int baud;
	//int outputType;
};

class PortInterface
{
    public:
	// Constructor:
	PortInterface();

	// Deconstructor:
	~PortInterface();
	
	// Configuration:
	int configure(portData theData);

	// Public Functions:
	int openPort();     //opens serial port with desired settings
	int flushPorts();                       //flushes serial buffers (read and write ports)
	int flushReadPort();                    //clears read port
	int flushWritePort();                   //flushes write port over serial
	int writePort(string data);            //writes data to serial port
	int writePort(char* data);
	int writePort(char* data, int length);
	//int writeTimeStamp(timeval &theTime);
	//int writeData(double &data);
	int readPort(char* temp);
	int readPort(char* temp, int length);
    int bufferCount();                     //returns a count of data that is contained in the serial buffer
	void closePort();                      //closes serial port
	bool isOpen(){ return portOpen; }
	//int getOutputType(){ return myData.outputType; }
    int getBaud(){ return myData.baud; }
    string getPort(){ return myData.port; }
    
    private:
	// File descriptor:
	int fd;
	// Local Locks:
    pthread_mutex_t readl;
    pthread_mutex_t writel;
    // Port Data:
    bool portOpen;
    portData myData;
};

#endif
