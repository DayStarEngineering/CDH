/***************************************************************************/
/*

    Filename:  MILERR.H
    Owner   :  Matrox Imaging dept.
    Revision:  9.02.0812
    Content :  This file contains the defines that are used by the
               mil functions to generate error codes and messages that
               will be used by the MIL Application Error Logging and
               other error related functions.

    Copyright © Matrox Electronic Systems Ltd., 1992-2011.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef  __MILERR_H
#define  __MILERR_H

/*
First line is the error code.
Second line is the error message for this code.
Other 9 lines are optional sub-messages with more detailed information.

------------------------------------------------------------------------
-                                                                      -
-  WARNING: Strings (including the NULL character at the end) should   -
-           never be longer than M_ERROR_MESSAGE_SIZE (128L).          -
-           No checking is done anywhere in the code to ensure this.   -
-                                                                      -
------------------------------------------------------------------------
*/


#define NO_MSG                   MIL_TEXT("")  /* empty error message          */
#define NO_SUBMSG                MIL_TEXT("")  /* empty sub-error message      */
#define NO_FCTNAME               MIL_TEXT("")  /* empty function name          */

// The following define must be set to a value higher
// than the error subcode range. For now, error subcode
// range is 1-9. M_NBSUBERRMSGMAX is 10.
#define M_SYSTEM_STRING_CODE     M_NBSUBERRMSGMAX

// ActiveMIL
// ychenard - 15/08/2000
// Please use the MILOCX_COMPILATION to remove any function definition from this file
// when not compiling ActiveMIL.
// This is a hack from us to include the low-level error messages from MIL.
// If MIL cleans up the error handling some day, please contact the ActiveMIL team.
// 
//   NOTE: if you add anything else than defines in this file, please put them 
//         within a "#ifndef MILOCX_COMPILATION" block.
#ifndef MILERR
   #define MILERR(Fake1, Fake2, Fake3, Fake4, Fake5)
#endif

/* LIST OF ERROR CODES AND MESSAGES */

#define M_NULL_ERROR             0L
#define M_ERR_0_MSG              MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_1         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_2         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_3         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_4         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_5         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_6         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_7         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_8         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_9         MIL_TEXT("Null.")

#define M_SIMD_ERROR_1           1L
#define M_ERR_1_MSG              MIL_TEXT("SIMD Error.")
#define M_ERR_1_SUBMSG_1         MIL_TEXT("Cannot force MMX on a non-MMX CPU.")
#define M_ERR_1_SUBMSG_2         MIL_TEXT("Cannot force SSE on a non-SSE CPU or the OS does not support SSE.")
#define M_ERR_1_SUBMSG_3         MIL_TEXT("Cannot force SSE2 on a non-SSE2 CPU or the OS does not support SSE2.")
#define M_ERR_1_SUBMSG_4         MIL_TEXT("Cannot force 3DNow on a non-3DNow CPU.")
#define M_ERR_1_SUBMSG_5         MIL_TEXT("Cannot force MMX Extension on a non-MMX Extenion CPU.")
#define M_ERR_1_SUBMSG_6         MIL_TEXT("Cannot force 3DNow Extension on a non-3DNow Extenion CPU.")
#define M_ERR_1_SUBMSG_7         MIL_TEXT("Cannot force SSE3 on a non-SSE3 CPU or the OS does not support SSE3.")
#define M_ERR_1_SUBMSG_8         MIL_TEXT("Cannot force SSE4 on a non-SSE4 CPU or the OS does not support SSE4.")
#define M_ERR_1_SUBMSG_9         NO_SUBMSG

#define M_SIMD_ERROR_2           2L
#define M_ERR_2_MSG              MIL_TEXT("SIMD Error.")
#define M_ERR_2_SUBMSG_1         MIL_TEXT("Cannot force Altivec on a non-Altivec CPU.")
#define M_ERR_2_SUBMSG_2         NO_SUBMSG
#define M_ERR_2_SUBMSG_3         NO_SUBMSG
#define M_ERR_2_SUBMSG_4         NO_SUBMSG
#define M_ERR_2_SUBMSG_5         NO_SUBMSG
#define M_ERR_2_SUBMSG_6         NO_SUBMSG
#define M_ERR_2_SUBMSG_7         NO_SUBMSG
#define M_ERR_2_SUBMSG_8         NO_SUBMSG
#define M_ERR_2_SUBMSG_9         NO_SUBMSG

#define M_FUNC_FCT_ERROR         3L
#define M_ERR_3_MSG              MIL_TEXT("Function call error.")
#define M_ERR_3_SUBMSG_1         MIL_TEXT("MappGetError cannot be called from inside a MIL function. Use MfuncGetError instead.")
#define M_ERR_3_SUBMSG_2         MIL_TEXT("Unable to obtain information about the slave function.")
#define M_ERR_3_SUBMSG_3         MIL_TEXT("Node selected is not a valid node.")
#define M_ERR_3_SUBMSG_4         MIL_TEXT("Cannot execute because an object resides in another workspace than the system selected to perform the call.")
#define M_ERR_3_SUBMSG_5         NO_SUBMSG
#define M_ERR_3_SUBMSG_6         NO_SUBMSG
#define M_ERR_3_SUBMSG_7         NO_SUBMSG
#define M_ERR_3_SUBMSG_8         NO_SUBMSG
#define M_ERR_3_SUBMSG_9         NO_SUBMSG

#define M_OPERATION_ERROR_5      4L
#define M_ERR_4_MSG              MIL_TEXT("Operation error.")
#define M_ERR_4_SUBMSG_1         MIL_TEXT("Buffer(s) must be unlocked before calling processing functions.")
#define M_ERR_4_SUBMSG_2         MIL_TEXT("Cannot retrieve the system decoder for shadow allocation.")
#define M_ERR_4_SUBMSG_3         MIL_TEXT("This lock type is not allowed on a buffer with GPU access only.")
#define M_ERR_4_SUBMSG_4         MIL_TEXT("The buffer must be unlocked before calling MbufControl.")
#define M_ERR_4_SUBMSG_5         MIL_TEXT("This operation cannot be forced to be executed from a specific node.")
#define M_ERR_4_SUBMSG_6         MIL_TEXT("Node selected is not a valid node.")
#define M_ERR_4_SUBMSG_7         MIL_TEXT("The graphic edition is not supported for this graphic element.")
#define M_ERR_4_SUBMSG_8         MIL_TEXT("No bounding box could be found.")
#define M_ERR_4_SUBMSG_9         MIL_TEXT("No neighbor could be found.")

#define M_OPERATION_ERROR_4      5L
#define M_ERR_5_MSG              MIL_TEXT("Operation error.")
#define M_ERR_5_SUBMSG_1         MIL_TEXT("Cannot unlock an unlocked mutex.")
#define M_ERR_5_SUBMSG_2         MIL_TEXT("Cannot free a mutex that still locked.")
#define M_ERR_5_SUBMSG_3         MIL_TEXT("Error while locking the mutex.")
#define M_ERR_5_SUBMSG_4         MIL_TEXT("Error while unlocking the mutex.")
#define M_ERR_5_SUBMSG_5         MIL_TEXT("Error while freeing the mutex.")
#define M_ERR_5_SUBMSG_6         MIL_TEXT("Deinterlacing is not supported on Odyssey systems.")
#define M_ERR_5_SUBMSG_7         MIL_TEXT("MimLocatePeak1d is not supported on Odyssey systems.")
#define M_ERR_5_SUBMSG_8         MIL_TEXT("MimDraw is not supported on Odyssey systems.")
#define M_ERR_5_SUBMSG_9         MIL_TEXT("No file selected by user.")

#define M_INVALID_PARAM_ERROR    6L
#define M_ERR_6_MSG              MIL_TEXT("Invalid parameter.")
#define M_ERR_6_SUBMSG_1         MIL_TEXT("Bad parameter value.")
#define M_ERR_6_SUBMSG_2         MIL_TEXT("One of the parameters does not reside within the buffer's limits.")
MILERR( M_ERR,6,SUBMSG,2,        MIL_TEXT("One of the parameters does not reside within the limits."))
#define M_ERR_6_SUBMSG_3         MIL_TEXT("The pointer should not be null.")
/* WARNING: Obsolete sub errors (4,5); if you want to use these, notify ActiveMIL team */
#define M_ERR_6_SUBMSG_4         MIL_TEXT("Parameter 1 not supported.")
#define M_ERR_6_SUBMSG_5         MIL_TEXT("Parameter 2 not supported.")
#define M_ERR_6_SUBMSG_6         MIL_TEXT("No graphic text font selected.")
MILERR( M_ERR,6,SUBMSG,6,        MIL_TEXT("No GraphicContext font selected."))
#define M_ERR_6_SUBMSG_7         MIL_TEXT("The member StructSize from the MILBUFFERINFOOLD structure which was given as an argument is invalid.")
#define M_ERR_6_SUBMSG_8         MIL_TEXT("The result buffer is too small to hold the result.")
#define M_ERR_6_SUBMSG_9         MIL_TEXT("The scale factors is out of the supported range.")

#define M_OVERSCAN_ERROR         7L
#define M_ERR_7_MSG              MIL_TEXT("Overscan processing error.")
#define M_ERR_7_SUBMSG_1         MIL_TEXT("Cannot allocate temporary buffers in memory.")
#define M_ERR_7_SUBMSG_2         MIL_TEXT("The buffer is too small to perform the selected overscan")
#define M_ERR_7_SUBMSG_3         NO_SUBMSG
#define M_ERR_7_SUBMSG_4         NO_SUBMSG
#define M_ERR_7_SUBMSG_5         NO_SUBMSG
#define M_ERR_7_SUBMSG_6         NO_SUBMSG
#define M_ERR_7_SUBMSG_7         NO_SUBMSG
#define M_ERR_7_SUBMSG_8         NO_SUBMSG
#define M_ERR_7_SUBMSG_9         NO_SUBMSG

#define M_ALLOC_ERROR            8L
#define M_ERR_8_MSG              MIL_TEXT("Allocation error.")
#define M_ERR_8_SUBMSG_1         MIL_TEXT("Not enough memory to allocate the application.")
#define M_ERR_8_SUBMSG_2         MIL_TEXT("Only one application can be allocated by the host thread.")
#define M_ERR_8_SUBMSG_3         MIL_TEXT("Cannot allocate temporary buffers in memory.")
#define M_ERR_8_SUBMSG_4         MIL_TEXT("Not enough memory to allocate the buffer.")
MILERR( M_ERR,8,SUBMSG,4,        MIL_TEXT("Not enough memory to perform the allocation."))
#define M_ERR_8_SUBMSG_5         MIL_TEXT("Cannot allocate system.")
#define M_ERR_8_SUBMSG_6         MIL_TEXT("Cannot allocate digitizer.")
#define M_ERR_8_SUBMSG_7         MIL_TEXT("Cannot allocate display.")
#define M_ERR_8_SUBMSG_8         MIL_TEXT("Not enough host memory to allocate buffer.")
MILERR( M_ERR,8,SUBMSG,8,        MIL_TEXT("Not enough host memory to perform allocation."))
#define M_ERR_8_SUBMSG_9         MIL_TEXT("Buffer type not supported.")
MILERR( M_ERR,8,SUBMSG,9,        MIL_TEXT("Type not supported."))

#define M_CHILD_ERROR            9L
#define M_ERR_9_MSG              MIL_TEXT("Child allocation error.")
#define M_ERR_9_SUBMSG_1         MIL_TEXT("Only one application can be allocated by the host thread.")
#define M_ERR_9_SUBMSG_2         MIL_TEXT("Not enough memory to allocate a child application.")
#define M_ERR_9_SUBMSG_3         MIL_TEXT("Not enough memory to allocate a child buffer.")
#define M_ERR_9_SUBMSG_4         MIL_TEXT("Cannot allocate a temporary child buffer in memory.")
#define M_ERR_9_SUBMSG_5         MIL_TEXT("It is impossible to make a band child from a compressed buffer.")
#define M_ERR_9_SUBMSG_6         MIL_TEXT("Impossible to make a band child. The parent does not have enough bands.")
#define M_ERR_9_SUBMSG_7         MIL_TEXT("It is impossible to make a child from a MPEG4 buffer.")
#define M_ERR_9_SUBMSG_8         MIL_TEXT("It is impossible to make a child from a H264 buffer.")
#define M_ERR_9_SUBMSG_9         NO_SUBMSG

#define M_ACCESS_ERROR           10L
#define M_ERR_10_MSG             MIL_TEXT("Buffer access error.")
#define M_ERR_10_SUBMSG_1        MIL_TEXT("Cannot M_RESTORE a M_RAW file format buffer.")
MILERR( M_ERR,10,SUBMSG,1,       MIL_TEXT("Cannot load a raw file format buffer with the AdjustImage parameter set to True."))
#define M_ERR_10_SUBMSG_2        MIL_TEXT("Cannot export the buffer.")
MILERR( M_ERR,10,SUBMSG,2,       MIL_TEXT("Cannot save the image."))
#define M_ERR_10_SUBMSG_3        MIL_TEXT("Source buffer must be an M_IMAGE buffer.")
MILERR( M_ERR,10,SUBMSG,3,       MIL_TEXT("Source image invalid."))
#define M_ERR_10_SUBMSG_4        MIL_TEXT("Cannot import buffer.")
MILERR( M_ERR,10,SUBMSG,4,       MIL_TEXT("Cannot load image."))
#define M_ERR_10_SUBMSG_5        MIL_TEXT("File format is not supported.")
#define M_ERR_10_SUBMSG_6        MIL_TEXT("Cannot export child buffers in M_PLANAR format")
MILERR( M_ERR,10,SUBMSG,6,       MIL_TEXT("Cannot save child images in M_PLANAR format"))
#define M_ERR_10_SUBMSG_7        MIL_TEXT("Cannot load the object.")
#define M_ERR_10_SUBMSG_8        MIL_TEXT("Cannot restore the object.")
#define M_ERR_10_SUBMSG_9        MIL_TEXT("Cannot save the object.")

#define M_DISPLAY_ERROR          11L
#define M_ERR_11_MSG             MIL_TEXT("Display error.")
#define M_ERR_11_SUBMSG_1        MIL_TEXT("The display and the buffer must be allocated on the same system.")
#define M_ERR_11_SUBMSG_2        MIL_TEXT("Display Lut dimensions are not compatible with the user Lut.")
#define M_ERR_11_SUBMSG_3        MIL_TEXT("Cannot associate a M_PSEUDO Lut with a monochrome display.")
MILERR( M_ERR,11,SUBMSG,3,       MIL_TEXT("Cannot associate a pseudo LUT with a monochrome display."))
#define M_ERR_11_SUBMSG_4        MIL_TEXT("The zoom factor is out of the zoom limit or equal to zero.")
#define M_ERR_11_SUBMSG_5        MIL_TEXT("Buffer not currently selected on the display.")
MILERR( M_ERR,11,SUBMSG,5,       MIL_TEXT("Buffer not currently associated with a display."))
#define M_ERR_11_SUBMSG_6        MIL_TEXT("Incompatible display type.")
#define M_ERR_11_SUBMSG_7        MIL_TEXT("Display must be allocated with the M_WINDOWED init flag.")
MILERR( M_ERR,11,SUBMSG,7,       MIL_TEXT("The DisplayType must be set to dispDefaultWindow, dispUserWindow, or dispExternalWindow."))
#define M_ERR_11_SUBMSG_8        MIL_TEXT("Invalid window handle.")
#define M_ERR_11_SUBMSG_9        MIL_TEXT("Cannot allocate compensation buffer. Display and buffer should belong to the same system")

#define M_OPERATION_ERROR        12L
#define M_ERR_12_MSG             MIL_TEXT("Operation error.")
#define M_ERR_12_SUBMSG_1        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_12_SUBMSG_2        MIL_TEXT("Not enough host memory to allocate a buffer.")
MILERR( M_ERR,12,SUBMSG,2,       MIL_TEXT("Not enough host memory to perform the allocation."))
#define M_ERR_12_SUBMSG_3        MIL_TEXT("The application still has MIL objects associated with it.")
MILERR( M_ERR,12,SUBMSG,3,       MIL_TEXT("The application still has ActiveMIL objects associated with it."))
#define M_ERR_12_SUBMSG_4        MIL_TEXT("Only logical addresses are supported on host systems.")
#define M_ERR_12_SUBMSG_5        MIL_TEXT("The pitch must be a multiple of 4 bytes with binary buffers.")
#define M_ERR_12_SUBMSG_6        MIL_TEXT("Requested operation not supported.") 
#define M_ERR_12_SUBMSG_7        MIL_TEXT("Pitch must be a multiple of 2 pixels.")
#define M_ERR_12_SUBMSG_8        MIL_TEXT("Can only create on a physical address with non paged buffers.")
#define M_ERR_12_SUBMSG_9        MIL_TEXT("The polar band to put must fit in the destination.")

#define M_DIGITIZER_ERROR        13L
#define M_ERR_13_MSG             MIL_TEXT("Digitizer error.")
#define M_ERR_13_SUBMSG_1        MIL_TEXT("Digitizer and buffer must belong to same system.")
#define M_ERR_13_SUBMSG_2        MIL_TEXT("Cannot free digitizer. Continuous grab in progress.")
#define M_ERR_13_SUBMSG_3        MIL_TEXT("Cannot grab. Digitizer is already being used for a continuous grab")
#define M_ERR_13_SUBMSG_4        MIL_TEXT("Operation already in progress.")
#define M_ERR_13_SUBMSG_5        MIL_TEXT("Digitizer has denied the request to be freed")
#define M_ERR_13_SUBMSG_6        MIL_TEXT("A buffer in the list is already being used by MdigGrab or MdigProcess.")
MILERR( M_ERR,13,SUBMSG,6,       MIL_TEXT("An image in the list is already being used for grabbing or processing."))
#define M_ERR_13_SUBMSG_7        MIL_TEXT("Unable to load DigitizerController.dll.")
#define M_ERR_13_SUBMSG_8        MIL_TEXT("Unable to find entry point in DigitizerController.dll.")
#define M_ERR_13_SUBMSG_9        MIL_TEXT("M_COMPRESS buffers are not supported.")
MILERR( M_ERR,13,SUBMSG,9,       MIL_TEXT("Compressed images are not supported."))

#define M_HOOK_ERROR             14L
#define M_ERR_14_MSG             MIL_TEXT("Hook function error.")
#define M_ERR_14_SUBMSG_1        MIL_TEXT("Function and/or user data not found.")
#define M_ERR_14_SUBMSG_2        MIL_TEXT("A hook function must be provided. If you are trying to unhook, add M_UNHOOK to the hook type.")
#define M_ERR_14_SUBMSG_3        MIL_TEXT("Object not hooked to an event.")
#define M_ERR_14_SUBMSG_4        MIL_TEXT("Invalid hook type.")
#define M_ERR_14_SUBMSG_5        MIL_TEXT("Required hardware not present.")
#define M_ERR_14_SUBMSG_6        MIL_TEXT("Address of hooked function is not accessible from current process.")
#define M_ERR_14_SUBMSG_7        MIL_TEXT("MIL has detected a stack corruption in user hook function.")
#define M_ERR_14_SUBMSG_8        MIL_TEXT("A C++ exception occurred in the user hook function.")
#define M_ERR_14_SUBMSG_9        MIL_TEXT("A C++ exception occurred in the user WinProc function.")    

#define M_JPEG_COMPRESS_ERROR    15L
#define M_ERR_15_MSG             MIL_TEXT("JPEG compression error.")
#define M_ERR_15_SUBMSG_1        MIL_TEXT("Unable to allocate memory.")
#define M_ERR_15_SUBMSG_2        MIL_TEXT("Invalid image depth for JPEG compression.")
#define M_ERR_15_SUBMSG_3        MIL_TEXT("Invalid compression parameter.")
#define M_ERR_15_SUBMSG_4        MIL_TEXT("Invalid Huffman table.")
#define M_ERR_15_SUBMSG_5        MIL_TEXT("Invalid predictor.")
#define M_ERR_15_SUBMSG_6        MIL_TEXT("Invalid Q Factor.")
#define M_ERR_15_SUBMSG_7        MIL_TEXT("Invalid quantization table.")
#define M_ERR_15_SUBMSG_8        MIL_TEXT("Invalid restart interval.")
#define M_ERR_15_SUBMSG_9        MIL_TEXT("Invalid source or destination format.")

#define M_COMPRESS_ERROR         16L
#define M_ERR_16_MSG             MIL_TEXT("Compression error")
#define M_ERR_16_SUBMSG_1        MIL_TEXT("Invalid compression type.")
#define M_ERR_16_SUBMSG_2        MIL_TEXT("Corrupted data.")
#define M_ERR_16_SUBMSG_3        MIL_TEXT("Invalid image depth for required compression type.")
#define M_ERR_16_SUBMSG_4        MIL_TEXT("Buffer allocated with MbufCreate cannot be the destination of a compression operation.")
MILERR( M_ERR,16,SUBMSG,4,       MIL_TEXT("Image allocated with AssignMemory cannot be the destination of a compression operation."))
#define M_ERR_16_SUBMSG_5        MIL_TEXT("Buffer allocated with MbufCreate cannot be the destination of a MbufPut operation.")
MILERR( M_ERR,16,SUBMSG,5,       MIL_TEXT("Image allocated with AssignMemory cannot be the destination of a Put method."))
#define M_ERR_16_SUBMSG_6        MIL_TEXT("Buffer too small to contain the compressed data.")
#define M_ERR_16_SUBMSG_7        MIL_TEXT("Cannot modify the pointer of a buffer allocated with MbufCreate.")
#define M_ERR_16_SUBMSG_8        NO_SUBMSG
#define M_ERR_16_SUBMSG_9        NO_SUBMSG

#define M_JPEG_COMPRESS_ERROR_2  17L
#define M_ERR_17_MSG             MIL_TEXT("JPEG compression error.")
#define M_ERR_17_SUBMSG_1        MIL_TEXT("Chrominance tables are allowed only with 3 band YUV buffers.")
#define M_ERR_17_SUBMSG_2        MIL_TEXT("Luminance tables are allowed only with 3 band YUV buffers.")
#define M_ERR_17_SUBMSG_3        MIL_TEXT("The predictor value is only available for 1 band buffers or child band buffers.")
#define M_ERR_17_SUBMSG_4        MIL_TEXT("The Q factor is only available for 1 band buffers or band child band buffers.")
#define M_ERR_17_SUBMSG_5        MIL_TEXT("The restart interval is only available for 1 band buffers or child band buffers.")
#define M_ERR_17_SUBMSG_6        MIL_TEXT("The source image must be a multiple of 16 in X and a multiple of 8 in Y.")
#define M_ERR_17_SUBMSG_7        MIL_TEXT("The destination image must be a multiple of 16 in X and a multiple of 8 in Y.")
#define M_ERR_17_SUBMSG_8        MIL_TEXT("The source image must be a multiple of 16 in X and a multiple of 16 in Y.")
#define M_ERR_17_SUBMSG_9        MIL_TEXT("The destination image must be a multiple of 16 in X and a multiple of 16 in Y.")


#define M_BMP_ERROR              18L
#define M_ERR_18_MSG             MIL_TEXT("BMP handler file access error.")
#define M_ERR_18_SUBMSG_1        MIL_TEXT("Not a bitmap file.")
#define M_ERR_18_SUBMSG_2        MIL_TEXT("Error closing bitmap file.")
#define M_ERR_18_SUBMSG_3        MIL_TEXT("Cannot open file in read mode.")
#define M_ERR_18_SUBMSG_4        MIL_TEXT("Error reading file.")
#define M_ERR_18_SUBMSG_5        MIL_TEXT("Unable to position file pointer.")
#define M_ERR_18_SUBMSG_6        MIL_TEXT("Cannot create or open file in write mode.")
#define M_ERR_18_SUBMSG_7        MIL_TEXT("No bitmap file opened in read mode.")
#define M_ERR_18_SUBMSG_8        MIL_TEXT("No bitmap file opened in write mode.")
#define M_ERR_18_SUBMSG_9        MIL_TEXT("Error writing file.")

#define M_BMP_ERROR_2            19L
#define M_ERR_19_MSG             MIL_TEXT("BMP handler general error.")
#define M_ERR_19_SUBMSG_1        MIL_TEXT("Unable to allocate sufficient memory.")
#define M_ERR_19_SUBMSG_2        MIL_TEXT("Color format not supported.")
#define M_ERR_19_SUBMSG_3        MIL_TEXT("Invalid write color format specified.")
#define M_ERR_19_SUBMSG_4        MIL_TEXT("Invalid write compression type specified.")
#define M_ERR_19_SUBMSG_5        MIL_TEXT("Conversion not supported.")
#define M_ERR_19_SUBMSG_6        MIL_TEXT("Invalid array format specified.")
#define M_ERR_19_SUBMSG_7        MIL_TEXT("Invalid length of palette arrays specified.")
#define M_ERR_19_SUBMSG_8        MIL_TEXT("No palette to read.")
#define M_ERR_19_SUBMSG_9        MIL_TEXT("Palette not needed for current write format.")


#define M_TIFF_ERROR             20L
#define M_ERR_20_MSG             MIL_TEXT("TIFF file access error.")
#define M_ERR_20_SUBMSG_1        MIL_TEXT("Cannot open file.")
#define M_ERR_20_SUBMSG_2        MIL_TEXT("Cannot close file.")
#define M_ERR_20_SUBMSG_3        MIL_TEXT("Cannot read file.")
#define M_ERR_20_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_20_SUBMSG_5        MIL_TEXT("Cannot write to file.")
#define M_ERR_20_SUBMSG_6        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_20_SUBMSG_7        MIL_TEXT("The image file does not conform to the TIFF 6.0 specification.")
#define M_ERR_20_SUBMSG_8        MIL_TEXT("Wrong Byte Order, Only INTEL Byte Ordering supported.")
#define M_ERR_20_SUBMSG_9        MIL_TEXT("Not a TIFF file.")

#define M_MIL_FILE_ERROR         21L
#define M_ERR_21_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_21_SUBMSG_1        MIL_TEXT("Cannot open file.")
#define M_ERR_21_SUBMSG_2        MIL_TEXT("Cannot close file.")
#define M_ERR_21_SUBMSG_3        MIL_TEXT("Cannot read file.")
#define M_ERR_21_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_21_SUBMSG_5        MIL_TEXT("Cannot write to file.")
#define M_ERR_21_SUBMSG_6        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_21_SUBMSG_7        MIL_TEXT("The image file does not conform to the TIFF 6.0 specification.")
#define M_ERR_21_SUBMSG_8        MIL_TEXT("Wrong Byte Order, Only INTEL Byte Ordering supported.")
#define M_ERR_21_SUBMSG_9        MIL_TEXT("Not a MIL file.")

#define M_MIL_FILE_ERROR_2       22L
#define M_ERR_22_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_22_SUBMSG_1        MIL_TEXT("Only 8, 16 or 32 BitsPerSample supported.")
#define M_ERR_22_SUBMSG_2        MIL_TEXT("Lempel-Ziv & Welch (LZW) compression not supported.")
#define M_ERR_22_SUBMSG_3        MIL_TEXT("PhotometricInterp incompatible with SamplePerPixel.")
#define M_ERR_22_SUBMSG_4        MIL_TEXT("Only PlanarConfiguration 2 supported for multi-band images.")
#define M_ERR_22_SUBMSG_5        MIL_TEXT("Up to 8 Samples Per Pixel supported.")
#define M_ERR_22_SUBMSG_6        MIL_TEXT("Only identical BitsPerSample for every sample supported.")
#define M_ERR_22_SUBMSG_7        MIL_TEXT("Cannot seek in file.")
#define M_ERR_22_SUBMSG_8        MIL_TEXT("Bad file format detected.")
#define M_ERR_22_SUBMSG_9        MIL_TEXT("Invalid info requested.")

#define M_MIL_FILE_ERROR_3       23L
#define M_ERR_23_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_23_SUBMSG_1        MIL_TEXT("Invalid parameter detected.")
#define M_ERR_23_SUBMSG_2        MIL_TEXT("Missing information in file.")
#define M_ERR_23_SUBMSG_3        MIL_TEXT("Invalid size information detected in file.")
#define M_ERR_23_SUBMSG_4        MIL_TEXT("Invalid identification information detected in file.")
#define M_ERR_23_SUBMSG_5        MIL_TEXT("Invalid data information detected in file.")
#define M_ERR_23_SUBMSG_6        MIL_TEXT("Unexpected internal error.")
#define M_ERR_23_SUBMSG_7        MIL_TEXT("Cannot open file: Invalid file name.")
#define M_ERR_23_SUBMSG_8        NO_SUBMSG
#define M_ERR_23_SUBMSG_9        NO_SUBMSG

#define M_MULTI_THREAD_ERROR     24L
#define M_ERR_24_MSG             MIL_TEXT("Multi thread error.")
#define M_ERR_24_SUBMSG_1        NO_SUBMSG
MILERR( M_ERR,24,SUBMSG,1,       MIL_TEXT("Cannot find a thread event to remove."))
#define M_ERR_24_SUBMSG_2        MIL_TEXT("Invalid MIL_ID, MIL thread or event was not allocated in current HOST thread.")
MILERR( M_ERR,24,SUBMSG,2,       MIL_TEXT("Invalid thread or event ID; it was not allocated in current host thread."))
#define M_ERR_24_SUBMSG_3        MIL_TEXT("Application must be freed before exiting a thread.")
#define M_ERR_24_SUBMSG_4        MIL_TEXT("Operation not supported on this system")
#define M_ERR_24_SUBMSG_5        MIL_TEXT("Cannot allocate thread")
#define M_ERR_24_SUBMSG_6        MIL_TEXT("Cannot select this thread in the current host thread")
#define M_ERR_24_SUBMSG_7        MIL_TEXT("The thread belongs to a system that does not support this operation")
#define M_ERR_24_SUBMSG_8        MIL_TEXT("Operation not supported.")
#define M_ERR_24_SUBMSG_9        MIL_TEXT("Cannot wait for the completion of a thread allocated in another host thread")

#define M_JPEG_ERROR             25L
#define M_ERR_25_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_25_SUBMSG_1        MIL_TEXT("Color format not supported.")
#define M_ERR_25_SUBMSG_2        MIL_TEXT("Error closing JPEG file.")
#define M_ERR_25_SUBMSG_3        MIL_TEXT("Error opening JPEG file.")
#define M_ERR_25_SUBMSG_4        MIL_TEXT("Unable to allocate sufficient memory.")
#define M_ERR_25_SUBMSG_5        MIL_TEXT("Image too large to save.")
#define M_ERR_25_SUBMSG_6        MIL_TEXT("Invalid JPEG Marker.")
#define M_ERR_25_SUBMSG_7        MIL_TEXT("Bad identification information detected in file.")
#define M_ERR_25_SUBMSG_8        MIL_TEXT("Buffer to receive data does not fit with data.")
#define M_ERR_25_SUBMSG_9        MIL_TEXT("Error reading JPEG file.")

#define M_BUFFER_FREE_ERROR      26L
#define M_ERR_26_MSG             MIL_TEXT("Buffer free operation error.")
#define M_ERR_26_SUBMSG_1        MIL_TEXT("Buffer still has child(ren) associated with it.")
#define M_ERR_26_SUBMSG_2        MIL_TEXT("Use MnatBufDestroy() on this kind of buffer.")
#define M_ERR_26_SUBMSG_3        MIL_TEXT("User attempting to free a system allocated buffer.")
#define M_ERR_26_SUBMSG_4        MIL_TEXT("Internal error, internal function attempting to free a user allocated buffer.")
#define M_ERR_26_SUBMSG_5        MIL_TEXT("This buffer is currently being used by a digitizer for a continuous grab.")
#define M_ERR_26_SUBMSG_6        MIL_TEXT("Memory corruption detected: the guard value has been overwritten.")
#define M_ERR_26_SUBMSG_7        MIL_TEXT("This buffer is still remotely mapped.")
#define M_ERR_26_SUBMSG_8        NO_SUBMSG
#define M_ERR_26_SUBMSG_9        NO_SUBMSG

#define M_SYSTEM_FREE_ERROR      27L
#define M_ERR_27_MSG             MIL_TEXT("System free error.")
#define M_ERR_27_SUBMSG_1        MIL_TEXT("System still has buffer(s) associated with it.")
#define M_ERR_27_SUBMSG_2        MIL_TEXT("System still has display(s) associated with it.")
#define M_ERR_27_SUBMSG_3        MIL_TEXT("System still has digitizer(s) associated with it.")
#define M_ERR_27_SUBMSG_4        MIL_TEXT("Cannot free M_DEFAULT_HOST")
MILERR( M_ERR,27,SUBMSG,4,       MIL_TEXT("Cannot free the default owner system."))
#define M_ERR_27_SUBMSG_5        MIL_TEXT("System still has object(s) associated with it.")
#define M_ERR_27_SUBMSG_6        MIL_TEXT("System still has processing object(s) associated with it.")
#define M_ERR_27_SUBMSG_7        MIL_TEXT("System is still selected in at least one thread.")
#define M_ERR_27_SUBMSG_8        NO_SUBMSG
#define M_ERR_27_SUBMSG_9        NO_SUBMSG

#define M_FUNCTION_START_ERROR   28L
#define M_ERR_28_MSG             MIL_TEXT("Function start error.")
#define M_ERR_28_SUBMSG_1        MIL_TEXT("No application allocated.")
#define M_ERR_28_SUBMSG_2        NO_SUBMSG
#define M_ERR_28_SUBMSG_3        NO_SUBMSG
#define M_ERR_28_SUBMSG_4        NO_SUBMSG
#define M_ERR_28_SUBMSG_5        NO_SUBMSG
#define M_ERR_28_SUBMSG_6        NO_SUBMSG
#define M_ERR_28_SUBMSG_7        NO_SUBMSG
#define M_ERR_28_SUBMSG_8        NO_SUBMSG
#define M_ERR_28_SUBMSG_9        NO_SUBMSG

#define M_COMMAND_DECODER_ERROR  29L
#define M_ERR_29_MSG             MIL_TEXT("System command error.")
#define M_ERR_29_SUBMSG_1        MIL_TEXT("Requested operation not supported.")
#define M_ERR_29_SUBMSG_2        MIL_TEXT("Operation execution failed.")
#define M_ERR_29_SUBMSG_3        NO_SUBMSG
#define M_ERR_29_SUBMSG_4        NO_SUBMSG 
#define M_ERR_29_SUBMSG_5        NO_SUBMSG
#define M_ERR_29_SUBMSG_6        NO_SUBMSG
#define M_ERR_29_SUBMSG_7        NO_SUBMSG
#define M_ERR_29_SUBMSG_8        NO_SUBMSG
#define M_ERR_29_SUBMSG_9        NO_SUBMSG

#define M_LABELLING_ERROR        30L
#define M_ERR_30_MSG             MIL_TEXT("Labeling error.")
#define M_ERR_30_SUBMSG_1        MIL_TEXT("Maximum number of labels reached.")
#define M_ERR_30_SUBMSG_2        MIL_TEXT("Should use a buffer of greater bit depth.")
MILERR( M_ERR,30,SUBMSG,2,       MIL_TEXT("Should use an Image or LUT of greater bit depth."))
#define M_ERR_30_SUBMSG_3        NO_SUBMSG
#define M_ERR_30_SUBMSG_4        NO_SUBMSG
#define M_ERR_30_SUBMSG_5        NO_SUBMSG
#define M_ERR_30_SUBMSG_6        NO_SUBMSG
#define M_ERR_30_SUBMSG_7        NO_SUBMSG
#define M_ERR_30_SUBMSG_8        NO_SUBMSG
#define M_ERR_30_SUBMSG_9        NO_SUBMSG

#define M_FILE_ERROR             31L
#define M_ERR_31_MSG             MIL_TEXT("File access error.")
#define M_ERR_31_SUBMSG_1        MIL_TEXT("Cannot open output file.")
#define M_ERR_31_SUBMSG_2        MIL_TEXT("Cannot write to file.")
#define M_ERR_31_SUBMSG_3        MIL_TEXT("Cannot open input file.")
#define M_ERR_31_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_31_SUBMSG_5        MIL_TEXT("Cannot close output file.")
#define M_ERR_31_SUBMSG_6        MIL_TEXT("Cannot close input file.")
#define M_ERR_31_SUBMSG_7        MIL_TEXT("The FileFormatBufId does not represent the actual file format.")
MILERR( M_ERR,31,SUBMSG,7,       MIL_TEXT("The Image.FileFormat does not represent the actual file format."))
#define M_ERR_31_SUBMSG_8        MIL_TEXT("This OS does not support file access.")
#define M_ERR_31_SUBMSG_9        MIL_TEXT("Not a MIL file.")
MILERR( M_ERR,31,SUBMSG,9,       MIL_TEXT("Not an ActiveMIL file."))

#define M_APP_FREE_ERROR         32L
#define M_ERR_32_MSG             MIL_TEXT("Application free operation error.")
#define M_ERR_32_SUBMSG_1        MIL_TEXT("Application still has system(s) associated with it.")
#define M_ERR_32_SUBMSG_2        MIL_TEXT("Default host system still has buffer(s) associated with it.")
#define M_ERR_32_SUBMSG_3        MIL_TEXT("Application still has child(ren) associated with it.")
#define M_ERR_32_SUBMSG_4        MIL_TEXT("Application was not freed.")
#define M_ERR_32_SUBMSG_5        MIL_TEXT("Application still has object(s) associated with it.")
#define M_ERR_32_SUBMSG_6        MIL_TEXT("Application must be freed in the thread in which it was allocated.")
#define M_ERR_32_SUBMSG_7        MIL_TEXT("Some display related object(s) were not freed.")
#define M_ERR_32_SUBMSG_8        MIL_TEXT("Could not free the Auxiliary IO service.")
#define M_ERR_32_SUBMSG_9        MIL_TEXT("Application is still processing.")

#define M_TIFF_ERROR_2           33L
#define M_ERR_33_MSG             MIL_TEXT("TIFF File access error.")
#define M_ERR_33_SUBMSG_1        MIL_TEXT("Only 1, 8, 16 or 32 BitsPerSample supported.")
#define M_ERR_33_SUBMSG_2        MIL_TEXT("Cannot read compressed image file.")
#define M_ERR_33_SUBMSG_3        MIL_TEXT("PhotometricInterp incompatible with SamplePerPixel.")
#define M_ERR_33_SUBMSG_4        MIL_TEXT("Only PlanarConfiguration 2 supported for multi-band images.")
#define M_ERR_33_SUBMSG_5        MIL_TEXT("Up to 8 Samples Per Pixel supported.")
#define M_ERR_33_SUBMSG_6        MIL_TEXT("Only identical BitsPerSample for every sample supported.")
#define M_ERR_33_SUBMSG_7        MIL_TEXT("Cannot seek in file.")
#define M_ERR_33_SUBMSG_8        MIL_TEXT("Bad file format detected.")
#define M_ERR_33_SUBMSG_9        MIL_TEXT("Invalid info requested.")

#define M_PROCESSING_ERROR       34L
#define M_ERR_34_MSG             MIL_TEXT("Processing error.")
#define M_ERR_34_SUBMSG_1        MIL_TEXT("All buffers do not have the same working system.")
#define M_ERR_34_SUBMSG_2        MIL_TEXT("Cannot find any working system between buffers.")
#define M_ERR_34_SUBMSG_3        MIL_TEXT("Cannot process a HOST buffer as a whole and a temporary buffer.")
#define M_ERR_34_SUBMSG_4        MIL_TEXT("Source buffers cannot overlap with destination buffers.")
#define M_ERR_34_SUBMSG_5        MIL_TEXT("No processor on target processing system.")
#define M_ERR_34_SUBMSG_6        MIL_TEXT("Pixel values out of supported range.")
#define M_ERR_34_SUBMSG_7        NO_SUBMSG
#define M_ERR_34_SUBMSG_8        NO_SUBMSG
#define M_ERR_34_SUBMSG_9        MIL_TEXT("Not enough memory or system limitation, cannot process buffer.")

#define M_INVALID_ID             35L
#define M_ERR_35_MSG             MIL_TEXT("Invalid MIL ID.")
#define M_ERR_35_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_35_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_35_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_35_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_35_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_35_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_35_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_35_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_35_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_INVALID_NATURE         36L
#define M_ERR_36_MSG             MIL_TEXT("Inappropriate MIL ID.")
#define M_ERR_36_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_36_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_36_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_36_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_36_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_36_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_36_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_36_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_36_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_INVALID_PARAM_ERROR_2  37L
#define M_ERR_37_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_37_SUBMSG_1        MIL_TEXT("For this operation, you should supply a LUT buffer with at least 512 entries.")
MILERR( M_ERR,37,SUBMSG,1,       MIL_TEXT("For this operation, you should supply a LUT with at least 512 entries."))
#define M_ERR_37_SUBMSG_2        MIL_TEXT("For this operation the grab mode must be asynchronous.")
#define M_ERR_37_SUBMSG_3        MIL_TEXT("This type of conversion requires two 3 band buffers.")
#define M_ERR_37_SUBMSG_4        MIL_TEXT("This type of conversion requires a 3 band source buffer.")
#define M_ERR_37_SUBMSG_5        MIL_TEXT("This type of conversion requires a 3 band destination buffer.")
#define M_ERR_37_SUBMSG_6        MIL_TEXT("Invalid interpolation type specified.")
#define M_ERR_37_SUBMSG_7        MIL_TEXT("Specified center is outside buffer.")
#define M_ERR_37_SUBMSG_8        MIL_TEXT("An 8 bit monochrome image buffer is required for this operation.")
MILERR( M_ERR,37,SUBMSG,8,       MIL_TEXT("Am 8 bit monochrome image is required for this operation."))
#define M_ERR_37_SUBMSG_9        MIL_TEXT("Look up tables must be 1 or 3 bands, 8 bits deep and the size of X must be greater than 255.")
MILERR( M_ERR,37,SUBMSG,9,       MIL_TEXT("LUTc must be 1 or 3 bands, 8 bits deep and have a size greater than 255."))

#define M_INVALID_ATTRIBUTE      38L
#define M_ERR_38_MSG             MIL_TEXT("Invalid attributes.")
#define M_ERR_38_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_38_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_38_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_38_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_38_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_38_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_38_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_38_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_38_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_CALL_CONTEXT_ERROR     39L
#define M_ERR_39_MSG             MIL_TEXT("Call context error")
#define M_ERR_39_SUBMSG_1        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_39_SUBMSG_2        NO_SUBMSG
#define M_ERR_39_SUBMSG_3        NO_SUBMSG
#define M_ERR_39_SUBMSG_4        NO_SUBMSG
#define M_ERR_39_SUBMSG_5        NO_SUBMSG
#define M_ERR_39_SUBMSG_6        NO_SUBMSG
#define M_ERR_39_SUBMSG_7        NO_SUBMSG
#define M_ERR_39_SUBMSG_8        NO_SUBMSG
#define M_ERR_39_SUBMSG_9        NO_SUBMSG

#define M_DRIVER_OBSOLETE        40L
#define M_ERR_40_MSG             MIL_TEXT("MIL driver version.")
#define M_ERR_40_SUBMSG_1        MIL_TEXT("Driver version is invalid.")
#define M_ERR_40_SUBMSG_2        NO_SUBMSG
#define M_ERR_40_SUBMSG_3        NO_SUBMSG
#define M_ERR_40_SUBMSG_4        NO_SUBMSG
#define M_ERR_40_SUBMSG_5        NO_SUBMSG
#define M_ERR_40_SUBMSG_6        NO_SUBMSG
#define M_ERR_40_SUBMSG_7        NO_SUBMSG
#define M_ERR_40_SUBMSG_8        NO_SUBMSG
#define M_ERR_40_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_3  41L
#define M_ERR_41_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_41_SUBMSG_1        MIL_TEXT("Parameter 1 not in supported list.")
#define M_ERR_41_SUBMSG_2        MIL_TEXT("Parameter 2 not in supported list.")
#define M_ERR_41_SUBMSG_3        MIL_TEXT("Parameter 3 not in supported list.")
#define M_ERR_41_SUBMSG_4        MIL_TEXT("Parameter 4 not in supported list.")
#define M_ERR_41_SUBMSG_5        MIL_TEXT("Parameter 5 not in supported list.")
#define M_ERR_41_SUBMSG_6        MIL_TEXT("Parameter 6 not in supported list.")
#define M_ERR_41_SUBMSG_7        MIL_TEXT("Parameter 7 not in supported list.")
#define M_ERR_41_SUBMSG_8        MIL_TEXT("Parameter 8 not in supported list.")
#define M_ERR_41_SUBMSG_9        MIL_TEXT("Parameter 9 not in supported list.")

#define M_ALLOC_ERROR_2          42L
#define M_ERR_42_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_42_SUBMSG_1        MIL_TEXT("Not enough host memory to do the operation.")
#define M_ERR_42_SUBMSG_2        MIL_TEXT("Invalid attribute, M_GRAB not supported on host.")
MILERR( M_ERR,42,SUBMSG,2,       MIL_TEXT("The CanGrab property is not supported on host."))
#define M_ERR_42_SUBMSG_3        MIL_TEXT("Incompatible buffer dimensions, SizeBand, SizeY and (SizeX x SizeBit) must be identical.")
MILERR( M_ERR,42,SUBMSG,3,       MIL_TEXT("Incompatible buffer dimensions, NumberOfBands, SizeY and (SizeX x DataDepth) must be identical."))
#define M_ERR_42_SUBMSG_4        MIL_TEXT("Unable to communicate with MIL Memory manager.")
#define M_ERR_42_SUBMSG_5        MIL_TEXT("The requested memory size is invalid.")
#define M_ERR_42_SUBMSG_6        MIL_TEXT("Impossible to make a band child of a compressed buffer.")
#define M_ERR_42_SUBMSG_7        MIL_TEXT("You require a fast overscan buffer, but the M_ALLOCATION_OVERSCAN_SIZE is 0.")
MILERR( M_ERR,42,SUBMSG,7,       MIL_TEXT("You require a fast overscan image, but the AllocationOverscanSize is set to 0."))
#define M_ERR_42_SUBMSG_8        MIL_TEXT("Memory already allocated.")
#define M_ERR_42_SUBMSG_9        MIL_TEXT("The MIL_ID table is full. Make sure you do not have a resource leak.")
MILERR( M_ERR,42,SUBMSG,9,       MIL_TEXT("Unable to create new ActiveMIL controls. Make sure you don't have a resource leak."))

#define M_TIMER_ERROR            43L
#define M_ERR_43_MSG             MIL_TEXT("Timer error.")
#define M_ERR_43_SUBMSG_1        MIL_TEXT("Invalid timer mode specified.")
#define M_ERR_43_SUBMSG_2        MIL_TEXT("TimePtr parameter cannot be null.")
#define M_ERR_43_SUBMSG_3        MIL_TEXT("Installed hardware does not support a high-resolution performance counter.")
#define M_ERR_43_SUBMSG_4        MIL_TEXT("Timer must be reset prior to a read.")
#define M_ERR_43_SUBMSG_5        NO_SUBMSG
#define M_ERR_43_SUBMSG_6        NO_SUBMSG
#define M_ERR_43_SUBMSG_7        NO_SUBMSG
#define M_ERR_43_SUBMSG_8        NO_SUBMSG
#define M_ERR_43_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_4  44L
#define M_ERR_44_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_44_SUBMSG_1        MIL_TEXT("The valid data formats for binary buffers are M_SINGLE_BAND and M_PLANAR.")
MILERR( M_ERR,44,SUBMSG,1,       MIL_TEXT("The valid formats for binary images are single band and planar."))
#define M_ERR_44_SUBMSG_2        MIL_TEXT("Operation not supported on float buffers.")
#define M_ERR_44_SUBMSG_3        MIL_TEXT("Destination buffer is binary, MaskValue must be equal to 0 or 1.")
#define M_ERR_44_SUBMSG_4        MIL_TEXT("Image buffer must be monochrome for this operation.")
MILERR( M_ERR,44,SUBMSG,4,       MIL_TEXT("Image must be monochrome for this operation."))
#define M_ERR_44_SUBMSG_5        MIL_TEXT("Source buffers must be of the same type")
#define M_ERR_44_SUBMSG_6        MIL_TEXT("Integer source buffers must be unsigned")
#define M_ERR_44_SUBMSG_7        MIL_TEXT("Operation not supported with binary buffers.")
#define M_ERR_44_SUBMSG_8        MIL_TEXT("Source buffers must be of the same pixel depth.")
#define M_ERR_44_SUBMSG_9        MIL_TEXT("The width and height of the source and destination buffers must be a power of 2.")

#define M_INVALID_PARAM_ERROR_5  45L
#define M_ERR_45_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_45_SUBMSG_1        MIL_TEXT("The number of bands is not valid.")
#define M_ERR_45_SUBMSG_2        MIL_TEXT("The X dimension is not valid.")
MILERR( M_ERR,45,SUBMSG,2,       MIL_TEXT("The width is not valid."))
#define M_ERR_45_SUBMSG_3        MIL_TEXT("The Y dimension is not valid.")
MILERR( M_ERR,45,SUBMSG,3,       MIL_TEXT("The height is not valid."))
#define M_ERR_45_SUBMSG_4        MIL_TEXT("The pixel depth is not valid.")
#define M_ERR_45_SUBMSG_5        MIL_TEXT("The buffer attributes are not valid.")
#define M_ERR_45_SUBMSG_6        MIL_TEXT("The data type is not valid.")
#define M_ERR_45_SUBMSG_7        MIL_TEXT("Invalid FFT type specified.")
#define M_ERR_45_SUBMSG_8        MIL_TEXT("Invalid operation mode specified.")
#define M_ERR_45_SUBMSG_9        MIL_TEXT("Invalid transform specified.")

#define M_INVALID_PARAM_ERROR_6  46L
#define M_ERR_46_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_46_SUBMSG_1        MIL_TEXT("Operation not supported on 32-bit buffers.")
#define M_ERR_46_SUBMSG_2        MIL_TEXT("Invalid minimal variation specified.")
#define M_ERR_46_SUBMSG_3        MIL_TEXT("Invalid combination of control flag constants.")
MILERR( M_ERR,46,SUBMSG,3,       MIL_TEXT("Invalid parameter combination."))
#define M_ERR_46_SUBMSG_4        MIL_TEXT("A marker image or a minimal variation must be supplied.")
#define M_ERR_46_SUBMSG_5        MIL_TEXT("Value out of range.")
#define M_ERR_46_SUBMSG_6        MIL_TEXT("Invalid mode specified.")
#define M_ERR_46_SUBMSG_7        MIL_TEXT("The pointer should not be null.")
#define M_ERR_46_SUBMSG_8        MIL_TEXT("The buffer must be a M_IMAGE + M_COMPRESS buffer.")
MILERR( M_ERR,46,SUBMSG,8,       MIL_TEXT("The image must be a compress image. CompressionType property no equal to imUncompressed."))
#define M_ERR_46_SUBMSG_9        MIL_TEXT("Invalid compression type.")

#define M_INVALID_PARAM_ERROR_7  47L
#define M_ERR_47_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_47_SUBMSG_1        MIL_TEXT("Cannot change the compression type of a single band.")
#define M_ERR_47_SUBMSG_2        MIL_TEXT("Invalid ControlFlag value.")
MILERR( M_ERR,47,SUBMSG,2,       MIL_TEXT("Invalid constant specified."))
#define M_ERR_47_SUBMSG_3        MIL_TEXT("The MIL_INT64 pointer cannot be null.")
#define M_ERR_47_SUBMSG_4        MIL_TEXT("Invalid source buffers.")
#define M_ERR_47_SUBMSG_5        MIL_TEXT("Invalid Q factor value.")
#define M_ERR_47_SUBMSG_6        MIL_TEXT("Invalid destination buffers.")
#define M_ERR_47_SUBMSG_7        MIL_TEXT("The second LUT must be M_NULL for M_WARP_POLYNOMIAL operation mode.")
MILERR( M_ERR,47,SUBMSG,7,       MIL_TEXT("When WarpParameters.Coefficients is used the WarpParameters.WarpLUT data is ignored."))
#define M_ERR_47_SUBMSG_8        MIL_TEXT("The angle range must be less than 360 degrees.")
#define M_ERR_47_SUBMSG_9        MIL_TEXT("Invalid First Warp parameter. Size or Type invalid.")

#define M_INVALID_PARAM_ERROR_8  48L
#define M_ERR_48_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_48_SUBMSG_1        MIL_TEXT("Source buffers must be of the same type and pixel depth.")
#define M_ERR_48_SUBMSG_2        MIL_TEXT("Destination buffers must be of the same type and pixel depth.")
#define M_ERR_48_SUBMSG_3        MIL_TEXT("Angle value must be between -360 and 360.")
#define M_ERR_48_SUBMSG_4        MIL_TEXT("Polar conversion only supported on float buffers.")
#define M_ERR_48_SUBMSG_5        MIL_TEXT("This type of conversion requires a 1 band destination buffer.")
#define M_ERR_48_SUBMSG_6        MIL_TEXT("Invalid transform type")
MILERR( M_ERR,48,SUBMSG,6,       MIL_TEXT("Invalid transformation."))
#define M_ERR_48_SUBMSG_7        MIL_TEXT("The M_NORMALIZE flag must be used with this transform.")
MILERR( M_ERR,48,SUBMSG,7,       MIL_TEXT("The Normalize parameter must set to True for this transform."))
#define M_ERR_48_SUBMSG_8        MIL_TEXT("This type of conversion requires a 1 band source buffer.")
#define M_ERR_48_SUBMSG_9        MIL_TEXT("Invalid number of bytes. Use zero or a positive value.")

#define M_JPEG_ERROR_2           49L
#define M_ERR_49_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_49_SUBMSG_1        MIL_TEXT("Vertical sampling factor of more than 4 are not supported.")
#define M_ERR_49_SUBMSG_2        MIL_TEXT("MIL supports only 1-band and 3-band buffers.")
MILERR( M_ERR,49,SUBMSG,2,       MIL_TEXT("Only 1-band and 3-band images supported."))
#define M_ERR_49_SUBMSG_3        MIL_TEXT("MIL only supports sequential baseline DCT JPEG and lossless JPEG files.")
MILERR( M_ERR,49,SUBMSG,3,       MIL_TEXT("Only sequential baseline DCT JPEG and lossless JPEG files supported."))
#define M_ERR_49_SUBMSG_4        MIL_TEXT("Point transform not supported.")
#define M_ERR_49_SUBMSG_5        MIL_TEXT("Reading beyond the available data.")
#define M_ERR_49_SUBMSG_6        MIL_TEXT("The End Of Image marker is before the end of the file.")
#define M_ERR_49_SUBMSG_7        MIL_TEXT("16-bit quantization table not supported.")
#define M_ERR_49_SUBMSG_8        MIL_TEXT("Horizontal sampling factor of more than 4 not supported.")
#define M_ERR_49_SUBMSG_9        MIL_TEXT("Sampling factors do not correspond to any supported format.")

#define M_INVALID_PARAM_ERROR_9  50L
#define M_ERR_50_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_50_SUBMSG_1        MIL_TEXT("Inquire type not supported.")
#define M_ERR_50_SUBMSG_2        MIL_TEXT("The look up table must have a Y size of 1.")
#define M_ERR_50_SUBMSG_3        MIL_TEXT("The size of the buffer is too large.")
MILERR( M_ERR,50,SUBMSG,3,       MIL_TEXT("The size is too large."))
#define M_ERR_50_SUBMSG_4        MIL_TEXT("The destination buffer cannot be 1-bit.")
#define M_ERR_50_SUBMSG_5        MIL_TEXT("SaturationSizeBit must be 1, 8, 16 or 32.")
#define M_ERR_50_SUBMSG_6        MIL_TEXT("SaturationType must be M_SIGNED, M_UNSIGNED or M_FLOAT.")
MILERR( M_ERR,50,SUBMSG,6,       MIL_TEXT("SaturationType must be imSigned, imUnsigned or imFloat."))
#define M_ERR_50_SUBMSG_7        MIL_TEXT("Invalid combinaison of SaturationType and SizeBit.")
#define M_ERR_50_SUBMSG_8        MIL_TEXT("YUV buffers must be M_UNSIGNED.")
MILERR( M_ERR,50,SUBMSG,8,       MIL_TEXT("YUV images DataType should must be imUnsigned."))
#define M_ERR_50_SUBMSG_9        MIL_TEXT("The file name length must be greater than 0.")

#define M_AVI_FILE_ERROR         51L
#define M_ERR_51_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_51_SUBMSG_1        MIL_TEXT("The frame to write contains no data.")
#define M_ERR_51_SUBMSG_2        MIL_TEXT("Error writing into the AVI file.")
#define M_ERR_51_SUBMSG_3        MIL_TEXT("File format not supported.")
#define M_ERR_51_SUBMSG_4        MIL_TEXT("The file format and image format are incompatible.")
#define M_ERR_51_SUBMSG_5        MIL_TEXT("Error opening the AVI file.")
#define M_ERR_51_SUBMSG_6        MIL_TEXT("Invalid file format.")
#define M_ERR_51_SUBMSG_7        MIL_TEXT("Cannot write the frame. The index is full.")
#define M_ERR_51_SUBMSG_8        MIL_TEXT("File format not supported. Cannot import MPEG4 sequences.")
#define M_ERR_51_SUBMSG_9        MIL_TEXT("File format not supported. Cannot import H264 sequences.")

#define M_DMA_ERROR              52L
#define M_ERR_52_MSG             MIL_TEXT("Error using Matrox Dma service.")
#define M_ERR_52_SUBMSG_1        MIL_TEXT("Cannot open the Matrox Dma manager.")
#define M_ERR_52_SUBMSG_2        MIL_TEXT("Cannot access PCI data.")
#define M_ERR_52_SUBMSG_3        NO_SUBMSG
#define M_ERR_52_SUBMSG_4        MIL_TEXT("Cannot communicate with Memory manager. Check if it is installed and started.")
#define M_ERR_52_SUBMSG_5        MIL_TEXT("Cannot access hook information.")
#define M_ERR_52_SUBMSG_6        MIL_TEXT("Can only perform this operation on the Default Host.")
#define M_ERR_52_SUBMSG_7        MIL_TEXT("Unable to recover info from Dma pool.")
#define M_ERR_52_SUBMSG_8        MIL_TEXT("Unsupported control flag.") // Error logged when using M_LOW_4GB_MEMORY or M_HIGH_4GB_MEMORY
#define M_ERR_52_SUBMSG_9        MIL_TEXT("Could not enable or disable the Write-combining feature.")

#define M_BMP_ERROR_3            53L
#define M_ERR_53_MSG             MIL_TEXT("BMP handler general error.")
#define M_ERR_53_SUBMSG_1        MIL_TEXT("MIL does not support a bit count of zero with BMP files.")
MILERR( M_ERR,53,SUBMSG,1,       MIL_TEXT("ActiveMIL does not support a bit count of zero with BMP files."))
#define M_ERR_53_SUBMSG_2        MIL_TEXT("MIL does not support 1-bit BMP files.")
MILERR( M_ERR,53,SUBMSG,2,       MIL_TEXT("ActiveMIL does not support 1-bit BMP files."))
#define M_ERR_53_SUBMSG_3        MIL_TEXT("MIL does not support 4-bit BMP files.")
MILERR( M_ERR,53,SUBMSG,3,       MIL_TEXT("ActiveMIL does not support 4-bit BMP files."))
#define M_ERR_53_SUBMSG_4        MIL_TEXT("Run Length Encoding ( RLE ) compression not supported.")
#define M_ERR_53_SUBMSG_5        NO_SUBMSG
#define M_ERR_53_SUBMSG_6        NO_SUBMSG
#define M_ERR_53_SUBMSG_7        NO_SUBMSG
#define M_ERR_53_SUBMSG_8        NO_SUBMSG
#define M_ERR_53_SUBMSG_9        NO_SUBMSG

#define M_JPEG_ERROR_3           54L
#define M_ERR_54_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_54_SUBMSG_1        MIL_TEXT("Invalid JPEG data.")
#define M_ERR_54_SUBMSG_2        MIL_TEXT("Invalid data for a MTRX specific marker.")
#define M_ERR_54_SUBMSG_3        MIL_TEXT("Extended Sequential DCT not supported in MIL.")
#define M_ERR_54_SUBMSG_4        MIL_TEXT("Progressive DCT not supported in MIL.")
MILERR( M_ERR,54,SUBMSG,4,       MIL_TEXT("Progressive DCT not supported in ActiveMIL."))
#define M_ERR_54_SUBMSG_5        MIL_TEXT("YUV9 Packed images not supported.")
#define M_ERR_54_SUBMSG_6        MIL_TEXT("YUV12 Packed images not supported.")
#define M_ERR_54_SUBMSG_7        MIL_TEXT("YUV24 Packed images not supported.")
#define M_ERR_54_SUBMSG_8        MIL_TEXT("Invalid data. EOI marker not found.")
#define M_ERR_54_SUBMSG_9        MIL_TEXT("Cannot create or open file in write mode.")
  
#define M_ALLOC_ERROR_3          55L
#define M_ERR_55_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_55_SUBMSG_1        MIL_TEXT("No pitch control flag used in create")
#define M_ERR_55_SUBMSG_2        MIL_TEXT("Cannot create a buffer with a physical address.")
#define M_ERR_55_SUBMSG_3        MIL_TEXT("Cannot allocate a M_COMPRESS buffer with the M_DISP attribute.")
MILERR( M_ERR,55,SUBMSG,3,       MIL_TEXT("Cannot allocate an image with a compression type and the CanDisplay property set to True."))
#define M_ERR_55_SUBMSG_4        MIL_TEXT("Cannot allocate a M_COMPRESS buffer with the M_SIGNED type.")
MILERR( M_ERR,55,SUBMSG,4,       MIL_TEXT("Cannot allocate an image with a compression type and the DataType property set to imSigned."))
#define M_ERR_55_SUBMSG_5        MIL_TEXT("Interlaced buffers should have a height of at least 2.")
#define M_ERR_55_SUBMSG_6        MIL_TEXT("Requested system DLL cannot be loaded.")
#define M_ERR_55_SUBMSG_7        MIL_TEXT("MIL DLLs not found.")
#define M_ERR_55_SUBMSG_8        MIL_TEXT("Not enough non-paged memory to allocate the buffer.")
#define M_ERR_55_SUBMSG_9        MIL_TEXT("Not enough non-paged memory for a MIL CE allocation.\nContinuing the application may cause abnormal behavior!")

#define M_LIMITATION_ERROR       56L
#define M_ERR_56_MSG             MIL_TEXT("Limitation error.")
#define M_ERR_56_SUBMSG_1        MIL_TEXT("This operation cannot be performed on a section of a compressed buffer.")
#define M_ERR_56_SUBMSG_2        MIL_TEXT("This operation cannot be performed on a child of a compressed buffer.")
#define M_ERR_56_SUBMSG_3        MIL_TEXT("This operation cannot be performed on a section of a YUV buffer.")
#define M_ERR_56_SUBMSG_4        MIL_TEXT("This operation cannot be performed on a child of a YUV buffer.")
#define M_ERR_56_SUBMSG_5        MIL_TEXT("This operation cannot be performed on a section of an M_PACKED buffer.")
MILERR( M_ERR,56,SUBMSG,5,       MIL_TEXT("This operation cannot be performed on a section of an imPacked format image."))
#define M_ERR_56_SUBMSG_6        MIL_TEXT("This operation cannot be performed on a child of an M_PACKED buffer.")
MILERR( M_ERR,56,SUBMSG,6,       MIL_TEXT("This operation cannot be performed on a child of an imPacked format image."))
#define M_ERR_56_SUBMSG_7        MIL_TEXT("This operation cannot be performed on a section of a M_PLANAR buffer.")
MILERR( M_ERR,56,SUBMSG,7,       MIL_TEXT("This operation cannot be performed on a section of an imPlanar format image."))
#define M_ERR_56_SUBMSG_8        MIL_TEXT("This operation cannot be performed on a child of a M_PLANAR buffer.")
MILERR( M_ERR,56,SUBMSG,8,       MIL_TEXT("This operation cannot be performed on a child of an imPlanar format image."))
#define M_ERR_56_SUBMSG_9        MIL_TEXT("This operation can only be performed on a compressed buffer.")

#define M_OPERATION_ERROR_2      57L
#define M_ERR_57_MSG             MIL_TEXT("Operation error.")
#define M_ERR_57_SUBMSG_1        MIL_TEXT("Pitch must be a multiple of 4 pixels.")
#define M_ERR_57_SUBMSG_2        MIL_TEXT("The default PitchByte value is incompatible with this type of buffer.")
#define M_ERR_57_SUBMSG_3        MIL_TEXT("Operation not supported on remote systems.")
#define M_ERR_57_SUBMSG_4        MIL_TEXT("Not enough non-paged memory to perform the operation on a remote system.")
#define M_ERR_57_SUBMSG_5        MIL_TEXT("Not enough remote memory to perform the operation on a remote system.")
#define M_ERR_57_SUBMSG_6        MIL_TEXT("Operation not supported on this system")
#define M_ERR_57_SUBMSG_7        MIL_TEXT("Cannot allocate event.")
#define M_ERR_57_SUBMSG_8        MIL_TEXT("Cannot create event.")
#define M_ERR_57_SUBMSG_9        MIL_TEXT("Buffer low level handle is invalid.")

#define M_LICENSING_ERROR        58L
#define M_ERR_58_MSG             MIL_TEXT("Licensing error")
#define M_ERR_58_SUBMSG_1        MIL_TEXT("A processing function was used with MIL-Lite.")
#define M_ERR_58_SUBMSG_2        MIL_TEXT("License watchdog timed out.")
#define M_ERR_58_SUBMSG_3        MIL_TEXT("A module was used without a valid license.")
#define M_ERR_58_SUBMSG_4        MIL_TEXT("Debugging is not allowed with a run-time license. You must have a development license.")
#define M_ERR_58_SUBMSG_5        MIL_TEXT("Your license does not allow the allocation of JPEG buffers.")
#define M_ERR_58_SUBMSG_6        MIL_TEXT("Your license does not allow the allocation of JPEG2000 buffers.")
#define M_ERR_58_SUBMSG_7        MIL_TEXT("A module not permitted by MappControl(M_LICENSE_PERMIT_MODULES) was used.")
#define M_ERR_58_SUBMSG_8        MIL_TEXT("This Early Access version of MIL has expired. Please contact your Matrox representative to obtain an updated version.")
#define M_ERR_58_SUBMSG_9        MIL_TEXT("The validity period of your MIL license is over. Please contact your Matrox representative to obtain a new license.")

#define M_AVI_FILE_ERROR_2       59L
#define M_ERR_59_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_59_SUBMSG_1        NO_SUBMSG
#define M_ERR_59_SUBMSG_2        NO_SUBMSG
#define M_ERR_59_SUBMSG_3        NO_SUBMSG
#define M_ERR_59_SUBMSG_4        NO_SUBMSG
#define M_ERR_59_SUBMSG_5        MIL_TEXT("Cannot write frame. The AVI file size limit has been reached.")
#define M_ERR_59_SUBMSG_6        MIL_TEXT("Impossible to write into a closed file.")
#define M_ERR_59_SUBMSG_7        MIL_TEXT("Error creating AVI stream.")
#define M_ERR_59_SUBMSG_8        MIL_TEXT("The file is already open.")
#define M_ERR_59_SUBMSG_9        MIL_TEXT("Impossible to read from a closed file.")

#define M_JPEG_COMPRESS_ERROR_3  60L
#define M_ERR_60_MSG             MIL_TEXT("JPEG compression error.")
#define M_ERR_60_SUBMSG_1        MIL_TEXT("Cannot allocate 3-band M_JPEG_LOSSLESS_INTERLACED buffers.")
MILERR( M_ERR,60,SUBMSG,1,       MIL_TEXT("Cannot allocate 3-band images with the Format property set to imJPEGLosslessInterlaced.")) 
#define M_ERR_60_SUBMSG_2        MIL_TEXT("In lossless, the RestartInterval multiplied by the number of \ncolumns in the buffer must fit in 16 bits (smaller than 65536).")
#define M_ERR_60_SUBMSG_3        MIL_TEXT("The restart interval must fit in 16 bits (smaller than 65536).")
#define M_ERR_60_SUBMSG_4        MIL_TEXT("Only JPEG lossless buffers can have predictors.")
#define M_ERR_60_SUBMSG_5        MIL_TEXT("Luminance parameters are only allowed for YUV buffers.")
#define M_ERR_60_SUBMSG_6        MIL_TEXT("Chrominance parameters are only allowed for YUV buffers.")
#define M_ERR_60_SUBMSG_7        MIL_TEXT("AC tables and quantization parameters are only allowed \nfor JPEG lossy buffers.")
#define M_ERR_60_SUBMSG_8        MIL_TEXT("For YUV buffers, specific luminance or chrominance \nflags must be used.")
#define M_ERR_60_SUBMSG_9        MIL_TEXT("Field size is only applicable to interlaced buffers.")

#define M_AVI_FILE_ERROR_3       61L
#define M_ERR_61_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_61_SUBMSG_1        MIL_TEXT("Error reading from the AVI file.")
#define M_ERR_61_SUBMSG_2        MIL_TEXT("Cannot read after the last frame.")
#define M_ERR_61_SUBMSG_3        NO_SUBMSG
#define M_ERR_61_SUBMSG_4        MIL_TEXT("Images must have a width greater than or equal to 16.")
#define M_ERR_61_SUBMSG_5        MIL_TEXT("Images must have a height greater than or equal to 8.")
#define M_ERR_61_SUBMSG_6        NO_SUBMSG
#define M_ERR_61_SUBMSG_7        MIL_TEXT("The frame rate has not been set.")
#define M_ERR_61_SUBMSG_8        NO_SUBMSG
#define M_ERR_61_SUBMSG_9        MIL_TEXT("The AVI file size exceeds the supported limit.")

#define M_USER_BIT_CONFIG_ERROR  62L         // These 2 following message are use for user bits of 4sightII
#define M_ERR_62_MSG             NO_MSG      // Now the error message are move the the milmtxapi.dll
#define M_ERR_62_SUBMSG_1        NO_SUBMSG
#define M_ERR_62_SUBMSG_2        NO_SUBMSG
#define M_ERR_62_SUBMSG_3        NO_SUBMSG
#define M_ERR_62_SUBMSG_4        NO_SUBMSG
#define M_ERR_62_SUBMSG_5        NO_SUBMSG
#define M_ERR_62_SUBMSG_6        NO_SUBMSG
#define M_ERR_62_SUBMSG_7        NO_SUBMSG
#define M_ERR_62_SUBMSG_8        NO_SUBMSG
#define M_ERR_62_SUBMSG_9        NO_SUBMSG

#define M_USER_BIT_ERROR         63L
#define M_ERR_63_MSG             NO_MSG
#define M_ERR_63_SUBMSG_1        NO_SUBMSG
#define M_ERR_63_SUBMSG_2        NO_SUBMSG
#define M_ERR_63_SUBMSG_3        NO_SUBMSG
#define M_ERR_63_SUBMSG_4        NO_SUBMSG
#define M_ERR_63_SUBMSG_5        NO_SUBMSG
#define M_ERR_63_SUBMSG_6        NO_SUBMSG
#define M_ERR_63_SUBMSG_7        NO_SUBMSG
#define M_ERR_63_SUBMSG_8        NO_SUBMSG
#define M_ERR_63_SUBMSG_9        NO_SUBMSG

#define M_TIFF_ERROR_3           64L
#define M_ERR_64_MSG             MIL_TEXT("TIFF File access error.")
#define M_ERR_64_SUBMSG_1        MIL_TEXT("Error recording tag")
#define M_ERR_64_SUBMSG_2        MIL_TEXT("LZW compression not supported in multi strip TIFF files")
#define M_ERR_64_SUBMSG_3        NO_SUBMSG
#define M_ERR_64_SUBMSG_4        NO_SUBMSG
#define M_ERR_64_SUBMSG_5        NO_SUBMSG
#define M_ERR_64_SUBMSG_6        NO_SUBMSG
#define M_ERR_64_SUBMSG_7        NO_SUBMSG
#define M_ERR_64_SUBMSG_8        NO_SUBMSG
#define M_ERR_64_SUBMSG_9        NO_SUBMSG

#define M_MIL_FILE_ERROR_4       65L
#define M_ERR_65_MSG             MIL_TEXT("MIL File access error.")
#define M_ERR_65_SUBMSG_1        MIL_TEXT("Error recording tag")
#define M_ERR_65_SUBMSG_2        MIL_TEXT("LZW compression not supported in multi strip MIL files")
#define M_ERR_65_SUBMSG_3        NO_SUBMSG
#define M_ERR_65_SUBMSG_4        NO_SUBMSG
#define M_ERR_65_SUBMSG_5        NO_SUBMSG
#define M_ERR_65_SUBMSG_6        NO_SUBMSG
#define M_ERR_65_SUBMSG_7        NO_SUBMSG
#define M_ERR_65_SUBMSG_8        NO_SUBMSG
#define M_ERR_65_SUBMSG_9        NO_SUBMSG

#define M_JPEG_ERROR_4           66L
#define M_ERR_66_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_66_SUBMSG_1        MIL_TEXT("Second field of interlaced image not found.")
#define M_ERR_66_SUBMSG_2        MIL_TEXT("Buffer width is greater than the maximum supported.")
#define M_ERR_66_SUBMSG_3        MIL_TEXT("Buffer height is greater than the maximum supported.")
#define M_ERR_66_SUBMSG_4        NO_SUBMSG
#define M_ERR_66_SUBMSG_5        NO_SUBMSG
#define M_ERR_66_SUBMSG_6        NO_SUBMSG
#define M_ERR_66_SUBMSG_7        NO_SUBMSG
#define M_ERR_66_SUBMSG_8        NO_SUBMSG
#define M_ERR_66_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_10 67L
#define M_ERR_67_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_67_SUBMSG_1        MIL_TEXT("The width and height of the source and destination buffers must be a multiple of 8.")
#define M_ERR_67_SUBMSG_2        MIL_TEXT("Operation not supported on 16 bits buffer.")
#define M_ERR_67_SUBMSG_3        MIL_TEXT("Size of image buffers must be greater than or equal to the size of the kernel.")
MILERR( M_ERR,67,SUBMSG,3,       MIL_TEXT("Size of images must be greater than or equal to the size of the kernel."))
#define M_ERR_67_SUBMSG_4        MIL_TEXT("Invalid data formats")
#define M_ERR_67_SUBMSG_5        MIL_TEXT("Operation not supported on 3 bands planar buffers.")
#define M_ERR_67_SUBMSG_6        MIL_TEXT("Float addresses must be a multiple of 4")
#define M_ERR_67_SUBMSG_7        MIL_TEXT("This operation is only supported on the host")
#define M_ERR_67_SUBMSG_8        MIL_TEXT("Cannot create an M_NO_MAP buffer with null pointers")
#define M_ERR_67_SUBMSG_9        MIL_TEXT("Can only create a M_NO_MAP buffer with a physical address")

#define M_J2K_ERROR_1            68L
#define M_ERR_68_MSG             MIL_TEXT("JPEG2000 handler general error.")
#define M_ERR_68_SUBMSG_1        MIL_TEXT("Error closing JPEG2000 file.")
#define M_ERR_68_SUBMSG_2        MIL_TEXT("Unable to allocate sufficient memory.")
#define M_ERR_68_SUBMSG_3        MIL_TEXT("Cannot create or open file in write mode.")
#define M_ERR_68_SUBMSG_4        MIL_TEXT("Error opening JPEG2000 file.")
#define M_ERR_68_SUBMSG_5        NO_SUBMSG
#define M_ERR_68_SUBMSG_6        NO_SUBMSG
#define M_ERR_68_SUBMSG_7        NO_SUBMSG
#define M_ERR_68_SUBMSG_8        NO_SUBMSG
#define M_ERR_68_SUBMSG_9        NO_SUBMSG

#define M_J2K_ERROR_2            69L
#define M_ERR_69_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_69_SUBMSG_1        MIL_TEXT("Invalid JPEG2000 data.")
#define M_ERR_69_SUBMSG_2        MIL_TEXT("Unexpected marker in the JPEG2000 image.")
#define M_ERR_69_SUBMSG_3        MIL_TEXT("Component index out of range.")
#define M_ERR_69_SUBMSG_4        MIL_TEXT("MIL supports only 1-band and 3-band buffers.")
MILERR( M_ERR,69,SUBMSG,4,       MIL_TEXT("ActiveMIL supports only 1-band and 3-band buffers."))
#define M_ERR_69_SUBMSG_5        MIL_TEXT("All components must have the same bit depth.")
#define M_ERR_69_SUBMSG_6        MIL_TEXT("Unsupported bit depth.")
#define M_ERR_69_SUBMSG_7        MIL_TEXT("Invalid subsampling factors.")
#define M_ERR_69_SUBMSG_8        MIL_TEXT("Scalar implicit quantization not supported.")
#define M_ERR_69_SUBMSG_9        MIL_TEXT("Unsupported coding style.")

#define M_LICENSE_ERROR_2        70L
#define M_ERR_70_MSG             MIL_TEXT("License error.")
#define M_ERR_70_SUBMSG_1        MIL_TEXT("No valid license found (1)")
#define M_ERR_70_SUBMSG_2        MIL_TEXT("No valid license found (2)")
#define M_ERR_70_SUBMSG_3        MIL_TEXT("No valid license found (3)")
#define M_ERR_70_SUBMSG_4        NO_SUBMSG
#define M_ERR_70_SUBMSG_5        NO_SUBMSG
#define M_ERR_70_SUBMSG_6        MIL_TEXT("No valid license found (6)")
#define M_ERR_70_SUBMSG_7        NO_SUBMSG
#define M_ERR_70_SUBMSG_8        NO_SUBMSG
#define M_ERR_70_SUBMSG_9        NO_SUBMSG

#define M_J2K_ERROR_3            71L
#define M_ERR_71_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_71_SUBMSG_1        MIL_TEXT("Unsupported progression order.")
#define M_ERR_71_SUBMSG_2        MIL_TEXT("Multi-layer images are not supported.")
#define M_ERR_71_SUBMSG_3        MIL_TEXT("Unsupported compression setting.")
#define M_ERR_71_SUBMSG_4        MIL_TEXT("This marker is not supported by MIL yet.")
MILERR( M_ERR,71,SUBMSG,4,       MIL_TEXT("This marker is not supported by ActiveMIL yet."))
#define M_ERR_71_SUBMSG_5        MIL_TEXT("Wavelet type cannot be changed.")
#define M_ERR_71_SUBMSG_6        MIL_TEXT("Mismatched field settings.")
#define M_ERR_71_SUBMSG_7        MIL_TEXT("Not enough user memory to do the operation.")
#define M_ERR_71_SUBMSG_8        MIL_TEXT("Invalid number of decomposition levels.")
#define M_ERR_71_SUBMSG_9        MIL_TEXT("Invalid number of wavelet sub-bands.")

#define M_J2K_ERROR_4            72L
#define M_ERR_72_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_72_SUBMSG_1        MIL_TEXT("The target size must be a positive number of bytes.")
#define M_ERR_72_SUBMSG_2        MIL_TEXT("Target size is only allowed in lossy modes.")
#define M_ERR_72_SUBMSG_3        MIL_TEXT("Quantization tables are applicable to lossy buffers only.")
#define M_ERR_72_SUBMSG_4        MIL_TEXT("The Q factor is only valid with lossy buffers.")
#define M_ERR_72_SUBMSG_5        MIL_TEXT("Wrong number of entries in the quantization table.")
#define M_ERR_72_SUBMSG_6        MIL_TEXT("Invalid MIL_ID for the quantization table.")
#define M_ERR_72_SUBMSG_7        MIL_TEXT("The quantization table must be one-band, 32-bit floating-point, one-dimensional, and M_ARRAY.")
MILERR( M_ERR,72,SUBMSG,7,       MIL_TEXT("The quantization table must be a 1-dimensional array of type 32-bit Single (float)."))
#define M_ERR_72_SUBMSG_8        MIL_TEXT("Valid Q factor values are between 1 and 99 (both inclusive).")
#define M_ERR_72_SUBMSG_9        MIL_TEXT("Unexpected number of tile-parts.")

#define M_J2K_ERROR_5            73L
#define M_ERR_73_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_73_SUBMSG_1        MIL_TEXT("Corrupted JPEG2000 data.")
#define M_ERR_73_SUBMSG_2        MIL_TEXT("Quantization coefficient out of range.")
#define M_ERR_73_SUBMSG_3        MIL_TEXT("Luminance and chrominance parameters are only allowed for YUV buffers.")
#define M_ERR_73_SUBMSG_4        MIL_TEXT("The number of reserved bytes must be greater than or equal to 0.")
#define M_ERR_73_SUBMSG_5        MIL_TEXT("Tile offsets are out of range.")
#define M_ERR_73_SUBMSG_6        MIL_TEXT("Image offsets are out of range.")
#define M_ERR_73_SUBMSG_7        MIL_TEXT("Only one COC marker by band is allowed.")
#define M_ERR_73_SUBMSG_8        MIL_TEXT("Only one QCC marker by band is allowed.")
#define M_ERR_73_SUBMSG_9        MIL_TEXT("Invalid size bit.")

#define M_FUNC_CALL_ERROR        74L
#define M_ERR_74_MSG             MIL_TEXT("Function call error.")
#define M_ERR_74_SUBMSG_1        MIL_TEXT("Calibration not supported on remote systems.")
#define M_ERR_74_SUBMSG_2        MIL_TEXT("Unable to load the DLL.")
#define M_ERR_74_SUBMSG_3        MIL_TEXT("Slave function not found in the DLL.")
#define M_ERR_74_SUBMSG_4        MIL_TEXT("Cannot execute because two MIL objects reside in two different workspaces/platforms and compensation cannot be done.") //TBM MIL 8
MILERR( M_ERR,74,SUBMSG,4,       MIL_TEXT("Cannot execute because two ActiveMIL objects reside in two different workspaces/platforms and compensation cannot be done."))
#define M_ERR_74_SUBMSG_5        MIL_TEXT("Slave module is not in the user module table.")
#define M_ERR_74_SUBMSG_6        MIL_TEXT("Slave function is not in the user function table.")
#define M_ERR_74_SUBMSG_7        MIL_TEXT("No slave function pointer specified.")
#define M_ERR_74_SUBMSG_8        MIL_TEXT("No slave function in the internal function table.")
#define M_ERR_74_SUBMSG_9        MIL_TEXT("The function table already contains a function pointer.\nCheck that you have not given the same opcode to 2 different functions.")

#define M_OPERATION_ERROR_3      75L
#define M_ERR_75_MSG             MIL_TEXT("Operation error.")
#define M_ERR_75_SUBMSG_1        MIL_TEXT("Cannot free internally allocated objects.")
#define M_ERR_75_SUBMSG_2        MIL_TEXT("SystemId and ObjectType are incompatible.") // MthrAlloc
MILERR( M_ERR,75,SUBMSG,2,       MIL_TEXT("The OwnerSystem is not compatible with this type of Threading sub-object."))
#define M_ERR_75_SUBMSG_3        MIL_TEXT("Thread or event id is not compatible with the control flag specified") // MthrControl
MILERR( M_ERR,75,SUBMSG,3,       MIL_TEXT("Thread or event is not compatible with the last method or property called."))
#define M_ERR_75_SUBMSG_4        MIL_TEXT("Cannot perform operation with this thread or event id")
MILERR( M_ERR,75,SUBMSG,4,       MIL_TEXT("Cannot perform operation with this thread or event."))
#define M_ERR_75_SUBMSG_5        MIL_TEXT("Cannot perform operation on unmapped buffer(s).")
#define M_ERR_75_SUBMSG_6        MIL_TEXT("Cannot map buffers.")
#define M_ERR_75_SUBMSG_7        MIL_TEXT("Buffer must have M_DIRECTX in its format.")
MILERR( M_ERR,75,SUBMSG,7,       MIL_TEXT("Image's format must be imDirectX."))
#define M_ERR_75_SUBMSG_8        MIL_TEXT("Cannot map 2 buffers of the same family at the same time.")
#define M_ERR_75_SUBMSG_9        MIL_TEXT("Buffer cannot have child buffers.")

#define M_BUF_TRANSFER_ERROR     76L
#define M_ERR_76_MSG             MIL_TEXT("Transfer Error")
#define M_ERR_76_SUBMSG_1        MIL_TEXT("Unknown transfer function.")
#define M_ERR_76_SUBMSG_2        MIL_TEXT("Transfer method not supported for this transfer function.")
#define M_ERR_76_SUBMSG_3        MIL_TEXT("Transfer cannot be done asynchronously.")
#define M_ERR_76_SUBMSG_4        MIL_TEXT("Scaling not supported by this transfer function.")
#define M_ERR_76_SUBMSG_5        MIL_TEXT("No transfer made.")
#define M_ERR_76_SUBMSG_6        MIL_TEXT("MTX0 transfer only supported on MTX0 buffers.")
#define M_ERR_76_SUBMSG_7        MIL_TEXT("MTX0 not supported in this environment.")
#define M_ERR_76_SUBMSG_8        MIL_TEXT("Illegal null MIL_ID passed to MbufTransfer.")
#define M_ERR_76_SUBMSG_9        MIL_TEXT("Invalid Transfer type.")

#define M_DISP_SERVICE_ERROR     77L
#define M_ERR_77_MSG             MIL_TEXT("Display service error.")
#define M_ERR_77_SUBMSG_1        MIL_TEXT("Cannot load MilDisplay DLL")
#define M_ERR_77_SUBMSG_2        MIL_TEXT("Cannot find address of requested function.")
#define M_ERR_77_SUBMSG_3        MIL_TEXT("Cannot find AppAlloc function in MilDisplay.")
#define M_ERR_77_SUBMSG_4        MIL_TEXT("Cannot find AppFree function in MilDisplay.")
#define M_ERR_77_SUBMSG_5        MIL_TEXT("Display service should not be called in PPC.")
#define M_ERR_77_SUBMSG_6        NO_SUBMSG
#define M_ERR_77_SUBMSG_7        NO_SUBMSG
#define M_ERR_77_SUBMSG_8        NO_SUBMSG
#define M_ERR_77_SUBMSG_9        NO_SUBMSG

#define M_ALLOC_ERROR_4          78L
#define M_ERR_78_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_78_SUBMSG_1        MIL_TEXT("M_BGR15 and M_BGR16 buffers are not supported.")
MILERR( M_ERR,78,SUBMSG,1,       MIL_TEXT("15-bit and 16-bit (BGR) images are not supported."))
#define M_ERR_78_SUBMSG_2        MIL_TEXT("The requested system is not (correctly) installed.")
#define M_ERR_78_SUBMSG_3        MIL_TEXT("Not enough logical address space to map the buffer.")
#define M_ERR_78_SUBMSG_4        MIL_TEXT("Cannot open the DCF.")
#define M_ERR_78_SUBMSG_5        MIL_TEXT("Cannot create a buffer at address 0.")
#define M_ERR_78_SUBMSG_6        MIL_TEXT("Cannot allocate a M_MAPPABLE buffer with the M_DISP attribute.")
#define M_ERR_78_SUBMSG_7        MIL_TEXT("The driver DLL has an invalid format and cannot be loaded.")
#define M_ERR_78_SUBMSG_8        MIL_TEXT("Invalid bits set in the attribute.")
#define M_ERR_78_SUBMSG_9        MIL_TEXT("The M_NO_PARSING control flag is only available to M_COMPRESS buffers.")

#define M_SYS_CTRL_INQ_ERROR     79L
#define M_ERR_79_MSG             MIL_TEXT("System Control/Inquire error.")
#define M_ERR_79_SUBMSG_1        MIL_TEXT("Control/Inquire type supported only on the Host system")
MILERR( M_ERR,79,SUBMSG,1,       MIL_TEXT("Method or property supported only on the Host system."))
#define M_ERR_79_SUBMSG_2        MIL_TEXT("Default PitchByte must be a power of 2.")
#define M_ERR_79_SUBMSG_3        MIL_TEXT("This Control/Inquire is not supported any more")
MILERR( M_ERR,79,SUBMSG,3,       MIL_TEXT("This method or property is not supported any more."))
#define M_ERR_79_SUBMSG_4        MIL_TEXT("This Control/Inquire is now a Digitizer Control/Inquire")
MILERR( M_ERR,79,SUBMSG,4,       MIL_TEXT("This method or property is now a Digitizer method or property."))
#define M_ERR_79_SUBMSG_5        MIL_TEXT("This Control/Inquire is now a Display Control/Inquire")
MILERR( M_ERR,79,SUBMSG,5,       MIL_TEXT("This method or property is now a Display method or property."))
#define M_ERR_79_SUBMSG_6        NO_SUBMSG
#define M_ERR_79_SUBMSG_7        NO_SUBMSG
#define M_ERR_79_SUBMSG_8        NO_SUBMSG
#define M_ERR_79_SUBMSG_9        NO_SUBMSG

#define M_APP_MODIF_ERROR        80L
#define M_ERR_80_MSG             MIL_TEXT("Swap ID error.")
#define M_ERR_80_SUBMSG_1        MIL_TEXT("This function does not support remote objects.")
#define M_ERR_80_SUBMSG_2        NO_SUBMSG
#define M_ERR_80_SUBMSG_3        NO_SUBMSG
#define M_ERR_80_SUBMSG_4        NO_SUBMSG
#define M_ERR_80_SUBMSG_5        NO_SUBMSG
#define M_ERR_80_SUBMSG_6        NO_SUBMSG
#define M_ERR_80_SUBMSG_7        NO_SUBMSG
#define M_ERR_80_SUBMSG_8        NO_SUBMSG
#define M_ERR_80_SUBMSG_9        NO_SUBMSG

#define M_INSTALLATION_ERROR     81L
#define M_ERR_81_MSG             MIL_TEXT("Installation error")
#define M_ERR_81_SUBMSG_1        MIL_TEXT("Could not find the installation path in the registry.")
#define M_ERR_81_SUBMSG_2        MIL_TEXT("The list of installed boards is corrupted in the registry. Please re-install MIL.")
MILERR( M_ERR,81,SUBMSG,2,       MIL_TEXT("The list of installed boards is corrupted in the registry. Please re-install ActiveMIL."))
#define M_ERR_81_SUBMSG_3        NO_SUBMSG
#define M_ERR_81_SUBMSG_4        NO_SUBMSG
#define M_ERR_81_SUBMSG_5        NO_SUBMSG
#define M_ERR_81_SUBMSG_6        NO_SUBMSG
#define M_ERR_81_SUBMSG_7        NO_SUBMSG
#define M_ERR_81_SUBMSG_8        NO_SUBMSG
#define M_ERR_81_SUBMSG_9        NO_SUBMSG

#define M_BUF_CTRL_INQ_ERROR     82L
#define M_ERR_82_MSG             MIL_TEXT("Buffer Control/Inquire error.")
#define M_ERR_82_SUBMSG_1        MIL_TEXT("Invalid index of bands.")
#define M_ERR_82_SUBMSG_2        NO_SUBMSG
#define M_ERR_82_SUBMSG_3        NO_SUBMSG
#define M_ERR_82_SUBMSG_4        NO_SUBMSG
#define M_ERR_82_SUBMSG_5        NO_SUBMSG
#define M_ERR_82_SUBMSG_6        NO_SUBMSG
#define M_ERR_82_SUBMSG_7        NO_SUBMSG
#define M_ERR_82_SUBMSG_8        NO_SUBMSG
#define M_ERR_82_SUBMSG_9        NO_SUBMSG

#define M_CALL_PA_PARAM_ERROR    83L
#define M_ERR_83_MSG             MIL_TEXT("Invalid parameter in user function call.")
#define M_ERR_83_SUBMSG_1        MIL_TEXT("All the MIL IDs need to be allocated on the same system.")
MILERR( M_ERR,83,SUBMSG,1,       MIL_TEXT("All controls need to be allocated on the same system."))
#define M_ERR_83_SUBMSG_2        MIL_TEXT("Only buffer IDs are supported.")
MILERR( M_ERR,83,SUBMSG,2,       MIL_TEXT("Only images are supported."))
#define M_ERR_83_SUBMSG_3        MIL_TEXT("At least one parameter must be an ID")
#define M_ERR_83_SUBMSG_4        MIL_TEXT("Cannot execute user functions on the Host system.")
#define M_ERR_83_SUBMSG_5        MIL_TEXT("Too many parameters.")
#define M_ERR_83_SUBMSG_6        NO_SUBMSG
#define M_ERR_83_SUBMSG_7        NO_SUBMSG
#define M_ERR_83_SUBMSG_8        NO_SUBMSG
#define M_ERR_83_SUBMSG_9        NO_SUBMSG

#define M_DISP_CTRL_INQ_ERROR    84L
#define M_ERR_84_MSG             MIL_TEXT("Display Control/Inquire error.")
#define M_ERR_84_SUBMSG_1        MIL_TEXT("This Control/Inquire is no longer supported.")
MILERR( M_ERR,84,SUBMSG,1,       MIL_TEXT("This method or property is no longer supported."))
#define M_ERR_84_SUBMSG_2        NO_SUBMSG
#define M_ERR_84_SUBMSG_3        NO_SUBMSG
#define M_ERR_84_SUBMSG_4        NO_SUBMSG
#define M_ERR_84_SUBMSG_5        NO_SUBMSG
#define M_ERR_84_SUBMSG_6        NO_SUBMSG
#define M_ERR_84_SUBMSG_7        NO_SUBMSG
#define M_ERR_84_SUBMSG_8        NO_SUBMSG
#define M_ERR_84_SUBMSG_9        NO_SUBMSG

#define M_J2K_ERROR_6            85L
#define M_ERR_85_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_85_SUBMSG_1        MIL_TEXT("Too many tiles.")
#define M_ERR_85_SUBMSG_2        MIL_TEXT("Invalid code block size.")
#define M_ERR_85_SUBMSG_3        MIL_TEXT("Unexpected field delimiter.")
#define M_ERR_85_SUBMSG_4        MIL_TEXT("Video standard not supported.")
#define M_ERR_85_SUBMSG_5        MIL_TEXT("Unknown wavelet and quantization settings.")
#define M_ERR_85_SUBMSG_6        MIL_TEXT("Unknown entropy coder parameters.")
#define M_ERR_85_SUBMSG_7        MIL_TEXT("Code block attributes are truncated.")
#define M_ERR_85_SUBMSG_8        MIL_TEXT("The field is truncated.")
#define M_ERR_85_SUBMSG_9        MIL_TEXT("Invalid JP2 format.")

#define M_INVALID_PARAM_ERROR_11 86L
#define M_ERR_86_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_86_SUBMSG_1        MIL_TEXT("Mask buffer must be the same size as the source buffer.")
#define M_ERR_86_SUBMSG_2        MIL_TEXT("Invalid frame rate value.")
#define M_ERR_86_SUBMSG_3        MIL_TEXT("Invalid number of frames.")
#define M_ERR_86_SUBMSG_4        MIL_TEXT("Invalid file format flag.")
#define M_ERR_86_SUBMSG_5        MIL_TEXT("The file name pointer must not be null.")
#define M_ERR_86_SUBMSG_6        MIL_TEXT("The pointer to the array of frames must be null.")
#define M_ERR_86_SUBMSG_7        MIL_TEXT("The pointer to the array of frames must not be null.")
#define M_ERR_86_SUBMSG_8        MIL_TEXT("The number of frames must be 0.")
#define M_ERR_86_SUBMSG_9        MIL_TEXT("Invalid control flag.")

#define M_INVALID_PARAM_ERROR_12 87L
#define M_ERR_87_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_87_SUBMSG_1        MIL_TEXT("The start image value must be 0.")
#define M_ERR_87_SUBMSG_2        MIL_TEXT("Invalid start image value.")
#define M_ERR_87_SUBMSG_3        MIL_TEXT("The operation flag must be M_NULL.")
#define M_ERR_87_SUBMSG_4        MIL_TEXT("Invalid operation flag.")
MILERR( M_ERR,87,SUBMSG,4,       MIL_TEXT("Invalid operation."))
#define M_ERR_87_SUBMSG_5        MIL_TEXT("The system identifier must be M_NULL.")
#define M_ERR_87_SUBMSG_6        MIL_TEXT("Invalid system identifier.")
MILERR( M_ERR,87,SUBMSG,6,       MIL_TEXT("Invalid owner system."))
#define M_ERR_87_SUBMSG_7        MIL_TEXT("Invalid shen filter type.")
#define M_ERR_87_SUBMSG_8        MIL_TEXT("Invalid shen smooth factor range.")
MILERR( M_ERR,87,SUBMSG,8,       MIL_TEXT("Invalid shen FilterSmoothness."))
#define M_ERR_87_SUBMSG_9        MIL_TEXT("Invalid deriche filter type.")

#define M_INVALID_PARAM_ERROR_13 88L
#define M_ERR_88_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_88_SUBMSG_1        MIL_TEXT("Invalid deriche smooth factor range.")
MILERR( M_ERR,88,SUBMSG,1,       MIL_TEXT("Invalid deriche FilterSmoothness value."))
#define M_ERR_88_SUBMSG_2        MIL_TEXT("Difference between angles must be in the range of 0 - 360 degrees.")
#define M_ERR_88_SUBMSG_3        MIL_TEXT("Invalid array format.")
#define M_ERR_88_SUBMSG_4        MIL_TEXT("This operation requires a child buffer.")
#define M_ERR_88_SUBMSG_5        MIL_TEXT("Cannot move the buffer because it has a child.")
#define M_ERR_88_SUBMSG_6        MIL_TEXT("Cannot resize the buffer because it is selected on a display.")
#define M_ERR_88_SUBMSG_7        MIL_TEXT("Cannot move a compressed buffer.")
#define M_ERR_88_SUBMSG_8        MIL_TEXT("Type and attribute depths do not match.")
MILERR( M_ERR,88,SUBMSG,8,       MIL_TEXT("DataType and DataDepth do not match."))
#define M_ERR_88_SUBMSG_9        MIL_TEXT("Invalid internal format.")

#define M_BUF_TRANSFER_ERROR_2   89L
#define M_ERR_89_MSG             MIL_TEXT("Transfer Error")
#define M_ERR_89_SUBMSG_1        MIL_TEXT("Source and Destination buffers must belong to the same system.")
#define M_ERR_89_SUBMSG_2        MIL_TEXT("M_DRIVER_METHOD cannot be specified with other methods.")
#define M_ERR_89_SUBMSG_3        MIL_TEXT("Invalid composition source: planar buffer not supported.") 
#define M_ERR_89_SUBMSG_4        MIL_TEXT("Composition only supported on all bands (in source and destination).")
#define M_ERR_89_SUBMSG_5        MIL_TEXT("Composition is only supported with Mono8, Mono16, RGB16, BGR24 and BGR32 buffers.")
#define M_ERR_89_SUBMSG_6        MIL_TEXT("Destination buffer of composition must have the same format as the source buffer.")
#define M_ERR_89_SUBMSG_7        MIL_TEXT("Invalid composition source: yuv buffer not supported.")
#define M_ERR_89_SUBMSG_8        MIL_TEXT("Invalid offset and/or size specified.")
#define M_ERR_89_SUBMSG_9        MIL_TEXT("Float buffer not supported.")

#define M_J2K_ERROR_7            90L
#define M_ERR_90_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_90_SUBMSG_1        MIL_TEXT("Precinct size must be a power of two.")
#define M_ERR_90_SUBMSG_2        MIL_TEXT("Only the first resolution can have a precinct size of 1.")
#define M_ERR_90_SUBMSG_3        MIL_TEXT("Precinct size must not exceed 32768.")
#define M_ERR_90_SUBMSG_4        MIL_TEXT("Code block size must be a power of 2.")
#define M_ERR_90_SUBMSG_5        MIL_TEXT("The quantization table must be a one-band, 16 bits unsigned, one-dimensional M_ARRAY.")
MILERR( M_ERR,90,SUBMSG,5,       MIL_TEXT("The quantization table must be a one-band, 16 bits unsigned, one-dimensional array."))
#define M_ERR_90_SUBMSG_6        MIL_TEXT("Invalid MIL_ID for the precincts size table.")
#define M_ERR_90_SUBMSG_7        MIL_TEXT("The precincts size table must be a one-band, 16 bits unsigned, one-dimensional M_ARRAY.")
MILERR( M_ERR,90,SUBMSG,7,       MIL_TEXT("The precincts size table must be a one-band, 16 bits unsigned, one-dimensional array."))
#define M_ERR_90_SUBMSG_8        MIL_TEXT("Expected marker not found.")
#define M_ERR_90_SUBMSG_9        MIL_TEXT("The buffer contains invalid data.")

#define M_AUX_SERVICE_ERROR      91L
#define M_ERR_91_MSG             MIL_TEXT("Auxiliary service error")
#define M_ERR_91_SUBMSG_1        MIL_TEXT("Cannot load MilAux DLL")
#define M_ERR_91_SUBMSG_2        MIL_TEXT("Cannot load MilMtxApi DLL")
#define M_ERR_91_SUBMSG_3        MIL_TEXT("Cannot find address of requested function.")
#define M_ERR_91_SUBMSG_4        MIL_TEXT("Hardware not supported by Auxiliary Service.")
#define M_ERR_91_SUBMSG_5        NO_SUBMSG
#define M_ERR_91_SUBMSG_6        NO_SUBMSG
#define M_ERR_91_SUBMSG_7        NO_SUBMSG
#define M_ERR_91_SUBMSG_8        NO_SUBMSG
#define M_ERR_91_SUBMSG_9        NO_SUBMSG

#define M_ALLOC_ERROR_5          92L
#define M_ERR_92_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_92_SUBMSG_1        MIL_TEXT("Cannot create a buffer on this MIL_ID, the source buffer does not have a valid host address.")
#define M_ERR_92_SUBMSG_2        MIL_TEXT("Cannot create a buffer on this MIL_ID, the source buffer does not have a valid physical address.")
#define M_ERR_92_SUBMSG_3        MIL_TEXT("Invalid pitch value.")
#define M_ERR_92_SUBMSG_4        MIL_TEXT("Cannot allocate an on-board buffer with the M_MAPPABLE attribute.")
#define M_ERR_92_SUBMSG_5        MIL_TEXT("This system does not support allocations with a non-default pitch.")
#define M_ERR_92_SUBMSG_6        MIL_TEXT("Unable to map the non-paged buffer to a logical address.")
#define M_ERR_92_SUBMSG_7        MIL_TEXT("Unable to allocate digitizer using a non-ansi DCF file name.")
#define M_ERR_92_SUBMSG_8        MIL_TEXT("DirectX version not supported.")
#define M_ERR_92_SUBMSG_9        MIL_TEXT("Unable to allocate shadow for inter-system calls.")

#if (BW_COMPATIBILITY == 0x90)
   #define M_DGPRCSS_WATCHOG_ERROR  93L
   #define M_ERR_93_MSG             MIL_TEXT("MdigProcess Grab Monitor thread")
   #define M_ERR_93_SUBMSG_1        MIL_TEXT("No grab activity detected on digitizer:")
#else
   #define M_DGPRCSS_WATCHOG_ERROR 302 //This define was given to the user. It is now only available internally.
   #define M_FREE_TO_USE_ERROR  93L
   #define M_ERR_93_MSG             NO_SUBMSG
   #define M_ERR_93_SUBMSG_1        NO_SUBMSG
#endif
#define M_ERR_93_SUBMSG_2        NO_SUBMSG
#define M_ERR_93_SUBMSG_3        NO_SUBMSG
#define M_ERR_93_SUBMSG_4        NO_SUBMSG
#define M_ERR_93_SUBMSG_5        NO_SUBMSG
#define M_ERR_93_SUBMSG_6        NO_SUBMSG
#define M_ERR_93_SUBMSG_7        NO_SUBMSG
#define M_ERR_93_SUBMSG_8        NO_SUBMSG
#define M_ERR_93_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_14 94L
#define M_ERR_94_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_94_SUBMSG_1        MIL_TEXT("If using float buffers, all source and destination buffers must be float.")
#define M_ERR_94_SUBMSG_2        MIL_TEXT("A format must be specified for 3-band 8-bit images.")
#define M_ERR_94_SUBMSG_3        MIL_TEXT("All buffers must have the same SizeX and SizeY.")
#define M_ERR_94_SUBMSG_4        MIL_TEXT("All sources must have the same internal format.")
#define M_ERR_94_SUBMSG_5        MIL_TEXT("All destinations must have the same internal format.")
#define M_ERR_94_SUBMSG_6        MIL_TEXT("All sources must be allocated on the same system.")
#define M_ERR_94_SUBMSG_7        MIL_TEXT("All destinations must be allocated on the same system.")
#define M_ERR_94_SUBMSG_8        MIL_TEXT("Buffers must have at least 2 lines.")
#define M_ERR_94_SUBMSG_9        MIL_TEXT("SrcStartImage must between 0 and SrcImageCount-1.")

#define M_BUF_TRANSFER_ERROR_3   95L
#define M_ERR_95_MSG             MIL_TEXT("Transfer Error")
#define M_ERR_95_SUBMSG_1        MIL_TEXT("Keying color does not correspond to the source data.")
#define M_ERR_95_SUBMSG_2        MIL_TEXT("Invalid band")
#define M_ERR_95_SUBMSG_3        MIL_TEXT("Functionality is not implemented")
#define M_ERR_95_SUBMSG_4        MIL_TEXT("Unknown transfer function")
#define M_ERR_95_SUBMSG_5        MIL_TEXT("Unknown transfer mode")
#define M_ERR_95_SUBMSG_6        MIL_TEXT("A parameter is invalid")
#define M_ERR_95_SUBMSG_7        MIL_TEXT("Transfer not supported with the current license")
#define M_ERR_95_SUBMSG_8        MIL_TEXT("Unable to map a DirectX buffer")
#define M_ERR_95_SUBMSG_9        MIL_TEXT("All source parameter should be null")

#define M_J2K_ERROR_8            96L
#define M_ERR_96_MSG             MIL_TEXT("JPEG2000 compression error.")
#define M_ERR_96_SUBMSG_1        MIL_TEXT("Unable to allocate memory.")
#define M_ERR_96_SUBMSG_2        MIL_TEXT("The quantization style is only applicable to lossy buffers.")
#define M_ERR_96_SUBMSG_3        MIL_TEXT("EOC marker found in a packet body.")
#define M_ERR_96_SUBMSG_4        MIL_TEXT("The default quantization table identifier is invalid.")
#define M_ERR_96_SUBMSG_5        MIL_TEXT("Invalid operation mode.")
#define M_ERR_96_SUBMSG_6        NO_SUBMSG
#define M_ERR_96_SUBMSG_7        NO_SUBMSG
#define M_ERR_96_SUBMSG_8        NO_SUBMSG
#define M_ERR_96_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_15 97L
#define M_ERR_97_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_97_SUBMSG_1        MIL_TEXT("Only 8 and 16-bit source buffers are supported.")
#define M_ERR_97_SUBMSG_2        MIL_TEXT("Only 8 and 16-bit destination buffers are supported.")
#define M_ERR_97_SUBMSG_3        MIL_TEXT("All source buffers must be M_FLIP or M_NO_FLIP.")
#define M_ERR_97_SUBMSG_4        MIL_TEXT("All destination buffers must be M_FLIP or M_NO_FLIP.")
#define M_ERR_97_SUBMSG_5        MIL_TEXT("Invalid number of source buffers.")
#define M_ERR_97_SUBMSG_6        MIL_TEXT("Invalid number of destination buffers.")
#define M_ERR_97_SUBMSG_7        MIL_TEXT("M_MOTION_DETECT_REFERENCE_FRAME must be between 0 and M_MOTION_DETECT_NUM_FRAMES - 1 or set to one of the predefined values.")
#define M_ERR_97_SUBMSG_8        MIL_TEXT("ControlFlag cannot be zero.")
#define M_ERR_97_SUBMSG_9        MIL_TEXT("Invalid ControlFlag. Only one type of create is supported.")

#define M_INVALID_PARAM_ERROR_16 98L
#define M_ERR_98_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_98_SUBMSG_1        MIL_TEXT("Invalid pitch specified.")
#define M_ERR_98_SUBMSG_2        MIL_TEXT("One of the IDs in the list is not a valid event.")
#define M_ERR_98_SUBMSG_3        MIL_TEXT("All events do not belong to the same system type.")
#define M_ERR_98_SUBMSG_4        MIL_TEXT("M_VIDEO_HARDWARE_DEVICE cannot be used with something else.")
#define M_ERR_98_SUBMSG_5        MIL_TEXT("Invalid warp parameters.")
#define M_ERR_98_SUBMSG_6        MIL_TEXT("Invalid matrix size. Allowed values are 3 or 4 for SizeX, and 1 or 3 for SizeY.")
#define M_ERR_98_SUBMSG_7        MIL_TEXT("BayerBitShift must be lower than source SizeBit.")
#define M_ERR_98_SUBMSG_8        MIL_TEXT("Workspace already reserved.")
#define M_ERR_98_SUBMSG_9        MIL_TEXT("Invalid version.")

#define M_BUF_TRANSFER_ERROR_4   99L
#define M_ERR_99_MSG             MIL_TEXT("Transfer Error")
#define M_ERR_99_SUBMSG_1        MIL_TEXT("Destination buffer id should be null")
#define M_ERR_99_SUBMSG_2        MIL_TEXT("The scaling method (type of interpolation) is unknown.")
#define M_ERR_99_SUBMSG_3        MIL_TEXT("The scaling method (type of interpolation) is not supported.")
#define M_ERR_99_SUBMSG_4        MIL_TEXT("M_ALLOW_LARGER_RECT is not compatible with the scaling function.")
#define M_ERR_99_SUBMSG_5        MIL_TEXT("Autoscale is only supported on 32-bit buffers when the buffer is an image.")
#define M_ERR_99_SUBMSG_6        MIL_TEXT("Transfer type is invalid.")
#define M_ERR_99_SUBMSG_7        MIL_TEXT("The source of the autoscale function must be an image.")
#define M_ERR_99_SUBMSG_8        NO_SUBMSG
#define M_ERR_99_SUBMSG_9        NO_SUBMSG

#define M_COMPOSITION_ERROR      100L
#define M_ERR_100_MSG            MIL_TEXT("Composition Error")
#define M_ERR_100_SUBMSG_1       MIL_TEXT("M_BGRX32_COMPOSITION requires 1-band buffers.")
#define M_ERR_100_SUBMSG_2       MIL_TEXT("M_BGRX32_COMPOSITION requires 32-bit buffers.")
#define M_ERR_100_SUBMSG_3       MIL_TEXT("M_BGRX32_COMPOSITION does not accept M_FLOAT buffers.")
#define M_ERR_100_SUBMSG_4       NO_SUBMSG
#define M_ERR_100_SUBMSG_5       NO_SUBMSG
#define M_ERR_100_SUBMSG_6       NO_SUBMSG
#define M_ERR_100_SUBMSG_7       NO_SUBMSG
#define M_ERR_100_SUBMSG_8       NO_SUBMSG
#define M_ERR_100_SUBMSG_9       NO_SUBMSG

#define M_JPEG_COMPRESS_ERROR_4  101L
#define M_ERR_101_MSG            MIL_TEXT("JPEG compression error.")
#define M_ERR_101_SUBMSG_1       MIL_TEXT("Field order is only applicable to interlaced buffers.")
#define M_ERR_101_SUBMSG_2       MIL_TEXT("Invalid field order.")
#define M_ERR_101_SUBMSG_3       NO_SUBMSG
#define M_ERR_101_SUBMSG_4       NO_SUBMSG
#define M_ERR_101_SUBMSG_5       NO_SUBMSG
#define M_ERR_101_SUBMSG_6       NO_SUBMSG
#define M_ERR_101_SUBMSG_7       NO_SUBMSG
#define M_ERR_101_SUBMSG_8       NO_SUBMSG
#define M_ERR_101_SUBMSG_9       NO_SUBMSG

#define M_OPERATION_ERROR_6      102L
#define M_ERR_102_MSG            MIL_TEXT("Operation error.")
#define M_ERR_102_SUBMSG_1       MIL_TEXT("In place operations are not supported.")
#define M_ERR_102_SUBMSG_2       MIL_TEXT("Cannot free a thread from within the same thread.")
#define M_ERR_102_SUBMSG_3       MIL_TEXT("All parameters must be set in the context before calling the function.")
#define M_ERR_102_SUBMSG_4       MIL_TEXT("The buffer to draw has not been set in the context.")
#define M_ERR_102_SUBMSG_5       MIL_TEXT("MappFileOperation is not supported on Odyssey systems.")
#define M_ERR_102_SUBMSG_6       MIL_TEXT("Buffer is already unmapped.")
#define M_ERR_102_SUBMSG_7       MIL_TEXT("The size array must not be set in this mode.")
#define M_ERR_102_SUBMSG_8       MIL_TEXT("Operation does not support buffers with region.")
#define M_ERR_102_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_17 103L
#define M_ERR_103_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_103_SUBMSG_1       MIL_TEXT("Invalid file format flag. Cannot import MPEG4 sequences.")
#define M_ERR_103_SUBMSG_2       MIL_TEXT("Array of ids parameter contains both local and remote ids.")
#define M_ERR_103_SUBMSG_3       MIL_TEXT("InWarpParameter contain invalid coordinates.")
#define M_ERR_103_SUBMSG_4       MIL_TEXT("Cannot convert an internal data structure to 32-bit values.")
#define M_ERR_103_SUBMSG_5       MIL_TEXT("This control cannot be executed on a child buffer.")
#define M_ERR_103_SUBMSG_6       MIL_TEXT("A buffer id must be specified in order to determine the target host.")
#define M_ERR_103_SUBMSG_7       MIL_TEXT("A system id must be specified in order to determine the target host.")
#define M_ERR_103_SUBMSG_8       MIL_TEXT("Objects in array must have the same owner system.")
#define M_ERR_103_SUBMSG_9       MIL_TEXT("Invalid file format flag. Cannot import H264 sequences.")

#define M_LICENSING_ERROR_2      104L
#define M_ERR_104_MSG            MIL_TEXT("Licensing error.")
#define M_ERR_104_SUBMSG_1       MIL_TEXT("MIL Lite requires a Matrox Imaging board or a valid license.")
#define M_ERR_104_SUBMSG_2       MIL_TEXT("If a Matrox Imaging board is present, make sure it is correctly installed.")
#define M_ERR_104_SUBMSG_3       MIL_TEXT("This system requires a license.")
#define M_ERR_104_SUBMSG_4       MIL_TEXT("Your license does not allow JPEG compression.")
#define M_ERR_104_SUBMSG_5       MIL_TEXT("Your license does not allow JPEG2000 compression.")
#define M_ERR_104_SUBMSG_6       MIL_TEXT("Your license does not allow the use of JPEG-compressed sequences.")
#define M_ERR_104_SUBMSG_7       MIL_TEXT("Your license has reached its time limit.")
#define M_ERR_104_SUBMSG_8       MIL_TEXT("Your license does not allow the use of JPEG2000-compressed sequences.")
#define M_ERR_104_SUBMSG_9       NO_SUBMSG

#define M_ALLOC_ERROR_6          105L
#define M_ERR_105_MSG            MIL_TEXT("Allocation error.")
#define M_ERR_105_SUBMSG_1       MIL_TEXT("Unable to allocate memory.")
#define M_ERR_105_SUBMSG_2       MIL_TEXT("Cannot allocate temporary buffer.")
#define M_ERR_105_SUBMSG_3       MIL_TEXT("This system is not registered. Make sure the driver is started.")
#define M_ERR_105_SUBMSG_4       MIL_TEXT("Not enough memory for a MIL CE allocation.\nContinuing the application may cause abnormal behavior!")
#define M_ERR_105_SUBMSG_5       MIL_TEXT("Unable to allocate object because it is not of the expected type.")
#define M_ERR_105_SUBMSG_6       NO_SUBMSG
#define M_ERR_105_SUBMSG_7       NO_SUBMSG
#define M_ERR_105_SUBMSG_8       NO_SUBMSG
#define M_ERR_105_SUBMSG_9       NO_SUBMSG

#define M_FONT_ERROR             106L
#define M_ERR_106_MSG            MIL_TEXT("Font error.")
#define M_ERR_106_SUBMSG_1       MIL_TEXT("Invalid font or font not installed.") 
#define M_ERR_106_SUBMSG_2       MIL_TEXT("Invalid font name.")
#define M_ERR_106_SUBMSG_3       MIL_TEXT("The default fonts do not support all character codes of the text. Please use another font.") 
#define M_ERR_106_SUBMSG_4       MIL_TEXT("The specified fonts do not support all characters of the text. Please use another font.")
#define M_ERR_106_SUBMSG_5       MIL_TEXT("Unable to find a system font that supports all character codes of the text. Please install a suitable font.")
#define M_ERR_106_SUBMSG_6       MIL_TEXT("Your locale environment is not in UTF8.")
#define M_ERR_106_SUBMSG_7       MIL_TEXT("Invalid font size")
#define M_ERR_106_SUBMSG_8       MIL_TEXT("Invalid font file.")
#define M_ERR_106_SUBMSG_9       MIL_TEXT("Invalid text encoding.")

#define M_FORMAT_ERROR           107L
#define M_ERR_107_MSG            MIL_TEXT("Format error.")
#define M_ERR_107_SUBMSG_1       MIL_TEXT("The specified YUV format is only supported for all bands and with a compatible YUV buffer.")
#define M_ERR_107_SUBMSG_2       MIL_TEXT("The specified format is only supported for all bands.")
#define M_ERR_107_SUBMSG_3       NO_SUBMSG
#define M_ERR_107_SUBMSG_4       NO_SUBMSG
#define M_ERR_107_SUBMSG_5       NO_SUBMSG
#define M_ERR_107_SUBMSG_6       NO_SUBMSG
#define M_ERR_107_SUBMSG_7       NO_SUBMSG
#define M_ERR_107_SUBMSG_8       NO_SUBMSG
#define M_ERR_107_SUBMSG_9       NO_SUBMSG

#define M_APP_CTRL_INQ_ERROR     108L
#define M_ERR_108_MSG            MIL_TEXT("Application Control/Inquire error.")
#define M_ERR_108_SUBMSG_1       MIL_TEXT("Some display related object(s) were not freed.")
#define M_ERR_108_SUBMSG_2       NO_SUBMSG
#define M_ERR_108_SUBMSG_3       NO_SUBMSG
#define M_ERR_108_SUBMSG_4       NO_SUBMSG
#define M_ERR_108_SUBMSG_5       NO_SUBMSG
#define M_ERR_108_SUBMSG_6       NO_SUBMSG
#define M_ERR_108_SUBMSG_7       NO_SUBMSG
#define M_ERR_108_SUBMSG_8       NO_SUBMSG
#define M_ERR_108_SUBMSG_9       NO_SUBMSG

#define M_GRA_OPERATION_ERROR    109L
#define M_ERR_109_MSG            MIL_TEXT("Drawing operation error.")
#define M_ERR_109_SUBMSG_1       MIL_TEXT("Cannot draw in world units in an uncalibrated image.")
#define M_ERR_109_SUBMSG_2       NO_SUBMSG
#define M_ERR_109_SUBMSG_3       NO_SUBMSG
#define M_ERR_109_SUBMSG_4       NO_SUBMSG
#define M_ERR_109_SUBMSG_5       NO_SUBMSG
#define M_ERR_109_SUBMSG_6       NO_SUBMSG
#define M_ERR_109_SUBMSG_7       NO_SUBMSG
#define M_ERR_109_SUBMSG_8       NO_SUBMSG
#define M_ERR_109_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_18 110L
#define M_ERR_110_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_110_SUBMSG_1       MIL_TEXT("Invalid inquire type for this graphic.")
#define M_ERR_110_SUBMSG_2       MIL_TEXT("Invalid LabelOrIndex.")
#define M_ERR_110_SUBMSG_3       MIL_TEXT("Invalid list type.")
#define M_ERR_110_SUBMSG_4       MIL_TEXT("This value cannot be modified.")
#define M_ERR_110_SUBMSG_5       MIL_TEXT("This value cannot be read.")
#define M_ERR_110_SUBMSG_6       MIL_TEXT("Invalid units.")
#define M_ERR_110_SUBMSG_7       MIL_TEXT("Invalid SubIndex.")
#define M_ERR_110_SUBMSG_8       MIL_TEXT("Invalid Number.")
#define M_ERR_110_SUBMSG_9       MIL_TEXT("XEndArray and YEndArray should be M_NULL for M_POLYLINE or M_POLYGON.")

#define M_MEM_MAN_INQ_ERROR      111L
#define M_ERR_111_MSG            MIL_TEXT("Memory manager Inquire error.")
#define M_ERR_111_SUBMSG_1       MIL_TEXT("MIL is not using Mtx Memory Manager driver.")
#define M_ERR_111_SUBMSG_2       MIL_TEXT("Cannot get memory manager handle.")
#define M_ERR_111_SUBMSG_3       MIL_TEXT("Cannot get memory manager driver information.")
#define M_ERR_111_SUBMSG_4       NO_SUBMSG
#define M_ERR_111_SUBMSG_5       NO_SUBMSG
#define M_ERR_111_SUBMSG_6       NO_SUBMSG
#define M_ERR_111_SUBMSG_7       NO_SUBMSG
#define M_ERR_111_SUBMSG_8       NO_SUBMSG
#define M_ERR_111_SUBMSG_9       NO_SUBMSG

#define M_NO_MEM_ERROR           112L
#define M_ERR_112_MSG            MIL_TEXT("Memory error.")
#define M_ERR_112_SUBMSG_1       MIL_TEXT("Not enough heap memory to process.")
#define M_ERR_112_SUBMSG_2       NO_SUBMSG
#define M_ERR_112_SUBMSG_3       NO_SUBMSG
#define M_ERR_112_SUBMSG_4       NO_SUBMSG
#define M_ERR_112_SUBMSG_5       NO_SUBMSG
#define M_ERR_112_SUBMSG_6       NO_SUBMSG
#define M_ERR_112_SUBMSG_7       NO_SUBMSG
#define M_ERR_112_SUBMSG_8       NO_SUBMSG
#define M_ERR_112_SUBMSG_9       NO_SUBMSG

#define M_GPU_ERROR              113L
#define M_ERR_113_MSG            MIL_TEXT("GPU driver error.")
#define M_ERR_113_SUBMSG_1       MIL_TEXT("DirectX version not supported.")
#define M_ERR_113_SUBMSG_2       MIL_TEXT("Invalid command decoder.")
#define M_ERR_113_SUBMSG_3       MIL_TEXT("MilGPUd3d9.dll DLL cannot be loaded.")
#define M_ERR_113_SUBMSG_4       MIL_TEXT("MilGPUd3d10.dll DLL cannot be loaded.")
#define M_ERR_113_SUBMSG_5       NO_SUBMSG
#define M_ERR_113_SUBMSG_6       NO_SUBMSG
#define M_ERR_113_SUBMSG_7       NO_SUBMSG
#define M_ERR_113_SUBMSG_8       NO_SUBMSG
#define M_ERR_113_SUBMSG_9       NO_SUBMSG

#define M_FILE_OPERATION_ERROR   114L
#define M_ERR_114_MSG            MIL_TEXT("File operation error.")
#define M_ERR_114_SUBMSG_1       MIL_TEXT("Source file must be specified")
#define M_ERR_114_SUBMSG_2       MIL_TEXT("Folder already exists")
#define M_ERR_114_SUBMSG_3       MIL_TEXT("File does not exist")
#define M_ERR_114_SUBMSG_4       MIL_TEXT("Could not create folder")
#define M_ERR_114_SUBMSG_5       MIL_TEXT("Could not delete folder")
#define M_ERR_114_SUBMSG_6       MIL_TEXT("Folder is not empty")
#define M_ERR_114_SUBMSG_7       MIL_TEXT("Error executing command")
#define M_ERR_114_SUBMSG_8       MIL_TEXT("File not found")
#define M_ERR_114_SUBMSG_9       MIL_TEXT("Permission denied")

#define M_FILE_OPERATION_ERROR_2 115L
#define M_ERR_115_MSG            MIL_TEXT("File operation error.")
#define M_ERR_115_SUBMSG_1       MIL_TEXT("Could not copy file.")
#define M_ERR_115_SUBMSG_2       MIL_TEXT("The command is not a valid executable.")
#define M_ERR_115_SUBMSG_3       MIL_TEXT("The executable must be specified.")
#define M_ERR_115_SUBMSG_4       MIL_TEXT("Destination file must be specified.")
#define M_ERR_115_SUBMSG_5       MIL_TEXT("Source and Destination files must be different.")
#define M_ERR_115_SUBMSG_6       MIL_TEXT("Sharing violation.")
#define M_ERR_115_SUBMSG_7       MIL_TEXT("Name is invalid.")
#define M_ERR_115_SUBMSG_8       MIL_TEXT("No file specified.")
#define M_ERR_115_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_19 116L
#define M_ERR_116_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_116_SUBMSG_1       MIL_TEXT("The ID of the source buffer can only be M_NULL when preprocessing the context.")
#define M_ERR_116_SUBMSG_2       MIL_TEXT("The ID of the destination buffer can only be M_NULL when preprocessing the context.")
#define M_ERR_116_SUBMSG_3       MIL_TEXT("Inquire type not supported.")
#define M_ERR_116_SUBMSG_4       MIL_TEXT("Control type not supported.")
#define M_ERR_116_SUBMSG_5       MIL_TEXT("Invalid control value.")
#define M_ERR_116_SUBMSG_6       MIL_TEXT("Invalid mode.")
#define M_ERR_116_SUBMSG_7       MIL_TEXT("DeadPixels buffer must be specified.")
#define M_ERR_116_SUBMSG_8       MIL_TEXT("DeadPixels array contain invalid coordinates.")
#define M_ERR_116_SUBMSG_9       MIL_TEXT("Matrix array must be 1 band.")

#define M_INVALID_PARAM_ERROR_20 117L
#define M_ERR_117_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_117_SUBMSG_1       MIL_TEXT("All arrays must have the same number of elements.")
#define M_ERR_117_SUBMSG_2       MIL_TEXT("Buffer must be 1 band.")
#define M_ERR_117_SUBMSG_3       MIL_TEXT("Buffer SizeY must be 1.")
#define M_ERR_117_SUBMSG_4       MIL_TEXT("Buffer SizeX must be multiple of 2.")
#define M_ERR_117_SUBMSG_5       MIL_TEXT("Src image size must be greater or equal to DeadPixels size.")
#define M_ERR_117_SUBMSG_6       MIL_TEXT("Dst image size must be greater or equal to DeadPixels size.")
#define M_ERR_117_SUBMSG_7       MIL_TEXT("DeadPixels could not be filled with all non-zero values.")
#define M_ERR_117_SUBMSG_8       MIL_TEXT("Invalid statistic type.")
#define M_ERR_117_SUBMSG_9       MIL_TEXT("SizeX and SizeY must be specified in the context or a source buffer must be passed at the preprocess.")

#define M_NULL_PARAMETER          118L
#define M_ERR_118_MSG             MIL_TEXT("Parameter cannot be NULL.")
#define M_ERR_118_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_118_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_118_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_118_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_118_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_118_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_118_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_118_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_118_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_INVALID_PARAM_ERROR_21 119L
#define M_ERR_119_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_119_SUBMSG_1       MIL_TEXT("The affinity mask array pointer cannot be NULL.")
#define M_ERR_119_SUBMSG_2       MIL_TEXT("The affinity mask array must contain at least one valid bit.")
#define M_ERR_119_SUBMSG_3       MIL_TEXT("The value pointer is not used and should be NULL.")
#define M_ERR_119_SUBMSG_4       MIL_TEXT("Context and result must be on the same system.")
#define M_ERR_119_SUBMSG_5       MIL_TEXT("Model must be specified.")
#define M_ERR_119_SUBMSG_6       MIL_TEXT("Mask must be specified.")
#define M_ERR_119_SUBMSG_7       MIL_TEXT("Invalid score type.")
#define M_ERR_119_SUBMSG_8       MIL_TEXT("Model step must be 1 or 2.")
#define M_ERR_119_SUBMSG_9       MIL_TEXT("Invalid max score.")

#define M_INVALID_PARAM_ERROR_22 120L
#define M_ERR_120_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_120_SUBMSG_1       MIL_TEXT("Invalid source buffer type.")
#define M_ERR_120_SUBMSG_2       MIL_TEXT("Invalid destination buffer type.")
#define M_ERR_120_SUBMSG_3       MIL_TEXT("Model must be a monochrome image.")
#define M_ERR_120_SUBMSG_4       MIL_TEXT("Invalid model buffer type.")
#define M_ERR_120_SUBMSG_5       MIL_TEXT("Invalid model size.")
#define M_ERR_120_SUBMSG_6       MIL_TEXT("Mask must be a monochrome image.")
#define M_ERR_120_SUBMSG_7       MIL_TEXT("Invalid mask buffer type.")
#define M_ERR_120_SUBMSG_8       MIL_TEXT("Invalid mask size.")
#define M_ERR_120_SUBMSG_9       MIL_TEXT("Invalid center structural element value.")

#define M_THRESHOLDS_ERROR       121L
#define M_ERR_121_MSG            MIL_TEXT("External thresholds error.")
#define M_ERR_121_SUBMSG_1       MIL_TEXT("Invalid file name.")
#define M_ERR_121_SUBMSG_2       MIL_TEXT("Cannot open file.")
#define M_ERR_121_SUBMSG_3       MIL_TEXT("Bad file format.")
#define M_ERR_121_SUBMSG_4       MIL_TEXT("Invalid threshold identifier.")
#define M_ERR_121_SUBMSG_5       MIL_TEXT("Invalid parameter value.")
#define M_ERR_121_SUBMSG_6       NO_SUBMSG
#define M_ERR_121_SUBMSG_7       NO_SUBMSG
#define M_ERR_121_SUBMSG_8       NO_SUBMSG
#define M_ERR_121_SUBMSG_9       NO_SUBMSG

#define M_SYS_CONFIG_ERROR       122L
#define M_ERR_122_MSG            MIL_TEXT("Config access error.")
#define M_ERR_122_SUBMSG_1       MIL_TEXT("Could not write to eeprom.")
#define M_ERR_122_SUBMSG_2       MIL_TEXT("Could not read from eeprom.")
#define M_ERR_122_SUBMSG_3       NO_SUBMSG
#define M_ERR_122_SUBMSG_4       NO_SUBMSG
#define M_ERR_122_SUBMSG_5       NO_SUBMSG
#define M_ERR_122_SUBMSG_6       NO_SUBMSG
#define M_ERR_122_SUBMSG_7       NO_SUBMSG
#define M_ERR_122_SUBMSG_8       NO_SUBMSG
#define M_ERR_122_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_23 123L
#define M_ERR_123_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_123_SUBMSG_1       MIL_TEXT("Invalid number of elements. The number of elements should greater or equal to zero.")
#define M_ERR_123_SUBMSG_2       MIL_TEXT("Parameter 2 must be set to M_NULL when the operation is M_DELETE.")
#define M_ERR_123_SUBMSG_3       MIL_TEXT("Parameter 2 cannot be M_NULL for this operation as the image buffer does not have any region information.")
#define M_ERR_123_SUBMSG_4       NO_SUBMSG
#define M_ERR_123_SUBMSG_5       NO_SUBMSG
#define M_ERR_123_SUBMSG_6       NO_SUBMSG
#define M_ERR_123_SUBMSG_7       NO_SUBMSG
#define M_ERR_123_SUBMSG_8       NO_SUBMSG
#define M_ERR_123_SUBMSG_9       NO_SUBMSG

#define M_SET_REGION_ERROR       124L
#define M_ERR_124_MSG            MIL_TEXT("Region error.")
#define M_ERR_124_SUBMSG_1       MIL_TEXT("Cannot rasterize a graphic list with world input units in an uncalibrated image.")
#define M_ERR_124_SUBMSG_2       MIL_TEXT("Unsupported operation value when using a graphic list as the region source.")
#define M_ERR_124_SUBMSG_3       MIL_TEXT("Unsupported operation value when using an image buffer as the region source.")
#define M_ERR_124_SUBMSG_4       MIL_TEXT("Unsupported buffer format used as the region source.")
#define M_ERR_124_SUBMSG_5       MIL_TEXT("The region buffer must have the same sizes as its owner buffer.")
#define M_ERR_124_SUBMSG_6       MIL_TEXT("Cannot set a region on a buffer that has one or more child.")
#define M_ERR_124_SUBMSG_7       NO_SUBMSG
#define M_ERR_124_SUBMSG_8       NO_SUBMSG
#define M_ERR_124_SUBMSG_9       NO_SUBMSG

#define M_OPERATION_ERROR_7      125L
#define M_ERR_125_MSG            MIL_TEXT("Operation error.")
#define M_ERR_125_SUBMSG_1       MIL_TEXT("Error while converting this graphic.")
#define M_ERR_125_SUBMSG_2       NO_SUBMSG
#define M_ERR_125_SUBMSG_3       NO_SUBMSG
#define M_ERR_125_SUBMSG_4       NO_SUBMSG
#define M_ERR_125_SUBMSG_5       NO_SUBMSG
#define M_ERR_125_SUBMSG_6       NO_SUBMSG
#define M_ERR_125_SUBMSG_7       NO_SUBMSG
#define M_ERR_125_SUBMSG_8       NO_SUBMSG
#define M_ERR_125_SUBMSG_9       NO_SUBMSG

#define M_DMIL_MONITOR_ERROR     126L
#define M_ERR_126_MSG            MIL_TEXT("DMILMonitor error")
#define M_ERR_126_SUBMSG_1       MIL_TEXT("Cannot load DMILMonitor DLL.")
#define M_ERR_126_SUBMSG_2       MIL_TEXT("A non-null cluster node must be specified during MappAlloc to activate the monitoring mode.")
#define M_ERR_126_SUBMSG_3       MIL_TEXT("The port must be set before enabling the connection")
#define M_ERR_126_SUBMSG_4       NO_SUBMSG
#define M_ERR_126_SUBMSG_5       NO_SUBMSG
#define M_ERR_126_SUBMSG_6       NO_SUBMSG
#define M_ERR_126_SUBMSG_7       NO_SUBMSG
#define M_ERR_126_SUBMSG_8       NO_SUBMSG
#define M_ERR_126_SUBMSG_9       NO_SUBMSG

#define M_MP_ERROR               127L
#define M_ERR_127_MSG            MIL_TEXT("MP subsystem error.")
#define M_ERR_127_SUBMSG_1       MIL_TEXT("Unrecognized host hardware configuration.  MP will be disabled.")
#define M_ERR_127_SUBMSG_2       NO_SUBMSG
#define M_ERR_127_SUBMSG_3       NO_SUBMSG
#define M_ERR_127_SUBMSG_4       NO_SUBMSG
#define M_ERR_127_SUBMSG_5       NO_SUBMSG
#define M_ERR_127_SUBMSG_6       NO_SUBMSG
#define M_ERR_127_SUBMSG_7       NO_SUBMSG
#define M_ERR_127_SUBMSG_8       NO_SUBMSG
#define M_ERR_127_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_24 128L
#define M_ERR_128_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_128_SUBMSG_1       MIL_TEXT("This GetType is not supported for this object type.")
#define M_ERR_128_SUBMSG_2       MIL_TEXT("This PutType is not supported for this object type.")
#define M_ERR_128_SUBMSG_3       MIL_TEXT("Cannot use both +M_AVAILABLE and +M_SUPPORTED at the same time.")
#define M_ERR_128_SUBMSG_4       MIL_TEXT("Cannot use both +M_AVAILABLE and +M_DEFAULT at the same time.")
#define M_ERR_128_SUBMSG_5       MIL_TEXT("Only one +M_TYPE_[] flag can be used at a time.")
#define M_ERR_128_SUBMSG_6       MIL_TEXT("+M_SUPPORTED, +M_AVAILABLE or +M_DEFAULT cannot be used with this operation.")
#define M_ERR_128_SUBMSG_7       MIL_TEXT("+M_TYPE_[] flags cannot be used with this operation.")
#define M_ERR_128_SUBMSG_8       MIL_TEXT("Empty arrays are not supported by this PutType.")
#define M_ERR_128_SUBMSG_9       MIL_TEXT("The MIL_ID given as control value cannot be M_NULL.")

#define M_OPERATION_ERROR_8      129L
#define M_ERR_129_MSG            MIL_TEXT("Operation error.")
#define M_ERR_129_SUBMSG_1       MIL_TEXT("The InquireType is not supported at this time.")
#define M_ERR_129_SUBMSG_2       MIL_TEXT("The ResultType is not available at this time.")
#define M_ERR_129_SUBMSG_3       MIL_TEXT("The PutType is not supported at this time.")
#define M_ERR_129_SUBMSG_4       MIL_TEXT("The GetType is not supported at this time.")
#define M_ERR_129_SUBMSG_5       NO_SUBMSG
#define M_ERR_129_SUBMSG_6       NO_SUBMSG
#define M_ERR_129_SUBMSG_7       MIL_TEXT("A streaming operation failed.")
#define M_ERR_129_SUBMSG_8       MIL_TEXT("No default value is available.")
#define M_ERR_129_SUBMSG_9       MIL_TEXT("When inquiring an array, the output pointer must not be M_NULL.")

#define M_OPERATION_ERROR_9      130L
#define M_ERR_130_MSG            MIL_TEXT("Operation error.")
#define M_ERR_130_SUBMSG_1       MIL_TEXT("The value of M_MAX_DISTANCE must be greater or equal to the value of M_MIN_DISTANCE.")
#define M_ERR_130_SUBMSG_2       NO_SUBMSG
#define M_ERR_130_SUBMSG_3       NO_SUBMSG
#define M_ERR_130_SUBMSG_4       NO_SUBMSG
#define M_ERR_130_SUBMSG_5       NO_SUBMSG
#define M_ERR_130_SUBMSG_6       NO_SUBMSG
#define M_ERR_130_SUBMSG_7       NO_SUBMSG
#define M_ERR_130_SUBMSG_8       NO_SUBMSG
#define M_ERR_130_SUBMSG_9       NO_SUBMSG

#define M_INVALID_PARAM_ERROR_25 131L
#define M_ERR_131_MSG            MIL_TEXT("Invalid parameter.")
#define M_ERR_131_SUBMSG_1       MIL_TEXT("Only M_DRAW_LIST objects are accepted.")
#define M_ERR_131_SUBMSG_2       MIL_TEXT("Only lists containing 1 polyline are accepted.")
#define M_ERR_131_SUBMSG_3       MIL_TEXT("The MIL_ID given as control value must be an M_IMAGE.")
#define M_ERR_131_SUBMSG_4       MIL_TEXT("The image buffer given as control value must have the M_PROC attribute.")
#define M_ERR_131_SUBMSG_5       MIL_TEXT("The image buffer given as control value must be 8-bit or 16-bit unsigned.")
#define M_ERR_131_SUBMSG_6       NO_SUBMSG
#define M_ERR_131_SUBMSG_7       NO_SUBMSG
#define M_ERR_131_SUBMSG_8       NO_SUBMSG
#define M_ERR_131_SUBMSG_9       NO_SUBMSG

#define M_CONNECTION_ERROR       132L
#define M_ERR_132_MSG            MIL_TEXT("Connection error.")
#define M_ERR_132_SUBMSG_1       MIL_TEXT("Cannot open connection.")
#define M_ERR_132_SUBMSG_2       MIL_TEXT("Connection is already established.")
#define M_ERR_132_SUBMSG_3       MIL_TEXT("Invalid parameter 1. This function requires a remote Application.")
#define M_ERR_132_SUBMSG_4       NO_SUBMSG
#define M_ERR_132_SUBMSG_5       NO_SUBMSG
#define M_ERR_132_SUBMSG_6       NO_SUBMSG
#define M_ERR_132_SUBMSG_7       NO_SUBMSG
#define M_ERR_132_SUBMSG_8       NO_SUBMSG
#define M_ERR_132_SUBMSG_9       NO_SUBMSG

#define M_PUBLICATION_ERROR      133L
#define M_ERR_133_MSG            MIL_TEXT("Publication error")
#define M_ERR_133_SUBMSG_1       MIL_TEXT("Displays cannot be published.")
#define M_ERR_133_SUBMSG_2       NO_SUBMSG
#define M_ERR_133_SUBMSG_3       NO_SUBMSG
#define M_ERR_133_SUBMSG_4       NO_SUBMSG
#define M_ERR_133_SUBMSG_5       NO_SUBMSG
#define M_ERR_133_SUBMSG_6       NO_SUBMSG
#define M_ERR_133_SUBMSG_7       NO_SUBMSG
#define M_ERR_133_SUBMSG_8       NO_SUBMSG
#define M_ERR_133_SUBMSG_9       NO_SUBMSG

#define M_APP_FREE_ERROR_2       134L
#define M_ERR_134_MSG            MIL_TEXT("Application free operation error.")
#define M_ERR_134_SUBMSG_1       MIL_TEXT("Some remote connections have not been closed.")
#define M_ERR_134_SUBMSG_2       NO_SUBMSG
#define M_ERR_134_SUBMSG_3       NO_SUBMSG
#define M_ERR_134_SUBMSG_4       NO_SUBMSG
#define M_ERR_134_SUBMSG_5       NO_SUBMSG
#define M_ERR_134_SUBMSG_6       NO_SUBMSG
#define M_ERR_134_SUBMSG_7       NO_SUBMSG
#define M_ERR_134_SUBMSG_8       NO_SUBMSG
#define M_ERR_134_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_135       135L
#define M_ERR_135_MSG            NO_SUBMSG
#define M_ERR_135_SUBMSG_1       NO_SUBMSG
#define M_ERR_135_SUBMSG_2       NO_SUBMSG
#define M_ERR_135_SUBMSG_3       NO_SUBMSG
#define M_ERR_135_SUBMSG_4       NO_SUBMSG
#define M_ERR_135_SUBMSG_5       NO_SUBMSG
#define M_ERR_135_SUBMSG_6       NO_SUBMSG
#define M_ERR_135_SUBMSG_7       NO_SUBMSG
#define M_ERR_135_SUBMSG_8       NO_SUBMSG
#define M_ERR_135_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_136       136L
#define M_ERR_136_MSG            NO_SUBMSG
#define M_ERR_136_SUBMSG_1       NO_SUBMSG
#define M_ERR_136_SUBMSG_2       NO_SUBMSG
#define M_ERR_136_SUBMSG_3       NO_SUBMSG
#define M_ERR_136_SUBMSG_4       NO_SUBMSG
#define M_ERR_136_SUBMSG_5       NO_SUBMSG
#define M_ERR_136_SUBMSG_6       NO_SUBMSG
#define M_ERR_136_SUBMSG_7       NO_SUBMSG
#define M_ERR_136_SUBMSG_8       NO_SUBMSG
#define M_ERR_136_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_137       137L
#define M_ERR_137_MSG            NO_SUBMSG
#define M_ERR_137_SUBMSG_1       NO_SUBMSG
#define M_ERR_137_SUBMSG_2       NO_SUBMSG
#define M_ERR_137_SUBMSG_3       NO_SUBMSG
#define M_ERR_137_SUBMSG_4       NO_SUBMSG
#define M_ERR_137_SUBMSG_5       NO_SUBMSG
#define M_ERR_137_SUBMSG_6       NO_SUBMSG
#define M_ERR_137_SUBMSG_7       NO_SUBMSG
#define M_ERR_137_SUBMSG_8       NO_SUBMSG
#define M_ERR_137_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_138       138L
#define M_ERR_138_MSG            NO_SUBMSG
#define M_ERR_138_SUBMSG_1       NO_SUBMSG
#define M_ERR_138_SUBMSG_2       NO_SUBMSG
#define M_ERR_138_SUBMSG_3       NO_SUBMSG
#define M_ERR_138_SUBMSG_4       NO_SUBMSG
#define M_ERR_138_SUBMSG_5       NO_SUBMSG
#define M_ERR_138_SUBMSG_6       NO_SUBMSG
#define M_ERR_138_SUBMSG_7       NO_SUBMSG
#define M_ERR_138_SUBMSG_8       NO_SUBMSG
#define M_ERR_138_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_139       139L
#define M_ERR_139_MSG            NO_SUBMSG
#define M_ERR_139_SUBMSG_1       NO_SUBMSG
#define M_ERR_139_SUBMSG_2       NO_SUBMSG
#define M_ERR_139_SUBMSG_3       NO_SUBMSG
#define M_ERR_139_SUBMSG_4       NO_SUBMSG
#define M_ERR_139_SUBMSG_5       NO_SUBMSG
#define M_ERR_139_SUBMSG_6       NO_SUBMSG
#define M_ERR_139_SUBMSG_7       NO_SUBMSG
#define M_ERR_139_SUBMSG_8       NO_SUBMSG
#define M_ERR_139_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_140       140L
#define M_ERR_140_MSG            NO_SUBMSG
#define M_ERR_140_SUBMSG_1       NO_SUBMSG
#define M_ERR_140_SUBMSG_2       NO_SUBMSG
#define M_ERR_140_SUBMSG_3       NO_SUBMSG
#define M_ERR_140_SUBMSG_4       NO_SUBMSG
#define M_ERR_140_SUBMSG_5       NO_SUBMSG
#define M_ERR_140_SUBMSG_6       NO_SUBMSG
#define M_ERR_140_SUBMSG_7       NO_SUBMSG
#define M_ERR_140_SUBMSG_8       NO_SUBMSG
#define M_ERR_140_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_141       141L
#define M_ERR_141_MSG            NO_SUBMSG
#define M_ERR_141_SUBMSG_1       NO_SUBMSG
#define M_ERR_141_SUBMSG_2       NO_SUBMSG
#define M_ERR_141_SUBMSG_3       NO_SUBMSG
#define M_ERR_141_SUBMSG_4       NO_SUBMSG
#define M_ERR_141_SUBMSG_5       NO_SUBMSG
#define M_ERR_141_SUBMSG_6       NO_SUBMSG
#define M_ERR_141_SUBMSG_7       NO_SUBMSG
#define M_ERR_141_SUBMSG_8       NO_SUBMSG
#define M_ERR_141_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_142       142L
#define M_ERR_142_MSG            NO_SUBMSG
#define M_ERR_142_SUBMSG_1       NO_SUBMSG
#define M_ERR_142_SUBMSG_2       NO_SUBMSG
#define M_ERR_142_SUBMSG_3       NO_SUBMSG
#define M_ERR_142_SUBMSG_4       NO_SUBMSG
#define M_ERR_142_SUBMSG_5       NO_SUBMSG
#define M_ERR_142_SUBMSG_6       NO_SUBMSG
#define M_ERR_142_SUBMSG_7       NO_SUBMSG
#define M_ERR_142_SUBMSG_8       NO_SUBMSG
#define M_ERR_142_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_143       143L
#define M_ERR_143_MSG            NO_SUBMSG
#define M_ERR_143_SUBMSG_1       NO_SUBMSG
#define M_ERR_143_SUBMSG_2       NO_SUBMSG
#define M_ERR_143_SUBMSG_3       NO_SUBMSG
#define M_ERR_143_SUBMSG_4       NO_SUBMSG
#define M_ERR_143_SUBMSG_5       NO_SUBMSG
#define M_ERR_143_SUBMSG_6       NO_SUBMSG
#define M_ERR_143_SUBMSG_7       NO_SUBMSG
#define M_ERR_143_SUBMSG_8       NO_SUBMSG
#define M_ERR_143_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_144       144L
#define M_ERR_144_MSG            NO_SUBMSG
#define M_ERR_144_SUBMSG_1       NO_SUBMSG
#define M_ERR_144_SUBMSG_2       NO_SUBMSG
#define M_ERR_144_SUBMSG_3       NO_SUBMSG
#define M_ERR_144_SUBMSG_4       NO_SUBMSG
#define M_ERR_144_SUBMSG_5       NO_SUBMSG
#define M_ERR_144_SUBMSG_6       NO_SUBMSG
#define M_ERR_144_SUBMSG_7       NO_SUBMSG
#define M_ERR_144_SUBMSG_8       NO_SUBMSG
#define M_ERR_144_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_145       145L
#define M_ERR_145_MSG            NO_SUBMSG
#define M_ERR_145_SUBMSG_1       NO_SUBMSG
#define M_ERR_145_SUBMSG_2       NO_SUBMSG
#define M_ERR_145_SUBMSG_3       NO_SUBMSG
#define M_ERR_145_SUBMSG_4       NO_SUBMSG
#define M_ERR_145_SUBMSG_5       NO_SUBMSG
#define M_ERR_145_SUBMSG_6       NO_SUBMSG
#define M_ERR_145_SUBMSG_7       NO_SUBMSG
#define M_ERR_145_SUBMSG_8       NO_SUBMSG
#define M_ERR_145_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_146       146L
#define M_ERR_146_MSG            NO_SUBMSG
#define M_ERR_146_SUBMSG_1       NO_SUBMSG
#define M_ERR_146_SUBMSG_2       NO_SUBMSG
#define M_ERR_146_SUBMSG_3       NO_SUBMSG
#define M_ERR_146_SUBMSG_4       NO_SUBMSG
#define M_ERR_146_SUBMSG_5       NO_SUBMSG
#define M_ERR_146_SUBMSG_6       NO_SUBMSG
#define M_ERR_146_SUBMSG_7       NO_SUBMSG
#define M_ERR_146_SUBMSG_8       NO_SUBMSG
#define M_ERR_146_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_147       147L
#define M_ERR_147_MSG            NO_SUBMSG
#define M_ERR_147_SUBMSG_1       NO_SUBMSG
#define M_ERR_147_SUBMSG_2       NO_SUBMSG
#define M_ERR_147_SUBMSG_3       NO_SUBMSG
#define M_ERR_147_SUBMSG_4       NO_SUBMSG
#define M_ERR_147_SUBMSG_5       NO_SUBMSG
#define M_ERR_147_SUBMSG_6       NO_SUBMSG
#define M_ERR_147_SUBMSG_7       NO_SUBMSG
#define M_ERR_147_SUBMSG_8       NO_SUBMSG
#define M_ERR_147_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_148       148L
#define M_ERR_148_MSG            NO_SUBMSG
#define M_ERR_148_SUBMSG_1       NO_SUBMSG
#define M_ERR_148_SUBMSG_2       NO_SUBMSG
#define M_ERR_148_SUBMSG_3       NO_SUBMSG
#define M_ERR_148_SUBMSG_4       NO_SUBMSG
#define M_ERR_148_SUBMSG_5       NO_SUBMSG
#define M_ERR_148_SUBMSG_6       NO_SUBMSG
#define M_ERR_148_SUBMSG_7       NO_SUBMSG
#define M_ERR_148_SUBMSG_8       NO_SUBMSG
#define M_ERR_148_SUBMSG_9       NO_SUBMSG

#define M_UNUSED_ERROR_149       149L
#define M_ERR_149_MSG            NO_SUBMSG
#define M_ERR_149_SUBMSG_1       NO_SUBMSG
#define M_ERR_149_SUBMSG_2       NO_SUBMSG
#define M_ERR_149_SUBMSG_3       NO_SUBMSG
#define M_ERR_149_SUBMSG_4       NO_SUBMSG
#define M_ERR_149_SUBMSG_5       NO_SUBMSG
#define M_ERR_149_SUBMSG_6       NO_SUBMSG
#define M_ERR_149_SUBMSG_7       NO_SUBMSG
#define M_ERR_149_SUBMSG_8       NO_SUBMSG
#define M_ERR_149_SUBMSG_9       NO_SUBMSG

// TO DO when adding a new error message
// Update M_NBERRMSGMAX in mil.h when adding a new error message
// Update Oserr.src as well

#endif
