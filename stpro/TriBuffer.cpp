#include "TriBuffer.h"

TriBuffer::TriBuffer()
{
	pthread_mutex_init(&lock,NULL);
	join_index = 1;
	node[0] = 0;
	node[1] = 1;
	node[2] = 2;
}

TriBuffer::~TriBuffer()
{
	pthread_mutex_destroy(&lock);
}

// Returns buffer member id:
int TriBuffer::join()
{
	int retID;
	
	pthread_mutex_lock(&lock);
	
	if(join_index >= FULL)
	{
		retID = -1;
	}
	else
	{
		retID = join_index;
		join_index++;
	}
	
	pthread_mutex_unlock(&lock);
	
	return retID;
}

// Returns newly checkout out index:
int TriBuffer::swap(int buf_id)
{
	int temp;

	pthread_mutex_lock(&lock);
	
	// Internal swap:
	temp = node[WAIT];
	node[WAIT] = node[buf_id];
	node[buf_id] = temp;
	
	// Give process new index:
	temp = node[buf_id];
	
	pthread_mutex_unlock(&lock);
	
	return temp;
}
