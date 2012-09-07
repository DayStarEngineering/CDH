#include "PortInterface.h"

PortInterface::PortInterface()
{
	// Set open to false:
	portOpen = false;
	
	
	// Setup mutex locks:
	pthread_mutex_init(&readl,NULL);
    pthread_mutex_init(&writel,NULL);
}

PortInterface::~PortInterface()
{
	// Flush and close the port:
	if(portOpen)
		closePort();
	
	pthread_mutex_destroy(&readl);
    pthread_mutex_destroy(&writel);
}

int PortInterface::configure(portData theData)
{
	if(theData.baud <= 0 || theData.baud > 500000)
		return -1;
	if(theData.port == "")
		return -1;
	/*
	if(theData.outputType < 0 || theData.outputType > 1)
		return -1;
	*/
	// Form global lock name:
	/*
	string temp = "";	
	for(unsigned int i = 0; i < theData.port.length(); i++)
	{
		if( theData.port[i] == '/' )
		{
			temp += "_";
		}
		else
		{
			temp += theData.port[i];
		}
	}

	string write_lock = "/tmp/" + temp + "_w.mut";
	string read_lock  = "/tmp/" + temp + "_r.mut";

	// Open global lock:
	if( (writel = globallock_open(write_lock.c_str())) == NULL )
		return -1;
	if( (readl = globallock_open(read_lock.c_str())) == NULL)
		return -1;
	*/
	
	myData = theData;

	return 0;
}

int PortInterface::openPort() 
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	// Open device:
	fd = open(myData.port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);		
	
	// If port opened, set up our parameters:
	if(fd != -1) 
	{
		struct termios options;

		fcntl(fd, F_SETFL, FNDELAY); // non-blocking read
		//fcntl(fd, F_SETFL,0);      // blocking read
		
		// Save current port settings so nothing is corrupt on exit:
		tcgetattr(fd, &options);
		cfmakeraw(&options);
		
		// Convert integer baud to baud type:
		// Default to 9600 baud if none specified:
		switch (myData.baud)
		{
			case 4800:
				cfsetispeed(&options, B4800); 
				cfsetospeed(&options, B4800);
				break;
			case 9600:
				cfsetispeed(&options, B9600); 
				cfsetospeed(&options, B9600);
				break;
			case 19200:
				cfsetispeed(&options, B19200); 
				cfsetospeed(&options, B19200);
				break;
			case 38400:	
				cfsetispeed(&options, B38400); 
				cfsetospeed(&options, B38400);
				break;
			case 57600:	
				cfsetispeed(&options, B57600); 
				cfsetospeed(&options, B57600);
				break;
			case 115200:	
				cfsetispeed(&options, B115200); 
				cfsetospeed(&options, B115200);
				break;
			case 230400:	
				cfsetispeed(&options, B230400); 
				cfsetospeed(&options, B230400);
				break;
			case 500000:	
				cfsetispeed(&options, B500000); 
				cfsetospeed(&options, B500000);
				break;
			default:
				cfsetispeed(&options, B9600); 
				cfsetospeed(&options, B9600);
				break;
		}

		// Set options for proper port settings:
		options.c_cflag |= (CLOCAL | CREAD);		

		// Turn off hardware flow control:
		options.c_cflag &= ~CRTSCTS;
		options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8; 

		// Write our changes to the port configuration:
		tcsetattr(fd, TCSANOW, &options);
		
		// Set port open:
		portOpen = true;
	}
	// Opening port failed!:
	else 
	{
		// Close the port after error:
		closePort();
		
		// Unlock write:
		pthread_mutex_unlock(&writel);
		
		// Set port open:
		portOpen = false;
		
		return -1;
	}

	// Unlock write:
	pthread_mutex_unlock(&writel);

	return 0;
}

int PortInterface::flushPorts() 
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	// If the port is actually open, flush it:
	if (fd != -1) 
	{
		if(tcflush(fd,TCIOFLUSH) == -1)
		{
			pthread_mutex_unlock(&writel);
			return -1;
		}
		
		// Unlock write:
		pthread_mutex_unlock(&writel);
		
		return 0;
	}
	
	// Unlock write:
	pthread_mutex_unlock(&writel);
	return 0;
}

int PortInterface::flushWritePort() 
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	// If the port is actually open, flush it:
	if (fd != -1) 
	{	
		if(tcflush(fd,TCOFLUSH) == -1)
		{
			pthread_mutex_unlock(&writel);
			return -1;
		}

		// Unlock write:
		pthread_mutex_unlock(&writel);
		
		return 0;
	}
	
	// Unlock write:
	pthread_mutex_unlock(&writel);
	return 0;
}

int PortInterface::flushReadPort() 
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	// If the port is actually open, flush it:
	if (fd != -1) 
	{	
		if(tcflush(fd,TCIFLUSH) == -1)
		{
			pthread_mutex_unlock(&writel);
			return -1;
		}
		
		// Unlock write:
		pthread_mutex_unlock(&writel);
		
		return 0;
	}
	
	// Unlock write:
	pthread_mutex_unlock(&writel);
	return 0;
}

int PortInterface::writePort(string data)
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	if(write(fd,data.c_str(),data.length()) == -1)
	{
		pthread_mutex_unlock(&writel);
		return -1;
	}

	// Unlock write:
	pthread_mutex_unlock(&writel);
	
	return 0;
}

int PortInterface::writePort(char* data)
{
	// Lock write:
	pthread_mutex_lock(&writel);

	for(unsigned int i=0; i < strlen(data); i++)
	{
		unsigned char temp = ((int)data[i]) & 0x000000FF;

		if(write(fd,&temp,1)==-1)
		{
		    pthread_mutex_unlock(&writel);
		    return -1;
		}
	}
	
	// Unlock write
	pthread_mutex_unlock(&writel);
	
	return 0;
}

int PortInterface::writePort(char* data, int length)
{
	// Lock write:
	pthread_mutex_lock(&writel);
	
	for( int i=0; i < length; i++)
	{
		unsigned char temp = ((int)data[i]) & 0x000000FF;
		
		// Write the temp char:
		if(write(fd,&temp,1)==-1)
		{
		    pthread_mutex_unlock(&writel);
		    return -1;
		}
		
	}

	// Unlock write:
	pthread_mutex_unlock(&writel);
	
	return 0;
}

/*
int PortInterface::writeTimeStamp(timeval &theTime)
{
	//if(writePort((char*)&theTime.tv_sec,4) != 0)
	//	return -1;
		
	//if(writePort((char*)&theTime.tv_usec,4) != 0)
	//	return -1;
	
	
	// ASCI:
	if(myData.outputType == ASCII)
	{
		ostringstream oss;
		oss << theTime.tv_sec << " " << theTime.tv_usec << " ";
		return writePort(oss.str());
	}
	else
	{
		return -1;
	}
}
*/
/*
int PortInterface::writeData(double &data)
{
	//if(writePort((char*)&data,8) != 0)
	//	return -1;
		
	//if(writePort((char*)&data,8) != 0)
	//	return -1;
	
	
	// ASCI:
	if(myData.outputType == ASCII)
	{
		ostringstream oss;
		oss << data << " ";
		return writePort(oss.str());
	}
	else
	{
		return -1;
	}
}
*/

int PortInterface::readPort(char* temp)
{	
	return readPort(temp, 1);
}

int PortInterface::readPort(char* temp, int length)
{
	int cnt;
	
	// Lock read:
	pthread_mutex_lock(&readl);
	
	// Read:
	if((cnt = read(fd,temp,length))==-1)
	{
		pthread_mutex_unlock(&readl);
		return -1;
	}
	
	// Unlock read:
	pthread_mutex_unlock(&readl);
	
	return cnt;
}

int PortInterface::bufferCount()
{
	int count;
	// Lock read:
	pthread_mutex_lock(&readl);
	
	// Get buffer count:
	ioctl(fd,FIONREAD, &count);
	
	// Unlock read:
	pthread_mutex_unlock(&readl);

	return count;
}

void PortInterface::closePort() 
{
	// Lock read:
	pthread_mutex_lock(&readl);
	pthread_mutex_lock(&writel);
	
	// If the port is actually open, close it:
	ioctl(fd, TCFLSH, FLUSHR);
	close(fd);
	portOpen = false;
	
	// Unlock read:
	pthread_mutex_unlock(&readl);
	pthread_mutex_unlock(&writel);
}
