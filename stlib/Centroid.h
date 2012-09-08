
#ifndef _CNTRD_H_
#define _CNTRD_H_

#include "StartrackerData.h"
#include <cstdlib>

using namespace std;

// Defined constants
#define FAILURE -1
#define SUCCESS 0
#define PRINT_MODE 0

struct centroidData
{
	double fovX;
	double fovY;
	double numsigma;
	unsigned int numpixelsinsubsample; //can possibly be a short later
	unsigned short minthresh;
	unsigned short maxthresh;
	unsigned short maxstars;
	unsigned short maxstars2return;
	unsigned short xlen;
	unsigned short ylen;
	unsigned short bitres;
};

class Centroid
{
public:
	// Contructor:
	Centroid();
	~Centroid();
	
	// Public functions:
	int configure(centroidData theData);
	int run(image* img, centroidList* cntrd);
	int resetFlags();
	
	// Variables:
	int semid;
	
private:
	// Functions:
	int correctPixels(double fovX, double fovY);
	int identifyStars(image* img);
	int dfsCoG(image* img, int s, int t);
	int roboMADsub(image* img);
	int roboMAD(image* img);
	int histogramMedianSub(image* img);
	int histogramMedianSub2(image* img);
	int histogramMedian(image* img);
	int histogramMedian2(image* img);
	int roboIWC(image* img);
	void bubbleSort();
	
	// Variables:
	centroidData myData;
	centroidList myList;
	short** stack;
	unsigned int* medhist;
	unsigned int* medhist2;
	unsigned long XIW[2];
	unsigned long IW;
	starCenter cent;
	int xmin, xmax, ymin, ymax;
	int neighb[8][2];
	double mn;
	unsigned short med;
	double std;
	int counts;
	int limit;
	unsigned int numrowsandcols;
	unsigned short dx, dy;
	unsigned short row, col;
	unsigned short levels;
	
	// Added:
	char** flag;
	double** xx;
	double** yy;
};

#endif  //_CNTRD_H_
