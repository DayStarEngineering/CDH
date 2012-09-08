
#if !defined(_DATAWRITER_H)
#define _DATAWRITER_H

// C++ Includes:
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "DataParser.h"

#define SEPSTR "DAYSTAR:"
#define SEPLEN 8

#define DW_DEBUG_MODE 0 //1 for cout debug statements

using namespace std;

//File format:
/*
	"DAYSTAR:" + (4 bytes seconds) + (4 bytes micro seconds) + (data)
*/
			
struct writerData 
{
	string partsdir;
	string donedir;
	string filestr;
	//bool binaryMode;
};
/*
struct calibrationData
{
	unsigned char numSensors;
	double* slope;
	double* intercept;
};
*/
// Image class (struct-like) for allocating and deallocating image memory:
// All variables are public for quick "struct-like" access. We avoid using
// set/get functions for speed.
class DataWriter
{
public:
	// Contructor:
	DataWriter();
	~DataWriter();
	int configure(writerData theData/*, calibrationData theCalibration*/);
	void openFile();
	void writeTimeStamp(timeval theTime);
	void writeData(double data);
	void writeData(unsigned int data);
	void writeData(unsigned short data);
	void writeData(unsigned char* data, int length);
	void writeDataSet(DataParser* DP);
	void flushToFile();
	void closeFile();
	
private:
	// Private variables:
	writerData myData;
	//calibrationData myCalibration;
	string moveStr;
	string fname;
	ofstream fout;
	// Private helper function:
};

#endif  //_DATAWRITER_H
