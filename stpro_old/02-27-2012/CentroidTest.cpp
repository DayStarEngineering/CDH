#include "Centroid.h"
#include <iostream>
#include <fstream>

using namespace std;

int getImage(const char* file, image* img);

int main()
{
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
	Logger myLogger("CentroidTest");
	Centroid myCentroid;
	centroidData myData;
	if (myCentroid.configure(myData, &myLogger) == -1)
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
	
	return 0;
}

int getImage(const char* file, image* img)
{
	ifstream stream(file);
	
	if (!stream) //not open
	{
		cout << "Error encountered while opening file." << endl;
		return -1;
	}
	// Populate image
	for (int i = 0; i < img->xlen; i++)
	{
		for (int j = 0; j < img->ylen; j++)
		{
			if (stream.eof())
			{
				cout << "Invalid number of expected pixels." << endl;
				return -1;
			}
			stream >> img->pixel[i][j].val;
		}
	}
	return 0;
}
