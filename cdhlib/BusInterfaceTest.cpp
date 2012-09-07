#include "BusInterface.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "starting test" << endl;
	BusInterface myBus;
	portData myData;
	myData.port = "/dev/ttyUSB0";
	myData.baud = 9600;
	myData.outputType = HEX;
	
	
	cout << "Configuring" << endl;
	myBus.configure(myData);
	
	commandData cmd;
	cmd.proc = 1;
	cmd.cmd  = 2;
	cmd.arg1 = 3;
	cmd.arg2 = 4;
	
	commandResp rsp; 
	rsp.length = 2;
	rsp.msg[0] = 'h';
	rsp.msg[1] = 'i';
	
	unsigned int ret = 7;
	
	myBus.writeResponse(&cmd,&rsp,ret);
	
	int returning;
	
	returning = myBus.readCommand(&cmd);
	cout << "reading from port: " << returning << endl;
	
	cout << "reading from port" << endl;
	while( ( returning = myBus.readCommand(&cmd) ) == 0)
	{
		sleep(1);
	}
	
	cout << "return: " << returning << endl;
	if(returning == 1)
	{
		cout << "command: " << endl;
		cout << "proc: " << cmd.proc << endl;
		cout << "cmd: " << cmd.cmd << endl;
		cout << "arg1: " << cmd.arg1 << endl;
		cout << "arg2: " << cmd.arg2 << endl;
	}
	else
	{
		cout << "ERROR!" << endl;
	}
		
	return 0;
}
