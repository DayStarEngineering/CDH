// grey2bin.h
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef GREY2BIN_H     // Prevent duplicate definition
#define GREY2BIN_H

#include "grey2binLUT.h"
#include "MILWrapper.h"
#include "../stlib/StartrackerData.h"

using namespace std;

// Convert a greycode image to binary:
void grey2bin(image* img);

#endif
