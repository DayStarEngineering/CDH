#include "BusInterface.h"

BusInterface::BusInterface() : myPort(){}

BusInterface::~BusInterface()
{
	myPort.closePort();
}

int BusInterface::configure(portData thePortData)
{
	if(myPort.configure(thePortData) != 0)
		return -1;

	if(myPort.openPort() != 0)
		return -1;
	
	return 0;
}

int BusInterface::readCommand(commandData* cmd)
{	
	int cnt;
	if( ( cnt = myPort.bufferCount() ) > 0 ) // We have data!
	{
		unsigned char msg[CMDLEN];
		int retval = 0;
		if( (retval = parseCommand((unsigned char*)&msg,CMDLEN)) == 1 )
		{
			#if DEBUG_PORT == 1
			cout << "filling data" << endl;
			#endif
			cmd->proc = (msg[0] & 0xFF);
			cmd->cmd  = (msg[1] & 0xFF);
			cmd->arg1 = (msg[2] & 0xFF);
			cmd->arg2 = (msg[3] & 0xFF);
			#if DEBUG_PORT == 1
			cout << "returning" << endl;
			#endif
			return retval;
		}
		// Error occured:
		else
		{
			return retval;
		}
	}
	else
	{
		#if DEBUG_PORT == 1
		cout << "buffer: " << cnt << endl;
		#endif
		return 0;
	}
}

int BusInterface::parseCommand(unsigned char* msg, int length)
{
	// Command string:
	string data = "";
	data += HEAD;
	data += TAIL;
	
	// Head and Tail Counters:
	int cnt = 0;
	
	// Buffers:
	char tmp;

	// Control bools:
	bool headerFound = false;
	bool msgFound = false;
	
	// Timeout Counter:
	int time_out = 0;
	
	// Check buffer & read:
	for(int ii = 0; ii < HEADLEN; ii++)
	{
		if((cnt = myPort.bufferCount()) > 0)
		{
			if(myPort.readPort(&tmp, 1) != 1)
			{
				return ERR_PORT_READ_ERROR;
			}
			
			#if DEBUG_PORT == 1
			cout << tmp << endl;
			#endif
	
			if(tmp == ((unsigned char)data[ii])) // Middle of header
			{
				#if DEBUG_PORT == 1
				cout << "head: " << ii << endl;
				#endif
					
				if(ii == (HEADLEN-1))
				{
					headerFound = true;
				}
			}
			else if(tmp == ((unsigned char)data[0])) // If its beginning of header
			{
				ii = 0;
				#if DEBUG_PORT == 1
				cout << "head: " << 0 << endl;
				#endif
			}
			else
			{
				#if DEBUG_PORT == 1
				cout << "head sucks" << endl;
				#endif
				continue;
			}
		}
		else
		{
			usleep(TIMEOUT_SLP); // Sleep 100 ms
			ii--;
			time_out++;
			
			#if DEBUG_PORT == 1
			cout << "time" << endl;
			#endif
			
			if(time_out >= TIMEOUT_CNT)
				return ERR_CMD_TIMEOUT;
		}
	}
	time_out = 0;
		
	
	if(headerFound)
	{
		#if DEBUG_PORT == 1
		cout << "header found" << endl;
		#endif
		for(int ii = 0; ii < length; ii++)
		{
			if((cnt = myPort.bufferCount()) > 0)
			{
				if(myPort.readPort(&tmp, 1) != 1)
				{
					return ERR_PORT_READ_ERROR;
				}
				
				#if DEBUG_PORT == 1
				cout << tmp << endl;
				#endif
		
				#if DEBUG_PORT == 1
				cout << "msg: " << ii << endl;
				#endif
					
				msg[ii] = tmp;
				
				if(ii == (length-1))
				{	
					msgFound = true;
				}
			}
			else
			{
				usleep(TIMEOUT_SLP); // Sleep 100 ms
				ii--;
				time_out++;
				
				#if DEBUG_PORT == 1
				cout << "time" << endl;
				#endif
		
				if(time_out >= TIMEOUT_CNT)
					return ERR_CMD_TIMEOUT;
			}
		}
		time_out = 0;
		headerFound = false;
	}
	
	if(msgFound)
	{
		#if DEBUG_PORT == 1
		cout << "MSG found" << endl;
		#endif
		for(int ii = 0; ii < TAILLEN; ii++)
		{
			if((cnt = myPort.bufferCount()) > 0)
			{
				if(myPort.readPort(&tmp, 1) != 1)
				{
					return ERR_PORT_READ_ERROR;
				}
				
				#if DEBUG_PORT == 1
				cout << tmp << endl;
				#endif
		
				if(tmp == ((unsigned char)data[HEADLEN+ii])) // Middle of header
				{
					#if DEBUG_PORT == 1
					cout << "tail: " << ii << endl;
					#endif
						
					if(ii == (TAILLEN-1))
					{
						#if DEBUG_PORT == 1
						cout << "tail found... message good!" << endl;
						#endif
					
						return 1;
					}
				}
				else
				{
					#if DEBUG_PORT == 1
					cout << "tail sucks" << endl;
					#endif
					break;
				}
			}
			else
			{
				usleep(TIMEOUT_SLP); // Sleep 100 ms
				ii--;
				time_out++;
				
				#if DEBUG_PORT == 1
				cout << "time" << endl;
				#endif
				
				if(time_out >= TIMEOUT_CNT)
					return ERR_CMD_TIMEOUT;
			}
		}
		time_out = 0;
		msgFound = false;
	}
	
	return 0;
}


int BusInterface::writeResponse(commandData* cmd,commandResp* rsp, unsigned int &ret)
{
	if(myPort.getOutputType() == ASCII)
	{
		string asciiSendBack = "";
		asciiSendBack = formASCIIResponse(cmd, rsp, ret);
		if(myPort.writePort(asciiSendBack) < 0)
			return -1;
	}
	else if(myPort.getOutputType() == HEX)
	{
		char hexSendBack[MAXLEN*2];
		int hexSendLength = 0; 
		formHexResponse(hexSendBack, hexSendLength, cmd, rsp, ret);
		if(myPort.writePort(hexSendBack,hexSendLength) < 0)
			return -1;
	}
	else
		return -1;
	
	myPort.flushWritePort();
	
	return 0;
}

string BusInterface::formASCIIResponse(commandData* cmd,commandResp* rsp, unsigned int &ret)
{
	stringstream temp;
	
	temp << hex << 0xFF 
		 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)cmd->proc & 0xFF)
		 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)cmd->cmd  & 0xFF)
		 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)cmd->arg1 & 0xFF)
		 << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)cmd->arg2 & 0xFF)
		 << setw( 8 ) << setfill( '0' ) << hex << ((unsigned int)ret       & 0xFFFFFFFF);
    if(rsp->length > 0)
    {
    	temp << setw( 2 ) << setfill( '0' ) << hex << ((unsigned short)rsp->length & 0xFFFF);
    	for(int i = 0; i < rsp->length; i++)
    	{
    		temp << setw( 2 ) << setfill( '0' ) << hex << ((unsigned int)rsp->msg[i] & 0xFF);
    	}
    }
	temp << 0xFF;
		
	return temp.str();
}

void BusInterface::formHexResponse(char* toSendBack, int &length, commandData* cmd, commandResp* rsp, unsigned int &ret)
{
	int ii = 0;
	
	// Header:	
	toSendBack[ii] = 0xFF;
	ii++;
	
	// Cmd:
	toSendBack[ii] = (cmd->proc & 0xFF);
	ii++;
	toSendBack[ii] = (cmd->cmd & 0xFF);
	ii++;
	toSendBack[ii] = (cmd->arg1 & 0xFF);
	ii++;
	toSendBack[ii] = (cmd->arg2 & 0xFF);
	ii++;
	
	// Return:
	for(int j = 0; j < 4; j++)
	{
		toSendBack[ii] = (unsigned char) ( ( ret >> 8*(3-j) ) & 0xFF);
		ii++;
	}

	// Response:
	if(rsp->length > 0)
    {
    	// Length:
    	for(int j = 0; j < 2; j++)
		{
			toSendBack[ii] = (unsigned char) ( ( rsp->length >> 8*(1-j) ) & 0xFF);
			ii++;
		}
	
		// Message:
    	for(int j = 0; j < rsp->length; j++)
    	{
    		toSendBack[ii] = (rsp->msg[j] & 0xFF);
    		ii++;
    	}
    }

	// Tailer:
	toSendBack[ii] = 0xFF;
	ii++;
	
	length = ii;
}
