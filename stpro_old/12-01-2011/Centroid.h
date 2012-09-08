
#ifndef _CNTRD_H_
#define _CNTRD_H_

#include "StartrackerProcessorData.h"
#include "math.h"

using namespace std;

struct centroidData
{
	unsigned short bitres;
	double numsigma;
	unsigned short minthresh;
	unsigned short maxthresh;
	unsigned short maxstars;
	unsigned int numpixelsinsubsample; //can possibly be a short later
	unsigned short xlen;
	unsigned short ylen;
};

class Centroid
{
public:
	// Contructor:
	Centroid();
	~Centroid();
	
	// Public functions:
	int configure(centroidData theData, Logger* aLogger);
	int setSigma(double sigma);
	int run(image* img, centroidList* cntrd);
	
	// Variables:
	int semid;
	
private:
	// Functions:
	int identifyStars(image* img, centroidList* cntrd);
	int dfsCoG(image* img, int s, int t);
	int roboMADsub(image* img);
	int roboMAD(image* img);
	void histogramMedianSub(image* img);
	int histogramMedianSub2(image* img);
	void histogramMedian(image* img);
	int histogramMedian2(image* img);
	int roboIWC(image* img);
	void bubbleSort(centroidList* cntrd);
	
	// Loggers:
	Logger* myLogger;
	
	// Variables:
	centroidData myData;
	short** stack;
	unsigned int* medhist;
	unsigned long XIW[2];
	unsigned long IW;
	starCenter cent;
	int xmin, xmax, ymin, ymax;
	int neighb[4][2];
	double mn;
	unsigned short med;
	double std;
	int counts;
	int limit;
	unsigned int numrowsandcols;
	unsigned short dx, dy;
	unsigned short row, col;
	unsigned short levels;
};

#endif  //_CNTRD_H_
