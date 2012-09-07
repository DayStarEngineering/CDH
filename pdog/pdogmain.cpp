#include "ProcessWatchdog.h"
#include<iostream>
#include<signal.h>

using namespace std;

int human=0;
const char *msgs[1][2]=
{
	{"0000","Usage: pdog [-h] config_file"}
};
void msgn(int n) { cout << msgs[n][human] << endl; }
void msgpass(int n) { msgn(n); exit(0); }
void msgfail(int n,int error=1) { msgn(n); exit(error); }

//Globals needed for signal catchers
Logger* theLogger;
volatile bool stop = false;

void signal_handler(int sig);

int main(int argc, char** argv)
{
	theLogger=NULL;

	int nargs=2;
	if ((argv[1]!=NULL)&&(strcmp(argv[1],"-h")==0)) { human=1; nargs=3; }
	if (argc<nargs) msgfail(1);

	//setup signal handlers
	signal(SIGTERM,signal_handler);
	signal(SIGINT,signal_handler);
	signal(SIGQUIT,signal_handler);
	signal(SIGHUP,signal_handler);

	ProcessWatchdog thePD(argv[1+human],&stop);
	theLogger=&thePD.myLogger;
	thePD.run();
	return 0;
}

void signal_handler(int sig)
{
	// Set global kill handler:
	(void) sig;
	stop = true;
}

