#include "PortInterface.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "starting test" << endl;


	PortInterface myPort;
	
	// Set up port vars:
	portData myData;
	myData.port = "/dev/ttyS1";
	myData.baud = 9600;
	
	myPort.configure(myData);
	
	cout << "opening port" << endl;
	if(myPort.openPort() != 0)
	{      
		cout << "could not open port" << endl;
	}
	
	cout << "write to port" << endl;
	string str = "Some data to write BABY!\n";
	myPort.writePort(str);            //writes data to serial port
	cout << "write 1" << endl;
	myPort.writePort((char *)str.c_str());
	cout << "write 2" << endl;
	myPort.writePort((char *)str.c_str(), str.length());
	cout << "write 3" << endl;
	
	cout << "Reading... waiting for buffer to fill" << endl;
	char temp[1];
	
	for(;;)
	{
		while(myPort.readPort(temp) > 0)
		{
			cout << temp[0];
		}
		usleep(10000);
	}
	
	cout << "closing port" << endl;
	myPort.flushPorts();
	myPort.closePort();   
	
	return 0;
}
