/*****************************************************************************************/
/*
 * File name: DistributedMilSyncAsyncMain.cpp 
 *
 * Synopsis:  This example shows how to use the MIL Function Development module to 
 *            call custom synchronous and asynchronous MIL functions.
 *
 *            It contains the main to test the SynchronousFunction() and 
 *            AsynchronousFunction() master functions.
 *
 *            The slave functions can be found in the DistributedMILSyncAsyncSlave project.
 */
#include <mil.h>

/* Master MIL functions declarations */
long MFTYPE SynchronousFunction(MIL_ID SrcImage, MIL_ID DstImage,  long Option);
void MFTYPE AsynchronousFunction(MIL_ID SrcImage, MIL_ID DstImage, long Option);

/* Target image file name */
#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("Wafer.mim")
#define NB_LOOP      100

/* Slave IP adress and system */
#define SLAVE_IP_ADDRESS         MIL_TEXT("127.0.0.1")
#define SLAVE_SYSTEM             M_SYSTEM_DEFAULT

/* Build slave system descriptor.  Use preprocessor behavior that */
/* concatenates adjacent strings in a single string.              */
/* Format of descriptor is: protocol://address/system             */
/* Eg.: dmiltcp://127.0.0.1/M_SYSTEM_HOST                          */
#define SLAVE_SYSTEM_DESCRIPTOR  M_DMILTCP_TRANSPORT_PROTOCOL MIL_TEXT("://") SLAVE_IP_ADDRESS MIL_TEXT("/") SLAVE_SYSTEM

/* Main to test the functions. */
/* --------------------------- */

int MosMain(void)
{
   MIL_ID       MilApplication,       /* Application Identifier.  */
                MilSystem,            /* System Identifier.       */
                MilDisplay,           /* Display Identifier.      */
                MilImage;             /* Image buffer Identifier. */
   long         ReturnValue;          /* Return Value holder.     */
   MIL_DOUBLE   SynchronousCallTime,  /* Timer variable.          */
                AsynchronousCallTime; /* Timer variable.          */
   int          n;                    /* Counter.                 */
   
   /* Allocate application, system and display. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(SLAVE_SYSTEM_DESCRIPTOR, M_DEF_SYSTEM_NUM, M_SETUP, &MilSystem);
   MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay);

   /* Restore source image into an automatically allocated image buffer. */
   MbufRestore(IMAGE_FILE, MilSystem, &MilImage);
  
   /* Uncomment to display the image.    */
   /* MdispSelect(MilDisplay, MilImage); */
   
   /* Pause */
   MosPrintf(MIL_TEXT("\nMIL DTK:\n"));
   MosPrintf(MIL_TEXT("--------\n\n"));
   MosPrintf(MIL_TEXT("Custom synchronous and asynchronous MIL functions:\n\n"));
   MosPrintf(MIL_TEXT("This example times a synchronous and asynchronous custom function call.\n"));
   MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
   MosGetch();

   /* Synchronous function call. */
   /* -------------------------- */

   /* Call the function a first time for more accurate timings later (dll load, ...). */
   ReturnValue = SynchronousFunction(MilImage, MilImage, M_DEFAULT);

   /* Start the timer */
   MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);

   /* Loop many times for more precise timing. */
   for (n= 0; n < NB_LOOP; n++)
      {
      /* Call the custom MIL synchronous function. */
      ReturnValue = SynchronousFunction(MilImage, MilImage, M_DEFAULT);
      }

   /* Read the timer. */
   MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &SynchronousCallTime);

   /* Print the synchronous call time. */
   MosPrintf(MIL_TEXT("Synchronous  function call time: %.1f us.\n"), SynchronousCallTime*1000000/NB_LOOP);

   /* Asynchronous function call. */
   /* --------------------------- */

   /* Call the function a first time for more accurate timings later (dll load, ...). */
  AsynchronousFunction(MilImage, MilImage, M_DEFAULT);
  MthrWait(M_DEFAULT, M_THREAD_WAIT, M_NULL);

   /* Start the timer */
   MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);

   /* Loop many times for more precise timing. */
   for (n= 0; n < NB_LOOP; n++)
      {
      /* Call the custom MIL asynchronous function. */
      AsynchronousFunction(MilImage, MilImage, M_DEFAULT);
      }

   /* Read and print the time. */
   MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &AsynchronousCallTime);
      
   /* Print the asynchronous call time. */
   MosPrintf(MIL_TEXT("Asynchronous function call time: %.1f us.\n"), AsynchronousCallTime*1000000/NB_LOOP);
   MosPrintf(MIL_TEXT("Press a key to terminate.\n\n"));
   MosGetch();

   /* Free all allocations. */
   MbufFree(MilImage);
   MdispFree(MilDisplay);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
}

