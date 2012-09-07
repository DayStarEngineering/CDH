//MfuncBuf DTK functions

/***************************************************************************/
/*

    Filename:  MILFUNC.H
    Revision:  9.02.0812

    Content :  This file contains the prototypes for the Matrox
               Imaging Library (MIL) MfuncBuf DTK functions.

    Copyright © Matrox Electronic Systems Ltd., 1992-2011.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MFUNCBUF_H
#define __MFUNCBUF_H

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __MILBUFFERINFO_H__
#if !M_MIL_USE_CPP_FUNC_BUF
typedef void* MIL_BUFFER_INFO;
MFTYPE32 void MFTYPE MfuncBufInCache(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_DOUBLE MFTYPE MfuncBufMaxValue(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_DOUBLE MFTYPE MfuncBufMinValue(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 void MFTYPE MfuncBufModified(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufDriverId(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_DATA_PTR  MFTYPE MfuncBufHostAdress(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_DATA_PTR  MFTYPE MfuncBufBandHostAdress(MIL_BUFFER_INFO BufInfoPtr, long Band);
MFTYPE32 MIL_DATA_PTR  MFTYPE MfuncBufBandPhysAdress(MIL_BUFFER_INFO BufInfoPtr, long Band);
MFTYPE32 MIL_DATA_PTR  MFTYPE MfuncBufPhysicalAdress(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufSizeX(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufSizeY(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufSizeBand(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufSizeBit(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufType(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufPitch(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufPitchByte(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 BUFATTRTYPE MFTYPE MfuncBufAttribute(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 BUFATTRTYPE MFTYPE MfuncBufFormat(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT64 MFTYPE MfuncBufFlags(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufLockable(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufParentOffsetX(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufParentOffsetY(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufParentOffsetBand(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufAncestorOffsetX(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufAncestorOffsetY(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufAncestorOffsetBand(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufAncestorOffsetBit(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufNativeId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufHostId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufParentId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufAncestorId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufOwnerSystemId(MIL_BUFFER_INFO BufInfoPtr);
MFTYPE32 MIL_INT MFTYPE MfuncBufOwnerSystemType(MIL_BUFFER_INFO BufInfoPtr);
#endif 
#else
MFTYPE32 void MFTYPE MfuncBufInCache(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_DOUBLE MFTYPE MfuncBufMaxValue(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_DOUBLE MFTYPE MfuncBufMinValue(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 void MFTYPE MfuncBufModified(MIL_BUFFER_INFO BufferInfoPtr);
MFTYPE32 MIL_ID MFTYPE MfuncBufDriverId(MIL_BUFFER_INFO BufferInfoPtr);
#endif 

// The documented names for these 2 functions are different than 
// the actual names.  Until MIL 9.00, we need to keep the same names, 
// hence these defines
#define MfuncBufHostAddressBand     MfuncBufBandHostAdress
#define MfuncBufPhysicalAddressBand MfuncBufBandPhysAdress
#define MfuncBufPhysicalAddress     MfuncBufPhysicalAdress
#define MfuncBufHostAddress         MfuncBufHostAdress


#ifdef __cplusplus
}
#endif


#endif
