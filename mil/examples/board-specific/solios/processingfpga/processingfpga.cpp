/*************************************************************************************/
/*
* File name:   ProcessingFpga.cpp
*
* Synopsis:    This program shows how to use the Solios Processing FPGA.
*
*              For this service pack release, the Processing FPGA firmware
*              (filename.firmware) can accelerate the following MIL functions:
*              1- MbufBayer
*              2- MimArithMultiple (M_OFFSET_GAIN)
*              3- MimArith (M_ADD_CONST)
*
*      Note:   Correct buffer allocation is critical for processing to be
*              offloaded by the processing FPGA. All source buffers must
*              be on-board in either M_MEMORY_BANK_0 (grab FPGA SDRAM memory)
*              or M_MEMORY_BANK_1 (processing FPGA SDRAM memory).
*              M_MEMORY_BANK_2 (processing FPGA SRAM memory) is not supported
*              for this release.
*
* Known
* limitations: 1- All buffers must have a line length that is a multiple of 64
*                 bytes. This is a temporary limitation.
*              2- Bayer processing is restricted to 8 bit buffers. 16 bit
*                 buffers will eventually be supported in a later service
*                 release.
*/
#include <mil.h>

/* Number of images in the buffering grab queue.
Generally, increasing this number gives better real-time grab.
*/
#define BUFFERING_SIZE_MAX    5

/* For bayer processing, you must choose the bayer filter type for your camera. */
#define BAYER_PATTERN         M_BAYER_RG
/*#define BAYER_PATTERN         M_BAYER_BG */
/*#define BAYER_PATTERN         M_BAYER_GB */
/*#define BAYER_PATTERN         M_BAYER_GR */

/* User's processing function prototype. */
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void MPTYPE *HookDataPtr);

/* User's processing function hook data structure. */
typedef struct
   {
   MIL_ID  MilImageDisp;
   MIL_ID  WhiteBalance;
   MIL_ID  MilGainImage;
   MIL_ID  MilOffsetImage;
   MIL_INT ProcessingToDo;
   MIL_INT BitShift;
   MIL_INT ProcessedImageCount;
   } HookDataStruct;

void AllocateProcessingBuffers(MIL_ID MilSystem, MIL_ID MilDigitizer, MIL_ID MilDisplay, MIL_INT SizeBand,
                               MIL_INT SizeX, MIL_INT SizeY, HookDataStruct* Struct);

/* Main function. */
/* ---------------*/
int MosMain(void)
   {
   MIL_ID  MilApplication;
   MIL_ID  MilSystem     ;
   MIL_ID  MilDigitizer  ;
   MIL_ID  MilDisplay    ;
   MIL_ID  MilGrabBufferList[BUFFERING_SIZE_MAX] = { 0 };
   MIL_INT MilGrabBufferListSize;
   MIL_INT ProcessFrameCount  = 0;
   MIL_INT NbFrames           = 0;
   double  ProcessFrameRate   = 0;
   HookDataStruct UserHookData;
   MIL_INT SizeX, SizeY, SizeBand;

   /* Allocate defaults. */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem, &MilDisplay,
      &MilDigitizer, M_NULL);

   if(MsysInquire(MilSystem, M_PROCESSOR_NUM, M_NULL) == 0)
      {
      MosPrintf(MIL_TEXT("Error, this example demonstrates processing FPGA usage\n"));
      MosPrintf(MIL_TEXT("No processing FPGA detected.\n"));
      return(1);
      }

   MosPrintf(MIL_TEXT("This example demonstrates how the use the Solios Processing Fpga\n"));
   MosPrintf(MIL_TEXT("This service pack release supports processing offload of ")
      MIL_TEXT("the following:\n"));
   MosPrintf(MIL_TEXT("(1)- MbufBayer\n"));
   MosPrintf(MIL_TEXT("(2)- MimArithMultiple (M_OFFSET_GAIN)\n"));
   MosPrintf(MIL_TEXT("(3)- MimArith (ADD_CONST)\n"));
   MosPrintf(MIL_TEXT("Choose the processing to do\n"));
   UserHookData.ProcessingToDo = MosGetch();

   switch(UserHookData.ProcessingToDo)
      {
      case '1':
         MosPrintf(MIL_TEXT("\nMbufBayer selected.\n\n"));
         UserHookData.ProcessingToDo = 1;
         UserHookData.BitShift = MdigInquire(MilDigitizer, M_SIZE_BIT, M_NULL) - 8;
         break;
      case '2':
         MosPrintf(MIL_TEXT("\nMimArithMultiple selected.\n\n"));
         UserHookData.ProcessingToDo = 2;
         break;
      case '3':
         MosPrintf(MIL_TEXT("\nMimArith selected.\n\n"));
         UserHookData.ProcessingToDo = 3;
         break;
      default:
         MosPrintf(MIL_TEXT("\nInvalid selection !.\n\nDefaulting to MimArith .\n\n"));
         UserHookData.ProcessingToDo = 3;
         break;
      }

   SizeX = MdigInquire(MilDigitizer, M_SIZE_X, M_NULL);
   SizeY = MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL);
   SizeBand = MdigInquire(MilDigitizer, M_SIZE_BAND, M_NULL);

   /* Allocate the grab buffers and clear them. */
   MappControl(M_ERROR, M_PRINT_DISABLE);

   AllocateProcessingBuffers(MilSystem, MilDigitizer, MilDisplay, SizeBand, SizeX, SizeY, &UserHookData);

   for(MilGrabBufferListSize = 0;
      MilGrabBufferListSize<BUFFERING_SIZE_MAX;
      MilGrabBufferListSize++)
      {
      MbufAllocColor(MilSystem,
         SizeBand,
         SizeX,
         SizeY,
         ((MdigInquire(MilDigitizer, M_SIZE_BIT, M_NULL) == 8) ? 8+M_UNSIGNED : 16+M_UNSIGNED),
         M_IMAGE+M_GRAB+M_PROC+M_FPGA_ACCESSIBLE,
         &MilGrabBufferList[MilGrabBufferListSize]);

      if(MilGrabBufferList[MilGrabBufferListSize])
         MbufClear(MilGrabBufferList[MilGrabBufferListSize], 0xFF);
      else
         break;
      }
   MappControl(M_ERROR, M_PRINT_ENABLE);

   /* Free a buffer to leave space for possible temporary buffer. */
   MilGrabBufferListSize--;
   MbufFree(MilGrabBufferList[MilGrabBufferListSize]);

   /* Print a message. */
   MosPrintf(MIL_TEXT("\nMULTIPLE BUFFERED PROCESSING.\n"));
   MosPrintf(MIL_TEXT("-----------------------------\n\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to start.\n\n"));

   /* Grab continuously on the display and wait for a key press. */
   MdigGrabContinuous(MilDigitizer, UserHookData.MilImageDisp);
   MosGetch();

   /* Halt continuous grab. */
   MdigHalt(MilDigitizer);

   if(UserHookData.ProcessingToDo == 1)
      {
      MIL_ID MilTempBuffer;
      /* For bayer processing, we must perform a white balance operation,
      White balancing is not supported by the Processing Fpga, MIL will
      therefore perform this operation using the host CPU instead. */

      /* Allocate a temporary host buffer */
      MbufAlloc2d(MilSystem,
                  SizeX,
                  SizeY,
                  ((MdigInquire(MilDigitizer, M_SIZE_BIT, M_NULL) == 8) ? 8+M_UNSIGNED : 16+M_UNSIGNED),
                  M_IMAGE+M_GRAB,
                  &MilTempBuffer);

      MdigGrab(MilDigitizer, MilTempBuffer);
      MbufBayer(MilTempBuffer, UserHookData.MilImageDisp, UserHookData.WhiteBalance,
         BAYER_PATTERN+M_WHITE_BALANCE_CALCULATE);

      MbufFree(MilTempBuffer);
      }

   /* Initialize the User's processing function data structure. */
   UserHookData.ProcessedImageCount = 0;

   /* Start the processing. The processing function is called for every frame grabbed. */
   MdigProcess(MilDigitizer, MilGrabBufferList, MilGrabBufferListSize,
      M_START, M_DEFAULT, ProcessingFunction, &UserHookData);


   /* NOTE: Now the main() is free to perform other tasks while the processing is executing. */
   /* --------------------------------------------------------------------------------- */


   /* Print a message and wait for a key press after a minimum number of frames. */
   MosPrintf(MIL_TEXT("Press <Enter> to stop.\n\n"));
   MosGetch();

   /* Stop the processing. */
   MdigProcess(MilDigitizer, MilGrabBufferList, MilGrabBufferListSize,
      M_STOP+M_WAIT, M_DEFAULT, ProcessingFunction, &UserHookData);


   /* Print statistics. */
   MdigInquire(MilDigitizer, M_PROCESS_FRAME_COUNT,  &ProcessFrameCount);
   MdigInquire(MilDigitizer, M_PROCESS_FRAME_RATE,   &ProcessFrameRate);
   MosPrintf(MIL_TEXT("\n\n%ld frames grabbed at %.1f frames/sec (%.1f ms/frame).\n"),
      ProcessFrameCount, ProcessFrameRate, 1000.0/ProcessFrameRate);
   MosPrintf(MIL_TEXT("Press <Enter> to end.\n\n"));
   MosGetch();

   /* Free the grab buffers. */
   while(MilGrabBufferListSize > 0)
      MbufFree(MilGrabBufferList[--MilGrabBufferListSize]);

   if(UserHookData.MilGainImage)
      MbufFree(UserHookData.MilGainImage);
   if(UserHookData.MilOffsetImage)
      MbufFree(UserHookData.MilOffsetImage);
   if(UserHookData.WhiteBalance)
      MbufFree(UserHookData.WhiteBalance);
   /* Release defaults. */
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, MilDigitizer,
      UserHookData.MilImageDisp);

   return 0;
   }


/* User's processing function called every time a grab buffer is modified. */
/* -----------------------------------------------------------------------*/
MIL_INT MFTYPE ProcessingFunction(MIL_INT HookType, MIL_ID HookId, void MPTYPE *HookDataPtr)
   {
   HookDataStruct *UserHookDataPtr = (HookDataStruct *)HookDataPtr;
   MIL_ID ModifiedBufferId;

   /* Retrieve the MIL_ID of the grabbed buffer. */
   MdigGetHookInfo(HookId, M_MODIFIED_BUFFER+M_BUFFER_ID, &ModifiedBufferId);

   /* Print and draw the frame count. */
   UserHookDataPtr->ProcessedImageCount++;
   MosPrintf(MIL_TEXT("Processing frame #%d.\r"), UserHookDataPtr->ProcessedImageCount);

   /* Perform the processing and update the display. */

   if(UserHookDataPtr->ProcessingToDo == 1)
      MbufBayer(ModifiedBufferId, UserHookDataPtr->MilImageDisp, UserHookDataPtr->WhiteBalance,
      BAYER_PATTERN+M_BAYER_BIT_SHIFT(UserHookDataPtr->BitShift));
   else if(UserHookDataPtr->ProcessingToDo == 2)
      MimArithMultiple(ModifiedBufferId, UserHookDataPtr->MilOffsetImage,
      UserHookDataPtr->MilGainImage, 8, M_NULL,
      UserHookDataPtr->MilImageDisp, M_OFFSET_GAIN, M_DEFAULT);
   else if(UserHookDataPtr->ProcessingToDo == 3)
      MimArith(ModifiedBufferId, 64, UserHookDataPtr->MilImageDisp, M_ADD_CONST+M_SATURATION);

   return 0;
   }


void AllocateProcessingBuffers(MIL_ID MilSystem, MIL_ID MilDigitizer, MIL_ID MilDisplay, MIL_INT SizeBand,
                               MIL_INT SizeX, MIL_INT SizeY, HookDataStruct* Struct)
   {
   MIL_INT DispSizeBand       = 0;
   BUFATTRTYPE DispAttribute  = 0;
   Struct->MilImageDisp       = M_NULL;
   Struct->WhiteBalance       = M_NULL;
   Struct->MilGainImage       = M_NULL;
   Struct->MilOffsetImage     = M_NULL;

   switch(Struct->ProcessingToDo)
      {
      case 1:  /* Bayer */
         DispSizeBand = 3;
         DispAttribute = M_IMAGE+M_GRAB+M_DISP+M_BGR32+M_PACKED+M_HOST_MEMORY+M_FPGA_ACCESSIBLE;
         MbufAlloc1d(MilSystem, 3, 32+M_FLOAT, M_ARRAY, &Struct->WhiteBalance);
         break;
      case 2:  /* Gain&Offset */
         DispSizeBand = SizeBand;
         DispAttribute = M_IMAGE+M_GRAB+M_DISP+M_PROC+M_HOST_MEMORY+M_FPGA_ACCESSIBLE;
         /* The gain&Offset buffers MUST reside in the Processing Fpga SDRAM memory */
         MbufAllocColor(MilSystem,
            SizeBand,
            SizeX,
            SizeY,
            ((MdigInquire(MilDigitizer, M_SIZE_BIT, M_NULL) == 8) ? 8+M_UNSIGNED : 16+M_UNSIGNED),
            M_IMAGE+M_PROC+M_FPGA_ACCESSIBLE,
            &Struct->MilGainImage);
         MbufAllocColor(MilSystem,
            SizeBand,
            SizeX,
            SizeY,
            ((MdigInquire(MilDigitizer, M_SIZE_BIT, M_NULL) == 8) ? 8+M_UNSIGNED : 16+M_UNSIGNED),
            M_IMAGE+M_PROC+M_FPGA_ACCESSIBLE,
            &Struct->MilOffsetImage);

         /* Lets clear the offset and gain buffers to a constant fro the
         purpose of this example. */
         MbufClear(Struct->MilGainImage, 16);
         MbufClear(Struct->MilOffsetImage, 2);
         break;
      case 3:  /* AddConstant */
         DispSizeBand = SizeBand;
         DispAttribute = M_IMAGE+M_GRAB+M_DISP+M_PROC+M_HOST_MEMORY+M_FPGA_ACCESSIBLE;
         break;
      }

   MbufAllocColor(MilSystem,
      DispSizeBand,
      SizeX,
      SizeY,
      8+M_UNSIGNED,
      DispAttribute,
      &Struct->MilImageDisp);

   MdispSelect(MilDisplay, Struct->MilImageDisp);
   }
