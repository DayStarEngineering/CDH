#include "StartrackerProcessorData.h"

#if DEBUG_MODE == 1
// timeTest Class:
timeTest::timeTest()
{
	// Set desired precision:
    cout.precision(10);
    cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
}
timeTest::~timeTest(){}

void timeTest::printTimes()
{
    /*
    cout << inTime.startTime.tv_sec << " " <<
    		inTime.endTime.tv_sec << " ";
    cout << procTime.startTime.tv_sec << " " <<
    		procTime.endTime.tv_sec << " ";
    cout << outTime.startTime.tv_sec << " " <<
    		outTime.endTime.tv_sec << " "<< endl;
    		
    cout << inTime.startTime.tv_usec << " " <<
    		inTime.endTime.tv_usec << " ";
    cout << procTime.startTime.tv_usec << " " <<
    		procTime.endTime.tv_usec << " ";
    cout << outTime.startTime.tv_usec << " " <<
    		outTime.endTime.tv_usec << " "<< endl << endl << endl;
    */
    
	// inTime:
	cout << ((double)(inTime.endTime.tv_sec) + (((double)inTime.endTime.tv_usec)/1000000.0)) -
			((double)(inTime.startTime.tv_sec) + (((double)inTime.startTime.tv_usec)/1000000.0))
		 << " ";
	
	// latency1:
	double l1 = ((double)(procTime.startTime.tv_sec) + (((double)procTime.startTime.tv_usec)/1000000.0)) -
				((double)(inTime.endTime.tv_sec) + (((double)inTime.endTime.tv_usec)/1000000.0));
	cout << l1
		 << " ";
		 
	// procTime:
	cout << ((double)(procTime.endTime.tv_sec) + (((double)procTime.endTime.tv_usec)/1000000.0)) -
			((double)(procTime.startTime.tv_sec) + (((double)procTime.startTime.tv_usec)/1000000.0))
		 << " ";
		 
	// latency2:
	double l2 = ((double)(outTime.startTime.tv_sec) + (((double)outTime.startTime.tv_usec)/1000000.0)) -
				((double)(procTime.endTime.tv_sec) + (((double)procTime.endTime.tv_usec)/1000000.0));
	cout << l2
		 << " ";
	
	// outTime:
	cout << ((double)(outTime.endTime.tv_sec) + (((double)outTime.endTime.tv_usec)/1000000.0)) -
			((double)(outTime.startTime.tv_sec) + (((double)outTime.startTime.tv_usec)/1000000.0))
		 << " ";
	
	// Total Latency:
	cout << l1 + l2
		 << " ";
	
	// Total Run Time:
	double t = ((double)(outTime.endTime.tv_sec) + (((double)outTime.endTime.tv_usec)/1000000.0)) -
			((double)(inTime.startTime.tv_sec) + (((double)inTime.startTime.tv_usec)/1000000.0));
	cout << t - (l1 + l2)
		 << " "; 
		 
	// Total Time:
	cout << t
		 << endl; 
	
	/*
	// inTime:	 
	cout << ((double)(inTime.endTime.tv_sec - inTime.startTime.tv_sec)) +
			(((double)(inTime.endTime.tv_usec - inTime.startTime.tv_usec))/1000000.0)
		 << " ";
	
	// latency1:
	double l1 = ((double)(procTime.startTime.tv_sec - inTime.endTime.tv_sec)) +
				(((double)(procTime.startTime.tv_usec - inTime.endTime.tv_usec))/1000000.0);
	cout << l1
		 << " ";
	
	// procTime:
	cout << ((double)(procTime.endTime.tv_sec - procTime.startTime.tv_sec)) +
			(((double)(procTime.endTime.tv_usec - procTime.startTime.tv_usec))/1000000.0)
		 << " ";
	
	// latency2:
	double l2 = ((double)(outTime.startTime.tv_sec - procTime.endTime.tv_sec)) +
				(((double)(outTime.startTime.tv_usec - procTime.endTime.tv_usec))/1000000.0);
	cout << l2
		 << " ";
	
	// outTime:
	cout << ((double)(outTime.endTime.tv_sec - outTime.startTime.tv_sec)) +
			(((double)(outTime.endTime.tv_usec - outTime.startTime.tv_usec))/1000000.0)
		 << " ";
		 
	// Total Latency:
	cout << l1 + l2
		 << " ";
	
	// Total Time:
	cout << ((double)(outTime.endTime.tv_sec - inTime.startTime.tv_sec)) +
			(((double)(outTime.endTime.tv_usec - inTime.startTime.tv_usec))/1000000.0)
		 << endl;
	*/
}
#endif

// Image Class:
image::image()
{
	pixel = NULL;
}

int image::create(int xlength, int ylength, double xfov, double yfov)
{
	if(xlength < 0 || ylength < 0 || xfov < 0 || yfov < 0)
		return -1;	
	
	// Set sizes:
	xlen = xlength; ylen = ylength;
	
	// Allocate memory:
	pixel = new imgPixel* [xlen];
	for( int i = 0; i < xlen; i++ )
		pixel[i] = new imgPixel[ylen];
		
	// Innitialize all values to zero:
	for( int i = 0; i < xlen; i++ )
	{
		for( int j = 0; j < ylen; j++ )
		{
			pixel[i][j].val = 0;
			pixel[i][j].flag = 0;
		}
	}
	
	if(correctPixels( xfov , yfov ) != 0)
		return -1;
	
	return 0;
}

image::~image()
{
	// Deallocate memory:
	if(pixel != NULL)
	{
		for( int i = 0; i < xlen; i++ )
			delete [] pixel[i];
		delete [] pixel;
		pixel = NULL;
	}
}

// Apply gnomonic projection correction to image pixel locations:
int image::correctPixels(double fovX, double fovY) // [rad]
{
	// Protect against divide by 0 error:
	if(fovX < 0 || fovY < 0)
		return -1;
	
	double thetaX = 0;       // [rad]
	double thetaY = 0;       // [rad]   
	double platescaleX = 0;  // [rad / pixel]
	double platescaleY = 0;  // [rad / pixel]
	
	// Find platescale [rad]:
	platescaleX = fovX/xlen;
	platescaleY = fovY/ylen;
	
	// Iterate through each pixel location:
	for(int i = 0; i < xlen; i++)
	{	
		for(int j = 0; j < ylen; j++)
		{
			thetaX = platescaleX*fabs(i - xlen/2.0);
			thetaY = platescaleY*fabs(j - ylen/2.0);
			pixel[i][j].x = fovX/2.0 * (sin(thetaX)-tan(thetaX)*cos(fovX/2.0)) / sin(fovX/2);
			pixel[i][j].y = fovY/2.0 * (sin(thetaY)-tan(thetaY)*cos(fovY/2.0)) / sin(fovY/2);		
		}
	}
	
	return 0;
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
	
	// Set sizes:
	maxlen = length;
	
	// Set temp size (will be changed during usage):
	numCentroids = length;
	
	// Allocate memory:
	centroid = new starCenter[maxlen];
	
	// Innitialize all values to zero:
	for( int i = 0; i < maxlen; i++ )
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
