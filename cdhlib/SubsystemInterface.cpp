#include "SubsystemInterface.h"

SubsystemInterface::SubsystemInterface() : myPort()
{
	pthread_mutex_init(&myLock,NULL);
}

SubsystemInterface::~SubsystemInterface()
{
	myPort.closePort();
	pthread_mutex_destroy(&myLock);
}

int SubsystemInterface::configure(portData myData)
{
	if(myPort.configure(myData) != 0)
		return ERR_PORT_OPEN_ERROR;
	
	if(myPort.openPort() != 0)
		return ERR_PORT_OPEN_ERROR;
	
	return 0;
}

/*
int SubsystemInterface::status(commandResp* resp)
{
	return command(resp, (unsigned char) STATUS,(unsigned char) 0xFF,(unsigned char) 0xFF,(unsigned char) 0xFF);
}

int SubsystemInterface::getData(commandResp* resp, unsigned char buffernum, unsigned short numdp)
{
	// I CHANGED THIS, BUT IT MAY HAVE BEEN CORRECT BEFORE...LOOK AT setPar()
	unsigned char val0 = (unsigned char) (numdp        & 0xFF);
	unsigned char val1 = (unsigned char) ((numdp >> 8) & 0xFF);
	#if DEBUG_PORT == 1
	cout << "numdp = " << numdp << " val0 = " << hex << (unsigned int) val0 << endl;
	#endif
	return command(resp, (unsigned char)DATA, buffernum, val0, val1);
}

int SubsystemInterface::getPar(commandResp* resp, unsigned char parnum)
{
	return command(resp, (unsigned char)GET, parnum,(unsigned char) 0xFF,(unsigned char) 0xFF);
}

int SubsystemInterface::setPar(commandResp* resp, unsigned char parnum, unsigned short value)
{
	
	// IF THE ORDER OF THE INPUTS IS WRONG, LOOK BACK AT THE SWITCH MADE TO getData()	
	unsigned char val0 = (unsigned char) ((value >> 8) & 0xFF);
	unsigned char val1 = (unsigned char) (value        & 0xFF);
	return command(resp, (unsigned char)SET, parnum, val0, val1);
}
*/

void SubsystemInterface::command(message* msg)
{
	// Command string:
	string data = "";
	
	// Time vars:
	timeval time;
	double t1, t2;
	
	// Counters for indexes:
	int cnt = 0;
	int ind = 0;
	
	// Temp message:
	unsigned char tmp;
	unsigned char tmp_lengthc[2];
	unsigned short tmp_length = 0;
	
	// Define the return value:
	msg->rsp.ret = ERR_CMD_TIMEOUT;
	
	// Set length to zero to start:
	msg->rsp.length = 0;
	
	// Form data string:
	data += HEAD;
	data += msg->cmd.type;
	data += msg->cmd.arg1;
	data += (unsigned char) ((msg->cmd.arg2 >> 8) & 0xFF);
	data += (unsigned char) (msg->cmd.arg2        & 0xFF);

	// Lock port while executing! //
	pthread_mutex_lock(&myLock);
	////////////////////////////////
	
	// Clear any data on read and write ports:
	#if DEBUG_PORT == 1
	cout << "Flushing all ports" << endl;
	#endif
	if(myPort.flushPorts() != 0)
	{
		pthread_mutex_unlock(&myLock);
		msg->rsp.ret = ERR_PORT_WRITE_ERROR;
		return;
	}
	
	// Send Data:
	#if DEBUG_PORT == 1
	cout << "Sending cmd: " << data << " " << hex
	<< " 0x" << (int) (data[0] & 0xFF)
	<< " 0x" << (int) (data[1] & 0xFF)
	<< " 0x" << (int) (data[2] & 0xFF)
	<< " 0x" << (int) (data[3] & 0xFF)
	<< " 0x" << (int) (data[4] & 0xFF)
	<< " 0x" << (int) (data[5] & 0xFF)
	<< " 0x" << (int) (data[6] & 0xFF)
	<< " 0x" << (int) (data[7] & 0xFF)
	<< endl;
	#endif
	if(myPort.writePort(data) != 0)
	{
		pthread_mutex_unlock(&myLock);
		msg->rsp.ret = ERR_PORT_WRITE_ERROR;
		return;
	}
	
	// Flush any remaining data on write port:
	#if DEBUG_PORT == 1
	cout << "Flushing write port" << endl;
	#endif
	
	if(myPort.flushWritePort() != 0)
	{
		pthread_mutex_unlock(&myLock);
		msg->rsp.ret = ERR_PORT_WRITE_ERROR;
		return;
	}
	
	// Get time:
	gettimeofday(&time, NULL);
	t1 = time.tv_sec + (time.tv_usec/1000000.0);
	t2 = t1;
		
	// Wait For Response:
	while((t2-t1) < (1.5 
	#if DEBUG_PORT == 1
	+ 20
	#endif
	) )
	{

		if (myPort.bufferCount() > 0)
		{
			if (myPort.readPort((char*) &tmp, 1) != 1)
			{
				msg->rsp.ret = ERR_PORT_READ_ERROR;
				break;
			}
		
			#if DEBUG_PORT == 1
			cout << "rec: 0x" << setw(2) << setfill('0') << hex << (int) tmp;
			cout << " " << dec << (char) tmp << endl;
			#endif

			// Header:
			if (cnt < (HEADLEN + CMDLEN))
			{
				if (tmp == ((unsigned char) data[cnt])) //middle of header
				{
					cnt++;
				}
				else if (tmp == ((unsigned char) data[0])) //beginning of header
				{
					cnt = 1;
				}
				else
				{
					cnt = 0;
				}
			}
			// Length:
			else if (cnt < (HEADLEN + CMDLEN + LENLEN))
			{
				tmp_lengthc[ind] = tmp;
				cnt++;
				ind++;
				
				if (ind == LENLEN)
				{
					tmp_length = ((tmp_lengthc[0] << 8) | tmp_lengthc[1]) & 0xFFFF;
					ind = 0;
					
					#if DEBUG_PORT == 1
					cout << "length: " << tmp_length << endl;
					#endif
					
					if (tmp_length == 0)
					{
						msg->rsp.ret = ERR_INV_SUBSYS_CMD;
						break;
					}
					else if(tmp_length > MAXLEN)
					{
						msg->rsp.ret = ERR_MSG_OVERFLOW;
						break;
					}
				}
			}
			// Message:
			else if (cnt < (HEADLEN + CMDLEN + LENLEN + tmp_length))
			{
				#if DEBUG_PORT == 1
				cout << "adding " << setw(2) << setfill('0') << hex << (int) tmp << " to index " << ind << " of msg->rsp.msg " << endl;
				#endif
				msg->rsp.msg[ind] = tmp;
				cnt++;
				ind++;
				
				// Copy over message after all has been recieved:
				if(cnt >= (HEADLEN + CMDLEN + LENLEN + tmp_length) )
				{
					msg->rsp.length = tmp_length;
					msg->rsp.ret = 1;
					break;
				}
			}
		}
		else
		{
			usleep(TIMEOUT_SLEEP
			#if DEBUG_PORT == 1
			+ 500000
			#endif
			); // Sleep 10 ms
		}
		
		
		#if DEBUG_PORT == 1
		cout << "byte " << dec << (cnt + 1) << ":" << endl;
		#endif
		
		// Check time:
		gettimeofday(&time, NULL);
		t2 = time.tv_sec + (time.tv_usec/1000000.0);
	}
	
	// Unlock port                //
	pthread_mutex_unlock(&myLock);
	////////////////////////////////
}

/*
int SubsystemInterface::command(response* resp, unsigned char type, unsigned char arg0, unsigned char arg1, unsigned char arg2)
{
	// Command string:
	string data = "";
	
	// Time vars:
	timeval time;
	double t1, t2;
	
	// Counters for indexes:
	int cnt = 0;
	int ind = 0;
	
	// Temp message:
	unsigned char tmp;
	unsigned char tmp_msg[MAXLEN];
	unsigned char tmp_lengthc[2];
	unsigned short tmp_length = 0;
	
	// Define the return value:
	int retval = ERR_CMD_TIMEOUT;
	
	// Form data string:
	data += HEAD;
	data += type;
	data += arg0;
	data += arg1;
	data += arg2;

	
	//#if DEBUG_PORT == 1
	//data = "";
	//data += HEAD;
	//data += 0x33;
	//data += 0x33;
	//data += 0x33;
	//data += 0x33;
	//#endif
	
	// Set length to zero to start:
	resp->length = 0;
	
	// Lock port while executing! //
	pthread_mutex_lock(&myLock);
	////////////////////////////////
	
	// Clear any data on read and write ports:
	#if DEBUG_PORT == 1
	cout << "Flushing all ports" << endl;
	#endif
	if(myPort.flushPorts() != 0)
	{
		pthread_mutex_unlock(&myLock);
		return ERR_PORT_WRITE_ERROR;
	}
	
	// Send Data:
	#if DEBUG_PORT == 1
	cout << "Sending cmd: " << data << " " << hex
	<< " 0x" << (int) (data[0] & 0xFF)
	<< " 0x" << (int) (data[1] & 0xFF)
	<< " 0x" << (int) (data[2] & 0xFF)
	<< " 0x" << (int) (data[3] & 0xFF)
	<< " 0x" << (int) (data[4] & 0xFF)
	<< " 0x" << (int) (data[5] & 0xFF)
	<< " 0x" << (int) (data[6] & 0xFF)
	<< " 0x" << (int) (data[7] & 0xFF)
	<< endl;
	#endif
	if(myPort.writePort(data) != 0)
	{
		pthread_mutex_unlock(&myLock);
		return ERR_PORT_WRITE_ERROR;
	}
	
	// Flush any remaining data on write port:
	#if DEBUG_PORT == 1
	cout << "Flushing write port" << endl;
	#endif
	
	if(myPort.flushWritePort() != 0)
	{
		pthread_mutex_unlock(&myLock);
		return ERR_PORT_WRITE_ERROR;
	}
	
	// Get time:
	gettimeofday(&time, NULL);
	t1 = time.tv_sec + (time.tv_usec/1000000.0);
	t2 = t1;
		
	// Wait For Response:
	while((t2-t1) < (0.5 
	#if DEBUG_PORT == 1
	+ 20
	#endif
	) )
	{

		if (myPort.bufferCount() > 0)
		{
			if (myPort.readPort((char*) &tmp, 1) != 1)
			{
				retval = ERR_PORT_READ_ERROR;
				break;
			}
		
			#if DEBUG_PORT == 1
			cout << "rec: 0x" << setw(2) << setfill('0') << hex << (int) tmp;
			cout << " " << dec << (char) tmp << endl;
			#endif

			// Header:
			if (cnt < (HEADLEN + CMDLEN))
			{
				if (tmp == ((unsigned char) data[cnt])) //middle of header
				{
					cnt++;
				}
				else if (tmp == ((unsigned char) data[0])) //beginning of header
				{
					cnt = 1;
				}
				else
				{
					cnt = 0;
				}
			}
			// Length:
			else if (cnt < (HEADLEN + CMDLEN + LENLEN))
			{
				tmp_lengthc[ind] = tmp;
				cnt++;
				ind++;
				
				if (ind == LENLEN)
				{
					tmp_length = ((tmp_lengthc[0] << 8) | tmp_lengthc[1]) & 0xFFFF;
					ind = 0;
					
					#if DEBUG_PORT == 1
					cout << "length: " << tmp_length << endl;
					#endif
					
					if (tmp_length == 0)
					{
						retval = ERR_INV_SUBSYS_CMD;
						break;
					}
					else if(tmp_length > MAXLEN)
					{
						retval = ERR_MSG_OVERFLOW;
						break;
					}
				}
			}
			// Message:
			else if (cnt < (HEADLEN + CMDLEN + LENLEN + tmp_length))
			{
				tmp_msg[ind] = tmp;
				cnt++;
				ind++;
				
				// Copy over message after all has been recieved:
				if(cnt >= (HEADLEN + CMDLEN + LENLEN + tmp_length) )
				{
					resp->length = tmp_length;
					
					for(ind = 0; ind < tmp_length; ind++)
					{
						resp->msg[ind] = tmp_msg[ind];
					}
					
					retval = 1;
					break;
				}
			}
		}
		else
		{
			usleep(TIMEOUT_SLEEP
			#if DEBUG_PORT == 1
			+ 500000
			#endif
			); // Sleep 10 ms
		}
		
		
		#if DEBUG_PORT == 1
		cout << "byte " << dec << (cnt + 1) << ":" << endl;
		#endif
		
		// Check time:
		gettimeofday(&time, NULL);
		t2 = time.tv_sec + (time.tv_usec/1000000.0);
	}
	
	// Unlock port                //
	pthread_mutex_unlock(&myLock);
	////////////////////////////////

	return retval;
}*/

