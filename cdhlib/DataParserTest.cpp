#include "DataWriter.h"
#include "DataParser.h"
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
	
	DataParser myParser;
	parserData dataP;
	dataP.vvlen = 3;
	dataP.bpv = 2;
	dataP.max_dp = 5;
	
	cout << "Configuring" << endl;
	cout << myWriter.configure(myData,myCalibration) << endl;
	cout << myParser.configure(dataP) << endl;
	cout << "Opening" << endl;
	myWriter.openFile();
	
	cout << "Making Data" << endl;
	unsigned int length = (4+2*3)*4;
	unsigned char data[length];
	for(unsigned int i = 0; i < 4; i++)
	{
		data[i*(4+2*3)] = 0;
		data[i*(4+2*3)+1] = (4-i); 
		data[i*(4+2*3)+2] = 0;
		data[i*(4+2*3)+3] = (4-i);
		for(unsigned int j = 0; j < 2*3; j++)
			data[i*(4+2*3)+4+j] = j;
	}
	
	// Get current time:
	cout << "Timestamping" << endl;
	timeval theTime1;
	gettimeofday(&theTime1, NULL);
	
	sleep(2);
	
	timeval theTime2;
	gettimeofday(&theTime2, NULL);
	
	cout << "Parsing Data" << endl;
	cout << myParser.parseData(theTime1, theTime2, (unsigned char*) &data, length) << endl;
	
	cout << "Getting Data" << endl;
	unsigned short value;
	timeval timeStamp;
	for(unsigned int i = 0; i < 4; i++)
	{
		myParser.getTS(timeStamp, i);
		cout << dec << timeStamp.tv_sec << " " << timeStamp.tv_usec << " ";
		
		for(unsigned int j = 0; j < 3; j++)
		{
			if(myParser.getValue(value, i, j) == 0)
				cout << hex << value << " ";
			else
				cout << "well shit" << endl;
		}
		cout << endl;
	}
	
	cout << "writing" << endl;
	myWriter.writeDataSet(&myParser);

	cout << "closing" << endl;
	
	myWriter.closeFile();
	
	cout << endl;

	return 0;
}
