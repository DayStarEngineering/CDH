#include "DataWriter.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "starting test" << endl;
	DataWriter myWriter;
	writerData myData;
	myData.partsdir = "/home/kevin/parts";
	myData.donedir = "/home/kevin/done";
	myData.filestr = "test";
	calibrationData myCalibration;
	myCalibration.numSensors = 0;
	
	cout << "Configuring" << endl;
	myWriter.configure(myData,myCalibration);
	cout << "Opening" << endl;
	myWriter.openFile();
	
	// Get current time:
	cout << "Timestamping" << endl;
	timeval theTime;
	gettimeofday(&theTime, NULL);
	
	myWriter.writeTimeStamp(theTime);
	
	cout << "writing" << endl;
	double hey = 1.123213231;
	myWriter.writeData(hey);
	
	cout << "sleeping 5" << endl;

	cout << "closing" << endl;
	
	myWriter.closeFile();
	
	cout << endl;
	//DataWriter::parseFile("/home/kevin/done/test_1319919419.dat");
	cout << endl;
	cout << endl;

	return 0;
}
