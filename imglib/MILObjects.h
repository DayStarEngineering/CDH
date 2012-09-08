// MILObjects.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef MILOBJECTS_H     // Prevent duplicate definition
#define MILOBJECTS_H

//Include:
#include <mil.h>
#include "MILWrapper.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/*
 * About: Builds a MIL objects for use with an MILWrapper Object such as image buffer
 *        digitizers, displays, and lookup tables.
 *
*/

using namespace std;

// Digitizer class:
class MILDigitizer
{
	public:
	MILDigitizer();
	~MILDigitizer();
	int create(MIL_ID systemID, const char* DCFfilename, int digNum = M_DEFAULT);
	MIL_ID ID;
};

// Digitizer2 class: (2 digitizers for two sensor halves)
class MILDigitizer2
{
	public:
	MILDigitizer2();
	~MILDigitizer2();
	int create(MIL_ID systemID, const char* DCFfilename1, const char* DCFfilename2, int digNum1 = M_DEFAULT, int digNum2 = 1);
	MIL_ID ID[2];
};

// Display class:
class MILDisplay
{
	public:
	MILDisplay();
	~MILDisplay();
	int create(MIL_ID systemID);
	MIL_ID ID;
};

// Image class:
class MILImage
{
	public:
	MILImage();
	~MILImage();
	int create(MIL_ID systemID, unsigned short xlen, unsigned short ylen);
	MIL_ID ID;
};

// Image2 class: (2 children buffers)
class MILImage2
{
	public:
	MILImage2();
	~MILImage2();
	int create(MIL_ID systemID, unsigned short xlen, unsigned short ylen);
	MIL_ID ID;
	MIL_ID childID[2];
};

// Float (32-bit) Look-up table class:
class MILFloatLut
{
	public:
	MILFloatLut();
	~MILFloatLut();
	int create(MIL_ID systemID, unsigned short xlen, unsigned short ylen);
	MIL_ID ID;
};

// Binary Look-up table class:
class MILBinArray
{
	public:
	MILBinArray();
	~MILBinArray();
	int create(MIL_ID systemID, unsigned short xlen, unsigned short ylen);
	MIL_ID ID;
};

#endif
