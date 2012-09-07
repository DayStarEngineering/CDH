/************************************************************************/
/*
*
* Filename     :  MILPA.H
* Revision     :  9.02.0812
* Owner        :  Matrox Imaging dept.
* Content      :  This file contains the defines necessary to use the
*                 Matrox Native PA DTK.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2011.
* All Rights Reserved
*************************************************************************/

#ifndef __MILPA_H
#define __MILPA_H

/* Defines necessary on the PowerPc to compile Native PA code. 

   Note: On Odyssey, MIL.H can also be included and MIL function used
   in the Slave PA function but this give a function that is not 
   portable on the Helios.
*/
#if M_MIL_USE_PPC
/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif													 

#define MFTYPE32
#define MFTYPE 
#define MPTYPE 
#if M_MIL_USE_CONST_API
   typedef const char*            MIL_API_CONST_TEXT_PTR;
   #define MIL_API_CONST const
#else
   typedef char*                  MIL_API_CONST_TEXT_PTR;
   #define MIL_API_CONST
#endif
typedef long   MIL_INT;
typedef long   MIL_INT32;
typedef long   MIL_ID;
typedef long long          MIL_INT64;
typedef unsigned long long MIL_UINT64;
typedef double   MIL_DOUBLE;
typedef unsigned long      IM_UINT;
#include <milfunc.h> 
#define M_NATIVE_ID 1016L
MFTYPE32 long MFTYPE MbufInquire(MIL_ID BufId, long InquireType, void MPTYPE *ResultPtr);
#define mp_mil_buf_inquire(Src, InquireType, VarPtr) (MbufInquire(Src, InquireType, VarPtr))
#define mp_mil_func_resource(Func) (mp_thr_thread_resource(mp_thr_thread_descriptor(mp_sys_this_thread())))
typedef void (*MFUNCSLAVEPAFCTPTR)(MIL_ID FunctionId);
#define M_NULL  0

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#include <image2.h> 
#endif

/* Defines necessary on the Host to compile Native PA code in the kernel mode DLL. */
#if M_MIL_USE_PA_CODE_ONLY
#include <heliospa.h>
#endif

#endif

/* Define to support MfuncErrorReport() in PA slave functions (must match MIL.H). */
#define M_FUNC_ERROR   49000

/* Defines for PA slave functions return value (must match MIL.H). */
#define M_TRUE         1L  /* sucess */
#define M_FALSE        0L  /* fail   */

