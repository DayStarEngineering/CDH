#include <iostream>
#include <cstdio>
#include "../cdhlib/DataWriter.h"

using namespace std;

void parseSTPRO(string inFname);
void parseDCOL(string inFname, int bpv, int vvlen);
bool isSepStr(char str[8]);

/*
 * Executes the DataWriter Parse function from the command line.
 */
int main(int argc, char** argv)
{
	// Incorrect arguments, so print help statement:
	if (argc < 3 || argc > 5)
	{
		cout << "Invalid command format." << endl;
		cout << "Expected: dpcl dcol BPV VVLEN FILENAME" << endl;
		cout << "                 or                   " << endl;
		cout << "Expected: dpcl stpro FILENAME" << endl;
		exit(-1);
	}
	
	if (strcmp(argv[1],"stpro")==0)
	{
		string filestr = argv[2];
		parseSTPRO(filestr);
	}
	else if (strcmp(argv[1],"dcol")==0)
	{
		string filestr = argv[4];
		parseDCOL(filestr,atoi(argv[2]),atoi(argv[3]));
	}
	else
		cout << "Invalid Process Name!" << endl;
	
	return 0;
}

void parseSTPRO(string inFname)
{
	ifstream fin;
	int buffsize = 8;
	int length;
	char* buffer;
	char temp[buffsize];
	char sec[4]; // make an int and do shifting instead to get rid of the warnings!
	char usec[4];
	bool TSFlag = false;
	
  	// Open File:
	fin.open(inFname.c_str(),ios::in | ios::binary);

	// Get length of file:
	fin.seekg (0, ios::end);
	length = fin.tellg();
	fin.seekg (0, ios::beg);

  	buffer = new char[length];
  	
	// Read file into memory:
	fin.read(buffer,length);	

	// Close file:
    fin.close();

    // Set desired precision:
    cout.precision(10);
    cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed

    // Parse and print to terminal:
    for( int i = 0; i < length; i += buffsize )
    {
    	for( int j = 0; j < 8; j++ )
    	{
    		temp[j] = buffer[i+j];
    	}
    	
    	if( isSepStr(temp) )
    	{
    		cout << endl;
    		TSFlag = true;
    	}
    	else 
    	{
    		if( TSFlag )
			{
				for( int j = 0; j < 4; j++ )
				{
					sec[j] = temp[j];
					usec[j] = temp[j + 4];
				}
			
				cout << setw( 10 ) << setfill( '0' ) << *((int*) sec) << " ";
				cout << setw( 10 ) << setfill( '0' ) << *((int*) usec) << " ";
				
				TSFlag = false;
			}
			else
			{
				cout << *((double*) temp) << " ";
			}
		}
    }
    cout << endl;
    
	// Clean up:
  	delete[] buffer;
  	buffer = NULL;
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
			
			if( cnt >= SEPLEN + sizeof(long)*2 + vvlen*bpv )
			{
				cout << setw( 10 ) << setfill( '0' ) << dec << *((unsigned int*) sec) << " ";
				cout << setw( 6 ) << setfill( '0' ) << dec << *((unsigned int*) usec) << " ";
			
				for(int j = 0; j < vvlen; j++)
				{
					cout << "0x" << hex << *((unsigned int*) data[j]) << " ";
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
