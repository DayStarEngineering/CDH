/*****************************************************************************************/
/*
 * File name: MFunc.cpp 
 *
 * Synopsis:  This example shows the use of the MIL Function Developer Tool Kit and how 
 *			  MIL and custom code can be mixed to create a custom MIL function that 
 *			  accesses the data pointer of a MIL buffer directly in order to process it.
 *
 *            The example creates a Master MIL function that registers all the parameters 
 *		      to MIL and calls the Slave function. The Slave function retrieves all the 
 *			  parameters, gets the pointers to the MIL image buffers, uses them to access 
 *			  the data directly and adds a constant.
 *             
 *            Note: The images must be 8-bit unsigned.
 */
#include <mil.h>

/* MIL function specifications. */
#define FUNCTION_NB_PARAM                 3
#define FUNCTION_OPCODE_ADD_CONSTANT      1 
#define FUNCTION_PARAMETER_ERROR_CODE     1
#define FUNCTION_SUPPORTED_IMAGE_TYPE     (8+M_UNSIGNED)

/* Target image file name. */
#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("BoltsNutsWashers.mim")

/* Master and Slave MIL functions declarations. */
void AddConstant(MIL_ID SrcImageId, MIL_ID DstImageId, MIL_INT ConstantToAdd);
void MFTYPE SlaveAddConstant(MIL_ID Func);


/* Master MIL Function definition. */
/* ------------------------------- */

void AddConstant(MIL_ID SrcImageId, MIL_ID DstImageId, MIL_INT ConstantToAdd)
{
   MIL_ID   Func;

   /* Allocate a MIL function context that will be used to call a target 
      Slave function locally on the Host to do the processing.
   */
   MfuncAlloc(MIL_TEXT("AddConstant"), 
              FUNCTION_NB_PARAM,
              SlaveAddConstant, M_NULL, M_NULL, 
              M_USER_MODULE_1+FUNCTION_OPCODE_ADD_CONSTANT, 
              M_LOCAL, 
              &Func
             );

   /* Register the parameters. */
   MfuncParamId(    Func, 1, SrcImageId, M_IMAGE, M_IN);
   MfuncParamId(    Func, 2, DstImageId, M_IMAGE, M_OUT);
   MfuncParamMilInt(Func, 3, ConstantToAdd);

   /* Call the target Slave function. */
   MfuncCall(Func);

   /* Free the MIL function context. */
   MfuncFree(Func);
}


/* MIL Slave function definition. */
/* ------------------------------ */

void MFTYPE SlaveAddConstant(MIL_ID Func)
{
  MIL_ID    SrcImageId, DstImageId;
  MIL_INT   ConstantToAdd, TempValue;
  unsigned  char *SrcImageDataPtr, *DstImageDataPtr;
  MIL_INT   SrcImageSizeX, SrcImageSizeY, SrcImageType, SrcImagePitchByte;
  MIL_INT   DstImageSizeX, DstImageSizeY, DstImageType, DstImagePitchByte;
  MIL_INT   x, y;

  /* Read the parameters. */
  MfuncParamValue(Func, 1, &SrcImageId);
  MfuncParamValue(Func, 2, &DstImageId);
  MfuncParamValue(Func, 3, &ConstantToAdd); 

  /* Lock buffers for direct access. */
  MbufControl(SrcImageId, M_LOCK, M_DEFAULT);
  MbufControl(DstImageId, M_LOCK, M_DEFAULT);

  /* Read image information. */
  MbufInquire(SrcImageId, M_HOST_ADDRESS, &SrcImageDataPtr);
  MbufInquire(SrcImageId, M_SIZE_X,       &SrcImageSizeX);
  MbufInquire(SrcImageId, M_SIZE_Y,       &SrcImageSizeY);
  MbufInquire(SrcImageId, M_TYPE,         &SrcImageType);
  MbufInquire(SrcImageId, M_PITCH_BYTE,   &SrcImagePitchByte);
  MbufInquire(DstImageId, M_HOST_ADDRESS, &DstImageDataPtr);
  MbufInquire(DstImageId, M_SIZE_X,       &DstImageSizeX);
  MbufInquire(DstImageId, M_SIZE_Y,       &DstImageSizeY);
  MbufInquire(DstImageId, M_TYPE,         &DstImageType);
  MbufInquire(DstImageId, M_PITCH_BYTE,   &DstImagePitchByte);

  /* Reduce the destination area to process if necessary. */
  if (SrcImageSizeX < DstImageSizeX)   DstImageSizeX = SrcImageSizeX;
  if (SrcImageSizeY < DstImageSizeY)   DstImageSizeY = SrcImageSizeY;

  /* If images have the proper depth, perform the operation using a custom C code. */
  if ((SrcImageType == DstImageType) && (SrcImageType == FUNCTION_SUPPORTED_IMAGE_TYPE))
     {
     /* Add the constant to the image. */
     for (y= 0; y < DstImageSizeY; y++)
        {
        for (x= 0; x < DstImageSizeX; x++) 
           {
           /* Calculate the value to write. */
           TempValue = (MIL_INT)SrcImageDataPtr[x] + (MIL_INT)ConstantToAdd;

           /* Write the value if no overflow, else saturate. */
           if (TempValue <= 0xff)
              DstImageDataPtr[x] = (unsigned char)TempValue;
           else 
              DstImageDataPtr[x] = 0xff;
           }

         /* Move pointer to the next line taking into account the image's pitch. */
         SrcImageDataPtr += SrcImagePitchByte;
         DstImageDataPtr += SrcImagePitchByte;
        }
     }
  else 
     {  
     /* Report a MIL error. */
     MfuncErrorReport(Func,M_FUNC_ERROR+FUNCTION_PARAMETER_ERROR_CODE,
                      MIL_TEXT("Invalid parameter."),
                      MIL_TEXT("Image type not supported"),
                      MIL_TEXT("Image depth must be 8-bit."),
                      M_NULL
                     );
     }

  /* Unlock buffers. */
  MbufControl(SrcImageId, M_UNLOCK, M_DEFAULT);
  MbufControl(DstImageId, M_UNLOCK, M_DEFAULT);

  /* Signal to MIL that the buffers are now in cache (required by Odyssey). */
  MbufControl(SrcImageId, M_CACHE_CONTROL, M_IN_CACHE); 
  MbufControl(DstImageId, M_CACHE_CONTROL, M_IN_CACHE); 

  /* Signal to MIL that the destination buffer was modified. */
  MbufControl(DstImageId, M_MODIFIED, M_DEFAULT); 
}


/* Main to test the custom function. */
/* --------------------------------- */

int MosMain(void)
{
   MIL_ID MilApplication,    /* Application identifier.    */
          MilSystem,         /* System identifier.         */
          MilDisplay,        /* Display identifier.        */
          MilImage;          /* Image buffer identifier.   */
   void* ImageHostAddress;   /* Image buffer host address. */

   /* Allocate default application, system, display and image. */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem,
                                &MilDisplay, M_NULL, M_NULL);

   /* Load source image into a Host memory image buffer. */
   MbufAlloc2d(MilSystem, 
               MbufDiskInquire(IMAGE_FILE, M_SIZE_X, M_NULL), 
               MbufDiskInquire(IMAGE_FILE, M_SIZE_Y, M_NULL), 
               8+M_UNSIGNED, 
               M_IMAGE+M_DISP+M_HOST_MEMORY,
               &MilImage);   
   MbufLoad(IMAGE_FILE, MilImage);

   MbufControl(MilImage, M_LOCK, M_DEFAULT);
   MbufInquire(MilImage, M_HOST_ADDRESS, &ImageHostAddress);
   MbufControl(MilImage, M_UNLOCK, M_DEFAULT);

   if(ImageHostAddress != M_NULL)
      {
      /* Display the image. */
      MdispSelect(MilDisplay, MilImage);
      
      /* Pause. */
      MosPrintf(MIL_TEXT("\nMIL FUNCTION DEVELOPER'S TOOLKIT:\n"));
      MosPrintf(MIL_TEXT("----------------------------------\n\n"));
      MosPrintf(MIL_TEXT("This example creates a custom MIL function that processes\n"));
      MosPrintf(MIL_TEXT("an image using its data pointer directly.\n\n"));
      MosPrintf(MIL_TEXT("Target image was loaded.\n"));
      MosPrintf(MIL_TEXT("Press a key to continue.\n\n"));
      MosGetch();

      /* Process the image directly with the custom MIL function. */
      AddConstant(MilImage, MilImage, 0x40);
      
      /* Pause */
      MosPrintf(MIL_TEXT("The white level of the image was augmented.\n"));
      }
   else
      {
      MosPrintf(MIL_TEXT("This example cannot be run with this system.\n"));
      }

   MosPrintf(MIL_TEXT("Press a key to terminate.\n\n"));
   MosGetch();

   /* Free all allocations. */
   MbufFree(MilImage);
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);

   return 0;
}
