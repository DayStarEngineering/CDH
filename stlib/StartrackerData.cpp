#include "StartrackerData.h"

// Image Class:
image::image()
{
	pixel = NULL;
	xlen = 0;
	ylen = 0;
}

int image::create(unsigned int xlength, unsigned int ylength)
{
	xlen = xlength;
	ylen = ylength;
	
	// Allocate memory:
	pixel = new unsigned short*[xlen];
	for( unsigned int i = 0; i < xlen; i++ )
		pixel[i] = new unsigned short[ylen];
		
	return 0;
}

image::~image()
{
	// Deallocate memory:
	if(pixel != NULL)
	{
		for( unsigned int i = 0; i < xlen; i++ )
			delete [] pixel[i];
		delete [] pixel;
		pixel = NULL;
	}
}

// Centroid List Class:
centroidList::centroidList()
{
	centroid = NULL;
}

int centroidList::create(int length)
{
	if(length < 0)
		return -1;
	
	// Set temp size (will be changed during usage):
	numCentroids = length;
	
	// Allocate memory:
	centroid = new starCenter[length];
	
	// Innitialize all values to zero:
	for( int i = 0; i < length; i++ )
	{
		centroid[i].x = 0.0;
		centroid[i].y = 0.0;
		centroid[i].intensity = 0;
		centroid[i].w = 0;
		centroid[i].h = 0;
	}
	
	return 0;
}

centroidList::~centroidList()
{
	// Deallocate memory:
	if(centroid != NULL)
	{
		delete [] centroid;
		centroid = NULL;
	}
}

