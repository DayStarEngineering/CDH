/*****************************************************************************************/
/*
 * File name: AddConstant.cpp
 *
 * Synopsis:  This file contains the main program to test and time the AddConstant
 *            function accelerated by the Solios Processing FPGA.
 *
 *            Note that this example requires a Solios with a processing FPGA that
 *            is loaded with a configuration containing the MIL standard add constant
 *            processing unit.
 */

/* Standard headers. */
#include <mil.h>

/* Target image file name */
#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("board.mim")

/* Timing loop iterations. */
#define NB_LOOP 100

/* Main to test the AddConstant functions. */
/* --------------------------------------- */

int MosMain(void)
   {
   MIL_ID  MilApplication,        /* Application Identifier.       */
           MilSystem,             /* System Identifier.            */
           MilDisplay,            /* Display Identifier.           */
           MilImageDisp,          /* Image buffer Identifier.      */
           MilImageProc,          /* Image buffer Identifier.      */
           MilImageSrc,           /* Image buffer Identifier.      */
           MilDigitizer;          /* Digitizer buffer Identifier.  */
   MIL_INT SizeX,
           SizeY,
           SizeBand,
           Selection,
           n;
   double  Time;                  /* Processing time.         */

   /* Allocate application, system and display. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(M_SYSTEM_SOLIOS, M_DEF_SYSTEM_NUM, M_SETUP, &MilSystem);
   MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay);

   MosPrintf(MIL_TEXT("Please select the type of source image to process:\n"));
   MosPrintf(MIL_TEXT("(1)- Grab image\n"));
   MosPrintf(MIL_TEXT("(2)- Static image\n"));
   Selection = MosGetch();

   switch(Selection)
      {
      case '1':   /* Grab image */
         MdigAlloc(MilSystem, M_DEF_DIGITIZER_NUM, M_DEF_DIGITIZER_FORMAT,
                   M_DEF_DIGITIZER_INIT, &MilDigitizer);
         SizeX = MdigInquire(MilDigitizer, M_SIZE_X, M_NULL);
         SizeY = MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL);
         SizeBand = MdigInquire(MilDigitizer, M_SIZE_BAND, M_NULL);
         break;

      case '2':   /* Static image */
      default:    /* Static image */
         MilDigitizer = M_NULL;
         SizeX = MbufDiskInquire(IMAGE_FILE, M_SIZE_X, M_NULL);
         SizeY = MbufDiskInquire(IMAGE_FILE, M_SIZE_Y, M_NULL);
         SizeBand = MbufDiskInquire(IMAGE_FILE, M_SIZE_BAND, M_NULL);
         break;
      }

   MosPrintf(MIL_TEXT("Processed image will be: %dx%d %d bands"), SizeX, SizeY, SizeBand);

   /* Buffer location is critical for processing to get offloaded by the
      processing FPGA. All source buffers must be on-board for processing
      to be done by the FPGA. See milsolios.txt for buffer allocation
      requirements.
   */
   if(MilDigitizer)
      {
      /* Allocates a Grab buffer M_GRAB (Grab SDRAM = Bank 1) and grab a frame to process. */
      MbufAllocColor(MilSystem,
               SizeBand,
               SizeX,
               SizeY,
               8+M_UNSIGNED,
               M_IMAGE+M_GRAB+M_PROC+M_FPGA_ACCESSIBLE,
               &MilImageSrc);
      MdigGrab(MilDigitizer, MilImageSrc);
      }
   else
      {
      /* Allocates a Processing only buffer (Processing SDRAM = Bank 2) and load an image. */
      MbufAllocColor(MilSystem,
               SizeBand,
               SizeX,
               SizeY,
               8+M_UNSIGNED,
               M_IMAGE+M_PROC+M_FPGA_ACCESSIBLE,
               &MilImageSrc);
      MbufLoad(IMAGE_FILE, MilImageSrc);
      }

   /* Allocates a Display buffer in the PC memory (M_HOST_MEMORY) and copy the source image. */
   MbufAllocColor(MilSystem,
               SizeBand,
               SizeX,
               SizeY,
               8+M_UNSIGNED,
               M_IMAGE+M_GRAB+M_DISP+M_FPGA_ACCESSIBLE,
               &MilImageDisp);
   MbufAllocColor(MilSystem,
               SizeBand,
               SizeX,
               SizeY,
               8+M_UNSIGNED,
               M_IMAGE+M_PROC+M_GRAB+M_HOST_MEMORY+M_FPGA_ACCESSIBLE,
               &MilImageProc);
   MbufCopy(MilImageSrc, MilImageDisp);

   /* Display the source image. */
   MdispSelect(MilDisplay, MilImageDisp);

   /* Pause */
   MosPrintf(MIL_TEXT("\nMIL FDK:\n"));
   MosPrintf(MIL_TEXT("--------\n\n"));
   MosPrintf(MIL_TEXT("This example tests and times the AddConstant function\n"));
   MosPrintf(MIL_TEXT("accelereted on the Solios Processing FPGA.\n"));
   MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
   MosGetch();

   /* Call and time all the versions of the add constant function.
      Do it in loop for more precision.
   */
   for (n= 0; n < NB_LOOP+1; n++)
      {
      /* Don't time the first iteration (avoid DLL load time, ...). */
      if (n == 1)
         MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);

      /* If the on board FPGA contains the MIL Add constant processing unit,
         the processing will be offloaded and executed by the hardware.
       */
      MimArith(MilImageSrc, 0x40, MilImageProc, M_ADD_CONST+M_SATURATION);
      }

   /* Read and print the time.*/
   MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);
   MosPrintf(MIL_TEXT("Add constant time: %.3f ms.\n"), Time*1000/NB_LOOP);
   MbufCopy(MilImageProc, MilImageDisp);

   /* Pause */
   MosPrintf(MIL_TEXT("Press a key to terminate.\n\n"));
   MosGetch();

   /* Free all allocations. */
   if(MilDigitizer)
      MdigFree(MilDigitizer);
   MbufFree(MilImageSrc);
   MbufFree(MilImageProc);
   MbufFree(MilImageDisp);
   MdispFree(MilDisplay);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
   }
