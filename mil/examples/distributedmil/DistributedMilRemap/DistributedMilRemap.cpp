/*****************************************************************************************/
/*
 * File name: DistributedMilRemap.cpp
 *
 * Synopsis:  This example shows how to use the MIL Function Development module to 
 *            create a custom asynchronous MIL function that does a series of MIL 
 *            commands on a target system in a single call from the host. The function 
 *            shows how to avoid having the Host to wait for remote calculation result 
 *            and also show how to reduce the overhead of sending multiple commands by
 *            grouping them in a meta MIL function. 
 *
 *            The example creates a Master MIL function that register all the parameters
 *            to MIL and calls the Slave function on the target system. The Slave function 
 *            retrieves all the parameters, finds the Max and Min of the source buffer and 
 *            remaps it to have its full range (min at 0x0 and the max at 0xFF).
 *
 *            The slave function can be found in the DistributedMilRemapSlave project.
 *             
 *            Note: For simplicity, the images are assumed to be 8-bit unsigned.
 */

/* MIL Header. */
#include <mil.h>

/* Master MIL functions declarations */
void MFTYPE CustomRemap(MIL_ID SrcImage, MIL_ID DstImage, unsigned long Option);

/* Compile the main() on the HOST only. */
#if !M_MIL_USE_PPC

/* Standard I/0 */

/* Target image file name */
#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("Wafer.mim")

/* Slave IP adress and system */
#define SLAVE_IP_ADDRESS         MIL_TEXT("127.0.0.1")
#define SLAVE_SYSTEM             M_SYSTEM_DEFAULT

/* Build slave system descriptor.  Use preprocessor behavior that */
/* concatenates adjacent strings in a single string.              */
/* Format of descriptor is: protocol://address/system             */
/* Eg.: dmiltcp://127.0.0.1/M_SYSTEM_HOST                          */
#define SLAVE_SYSTEM_DESCRIPTOR  M_DMILTCP_TRANSPORT_PROTOCOL MIL_TEXT("://") SLAVE_IP_ADDRESS MIL_TEXT("/") SLAVE_SYSTEM

/* Main to test the function. */
/* -------------------------- */

int MosMain(void)
{
   MIL_ID MilApplication,    /* Application Identifier.  */
          MilSystem,         /* System Identifier.       */
          MilDisplay,        /* Display Identifier.      */
          MilImage;          /* Image buffer Identifier. */
   
   /* Allocate application, system and display. */
   MappAlloc(M_DEFAULT, &MilApplication);
   MsysAlloc(SLAVE_SYSTEM_DESCRIPTOR, M_DEF_SYSTEM_NUM, M_SETUP, &MilSystem);
   MdispAlloc(MilSystem, M_DEV0, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDisplay);

   /* Restore source image into an automatically allocated image buffer. */
   MbufRestore(IMAGE_FILE, MilSystem, &MilImage);
  
   /* Display the image. */
   MdispSelect(MilDisplay, MilImage);
   
   /* Pause */
   MosPrintf(MIL_TEXT("\nMIL DTK:\n"));
   MosPrintf(MIL_TEXT("--------\n\n"));
   MosPrintf(MIL_TEXT("Custom asynchronous processing function:\n\n"));
   MosPrintf(MIL_TEXT("This example creates a custom MIL function that maximize the contrast.\n"));
   MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
   MosGetch();

   /* Process the image with the custom MIL function. */
   CustomRemap(MilImage, MilImage, M_DEFAULT);
   
   /* Pause */
   MosPrintf(MIL_TEXT("A smart image remapping was done on the image using a user made MIL function.\n"));
   MosPrintf(MIL_TEXT("Press a key to terminate.\n\n"));
   MosGetch();

   /* Free all allocations. */
   MbufFree(MilImage);
   MdispFree(MilDisplay);
   MsysFree(MilSystem);
   MappFree(MilApplication);

   return 0;
}

#endif /* !M_MIL_USE_PPC */


/* Master MIL Function definition. */
/* ------------------------------- */

/* MIL Function specifications */
#define FUNCTION_OPCODE_REMAP   (M_USER_FUNCTION+1)
#define FUNCTION_NB_PARAM       3

/* Slave function name and DLL path */
#define SLAVE_FUNC_NAME      MIL_TEXT("SlaveCustomRemap")
#define SLAVE_DLL_NAME       MIL_TEXT("DistributedMilRemapSlave.dll")

void MFTYPE CustomRemap(MIL_ID SrcImage, MIL_ID DstImage, unsigned long Option)
{
   MIL_ID   Func;
   
   /* Allocate a MIL function context that will be used to call a target 
      slave function to do the processing.
   */
   MfuncAlloc(MIL_TEXT("CustomRemap"), 
              FUNCTION_NB_PARAM,
              M_NULL, SLAVE_DLL_NAME, SLAVE_FUNC_NAME,  
              FUNCTION_OPCODE_REMAP, 
              M_ASYNCHRONOUS_FUNCTION, 
              &Func);

   /* Register the parameters. */
   MfuncParamId(  Func, 1, SrcImage, M_IMAGE, M_IN  + M_PROC);
   MfuncParamId(  Func, 2, DstImage, M_IMAGE, M_OUT + M_PROC);
   MfuncParamLong(Func, 3, Option);

   /* Call the target Slave function. */
   MfuncCall(Func);

   /* Free the MIL function context. */
   MfuncFree(Func);
}
