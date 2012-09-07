
#if !defined(_STDATA_H)
#define _STDATA_H

// C++ Includes:
#include <iostream>
#include <signal.h>
#include <math.h>
#include <sys/time.h>

using namespace std;

/*
 #define XLENGTH 2560
 #define YLENGTH 2160


struct DayStarImage
{
	unsigned short pixel[XLENGTH][YLENGTH];
	timeval timestamp;
};
*/

// Image class (struct-like) for allocating and deallocating image memory:
// All variables are public for quick "struct-like" access. We avoid using
// set/get functions for speed.
class image
{
	public:
	// Contructor:
	image();
	int create(unsigned int xlength, unsigned int ylength);
	~image();
	
	// Public vars:
	unsigned short** pixel;
	timeval timestamp;
	unsigned int xlen;
	unsigned int ylen;
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
	timeval timestamp;
	
	private:
	
};

#endif  //_STDATA_H
