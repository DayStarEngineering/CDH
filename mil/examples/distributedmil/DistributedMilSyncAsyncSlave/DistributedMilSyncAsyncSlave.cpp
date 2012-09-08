/*****************************************************************************************/
/*
 * File name: DistributedMilSyncAsyncSlave.cpp
 *
 * Synopsis:  This example shows how to use the MIL Function Development module to 
 *            create custom synchronous and asynchronous MIL functions.
 *
 *            It contains the SlaveSynchronousFunction() and SlaveAsynchronousFunction()
 *            slave functions.
 */
#include <mil.h>

/* Slave MIL Function prototypes. */
void MFTYPE SlaveSynchronousFunction(MIL_ID Func);
void MFTYPE SlaveAsynchronousFunction(MIL_ID Func);

/* Slave Synchronous MIL Function definition. */
/* ------------------------------------------ */

void MFTYPE SlaveSynchronousFunction(MIL_ID Func)
{
  MIL_ID SrcImage, DstImage;
  unsigned long Option, *ReturnValuePtr, ValueToReturn = M_NULL;

  /* Read the parameters including pointer to the ReturnValue data. */
  MfuncParamValue(Func, 1, &SrcImage);
  MfuncParamValue(Func, 2, &DstImage);
  MfuncParamValue(Func, 3, &Option); 
  MfuncParamValue(Func, 4, &ReturnValuePtr); 

  /* Do the processing and calculate the value to return. */
  // ValueToReturn = ...
 
  /* Write the return value. */
  *ReturnValuePtr = ValueToReturn;
}


/* Slave Asynchronous MIL Function definition. */
/* ------------------------------------------- */

void MFTYPE SlaveAsynchronousFunction(MIL_ID Func)
{
  MIL_ID SrcImage, DstImage;
  unsigned long Option;

  /* Read the parameters including pointer to the ReturnValue data. */
  MfuncParamValue(Func, 1, &SrcImage);
  MfuncParamValue(Func, 2, &DstImage);
  MfuncParamValue(Func, 3, &Option); 

  /* Do the processing. */
  //...
}
