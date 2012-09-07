
#if !defined(_DATAPARSER_H)
#define _DATAPARSER_H

// C++ Includes:
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

#define TS_SEC_LEN 2   // length of seconds in bytes
#define TS_FRAC_LEN 2  // length of fraction of seconds in bytes
#define TS_LEN 4
#define BYTE 8

/*
 Store data as follows (ex: bpv = 1, vvlen = 3):
 Input - Unsigned char array in form:: 
              [TS_SECONDS][TS_FRAC][DATA][DATA][DATA][TS_SECONDS][TS_FRAC][DATA][DATA][DATA]... etc.
*/
	
struct parserData 
{
	unsigned int bpv;    // bytes per value
	unsigned int vvlen;  // value vector length
	unsigned int max_dp; // max number of data points
};

class DataPoint
{
public:
	// Contructor:
	DataPoint();
	~DataPoint();
	void create(parserData* theData);
	timeval time_stamp;
	unsigned short* data;
};

class DataParser
{
public:
	// Contructor:
	DataParser();
	~DataParser();
	int configure(parserData theData);
	int parseData(timeval &currentTime, timeval &newTime, unsigned char* msg, unsigned int length);
	int getValue(unsigned short &value,  unsigned int DP = 0, unsigned int sensorNum = 0); 
	int getTS(timeval &timeStamp,  unsigned int DP = 0); 
	parserData myData;
	DataPoint* dataSet;
	unsigned int numDP;
	double currentSSTime;
};

int parseParam(unsigned short &value, unsigned char* msg, unsigned int length);

#endif  //_DATAPARSER_H
