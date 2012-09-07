/************************************************************************/
/*
*
* Filename     :  milfpga.h
* Revision     :  9.02.0812
* Content      :  This file contains the defines necessary to use the
*                 Matrox Imaging Library FPGA DTK "C" user interface.
*
* Comments     :  Some defines may be here but not yet
*                 implemented in the library.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2011.
* All Rights Reserved
*************************************************************************/

#ifndef __MILFPGA_H__
#define __MILFPGA_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if (BW_COMPATIBILITY == 0x080)
#define MILFPGA_EXPORT __declspec(dllexport)
#define MILFPGA_EXPORT_TYPE 
#else
#define MILFPGA_EXPORT      MFTYPE32
#define MILFPGA_EXPORT_TYPE MFTYPE 
#endif

/************************************************************************/
/* MIL FPGA context identifier type                                     */
/************************************************************************/
typedef void* MIL_FPGA_CONTEXT;
typedef MFTYPE32 MIL_INT (MILFPGA_EXPORT_TYPE MPTYPE *MIL_FPGA_HOOK_FUNCTION_PTR)(  MIL_INT HookType,
                                                                                    MIL_ID EventId,
                                                                                    void MPTYPE* UserDataPtr);

typedef MFTYPE32 MIL_INT (MILFPGA_EXPORT_TYPE  MPTYPE *MFPGAINQUIRE)(               MIL_ID SystemId,
                                                                                    MIL_INT FpgaDeviceNum,
                                                                                    MIL_INT   InquireType,
                                                                                    void MPTYPE *ResultPtr);
/************************************************************************/
/* MIL FPGA API declaration                                             */
/************************************************************************/
MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaCommandAlloc(  MIL_ID SystemId,
                                                MIL_INT DeviceNum,
                                                MIL_INT FunctionId,
                                                MIL_INT SubFunctionId,
                                                MIL_INT FunctionNum,
                                                MIL_INT FunctionType,
                                                MIL_INT Flag,
                                                MIL_FPGA_CONTEXT* FpgaContextPtr);

MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaCommandFree(   MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT Flag);

#if M_MIL_USE_UNICODE
MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaLoadA(         MIL_ID SystemId,
                                                MIL_INT FpgaDeviceNum,
                                                MIL_API_CONST char* FirmwareFile,
                                                MIL_INT Flag);
MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaLoadW(         MIL_ID SystemId,
                                                MIL_INT FpgaDeviceNum,
                                                MIL_API_CONST_TEXT_PTR FirmwareFile,
                                                MIL_INT Flag);
#if M_MIL_UNICODE_API
#define MfpgaLoad MfpgaLoadW
#else
#define MfpgaLoad MfpgaLoadA
#endif
#else
MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaLoad(          MIL_ID SystemId,
                                                MIL_INT FpgaDeviceNum,
                                                MIL_API_CONST_TEXT_PTR FirmwareFile,
                                                MIL_INT Flag);
#define MfpgaLoadW MfpgaLoad
#endif

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaSetSource(        MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_BUFFER_INFO Buf,
                                                MIL_INT StreamOffset,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaSetDestination(   MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_BUFFER_INFO Buf,
                                                MIL_INT StreamOffset,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaSetLink(          MIL_FPGA_CONTEXT SourceFpgaContext,
                                                MIL_INT SourceStreamPort,
                                                MIL_FPGA_CONTEXT DestinationFpgaContext,
                                                MIL_INT DestinationStreamPort,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaCommandQueue(     MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT CompletionMode,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaGetRegister(      MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT RegisterBank,
                                                MIL_INT Offset,
                                                MIL_INT Length,
                                                void *ValuePtr,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaSetRegister(      MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT RegisterBank,
                                                MIL_INT Offset,
                                                MIL_INT Length,
                                                void *ValuePtr,
                                                MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaGetAndSetRegister(   MIL_FPGA_CONTEXT FpgaCommandId,
                                                   MIL_INT SrcRegisterBank,
                                                   MIL_INT SrcOffset,
                                                   MIL_INT DstRegisterBank,
                                                   MIL_INT DstOffset,
                                                   MIL_INT BitMaskRegisterBank,
                                                   MIL_INT BitMaskOffset,
                                                   MIL_INT Length,
                                                   MIL_INT Flag);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaCommandControl(   MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT Flag,
                                                void *ValuePtr);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaCommandInquire(   MIL_FPGA_CONTEXT FpgaCommandId,
                                                MIL_INT Flag,
                                                void *ValuePtr);

MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaInquire(       MIL_ID MilSystemId,
                                                MIL_INT FpgaDeviceNumber,
                                                MIL_INT InquireType,
                                                void* ValuePtr);

MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaControl(       MIL_ID MilSystemId,
                                                MIL_INT FpgaDeviceNumber,
                                                MIL_INT ControlType,
                                                void* ValuePtr);

MILFPGA_EXPORT
void MILFPGA_EXPORT_TYPE MfpgaHookFunction(     MIL_ID SystemId,
                                                MIL_INT DeviceNum,
                                                MIL_INT FunctionId,
                                                MIL_INT SubFunctionId,
                                                MIL_INT FunctionNum,
                                                MIL_INT HookType,
                                                MIL_FPGA_HOOK_FUNCTION_PTR HookHandlerPtr,
                                                void *UserDataPtr);

MILFPGA_EXPORT
MIL_INT MILFPGA_EXPORT_TYPE MfpgaGetHookInfo(   MIL_ID EventId,
                                                MIL_INT InfoType,
                                                void *UserVarPtr);

/************************************************************************/
/* Transfer unit Function ID  and SubFunction ID definitions            */
/************************************************************************/
#define FPGA_HOST_2_AVALON_FID                        0xC001
#define FPGA_DMA_READ_2_STREAM_FID                    0xC010
#define FPGA_STREAM_2_DMA_WRITE_FID                   0xC011
#define FPGA_HSSI_2_AVALON_FID                        0xC012

/************************************************************************/
/* For Processing unit Function ID definitions                          */
/* see milfunctioncode.h                                                */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* MfpgaSetSource, MfpgaSetDestination and MfpgaSetLink                 */
/* stream offset defines                                                */
/*                                                                      */
/************************************************************************/
#define M_FPGA_STREAM_INPUT_BIT                 0x10000000
#define M_FPGA_STREAM_OUTPUT_BIT                0x20000000
#define M_FPGA_STREAM_IO_MASK                   (M_FPGA_STREAM_INPUT_BIT | M_FPGA_STREAM_OUTPUT_BIT)
#define M_FPGA_STREAM_IO_FILTER              (~ (M_FPGA_STREAM_INPUT_BIT | M_FPGA_STREAM_OUTPUT_BIT))

#define M_INPUT0                                (M_FPGA_STREAM_INPUT_BIT | 0x00000000)
#define M_INPUT1                                (M_FPGA_STREAM_INPUT_BIT | 0x00000001)
#define M_INPUT2                                (M_FPGA_STREAM_INPUT_BIT | 0x00000002)
#define M_INPUT3                                (M_FPGA_STREAM_INPUT_BIT | 0x00000003)
#define M_INPUT4                                (M_FPGA_STREAM_INPUT_BIT | 0x00000004)
#define M_INPUT5                                (M_FPGA_STREAM_INPUT_BIT | 0x00000005)
#define M_INPUT6                                (M_FPGA_STREAM_INPUT_BIT | 0x00000006)
#define M_INPUT7                                (M_FPGA_STREAM_INPUT_BIT | 0x00000007)
#define M_INPUT8                                (M_FPGA_STREAM_INPUT_BIT | 0x00000008)
#define M_INPUT9                                (M_FPGA_STREAM_INPUT_BIT | 0x00000009)

#define M_OUTPUT0                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000000)
#define M_OUTPUT1                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000001)
#define M_OUTPUT2                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000002)
#define M_OUTPUT3                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000003)
#define M_OUTPUT4                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000004)
#define M_OUTPUT5                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000005)
#define M_OUTPUT6                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000006)
#define M_OUTPUT7                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000007)
#define M_OUTPUT8                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000008)
#define M_OUTPUT9                               (M_FPGA_STREAM_OUTPUT_BIT | 0x00000009)

/************************************************************************/
/*                                                                      */
/* MfpgaSetSource, MfpgaSetDestination and MfpgaSetLink                 */
/* flag defines                                                         */
/*                                                                      */
/************************************************************************/
//#define M_DEFAULT                             0x10000000L
#define M_FPGA_FLAG_TYPE                        0xf0000000L
#define M_FPGA_FLAG_TU_FLAVOR_MASK              0x70000000L
#define M_FPGA_MULTI_CONTEXT                    0x30000000L
#define M_FPGA_MULTI_STREAM_PORT                0x40000000L
#define M_FPGA_DONT_INTERSECT                   0x80000000L

#define M_CONTEXT0                              (M_FPGA_MULTI_CONTEXT | 0)
#define M_CONTEXT1                              (M_FPGA_MULTI_CONTEXT | 1)
#define M_CONTEXT2                              (M_FPGA_MULTI_CONTEXT | 2)
#define M_CONTEXT3                              (M_FPGA_MULTI_CONTEXT | 3)

/************************************************************************/
/*                                                                      */
/* MfpgaCommandQueue completion mode defines                            */
/*                                                                      */
/************************************************************************/
//#define M_DEFAULT                             0x10000000L
#define M_PROCESSING_COMPLETED                  0x00000001L
#define M_DESTINATION_WRITTEN                   0x00000002L
#define M_SOURCE_READ                           0x00000003L

/************************************************************************/
/*                                                                      */
/* MfpgaCommandQueue flags                                              */
/*                                                                      */
/************************************************************************/
//#define M_DEFAULT                             0x10000000L
//#define M_WAIT                                1L
#define M_DISPATCH                              2L

/************************************************************************/
/*                                                                      */
/* MfpgaGetRegister/MfpgaSetRegister Register bank defines              */
/*                                                                      */
/************************************************************************/
#define M_USER                                  0x00000001L
#define M_STREAMER_BASE                         0x00000002L
#define M_PU_BASE                               0x00000003L
#define M_FPGA_BASE                             0x00000004L

/************************************************************************/
/*                                                                      */
/* MfpgaGetRegister/MfpgaSetRegister Flag defines                       */
/*                                                                      */
/************************************************************************/
#define M_WHEN_DISPATCHED                       1
#define M_WHEN_COMPLETED                        2

/************************************************************************/
/*                                                                      */
/* MfpgaGetError                                                        */
/*                                                                      */
/************************************************************************/
#define M_FPGA_ERROR_CODE     1
#define M_FPGA_ERROR_MESSAGE  2
#define M_FPGA_ERROR_SYSTEM   3
#define M_FPGA_ERROR_DELETE   0x80000000L

/************************************************************************/
/*                                                                      */
/* MfpgaInquire / MfpgaControl                                          */
/*                                                                      */
/************************************************************************/
#define M_NUMBER_OF_PU                       0x1000
#define M_NUMBER_OF_TU                       0x1001
#define M_PU_LIST                            0x1002
#define M_TU_LIST                            0x1003
#define M_FPGA_PACKAGE_NAME_LENGTH           0x1004
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API)
#define M_FPGA_PACKAGE_NAME                  (0x1005|M_CLIENT_ASCII_MODE)
#else
#define M_FPGA_PACKAGE_NAME                  0x1005
#endif
#define M_FPGA_CONFIGURATION_FILENAME_LENGTH 0x1006
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API)
#define M_FPGA_CONFIGURATION_FILENAME       (0x1007|M_CLIENT_ASCII_MODE)
#else
#define M_FPGA_CONFIGURATION_FILENAME        0x1007
#endif
#define M_FPGA_CONFIG                        0x1008
#define M_FPGA_BUILD_NUMBER                  0x1009
#define M_PU_SELECT                          0x1010

/************************************************************************/
/*                                                                      */
/* MfpgaCommandInquire                                                  */
/*                                                                      */
/************************************************************************/
#define M_MINOR_VERSION                      0x2000
#define M_MAJOR_VERSION                      0x2001
#define M_FUNCTION_ID                        0x2003
#define M_INSTANCE_ID                        0x2004
#define M_REG_USER_SIZE                      0x2005
#define M_REG_FULL_SIZE                      0x2006
#define M_REG_USER_OFFSET                    0x2007
#define M_REG_IOCTL_OFFSET                   0x2008
#define M_NUMBER_OF_EVENTS                   0x2009
#define M_CAPABILITY                         0x200A
#define M_SUB_FUNCTION_ID                    0x200B

/************************************************************************/
/*                                                                      */
/* MfpgaCommandControl                                                  */
/*                                                                      */
/************************************************************************/
#define M_FPGA_CMD_CTRL_TYPE_MASK            0x0FFFF000L
#define M_COMPLETION_MODE                    0x00003000L
#define M_STREAM_OUTPUT_FORMAT               0x00004000L

#define M_FPGA_OVERSCAN                      0x00005000L
#define M_LEFT                               0x00000100L
#define M_RIGHT                              0x00000200L
#define M_TOP                                0x00000400L
#define M_BOTTOM                             0x00000800L
#define M_FPGA_OVERSCAN_POSITION_MASK        (M_LEFT|M_RIGHT|M_TOP|M_BOTTOM)

/************************************************************************/
/*                                                                      */
/* MfpgaHookFunction                                                     */
/*                                                                      */
/************************************************************************/
#define M_END_OF_PROCESSING                  0x0001
#define M_INTERRUPT_OVERRUN                  0x0080

/************************************************************************/
/*                                                                      */
/* MfpgaGetHookInfo                                                     */
/*                                                                      */
/************************************************************************/
//#define M_TIME_STAMP                       0x0040
//#define M_FUNCTION_ID                      0x2003
//#define M_INSTANCE_ID                      0x2004
//#define M_SUB_FUNCTION_ID                    0x200B
#define M_FPGA_DEVICE_NUMBER                 0x2100

#define M_IN_FPGA_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) (false)
#define M_IN_FPGA_INQUIRE_STRING_RANGE(InquireType) (InquireType == M_FPGA_PACKAGE_NAME)
#define M_IN_FPGA_INQUIRE_DOUBLE_RANGE(InquireType) (false)
#define M_IN_FPGA_INQUIRE_MIL_INT64_RANGE(InquireType) (false)

#define M_FPGA_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_FPGA_INQUIRE_STRING_RANGE(InquireType)          || \
                                                        M_IN_FPGA_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType)  )

#ifdef __cplusplus
}
#endif

#endif

