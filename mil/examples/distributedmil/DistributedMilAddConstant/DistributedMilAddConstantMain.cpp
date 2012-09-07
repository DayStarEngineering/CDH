/*****************************************************************************************/
/*
 * File name: DistributedMilAddConstantMain.cpp
 *
 * Synopsis:  This file contains the main program to test and time the different 
 *            versions of a custom add constant MIL function MIL created with 
 *            the MIL Function Development module.
 *
 *            The slave functions can be found in the DistributedMILAddConstantSlave project.
 */

/* Standard headers. */
#include <mil.h>

/* Target image file name */
#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("board.mim")

/* Timing loop iterations. */
#define NB_LOOP 100

/* Defines for the different versions of the target function to run on the Odyssey. */
#define USE_C           0 /* Target C function C.                 */
#define USE_MIL         1 /* Target function MIL.                 */
#define NB_VERSIONS     2 /* Number of different versions to call. */
static MIL_TEXT_CHAR *VersionName[] = {MIL_TEXT("C"), MIL_TEXT("MIL")}; 

/* Slave IP adress and system */
#define SLAVE_IP_ADDRESS         MIL_TEXT("127.0.0.1")
#define SLAVE_SYSTEM             M_SYSTEM_DEFAULT

/* Build slave system descriptor.  Use preprocessor behavior that */
/* concatenates adjacent strings in a single string.              */
/* Format of descriptor is: protocol://address/system             */
/* Eg.: miltcp://127.0.0.1/M_SYSTEM_HOST                          */
#define SLAVE_SYSTEM_DESCRIPTOR M_DMILTCP_TRANSPORT_PROTOCOL MIL_TEXT("://") SLAVE_IP_ADDRESS MIL_TEXT("/") SLAVE_SYSTEM

/* Master functions prototypes: */
/* Custom C function (See DTKAddConstantC.c) */
void MFTYPE AddConstantC(MIL_ID SrcImage, MIL_ID DstImage, unsigned long Constant);


/* Main to test the AddConstant functions. */
/* --------------------------------------- */

int MosMain(void)
   {
   MIL_ID MilApplication,        /* Application Identifier.  */
          MilSystem,             /* System Identifier.       */
          MilDisplay,            /* Display Identifier.      */
          MilImageDisp,          /* Image buffer Identifier. */ 
          MilImageSrc,           /* Image buffer Identifier. */ 
          MilImageDst;           /* Image buffer Identifier. */ 
   int    Version, n;            /* Loop variables.          */
   MIL_DOUBLE Time;                  /* Processing time.         */

   /* Allocate application, system and display. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(SLAVE_SYSTEM_DESCRIPTOR, M_DEF_SYSTEM_NUM, M_SETUP, &MilSystem);
   MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay);

   /* Restore the source image into one display buffer and 2 processing buffers. */
   MbufRestore(IMAGE_FILE, MilSystem, &MilImageDisp);
   MbufRestore(IMAGE_FILE, MilSystem, &MilImageSrc);
   MbufRestore(IMAGE_FILE, MilSystem, &MilImageDst);

   /* Display the source image. */
   MdispSelect(MilDisplay, MilImageDisp);
   
   /* Pause */
   MosPrintf(MIL_TEXT("\nMIL DTK:\n"));
   MosPrintf(MIL_TEXT("--------\n\n"));
   MosPrintf(MIL_TEXT("This example tests and times different versions of a custom\n"));
   MosPrintf(MIL_TEXT("asynchronous MIL function that adds a constant to an image.\n"));
   MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
   MosGetch();

   /* Process the image using the C version of the custom MIL function. */
   AddConstantC(MilImageSrc, MilImageDisp, 0x40);
   
   /* Print comment */
   MosPrintf(MIL_TEXT("A constant was added to the image using a user-made MIL function.\n\n"));

   /* Call and time all the versions of the add constant function.
      Do it in loop for more precision.
   */
   for (Version = 0; Version < NB_VERSIONS; Version++)
      {
      for (n= 0; n < NB_LOOP+1; n++)
         {
         /* Don't time the first iteration (avoid DLL load time, ...). */
         if (n == 1)
            MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);

         /* Call the proper version */
         switch(Version)
            {
            case USE_C:
                 AddConstantC(MilImageSrc, MilImageDst, 0x40);
                 break;

            case USE_MIL:
                 MimArith(MilImageSrc, 0x40, MilImageDst, M_ADD_CONST);  
                 break;
            }
         }

      /* Read and print the time.*/
      MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);
      MosPrintf(MIL_TEXT("Add constant time (%s version): %.3f ms.\n"), VersionName[Version], Time*1000/NB_LOOP);
      }

   /* Pause */
   MosPrintf(MIL_TEXT("Press a key to terminate.\n\n"));
   MosGetch();

   /* Free all allocations. */
   MbufFree(MilImageSrc);
   MbufFree(MilImageDst);
   MbufFree(MilImageDisp);
   MdispFree(MilDisplay);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
   }



