#include "GlobalLock.h"

pthread_mutex_t* globallock_open(const char* lock_path)
{
	// Defines:
	int fd;
	pthread_mutexattr_t theMutexAttr;
	pthread_mutex_t* theMutex = NULL;
	
	// Create mutex in shared memory:
	if((fd = open(lock_path, O_RDWR | O_CREAT | O_EXCL, 0666)) > 0)
	{
		// Size the file:
		if(ftruncate(fd,sizeof(pthread_mutex_t)) < 0)
			return NULL;
			
		// Innitialize global mutex attribute variable:
		pthread_mutexattr_init(&theMutexAttr);
		pthread_mutexattr_setpshared(&theMutexAttr,PTHREAD_PROCESS_SHARED);
		
		// Point the file to our mutex:
		theMutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE, MAP_SHARED,
            fd, 0);
            
		// Initialize our mutex with our attributes:
		pthread_mutex_init(theMutex, &theMutexAttr);
	}
	// Open mutex in shared memory if already open:
	else
	{
		if((fd = open(lock_path, O_RDWR, 0666)) < 0)
			return NULL;
			
		theMutex = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t),
            PROT_READ | PROT_WRITE, MAP_SHARED,
            fd, 0);
	}
	
	// Return our mutex:
	return theMutex;           
}

