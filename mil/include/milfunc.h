/***************************************************************************/
/*

    Filename:  MILFUNC.H
    Revision:  9.02.0812
    Content :  This file contains the prototypes for the Matrox
               Imaging Library (MIL) Mfunc user's functions.

    Copyright © Matrox Electronic Systems Ltd., 1992-2011.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILFUNC_H
#define __MILFUNC_H

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/
/* TOOLKIT FOR PSEUDO MIL FUNCTIONS DEVELOPMENT                            */
/***************************************************************************/
typedef MFTYPE32 void (MFTYPE MPTYPE *MIL_FUNC_FUNCTION_PTR)(MIL_ID FunctionId);
typedef MIL_FUNC_FUNCTION_PTR MFUNCSLAVEFCTPTR;
typedef MIL_FUNC_FUNCTION_PTR MFUNCFCTPTR;
typedef MIL_FUNC_FUNCTION_PTR MFUNCSLAVEPAFCTPTR;

#if M_MIL_USE_UNICODE
   MFTYPE32 MIL_ID MFTYPE MfuncAllocW(MIL_API_CONST_TEXT_PTR FunctionName,
                                      MIL_INT ParameterNumber,
                                      MIL_FUNC_FUNCTION_PTR WorkFunctionPtr,
                                      MIL_API_CONST_TEXT_PTR WorkDllName,
                                      MIL_API_CONST_TEXT_PTR WorkFunctionName,
                                      MIL_INT WorkFunctionOpcode,
                                      MIL_INT InitFlag,
                                      MIL_ID *FuncIdVarPtr);
   MFTYPE32 MIL_ID MFTYPE MfuncAllocA(MIL_API_CONST char* FunctionName,
                                      MIL_INT ParameterNumber,
                                      MIL_FUNC_FUNCTION_PTR WorkFunctionPtr,
                                      MIL_API_CONST char* WorkDllName,
                                      MIL_API_CONST char* WorkFunctionName,
                                      MIL_INT WorkFunctionOpcode,
                                      MIL_INT InitFlag,
                                      MIL_ID *FuncIdVarPtr);

   MFTYPE32 MIL_INT MFTYPE MfuncErrorReportW(MIL_ID FuncId,
                                            MIL_INT ErrorCode,
                                            MIL_API_CONST_TEXT_PTR ErrorString,
                                            MIL_API_CONST_TEXT_PTR ErrorSubString1,
                                            MIL_API_CONST_TEXT_PTR ErrorSubString2,
                                            MIL_API_CONST_TEXT_PTR ErrorSubString3);
   MFTYPE32 MIL_INT MFTYPE MfuncErrorReportA(MIL_ID FuncId,
                                            MIL_INT ErrorCode,
                                            MIL_API_CONST char* ErrorString,
                                            MIL_API_CONST char* ErrorSubString1,
                                            MIL_API_CONST char* ErrorSubString2,
                                            MIL_API_CONST char* ErrorSubString3);

   MFTYPE32 void MFTYPE MfuncParamStringW(MIL_ID FuncId, MIL_INT ParamIndex,MIL_API_CONST_TEXT_PTR ParamVal, MIL_INT SizeOfData, MIL_INT ParamAttribute);
   MFTYPE32 void MFTYPE MfuncParamStringA(MIL_ID FuncId, MIL_INT ParamIndex,MIL_API_CONST char* ParamVal, MIL_INT SizeOfData, MIL_INT ParamAttribute);

   MFTYPE32 void MFTYPE MfuncParamFilenameW(MIL_ID FuncId, MIL_INT ParamIndex, MIL_API_CONST_TEXT_PTR Filename, MIL_INT SizeOfFilename, MIL_INT ParamRole);
   MFTYPE32 void MFTYPE MfuncParamFilenameA(MIL_ID FuncId, MIL_INT ParamIndex, MIL_API_CONST char* Filename, MIL_INT SizeOfFilename, MIL_INT ParamRole);

   MFTYPE32 MIL_INT MFTYPE MfuncPrintMessageW(MIL_INT Mode,
                                              MIL_API_CONST_TEXT_PTR Str1,
                                              MIL_API_CONST_TEXT_PTR Str2,
                                              MIL_API_CONST_TEXT_PTR Str3,
                                              MIL_API_CONST_TEXT_PTR Str4,
                                              MIL_API_CONST_TEXT_PTR Str5);
   MFTYPE32 MIL_INT MFTYPE MfuncPrintMessageA(MIL_INT Mode,
                                              MIL_API_CONST char* Str1,
                                              MIL_API_CONST char* Str2,
                                              MIL_API_CONST char* Str3,
                                              MIL_API_CONST char* Str4,
                                              MIL_API_CONST char* Str5);
   #if M_MIL_UNICODE_API
      #define MfuncAlloc         MfuncAllocW
      #define MfuncErrorReport   MfuncErrorReportW
      #define MfuncParamString   MfuncParamStringW
      #define MfuncParamFilename MfuncParamFilenameW
      #define MfuncPrintMessage  MfuncPrintMessageW
   #else
      #define MfuncAlloc         MfuncAllocA
      #define MfuncErrorReport   MfuncErrorReportA
      #define MfuncParamString   MfuncParamStringA
      #define MfuncParamFilename MfuncParamFilenameA
      #define MfuncPrintMessage  MfuncPrintMessageA
   #endif
   #else
      MFTYPE32 MIL_ID MFTYPE MfuncAlloc(MIL_API_CONST_TEXT_PTR FunctionName,
                                        MIL_INT ParameterNumber,
                                        MIL_FUNC_FUNCTION_PTR WorkFunctionPtr,
                                        MIL_API_CONST_TEXT_PTR WorkDllName,
                                        MIL_API_CONST_TEXT_PTR WorkFunctionName,
                                        MIL_INT WorkFunctionOpcode,
                                        MIL_INT InitFlag,
                                        MIL_ID *FuncIdVarPtr);

      MFTYPE32 MIL_INT MFTYPE MfuncErrorReport( MIL_ID FuncId,
                                                MIL_INT ErrorCode,
                                                MIL_API_CONST_TEXT_PTR ErrorString,
                                                MIL_API_CONST_TEXT_PTR ErrorSubString1,
                                                MIL_API_CONST_TEXT_PTR ErrorSubString2,
                                                MIL_API_CONST_TEXT_PTR ErrorSubString3);

      MFTYPE32 void MFTYPE MfuncParamString(MIL_ID FuncId, MIL_INT ParamIndex,MIL_API_CONST_TEXT_PTR ParamVal, MIL_INT SizeOfData, MIL_INT ParamAttribute);

      MFTYPE32 void MFTYPE MfuncParamFilename(MIL_ID FuncId, MIL_INT ParamIndex, MIL_API_CONST_TEXT_PTR Filename, MIL_INT SizeOfFilename, MIL_INT ParamRole);

      MFTYPE32 MIL_INT MFTYPE MfuncPrintMessage(MIL_INT Mode, MIL_API_CONST_TEXT_PTR Str1,
                                                MIL_API_CONST_TEXT_PTR Str2,
                                                MIL_API_CONST_TEXT_PTR Str3,
                                                MIL_API_CONST_TEXT_PTR Str4,
                                                MIL_API_CONST_TEXT_PTR Str5);
#endif

MFTYPE32 MIL_ID MFTYPE MfuncAllocId(MIL_ID FunctionId, MIL_UINT64 ObjectType, void *UserPtr);
MFTYPE32 MIL_INT MFTYPE MfuncParamCheck(MIL_ID FuncId);
MFTYPE32 void MFTYPE MfuncParamId(MIL_ID FuncId, MIL_INT ParamIndex,MIL_ID ParamVal,
                                  MIL_UINT64 ParamIs, MIL_INT ParamHasAttr);
MFTYPE32 void MFTYPE MfuncParamLong (MIL_ID FuncId, MIL_INT ParamIndex, long ParamVal);
MFTYPE32 void MFTYPE MfuncParamMilInt(MIL_ID FuncId, MIL_INT ParamIndex, MIL_INT ParamVal);
MFTYPE32 void MFTYPE MfuncParamMilInt32(MIL_ID FuncId, MIL_INT ParamIndex, MIL_INT32 ParamVal);
MFTYPE32 void MFTYPE MfuncParamMilInt64(MIL_ID FuncId, MIL_INT ParamIndex, MIL_INT64 ParamVal);
MFTYPE32 void MFTYPE MfuncParamDouble(MIL_ID FuncId, MIL_INT ParamIndex, MIL_DOUBLE ParamVal);
#define MfuncParamMilDouble MfuncParamDouble
MFTYPE32 void MFTYPE MfuncParamPointer(MIL_ID FuncId, MIL_INT ParamIndex, void * ParamVal, MIL_INT SizeOfData, MIL_INT ParamAttribute);
MFTYPE32 void MFTYPE MfuncParamIdPointer(MIL_ID FuncId, MIL_INT ParamIndex, MIL_ID *ParamVal, MIL_UINT64 ParamIs, MIL_INT ParamAttribute);
MFTYPE32 void MFTYPE MfuncParamValue(MIL_ID FuncId, MIL_INT ParamIndex, void *ParamValuePtr);
MFTYPE32 MIL_INT MFTYPE MfuncGetError(MIL_ID FunctId, MIL_INT ErrorType,void MPTYPE *ErrorVarPtr);
MFTYPE32 void MFTYPE MfuncFreeId(MIL_ID FunctionId, MIL_ID ObjectId);
MFTYPE32 void MFTYPE MfuncFree(MIL_ID FuncId);
MFTYPE32 MIL_INT MFTYPE MfuncCall(MIL_ID FuncId);
MFTYPE32 MIL_INT MFTYPE MfuncInquire(MIL_ID ObjectId, MIL_INT InquireType, void* UserVarPtr);
MFTYPE32 MIL_INT MFTYPE MfuncExit();
MFTYPE32 void* MFTYPE MfuncMemory(MIL_INT Operation, MIL_INT OperationValue, MIL_INT OperationFlag, void *DataPointer);
MFTYPE32 MIL_ID MFTYPE MfuncGetNextId(MIL_ID CurrentId);

#if M_MIL_USE_64BIT
   MFTYPE32 void   MFTYPE MfuncControlInt64(MIL_ID ObjectId, MIL_INT ControlType, MIL_INT64 ControlFlag);
   #ifdef __cplusplus
      //////////////////////////////////////////////////////////////
      // MfuncControl function definition when compiling c++ files
      //////////////////////////////////////////////////////////////
      inline void MfuncControl(MIL_ID ObjectId,
                               MIL_INT ControlType,
                               MIL_INT64 ControlFlag)
         {
         MfuncControlInt64(ObjectId, ControlType, ControlFlag);
         };
   #else
      //////////////////////////////////////////////////////////////
      // For C file, call the default function, i.e. Int64 one
      //////////////////////////////////////////////////////////////
      #define MfuncControl MfuncControlInt64
   #endif // __cplusplus
#else
   #define MfuncControlInt64 MfuncControl
   MFTYPE32 void   MFTYPE MfuncControl(MIL_ID ObjectId, MIL_INT ControlType, MIL_DOUBLE ControlFlag);
#endif // M_MIL_USE_64BIT

/*The following Mfunc functions are obsolete*/
MFTYPE32 MIL_INT MFTYPE MfuncStart(MIL_ID FuncId);          /*Replaced by MfuncCall*/
MFTYPE32 void MFTYPE MfuncFreeAndEnd(MIL_ID FuncId);     /*Replaced by MfuncCall*/
MFTYPE32 MIL_INT MFTYPE MfuncModified(MIL_ID ImageId);      /*Replaced by MbufControl(M_MODIFIED)*/
MFTYPE32 MIL_INT MFTYPE MfuncParamRegister(MIL_ID FuncId);  /*Parameters must always be registered*/
MFTYPE32 void MFTYPE MfuncIdSetObjectType(MIL_ID FunctionId, MIL_ID ObjectId, MIL_INT ObjectType); /*Replaced by MfuncInquire and MfuncControl*/
MFTYPE32 MIL_INT MFTYPE MfuncIdGetObjectType(MIL_ID FunctionId, MIL_ID ObjectId);                  /*Replaced by MfuncInquire*/
MFTYPE32 void MFTYPE MfuncIdSetUserPtr(MIL_ID FunctionId, MIL_ID ObjectId, void *UserPtr);      /*Replaced by MfuncControl*/
MFTYPE32 void* MFTYPE MfuncIdGetUserPtr(MIL_ID FunctionId, MIL_ID ObjectId);                    /*Replaced by MfuncInquire*/



/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#endif
