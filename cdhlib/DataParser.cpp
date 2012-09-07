
#include "DataParser.h"

///////////////////////////////////////////////////////////////////
// DATA POINT:
///////////////////////////////////////////////////////////////////
DataPoint::DataPoint()
{
	data = NULL;
}

DataPoint::~DataPoint()
{
	if(data != NULL){ delete[] data; data = NULL; }
}

void DataPoint::create(parserData* theData)
{
	data = new unsigned short[theData->vvlen];
}
///////////////////////////////////////////////////////////////////
// DATA PARSER:
///////////////////////////////////////////////////////////////////
DataParser::DataParser()
{
	dataSet = NULL;
	numDP = 0;
	currentSSTime = 0;
}

DataParser::~DataParser()
{
	if(dataSet != NULL){ delete[] dataSet; dataSet = NULL; }
}

int DataParser::configure(parserData theData)
{
	if(theData.bpv < 1 || theData.bpv > 2)
		return -1;
	if(theData.vvlen < 1 || theData.vvlen > 20)
		return -1;
	if(theData.max_dp < 1 || theData.max_dp > 50)
		return -1;
		
	myData = theData;
	
	dataSet = new DataPoint[myData.max_dp];
	for(unsigned int i = 0; i < myData.max_dp; i++ )
		dataSet[i].create(&myData);
		
	return 0;
}

int DataParser::parseData(timeval &currentTime, timeval &newTime, unsigned char* msg, unsigned int length)
{
	numDP = 0;
	unsigned int tempi1, tempi2;
	unsigned short temps;
	unsigned int offset;
	double SStime;
	
	// Length of 1 data set:
	int set_length = TS_LEN + myData.vvlen*myData.bpv;
	
	// Check length against bpv and vvlen!
	if( ( length % set_length ) != 0 )
		return -1;
	// Ensure that total length is not going to overflow our buffer!
	if( ( tempi1 = length / set_length ) > myData.max_dp )
		return -1;
	
	// Store new number of datapoints:
	numDP = tempi1;
	
	// Parse data:
	for( unsigned int i = 0; i < numDP; i++ )
	{
		offset = i*set_length;
		
		// Time stamp (seconds):
		tempi1 = 0;
		for(int k = 0; k < TS_SEC_LEN; k++)
		{
			tempi1 |= (unsigned int) ( msg[ offset + k ] << ( BYTE*(TS_SEC_LEN-1-k) ) );
		}
		
		// Time stamp (fraction of seconds):
		tempi2 = 0;
		for(int k = 0; k < TS_FRAC_LEN; k++)
		{
			tempi2 |= (unsigned int) ( msg[ offset + TS_SEC_LEN + k ] << ( BYTE*(TS_FRAC_LEN-1-k) ) );
		}
		tempi2 *= 1000; // ms to us
		
		// Update current subsystem time:
		SStime = ((double)tempi1) + ((double)(((double)tempi2)/1000000.0)); // May change later depending on subsystem counting scheme!
		
		// Did subsystem go back in time?"
		if(SStime < currentSSTime)
		{
			currentTime = newTime; // Update current time with new time for datacollector!
		}
		
		// Store time stamps:
		currentSSTime = SStime;
		dataSet[i].time_stamp.tv_sec  = ( (long) tempi1 ) + currentTime.tv_sec;
		dataSet[i].time_stamp.tv_usec  = ( (long) tempi2 ) + currentTime.tv_usec;
								
		// Data vector:
		for( unsigned int j = 0; j < myData.vvlen; j++ )
		{
			temps = 0;
			for( unsigned int l = 0; l < myData.bpv; l++ )
			{
				temps |= (unsigned short) ( msg[ offset + TS_LEN + j*myData.bpv + l ] << ( BYTE*(myData.bpv-1-l) ) );
			}
			dataSet[i].data[j] = temps;
		}
	}

	return numDP;
}

int DataParser::getValue(unsigned short &value, unsigned int DP, unsigned int sensorNum)
{
	if( DP > numDP || sensorNum > myData.vvlen )
		return -1;
	
	value = dataSet[DP].data[sensorNum];
		
	return 0;
}

int DataParser::getTS(timeval &timeStamp, unsigned int DP)
{
	if( DP > numDP )
		return -1;
	
	timeStamp = dataSet[DP].time_stamp;
		
	return 0;
}

// Outside class function:
int parseParam(unsigned short &value, unsigned char* msg, unsigned int length)
{
	if(length != 2)
		return -1;
		
	value = (unsigned short) ((msg[0] << BYTE) | msg[1]) & 0xFFFF;
	
	return 0;
}

	
