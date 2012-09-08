#include "MILWrapper.h"

// Constructor:
MILWrapper::MILWrapper()
{  
   // Innitialize Variables:
   AppID = M_NULL;
   SysID = M_NULL;
}

// Deconstructor:
MILWrapper::~MILWrapper()
{  	
	// Free System:
	if(SysID != M_NULL)
	{ 
		MsysFree(SysID);
		SysID = M_NULL;
   	}
   	
	// Free Application:
	// This MUST be called in the same thread in which it was allocated.
	// This MUST be the ABSOLUTE LAST MIL Call in the program's execution.
	if(AppID != M_NULL)
	{
		MappFree(AppID);
		AppID = M_NULL;
	}
}

// Configuration:
int MILWrapper::create(Logger* theLogger)
{
	// Allocate MIL Application, must be allocated prior to using any other MIL functions:
	if( MappAlloc(M_DEFAULT, &AppID) == M_NULL )
	   	return -1;
	  
	// Disable MIL GUI Error messages: ( we will check for them with our handler ):
    MappControl(M_ERROR, M_PRINT_DISABLE);
   
	// Ensures that any MIL errors are caught by handler:
	MappHookFunction(M_ERROR_CURRENT /*+ M_THREAD_CURRENT*/, ErrorHandler, (void*)theLogger);
	
	// Allocate MIL System, must be allocated before allocating digitizers, buffers, or displays:
    if( MsysAlloc(M_SYSTEM_SOLIOS /*M_SYSTEM_HOST*/, M_DEFAULT, M_DEFAULT, &SysID) == M_NULL )
    	return -1;
	
	return 0;
}

///////////////////////////////////////////////////
// Static Functions:
///////////////////////////////////////////////////

// Digitizer Functions:
int digGrab(MIL_ID dig, MIL_ID img)
{
	MdigGrab(dig, img);
	return getError();
}

int digGrab2(MIL_ID dig1, MIL_ID dig2, MIL_ID img1, MIL_ID img2)
{
	MdigGrab(dig1, img1);
	// MdigControl(dig2,M_SYNCHRONIZE_ON_STARTED,dig1); 
	MdigGrab(dig2, img2);
	return getError();
}
  
int digGrabContinuous(MIL_ID dig, MIL_ID img)
{
	MdigGrabContinuous(dig, img);
	return getError();
}

int digGrabHalt(MIL_ID dig)
{
	MdigHalt(dig);
	return getError();
}

int getImgSize(MIL_ID dig, unsigned int &xlen, unsigned int &ylen)
{
	xlen = MdigInquire(dig, M_SIZE_X, M_NULL);
	ylen = MdigInquire(dig, M_SIZE_Y, M_NULL);
	return getError();
}

int digSetDataChannel(MIL_ID dig, int channel)
{
	MIL_INT64 Channel;
	switch(channel)
	{
		case 0:
			Channel = M_CH0;
			break;
		case 1:
			Channel = M_CH1;
			break;
		case 2:
			Channel = M_CH2;
			break;
		case 3:
			Channel = M_CH3;
			break;
		case 4:
			Channel = M_CH4;
			break;
		default:
			return -1;
	}
	MdigChannel(dig, Channel);
	return getError();
}

int digSetSyncChannel(MIL_ID dig, int channel)
{
	MIL_INT64 Channel;
	switch(channel)
	{
		case 0:
			Channel = M_CH0;
			break;
		case 1:
			Channel = M_CH1;
			break;
		case 2:
			Channel = M_CH2;
			break;
		case 3:
			Channel = M_CH3;
			break;
		case 4:
			Channel = M_CH4;
			break;
		default:
			return -1;
	}
	MdigChannel(dig, Channel + M_SYNC);
	return getError();
}

// Image Functions:
int getChildImg(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, MIL_ID &child)
{
  	MbufChild2d(img, OffX, OffY, SizeX, SizeY, &child);
	return getError();
}

int clearImg(MIL_ID img, int value)
{
	 MbufClear(img, value);
	 return getError();
}

int saveImg(MIL_ID img, const char* fname)
{
	MbufExport(fname, M_RAW, img);
	return getError();
}

int saveImg(MIL_ID img, string fname)
{
	MbufExport(fname.c_str(), M_RAW, img);
	return getError();
}

int saveImgTIFF(MIL_ID img, const char* fname)
{	
	MbufExport(fname, M_TIFF, img);
	return getError();
}

int saveImgTIFF(MIL_ID img, string fname)
{
	MbufExport(fname.c_str(), M_TIFF, img);
	return getError();
}

int convert11to16bitres(MIL_ID img)
{
	MimArith(img,32,img,M_MULT_CONST);
	return getError();
}

int saveVid(const MIL_ID* imgs, int numFrames, double frameRate, const char* fname)
{
	MbufExportSequence(fname, M_DEFAULT, imgs, numFrames, frameRate, M_DEFAULT);
	return getError();
}

int saveVid(const MIL_ID* imgs, int numFrames, double frameRate, string fname)
{
	MbufExportSequence(fname.c_str(), M_DEFAULT, imgs, numFrames, frameRate, M_DEFAULT);
	return getError();
}

int getImgSize(const char* fname, unsigned int &xlen, unsigned int &ylen)
{
	xlen = MbufDiskInquire(fname, M_SIZE_X, M_NULL);
	ylen = MbufDiskInquire(fname, M_SIZE_Y, M_NULL);
	return getError();
}

int getImgSize(string fname, unsigned int &xlen, unsigned int &ylen)
{
	return getImgSize(fname.c_str(),xlen,ylen);
}

int loadImg(MIL_ID img, const char* fname)
{
	MbufLoad(fname, img);
	return getError();
}

int loadImg(MIL_ID img, string fname)
{
	MbufLoad(fname.c_str(), img);
	return getError();
}

int loadImgTEXT(image* img, const char* fname)
{	
	unsigned short temp;
	
	// Open stream;
	ifstream stream(fname);
	if (!stream) { return -1; }
	if (img == NULL) { return -1; }
	
	// Populate image
	for (unsigned int i = 0; i < img->xlen; i++)
	{
		for (unsigned int j = 0; j < img->ylen; j++)
		{
			// Check for EOF:
			if (stream.eof()){ return -1; }

			// Copy over stream value:
			stream >> temp;
			img->pixel[i][j] = temp;
		}
	}
	
	stream.close();
	
	return 0;
}

int loadImgTEXT(image* img, string fname)
{	
	return loadImgTEXT(img, fname.c_str());
}

int loadVid(MIL_ID* imgs, MIL_ID sys, int& numFrames, double& frameRate, const char* fname)
{
	MbufDiskInquire(fname, M_NUMBER_OF_IMAGES, &numFrames);
	MbufDiskInquire(fname, M_FRAME_RATE, &frameRate);
	MbufImportSequence(fname, M_DEFAULT, M_RESTORE, sys, imgs, 0, numFrames, M_DEFAULT);
	return getError();
}

int loadVid(MIL_ID* imgs, MIL_ID sys, int& numFrames, double& frameRate, string fname)
{
	return loadVid(imgs,sys,numFrames,frameRate,fname.c_str());
}

int copyImg(MIL_ID imgSrc, MIL_ID imgDest)
{
	MbufCopy(imgSrc, imgDest);
	return getError();
}


int copyImg(MIL_ID imgSrc, image* imgDest)
{
	for( unsigned int i = 0; i < imgDest->xlen; i++ )
	{
		if( getPixels2D(imgSrc, (int) i, 0, 1, (int) imgDest->ylen, (unsigned short*) imgDest->pixel[i]) == -1 )
			return -1;
	}
	
	return 0;
}

int copyImg(image* imgSrc, MIL_ID imgDest)
{
	for( unsigned int i = 0; i < imgSrc->xlen; i++ )
	{
		if( putPixels2D(imgDest, (int) i, 0, 1, (int) imgSrc->ylen, (unsigned short*) imgSrc->pixel[i]) == -1 )
			return -1;
	}
	
	return 0;
}

int printImg(image* img)
{
	for (unsigned int i = 0; i < img->xlen; i++)
	{
		for (unsigned int j = 0; j < img->ylen; j++)
		{
			cout <<  setfill('0') << setw(2) << img->pixel[i][j] << " ";
		}
		cout << endl;
	}
	
	return 0;
}

int printImg(MIL_ID img, unsigned int xlen, unsigned int ylen)
{
	
	unsigned short val;
	for (unsigned int i = 0; i < xlen; i++)
	{
		for (unsigned int j = 0; j < ylen; j++)
		{
			if( getPixel(img, i, j, &val) == -1)
				return -1;
				
			cout << setfill('0') << setw(2) << val << " ";
		}
		cout << endl;
	}
	
	return 0;
}

int drawCircle(MIL_ID img, double XCenter, double YCenter, double XRad, double YRad)
{
	MgraArc(M_DEFAULT, img, XCenter, YCenter, XRad, YRad, 0, 360);
	return getError();
}

// Pixel Functions:
int putPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, unsigned short* array)
{ 
    MbufPut2d(img,OffX,OffY,SizeX,SizeY,array);
	return getError();
}

int putPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, float* array)
{ 
    MbufPut2d(img,OffX,OffY,SizeX,SizeY,array);
	return getError();
}

int putPixels1D(MIL_ID img, int OffX, int SizeX, unsigned short* array)
{ 
    MbufPut1d(img,OffX,SizeX,array);
	return getError();
}

int putPixels1D(MIL_ID img, int OffX, int SizeX, float* array)
{ 
    MbufPut1d(img,OffX,SizeX,array);
	return getError();
}

int putPixel(MIL_ID img, int OffX, int OffY, unsigned short* val)
{ 
    return putPixels2D( img, OffX, OffY, 1, 1, (unsigned short*) val);
}

int putPixel(MIL_ID img, int OffX, int OffY, float* val)
{ 
    return putPixels2D( img, OffX, OffY, 1, 1, (float*) val);
}

int getPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, unsigned short* array)
{ 
    MbufGet2d(img,OffX,OffY,SizeX,SizeY,array);
	return getError();
}

int getPixels2D(MIL_ID img, int OffX, int OffY, int SizeX, int SizeY, float* array)
{ 
    MbufGet2d(img,OffX,OffY,SizeX,SizeY,array);
	return getError();
}

int getPixels1D(MIL_ID img, int OffX, int SizeX, unsigned short* array)
{ 
    MbufGet1d(img,OffX,SizeX,array);
	return getError();
}

int getPixels1D(MIL_ID img, int OffX, int SizeX, float* array)
{ 
    MbufGet1d(img,OffX,SizeX,array);
	return getError();
}

int getPixel(MIL_ID img, int OffX, int OffY, unsigned short* val)
{ 
    return getPixels2D( img, OffX, OffY, 1, 1, (unsigned short*) val);
}

int getPixel(MIL_ID img, int OffX, int OffY, float* val)
{ 
    return getPixels2D( img, OffX, OffY, 1, 1, (float*) val);
}

// Display Functions:
int autoscaleDisp(MIL_ID disp)
{
	 MdispControl(disp,M_VIEW_MODE,M_AUTO_SCALE);
	 return getError();
}

int scaleDisp(MIL_ID disp, int bitRes)
{
	MdispControl(disp,M_VIEW_BIT_SHIFT,bitRes - 8);
	MdispControl(disp,M_VIEW_MODE,M_BIT_SHIFT);
	return getError();
}

int dispImg(MIL_ID disp, MIL_ID img)
{
	 MdispSelect(disp, img);
	 return getError();
}

int dispVid(MIL_ID disp, const MIL_ID* imgs, int numFrames, double frameRate)
{
	// Convert framerate to sleeptime in us:
	useconds_t uSleepTime = (useconds_t) ( ( 1.0 / frameRate ) * 1000000 );
	
	for( int i = 0; i < numFrames; i++ )
	{
		// Display Image:
		if( dispImg(disp, imgs[i]) == -1 )
		{
			return -1;
		}
		
		// Take a nap:
		usleep(uSleepTime);
	}
	
	return 0;
}

int clearDisp(MIL_ID disp)
{
	 MdispSelect(disp, M_NULL);
	 return getError();
}

// Error handler for a function call basis by each thread:
int getError()
{
	if(MappGetError(M_CURRENT + M_THREAD_CURRENT, M_NULL) == M_NULL_ERROR)
		return 0;
	else
		return -1;
}

// Global Error Handler and Logger:
MIL_INT MFTYPE ErrorHandler(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserStructPtr)
{
	// Ignore unused inputs:
	(void) HookType; (void) EventId;
	
	// Global vars:
	Logger* logger = (Logger*) UserStructPtr;
	
	// Local Vars:
	MIL_TEXT_CHAR errorStr[M_ERROR_MESSAGE_SIZE];
	MIL_INT numErrors = -1;
	string errMsg = "";
	
	// Get error function name:
	if(MappGetHookInfo(EventId,M_MESSAGE + M_CURRENT_FCT,errorStr))
	{
		errMsg += "[Unable to retrieve function name.]";
	}
	else
	{
		errMsg += errorStr;
		errMsg += "(): ";
	}
	
	// Get number of errors:
	if(MappGetHookInfo(EventId,M_CURRENT_SUB_NB,&numErrors))
	{
		errMsg += "[Unable to retrieve number of error messages.]";
	}
	
	// Fill error string:
	if(numErrors >= 0)
	{
		if(MappGetHookInfo(EventId,M_CURRENT + M_MESSAGE,errorStr))
		{
			errMsg += "(0) Retrieving error message failed. ";
		}
		else
		{
			errMsg += "(0) "; errMsg += errorStr; errMsg += " ";
		}
	}
	
	if(numErrors >= 1)
	{
		if(MappGetHookInfo(EventId,M_CURRENT_SUB_1 + M_MESSAGE,errorStr))
		{
			errMsg += "(1) Retrieving error message failed ";
		}
		else
		{
			errMsg += "(1) "; errMsg += errorStr; errMsg += " ";
		}
	}
	
	if(numErrors >= 2)
	{
		if(MappGetHookInfo(EventId,M_CURRENT_SUB_2 + M_MESSAGE,errorStr))
		{
			errMsg += "(2) Retrieving error message failed ";
		}
		else
		{
			errMsg += "(2) "; errMsg += errorStr; errMsg += " ";
		}
	}
	
	if(numErrors >= 3)
	{
		if(MappGetHookInfo(EventId,M_CURRENT_SUB_3 + M_MESSAGE,errorStr))
		{
			errMsg += "(3) Retrieving error message failed ";
		}
		else
		{
			errMsg += "(3) "; errMsg += errorStr; errMsg += " ";
		}
	}
	
	if(logger != NULL)
		logger->lw(ERROR,"MIL: Error in %s",errMsg.c_str());
	else
		printf("MIL: Error in %s\n",errMsg.c_str());
	
	return 0;
}
