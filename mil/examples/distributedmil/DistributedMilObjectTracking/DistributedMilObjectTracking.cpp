/**********************************************************************************/
/*
 *  File name: DistributedMilObjectTracking.cpp
 *
 *  Synopsis:  This example uses DistributedMIL to create an autonomous processing
 *             loop that runs directly on target system. The processing loop does 
 *             object tracking.
 *
 *             To optimize the processing and free the Host cpu, the function will run 
 *             completely on the target system and do the complete grab and model search 
 *             job in real time instead of sending each individual commands from the Host. 
 *             The results of each search will be returned in lot at each processing loop 
 *             in a shared Data Exchange structure copied from the Target system to the Host.
 *             
 *             The example will first do a grab controlled from the Host to define the model. 
 *             After it will start the autonomous processing function to follow the model on 
 *             the target system while printing the results and displaying the 
 *             annotated images on the Host.
 *
 *             The slave function can be found in the DistributedMILSyncAsyncRemapSlave project.
 */

/* MIL Header. */
#include <mil.h> 

/* Specify which pattern matching type to use (choose one). */
#define GEOMETRIC        0
#define GRAYSCALE        1
#define PATTERN_MATCHING_METHOD GRAYSCALE  


/* Specify where the Slave processing loop will be run (choose one). */
#define TARGET_PLATFORM      M_NULL   /* Automatic choice.           */
//#define TARGET_PLATFORM    M_LOCAL  /* Force Slave to run on Host. */
//#define TARGET_PLATFORM    M_REMOTE /* Force Slave to run on remote system.  */

/* Flag to update the display and draw the position found while processing. */
#define DISPLAY_UPDATE        M_YES

/* Target model specifications. */
#define MODEL_MIN_MATCH_SCORE 50.0

/* Number of grab images for Mdigprocess(). */
#define NB_TARGET_IMAGES      4

/* Slave IP adress and system */
#define SLAVE_IP_ADDRESS         MIL_TEXT("127.0.0.1")
#define SLAVE_SYSTEM             M_SYSTEM_DEFAULT

/* Build slave system descriptor.  Use preprocessor behavior that */
/* concatenates adjacent strings in a single string.              */
/* Format of descriptor is: protocol://address/system             */
/* Eg.: dmiltcp://127.0.0.1/M_SYSTEM_HOST                          */
#define SLAVE_SYSTEM_DESCRIPTOR  M_DMILTCP_TRANSPORT_PROTOCOL MIL_TEXT("://") SLAVE_IP_ADDRESS MIL_TEXT("/") SLAVE_SYSTEM

/* Processing functions prototypes. */
MIL_UINT32 MFTYPE PatternMatchingLoop(void *MilDataExchangeBuffer);

/* Data Exchange structure between Host and Target processors. */
typedef struct
   {
   MIL_ID MilSystem;
   MIL_ID MilDisplay;
   MIL_ID MilDigitizer;
   MIL_ID MilImageDisp;
   MIL_ID MilImage[NB_TARGET_IMAGES]; 
   MIL_ID MilThread;
   MIL_ID MilDataExchangeBuffer; 
   MIL_ID MilDataExchangeBufferReadyEvent; 
   MIL_ID MilModelPositionOkEvent;
   MIL_ID MilStopProcessingEvent;
   MIL_ID MilModel;           
   MIL_ID MilResult;   
   MIL_INT32 PatternMatchingMethod;
   MIL_INT32 DisplayUpdateFlag;
   MIL_INT32 Found;
   MIL_DOUBLE PosX;
   MIL_DOUBLE PosY;
   MIL_DOUBLE Score;
   MIL_DOUBLE Time;
   MIL_INT32 NbFindDone;
   MIL_INT32 Error;
   } DataExchangeStruct;

/* Host MbufHookFunction() prototype. */
MIL_INT MFTYPE DataExchangeBufferModified(MIL_INT, MIL_ID, void MPTYPE *);


/******************************************************************************/
/* main function. */
int MosMain(void)
{ 
#if (!M_MIL_LITE)
   /* Variables declaration */
   MIL_ID             MilApplication;
   DataExchangeStruct DataEx;
   long               i=0;
   long               Error = 0;
   long               NbGrab     = 0;
   MIL_DOUBLE         Time       = 0.0;

   /* Allocate MIL objects. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(SLAVE_SYSTEM_DESCRIPTOR, M_DEFAULT, M_DEFAULT, &DataEx.MilSystem);
   MdispAlloc(DataEx.MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &DataEx.MilDisplay);
   MdigAlloc(DataEx.MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &DataEx.MilDigitizer);
   MbufAlloc2d(DataEx.MilSystem,  
               MdigInquire(DataEx.MilDigitizer, M_SIZE_X, M_NULL),
               MdigInquire(DataEx.MilDigitizer, M_SIZE_Y, M_NULL),
               8L+M_UNSIGNED, 
               M_IMAGE+M_PROC+M_DISP+M_GRAB, &DataEx.MilImageDisp);
   MthrAlloc(DataEx.MilSystem, M_EVENT, M_NOT_SIGNALED+M_AUTO_RESET, 
             M_NULL, M_NULL, &DataEx.MilModelPositionOkEvent);
   MthrAlloc(DataEx.MilSystem, M_EVENT, M_NOT_SIGNALED+M_AUTO_RESET, 
             M_NULL, M_NULL, &DataEx.MilStopProcessingEvent);
   MthrAlloc(DataEx.MilSystem, M_EVENT, M_SIGNALED    +M_AUTO_RESET, 
             M_NULL, M_NULL, &DataEx.MilDataExchangeBufferReadyEvent);

   /* Initialize the display */
   MbufClear(DataEx.MilImageDisp, 0x0);            
   MdispSelect(DataEx.MilDisplay, DataEx.MilImageDisp);

   /* Allocate a MIL array buffer for the Data Exchange structure with the Target
      system. This data will include the Target processing results which will be 
      read in a single faster MbufGet() operation.
   */
   MbufAlloc1d(DataEx.MilSystem, sizeof(DataExchangeStruct), 
               8L+M_UNSIGNED, M_ARRAY, &DataEx.MilDataExchangeBuffer);

   /* Specify to update the display with the model position found. */
   DataEx.DisplayUpdateFlag = DISPLAY_UPDATE;

   /* Specify which type of pattern matching to perform. */
   DataEx.PatternMatchingMethod = PATTERN_MATCHING_METHOD;

   /* Initialize the MIL Data Exchange buffer with the structure. */
   MbufPut(DataEx.MilDataExchangeBuffer, &DataEx);
   
   /* Hook a callback function to the Data Exchange buffer modification 
      to get the result on the Host. 
   */
   MbufHookFunction(DataEx.MilDataExchangeBuffer, M_MODIFIED_BUFFER, 
                    DataExchangeBufferModified, &DataEx.MilDataExchangeBuffer);

   /* START THE TARGET PROCESSING PROCEDURE:
      This function will allocate and start an autonomous thread on the remote system 
      that will run the pattern matching procedure autonomously on the target system.
   */
   MthrAlloc(DataEx.MilSystem, M_THREAD, M_DEFAULT, PatternMatchingLoop, 
             &DataEx.MilDataExchangeBuffer, &DataEx.MilThread);

   /* Here the Host is free to do any other task. The processing loop is running 
      autonomously, grabbing and waiting for the Host to signal that the 
      Target Model is properly positionned. It will then define the model and 
      start the processing.
   */

   /* Print a user message and wait for good model position. */
   MosPrintf(MIL_TEXT("\nMIL DTK:\n"));
   MosPrintf(MIL_TEXT("--------\n\n"));
   MosPrintf(MIL_TEXT("Distributed object tracking:\n\n"));
   MosPrintf(MIL_TEXT("Place the rectangle on the model to be found.\n"));
   MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
   MosGetch();   

   /* Set the Model Position Ok Event to allocate model and start the procesing. */
   MthrControl(DataEx.MilModelPositionOkEvent, M_EVENT_SET, M_SIGNALED);

   /* Print a user message to announce the processing loop. */
   MosPrintf(MIL_TEXT("Finding the model using an autonomous user-defined function.\n"));
   MosPrintf(MIL_TEXT("Press a key to stop processing.\n\n"));

   /* Here the Host is free to do any other task again. The processing loop 
      is running autonomously and passing the necessary results to the Host via the
      data exchange buffer. The host is called in a separate thread via its buffer 
      hook function each time new results are written by the processing procedure to 
      print the results and statistics.
   */

   /* Wait for a key. */
   MosGetch();

   /* Stop the processing loop. */
   MthrControl(DataEx.MilStopProcessingEvent, M_EVENT_SET, M_SIGNALED);

   /* Wait for processing thread to be completed before freeing the MIL objects. */
   MthrWait(DataEx.MilThread, M_THREAD_END_WAIT, M_NULL);

   /* Unhook the Data exchange buffer modifications */
   MbufHookFunction(DataEx.MilDataExchangeBuffer, M_MODIFIED_BUFFER+M_UNHOOK, 
                    DataExchangeBufferModified, &DataEx.MilDataExchangeBuffer);

   /* Free allocations. */
   MthrFree(DataEx.MilDataExchangeBufferReadyEvent);
   MthrFree(DataEx.MilStopProcessingEvent);
   MthrFree(DataEx.MilModelPositionOkEvent);
   MthrFree(DataEx.MilThread);
   MbufFree(DataEx.MilDataExchangeBuffer);
   MbufFree(DataEx.MilImageDisp);
   MdispFree(DataEx.MilDisplay);
   MdigFree(DataEx.MilDigitizer);
   MsysFree(DataEx.MilSystem);
   MappFree(MilApplication);
#else
   MosPrintf(MIL_TEXT("This example needs a full installation of MIL\n"));
   MosPrintf(MIL_TEXT("Press a key to end\n\n"));
   MosGetch();
#endif

   return 0;
}  


/****************************************************************************** 
 * Data Modified hook function: 
 *      - This function is used to print the position of the model found. It gets 
 *        called each time new results are written in the Data Exchange Buffer.
 *
 *  Note: Time spend in the hook function should be minimal. External 
 *        thread waiting on an event should be used to do long processing
 *        otherwise the processing loop will be waiting to continue.
 */
MIL_INT MFTYPE DataExchangeBufferModified(MIL_INT HookType, MIL_ID EventId, void MPTYPE *DataExchangeIdPtr)
{
   /* Variables declaration. */
   DataExchangeStruct DataEx;
   
   /* Get the pattern matching results by reading the Data Exchange structure. */
   MbufGet(*(MIL_ID *)DataExchangeIdPtr, &DataEx);
   
   /* Set the Buffer Ready event to signal to the Target system that the results were read. */
   MthrControl(DataEx.MilDataExchangeBufferReadyEvent, M_EVENT_SET, M_SIGNALED);
   
   /* Print the model search results and processing statistics. */
   if (DataEx.Found)
      {
      MosPrintf(MIL_TEXT("Search #%ld: X=%-6.2f, Y=%-6.2f, Score=%5.1f %%, Frame rate=%.1f fps. \r"),
              DataEx.NbFindDone, DataEx.PosX, DataEx.PosY, DataEx.Score, DataEx.NbFindDone/DataEx.Time);
      }
   else
      {
      MosPrintf(MIL_TEXT("Search #%ld: Model not found: Score<%5.1f %%, Frame rate=%.1f fps.    \r"), 
              DataEx.NbFindDone, MODEL_MIN_MATCH_SCORE, DataEx.NbFindDone/DataEx.Time);
      }

   /* return successful completion status */
   return(M_NULL);
}



/******************************************************************************
 *  Master MIL function: 
 *      - This function is used to launch the execution of a group of MIL 
 *        functions on a Target system. This function grabs and processes
 *        in double buffering mode on the Target system without sending every 
 *        MIL command individually from the Host computer. This has the great 
 *        advantages of reducing the Host and Target CPU usage, the command 
 *        send and result get overhead, the processing time and latency.
 *
 *        Although it can be called directly, we defined the function prototype 
 *        to be compatible with MappControlThead(..., M_THREAD_CREATE, ...) to 
 *        be able to start it in a separate thread on the Host and on the Odyssey.
 */

/* Function Parameters */
#define PATTERN_MATCHING_LOOP     (M_USER_FUNCTION+7)
#define NB_PARAMETERS             1

/* Slave function name and DLL path */
#define SLAVE_FUNC_NAME      MIL_TEXT("SlavePatternMatchingLoop")
#define SLAVE_DLL_NAME       MIL_TEXT("DistributedMilObjectTrackingSlave.dll")

MIL_UINT32 MFTYPE PatternMatchingLoop(void *MilDataExchangeBuffer)
   {
   /* Variables declaration */
   MIL_ID  Func;
   
   /* Allocate a Custom MIL function that will call a Target work function 
      to do the real processing job on the Target computer.
   */
   MfuncAlloc(MIL_TEXT("PatternMatchingLoop"), 
              NB_PARAMETERS,
              M_NULL, SLAVE_DLL_NAME, SLAVE_FUNC_NAME, 
              PATTERN_MATCHING_LOOP, 
              M_SYNCHRONOUS_FUNCTION+TARGET_PLATFORM, 
              &Func);
   
   /* Register the function parameters. */
   MfuncParamId(Func, 1, *(MIL_ID *)MilDataExchangeBuffer, M_ARRAY, M_IN+M_OUT);
      
   /* Call the Slave processing function on the Target system. */
   MfuncCall(Func);
       
   /* Mark the end of the function. */
   MfuncFree(Func);

   /* Thread return value. */
   return(M_TRUE);
   }
