#include "GlobalLock.h"

using namespace std;

int main()
{
	pthread_mutex_t * tmp;
	tmp = globallock_open("/tmp/LOCKTEST");
	pthread_mutex_unlock(tmp);
}
