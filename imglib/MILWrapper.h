// MILWrapper.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef MILWRAPPER_H     // Prevent duplicate definition
#define MILWRAPPER_H

//Include:
#include <mil.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include "../cdhlib/Logger.h"
#include "../stlib/StartrackerData.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*
 * About: Builds a single MIL Application with a single system for the DayStar Solios Board.
 *
*/

// Defines:

using namespace std;

class MILWrapper
{
    public:
	// Constructor:
	MILWrapper();

	// Deconstructor:
	~MILWrapper();
	
	// Configuration:
	int create(Logger* theLogger = NULL);
    
    // Declare MIL Application IDs:
    MIL_ID  AppID,           /* Application identifier.                */
            SysID;           /*   --> System identifier.               */
                             /*   (Implemented in MILObjects.h)        */
   	//	    DigID,           /*         --> Digitizer identifier.      */
   	//	    DspID;           /*         --> Display identifier.        */
    //      ImgID;           /*         --> Image buffer identifier.   */
};

///////////////////////////////////////////////////
// Static Functions:
///////////////////////////////////////////////////

// Digitizer Manipulation:
int digGrab(MIL_ID dig, MIL_ID img);
int digGrab2(MIL_ID dig1, MIL_ID dig2, MIL_ID img1, MIL_ID img2);
int digGrabContinuous(MIL_ID dig, MIL_ID img);
int digGrabHalt(MIL_ID dig);
int digSetDataChannel(MIL_ID dig, int channel);
int digSetSyncChannel(MIL_ID dig, int channel);
int getImgSize(MIL_ID dig, unsigned int &xlen, unsigned int &ylen);

// Image Manipulation:
int getChildImg(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, MIL_ID &child);
int clearImg(MIL_ID img, int value = 0);
int saveImg(MIL_ID img, const char* fname);
int saveImg(MIL_ID img, string fname);
int saveImgTIFF(MIL_ID img, const char* fname);
int saveImgTIFF(MIL_ID img, string fname);
int convert11to16bitres(MIL_ID img);
int saveVid(const MIL_ID* imgs, int numFrames, double frameRate, const char* fname);
int saveVid(const MIL_ID* imgs, int numFrames, double frameRate, string fname);
int getImgSize(const char* fname, unsigned int &xlen, unsigned int &ylen);
int getImgSize(string fname, unsigned int &xlen, unsigned int &ylen); 
int loadImg(MIL_ID img, const char* fname);
int loadImg(MIL_ID img, string fname);
int loadImgTEXT(image* img, const char* fname);
int loadImgTEXT(image* img, string fname);
int loadVid(MIL_ID* imgs, MIL_ID sys, int& numFrames, double& frameRate, const char* fname);
int loadVid(MIL_ID* imgs, MIL_ID sys, int& numFrames, double& frameRate, string fname);
int copyImg(MIL_ID imgSrc, MIL_ID imgDest);
int copyImg(MIL_ID imgSrc, image* imgDest);
int copyImg(image* imgSrc, MIL_ID imgDest);
int printImg(image* img);
int printImg(MIL_ID img, unsigned int xlen, unsigned int ylen);
int drawCircle(MIL_ID img, double XCenter, double YCenter, double XRad, double YRad);

// Pixel Manipulation
int putPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, unsigned short* array);
int putPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, float* array);
int putPixels1D(MIL_ID img, int OffX, int SizeX, unsigned short* array);
int putPixels1D(MIL_ID img, int OffX, int SizeX, float* array);
int putPixel(MIL_ID img, int OffX, int OffY, unsigned short* val);
int putPixel(MIL_ID img, int OffX, int OffY, float* val);
int getPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, unsigned short* array);
int getPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, float* array);
int getPixels1D(MIL_ID img, int OffX, int SizeX, unsigned short* array);
int getPixels1D(MIL_ID img, int OffX, int SizeX, float* array);
int getPixel(MIL_ID img, int OffX, int OffY, unsigned short* val);
int getPixel(MIL_ID img, int OffX, int OffY, float* val);

// Display Manipulation:
int scaleDisp(MIL_ID disp, int bitRes);
int autoscaleDisp(MIL_ID disp);
int dispImg(MIL_ID disp, MIL_ID img);
int dispVid(MIL_ID disp, const MIL_ID* imgs, int numFrames, double frameRate);
int clearDisp(MIL_ID disp);

// Error Manipulation:
int getError();

// MIL Application Hook Handler ( Configured to recieve errors from MappError() )
MIL_INT MFTYPE ErrorHandler(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserStructPtr); 
	
#endif
