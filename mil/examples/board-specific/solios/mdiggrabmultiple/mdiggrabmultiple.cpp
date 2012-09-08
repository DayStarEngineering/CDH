/***********************************************************************************/
/*
 * File name: MDigGrabMultiple.cpp
 *
 * Synopsis:  This example performs 2 continuous grabs using the 2 digitizers
 *            of a system.
 *
 */

/* Headers. */
#include <mil.h>

/* Grab scale. */
#define GRAB_SCALE  1.0

/* Main function. */
int MosMain(void)
   {
   MIL_ID   MilApplication;
   MIL_ID   MilSystem;
   MIL_ID   MilDigitizer[2];
   MIL_ID   MilDisplay[2];
   MIL_ID   MilImageDisp[2];

   /* Allocations. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(MIL_TEXT("M_DEFAULT"), M_DEFAULT, M_DEFAULT, &MilSystem);
   MdigAlloc(MilSystem,  M_DEV0,    MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer[0]);
   MdigAlloc(MilSystem,  M_DEV1,    MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer[1]);
   MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay[0]);
   MdispAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay[1]);

   /* Allocate 2 display buffers and clear them. */
   MbufAlloc2d(MilSystem,
               (MIL_INT)(MdigInquire(MilDigitizer[0], M_SIZE_X, M_NULL)*GRAB_SCALE),
               (MIL_INT)(MdigInquire(MilDigitizer[0], M_SIZE_Y, M_NULL)*GRAB_SCALE),
               8L+M_UNSIGNED,
               M_IMAGE+M_GRAB+M_PROC+M_DISP, &MilImageDisp[0]);
   MbufClear(MilImageDisp[0], 0x0);
   MbufAlloc2d(MilSystem,
               (MIL_INT)(MdigInquire(MilDigitizer[1], M_SIZE_X, M_NULL)*GRAB_SCALE),
               (MIL_INT)(MdigInquire(MilDigitizer[1], M_SIZE_Y, M_NULL)*GRAB_SCALE),
               8L+M_UNSIGNED,
               M_IMAGE+M_GRAB+M_PROC+M_DISP, &MilImageDisp[1]);
   MbufClear(MilImageDisp[1], 0x80);

   /* Display the buffers. */
   MdispSelect(MilDisplay[0], MilImageDisp[0]);
   MdispSelect(MilDisplay[1], MilImageDisp[1]);

   /* Grab continuously on displays at the specified scale. */
   MdigControl(MilDigitizer[0], M_GRAB_SCALE, GRAB_SCALE);
   MdigGrabContinuous(MilDigitizer[0],MilImageDisp[0]);
   MdigControl(MilDigitizer[1], M_GRAB_SCALE, GRAB_SCALE);
   MdigGrabContinuous(MilDigitizer[1],MilImageDisp[1]);

   /* Print a message. */
   MosPrintf(MIL_TEXT("Press <Enter> to stop continuous grab.\n"));
   MosGetch();

   /* Halt continuous grab. */
   MdigHalt(MilDigitizer[0]);
   MdigHalt(MilDigitizer[1]);

   /* Print a message. */
   MosPrintf(MIL_TEXT("Press <Enter> to end.\n"));
   MosGetch();

   /* Free allocations. */
   MbufFree(MilImageDisp[0]);
   MbufFree(MilImageDisp[1]);
   MdispFree(MilDisplay[0]);
   MdispFree(MilDisplay[1]);
   MdigFree(MilDigitizer[0]);
   MdigFree(MilDigitizer[1]);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
   }
