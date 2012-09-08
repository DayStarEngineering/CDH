#ifndef COMMAND_H     // Prevent duplicate definition
#define COMMAND_H

// Includes:
#include "CommandData.h"
#include "SemaphoreWrapper.h"
#include "MsgQueueWrapper.h"
#include "GlobalLock.h"
#include "SubsystemInterface.h"
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include "../configmap/configmap.h"

using namespace std;

//unsigned int isCommand(commandData* theCmd);
//unsigned int sendResponse(commandData* theCmd, int length, int response);
//unsigned int updateStatus(commandData* theCmd, int length);

class CommandWrapper : public msg
{
	public:
	CommandWrapper(int proc);
	~CommandWrapper();
	message createMessage(char proc, char type, char arg1, short arg2);
	void execute(message* msg);

	private:
	MsgQueueWrapper msgQueueWrapper;
	int myqid;
	int ssmqid;
	long mytid;
};

#endif
