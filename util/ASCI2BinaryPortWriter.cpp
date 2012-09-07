#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include "../cdhlib/PortInterface.h"

using namespace std;

int main(int argc, char** argv)
{
	unsigned char* bin_str = NULL;
	PortInterface myPort;
	portData myData;
	int numbytes = 0;
	
	// Incorrect arguments, so print help statement:
	if (argc < 3)
	{
		cout << "Invalid command format." << endl;
		cout << "Expected: asci2bin [/path/to/port] [ASCI string]" << endl;
		goto END;
	}
	
	// Port Data:
	myData.port = argv[1];
	myData.baud = 9600;

	// Send string:
	numbytes = argc-2;
	bin_str = new unsigned char[numbytes];
	
	// Set-up string:
	for(int i = 0; i < numbytes; i++)
	{
		bin_str[i] = (unsigned char) (atoi(argv[i+2]) & 0xFF);
	}
	
	if(myPort.configure(myData)==-1)
	{
		cout << "Error configuring port" << endl;
		goto END;
	}
	
	cout << "Sending: ";
	for(int i = 0; i < numbytes; i++)
	{
		cout << "0x" << setw( 2 ) << setfill( '0' ) << hex << (unsigned int) bin_str[i] << " ";
	}
	cout << endl;
	
	
	if(myPort.writePort((char*)bin_str, numbytes)==-1)
	{
		cout << "Error writing to port" << endl;
		goto END;
	}
	
	// Deallocate memory:
	END:
	if(bin_str != NULL) delete[] bin_str;
	
	return 0;
}
