#include "Centroid.h"

Centroid::Centroid()
{
	// Initialize values
	mn = 0;
	med = 0;
	std = 0;
	limit = -1;
	stack = NULL;
	medhist = NULL;
	medhist2 = NULL;
	flag = NULL;
	xx = NULL;
	yy = NULL;
}

Centroid::~Centroid()
{
	// De-allocate stack memory:
	if (stack != NULL)
	{
		for (int i = 0; i < myData.xlen*myData.ylen; i++)
			delete [] stack[i];
		delete [] stack;
		stack = NULL;
	}
	
	// De-allocate median histogram memory:
	if (medhist != NULL)
	{
		delete [] medhist;
		medhist = NULL;
	}
	if (medhist2 != NULL)
	{
		delete [] medhist2;
		medhist2 = NULL;
	}
	
	// De-allocate flag memory:
	if (flag != NULL)
	{
		for (int i = 0; i < myData.xlen; i++)
			delete [] flag[i];
		delete [] flag;
		flag = NULL;
	}
	
	// De-allocate xx memory:
	if (xx != NULL)
	{
		for (int i = 0; i < myData.xlen; i++)
			delete [] xx[i];
		delete [] xx;
		xx = NULL;
	}
	
	// De-allocate yy memory:
	if (yy != NULL)
	{
		for (int i = 0; i < myData.xlen; i++)
			delete [] yy[i];
		delete [] yy;
		yy = NULL;
	}
}

int Centroid::configure(centroidData theData)
{
	if (theData.fovX < 0 || theData.fovY < 0)
		return FAILURE;
	if (theData.numsigma < 0 || theData.numsigma > 10)
		return FAILURE;
	if (theData.numpixelsinsubsample <= 0)
		return FAILURE;
	if (theData.minthresh < 1 || theData.maxthresh < 1)
		return FAILURE;
	if (theData.minthresh >= theData.maxthresh)
		return FAILURE;
	if (theData.maxstars < 1)
		return FAILURE;
	if (theData.maxstars2return < 1)
		return FAILURE;
	if (theData.maxstars2return > theData.maxstars)
		return FAILURE;
	if (theData.xlen < 1 || theData.xlen > 3000 || theData.ylen < 1 || theData.ylen > 3000)
		return FAILURE;
	if (theData.bitres < 1 || theData.bitres > 16)
		return FAILURE;
	
	// Copy over objects
	myData = theData;
	
	// Set levels
	levels = pow(2,myData.bitres);
	
	// Compute number of rows and columns to sample: approximate ceil() function
	numrowsandcols = (unsigned int) (sqrt(theData.numpixelsinsubsample)+1);
	
	// Compute spacing of rows and columns
	dx = (unsigned short) (theData.xlen)/numrowsandcols;
	dy = (unsigned short) (theData.ylen)/numrowsandcols;
	
	// Allocate centroidList memory:
	myList.create(myData.maxstars);
	
	// Allocate median histogram memory
	medhist = new unsigned int[levels];
	medhist2 = new unsigned int[levels];
	
	// Allocate stack memory
	// NOTE THAT THIS IS THE SIZE OF THE IMAGE, SO WE DON'T NEED TO CHECK
	// THE INDEX INTO THE STACK IN dfsCoG
	stack = new short*[myData.xlen*myData.ylen];
	for (int i = 0; i < myData.xlen*myData.ylen; i++)
		stack[i] = new short[2];
	
	// Allocate flag memory:
	flag = new char*[myData.xlen];
	for (int i = 0; i < myData.xlen; i++)
		flag[i] = new char[myData.ylen];
	
	// Allocate xx memory:
	xx = new double*[myData.xlen];
	for (int i = 0; i < myData.xlen; i++)
		xx[i] = new double[myData.ylen];
	
	// Allocate yy memory:
	yy = new double*[myData.xlen];
	for (int i = 0; i < myData.xlen; i++)
		yy[i] = new double[myData.ylen];
	
	// Compute gnomonic tangent correction:
	if (correctPixels(myData.fovX,myData.fovY) != SUCCESS)
		return FAILURE;
	
	// Initialize the flags to zero:
	int ret;
	if ((ret = resetFlags()) != SUCCESS) //currently cannot happen
	{
		return ret;
	}
	
	return SUCCESS;
}

int Centroid::run(image* img, centroidList* cntrd)
{
	
	#if PRINT_MODE == 1
	cout<<"CNTRD: start run"<<endl;
	#endif
	
	if (img == NULL)
		return FAILURE;
	if (cntrd == NULL)
		return FAILURE;
		
	// Copy over image time stamp
	cntrd->timestamp = img->timestamp;
	
	#if PRINT_MODE == 1
	cout<<"CNTRD: roboMAD"<<endl;
	#endif
	
	// Get mean and standard deviation
	if (roboMADsub(img) == FAILURE)
		return FAILURE;
	
	#if PRINT_MODE == 1
	cout<<"mn "<<mn<<" std "<<std<<" med "<<med<<endl;
	#endif
	
	limit = (int) (mn + (double) myData.numsigma*std);
	// NEED TO DEFINE A MINIMUM LIMIT AND NEVER GO BELOW THAT
	#if PRINT_MODE == 1
	cout << "limit = " << limit << endl;
	cout<<"CNTRD: identifyStars"<<endl;
	#endif
	
	// Identify possible stars in the image
	if (identifyStars(img) == FAILURE)
		return FAILURE;
	
	// Sort all centroids by intensity
	#if PRINT_MODE == 1
	cout<<"CNTRD: "<<myList.numCentroids<<" centroids found."<<endl;
	cout<<"CNTRD: bubbleSort"<<endl;
	#endif
	bubbleSort();
	
	// Determine number of stars to copy over into user data structure:
	int numstars2copy;
	if( myList.numCentroids <= myData.maxstars2return)
		numstars2copy = myList.numCentroids;
	else
		numstars2copy = myData.maxstars2return;
	
	#if PRINT_MODE == 1
	cout<<"CNTRD: Copying "<< numstars2copy <<" centroids"<<endl;
	#endif
	
	// Copy over and return the desired number of star centroids:
	int cnt = 0;
	while (cnt < numstars2copy)
	{
		cntrd->centroid[cnt].x = myList.centroid[cnt].x;
		cntrd->centroid[cnt].y = myList.centroid[cnt].y;
		cntrd->centroid[cnt].intensity = myList.centroid[cnt].intensity;
		cntrd->centroid[cnt].w = myList.centroid[cnt].w;
		cntrd->centroid[cnt].h = myList.centroid[cnt].h;
		cnt++;
	}
	cntrd->numCentroids = cnt;
	
	#if PRINT_MODE == 1
	cout<<"CNTRD: end run()"<<endl;
	#endif
	return SUCCESS;
}

int Centroid::resetFlags()
{
	// Reset the DFS pixel flags:
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			flag[i][j] = 0;
		}
	}
	
	// Initialize all histogram bins to zero:
	for (int i = 0; i < levels; i++)
	{
		medhist[i] = 0;
		medhist2[i] = 0;
	}
	
	return SUCCESS;
}

// Apply gnomonic projection correction to image pixel locations:
int Centroid::correctPixels(double fovX, double fovY) // [rad]
{
	// Protect against divide by 0 error:
	if(fovX < 0 || fovY < 0)
		return FAILURE;
	
	////////////////////////////////////////
	// Set Pixel Value as index:
	////////////////////////////////////////
	for(int i = 0; i < myData.xlen; i++)
	{	
		for(int j = 0; j < myData.ylen; j++)
		{
			// Correct pixel at this location:
			xx[i][j] = i;
			yy[i][j] = j;	
		}
	}
	
	////////////////////////////////////////
	// Half Pixel Offset:
	////////////////////////////////////////
	for(int i = 0; i < myData.xlen; i++)
	{	
		for(int j = 0; j < myData.ylen; j++)
		{
			// Correct pixel at this location:
			xx[i][j] += 0.5;
			yy[i][j] += 0.5;	
		}
	}
	
	////////////////////////////////////////
	// Gnomonic Projection:
	////////////////////////////////////////
	
	double thetaX = 0;       // [rad]
	double thetaY = 0;       // [rad]   
	double platescaleX = 0;  // [rad / pixel]
	double platescaleY = 0;  // [rad / pixel]
	
	// Find platescale [rad]:
	platescaleX = fovX/myData.xlen;
	platescaleY = fovY/myData.ylen;
	// cout << "platescale [" << platescaleX << " " << platescaleY << "] " <<endl;
	
	// Iterate through each pixel location:
	for(int i = 0; i < myData.xlen; i++)
	{	
		for(int j = 0; j < myData.ylen; j++)
		{
			// Find angle theta, between (pixel index + 0.5) and middle of image:
			thetaX = platescaleX*(myData.xlen/2.0 - (i+0.5));
			thetaY = platescaleY*(myData.ylen/2.0 - (j+0.5));
			
			// Correct pixel at this location:
			xx[i][j] += fovX/2.0 * (sin(thetaX)-tan(thetaX)*cos(fovX/2.0)) / sin(fovX/2.0) / platescaleX;
			yy[i][j] += fovY/2.0 * (sin(thetaY)-tan(thetaY)*cos(fovY/2.0)) / sin(fovY/2.0) / platescaleY;
			
			// cout << "[ " <<	thetaX << ", " << thetaY << " ], ";
			// cout << "[ " <<	xx[i][j] << ", " << yy[i][j] << " ], ";
		}
		// cout << endl;
	}
	
	return SUCCESS;
}

int Centroid::identifyStars(image* img)
{
	// Initialize index to track number of centroids in image
	int ind = 0;
	// Identify and explore possible stars
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			if (img->pixel[i][j] > limit)
			{
				// Explore bright cells
				if (dfsCoG(img,i,j) != SUCCESS)
				{
					// Can make checks for different errors here
					continue; //maybe need to do more depending on data struct
				}
				// Make sure the max number of centroids have not been found
				#if PRINT_MODE == 1
				//cout << "ind = " << ind << endl;
				#endif
				if (ind == myData.maxstars)
				{
					goto END;
				}
				// Improve upon the CoG result
				if (roboIWC(img) != SUCCESS)
				{
					// Can make checks for different errors here
					continue; //maybe need to do more depending on data struct
				}
				// Store the centroid
				myList.centroid[ind].x = cent.x;
				myList.centroid[ind].y = cent.y;
				myList.centroid[ind].intensity = cent.intensity;
				ind++;
			}
		}
	}
	///////////////////////////////
	END:
	///////////////////////////////
	
	// Store the number of centroids found in this image
	myList.numCentroids = ind;
	
	return SUCCESS;
}

int Centroid::roboIWC(image* img)
{
	#if PRINT_MODE == 1
	//cout<<"roboIWC"<<endl;
	#endif
	// CoG has already been called at this point
	int subR = ((cent.w>cent.h)?cent.w:cent.h)/2 + 2;
	#if PRINT_MODE == 1
	//cout<<"subR "<<subR<<" w "<<cent.w<<" h "<<cent.h<<" x "<<cent.x<<" y "<<cent.y<<endl;
	#endif
	
    // Check to see if the star is "too close" to the edge
    if (cent.x < subR || cent.x >= img->xlen-subR)
		return FAILURE;
	if (cent.y < subR || cent.y >= img->ylen-subR)
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
			if (img->pixel[i][j] <= med)
				continue;
			//XIW[0] += i*pow(img->pixel[i][j]-med,2);
			//XIW[1] += j*pow(img->pixel[i][j]-med,2);
			XIW[0] += xx[i][j]*pow(img->pixel[i][j]-med,2);
			XIW[1] += yy[i][j]*pow(img->pixel[i][j]-med,2);
			IW += pow(img->pixel[i][j]-med,2);
		}
	}
	cent.x = ((double) XIW[0])/((double) IW);
	cent.y = ((double) XIW[1])/((double) IW);
	#if PRINT_MODE == 1
	//cout<<"newx "<<cent.x<<" newy "<<cent.y<<endl;
	#endif
    
    return SUCCESS;
}

int Centroid::dfsCoG(image* img, int s, int t)
{
	#if PRINT_MODE == 1
	// cout<<"dfsCoG"<<endl;
	//cout<<"xx "<<xx[s][t]<<" yy "<<yy[s][t]<<endl;
	#endif
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
	//XIW[0] = s*(img->pixel[s][t]-limit);
	//XIW[1] = t*(img->pixel[s][t]-limit);
	XIW[0] = xx[s][t]*(img->pixel[s][t]-limit);
	XIW[1] = yy[s][t]*(img->pixel[s][t]-limit);
	IW = img->pixel[s][t]-limit;
	// Mark source
	flag[s][t] = 1;
	// Begin exploration
	int numNodes = 1;
	while (ind > -1)
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
		neighb[1][0] = s;   //left
		neighb[1][1] = t-1;
		neighb[2][0] = s;   //right
		neighb[2][1] = t+1;
		neighb[3][0] = s+1; //below
		neighb[3][1] = t;
		neighb[4][0] = s-1; //above left
		neighb[4][1] = t-1;
		neighb[5][0] = s-1; //above right
		neighb[5][1] = t+1;
		neighb[6][0] = s+1; //below left
		neighb[6][1] = t-1;
		neighb[7][0] = s+1; //below right
		neighb[7][1] = t+1;
		for (int i = 0; i < 8; i++)
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
			if ((img->pixel[s][t] > limit) && (flag[s][t] == 0))
			{
				// Push node
				ind += 1;
				stack[ind][0] = s;
				stack[ind][1] = t;
				// Store node info to CoG calculation
				//XIW[0] += s*(img->pixel[s][t]-limit);
				//XIW[1] += t*(img->pixel[s][t]-limit);
				XIW[0] += xx[s][t]*(img->pixel[s][t]-limit);
				XIW[1] += yy[s][t]*(img->pixel[s][t]-limit);
				IW += img->pixel[s][t]-limit;
				// Mark node
				numNodes += 1;
				flag[s][t] = 1;
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
	#if PRINT_MODE == 1
	//cout<<"num nodes "<<numNodes<<" X "<<XIW[0]<<" Y "<<XIW[1]<<" I "<<IW<<endl;
	#endif
	// Check the elliptical nature of the patch
	//cout<<"ellipse "<<(double) (xmax-xmin)/(ymax-ymin)<<endl;
	// Check/Compute dimension of the patch
	cent.w = ymax - ymin;
	cent.h = xmax - xmin;
	// Compute CoG of this patch
	cent.x = ((double) XIW[0])/((double) IW);
	cent.y = ((double) XIW[1])/((double) IW);
	cent.intensity = IW;
	
	return SUCCESS;
}

int Centroid::roboMADsub(image* img)
{
	// Step 1: Start by getting the median and MAD as robust proxies for the
	//         mean and standard deviation
	#if PRINT_MODE == 1
	cout<<"ROBOMADsub: histogramMedianSub"<<endl;
	#endif
	
	// Calculate median and verify it has been set
	int ret;
	if ((ret = histogramMedianSub(img)) == FAILURE)
	{
		return FAILURE;
	}
	#if PRINT_MODE == 1
	cout<<"med = "<<med<<endl;
	cout<<"ROBOMADsub: histogramMedianSub2"<<endl;
	#endif
	// Calculate MAD and store as standard deviation
	std = 1.4826*histogramMedianSub2(img); //applies for normally distributed data
	// Check that histogramMedianSub2 was successful (return FAILURE when fails)
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	if (std < 0)
		return FAILURE;
	bool goodimage = false;
	if (std < 0.0000000001) //machine precision
	{
		if (med > 0)
		{
			mn = med;
			return SUCCESS;
		}
		#if PRINT_MODE == 1
		cout<<"we have a good image"<<endl;
		#endif
		goodimage = true;
	}
	
	// Step 2: Identify outliers, recompute mean and std with pixels that remain
	
	#if PRINT_MODE == 1
	cout<<"step 2"<<endl;
	cout<<"exclude outliers 1"<<endl;
	#endif
	unsigned long sum = 0;
	int goodPix = 0;
	if (goodimage)
	{
		// Calculate the mean of the image:
		for (unsigned int i = 0; i < numrowsandcols; i++)
		{
			row = i*dx;
			for (unsigned int j = 0; j < numrowsandcols; j++)
			{
				col = j*dy;
				sum += img->pixel[row][col];
			}
		}
		mn = (double) sum/numrowsandcols/numrowsandcols;
		std = 1; //set to 1 as a kludge
		#if PRINT_MODE == 1
		cout<<"mn = "<<mn<<endl;
		cout<<"std = "<<std<<endl;
		#endif
		return SUCCESS;
	}
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Exclude outliers from the calculation
			if (abs(img->pixel[row][col]-med) < 5*std)
			{
				sum += img->pixel[row][col];
				goodPix++;
			}
		}
	}
	#if PRINT_MODE == 1
	cout<<"done exclude outliers 1"<<endl;
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	if (goodPix == 0)
		return FAILURE;
	mn = (double) sum/goodPix;
	#if PRINT_MODE == 1
	cout<<"mn = "<<mn<<endl;
	cout<<"exclude outliers 2"<<endl;
	#endif
	sum = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++ )
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[row][col]-med) < 5*std)
				sum += pow(img->pixel[row][col]-mn,2);
		}
	}
	#if PRINT_MODE == 1
	cout<<"done exclude outliers 2"<<endl;
	cout<<"sum = "<<sum<<endl;
	#endif
	std = sqrt((double) sum/goodPix);
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	
	// Step 3: Repeat step 2 with new mean and standard deviation values
	
	#if PRINT_MODE == 1
	cout<<"step 3"<<endl;
	cout<<"exclude outliers 1"<<endl;
	#endif
	sum = 0;
	goodPix = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Exclude outliers from the calculation
			if (abs(img->pixel[row][col]-(int) mn) < 5*std)
			{
				sum += img->pixel[row][col];
				goodPix++;
			}
		}
	}
	#if PRINT_MODE == 1
	cout<<"done exclude outliers 1"<<endl;
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	double mn2 = (double) sum/goodPix;
	#if PRINT_MODE == 1
	cout<<"mn = "<<mn<<endl;
	cout<<"exclude outliers 2"<<endl;
	#endif
	sum = 0;
	for (unsigned int i = 0; i < numrowsandcols; i++ )
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[row][col]-(int) mn2) < 5*std)
				sum += pow(img->pixel[row][col]-mn2,2);
		}
	}
	#if PRINT_MODE == 1
	cout<<"done exclude outliers 2"<<endl;
	#endif
	mn = mn2;
	#if PRINT_MODE == 1
	cout<<"sum = "<<sum<<endl;
	#endif
	std = sqrt((double) sum/goodPix);
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	
	return SUCCESS;
}

int Centroid::roboMAD(image* img)
{
	// Step 1: Start by getting the median and MAD as robust proxies for the
	//         mean and standard deviation
	
	#if PRINT_MODE == 1
	cout<<"ROBOMAD: histogramMedian"<<endl;
	#endif
	// Calculate median and verify it has been set
	int ret;
	if ((ret = histogramMedian(img)) == FAILURE)
	{
		return FAILURE;
	}
	#if PRINT_MODE == 1
	cout<<"med = "<<med<<endl;
	cout<<"ROBOMAD: histogramMedian2"<<endl;
	#endif
	// Calculate MAD and store as standard deviation
	std = 1.4826*histogramMedian2(img); //applies for normally distributed data
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	// Check that histogramMedian2 was successful (return FAILURE when fails)
	if (std < 0)
		return FAILURE;
	bool goodimage = false;
	if (std < 0.0000000001) //machine precision
	{
		if (med > 0)
		{
			mn = med;
			return SUCCESS;
		}
		#if PRINT_MODE == 1
		cout<<"we have a good image"<<endl;
		#endif
		goodimage = true;
	}
	
	// Step 2: Identify outliers, recompute mean and std with pixels that remain
	
	#if PRINT_MODE == 1
	cout<<"step 2"<<endl;
	cout<<"refine mean"<<endl;
	#endif
	unsigned long sum = 0;
	int goodPix = 0;
	if (goodimage)
	{
		// Calculate the mean of the image:
		for (int i = 0; i < myData.xlen; i++)
		{
			for (int j = 0; j < myData.ylen; j++)
			{
				sum += img->pixel[i][j];
			}
		}
		mn = (double) sum/myData.xlen/myData.ylen;
		std = 1; //set to 1 as a kludge
		#if PRINT_MODE == 1
		cout<<"mn = "<<mn<<endl;
		cout<<"std = "<<std<<endl;
		#endif
		return SUCCESS;
	}
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Exclude outliers from the calculation
			if (abs(img->pixel[i][j]-med) < 5*std)
			{
				sum += img->pixel[i][j];
				goodPix++;
			}
		}
	}
	#if PRINT_MODE == 1
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	if (goodPix == 0)
		return FAILURE;
	mn = (double) sum/goodPix;
	#if PRINT_MODE == 1
	cout<<"mn = "<<mn<<endl;
	cout<<"refine std"<<endl;
	#endif
	sum = 0;
	for (int i = 0; i < myData.xlen; i++ )
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[i][j]-med) < 5*std)
				sum += pow(img->pixel[i][j]-mn,2);
		}
	}
	#if PRINT_MODE == 1
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	std = sqrt((double) sum/goodPix);
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	
	// Step 3: Repeat step 2 with new mean and standard deviation values
	
	#if PRINT_MODE == 1
	cout<<"step 3"<<endl;
	cout<<"refine mean"<<endl;
	#endif
	sum = 0;
	goodPix = 0;
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Exclude outliers from the calculation
			if (abs(img->pixel[i][j]-(int) mn) < 5*std)
			{
				sum += img->pixel[i][j];
				goodPix++;
			}
		}
	}
	#if PRINT_MODE == 1
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	double mn2 = (double) sum/goodPix;
	#if PRINT_MODE == 1
	cout<<"mn = "<<mn2<<endl;
	cout<<"refine std"<<endl;
	#endif
	sum = 0;
	for (int i = 0; i < myData.xlen; i++ )
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			// Number of good pixels will be the same as last time
			if (abs(img->pixel[i][j]-(int) mn) < 5*std)
				sum += pow(img->pixel[i][j]-mn,2);
		}
	}
	mn = mn2;
	#if PRINT_MODE == 1
	cout<<"sum = "<<sum<<endl;
	cout<<"goodPix = "<<goodPix<<endl;
	#endif
	std = sqrt((double) sum/goodPix);
	#if PRINT_MODE == 1
	cout<<"std = "<<std<<endl;
	#endif
	
	return SUCCESS;
}

int Centroid::histogramMedianSub(image* img)
{
	// Populate histogram
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			medhist[img->pixel[row][col]]++;
		}
	}
	// Find median
	#if PRINT_MODE == 1
	//for (int i = 0; i < levels; i++)
	//{
	//	if (medhist[i] > 0)
	//		cout << i << ": " << medhist[i] << endl;
	//}
	#endif
	counts = (int) myData.numpixelsinsubsample/2;
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
		{
			med = i;
			return med;
		}
	}
	#if PRINT_MODE == 1
	cout << "counts = " << counts << endl;
	#endif
	return FAILURE;
}

int Centroid::histogramMedianSub2(image* img)
{
	// Populate histogram (assumes median has already been calculated)
	for (unsigned int i = 0; i < numrowsandcols; i++)
	{
		row = i*dx;
		for (unsigned int j = 0; j < numrowsandcols; j++)
		{
			col = j*dy;
			medhist2[abs(img->pixel[row][col]-med)]++;
		}
	}
	// Find median, which corresponds to the Median Absolute Deviation
	counts = (int) myData.numpixelsinsubsample/2;
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist2[i];
		if (counts < 0)
			return i;
	}
	#if PRINT_MODE == 1
	cout << "counts = " << counts << endl;
	#endif
	return FAILURE;
}

int Centroid::histogramMedian(image* img)
{
	// Populate histogram
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			medhist[img->pixel[i][j]]++;
		}
	}
	// Find median
	#if PRINT_MODE == 1
	//for (int i = 0; i < levels; i++)
	//{
	//	if (medhist[i] > 0)
	//		cout << i << ": " << medhist[i] << endl;
	//}
	#endif
	counts = (int) (img->xlen)*(img->ylen)/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist[i];
		if (counts < 0)
		{
			med = i;
			return med;
		}
	}
	#if PRINT_MODE == 1
	cout << "counts = " << counts << endl;
	#endif
	return FAILURE;
}

int Centroid::histogramMedian2(image* img)
{
	// Populate histogram (assumes median has already been calculated)
	for (int i = 0; i < myData.xlen; i++)
	{
		for (int j = 0; j < myData.ylen; j++)
		{
			medhist2[abs(img->pixel[i][j]-med)]++;
		}
	}
	// Find median, which corresponds to the Median Absolute Deviation
	#if PRINT_MODE == 1
	//cout << "MAD histogram:" << endl;
	//for (int i = 0; i < levels; i++)
	//{
	//	if (medhist2[i] > 0)
	//		cout << i << ": " << medhist2[i] << endl;
	//}
	#endif
	counts = (int) (img->xlen)*(img->ylen)/2; //number of counts to median value
	for (int i = 0; i < levels; i++)
	{
		counts -= medhist2[i];
		if (counts < 0)
			return i;
	}
	#if PRINT_MODE == 1
	cout << "counts = " << counts << endl;
	#endif
	return FAILURE;
}

void Centroid::bubbleSort()
{
	int n = myList.numCentroids;
	int newn;
	while (n > 0)
	{
		newn = 0;
		for (int i = 1; i < n; i++)
		{
			if (myList.centroid[i-1].intensity < myList.centroid[i].intensity)
			{
				// Swap using cent as swap space
				cent.x = myList.centroid[i-1].x;
				cent.y = myList.centroid[i-1].y;
				cent.intensity = myList.centroid[i-1].intensity;
				cent.w = myList.centroid[i-1].w;
				cent.h = myList.centroid[i-1].h;
				myList.centroid[i-1].x = myList.centroid[i].x;
				myList.centroid[i-1].y = myList.centroid[i].y;
				myList.centroid[i-1].intensity = myList.centroid[i].intensity;
				myList.centroid[i-1].w = myList.centroid[i].w;
				myList.centroid[i-1].h = myList.centroid[i].h;
				myList.centroid[i].x = cent.x;
				myList.centroid[i].y = cent.y;
				myList.centroid[i].intensity = cent.intensity;
				myList.centroid[i].w = cent.w;
				myList.centroid[i].h = cent.h;
				// Set max bound
				newn = i;
			}
		}
		n = newn;
	}
}
