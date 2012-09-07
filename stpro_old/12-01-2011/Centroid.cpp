#include "Centroid.h"

// Defined constants
#define FAILURE -1
#define SUCCESS 0

Centroid::Centroid()
{
	// Initialize values
	mn = 0;
	med = 0;
	std = 0;
	limit = -1;
	stack = NULL;
	medhist = NULL;
}

Centroid::~Centroid()
{
	// De-allocate stack memory
	if (stack != NULL)
	{
		for (int i = 0; i < myData.maxstars; i++)
			delete [] stack[i];
		delete [] stack;
		stack = NULL;
	}
	
	// De-allocate median histogram memory
	if (medhist != NULL)
	{
		delete [] medhist;
		medhist = NULL;
	}
}

int Centroid::configure(centroidData theData, Logger* aLogger)
{
	if (aLogger == NULL)
		return FAILURE;
	if (theData.bitres < 0 || theData.bitres > 16)
		return FAILURE;
	if (theData.numsigma < 0 || theData.numsigma > 10)
		return FAILURE;
	if (theData.minthresh < 0 || theData.maxthresh < 0 || theData.minthresh >= theData.maxthresh)
		return FAILURE;
	if (theData.maxstars < 1)
		return FAILURE;
	if (theData.numpixelsinsubsample == 0 || theData.numpixelsinsubsample > 500000)
		return FAILURE;
	if (theData.xlen == 0 || theData.xlen > 3000 || theData.ylen == 0 || theData.ylen > 3000)
		return FAILURE;
	
	// Copy over objects
	myLogger = aLogger;
	myData = theData;
	
	// Set levels
	levels = pow(2,myData.bitres);
	
	// Compute number of rows and columns to sample: approximate ceil() function
	numrowsandcols = (unsigned int) (sqrt(theData.numpixelsinsubsample)+1);
	
	// Compute spacing of rows and columns
	dx = (unsigned short) (theData.xlen)/numrowsandcols;
	dy = (unsigned short) (theData.ylen)/numrowsandcols;
	
	// Allocate median histogram memory
	medhist = new unsigned int[levels];
	
	// Allocate stack memory
	stack = new short*[myData.maxstars];
	for (int i = 0; i < myData.maxstars; i++)
		stack[i] = new short[2];
	
	return SUCCESS;
}

int Centroid::setSigma(double sigma)
{
	if(sigma < 0 || sigma > 10)
		return FAILURE;
	myData.numsigma = sigma;
	return SUCCESS;
}

int Centroid::run(image* img, centroidList* cntrd)
{
	//cout<<"start run"<<endl;
	// Copy over image time stamp
	cntrd->timestamp = img->timestamp;
	#if DEBUG_MODE == 1
	cntrd->testTimes = img->testTimes;
	#endif
	
	if (img == NULL)
		return FAILURE;
	if (cntrd == NULL)
		return FAILURE;
	
	//cout<<"roboMADsub"<<endl;
	// Get mean and standard deviation
	if (roboMADsub(img) == FAILURE)
		return FAILURE;
	// cout<<"mn "<<mn<<" std "<<std<<" med "<<med<<endl;
	limit = (int) mn + myData.numsigma*std;
	// NEED TO DEFINE A MINIMUM LIMIT AND NEVER GO BELOW THAT
	// cout << "limit = " << limit << endl;
	// Identify possible stars in the image
	//cout<<"identifyStars"<<endl;
	if (identifyStars(img,cntrd) == FAILURE)
		return FAILURE;
	// Sort all centroids by intensity
	//cout<<"bubbleSort"<<endl;
	bubbleSort(cntrd);
	
	//cout<<"end run"<<endl;
	return SUCCESS;
}

int Centroid::identifyStars(image* img, centroidList* cntrd)
{
	// Initialize index to track number of centroids in image
	int ind = -1;
	// Identify and explore possible stars
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			if (img->pixel[i][j].val > limit)
			{
				// Explore bright cells
				if (dfsCoG(img,i,j) < 0)
				{
					// Can make checks for different errors here
					continue; //maybe need to do more depending on data struct
				}
				// Make sure the max number of centroids have not been found
				if (ind == cntrd->maxlen-1)
				{
					break; //consider ending the search here to save time
					// Need to get out of both loops
				}
				// Improve upon the CoG result
				if (roboIWC(img) < 0)
				{
					// Can make checks for different errors here
					continue; //maybe need to do more depending on data struct
				}
				// Store the centroid
				ind++;
				cntrd->centroid[ind].x = cent.x;
				cntrd->centroid[ind].y = cent.y;
				cntrd->centroid[ind].intensity = cent.intensity;
			}
		}
	}
	// Store the number of centroids found in this image
	cntrd->numCentroids = ind+1;
	
	return SUCCESS;
}

int Centroid::roboIWC(image* img)
{
	//cout<<"roboIWC"<<endl;
	// CoG has already been called at this point
	int subR = ((cent.w>cent.h)?cent.w:cent.h)/2 + 2;
	
    // Check to see if the star is "too close" to the edge
    if (cent.x < subR || cent.x >= myData.xlen-subR)
		return FAILURE;
	if (cent.y < subR || cent.y >= myData.ylen-subR)
		return FAILURE;
	
	// Loop over the subframe and calculate the intensity weighted centroid
	XIW[0] = 0;
	XIW[1] = 0;
	IW = 0;
	for (int i = cent.x-subR; i <= cent.x+subR; i++)
	{
		for (int j = cent.y-subR; j <= cent.y+subR; j++)
		{
			// Skip calculations with "negative" intensities (set them to zero)
			if (img->pixel[i][j].val <= med)
				continue;
			//XIW[0] += i*pow(img->pixel[i][j].val-med,2);
			//XIW[1] += j*pow(img->pixel[i][j].val-med,2);
			XIW[0] += (img->pixel[i][j].x)*pow(img->pixel[i][j].val-med,2);
			XIW[1] += (img->pixel[i][j].y)*pow(img->pixel[i][j].val-med,2);
			IW += pow(img->pixel[i][j].val-med,2);
		}
	}
	// cout<<"newx "<<(double) XIW[0]/IW<<" newy "<<(double) XIW[1]/IW<<endl;
    
    return SUCCESS;
}

int Centroid::dfsCoG(image* img, int s, int t)
{
	//cout<<"dfsCoG"<<endl;
	// Initialize variable to be used in the loop
	bool onEdge = false;
	// Push source node (s,t) onto stack
	int ind = 0; //stack index pointer
	stack[ind][0] = s;
	stack[ind][1] = t;
	// Store node as geometric center
	xmin = s;
	xmax = s;
	ymin = t;
	ymax = t;
	// Store source info to CoG calculation
	//XIW[0] = s*(img->pixel[s][t].val-limit);
	//XIW[1] = t*(img->pixel[s][t].val-limit);
	XIW[0] = (img->pixel[s][t].x)*(img->pixel[s][t].val-limit);
	XIW[1] = (img->pixel[s][t].y)*(img->pixel[s][t].val-limit);
	IW = img->pixel[s][t].val-limit;
	// Mark source
	img->pixel[s][t].flag = 1;
	// Begin exploration
	int numNodes = 1;
	while (ind > -1 && numNodes < myData.maxthresh)
	{
		// Pop last element into node (s,t)
		s = stack[ind][0];
		t = stack[ind][1];
		ind -= 1;
		// Check if node (s,t) updates the geometric center
		if (s < xmin)
			xmin = s;
		if (s > xmax)
			xmax = s;
		if (t < ymin)
			ymin = t;
		if (t > ymax)
			ymax = t;
		// Explore every edge from node (s,t)
		neighb[0][0] = s-1; //above
		neighb[0][1] = t;
		neighb[1][0] = s; //left
		neighb[1][1] = t-1;
		neighb[2][0] = s; //right
		neighb[2][1] = t+1;
		neighb[3][0] = s+1; //below
		neighb[3][1] = t;
		for (int i = 0; i < 4; i++)
		{
			// Assume the neighbor's position
			s = neighb[i][0];
			t = neighb[i][1];
			// Don't explore outside image bounds
			if (s < 0 || s >= myData.xlen)
			{
				onEdge = true;
				continue;
			}
			if (t < 0 || t >= myData.ylen)
			{
				onEdge = true;
				continue;
			}
			// Explore if not marked
			if (img->pixel[s][t].val > limit && img->pixel[s][t].flag == 0)
			{
				// Push node
				ind += 1;
				stack[ind][0] = s;
				stack[ind][1] = t;
				// Store node info to CoG calculation
				//XIW[0] += s*(img->pixel[s][t].val-limit);
				//XIW[1] += t*(img->pixel[s][t].val-limit);
				XIW[0] = (img->pixel[s][t].x)*(img->pixel[s][t].val-limit);
				XIW[1] = (img->pixel[s][t].y)*(img->pixel[s][t].val-limit);
				IW += img->pixel[s][t].val-limit;
				// Mark node
				numNodes += 1;
				img->pixel[s][t].flag = 1;
			}
		}
	}
	// Determine if the patch has the desired number of pixels
	if (numNodes < myData.minthresh)
		return FAILURE;
	if (numNodes > myData.maxthresh)
		return FAILURE;
	// Check that the patch is not on the edge of the image
	if (onEdge)
		return FAILURE;
	// Check the elliptical nature of the patch
	//cout<<"ellipse "<<(double) (xmax-xmin)/(ymax-ymin)<<endl;
	// Check/Compute dimension of the patch
	cent.w = ymax - ymin;
	cent.h = xmax - xmin;
	// Compute CoG of this patch
	cent.x = (double) XIW[0]/IW;
	cent.y = (double) XIW[1]/IW;
	cent.intensity = IW;
	
	return SUCCESS;
}

int Centroid::roboMADsub(image* img)
{
	// Step 1: Start by getting the median and MAD as robust proxies for the
	//         mean and standard deviation
	
	//cout<<"histogramMedianSub"<<endl;
	// Calculate median
	histogramMedianSub(img);
	// Verify the median has been set
	if (med < 0)
		return FAILURE;
	//cout<<"med = "<<med<<endl;
	// Calculate MAD and store as standard deviation
	//cout<<"histogramMedianSub2"<<endl;
	std = 1.4826*histogramMedianSub2(img); //applies for normally distributed data
	// Check that histogramMedianSub2 was successful (return FAILURE when fails)
	if (std <= 0)
		return FAILURE;
	//cout<<"std = "<<std<<endl;
	
	// Step 2: Identify outliers, recompute mean and std with pixels that remain
	
	//cout<<"step 2"<<endl;
	//cout<<"exclude outliers 1"<<endl;
	unsigned long sum = 0;
	int goodPix = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Exclude outliers from the calculation
			if (abs(img->pixel[row][col].val-med) < 5*std)
			{
				sum += img->pixel[row][col].val;
				goodPix++;
			}
		}
	}
	//cout<<"done exclude outliers 1"<<endl;
	// cout<<"sum = "<<sum<<endl;
	// cout<<"goodPix = "<<goodPix<<endl;
	if (goodPix == 0)
		return FAILURE;
	mn = (double) sum/goodPix;
	// cout<<"mn = "<<mn<<endl;
	//cout<<"exclude outliers 2"<<endl;
	sum = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++ )
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[row][col].val-med) < 5*std)
				sum += pow(img->pixel[row][col].val-mn,2);
		}
	}
	//cout<<"done exclude outliers 2"<<endl;
	// cout<<"sum = "<<sum<<endl;
	std = sqrt((double) sum/goodPix);
	// cout<<"std = "<<std<<endl;
	
	// Step 3: Repeat step 2 with new mean and standard deviation values
	
	//cout<<"step 3"<<endl;
	//cout<<"exclude outliers 1"<<endl;
	sum = 0;
	goodPix = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Exclude outliers from the calculation
			if (abs(img->pixel[row][col].val-(int) mn) < 5*std)
			{
				sum += img->pixel[row][col].val;
				goodPix++;
			}
		}
	}
	//cout<<"done exclude outliers 1"<<endl;
	// cout<<"sum = "<<sum<<endl;
	// cout<<"goodPix = "<<goodPix<<endl;
	double mn2 = (double) sum/goodPix;
	// cout<<"mn = "<<mn<<endl;
	//cout<<"exclude outliers 2"<<endl;
	sum = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++ )
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[row][col].val-(int) mn2) < 5*std)
				sum += pow(img->pixel[row][col].val-mn2,2);
		}
	}
	//cout<<"done exclude outliers 2"<<endl;
	mn = mn2;
	// cout<<"sum = "<<sum<<endl;
	std = sqrt((double) sum/goodPix);
	// cout<<"std = "<<std<<endl;
	
	return SUCCESS;
}

int Centroid::roboMAD(image* img)
{
	// Step 1: Start by getting the median and MAD as robust proxies for the
	//         mean and standard deviation
	
	//cout<<"histogramMedian"<<endl;
	// Calculate median
	histogramMedian(img);
	// Verify the median has been set
	if (med < 0)
		return FAILURE;
	//cout<<"med = "<<med<<endl;
	// Calculate MAD and store as standard deviation
	//cout<<"histogramMedian2"<<endl;
	std = 1.4826*histogramMedian2(img); //applies for normally distributed data
	// Check that histogramMedian2 was successful (return FAILURE when fails)
	if (std <= 0)
		return FAILURE;
	//cout<<"std = "<<std<<endl;
	
	// Step 2: Identify outliers, recompute mean and std with pixels that remain
	
	//cout<<"step 2"<<endl;
	//cout<<"exclude outliers 1"<<endl;
	unsigned long sum = 0;
	int goodPix = 0;
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Exclude outliers from the calculation
			if (abs(img->pixel[i][j].val-med) < 5*std)
			{
				sum += img->pixel[i][j].val;
				goodPix++;
			}
		}
	}
	//cout<<"done exclude outliers 1"<<endl;
	// cout<<"sum = "<<sum<<endl;
	// cout<<"goodPix = "<<goodPix<<endl;
	if (goodPix == 0)
		return FAILURE;
	mn = (double) sum/goodPix;
	// cout<<"mn = "<<mn<<endl;
	//cout<<"exclude outliers 2"<<endl;
	sum = 0;
	for (int i = 0; i < myData.xlen; i++ )
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[i][j].val-med) < 5*std)
				sum += pow(img->pixel[i][j].val-mn,2);
		}
	}
	//cout<<"done exclude outliers 2"<<endl;
	// cout<<"sum = "<<sum<<endl;
	std = sqrt((double) sum/goodPix);
	// cout<<"std = "<<std<<endl;
	
	// Step 3: Repeat step 2 with new mean and standard deviation values
	
	//cout<<"step 3"<<endl;
	//cout<<"exclude outliers 1"<<endl;
	sum = 0;
	goodPix = 0;
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Exclude outliers from the calculation
			if (abs(img->pixel[i][j].val-(int) mn) < 5*std)
			{
				sum += img->pixel[i][j].val;
				goodPix++;
			}
		}
	}
	//cout<<"done exclude outliers 1"<<endl;
	// cout<<"sum = "<<sum<<endl;
	// cout<<"goodPix = "<<goodPix<<endl;
	double mn2 = (double) sum/goodPix;
	// cout<<"mn = "<<mn<<endl;
	//cout<<"exclude outliers 2"<<endl;
	sum = 0;
	for (int i = 0; i < myData.xlen; i++ )
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[i][j].val-(int) mn2) < 5*std)
				sum += pow(img->pixel[i][j].val-mn2,2);
		}
	}
	//cout<<"done exclude outliers 2"<<endl;
	mn = mn2;
	// cout<<"sum = "<<sum<<endl;
	std = sqrt((double) sum/goodPix);
	// cout<<"std = "<<std<<endl;
	
	return SUCCESS;
}

void Centroid::histogramMedianSub(image* img)
{
	med = -1;
	// Initialize all bins to zero
	for (int i = 0; i < levels; i++)
	{
		medhist[i] = 0;
	}
	// Populate histogram
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			medhist[img->pixel[row][col].val]++;
		}
	}
	// Find median
	counts = (int) ((myData.xlen)*(myData.ylen))/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
		{
			med = i;
			break;
		}
	}
}

int Centroid::histogramMedianSub2(image* img)
{
	// Initialize all bins to zero
	for (int i = 0; i < levels; i++)
	{
		medhist[i] = 0;
	}
	// Populate histogram (assumes median has already been calculated)
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			medhist[abs(img->pixel[row][col].val-med)]++;
		}
	}
	// Find median, which corresponds to the Median Absolute Deviation
	counts = (int) ((myData.xlen)*(myData.ylen))/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
			return i;
	}
	return FAILURE;
}

void Centroid::histogramMedian(image* img)
{
	med = -1;
	// Initialize all bins to zero
	for (int i = 0; i < levels; i++)
	{
		medhist[i] = 0;
	}
	// Populate histogram
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			medhist[img->pixel[i][j].val]++;
		}
	}
	// Find median
	counts = (int) ((myData.xlen)*(myData.ylen))/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
		{
			med = i;
			break;
		}
	}
}

int Centroid::histogramMedian2(image* img)
{
	// Initialize all bins to zero
	for (int i = 0; i < levels; i++)
	{
		medhist[i] = 0;
	}
	// Populate histogram (assumes median has already been calculated)
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			medhist[abs(img->pixel[i][j].val-med)]++;
		}
	}
	// Find median, which corresponds to the Median Absolute Deviation
	counts = (int) ((myData.xlen)*(myData.ylen))/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
			return i;
	}
	return FAILURE;
}

void Centroid::bubbleSort(centroidList* cntrd)
{
	int n = cntrd->numCentroids;
	int newn;
	while (n > 0)
	{
		newn = 0;
		for (int i = 1; i < n; i++)
		{
			if (cntrd->centroid[i-1].intensity < cntrd->centroid[i].intensity)
			{
				// Swap using cent as swap space
				cent = cntrd->centroid[i-1];
				cntrd->centroid[i-1] = cntrd->centroid[i];
				cntrd->centroid[i] = cent;
				// Set max bound
				newn = i;
			}
		}
		n = newn;
	}
}
