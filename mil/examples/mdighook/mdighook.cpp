/*************************************************************************/
/*
 * File name: MDigHook.cpp
 *
 * Synopsis:  This grab example shows how to use the digitizer hook functions.
 *            It grabs a sequence of images using hooks and plays it back. It 
 *            also uses events to signal the end of each grab and to  
 *            annotate the buffer.
 */                                                                   
#include <mil.h>

/* Number of buffers in the sequence. */
#define NB_GRAB_MAX   22

/* Hook functions prototypes. */
MIL_INT MFTYPE GrabStart(MIL_INT, MIL_ID, void MPTYPE *);
MIL_INT MFTYPE GrabEnd(MIL_INT, MIL_ID, void MPTYPE *);

/* Hook data structure. */
typedef struct
   {
   MIL_ID        *MilImage; 
   MIL_ID        MilDigitizer;  
   MIL_ID        GrabEndEvent;
   long          NbGrabStart;
   long          NbGrabEnd;
   long          NbFrames;
   MIL_DOUBLE    Time;
   } UserDataStruct;

/* Main function. */
int MosMain(void)
{ 
   MIL_ID   MilApplication;
   MIL_ID   MilSystem     ;
   MIL_ID   MilDigitizer  ;
   MIL_ID   MilDisplay    ;
   MIL_ID   MilImage[NB_GRAB_MAX];
   MIL_ID   MilImageDisp  ;
   MIL_TEXT_CHAR FrameIndex[10];
   UserDataStruct UserStruct;
   MIL_DOUBLE TimeWait = 0.0;
   long NbFrames = 0, n=0;
         
   /* Allocate defaults. */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem, &MilDisplay, 
                                              &MilDigitizer, &MilImageDisp);

   /* Allocate and clear sequence and display images. */
   MappControl(M_ERROR, M_PRINT_DISABLE);
   for (NbFrames=0; NbFrames<NB_GRAB_MAX; NbFrames++)
      {
      MbufAlloc2d(MilSystem,  
               MdigInquire(MilDigitizer, M_SIZE_X, M_NULL),
               MdigInquire(MilDigitizer, M_SIZE_Y, M_NULL),
               M_DEF_IMAGE_TYPE,
               M_IMAGE+M_GRAB, &MilImage[NbFrames]);
      
      if (MilImage[NbFrames])
         {
         MbufClear(MilImage[NbFrames], 0xFF);
         }
      else
         break;
      }
   MappControl(M_ERROR, M_PRINT_ENABLE);

   /* Free buffers to leave space for possible temporary buffers. */
   for (n=0; n<2 && NbFrames; n++)
      {
      NbFrames--;
      MbufFree(MilImage[NbFrames]);
      }

   /* MIL event allocation for grab end hook. */
   MthrAlloc(MilSystem, M_EVENT, M_DEFAULT, M_NULL, M_NULL, &UserStruct.GrabEndEvent);
   
   /* Initialize hook structure. */
   UserStruct.MilDigitizer = MilDigitizer;
   UserStruct.MilImage     = MilImage;
   UserStruct.NbGrabStart  = -2;
   UserStruct.NbGrabEnd    = -2;
   UserStruct.NbFrames     = NbFrames;
   UserStruct.Time         =  0;

   /* Grab on display. */
   MdigGrabContinuous(MilDigitizer, MilImageDisp);
  
   /* Print a message, wait for a key press and stop the grab. */
   MosPrintf(MIL_TEXT("\nDIGITIZER HOOK:\n"));
   MosPrintf(MIL_TEXT("---------------\n\n"));
   MosPrintf(MIL_TEXT("Press <Enter> to record the sequence using grab hook.\n\n"));
   MosGetch();
   MdigHalt(MilDigitizer);
  
   /* Hook functions to grab the sequence. */
   MdigHookFunction(MilDigitizer, M_GRAB_START, GrabStart, (void *)(&UserStruct));
   MdigHookFunction(MilDigitizer, M_GRAB_END,   GrabEnd,   (void *)(&UserStruct));

   /* Put digitizer in asynchronous mode. */
   MdigControl(MilDigitizer, M_GRAB_MODE, M_ASYNCHRONOUS);

   /* Start sequence with a grab in the first buffer. */
   MdigGrab(MilDigitizer, MilImage[0]);
   
   /* At this point the CPU is free to do other tasks and the sequence will be
    * grabbed during this time. Here, the CPU will print and draw the   
    * index of the buffer grabbed before copying it to display.
    */
   while (UserStruct.NbGrabEnd < NbFrames)
     {
     long GrabEndIndex;
     
     /* Wait end of grab event */
     MthrWait(UserStruct.GrabEndEvent, M_EVENT_WAIT, M_NULL);

     /* Print the current grab index. */
     GrabEndIndex = UserStruct.NbGrabEnd-1;
     if (GrabEndIndex >= 0)
         {
         MosPrintf(MIL_TEXT("\rBuffer #%ld grabbed.   "),GrabEndIndex);
         MosSprintf(FrameIndex, 10, MIL_TEXT("%ld"), GrabEndIndex);
         MgraText(M_DEFAULT, MilImage[GrabEndIndex], 32, 32, FrameIndex);
         MbufCopy(MilImage[GrabEndIndex],MilImageDisp);
         }
     }

   /* Wait for end of last grab. */
   MdigGrabWait(MilDigitizer, M_GRAB_END);

   /* Print statistics. */
   MosPrintf(MIL_TEXT("\n\n%ld frames grabbed, at a frame rate of %.2f frames/sec ")
             MIL_TEXT("(%.2f ms/frame).\n"),UserStruct.NbGrabStart, 
                                           UserStruct.NbGrabStart/UserStruct.Time, 
                                           1000.0*UserStruct.Time/UserStruct.NbGrabStart);
          
   /* Play the sequence until <enter> is pressed. */
   MosPrintf(MIL_TEXT("Press <enter> to end the playback.\n"));
   while( !MosKbhit() )
      {
      /* Play the sequence. */
      for (n=0; n<NbFrames; n++)
         {
         /* Copy one image to the screen. */
         MappTimer(M_TIMER_RESET+M_SYNCHRONOUS, M_NULL);
         MbufCopy(MilImage[n],MilImageDisp);
         MappTimer(M_TIMER_READ+M_SYNCHRONOUS, &TimeWait);
         TimeWait = (UserStruct.Time/UserStruct.NbGrabStart) - TimeWait;
         MappTimer(M_TIMER_WAIT, &TimeWait);
         }
      }   
   MosGetch();   
      
   /* Unhook functions. */
   MdigHookFunction(MilDigitizer, M_GRAB_START+M_UNHOOK, GrabStart, (void *)(&UserStruct));
   MdigHookFunction(MilDigitizer, M_GRAB_END+M_UNHOOK, GrabEnd, (void *)(&UserStruct));

   /* Free event. */
   MthrFree(UserStruct.GrabEndEvent);
   
   /* Free allocations. */
   for (n=0; n<NbFrames; n++)
      {
      MbufFree(MilImage[n]);
      }
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, MilDigitizer, MilImageDisp);

   return 0;
}  


/* Grab Start hook function: 
 *      - This function is used to queue a grab at the beginning of
 *        the each current grab.
 *      - It is also used to measure the frame rate. This is done 
 *        by starting a timer at the beginning of a dummy grab and 
 *        by stopping the timer at the beginning of the last grab.  
 */
MIL_INT MFTYPE GrabStart(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserStructPtr)
{
  UserDataStruct *UserPtr=(UserDataStruct*)UserStructPtr;

  /* Increment grab start count. */
  UserPtr->NbGrabStart++;

  /* Start the timer when needed. */
  if(UserPtr->NbGrabStart == 0)
  	 MappTimer(M_TIMER_RESET+M_GLOBAL, (MIL_DOUBLE *)&UserPtr->Time);
     
  /* Queue a new grab or stop the timer at the end. */
  if (UserPtr->NbGrabStart < UserPtr->NbFrames)
     MdigGrab(UserPtr->MilDigitizer, 
              UserPtr->MilImage[(UserPtr->NbGrabStart < 0) ? 0 : UserPtr->NbGrabStart]);
  else   
     MappTimer(M_TIMER_READ+M_GLOBAL, (MIL_DOUBLE *)&UserPtr->Time);
        
  return(0);
}


/* Grab end hook function: 
 *      - This function is used to signal to a waiting thread (here the main())
 *        that a grab is completed and that the data can be processed.
 *
 *  Note: Time spend in the hook function should be minimal. External 
 *	      thread waiting on an event should be used to do processing.
 */
MIL_INT MFTYPE GrabEnd(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserStructPtr)
{
  UserDataStruct *UserPtr=(UserDataStruct*)UserStructPtr;
  
  /* Increment grab count. */
  UserPtr->NbGrabEnd++;
        
  /* Signal the end of grab event to the main thread waiting. */
  MthrControl(UserPtr->GrabEndEvent, M_EVENT_SET, M_SIGNALED);
  
  return(0);
}

