
#include "DataWriter.h"

DataWriter::DataWriter()
{
	moveStr = "";
	fname = "";
	//myCalibration.slope = NULL;
	//myCalibration.intercept = NULL;
}

DataWriter::~DataWriter()
{
	// Deallocate Memory:
	/*
	if (myCalibration.slope != NULL)
	{
		delete [] myCalibration.slope;
		myCalibration.slope = NULL;
	}
	if (myCalibration.intercept != NULL)
	{
		delete [] myCalibration.intercept;
		myCalibration.intercept = NULL;
	}
	*/
	closeFile();
}

int DataWriter::configure(writerData theData/*, calibrationData theCalibration*/)
{
	if (theData.partsdir == "")
		return -1;
	if (theData.donedir == "")
		return -1;
	if (theData.filestr == "")
		return -1;	
	/*
	if (theCalibration.numSensors != 0)
	{
		if (theCalibration.slope == NULL)
			return -1;
		if (theCalibration.intercept == NULL)
			return -1;
	}
	*/
	//myCalibration = theCalibration;
	myData = theData;
	
	return 0;
}

void DataWriter::openFile()
{
	// Get current time:
	timeval theTime;
	gettimeofday(&theTime, NULL);
	
	// Get file name and move string:
	stringstream time;
	time << ((long)theTime.tv_sec);
	//if (myData.binaryMode)
	//{
		fname = myData.partsdir+"/"+myData.filestr+"_"+time.str()+".dat";
	//}
	/*
	else
	{
		fname = myData.partsdir+"/"+myData.filestr+"_ASCII_"+time.str()+".csv";
	}*/
	
	#if DW_DEBUG_MODE == 1
	cout << "Date to be stored in " << fname << endl;
	#endif
	
	moveStr = "mv "+fname+" "+myData.donedir + "/";
	
	// Open file:
	//if (myData.binaryMode)
	//{
		fout.open(fname.c_str(),ios::out | ios::binary);
	//}
	//else
	//{
	//	fout.open(fname.c_str(),ios::out);
	//}
}

void DataWriter::writeTimeStamp(timeval theTime) 
{
	// Write separation string:
	fout.write(SEPSTR,SEPLEN);

	// Write seconds and microseconds since epoch:
	fout.write((char*)&theTime.tv_sec,sizeof(long));
	//cout << "saving: " << sizeof(long) << " bytes " << theTime.tv_usec << endl;
	fout.write((char*)&theTime.tv_usec,sizeof(long));
}

void DataWriter::writeData(double data)
{	
	// Write data:
	fout.write((char*)&data,sizeof(double));
}

void DataWriter::writeData(unsigned int data)
{	
	// Write data:
	fout.write((char*)&data,sizeof(unsigned int));
}

void DataWriter::writeData(unsigned short data)
{	
	// Write data:
	fout.write((char*)&data,sizeof(unsigned short));
}

void DataWriter::writeData(unsigned char* data, int length)
{	
	// Write data:
	fout.write((char*)data,length);
}

void DataWriter::flushToFile()
{
	fout.flush();
}

void DataWriter::writeDataSet(DataParser* DP)
{
	//double voltage, slope, intercept;
	
	//#if DW_DEBUG_MODE == 1
	//cout << "binary mode?: " << myData.binaryMode << endl;
	//#endif
	//cout << "Writing " << DP->numDP << " data points" << endl;
	for(unsigned int i = 0; i < DP->numDP; i++)
	{
		//if (myData.binaryMode)
		//{
			writeTimeStamp(DP->dataSet[i].time_stamp);
			//cout << "Writing timestamp: " << DP->dataSet[i].time_stamp.tv_sec << endl;
		//}
		
		for(unsigned int j = 0; j < DP->myData.vvlen; j++)
		{
			//#if DW_DEBUG_MODE == 1
			//cout<<"data["<<j<<"]: "<<"0x"<<setw(4)<<setfill('0')<<hex<<DP->dataSet[i].data[j];
			//cout<<" ("<<dec<<(int)DP->dataSet[i].data[j]<<")";
			//cout<<" -> "<<(double)(((int)DP->dataSet[i].data[j])/16384.0)<<" V"<<endl;
			//#endif
			
			/*
			if (myData.binaryMode)
			{
			*/
				writeData(DP->dataSet[i].data[j]);
				//cout << "Writing data: " << DP->dataSet[i].data[j] << endl;
			/*
			}
			else
			{
				voltage = (double) (((int)DP->dataSet[i].data[j])/16384.0);
				slope = myCalibration.slope[j];
				intercept = myCalibration.intercept[j];
				
				fout.setf(ios::fixed,ios::floatfield);
				fout.precision(2);
				fout.width(7);
				fout << right << (voltage-intercept)/slope << ", ";
			}
			*/
		}
		/*
		if (!myData.binaryMode)
		{
			fout << endl;
		}
		*/
	}
}

void DataWriter::closeFile()
{
	int ret;
	// Flush / Close / & Move the old file:
	if(fout.is_open())
	{
		#if DW_DEBUG_MODE == 1
		cout << "close() found an open file" << endl;
		#endif
		fout.flush();
		fout.close();
	}
	(void) (ret = system(moveStr.c_str()));
}
