/***********************************************************************************/
/*
 * File name: MDigProcessMultiple.cpp
 *
 * Synopsis:  This program shows how to use multiple digitizers to do processing.
 *            The main starts an independent processing job for each digitizer
 *            (one per camera) and then waits for a key to be pressed to stop them.
 *
 *     Note:  To do PA processing when using the Matrox Helios, +M_ON_BOARD
 *            attribute is added to the buffer allocations.
 *
 */

/* Headers. */
#include <mil.h>

/* Number of digitizer to use. */
#define DIGITIZER_NUM   2

/* Maximum number of images in the buffering grab queue of each digitizer.
   Generally, increasing the number of buffers prevents missing frames.
 */
#define BUFFERING_SIZE_MAX  30

/* Draw annotation in the Grab image buffers. This can increase CPU
   usage significantly. This is especially true for on-board buffers.
 */
#define DRAW_ANNOTATION M_NO

/* User's processing function prototype and hook parameter structure. */
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);
typedef struct
   {
   MIL_ID  MilImageDisp;
   MIL_INT ProcessedImageCount;
   } HookDataStruct;


/* Main function: */
/* -------------- */
int MosMain(void)
   {
   MIL_ID MilApplication;
   MIL_ID MilSystem;
   MIL_ID MilDigitizer[DIGITIZER_NUM];
   MIL_ID MilDisplay[DIGITIZER_NUM];
   MIL_ID MilImageDisp[DIGITIZER_NUM];
   MIL_ID MilGrabBufferList[DIGITIZER_NUM][BUFFERING_SIZE_MAX];
   MIL_INT n, m, BufferLocation = M_NULL;
   MIL_INT LastAllocatedN = M_NULL;
   MIL_INT LastAllocatedM = M_NULL;
   MIL_INT MilGrabBufferListSize = M_NULL;
   MIL_INT ProcessFrameCount;
   double ProcessFrameRate;
   MIL_INT BufferAllocationSuccess = 1;
   HookDataStruct UserHookData[DIGITIZER_NUM];

   /* Allocate application and system. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(M_DEF_SYSTEM_TYPE, M_DEFAULT, M_DEFAULT, &MilSystem);

   /* Allocate digitizers using the default DCF. */
   for(n=0; n<DIGITIZER_NUM; n++)
       MdigAlloc(MilSystem, n, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer[n]);

   /* Allocate displays. */
   for(n=0; n<DIGITIZER_NUM; n++)
       MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay[n]);

   /* If the system is a Matrox Helios, allocate the buffer on-board to benefit from
      Oasis PA processing. */
   if (MsysInquire(MilSystem, M_SYSTEM_TYPE, M_NULL) == M_SYSTEM_HELIOS_TYPE)
      BufferLocation = M_ON_BOARD;

   /* Allocate display buffers and clear them. */
   for(n=0; n<DIGITIZER_NUM; n++)
       {
       MbufAlloc2d(MilSystem,
                   MdigInquire(MilDigitizer[n], M_SIZE_X, M_NULL),
                   MdigInquire(MilDigitizer[n], M_SIZE_Y, M_NULL),
                   8+M_UNSIGNED, M_IMAGE+M_GRAB+M_PROC+M_DISP+BufferLocation,
                   &MilImageDisp[n]);
       MbufClear(MilImageDisp[n], 0);
       }

   /* Allocate the grab buffers for each digitizer and clear them. */
    MappControl(M_ERROR, M_PRINT_DISABLE);

    /* Init table. */
    for(n = 0; n < DIGITIZER_NUM; n++)
       for(m = 0; m < BUFFERING_SIZE_MAX; m++)
          MilGrabBufferList[n][m] = M_NULL;

    /* Try to allocate as many buffers as possible */
    for(m = M_NULL; m < BUFFERING_SIZE_MAX; m++)
      {
      for(n = M_NULL; n < DIGITIZER_NUM; n++)
         {
         /* Try to allocate a buffer. */
         MbufAlloc2d(MilSystem,
                     MdigInquire(MilDigitizer[n], M_SIZE_X, M_NULL),
                     MdigInquire(MilDigitizer[n], M_SIZE_Y, M_NULL),
                     MdigInquire(MilDigitizer[n], M_TYPE, M_NULL),
                     M_IMAGE+M_GRAB+M_PROC+BufferLocation,
                     &MilGrabBufferList[n][m]);

         /* If allocation is successful, clear the buffer. */
         if (MilGrabBufferList[n][m])
            {
            MbufClear(MilGrabBufferList[n][m], 0xFF);

            /* Keep index in table, in case it is the last allocated buffer. */
            LastAllocatedN = n;
            LastAllocatedM = m;
          }

         /* Allocation failed, stop immediately. */
         else
            {
            BufferAllocationSuccess = 0;
            break;
            }

         }

      /* If allocation worked on all digitizers, increase the number of buffers per
         digitizer. */
      if(BufferAllocationSuccess)
         MilGrabBufferListSize++;

      /* Allocation failed, stop immediately. */
      else
         break;
      }
   MappControl(M_ERROR, M_PRINT_ENABLE);

   /* Free the last allocated buffer to leave space for possible temporary buffer. */
   MbufFree(MilGrabBufferList[LastAllocatedN][LastAllocatedM]);
   MilGrabBufferList[LastAllocatedN][LastAllocatedM] = M_NULL;

   /* If other digitizers have a buffer allocated at same index, delete them for symmetry. */
   for(n = 0; n < DIGITIZER_NUM; n++)
      {
      if(MilGrabBufferList[n][LastAllocatedM])
         {
         MbufFree(MilGrabBufferList[n][LastAllocatedM]);
         MilGrabBufferList[n][LastAllocatedM] = M_NULL;
         }
      }
   MilGrabBufferListSize--;

   /* Start processing jobs. */
   for(n = 0; n < DIGITIZER_NUM; n++)
      {
      /* Display the target image. */
       MdispSelect(MilDisplay[n], MilImageDisp[n]);

       /* Grab continuously on the display and wait for a key press. */
       MdigGrabContinuous(MilDigitizer[n], MilImageDisp[n]);

       /* Print a message. */
       MosPrintf(MIL_TEXT("\nPROCESSING #%ld: Multiple buffered processing (%d buffers).\n"),
                 n+1, MilGrabBufferListSize);
       MosPrintf(MIL_TEXT("--------------------------------------------\n\n"));
       MosPrintf(MIL_TEXT("Press <Enter> to start.\r"));
       MosGetch();
       MosPrintf(MIL_TEXT("Processing started...  \n\n"));

       /* Halt continuous grab. */
       MdigHalt(MilDigitizer[n]);

       /* Initialize the User processing function data structure. */
       UserHookData[n].MilImageDisp        = MilImageDisp[n];
       UserHookData[n].ProcessedImageCount = 0;

       /* Start the processing. The processing function is called for every grabbed frame. */
       MdigProcess(MilDigitizer[n], MilGrabBufferList[n], MilGrabBufferListSize,
                                 M_START, M_DEFAULT, ProcessingFunction, &UserHookData[n]);
       }


   /* NOTE: Now the main is free to do other tasks while the processing is executing. */
   /* ------------------------------------------------------------------------------- */


   /* Report that the threads are started and wait for a key press. */
   MosPrintf(MIL_TEXT("\nMAIN: Processing task(s) running...\n"));
   MosPrintf(MIL_TEXT("-----------------------------------\n\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to stop.\n\n"));
   MosGetch();

   /* Stop the processing jobs. */
   for(n=0; n<DIGITIZER_NUM; n++)
       {
       /* Stop the processing. */
       MdigProcess(MilDigitizer[n], MilGrabBufferList[n], MilGrabBufferListSize,
                   M_STOP, M_DEFAULT, ProcessingFunction, &UserHookData[n]);


       /* Print statistics. */
       MdigInquire(MilDigitizer[n], M_PROCESS_FRAME_COUNT,  &ProcessFrameCount);
       MdigInquire(MilDigitizer[n], M_PROCESS_FRAME_RATE,   &ProcessFrameRate);
       MosPrintf(MIL_TEXT("Processing #%ld: %ld frames grabbed at %.1f frames/sec ")
                 MIL_TEXT("(%.1f ms/frame).\n"), n+1, ProcessFrameCount, ProcessFrameRate,
                 1000.0/ProcessFrameRate);
       }

    /* Free the grab buffers and MIL objects. */
    MappControl(M_ERROR, M_PRINT_DISABLE);
    for (n=0 ;n<DIGITIZER_NUM; n++)
       {
       for (m = 0; m < BUFFERING_SIZE_MAX; m++)
          {
          if(MilGrabBufferList[n][m])
             {
             MbufFree(MilGrabBufferList[n][m]);
             MilGrabBufferList[n][m] = 0;
             }
          }
       MbufFree(MilImageDisp[n]);
       MdispFree(MilDisplay[n]);
       MdigFree(MilDigitizer[n]);
       }

    MappControl(M_ERROR, M_PRINT_ENABLE);

   /* Wait for a key press to exit. */
   MosPrintf(MIL_TEXT("\nPress <Enter> to end.\n\n"));
   MosGetch();

   /* Free buffers. */
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
   }

/* Processing thread(s) function: */
/* ---------------------------------------------------------------- */



/* User's processing function called every time a grab buffer is modified. */
/* ------------------------------------------------------------------------*/

/* Local defines. */
#define STRING_LENGTH_MAX  20
#define STRING_POS_X       20
#define STRING_POS_Y       20

MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void MPTYPE *HookDataPtr)
   {
   HookDataStruct *UserHookDataPtr = (HookDataStruct *)HookDataPtr;
   MIL_ID ModifiedBufferId;
   MIL_TEXT_CHAR Text[STRING_LENGTH_MAX]= {MIL_TEXT('\0'),};

   /* Retrieve the MIL_ID of the grabbed buffer. */
   MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);

   /* Increase the frame count. */
   UserHookDataPtr->ProcessedImageCount++;

   /* Draw the frame count (if enabled). */
   if (DRAW_ANNOTATION)
      {
      MosSprintf(Text, STRING_LENGTH_MAX, MIL_TEXT("%ld"),
                 UserHookDataPtr->ProcessedImageCount);
      MgraText(M_DEFAULT, ModifiedBufferId, STRING_POS_X, STRING_POS_Y, Text);
      }

   /* Perform the processing and update the display. */
   MimArith(ModifiedBufferId, M_NULL, UserHookDataPtr->MilImageDisp, M_NOT);

   return 0;
   }
