#ifndef _MSG_Q_WRAPPER_H_
#define _MSG_Q_WRAPPER_H_

#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <iostream>
#include "errno.h"
// #include "BMsg.h"
// #include "MMsg.h"
// #include "CRMsg.h"
#include "CommandData.h"

using namespace std;

/*****************************************************
 * Section: Constants
 *
 * Queue keys should go here.  The key is what
 * creates the queue, or gets the qid, for a
 * message queue.  I have tried to give each process
 * its own queue, so that they don't conflict with
 * each other.  Additional processes should define
 * a new key here.
 *****************************************************/
//#define SSM_KEY    0x1001   // Interrupts go here
//#define DCOL_KEY   0x1002
//#define HKPR_KEY   0x1003
//#define STCL_KEY   0x1004
//#define STIMG_KEY  0x1005
//#define STPRO_KEY  0x1006

/*****************************************************************
 * Class: MsgQueueWrapper
 * Purpose: This class contains functions to create and delete
 *          message queues, as well as send and receive messages.
 * TODO: Consolidate this so that there is only one
 *       implementation of msgQueueSend() and msgQueueReceive().
 * Member msgQueueCreate(): Creates a message queue
 * Member msgQueueDelete(): Deletes a message queue
 * Member msgQueueSend() (3): Sends a message over a message queue.
 * Member msgQueueReceive() (3): Receives a message from a message queue.
 *****************************************************************/
class MsgQueueWrapper
{
public:
	// Message queue utilities
	int msgQueueGet(key_t key);
	int msgQueueCreate(key_t key);
	int msgQueueDelete(int qid);
	
	// Message send & receive:
	int msgQueueSend(int qid, message *msg);
	int msgQueueReceive(int qid, long type, message *msg);
	int msgQueueSend_nowait(int qid, message *msg);
	int msgQueueReceive_nowait(int qid, long type, message *msg);
	
	// Debug:
	string printError();
};
#endif
