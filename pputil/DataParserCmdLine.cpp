#include <iostream>
#include <cstdio>
#include <iomanip>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

#define SEPSTR "DAYSTAR:"
#define SEPLEN 8

void parseDCOL(string inFname, int bpv, int vvlen);
bool isSepStr(char str[8]);

/*
 * Executes the DataWriter Parse function from the command line.
 */
int main(int argc, char** argv)
{
	// Incorrect arguments, so print help statement:
	if (argc < 2 || argc > 2)
	{
		cout << "Invalid command format." << endl;
		cout << "Expected: dpcl FILENAME" << endl;
		exit(-1);
	}
	
	string filestr = argv[1];
	parseDCOL(filestr,2,8);

	
	return 0;
}

void parseDCOL(string inFname, int bpv, int vvlen)
{
	ifstream fin;
	int length;
	char* buffer;
	char sec[4];
	char usec[4];
	int vvlencnt = 0;
	int bpvcnt = 0;
	char* sepstr = (char *) SEPSTR;
	int cnt = 0;
	
  	// Open File:
	fin.open(inFname.c_str(),ios::in | ios::binary);

	// Get length of file:
	fin.seekg (0, ios::end);
	length = fin.tellg();
	fin.seekg (0, ios::beg);

  	buffer = new char[length];
  	
  	char** data = new char*[vvlen];
  	for( int l = 0; l < vvlen; l++)
  		data[l] = new char[bpv];
  	
	// Read file into memory:
	fin.read(buffer,length);	

	// Close file:
    fin.close();

    // Parse and print to terminal:
    for( int i = 0; i < length; i++ )
    {
		if( cnt >= SEPLEN + sizeof(long)*2 )
		{
			data[vvlencnt][bpvcnt] = buffer[i];
			
			if( ( bpvcnt = (bpvcnt+1)%bpv ) == 0)
			{
				vvlencnt = (vvlencnt+1)%vvlen;
			}
			cnt++;
			
			if( cnt >= SEPLEN + 8 + vvlen*bpv )
			{
				cout << setw( 10 ) << setfill( '0' ) << dec << *((unsigned int*) sec) << " ";
				cout << setw( 6 ) << setfill( '0' ) << dec << *((unsigned int*) usec) << " ";
			
				for(int j = 0; j < vvlen; j++)
				{
					cout <</* "0x" <<*/ dec << *((unsigned int*) data[j]) << " ";
				}
				cout << endl;
				cnt = 0;
			}
		}
		else if( cnt >= SEPLEN + sizeof(long) )
		{
			//cout << "reading : " << (unsigned int) buffer[i] << " into " << cnt - SEPLEN - 4 << endl;
			usec[cnt - SEPLEN - sizeof(long)] = buffer[i];
			cnt++;
		}
		else if( cnt >= SEPLEN )
		{
			sec[cnt - SEPLEN] = buffer[i];
			cnt++;
		}	
    	else
    	{
    		if( buffer[i] == sepstr[cnt] )
    		{
    			cnt++;
    		}	
    		else if( buffer[i] == sepstr[0] )
    		{
    			cnt = 1;
    		}
    		else
    		{
    			cnt = 0;
    		}	
    	}
    	
    	
    }
    cout << endl;
    
	// Clean up:
  	delete[] buffer;
  	buffer = NULL;
  	for( int l = 0; l < vvlen; l++)
  		delete[] data[l];
  	delete data;
  	data = NULL;
}

bool isSepStr(char str[8])
{
	bool ret = true;
	char* test = (char *) SEPSTR;
	
	for( int j = 0; j < SEPLEN; j++ )
	{
		if(str[j] != test[j])
			return false;
	}
	return ret;
}
