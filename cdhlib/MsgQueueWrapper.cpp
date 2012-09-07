/**********************************************************************
 * File: MsgQueueWrapper.cpp
 * Purpose: Provides IPC using message queues.
 * Author: Mathew Strauss
 **********************************************************************/

/***************************************************
 * Section: Includes
 **************************************************/
#include "MsgQueueWrapper.h"
/***************************************************
 * Function: msgQueueGet(key_t key, int p)
 * Param key: A key (from ftok) used to create a queue.
 * Param p: The priority level of the queue you are creating.
 * Purpose: Creates a queue based on key.
 * Returns: The qid on success, -1 on failure.
 **************************************************/
int MsgQueueWrapper::msgQueueGet(key_t key)
{
	int qid;
	if ((qid = msgget(key, 0666)) == -1)
		return -1;

	return qid;
}
/***************************************************
 * Function: msgQueueCreate(key_t key, int p)
 * Param key: A key (from ftok) used to create a queue.
 * Param p: The priority level of the queue you are creating.
 * Purpose: Creates a queue based on key.
 * Returns: The qid on success, -1 on failure.
 **************************************************/
int MsgQueueWrapper::msgQueueCreate(key_t key)
{
	int qid;
	if ((qid = msgget(key, IPC_CREAT | 0666)) == -1)
		return -1;
	
	//increase message queue size
	struct msqid_ds buf;
	if (msgctl(qid, IPC_STAT, &buf) == -1) 
		return -1;

	//set new buffer size
	buf.msg_qbytes = 262144;
	
	//set Queue values
	if (msgctl(qid, IPC_SET, &buf) == -1) 
		return -1;

	return qid;
}
/*********************************************************
 * Function: msgQueueDelete(int qid)
 * Param qid: The queue ID of the message queue to be deleted.
 * Purpose: Deletes a message queue to release system resources.
 * Returns: -1 on failure, 0 on success.
 *********************************************************/
int MsgQueueWrapper::msgQueueDelete(int qid)
{
	return msgctl(qid, IPC_RMID, NULL);
}
/****************************************************
 * Function: msgQueueSend(int qid, MMsg *msg)
 * Param qid: The queue ID of the message queue.
 * Param msg: A MMsg struct that has been initialized
 * 		  and will be sent over the message queue
 * Purpose: Sends a message over a queue denoted by qid
 * Returns: -1 on failure, 0 on success.
 ****************************************************/
int MsgQueueWrapper::msgQueueSend(int qid, message *msg)
{
	int ret;
	if ((ret = msgsnd(qid, msg, sizeof(message) - sizeof(long), 0)) == -1)
	{
		msg->err=errno;
		return -1;
	}
	return ret;
}
/*******************************************************
 * Function: msgQueueReceive(int qid, long type, MMsg *msg)
 * Param qid: The queue ID of the message queue.
 * Param type: The specific type of message you want to get.
 *                 Can be any integer.
 * Param msg: A MMsg struct that will store the return data.
 * Purpose: Receives a message from the message queue.
 * Returns: -1 on failure, 0 on success.
 *********************************************************/
int MsgQueueWrapper::msgQueueReceive(int qid, long type, message *msg)
{
	int ret, length;
	length = sizeof(message) - sizeof(long);
	if ((ret = msgrcv(qid, msg, length, type, 0)) == -1)
	{
		msg->err=errno;
		return -1;
	}
	return ret;
}
/****************************************************
 * Function: msgQueueSend(int qid, BMsg *msg)
 * Param qid: The queue ID of the message queue.
 * Param msg: A BMsg struct that has been initialized
 * 		  and will be sent over the message queue
 * Purpose: Sends a message over a queue denoted by qid
 * Returns: -1 on failure, 0 on success.
 ****************************************************/
int MsgQueueWrapper::msgQueueSend_nowait(int qid, message *msg)
{
	int ret;

/////////////////////////////////////////////////////////////////////////////////////////
//This is debugging code for the message queues, it prints out all the relevent status information about the queues.
/*
	struct msqid_ds buf;
	int temp;
	temp = msgctl(qid, IPC_STAT, &buf);
	if (temp == -1) {
		(void) fprintf(stderr, "msgctl fail");
	}
	else {
		cerr << "msg_perm.uid = "<< buf.msg_perm.uid<< endl;
	   cerr << "msg_perm.gid = "<< buf.msg_perm.gid<< endl;
	   cerr << "msg_perm.cuid = "<< buf.msg_perm.cuid<< endl;
	   cerr << "msg_perm.cgid = "<< buf.msg_perm.cgid<< endl;
	   cerr << "msg_perm.mode = "<< buf.msg_perm.mode;
	   cerr << " access permissions = "<< (buf.msg_perm.mode & 0777)<< endl;
	   cerr << "msg_cbytes = "<< buf.msg_cbytes<< endl;
	   cerr << "msg_qbytes = "<< buf.msg_qbytes<< endl;
	   cerr << "msg_qnum = "<< buf.msg_qnum<< endl;
	   cerr << "msg_lspid = "<< buf.msg_lspid<< endl;
	   cerr << "msg_lrpid = "<< buf.msg_lrpid << endl;
	}
*/
/////////////////////////////////////////////////////////////////////////////////////////


	if ((ret = msgsnd(qid, msg, sizeof(message) - sizeof(long), IPC_NOWAIT)) == -1)
	{
		msg->err=errno;
		return -1;
	}
	return ret;
}
/*******************************************************
 * Function: msgQueueReceive(int qid, long type, MMsg *msg)
 * Param qid: The queue ID of the message queue.
 * Param type: The specific type of message you want to get.
 *                 Can be any integer.
 * Param msg: A MMsg struct that will store the return data.
 * Purpose: Receives a message from the message queue.
 * Returns: -1 on failure, 0 on success.
 *********************************************************/
int MsgQueueWrapper::msgQueueReceive_nowait(int qid, long type, message *msg)
{
	int ret, length;
	length = sizeof(message) - sizeof(long);
	if ((ret = msgrcv(qid, msg, length, type, IPC_NOWAIT)) == -1)
	{
		msg->err=errno;
		return -1;
	}
	return ret;
}
string MsgQueueWrapper::printError()
{
	switch (errno)
	{
	case EACCES:
		return string("EACCES");
		break;
	case EAGAIN:
		return string("EAGAIN");
		break;
	case EFAULT:
		return string("EFAULT");
		break;
	case EIDRM:
		return string("EIDRM");
		break;
	case EINTR:
		return string("EINTR");
		break;
	case EINVAL:
		return string("EINVAL");
		break;
	case ENOMEM:
		return string("ENOMEM");
		break;
	case E2BIG:
		return string("E2BIG");
		break;
	case ENOMSG:
		return string("ENOMSG");
		break;
	case EEXIST:
		return string("EEXIST");
		break;
	case ENOENT:
		return string("ENOENT");
		break;
	case ENOSPC:
		return string("ENOSPC");
		break;
	default:
		return string("Unknown error code");
	}
}
