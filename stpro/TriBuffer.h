
#if !defined(_TRIBUFFER_H)
#define _TRIBUFFER_H

#include <pthread.h>

using namespace std;

// Status of each entry in buffer:
#define WAIT 0
#define FULL 3

class TriBuffer
{
	public:
	TriBuffer();
	~TriBuffer();
	int join();
	int swap(int index);
	
	private:
	int node[3];
	int join_index;
	pthread_mutex_t lock;
};

#endif  //_TRIBUFFER_H
