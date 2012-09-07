
#if !defined(_STPRODATA_H)
#define _STPRODATA_H

// Include Defines:
#include "StartrackerProcessorDefines.h"

// C++ Includes:
#include <iostream>
#include <signal.h>
#include <math.h>

using namespace std;

// Image/Centroid Status Definition (circular image/centroid buffer of length = 3)
struct status
{
	int write;   // Index of shared var being written to
	int wait;    // Index of shared var that is inactive (waiting to be written to or read from)
	int read;    // Index of shared var being read
};

// Struct to hold the data of a single centroid:
struct starCenter
{
	double x;
	double y;
	int intensity;
	int w;
	int h;
};

// Struct to hold pixel values and flags for modification
struct imgPixel
{
	unsigned short val;
	char flag;
	double x;
	double y;
};

// Image class (struct-like) for allocating and deallocating image memory:
// All variables are public for quick "struct-like" access. We avoid using
// set/get functions for speed.
class image
{
	public:
	// Contructor:
	image();
	int create(int xlength, int ylength, double xfov, double yfov);
	~image();
	
	// Public vars:
	imgPixel** pixel;
	unsigned short xlen;
	unsigned short ylen;
	timeval timestamp;
	
	private:
	int correctPixels(double fovX, double fovY);	
};

// Centroid list class (struct-like) for allocating and deallocating image memory:
// All variables are public for quick "struct-like" access. We avoid using
// set/get functions for speed.
class centroidList
{
	public:
	// Contructor:
	centroidList();
	int create(int length);
	~centroidList();
	
	// Public vars:
	starCenter* centroid;
	int numCentroids;
	int maxlen;
	timeval timestamp;
	
	private:
	
};

#endif  //_STPRODATA_H
