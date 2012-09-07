#include "Centroid.h"
#include <iostream>
#include <fstream>

using namespace std;

int getImage(const char* file, image* img);

Centroid myCentroid;

int main()
{
	/*
	// Allocate image object memory
	image* img = new image;
	if (img->create(360,360,0,0) == -1)
	{
		cout << "Failure making image object." << endl;
		exit(-1);
	}
	// Load the image
	if (getImage("../../dev/data/image_47819_5597.txt",img) == -1)
	{
		cout << "Failure populating image." << endl;
		exit(-1);
	}
	// Allocate centroid list object memory
	centroidList* cntrd = new centroidList;
	if (cntrd->create(100) == -1)
	{
		cout << "Failure making centroid list object." << endl;
		exit(-1);
	}
	// Make the logger and configure centroid
	//Logger myLogger("CentroidTest");
	Centroid myCentroid;
	centroidData myData;
	if (myCentroid.configure(myData) == -1)
	{
		cout << "Failure configuring centroid." << endl;
		exit(-1);
	}
	// Do work!
	if (myCentroid.run(img, cntrd) == -1)
	{
		cout << "Failure running algorithms." << endl;
		exit(-1);
	}
	// Display results
	cout<<"found "<<cntrd->numCentroids<<" centroids:"<<endl;
	for (int i = 0; i < cntrd->numCentroids; i++)
	{
		cout<<i+1<<") "<<cntrd->centroid[i].x<<" "<<cntrd->centroid[i].y;
		cout<<" "<<cntrd->centroid[i].intensity<<endl;
	}
	// De-allocate image object memory
	delete img;
	// De-allocate centroid list object
	delete cntrd;
	*/
	
	// Make and configure centroid:
	centroidData myData;
	myData.fovX                 = 0.125112182;
	myData.fovY                 = 0.105564494;
	myData.numsigma  		  	= 2.5;
	myData.numpixelsinsubsample = 50000;
	myData.minthresh 		    = 9;
	myData.maxthresh 		    = 100;
	myData.maxstars             = 100;
	myData.maxstars2return		= 32;
	myData.xlen                 = 2560;
	myData.ylen                 = 2160;
	myData.bitres   		    = 11;
	
	if (myCentroid.configure(myData) != SUCCESS)
	{
		cout << "TEST: Failure configuring centroid." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Centroid configured." << endl;
	}
	
	// Load the image:
	image* img = new image;
	if (img->create(myData.xlen,myData.ylen) != 0)
	{
		cout << "TEST: Failure creating image object." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Image object created." << endl;
	}
	
	if (getImage("../test_images/big_image.txt",img) != SUCCESS)
	{
		cout << "TEST: Failure populating image." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Image populated." << endl;
	}
	
	// Allocate centroid list object memory:
	centroidList* cntrd = new centroidList;
	if (cntrd->create(32) == -1)
	{
		cout << "TEST: Failure making centroid list object." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Centroid list object created." << endl;
	}
	
	// Reset centroid:
	// THIS IS TECHNICALLY DONE IN CONFIGURE()
	if (myCentroid.resetFlags() != SUCCESS)
	{
		cout << "TEST: Failure resetting flags." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Flags reset." << endl;
	}
	
	// Process the image:
	if (myCentroid.run(img, cntrd) != SUCCESS)
	{
		cout << "TEST: Failure processing image." << endl;
		exit(-1);
	}
	else
	{
		cout << "TEST: Image processed." << endl;
	}
	
	// Print out the centroids found:
	cout << "TEST: Number of centroids: " << cntrd->numCentroids << endl;
	for (int i = 0; i < cntrd->numCentroids; i++)
	{
		cout << cntrd->centroid[i].x << " " << cntrd->centroid[i].y << " ";
		cout << cntrd->centroid[i].intensity << endl;
	}
	
	return SUCCESS;
}

int getImage(const char* file, image* img)
{
	ifstream stream(file);
	
	if (!stream) //not open
	{
		cout << "Error encountered while opening file." << endl;
		return FAILURE;
	}
	// Populate image
	for (unsigned int i = 0; i < img->xlen; i++)
	{
		for (unsigned int j = 0; j < img->ylen; j++)
		{
			if (stream.eof())
			{
				cout << "Invalid number of expected pixels:" << endl;
				cout << "i = " << i << ", j = " << j << endl;
				return FAILURE;
			}
			stream >> img->pixel[i][j];
		}
	}
	return SUCCESS;
}

