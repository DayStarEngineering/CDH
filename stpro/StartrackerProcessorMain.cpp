#include "StartrackerProcessor.h"

// Globals needed for signal catcher:
void alarm_handler(int sig);
void signal_handler(int sig);
volatile bool stop = false;
volatile pthread_mutex_t mutex_signal;
volatile timeval global_timer;
Logger* theLogger = NULL;

int main(int argc, char** argv)
{
	// Check inputs:
	int nargs=2;
	if (argc<nargs){
		cout << "Not enough arguments! Did you include a configuration file?"; exit(-1);
	}

	// Setup signal handlers:
	signal(SIGTERM,signal_handler);
	signal(SIGINT,signal_handler);
	signal(SIGQUIT,signal_handler);
	signal(SIGHUP,signal_handler);
	
	// Setup alarm handler:
	signal(SIGALRM, alarm_handler);
	
	// Start process:
	stpro theSTPro(argv[1], &mutex_signal, &global_timer, &stop);
	theSTPro.run();
	return 0;
}

// Alarm handler: (for initiating grab image)
void alarm_handler(int sig)
{
	// Set global kill handler:
	(void) sig;
	
	#if DEBUG_MODE == 2
	cout << "Alarm!" << endl;
	#endif
	
	//^^^^^^^ SIGNAL IN DATA ^^^^^^^^^^^^
	pthread_mutex_trylock((pthread_mutex_t*)&mutex_signal); // Make sure mutex is locked before we unlock it!
	pthread_mutex_unlock((pthread_mutex_t*)&mutex_signal);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	
	// Set up timer:
	struct itimerval tval;
  	tval.it_interval.tv_sec = 0;
  	tval.it_interval.tv_usec = 0;
  	tval.it_value.tv_sec = global_timer.tv_sec; 
  	tval.it_value.tv_usec = global_timer.tv_usec;
  
  	///////// RESET TIMER ///////////////
	setitimer(ITIMER_REAL, &tval, NULL);
	/////////////////////////////////////
}

// Signal handler:
void signal_handler(int sig)
{
	// Set global kill handler:
	(void) sig;
	stop = true;
}
