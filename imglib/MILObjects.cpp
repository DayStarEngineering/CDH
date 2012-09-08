#include "MILObjects.h"

// Digitizer class:
MILDigitizer::MILDigitizer()
{
	ID = M_NULL;
}

MILDigitizer::~MILDigitizer()
{
	if(ID != M_NULL)
	{
		MdigFree(ID);
		ID = M_NULL;
	}
}

int MILDigitizer::create(MIL_ID systemID, const char* DCFfilename, int digNum)
{ 
	// Allocate Digitizer
	if( MdigAlloc(systemID, digNum, MIL_TEXT(DCFfilename) /*MIL_TEXT("M_DEFAULT")*/, M_DEFAULT, &ID) == M_NULL )
	   		return -1;
	   	
	MdigControl(ID,M_GRAB_TIMEOUT,100); // default is infinite... value > 0 is wait time in msec
									 
	return 0;
}

// Digitizer class:
MILDigitizer2::MILDigitizer2()
{
	ID[0] = M_NULL;
	ID[1] = M_NULL;
}

MILDigitizer2::~MILDigitizer2()
{
	if(ID[0] != M_NULL)
	{
		MdigFree(ID[0]);
		ID[0] = M_NULL;
	}
	
	if(ID[1] != M_NULL)
	{
		MdigFree(ID[1]);
		ID[1] = M_NULL;
	}
}

int MILDigitizer2::create(MIL_ID systemID, const char* DCFfilename1, const char* DCFfilename2, int digNum1, int digNum2)
{ 
	// Allocate Digitizers
	if( MdigAlloc(systemID, digNum1, MIL_TEXT(DCFfilename1) /*MIL_TEXT("M_DEFAULT")*/, M_DEFAULT, &ID[0]) == M_NULL )
	   		return -1;
	   		
	if( MdigAlloc(systemID, digNum2, MIL_TEXT(DCFfilename2) /*MIL_TEXT("M_DEFAULT")*/, M_DEFAULT, &ID[1]) == M_NULL )
	   		return -1;
	   	
	MdigControl(ID[0],M_GRAB_TIMEOUT,100); // default is infinite... value > 0 is wait time in msec
	MdigControl(ID[1],M_GRAB_TIMEOUT,100); // default is infinite... value > 0 is wait time in msec 
	// MdigControl(ID[0],M_GRAB_MODE,M_ASYNCHRONOUS);
	// MdigControl(ID[1],M_GRAB_MODE,M_ASYNCHRONOUS);
	return 0;
}

// Display class:
MILDisplay::MILDisplay()
{
	ID = M_NULL;
}

MILDisplay::~MILDisplay()
{
	if(ID != M_NULL)
	{
		MdispFree(ID);
		ID = M_NULL;
	}
}

int MILDisplay::create(MIL_ID systemID)
{ 
	// Allocate display:
	if( MdispAlloc(systemID, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &ID) == M_NULL )
   		 	return -1;
   		 
	 // Display can only handle 8 bit resolution.. Map our 11 bits to 8 bits:
	 scaleDisp(ID, 11);
	 // autoscaleDisp(ID);
									 
	return 0;
}

// Image class:
MILImage::MILImage()
{
	ID = M_NULL;
}

MILImage::~MILImage()
{
	if(ID != M_NULL)
	{
		MbufFree(ID);
		ID = M_NULL;
	}
}

int MILImage::create(MIL_ID systemID, unsigned short xlen, unsigned short ylen)
{ 
	// Allocate image buffer:
	if( MbufAlloc2d(                           systemID, 
					                               xlen, 
					                               ylen, 
					                    16 + M_UNSIGNED, 
					 M_IMAGE + M_DISP + M_PROC + M_GRAB, 
					                               &ID) 
														 == M_NULL )
	{
		return -1;
	}				
	
	// Clear image:
	if(clearImg(ID) != 0)
		return -1;
									 
	return 0;
}

// Image2 class:
MILImage2::MILImage2()
{
	ID = M_NULL;
	childID[0] = M_NULL;
	childID[1] = M_NULL;
}

MILImage2::~MILImage2()
{
	if(childID[0] != M_NULL)
	{
		MbufFree(childID[0]);
		childID[0] = M_NULL;
	}
	
	if(childID[1] != M_NULL)
	{
		MbufFree(childID[1]);
		childID[1] = M_NULL;
	}
	
	if(ID != M_NULL)
	{
		MbufFree(ID);
		ID = M_NULL;
	}
}

int MILImage2::create(MIL_ID systemID, unsigned short xlen, unsigned short ylen)
{ 
	// Allocate image buffer:
	if( MbufAlloc2d(                           systemID, 
					                               xlen, 
					                               ylen, 
					                    16 + M_UNSIGNED, 
					 M_IMAGE + M_DISP + M_PROC + M_GRAB, 
					                               &ID) 
														 == M_NULL )
	{
		return -1;
	}				
	
	// Clear image:
	if(clearImg(ID) != 0)
		return -1;
		
	// Allocate child buffers:
	if( getChildImg(ID, 0, 0, xlen, ylen/2, childID[0]) == -1)
	{
		return -1;
	}

	if( getChildImg(ID, 0, ylen/2, xlen, ylen/2, childID[1]) == -1)
	{
		return -1;
	}

	return 0;
}

// Lookup table class:
MILFloatLut::MILFloatLut()
{
	ID = M_NULL;
}

MILFloatLut::~MILFloatLut()
{
	if(ID != M_NULL)
	{
		MbufFree(ID);
		ID = M_NULL;
	}
}

int MILFloatLut::create(MIL_ID systemID, unsigned short xlen, unsigned short ylen)
{ 
	// Allocate lut buffer:
	if( MbufAlloc2d(                           systemID, 
					                               xlen, 
					                               ylen, 
					                       32 + M_FLOAT, 
					 							  M_LUT, 
					                               &ID) 
														 == M_NULL )
	{
		return -1;
	}				
	
	// Clear image:
	if(clearImg(ID) != 0)
		return -1;
		
	return 0;
}

// Binary look-up table class:
MILBinArray::MILBinArray()
{
	ID = M_NULL;
}

MILBinArray::~MILBinArray()
{
	if(ID != M_NULL)
	{
		MbufFree(ID);
		ID = M_NULL;
	}
}

int MILBinArray::create(MIL_ID systemID, unsigned short xlen, unsigned short ylen)
{ 
	// Allocate lut buffer:
	if( MbufAlloc2d(                           systemID, 
					                               xlen, 
					                               ylen, 
					                     1 + M_UNSIGNED, 
					 							M_ARRAY, 
					                               &ID) 
														 == M_NULL )
	{
		return -1;
	}				
	
	// Clear image:
	if(clearImg(ID) != 0)
		return -1;
		
	return 0;
}
