/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*  Filename:  MILSETUP.H                                                  */
/*  Revision:  9.02.0812                                                    */
/*  Content :  This file contains definitions for specifying the target    */
/*             compile environment and the default state to set for        */
/*             MIL (Matrox Imaging Library). It also defines the           */
/*             MappAllocDefault() and MappFreeDefault() macros.            */
/*                                                                         */
/*  Copyright © Matrox Electronic Systems Ltd., 1992-2011.                */
/*  All Rights Reserved.                                                   */
/*                                                                         */
/*                                                                         */
/***************************************************************************/

#ifndef __MILSETUP_H__
#define __MILSETUP_H__


/************************************************************************/
/* COMPILATION FLAG                                                     */
/* One and only one flag must be active                                 */
/************************************************************************/
#ifndef M_MIL_USE_OS
   #define M_MIL_USE_OS               1
   #if defined(__linux__)
      #define M_MIL_USE_WINDOWS       0
      #define M_MIL_USE_LINUX         1
      #define M_MIL_USE_CE            0
      #ifdef __x86_64__
         #define M_MIL_USE_64BIT      1
      #endif

      #ifdef __INTEL_COMPILER
         #define M_MIL_USE_LINTEL     1
      #endif
   #elif defined(UNDER_CE)
      #define M_MIL_USE_WINDOWS       1
      #define M_MIL_USE_LINUX         0
      #define M_MIL_USE_CE            1

      #if (_MSC_VER >= 1400) && !defined(M_MIL_USING_SAFE_CRT)
        #if (_WIN32_WCE >= 0x600)
          #define M_MIL_USING_SAFE_CRT       1
        #else
          #define M_MIL_USING_SAFE_CRT       0
        #endif
      #endif
   #else
      #define M_MIL_USE_WINDOWS       1
      #define M_MIL_USE_LINUX         0
      #define M_MIL_USE_CE            0
      #ifdef _WIN64
         #define M_MIL_USE_64BIT      1
      #endif

      #if (_MSC_VER >= 1400) && !defined(M_MIL_USING_SAFE_CRT)
         #define M_MIL_USING_SAFE_CRT       1
      #endif
   #endif

   #if defined(__POWERPC__)
      #define M_MIL_USE_PPC           1
   #else
      #define M_MIL_USE_PPC           0
   #endif
#endif

#if !(M_MIL_USE_WINDOWS || M_MIL_USE_PPC || M_MIL_USE_LINUX)
#error "You must set at least one compilation flag."
#endif

#if ( (M_MIL_USE_WINDOWS && M_MIL_USE_PPC)   || \
      (M_MIL_USE_PPC     && M_MIL_USE_LINUX) || \
      (M_MIL_USE_WINDOWS && M_MIL_USE_LINUX) )
#error "You must select one and only one compilation flag."
#endif

// Defined M_MIL_LITE to avoid declaration of highlvl safe type functions
// while compiling MIL dll
#if M_COMPILING_MIL_LITE && !defined M_MIL_LITE
#define M_MIL_LITE 1
#endif

/************************************************************************/
/*This flag indicates if MIL has been compiled without UNICODE support  */
/*If MIL supports UNICODE, user can define UNICODE to use UNICODE API   */
/************************************************************************/
#if !defined(M_MIL_USE_UNICODE) && !M_MIL_USE_LINUX && !M_MIL_USE_PPC
   #define M_MIL_USE_UNICODE 1
#elif !defined (M_MIL_USE_UNICODE)
   #define M_MIL_USE_UNICODE 0
#endif

#if  M_MIL_USE_UNICODE
   #if defined(UNICODE)
      #define M_MIL_UNICODE_API 1
   #else
      #define M_MIL_UNICODE_API 0
   #endif
#endif

#if (M_MIL_USE_LINUX || M_MIL_USE_WINDOWS) && !M_MIL_USE_PHARLAP
#define M_MIL_USE_TTF_TEXT 1
#endif

#if M_MIL_USE_LINUX || (UNICODE && M_MIL_USE_UNICODE)
#define M_MIL_USE_TTF_UNICODE 1
#endif
/************************************************************************/
/* DEFAULT STATE INITIALIZATION FLAG                                    */
/************************************************************************/

#define M_SETUP                    M_DEFAULT

//Defines for INSTALLDIR support
#define INSTALL_DIR MIL_TEXT("///INSTALLDIR///")
#define M_TEMP_DIR MIL_TEXT("///MILTEMPDIRDIR///")

#if   M_MIL_USE_LINUX
   #define M_IMAGE_PATH               INSTALL_DIR MIL_TEXT("images/")
   #define M_CONTEXT_PATH             INSTALL_DIR MIL_TEXT("contexts/")
   #define M_SAVE_PATH                MIL_TEXT("")
#elif M_MIL_USE_CE
   #define M_IMAGE_PATH               MIL_TEXT("\\Userdisk\\mil\\images\\")
   #define M_CONTEXT_PATH             MIL_TEXT("\\Userdisk\\mil\\contexts\\")
   #define M_SAVE_PATH                MIL_TEXT("\\Userdisk\\")
#else
   #define M_IMAGE_PATH               INSTALL_DIR MIL_TEXT("images\\")
   #define M_CONTEXT_PATH             INSTALL_DIR MIL_TEXT("contexts\\")
   #define M_SAVE_PATH                MIL_TEXT("")
#endif

/************************************************************************/
/* DEFAULT SYSTEM SPECIFICATIONS                                        */
/************************************************************************/

/*DO NOT EDIT: you should change the default values with the Mil Configuration utility*/
#define M_DEF_SYSTEM_TYPE          M_SYSTEM_DEFAULT
#define M_DEF_SYSTEM_NUM           M_DEFAULT
#define M_SYSTEM_SETUP             M_DEF_SYSTEM_TYPE

/************************************************************************/
/* DEFAULT DIGITIZER SPECIFICATIONS                                     */
/************************************************************************/

/*DO NOT EDIT: you should change the default values with the Mil Configuration utility*/
#define M_DEF_DIGITIZER_NUM        M_DEFAULT
#define M_DEF_DIGITIZER_FORMAT     MIL_TEXT("M_DEFAULT")
#define M_DEF_DIGITIZER_INIT       M_DEFAULT
#define M_CAMERA_SETUP             M_DEF_DIGITIZER_FORMAT

/************************************************************************/
/* DEFAULT DISPLAY SPECIFICATIONS                                       */
/************************************************************************/

/*DO NOT EDIT: you should change the default values with the Mil Configuration utility*/
#define M_DEF_DISPLAY_NUM                  M_DEFAULT
#define M_DEF_DISPLAY_FORMAT               MIL_TEXT("M_DEFAULT")
#define M_DEF_DISPLAY_INIT                 M_DEFAULT
#define M_DISPLAY_SETUP                    M_DEF_DISPLAY_FORMAT

/************************************************************************/
/* DEFAULT IMAGE BUFFER SPECIFICATIONS                                  */
/************************************************************************/

#define M_DEF_IMAGE_NUMBANDS_MIN   1
#define M_DEF_IMAGE_SIZE_X_MIN     50
#define M_DEF_IMAGE_SIZE_Y_MIN     50
#define M_DEF_IMAGE_SIZE_X_MAX     4000000
#define M_DEF_IMAGE_SIZE_Y_MAX     4000000
#define M_DEF_IMAGE_TYPE           (8+M_UNSIGNED)
#define M_DEF_IMAGE_ATTRIBUTE_MIN  (M_IMAGE+M_PROC)

/************************************************************************/
/* Enables DMIL monitoring auto-publish mode. 0 == Disabled             */
/************************************************************************/
#define M_DEF_CLUSTER_NODE  0

/***************************************************************************/
/* LocalBufferAllocDefault - Local macro to allocate a default MIL buffer: */
/*                                                                         */
/* MIL_ID *SystemIdVarPtr;                                                 */
/* MIL_ID *DisplayIdVarPtr;                                                */
/* MIL_ID *ImageIdVarPtr;                                                  */
/*                                                                         */
/***************************************************************************/
#define LocalBufferAllocDefault(SystemIdVarPtr,DisplayIdVarPtr,DigitizerIdVarPtr,ImageIdVarPtr) \
{                                                                            \
  /* local variables */                                                      \
  MIL_INT m_def_image_numbands = M_DEFAULT;                                  \
  MIL_INT m_def_image_size_x   = M_DEFAULT;                                  \
  MIL_INT m_def_image_size_y   = M_DEFAULT;                                  \
  MIL_INT m_def_image_type     = M_DEF_IMAGE_TYPE;                           \
  MIL_INT m_def_image_attribute= M_DEF_IMAGE_ATTRIBUTE_MIN;                  \
  MIL_ID *LNullPtr = M_NULL;                                                 \
  MIL_ID LNull     = M_NULL;                                                 \
                                                                             \
  /* determines the needed size band, x, y, type and attribute */            \
  if ((((MIL_ID *)(DigitizerIdVarPtr))   != LNullPtr)   &&                   \
         ((*((MIL_ID *)(DigitizerIdVarPtr)))!= LNull))                       \
     {                                                                       \
     m_def_image_size_x =                                                    \
       MdigInquire(*((MIL_ID *)(DigitizerIdVarPtr)),M_SIZE_X,M_NULL);        \
     m_def_image_size_y =                                                    \
       MdigInquire(*((MIL_ID *)(DigitizerIdVarPtr)),M_SIZE_Y,M_NULL);        \
     m_def_image_type =                                                      \
       MdigInquire(*((MIL_ID *)(DigitizerIdVarPtr)),M_TYPE,M_NULL);          \
                                                                             \
     if (m_def_image_size_x < M_DEF_IMAGE_SIZE_X_MIN)                        \
         m_def_image_size_x = M_DEF_IMAGE_SIZE_X_MIN;                        \
     if (m_def_image_size_y < M_DEF_IMAGE_SIZE_Y_MIN)                        \
         m_def_image_size_y = M_DEF_IMAGE_SIZE_Y_MIN;                        \
     if (m_def_image_size_x > M_DEF_IMAGE_SIZE_X_MAX)                        \
         m_def_image_size_x = M_DEF_IMAGE_SIZE_X_MAX;                        \
     if (m_def_image_size_y > M_DEF_IMAGE_SIZE_Y_MAX)                        \
         m_def_image_size_y = M_DEF_IMAGE_SIZE_Y_MAX;                        \
     if (((m_def_image_type & 0xFF) < (M_DEF_IMAGE_TYPE & 0xFF)) ||          \
         ((m_def_image_type & 0xFF) > (M_DEF_IMAGE_TYPE & 0xFF)))            \
         m_def_image_type   = M_DEF_IMAGE_TYPE;                              \
      }                                                                      \
                                                                             \
                                                                             \
  /* determines the needed attribute and number of band */                   \
  m_def_image_attribute = M_DEF_IMAGE_ATTRIBUTE_MIN;                         \
  if ((((MIL_ID *)(DisplayIdVarPtr))   != LNullPtr)   &&                     \
      ((*((MIL_ID *)(DisplayIdVarPtr)))!= LNull))                            \
     m_def_image_attribute |= M_DISP;                                        \
  if (((((MIL_ID *)DigitizerIdVarPtr))   != LNullPtr) &&                     \
      ((*((MIL_ID *)(DigitizerIdVarPtr)))!= LNull))                          \
      {                                                                      \
      m_def_image_attribute |= M_GRAB;                                       \
      m_def_image_numbands =                                                 \
        MdigInquire(*(MIL_ID *)DigitizerIdVarPtr,M_SIZE_BAND,M_NULL);        \
      if (m_def_image_numbands<M_DEF_IMAGE_NUMBANDS_MIN)                     \
         m_def_image_numbands=M_DEF_IMAGE_NUMBANDS_MIN;                      \
      }                                                                      \
                                                                             \
  /* allocates a monochromatic or color image buffer */                      \
  MbufAllocColor(*((MIL_ID *)(SystemIdVarPtr)),                              \
                m_def_image_numbands,                                        \
                m_def_image_size_x,                                          \
                m_def_image_size_y,                                          \
                m_def_image_type,                                            \
                m_def_image_attribute,                                       \
                ((MIL_ID *)(ImageIdVarPtr)));                                \
                                                                             \
  /* clear and display the image buffer */                                   \
  if (((DisplayIdVarPtr) !=LNullPtr) &&                                      \
      ((*((MIL_ID *)(DisplayIdVarPtr)))!=LNull)  &&                          \
      ((*((MIL_ID *)(ImageIdVarPtr)))  !=LNull))                             \
     {                                                                       \
     MbufClear(*((MIL_ID *)(ImageIdVarPtr)), 0);                             \
     MdispSelect(*((MIL_ID *)(DisplayIdVarPtr)),                             \
                 *((MIL_ID *)(ImageIdVarPtr)));                              \
     }                                                                       \
}

/**************************************************************************/
/* MappAllocDefault - macro to allocate default MIL objects:              */
/*                                                                        */
/* long    InitFlag;                                                      */
/* MIL_ID *ApplicationIdVarPtr;                                           */
/* MIL_ID *SystemIdVarPtr;                                                */
/* MIL_ID *DisplayIdVarPtr;                                               */
/* MIL_ID *DigitizerIdVarPtr;                                             */
/* MIL_ID *ImageIdVarPtr;                                                 */
/*                                                                        */
/* Note:                                                                  */
/*       An application must be allocated before a system.                */
/*       An system must be allocated before a display,digitzer or image.  */
/*                                                                        */
/**************************************************************************/

#define MappAllocDefault(InitFlag,ApplicationIdVarPtr,SystemIdVarPtr,DisplayIdVarPtr,DigitizerIdVarPtr,ImageIdVarPtr) \
{                                                                            \
  /* local variables */                                                      \
  MIL_ID *LNullPtr = M_NULL;                                                 \
  MIL_ID LNull     = M_NULL;                                                 \
  /*Make sure variables are initialized to M_NULL if a call fails*/          \
  if (((MIL_ID *)(ApplicationIdVarPtr)) != LNullPtr)                         \
            (*(MIL_ID *)(ApplicationIdVarPtr)) = M_NULL;                     \
  if (((MIL_ID *)(SystemIdVarPtr)) != LNullPtr)                              \
            (*(MIL_ID *)(SystemIdVarPtr)) = M_NULL;                          \
  if (((MIL_ID *)(DisplayIdVarPtr)) != LNullPtr)                             \
            (*(MIL_ID *)(DisplayIdVarPtr)) = M_NULL;                         \
  if (((MIL_ID *)(DigitizerIdVarPtr)) != LNullPtr)                           \
            (*(MIL_ID *)(DigitizerIdVarPtr)) = M_NULL;                       \
  if (((MIL_ID *)(ImageIdVarPtr)) != LNullPtr)                               \
            (*(MIL_ID *)(ImageIdVarPtr)) = M_NULL;                           \
  /* allocate a MIL application. */                                          \
  if (((MIL_ID *)(ApplicationIdVarPtr)) != LNullPtr)                         \
     MappAlloc(InitFlag|M_CLUSTER_NODE(M_DEF_CLUSTER_NODE),((MIL_ID *)(ApplicationIdVarPtr))); \
                                                                             \
  /* Enables DMIL monitoring mode */                                         \
  if(M_DEF_CLUSTER_NODE)                                                     \
     {                                                                       \
     MappControl(M_DMIL_CONNECTION, M_DMIL_MONITOR);                         \
     MappControl(M_DMIL_AUTO_PUBLISH_ALL, M_ENABLE);                         \
     }                                                                       \
                                                                             \
  /* allocate a system */                                                    \
  if ((((MIL_ID *)(SystemIdVarPtr))        != LNullPtr) &&                   \
      (((MIL_ID *)(ApplicationIdVarPtr))   != LNullPtr) &&                   \
      ((*((MIL_ID *)(ApplicationIdVarPtr)))!= LNull))                        \
     MsysAlloc(M_DEF_SYSTEM_TYPE,                                            \
               M_DEF_SYSTEM_NUM,                                             \
               (InitFlag),                                                   \
               ((MIL_ID *)(SystemIdVarPtr)));                                \
                                                                             \
  /* allocate a display */                                                   \
  if ((((MIL_ID *)(DisplayIdVarPtr)) != LNullPtr)  &&                        \
      (((MIL_ID *)(SystemIdVarPtr))  != LNullPtr)  &&                        \
      ((*((MIL_ID *)(SystemIdVarPtr))) != LNull))                            \
     MdispAlloc(*((MIL_ID *)(SystemIdVarPtr)),                               \
               M_DEF_DISPLAY_NUM,                                            \
               M_DEF_DISPLAY_FORMAT,                                         \
               M_DEF_DISPLAY_INIT,                                           \
               ((MIL_ID *)(DisplayIdVarPtr)));                               \
                                                                             \
  /* allocate a digitizer */                                                 \
  if ((((MIL_ID *)(DigitizerIdVarPtr)) != LNullPtr) &&                       \
      (((MIL_ID *)(SystemIdVarPtr))    != LNullPtr) &&                       \
      ((*((MIL_ID *)(SystemIdVarPtr))) != LNull))                            \
     MdigAlloc(*((MIL_ID *)(SystemIdVarPtr)),                                \
               M_DEF_DIGITIZER_NUM,                                          \
               M_DEF_DIGITIZER_FORMAT,                                       \
               M_DEF_DIGITIZER_INIT,                                         \
               ((MIL_ID *)(DigitizerIdVarPtr)));                             \
                                                                             \
                                                                             \
  /* allocate an image buffer */                                             \
  if ((((MIL_ID *)(ImageIdVarPtr))  != LNullPtr)  &&                         \
      (((MIL_ID *)(SystemIdVarPtr)) != LNullPtr)  &&                         \
      ((*((MIL_ID *)(SystemIdVarPtr)))!= LNull))                             \
     LocalBufferAllocDefault(((MIL_ID *)(SystemIdVarPtr)),                   \
                             ((MIL_ID *)(DisplayIdVarPtr)),                  \
                             ((MIL_ID *)(DigitizerIdVarPtr)),                \
                             ((MIL_ID *)(ImageIdVarPtr)));                   \
                                                                             \
}

/************************************************************************/
/* MappFreeDefault - macro to free default MIL objects:                 */
/*                                                                      */
/* MIL_ID ApplicationId;                                                */
/* MIL_ID SystemId;                                                     */
/* MIL_ID DisplayId;                                                    */
/* MIL_ID DigitizerId;                                                  */
/* MIL_ID ImageId;                                                      */
/*                                                                      */
/************************************************************************/

#define MappFreeDefault(ApplicationId,SystemId,DisplayId,DigitizerId,BufferId) \
{                                                                           \
  MIL_ID NullId = M_NULL;                                                   \
                                                                            \
  /* free the image buffer */                                               \
  if ((BufferId) != NullId)                                                 \
     {                                                                      \
     MbufFree((BufferId));                                                  \
     }                                                                      \
                                                                            \
  /* free digitizer */                                                      \
  if ((DigitizerId) != NullId)                                              \
     {                                                                      \
     MdigFree((DigitizerId));                                               \
     }                                                                      \
                                                                            \
  /* free the display */                                                    \
  if ((DisplayId) != NullId)                                                \
     {                                                                      \
     MdispFree((DisplayId));                                                \
     }                                                                      \
                                                                            \
  /* free the system */                                                     \
  if ((SystemId) != NullId)                                                 \
     {                                                                      \
     MsysFree((SystemId));                                                  \
     }                                                                      \
                                                                            \
  /* free the application */                                                \
  if ((ApplicationId) != NullId)                                            \
     {                                                                      \
     MappFree((ApplicationId));                                             \
     }                                                                      \
}

#endif /*__MILSETUP_H__*/
