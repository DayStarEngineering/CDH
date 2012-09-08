/************************************************************************/
/*
 * File name: MDigDoubleBuffering.cpp
 *
 * Synopsis:  This program performs a double-buffering grab,
 *            times the processing, and displays some statistics.
 *
 *     Note:  The double buffering method is not recommended for real-time
 *            processing when the CPU usage is high. For more 
 *            robust real-time behavior, use the MdigProcess() function.
 *            See MDigProcess.c for a complete example.
 */
#include <mil.h>
#include <stdlib.h>

/* Main function. */
int MosMain(void)
{
   MIL_ID      MilApplication;
   MIL_ID      MilSystem     ;
   MIL_ID      MilDigitizer  ;
   MIL_ID      MilDisplay    ;
   MIL_ID      MilImage[2]   ;
   MIL_ID      MilImageDisp  ;
   long        NbProc = 0, n = 0;
   MIL_DOUBLE  Time = 0.0;
   MIL_TEXT_CHAR Text[10] = MIL_TEXT("0");

   /* Allocate defaults. */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem, &MilDisplay,
                                              &MilDigitizer, &MilImageDisp);

   /* Allocate 2 grab buffers. */
   for (n=0; n<2; n++)
       MbufAlloc2d(MilSystem,
                   MdigInquire(MilDigitizer, M_SIZE_X, M_NULL),
                   MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL),
                   8L+M_UNSIGNED,
                   M_IMAGE+M_GRAB+M_PROC, &MilImage[n]);


   /* Print a message. */
   MosPrintf(MIL_TEXT("\nDOUBLE BUFFERING ACQUISITION:\n"));
   MosPrintf(MIL_TEXT("-----------------------------\n\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to start.\n\n"));

   /* Grab continuously on display and wait for a key press. */
   MdigGrabContinuous(MilDigitizer,MilImageDisp);
   MosGetch();

   /* Halt continuous grab. */
   MdigHalt(MilDigitizer);
   MosPrintf(MIL_TEXT("Press <Enter> to stop.\n\n"));

   /* Put the digitizer in asynchronous mode to be able to process while grabbing. */
   MdigControl(MilDigitizer, M_GRAB_MODE, M_ASYNCHRONOUS);

   /* Grab the first buffer. */
   MdigGrab(MilDigitizer, MilImage[0]);

   /* Process one buffer while grabbing the other. */
   n=0;
   do {
      /* Grab the other buffer while processing previous one. */
      MdigGrab(MilDigitizer, MilImage[1-n]);

      /* Synchronize and start the timer. */
      if (NbProc == 0)
         MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);

      /* Write the frame counter. */
      MosSprintf(Text, 10, MIL_TEXT("%ld"), NbProc+1);
      MgraText(M_DEFAULT, MilImage[n], 32, 32, Text);

      /* Process the first buffer already grabbed.  */
      MimArith(MilImage[n], M_NULL, MilImageDisp, M_NOT);

      /* Count processed buffers. */
      NbProc++;

      /* Toggle grab buffers. */
      n = 1-n;
      }
   while(!MosKbhit());

   /* Wait until the end of the last grab and stop timer. */
   MdigGrabWait(MilDigitizer, M_GRAB_END);

   /* Print statistics. */
   MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &Time);
   MosGetch();

   MosPrintf(MIL_TEXT("%ld frames grabbed, at a frame rate of %.2f frames/sec ")
             MIL_TEXT("(%.2f ms/frame).\n"), NbProc, NbProc/Time, 1000.0*Time/NbProc);
   MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
   MosGetch();

   /* Free allocations. */
   for (n=0; n<2; n++)
       MbufFree(MilImage[n]);
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, MilDigitizer, MilImageDisp);

   return 0;
}
