#include "Logger.h"

const char *LogLevStr[6] = {"FATAL_ERROR","ERROR","WARNING","INFO","DEBUG","SPAM"};

Logger::Logger(const char* processname)
{
	strcpy(pname,processname);
	isopen = 0;
	buffer="";
	limit=100;
	maxlen=-1;
	position=0;
	startnew=false;
	pthread_mutex_init(&logMutex,NULL);
	pthread_mutex_unlock(&logMutex);
}

Logger::~Logger()
{
	pthread_mutex_destroy(&logMutex);
}


void Logger::open(const char* logfile)
{
	strcpy(filename,logfile);
	isopen = 1;
	//create the file if necessary
	fout.open(filename, ios_base::out | ios_base::app);
	fout.close();
	//get the position to start from, in case we are still growing the original file
	fout.open(filename, ios_base::in | ios_base::out | ios_base::ate);
	position = fout.tellp();
	fout.close();
	//clear out any log messages waiting in the buffer
	flush();
}

void Logger::lw(LOGLEVEL level, const std::string& message, ...)
{
	if (level>limit) return;
	pthread_mutex_lock(&logMutex);
	char lineseg[BUFF_LEN]={0};
	va_list args;
	va_start(args, message);
	//time_t rawtime;
	//time(&rawtime);
	//strcpy(timestr,ctime(&rawtime));
	//timestr[24]='\0';
	//time_t timestr;
	//timestr = time(NULL);
	if (level != NON)
		snprintf(lineseg,BUFF_LEN,"%ld - %s (%s): ",time(NULL),pname,LogLevStr[level]);
	buffer.append(lineseg);
	vsnprintf(lineseg,BUFF_LEN,message.c_str(),args);
	buffer.append(lineseg);
	buffer.append("\n");
	va_end(args);
	flush();
	pthread_mutex_unlock(&logMutex);
}

//Logger:lw is a thread safe function and the ONLY thread safe function in Logger!
void Logger::lw(LOGLEVEL level, const char* message, ...)
{
	if (level>limit) return;
	pthread_mutex_lock(&logMutex);
	char lineseg[BUFF_LEN]={0};
	va_list args;
	va_start(args, message);
	//time_t rawtime;
	//time(&rawtime);
	//strcpy(timestr,ctime(&rawtime));
	//timestr[24]='\0';
	//time_t timestr;
	//timestr = time(NULL);
	if (level != NON)
		snprintf(lineseg,BUFF_LEN,"%ld - %s (%s): ",time(NULL),pname,LogLevStr[level]);
	buffer.append(lineseg);
	vsnprintf(lineseg,BUFF_LEN,message,args);
	buffer.append(lineseg);
	buffer.append("\n");
	va_end(args);
	flush();
	pthread_mutex_unlock(&logMutex);
}

void Logger::flush()
{
	int ret;
	//long end=0, beg=0, cur=0;
	if (isopen == 1 && buffer.length() > 0)
	{
		fout.open(filename, ios_base::in | ios_base::out | ios_base::ate);
		if (!fout.good())printf("Error writing log file \"%s\"!\n",filename);
		if (maxlen > 0)
			fout.seekp(position,ios_base::beg);
		position += buffer.length();
		fout.write(buffer.c_str(),buffer.length());
		fout.flush();
		fout.close();
		buffer.erase();

		if (maxlen > 0) //if we are keeping track of how large our log files get...
		{
			if (position > maxlen) //and our log file is larger than that size...
			{
				position = 0; //then set our starting position tracking
				//variable to zero.
				if (startnew) //If we want also want multiple files
				{
					//to be generated...
					fout.close(); //then close the file
					char movefile[BUFF_LEN]; //generate a filename
					//of where to move the full file:
					snprintf(movefile,BUFF_LEN,"%s_%lu",filename,time(NULL));
					//execute the move:
					char movecmd[1024];
					snprintf(movecmd,1024,"mv %s %s",filename,movefile);
					(void)(ret = system(movecmd));
					//create the file if necessary
					fout.open(filename, ios_base::out | ios_base::app);
					fout.close();
				}
			}
		}//if maxlen > 0
	}//if isopen
}

void Logger::setlim(int lim)
{
	limit = lim;
}

void Logger::setmaxlen(int bytes, bool multiplefiles)
{
	maxlen = bytes;
	startnew = multiplefiles;
	if (position > maxlen) position = 0;
}

void Logger::close() 
{
	flush();	
	
	if(fout.is_open())
	{
		fout.flush(); 
		fout.close(); 
	}
}

