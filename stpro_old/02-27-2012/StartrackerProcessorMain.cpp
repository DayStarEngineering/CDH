#include "StartrackerProcessor.h"

// Globals needed for signal catcher:
void signal_handler(int sig);
volatile bool stop = false;
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

	// Start process:
	stpro theSTPro(argv[1],&stop);
	theSTPro.run();
	return 0;
}

// Signal handler:
void signal_handler(int sig)
{
	// Set global kill handler:
	(void) sig;
	stop = true;
}

