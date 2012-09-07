#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include "../cdhlib/Command.h"
#include "../imglib/MILWrapper.h"
#include "../imglib/MILObjects.h"
#include "../imglib/grey2bin.h"
#include "../stlib/Centroid.h"
#include "../stlib/StartrackerData.h"

// Defines:
#define DEFAULT_IMAGE_PATH "/data/images/img"
#define CONFIG_FILE_PATH "/home/conf/fgcl.xml"
#define DEFAULT_SLEEP 10000
enum{ GRAB, GRABQ, GRAB2, GRABQ2, GRABC, GRABC2, DISP, /*DISPC,*/ CENTROID, CONV, CONVTXT };

using namespace std;

void help();
void run(int command, string infname, string outfname);
int displayImage(string fname);
int convertImage(string infname, string outfname);
int convertImageTEXT(string infname, string outfname);
// int displayContinuous(string fname);
int grabImage(string fname);
int grabImageQ(string fname);
int grabImage2(string fname);
int grabImageQ2(string fname);
int grabContinuous();
int grabContinuous2();
int grabContinuous_noconvert();
int centroidImage(string infname, string outfname);
int _kbhit();

int input = 0;
int output = 0;
int quiet = 0;
	
/*
 * Executes the FGCL program.  Parses the command line arguments, and executes.
 */
int main(int argc, char** argv)
{	
	string infname = "";
	string outfname = "";
	char temp[100];
	char tempflg[1];
	int command;
	int numFlags = 0;
	
	// Get time:
	timeval ts;
	gettimeofday(&ts, NULL);
	
	// Check Arguments:
	if (argc < (2) ) help();
	
	// Check for flags:
	for( int i = 2; i < argc; i++ )
	{
		tempflg[0] = argv[i][0];
		if(!strcmp(tempflg,"-"))
		{
			if (strcmp(argv[i],"-i")==0)
			{
				input = i+1;
				i++;
				numFlags++;
			}
			else if (strcmp(argv[i],"-o")==0)
			{
				output = i+1;
				i++;
				numFlags++;
			}
			else if (strcmp(argv[i],"-q")==0)
			{
				quiet = 1;
				numFlags++;
			}
			else
			{
				cerr << "Invalid flag '" << argv[i] << "' not recognized!" << endl;
				cerr << "Type 'fgcl' for help!" << endl;
				exit(-1);
			}
		}
		else
		{
			cerr << "Argument '" << argv[i] << "' not recognized!" << endl;
			cerr << "Type 'fgcl' for help!" << endl;
			exit(-1);
		}
	}
	
	// Set output file:
	if(input > 0)
	{
		infname = argv[input];
	}

	if(output > 0)
	{
		outfname = argv[output];
	}
	else
	{
		sprintf(temp,"%s_%ld_%ld.dat",DEFAULT_IMAGE_PATH,ts.tv_sec,ts.tv_usec);
		outfname += temp;
	}
	
	// Parse Process:
	if (strcmp(argv[1],"grab")==0)
	{
		command = GRAB;
	}
	else if (strcmp(argv[1],"grabq")==0)
	{
		command = GRABQ;
	}
	else if (strcmp(argv[1],"grab2")==0)
	{
		command = GRAB2;
	}
	else if (strcmp(argv[1],"grabq2")==0)
	{
		command = GRABQ2;
	}
	else if (strcmp(argv[1],"grabc")==0)
	{
		command = GRABC;
	}
	else if (strcmp(argv[1],"grabc2")==0)
	{
		command = GRABC2;
	}
	else if (strcmp(argv[1],"disp")==0)
	{
		command = DISP;
	}
	/*else if (strcmp(argv[1],"dispc")==0)
	{
		command = DISPC;
	}*/
	else if (strcmp(argv[1],"centroid")==0)
	{
		command = CENTROID;
	}
	else if (strcmp(argv[1],"conv")==0)
	{
		command = CONV;
	}
	else if (strcmp(argv[1],"convtxt")==0)
	{
		command = CONVTXT;
	}
	else
	{
		cerr << "Invalid argument (" << argv[1] << "), must be a valid command." << endl;
		cerr << "Type 'fgcl' for help!" << endl;
		exit(-1);
	}
	
	// Execute function:
	run(command, infname, outfname);
	
	return 0;
}

// Prints out a detailed help statement for when the user doesn't know how to use the program.
void help()
{
	cout << endl
	<< "Usage: fgcl COMMAND [flag] [OPTION...]"<<endl
	<< "  fgcl: Frame Grabber Commandline Client"<<endl
	<< "  note - all fgcl configuration options can be found in /home/conf/fgcl.xml"<<endl
	<< endl
	<< "  COMMAND   A lowercase string indicating the command type"<<endl
	<< endl
	<< endl
	<< "COMMAND Names:"<<endl
	<< "  grab     (grab image)"<<endl
	<< "  grabq    (grab image without display, works with \"headless\" computer" << endl
	<< "  grab2    (grab image with 2 seperate DCFs and digitizer numbers (for top and bottom halves) into a single image"<<endl
	<< "  grabq2   (grab 2 images from each channel)" << endl
	<< "  grabc    (grab image continuously)"<<endl
	<< "  grabc2   (grab image with 2 seperate DFCs and digitizer numbers into single image continuously)"<<endl
	<< "  disp     (display image, FNAME required!)"<<endl
	<< "  centroid (centroid stars found in the image, FNAME required!)"<<endl
	<< "  conv     (convert image from startracker format (11-bit .dat) to PC-viewable format (16-bit .tif)"<<endl
	<< "  convtxt  (convert DayStar Python image (.txt) to startracker image (11-bit .dat)"<<endl
	<< endl
	<< "flags: " << endl
	<< "  -o       (specify output file, ex: 'fgcl grab -o img.dat')" << endl
	<< "  -i       (specify input file, ex: 'fgcl conv -i img.dat')" << endl
	<< "  -q       (quiet mode, do not display unnecessary output or images)" << endl
	<< endl
	<< "Example Calls: "<<endl
	<< " ---------------------------------------------------------------"<<endl
	<< " _fgcl_|__COMMAND___|__[flag]__|______[OPTION]_________|"<<endl
	<< "  fgcl |   grab     |  -q -o   | /data/images/img.dat  |"<<endl
	<< "  fgcl |   grabc    |  [none]  |      [none]           |"<<endl
	<< "  fgcl |   disp     |   -i     | /data/images/img.dat  |"<<endl
	<< "  fgcl |   centroid |   -i     | /data/images/img.dat  |"<<endl
	<< "  fgcl |   conv     |   -i     | /data/images/img.dat  |"<<endl
	<< " ---------------------------------------------------------------"<<endl
	<< endl;
	
	exit(1);
}

void run(int command, string infname, string outfname)
{
	switch( command )
	{
		case GRAB:
			grabImage(outfname);
			break;
		case GRABQ:
			grabImageQ(outfname);
			break;
		case GRAB2:
			grabImage2(outfname);
			break;
		case GRABQ2:
			grabImageQ2(outfname);
			break;
		case GRABC:
			grabContinuous();
			break;
		case GRABC2:
			grabContinuous2();
			break;
		case DISP:
			displayImage(infname);
			break;
		/*case DISPC:
			displayContinuous();
			break;*/
		case CENTROID:
			centroidImage(infname, outfname);
			break;
		case CONV:
			convertImage(infname, outfname);
			break;
		case CONVTXT:
			convertImageTEXT(infname, outfname);
			break;
		default:
			cerr << "FATAL ERROR. Contact CDH!" << endl;
			break;
	}
}

int displayImage(string fname)
{
	if(quiet)
	{	
		cerr << "-q option is not valid with command: 'DISP'" << endl;
		return -1;
	}
	
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	MILDisplay disp;
	unsigned int xlen = 0; unsigned int ylen = 0;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	xlen = atoi(myConfig["xpix_size"].c_str());
	ylen = atoi(myConfig["ypix_size"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	////////////////////////////////////////
	
	if( input == 0 )
	{
		cerr << "Input filename must be specified to display image!" << endl;
		return -1;
	}
	
	if( loadImg(img.ID, fname) == -1 )
	{
		cerr << "Error loading " << fname << " into image " << img.ID << endl;
		return -1;
	}
	
	if( scaleDisp(disp.ID, bitres) == -1 )
	{
		cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
		return -1;
	}
	
	if( dispImg(disp.ID, img.ID) == -1 )
	{
		cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
		return -1;
	}
	
	cout << "Press any key to exit." << endl;
	while(!_kbhit()){ usleep(500000); }

	return 0;
}

int convertImage(string infname, string outfname)
{
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	unsigned int xlen, ylen;

	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	xlen = atoi(myConfig["xpix_size"].c_str());
	ylen = atoi(myConfig["ypix_size"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	////////////////////////////////////////
	
	if( input == 0 )
	{
		cerr << "Input filename must be specified to display image!" << endl;
		return -1;
	}
	
	if( loadImg(img.ID, infname) == -1 )
	{
		cerr << "Error loading " << infname << " into image " << img.ID << endl;
		return -1;
	}
	
	// Convert image to 16-bit for easy viewing on PCs
	if( convert11to16bitres(img.ID) == -1 )
	{
		cerr << "Error converting image from 11-bit to 16-bit resolution." << endl;
		return -1;
	}

	// Make new filename:
	if( output == 0 )
	{
		outfname = "";
		int cnt = 0;
		while( infname[cnt] != '.' )
		{
			outfname += infname[cnt];
			cnt++;
		}
		outfname += "_conv.tif";
	}

	// Save converted file:	
	if( saveImgTIFF(img.ID, outfname) == -1)
	{
		cerr << "Error saving: " << outfname << endl;
	}
	else
	{
		cout << "Converted file saved to " << outfname << endl;
	}
	
	return 0;
}

int convertImageTEXT(string infname, string outfname)
{
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	image DSimg;
	unsigned short xlen, ylen;

	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	xlen = atoi(myConfig["xpix_size"].c_str());
	ylen = atoi(myConfig["ypix_size"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
		
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	if( input == 0 )
	{
		cerr << "Input filename must be specified to display image!" << endl;
		return -1;
	}
	
	// Load image:
	if( loadImgTEXT( &DSimg, infname) == -1 )
	{
		cerr << "Error loading " << infname << " into image " << img.ID << endl;
		return -1;
	}
	
	// Copy image:
	if( copyImg( &DSimg, img.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}

	// Make new filename:
	if( output == 0 )
	{
		outfname = "";
		int cnt = 0;
		while( infname[cnt] != '.' )
		{
			outfname += infname[cnt];
			cnt++;
		}
		outfname += ".dat";
	}

	// Save converted file:	
	if( saveImg(img.ID, outfname) == -1)
	{
		cerr << "Error saving: " << outfname << endl;
	}
	else
	{
		cout << "Converted file saved to " << outfname << endl;
	}
	
	return 0;
}

int grabImage(string fname)
{
	string tempfname = "";
		
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	MILDisplay disp;
	MILDigitizer dig;
	image DSimg;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path = myConfig["grab_DCF"];
	int digNum = atoi(myConfig["grab_dig_num"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path.c_str(),digNum) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID, xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Grab image:
	if( digGrab(dig.ID, img.ID) == -1 )
	{
		cerr << "Error grabbing image with digitizer " << dig.ID << " to buffer " << img.ID << endl;
		return -1;
	}
	
	// Copy image:
	if( copyImg( img.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Convert image:
    grey2bin( &DSimg );
	
	// Copy back:
	if( copyImg( &DSimg, img.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}
	
	// Display image:
	if(!quiet)
	{
		if( scaleDisp(disp.ID, bitres) == -1 )
		{
			cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
			return -1;
		}
	
		if( dispImg(disp.ID, img.ID) == -1 )
		{
			cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
			return -1;
		}
	}
	
	// Get user path for saving image or exit:
	if(!quiet)
	{
		for(;;)
		{
			if( output == 0 )
			{
				cout << "Save File Options:" << endl
					 << "To use default file path input 'y' and [ENTER]."<< endl
					 << "To use custom file path input '/path/to/custom/file.dat' and [ENTER]." << endl
					 << "To exit without saving hit [ENTER]." << endl;
				cout << ">> ";
			
				// Get user input:
				getline(cin,tempfname);
		
				// Determine filename or exit:
				if( !tempfname.compare("") || !tempfname.compare("n") )
				{
					break;
				}
				else if( !tempfname.compare("y") )
				{
					output++;
				}
				else
				{
					fname = tempfname;
					output++;
				}
			}
			else
			{
				// Save image:
				if( saveImg(img.ID, fname) == -1 )
				{
					cerr << "Error saving image to " << fname << endl;
					fname.clear();
				}
				else
				{
					cout << "Imaged saved to " << fname << endl;
					break;
				}
			}
		}
	
		cout << "Press any key to exit." << endl;
		while(!_kbhit())
		{
			// Take a little nap:
			usleep(DEFAULT_SLEEP);
		}
	}
	else
	{
			// Save image:
			if( saveImg(img.ID, fname) == -1 )
			{
				cerr << "Error saving image to " << fname << endl;
				return -1;
			}
			else
			{
				cout << "Imaged saved to " << fname << endl;
			}
	}
	
	return 0;
}

int grabImageQ(string fname)
{
	string tempfname = "";
		
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	MILDigitizer dig;
	image DSimg;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path = myConfig["grab_DCF"];
	int digNum = atoi(myConfig["grab_dig_num"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path.c_str(),digNum) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID, xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Grab image:
	if( digGrab(dig.ID, img.ID) == -1 )
	{
		cerr << "Error grabbing image with digitizer " << dig.ID << " to buffer " << img.ID << endl;
		return -1;
	}
	
	// Copy image:
	if( copyImg( img.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Convert image:
    grey2bin( &DSimg );
	
	// Copy back:
	if( copyImg( &DSimg, img.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}
	
	// Save image:
	if( saveImg(img.ID, fname) == -1 )
	{
		cerr << "Error saving image to " << fname << endl;
		return -1;
	}
	else
	{
		cout << "Imaged saved to " << fname << endl;
	}
	
	return 0;
}

int grabImage2(string fname)
{
	string tempfname = "";
		
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage2 img;
	//MILDisplay disp;
	MILDigitizer2 dig;
	image DSimg;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path_1 = myConfig["grab2_DCF1"];
	string dcf_path_2 = myConfig["grab2_DCF2"];
	int digNum1 = atoi(myConfig["grab2_dig_num1"].c_str());
	int digNum2 = atoi(myConfig["grab2_dig_num2"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path_1.c_str(), dcf_path_2.c_str(), digNum1, digNum2) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path_1 << " and " << dcf_path_2 << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID[0], xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	// Multiply by two because we want a full image, not half:	
	ylen = ylen * 2;
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	/*
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	*/
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Grab image:
	if( digGrab2(dig.ID[0], dig.ID[1], img.childID[0], img.childID[1]) == -1 )
	{
		cerr << "Error grabbing image (2) with digitizer " << dig.ID[0] << " and " << dig.ID[1] << " to children buffers " << img.childID[0] << " and " << img.childID[1] << endl;
		return -1;
	}
	
	// Copy image:
	if( copyImg( img.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Convert image:
    grey2bin( &DSimg );
	
	// Copy back:
	if( copyImg( &DSimg, img.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}
	
	// Display image:
	/*
	if(!quiet)
	{
		if( scaleDisp(disp.ID, bitres) == -1 )
		{
			cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
			return -1;
		}
	
		if( dispImg(disp.ID, img.ID) == -1 )
		{
			cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
			return -1;
		}
	}
	
	// Get user path for saving image or exit:
	if(!quiet)
	{
		for(;;)
		{
			if( output == 0 )
			{
				cout << "Save File Options:" << endl
					 << "To use default file path input 'y' and [ENTER]."<< endl
					 << "To use custom file path input '/path/to/custom/file.dat' and [ENTER]." << endl
					 << "To exit without saving hit [ENTER]." << endl;
				cout << ">> ";
			
				// Get user input:
				getline(cin,tempfname);
		
				// Determine filename or exit:
				if( !tempfname.compare("") || !tempfname.compare("n") )
				{
					break;
				}
				else if( !tempfname.compare("y") )
				{
					output++;
				}
				else
				{
					fname = tempfname;
					output++;
				}
			}
			else
			{
				// Save image:
				if( saveImg(img.ID, fname) == -1 )
				{
					cerr << "Error saving image to " << fname << endl;
					fname.clear();
				}
				else
				{
					cout << "Imaged saved to " << fname << endl;
					break;
				}
			}
		}
	
		cout << "Press any key to exit." << endl;
		while(!_kbhit())
		{
			// Take a little nap:
			usleep(DEFAULT_SLEEP);
		}
	}
	else
	{*/
			// Save image:
			if( saveImg(img.ID, fname) == -1 )
			{
				cerr << "Error saving image to " << fname << endl;
				return -1;
			}
			else
			{
				cout << "Imaged saved to " << fname << endl;
			}
//	}
	
	return 0;
}

int grabImageQ2(string fname)
{
	string tempfname = "";
		
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img1, img2;
	MILDigitizer2 dig;
	image DSimg, DSimg2;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path_1 = myConfig["grab2_DCF1"];
	string dcf_path_2 = myConfig["grab2_DCF2"];
	int digNum1 = atoi(myConfig["grab2_dig_num1"].c_str());
	int digNum2 = atoi(myConfig["grab2_dig_num2"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	
	//////// TIMING //////////////////////
	//timeval starttime;
	//timeval midtime;
	//timeval endtime;
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	/*if( dig.create(MilWrapper.SysID,  dcf_path_1.c_str(),0) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path_1 << endl;
		return -1;
	}*/
	int ret;
	if( ( ret = dig.create(MilWrapper.SysID,  dcf_path_1.c_str(),dcf_path_2.c_str(),0,1) ) <= -1 )
	{
		cerr << "Error creating MILDigitizer with DCF: " << ret << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID[0], xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	else
	{
	//	cout << "image size: " << xlen << " " << ylen << endl;
	}
	
	if( img1.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage1." << endl;
		return -1;
	}
	
	if( img2.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage2." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Grab image 1:
	/*
	if(digSetSyncChannel(dig.ID, 0) == -1)
	{
		cerr << "Error syncing to channel zero" << endl;
		return -1;
	}
	
	if(digSetDataChannel(dig.ID, 0) == -1)
	{
		cerr << "Error choosing channel zero " << endl;
		return -1;
	}*/
	
	//gettimeofday(&starttime,NULL);
	
	if( digGrab(dig.ID[0], img1.ID) == -1 )
	{
		cerr << "Error grabbing image with digitizer " << dig.ID << " to buffer " << img1.ID << endl;
		return -1;
	}
	//gettimeofday(&midtime,NULL);
	// Switch Channel:
	/*
	if(digSetDataChannel(dig.ID, 1) == -1)
	{
		cerr << "Error choosing channel one" << endl;
		return -1;
	}*/
	
	// Grab image 2:
	if( digGrab(dig.ID[1], img2.ID) == -1 )
	{
		cerr << "Error grabbing image with digitizer " << dig.ID << " to buffer " << img2.ID << endl;
		return -1;
	}
	//gettimeofday(&endtime,NULL);
	
	/*
	cout << "first image" << endl;
	cout << ((double)(midtime.tv_sec) + (((double)midtime.tv_usec)/1000000.0)) -
			((double)(starttime.tv_sec) + (((double)starttime.tv_usec)/1000000.0));
	cout << endl << "second image" << endl;
	cout << ((double)(endtime.tv_sec) + (((double)endtime.tv_usec)/1000000.0)) -
			((double)(midtime.tv_sec) + (((double)midtime.tv_usec)/1000000.0));
			cout << endl << "total" << endl;
	// outTime:
	cout << ((double)(endtime.tv_sec) + (((double)endtime.tv_usec)/1000000.0)) -
			((double)(starttime.tv_sec) + (((double)starttime.tv_usec)/1000000.0));
	*/
	// Copy image:
	/*
	if( copyImg( img1.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Convert image:
    grey2bin( &DSimg );
	
	// Copy back:
	if( copyImg( &DSimg, img1.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}
	*/
	
	// Create fname image:
	int cnt = 0;
	while( fname[cnt] != '.' )
	{
		tempfname += fname[cnt];
		cnt++;
	}
	fname = tempfname;

	// Save image:
	if( saveImg(img1.ID, fname + "_LG.dat") == -1 )
	{
		cerr << "Error saving image to " << fname + "_LG.dat" << endl;
		return -1;
	}
	else
	{
		cout << "Imaged saved to " << fname  + "_LG.dat"<< endl;
	}
	
	/////////////////////////////////////////////////
	// Copy image:
	/*
	if( copyImg( img2.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Convert image:
    grey2bin( &DSimg );
	
	// Copy back:
	if( copyImg( &DSimg, img2.ID ) == -1 )
	{
		cerr << "Failed to copy daystar image to MILImage." << endl;
		return -1;
	}
	*/
	
	// Save image:
	if( saveImg(img2.ID, fname + "_HG.dat") == -1 )
	{
		cerr << "Error saving image to " << fname + "_HG.dat" << endl;
		return -1;
	}
	else
	{
		cout << "Imaged saved to " << fname + "_HG.dat" << endl;
	}
	
	return 0;
}


int grabContinuous()
{
	if(quiet)
	{	
		cerr << "-q option is not valid with command: 'GRABC'" << endl;
		return -1;
	}
	
	if(output)
	{	
		cerr << "-o option is not valid with command: 'GRABC'" << endl;
		return -1;
	}
	
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	MILImage dimg[2];
	MILDisplay disp;
	MILDigitizer dig;
	image DSimg;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path = myConfig["grab_DCF"];
	int digNum = atoi(myConfig["grab_dig_num"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	int ussleep = atoi(myConfig["grabc_sleep_us"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path.c_str(),digNum) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID, xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( dimg[0].create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( dimg[1].create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Display image:
	if( scaleDisp(disp.ID, bitres) == -1 )
	{
		cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
		return -1;
	}
	
	cout << "Press any key to terminate capture sequence." << endl;
	int frame = 1;
	while(!_kbhit())
	{
		// Grab image:
		if( digGrab(dig.ID, img.ID) == -1)
		{
			cerr << "Error grabbing image with digitizer " << dig.ID << " to buffer " << img.ID << endl;
			return -1;
		}
    	
    	// Copy Image:
    	if( copyImg( img.ID, &DSimg ) == -1 )
		{
			cerr << "Failed to copy MILImage to daystar image." << endl;
			return -1;
		}
	
		// Convert image:
		grey2bin( &DSimg );
	
		// Copy back:
		if( copyImg( &DSimg, dimg[frame].ID ) == -1 )
		{
			cerr << "Failed to copy daystar image to MILImage." << endl;
			return -1;
		}
		
		// Display image:
		if( dispImg(disp.ID, dimg[frame].ID) == -1 )
		{
			cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
			return -1;
		}
		
		frame = frame^1;
		
		// Take a little nap:
		usleep(ussleep);
	}
	
	return 0;
}

int grabContinuous2()
{
	if(quiet)
	{	
		cerr << "-q option is not valid with command: 'GRABC'" << endl;
		return -1;
	}
	
	if(output)
	{	
		cerr << "-o option is not valid with command: 'GRABC'" << endl;
		return -1;
	}
	
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage2 img;
	MILImage dimg[2];
	MILDisplay disp;
	MILDigitizer2 dig;
	image DSimg;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path_1 = myConfig["grab2_DCF1"];
	string dcf_path_2 = myConfig["grab2_DCF2"];
	int digNum1 = atoi(myConfig["grab2_dig_num1"].c_str());
	int digNum2 = atoi(myConfig["grab2_dig_num2"].c_str());
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	int ussleep = atoi(myConfig["grabc_sleep_us"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path_1.c_str(), dcf_path_2.c_str(), digNum1, digNum2) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path_1 << " and " << dcf_path_2 << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID[0], xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	// Multiply by two because we want a full image, not half:	
	ylen = ylen * 2;
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( dimg[0].create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( dimg[1].create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	
	if( DSimg.create(xlen, ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Display image:
	if( scaleDisp(disp.ID, bitres) == -1 )
	{
		cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
		return -1;
	}
	
	cout << "Press any key to terminate capture sequence." << endl;
	int frame = 1;
	while(!_kbhit())
	{
		// Grab image:
		if( digGrab2(dig.ID[0], dig.ID[1], img.childID[0], img.childID[1]) == -1 )
		{
			cerr << "Error grabbing image (2) with digitizer " << dig.ID[0] << " and " << dig.ID[1] << " to children buffers " << img.childID[0] << " and " << img.childID[1] << endl;
			return -1;
		}
    	
    	// Copy Image:
    	if( copyImg( img.ID, &DSimg ) == -1 )
		{
			cerr << "Failed to copy MILImage to daystar image." << endl;
			return -1;
		}
	
		// Convert image:
		grey2bin( &DSimg );
	
		// Copy back:
		if( copyImg( &DSimg, dimg[frame].ID ) == -1 )
		{
			cerr << "Failed to copy daystar image to MILImage." << endl;
			return -1;
		}
		
		// Display image:
		if( dispImg(disp.ID, dimg[frame].ID) == -1 )
		{
			cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
			return -1;
		}
		
		frame = frame^1;
		
		// Take a little nap:
		usleep(ussleep);
	}
	
	return 0;
}

int grabContinuous_noconvert()
{
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage img;
	MILDisplay disp;
	MILDigitizer dig;
	unsigned int xlen, ylen;
	
	configmap myConfig;
	myConfig.readfile(CONFIG_FILE_PATH);
	string dcf_path = myConfig["grab_DCF"];
	int bitres = atoi(myConfig["bit_resolution"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( dig.create(MilWrapper.SysID, dcf_path.c_str()) == -1 )
	{
		cerr << "Error creating MILDigitizer with DCF " << dcf_path << endl;
		return -1;
	}
	
	if( getImgSize(dig.ID, xlen, ylen) == -1 )
	{
		cerr << "Error grabbing image size from digitizer." << endl;
		return -1;
	}
	
	if( img.create(MilWrapper.SysID, xlen, ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Display image:
	if( scaleDisp(disp.ID, bitres) == -1 )
	{
		cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
		return -1;
	}
	
	if( dispImg(disp.ID, img.ID) == -1 )
	{
		cerr << "Error displaying image " << img.ID << " on display " << disp.ID << endl;
		return -1;
	}
	
	// Grab Continuously:
	if( digGrabContinuous(dig.ID, img.ID) == -1 )
	{
		cerr << "Error grabbing images continuously with digitizer " << dig.ID << " to image " << img.ID << endl;
	}
	
	cout << "Press any key to terminate capture sequence." << endl;
	while(!_kbhit())
	{
		// Take a little nap:
		usleep(DEFAULT_SLEEP);
	}
	
	if( digGrabHalt(dig.ID) == -1 )
	{
		cerr << "Could not halt continuous grab with digitizer " << dig.ID << endl;
	}
	
	return 0;
}

int centroidImage(string infname, string outfname)
{	
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MILImage MilImage;
	MILDisplay disp;
	image DSimg;
	string tempfname;
	
	Centroid myProcessor;
	centroidList centList;
	configmap myConfig;
	
	if( input == 0 )
	{
		cerr << "Input filename must be specified to display image!" << endl;
		return -1;
	}
	
	// Read config:
	myConfig.readfile(CONFIG_FILE_PATH);
	
	// Get processing info:
	centroidData cData;
	cData.bitres   			    = atoi(myConfig["bit_resolution"].c_str());
	cData.numsigma  		  	= atof(myConfig["num_sigma"].c_str());
	cData.minthresh 		    = atoi(myConfig["min_pix_per_star"].c_str());
	cData.maxthresh 		    = atoi(myConfig["max_pix_per_star"].c_str());
	cData.maxstars              = atoi(myConfig["max_star_count"].c_str());
	cData.maxstars2return       = atoi(myConfig["max_star_to_return"].c_str());
	cData.xlen                  = atoi(myConfig["xpix_size"].c_str());
	cData.ylen                  = atoi(myConfig["ypix_size"].c_str());
	cData.fovX                  = atof(myConfig["xfov"].c_str());
	cData.fovY                  = atof(myConfig["yfov"].c_str());
	cData.maxstars              = atoi(myConfig["max_star_count"].c_str());
	cData.numpixelsinsubsample  = atoi(myConfig["median_subsample"].c_str());
	
	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( MilImage.create(MilWrapper.SysID, cData.xlen, cData.ylen) == -1 )
	{
		cerr << "Error creating MILImage." << endl;
		return -1;
	}
	
	if(!quiet)
	{
		if( disp.create(MilWrapper.SysID) == -1 )
		{
			cerr << "Error creating MILDisplay." << endl;
			return -1;
		}
	}
	
	if( DSimg.create(cData.xlen, cData.ylen) == -1 )
	{
		cerr << "Error creating daystar image" << endl;
		return -1;
	}
	////////////////////////////////////////
	
	// Configure processor object:
	if( myProcessor.configure(cData) != 0 )
	{
		cerr << "Error configuring centroid object." << endl;
		return -1;
	}
	
	// Create centroid list object:
	if(centList.create(cData.maxstars2return) != 0)
	{
		cerr << "Error creating centroid list object." << endl;
		return -1;
	}
	////////////////////////////////////////
	
	if( loadImg(MilImage.ID, infname) == -1 )
	{
		cerr << "Error loading " << infname << " into image " << MilImage.ID << endl;
		return -1;
	}
	
	// Copy Image:
	if( copyImg( MilImage.ID, &DSimg ) == -1 )
	{
		cerr << "Failed to copy MILImage to daystar image." << endl;
		return -1;
	}
	
	// Process Image:
	if( myProcessor.run(&DSimg, &centList) == -1 )
	{
		cerr << "Centroiding " << infname << " failed!" << endl;
	}
	else
	{
		// Print centroids:
		cout.precision(10);
		cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
		cout << centList.numCentroids << ", ";
		for( int i = 0; i < centList.numCentroids; i++ )
			cout << centList.centroid[i].x << ", " << centList.centroid[i].y << ", ";
		cout << endl;
	
		
		// Get user path for saving image or exit:
		if(!quiet)
		{
			// Draw circles around centroids:
			for( int i = 0; i < centList.numCentroids; i++ )
				drawCircle(MilImage.ID, centList.centroid[i].x, centList.centroid[i].y, 15, 15);
				
			if( scaleDisp(disp.ID, cData.bitres) == -1 )
			{
				cerr << "Error changing display " << disp.ID << " to a bit resolution of " << cData.bitres << endl;
				return -1;
			}
	
			if( dispImg(disp.ID, MilImage.ID) == -1 )
			{
				cerr << "Error displaying image " << MilImage.ID << " on display " << disp.ID << endl;
				return -1;
			}
			
			for(;;)
			{
				if( output == 0 )
				{
					cout << "Save File Options:" << endl
						 << "To use default file path input 'y' and [ENTER]."<< endl
						 << "To use custom file path input '/path/to/custom/file.tif' and [ENTER]." << endl
						 << "To exit without saving hit [ENTER]." << endl;
					cout << ">> ";
			
					// Get user input:
					getline(cin,tempfname);
		
					// Determine filename or exit:
					if( !tempfname.compare("") || !tempfname.compare("n") )
					{
						break;
					}
					else if( !tempfname.compare("y") )
					{
						outfname = "";
						int cnt = 0;
						while( infname[cnt] != '.' )
						{
							outfname += infname[cnt];
							cnt++;
						}
						outfname += "_centroided.tif";
						output++;
					}
					else
					{
						outfname = tempfname;
						output++;
					}
				}
				else
				{
					// Save image:
					if( saveImgTIFF(MilImage.ID, outfname) == -1 )
					{
						cerr << "Error saving image to " << outfname << endl;
						outfname.clear();
					}
					else
					{
						cout << "Imaged saved to " << outfname << endl;
						break;
					}
				}
			}
	
			cout << "Press any key to exit." << endl;
			while(!_kbhit())
			{
				// Take a little nap:
				usleep(DEFAULT_SLEEP);
			}
		}
		else
		{
			if( output > 0 )
			{
				// Save image:
				if( saveImgTIFF(MilImage.ID, outfname) == -1 )
				{
					cerr << "Error saving image to " << outfname << endl;
					return -1;
				}
				else
				{
					// cout << "Imaged saved to " << outfname << endl;
				}
			}
		}
	
	}
	
	return 0;
}

/*
int displayContinuous(string fname)
{
	int numFrames;
	double frameRate;
	
	////// ALLOCATION SECTION: ////////////
	MILWrapper MilWrapper;
	MIL_ID* imgs = NULL;
	MILDisplay disp;

	if( MilWrapper.create() == -1 )
	{
		cerr << "Error creating MILWrapper." << endl;
		return -1;
	}
	
	if( disp.create(MilWrapper.SysID) == -1 )
	{
		cerr << "Error creating MILDisplay." << endl;
		return -1;
	}
	////////////////////////////////////////
	
	if( input == 0 )
	{
		cerr << "Input filename must be specified to display video!" << endl;
		return -1;
	}
	
	if( loadVid(imgs, MilWrapper.SysID, numFrames, frameRate, fname) == -1 )
	{
		cerr << "Error loading " << fname << " into image array " << imgs << endl;
		return -1;
	}
	
	if( scaleDisp(disp.ID, bitres) == -1 )
	{
		cerr << "Error changing display " << disp.ID << " to a bit resolution of " << bitres << endl;
		return -1;
	}
	
	if( dispVid(disp.ID, imgs, numFrames, frameRate) == -1 )
	{
		cerr << "Error displaying video with " << numFrames << " frames at " << frameRate << " frames/second." << endl;
		return -1;
	}
	
	return 0;
}
*/

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

