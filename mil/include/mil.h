
/************************************************************************/
/*
*
* Filename     :  MIL.H
* Revision     :  9.02.0812
* Content      :  This file contains the defines necessary to use the
*                 Matrox Imaging Library "C" user interface.
*
* Comments     :  Some defines may be here but not yet
*                 implemented in the library.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2011.
* All Rights Reserved
*************************************************************************/

#ifndef __MIL_H
#define __MIL_H

#ifndef BW_COMPATIBILITY
   #define BW_COMPATIBILITY 0x092
#endif

/************************************************************************/
/* DEFAULT SETUP FLAG */
/************************************************************************/

/* include set-up instructions (if not specified) */
#include <milsetup.h>

/* include mil memory allocator when needed */
#if M_MIL_USE_MEMORY_ALLOCATOR
   #include <milmem.h>
#endif

/************************************************************************/
/* MIL buffer identifier type                                           */
/************************************************************************/
#if M_MIL_USE_64BIT
#define M_MIL_USE_INT64_ID 1
#define M_MIL_USE_LARGE_ID_LIST 1
#else
#define M_MIL_USE_LARGE_ID_LIST 0
#endif

#if defined(M_USE_MBUFBLIT) && !(M_MIL_USE_PPC || M_MIL_USE_LINUX)
#include <memory.h>  // for memset()
#include <mddraw.h>   // for lpdirectdrawsurface
#endif

#if (BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x91)
#define M_MIL_USE_UNIFIED_MILBUFFERINFO 0
#else
#define M_MIL_USE_UNIFIED_MILBUFFERINFO 0
#endif
/************************************************************************/
/* Support for old defines name                                         */
/************************************************************************/
#ifndef OldDefinesSupport
#define OldDefinesSupport     1
#endif

/************************************************************************/
/* MIL OS support                                                       */
/************************************************************************/
#include <milos.h>


/************************************************************************/
/* MIL HOST CURRENT VERSION  (Inquired by MappInquire)                  */
/************************************************************************/
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
   #define M_MIL_CURRENT_VERSION          9.00
   #define M_MIL_CURRENT_INT_VERSION    0x0900
   #define M_MIL_CURRENT_ASCII_VERSION  "9.00"

   #define M_CURRENT_DATAGRAM_VERSION        900
   #define M_CURRENT_DATAGRAM_ASCII_VERSION  "9.00"
#else
   #define M_MIL_CURRENT_VERSION          9.60
   #define M_MIL_CURRENT_INT_VERSION    0x0960
   #define M_MIL_CURRENT_ASCII_VERSION  "9.60"

   #define M_CURRENT_DATAGRAM_VERSION        960
   #define M_CURRENT_DATAGRAM_ASCII_VERSION  "9.60"
#endif   // ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))

#define M_DMILTCP_TRANSPORT_PROTOCOL   MT("dmiltcp")
#define M_DMILPCIE_TRANSPORT_PROTOCOL  MT("dmilpcie")
#define M_DMILIB_TRANSPORT_PROTOCOL    MT("dmilib")


/************************************************************************
 * MIL Highlevel processing pack versions
 * Those version numbers are used only by the highlevel module and must NOT
 * be confused with M_MIL_CURRENT_VERSION and MappInquire(...M_VERSION...)
 * The define serves for the MxxxStream function of each highlevel module
 ************************************************************************/
// DO NOT CHANGE THOSE VALUES
#define M_PROC_VERSION_75        7.5
#define M_PROC_VERSION_75_PP1    7.51
#define M_PROC_VERSION_80        8.0
#define M_PROC_VERSION_80_PP1    8.1
#define M_PROC_VERSION_80_PP2    8.2
#define M_PROC_VERSION_80_PP3    8.3
#define M_PROC_VERSION_80_PP4    8.4
#define M_PROC_VERSION_90        9.0
#define M_PROC_VERSION_90_PP1    9.1
#define M_PROC_VERSION_90_PP2    9.2

#if M_MIL_USE_INT64_ID
   typedef  MIL_INT64  MIL_ID;
#else
   typedef  MIL_INT32  MIL_ID;
#endif

/************************************************************************/
/* MIL HighLevel Context File Data type                                 */
/************************************************************************/
#define M_MIL_USE_INT64_DATA_FILES 0
#if M_MIL_USE_INT64_DATA_FILES
   typedef MIL_INT64 FILE_DATA_TYPE;
#else
   typedef MIL_INT32 FILE_DATA_TYPE;
#endif

/************************************************************************/
/* MIL main                                                             */
/************************************************************************/
#if M_MIL_USE_CE
   #define WIN32_LEAN_AND_MEAN
   //#include <winsock2.h>
   #include <windows.h>
   #include <cesdk.h>
#endif


/************************************************************************/
/* General default parameters (may be bit encoded)                      */
/************************************************************************/
#if M_MIL_USE_LINUX && M_MIL_USE_64BIT
#define M_NULL                                           0L
#else
#define M_NULL                                           0
#endif

#if M_MIL_USE_LINUX && M_MIL_USE_64BIT
   #define MAKE_INT64(I)        (I ## L)
   #define MAKE_UINT64(I)       (I ## LU)
#elif M_MIL_USE_LINUX || M_MIL_USE_PPC || __GNUC__
   #define MAKE_INT64(I)        (I ## LL)
   #define MAKE_UINT64(I)       (I ## LLU)
#elif M_MIL_USE_WINDOWS
   #define MAKE_INT64(I)        (I##I64)
   #define MAKE_UINT64(I)       (I##Ui64)
#else
   #define MAKE_INT64(I)        (I)
   #define MAKE_UINT64(I)       (I)
#endif

// Make constant value
#if M_MIL_USE_64BIT
   #define MIL_MAKE_CONST(X32, X64) (MAKE_INT64(X64))
#else
   #define MIL_MAKE_CONST(X32, X64) (X32)
#endif

/*Pseudo IDs*/
#define M_PSEUDO_ID                                   0x00800000L
#define M_DEFAULT_LUT                                 (M_PSEUDO_ID+1)
#define M_PSEUDO_LUT                                  (M_PSEUDO_ID+2)
#define M_ALL_DISPLAYS                                (M_PSEUDO_ID+3)
#define M_INDIAN_PATTERN                              (M_PSEUDO_ID+4)   // Use in Indian display scheme
#define M_TRANSIENT_PATTERN                           (M_PSEUDO_ID+5)   // Use in Transient display scheme
#define M_DISPLAY_SERVICE                             (M_PSEUDO_ID+6)   // Used for control/inquires not specific to one display.
#define M_DEFAULT_ERROR_CONTEXT                       (M_PSEUDO_ID+7)   // Used as a pseudo func ID for MfuncErrorReport.
#define M_DEFAULT_UNIFORM_CALIBRATION                 (M_PSEUDO_ID+8)   // Used as a pseudo calibration object ID

#define M_ID_OFFSET_OF_DEFAULT_KERNEL                 (0x00100000L|M_PSEUDO_ID)
/*Reserve 256 values*/
/*#define M_ID_OFFSET_OF_DEFAULT_KERNEL                 (0x00100000L|M_PSEUDO_ID + 255)*/

#define M_IS_PSEUDO_ID(X)                             (X&M_PSEUDO_ID)
#define M_IS_VIDEO_DEVICE_ID(a)                       ((a>=M_VIDEO_DEVICE_ID) && (a<M_VIDEO_DEVICE_ID+M_MAX_VIDEO_DEVICE))
#define M_VIDEO_DEVICE_INDEX_FROM_ID(a)               ((M_IS_VIDEO_DEVICE_ID(a)) ? ((a) - M_VIDEO_DEVICE_ID) : M_INVALID)
#define M_OVERSCAN_DISABLE                            0x00080000L

//////////////////////////////////////////////////////////////////////////////
// MIL_ID manipulation macros
#if M_MIL_USE_INT64_ID
   // Id use the following representation:
   // SUUU UUUU UUUU LLLL LLLL LLLL LLLL NNNN     NNNN NNNN POOO BBBB XXXX XXXX XXXX XXXX
   //
   // where
   //    U: Unusable (ID in double)
   //    L: if M_MIL_USE_LARGE_ID_LIST == 1, defined as X otherwise as Reserved
   //    R: Reserved
   //    S: Sign bit (can't be used)
   //    N: Cluster node
   //    P: Pseudo-id
   //    O: ONL system number
   //    B: ONL board number
   //    X: Id

   #define M_WORKSPACE_MASK               0xFFF7F0000
   #define M_CLUSTER_NODE_MASK            0xFFF000000
   #define M_LOCAL_WORKSPACE_MASK         0x0007F0000
   #define M_INVALID_PART_MASK            0xFFFF000000800000
   #define M_DEFAULT_WORKSPACE_VALUE      0xFFF7F0000
   #define M_DEFAULT_CLUSTER_NODE_VALUE   0xFFF000000
   #define M_DEFAULT_LOCAL_WORKSPACE      0x0007F0000
   #define M_NB_CLUSTER_NODES             0x1000
   #define M_INVALID_CLUSTER_NODE         M_NB_CLUSTER_NODES+1L
#else
   // Id use the following representation:
   // SNNN NNNN POOO BBBB XXXX XXXX XXXX XXXX
   //
   // where
   //    S: Sign bit (can't be used)
   //    N: Cluster node
   //    P: Pseudo-id
   //    O: ONL system number
   //    B: ONL board number
   //    X: Id

   #define M_WORKSPACE_MASK               0x7F7F0000
   #define M_CLUSTER_NODE_MASK            0x7F000000
   #define M_LOCAL_WORKSPACE_MASK         0x007F0000
   #if M_MIL_USE_PPC
      // PPC only reads the first 32 bits of the ID, even if it was
      // logged as a 64 bits value.  This makes it possible to have
      // the high-bit of the ID set, which should not be seen as an
      // invalid id.  Thus, the high-bit is not considered as invalid
      // in PPC and will simply always be ignored.
      #define M_INVALID_PART_MASK         0x00800000
   #else
      #define M_INVALID_PART_MASK         0x80800000
   #endif   // M_MIL_USE_PPC
   #define M_DEFAULT_WORKSPACE_VALUE      0x7F7F0000
   #define M_DEFAULT_CLUSTER_NODE_VALUE   0x7F000000
   #define M_DEFAULT_LOCAL_WORKSPACE      0x007F0000
   #define M_NB_CLUSTER_NODES             0x80
   #define M_INVALID_CLUSTER_NODE         M_NB_CLUSTER_NODES+1L
#endif   // M_MIL_USE_INT64_ID

#define M_NB_LOCAL_WORKSPACES          0x80
#define M_INVALID_LOCAL_WORKSPACE      M_NB_LOCAL_WORKSPACES+1L
#define M_INVALID_WORKSPACE            -1L

#define M_ONL_SYSTEM_MASK        0x700000
#define M_ONL_BOARD_MASK         0xF0000
#define M_ONL_SYSTEM_SHIFT       20
#define M_ONL_BOARD_SHIFT        16
#define M_WORKSPACE_SHIFT        16
#define M_CLUSTER_NODE_SHIFT     24
#define M_LOCAL_WORKSPACE_SHIFT  16
#if M_MIL_USE_LARGE_ID_LIST
#define M_NAKED_ID_MASK          MAKE_INT64(0x0000FFF00000FFFF)
#else
#define M_NAKED_ID_MASK          0xFFFF
#endif

#define M_MAKE_ID(NakedId, FullWorkspace)       ((((FullWorkspace) << M_WORKSPACE_SHIFT) & M_WORKSPACE_MASK) | \
                                                 ((NakedId) & M_NAKED_ID_MASK))
#define M_MAKE_DEFAULT_ID(NakedId)              M_MAKE_ID((NakedId), (M_DEFAULT_WORKSPACE_VALUE >> M_WORKSPACE_SHIFT))

#define M_FALSE                                       0L
#define M_NO                                          0L
#define M_OFF                                         0L
#define M_IN_PROGRESS                                 0L
#define M_OUTSIDE                                     0L
#define M_INSIDE                                      1L
#define M_FINISHED                                    1L
#define M_TRUE                                        1L
#define M_YES                                         1L
#define M_ON                                          1L
#define M_WAIT                                        1L
#define M_CREATE                                      M_YES
#define M_FREE                                        0x00020000
#define M_UNICODE_CLIENT                              0x01000000L
#define M_SPECIAL                                     0x02000000L
#define M_ASCII_CLIENT                                0x04000000L
#define M_QUIET                                       0x08000000L
#define M_DEFAULT                                     0x10000000L
#define M_VALID                                       0x00000001L
#define M_INVALID                                     -1
#define M_UNKNOWN                                     -9999L
#define M_CLEAR                                       0x00000001L
#define M_NO_CLEAR                                    0x00000002L
#define M_ENABLE                                      -9997L
#define M_DISABLE                                     -9999L
#define M_CONFIG                                      0x20000000L
#define M_LOCAL                                       0x01000000
#define M_REMOTE                                      0x00000000
#define M_CUSTOM                                      2
#define M_OFFICIAL                                    3
#define M_SKIP_CHECK                                  2
 

#define M_UNINITIALIZED                               0x0badbad0

#define M_PERSISTENT                                  0x00000100L

#define M_ALL                                         0x40000000L
#define M_ANY                                         0x11000000L
#define M_SAME                                                -1L
#define M_INVALID_MDID                                0x40000000L
#define M_ALWAYS                                               0L  // defined in Milblob.h
#define M_FOREVER                                             -1   // Same as in mildrv.h

// Macro used to process M_DEFAULT
#define PROCESS_M_DEFAULT(VALUE, REPLACEMENT_VALUE) if((VALUE) == M_DEFAULT) {(VALUE) = (REPLACEMENT_VALUE);}

// Macro for M_INDSIDE & M_OUTSIDE
#define M_IS_MOUSE_OUTSIDE(v) (((M_OUTSIDE == v) || (M_ENABLE == v))? M_YES: M_NO)
#define M_IS_MOUSE_INSIDE(v) ((M_INSIDE == v)? M_YES: M_NO)


/************************************************************************/
/* Tube generic information.                                            */
/************************************************************************/
// Tubes are used by the command dispatcher to obtain information
// about unknown ids for creating the necessary local shadows.
#define M_TUBE_NETWORK     0
#define M_TUBE_ODYSSEY     1
#define M_TUBE_COUNT       2  // Number of different tube types

/************************************************************************/
/* Board generic information.                                           */
/************************************************************************/
#define M_RS170                                       0x00000001L
#define M_NTSC                                        0x00000002L
#define M_CCIR                                        0x00000003L
#define M_PAL                                         0x00000004L
#define M_NTSC_RGB                                    0x00000005L
#define M_PAL_RGB                                     0x00000006L
#define M_SECAM_RGB                                   0x00000007L
#define M_SECAM                                       0x00000008L
/* Reserve next 2 values                       from   0x00000009L*/
/*                                             to     0x0000000AL*/

/************************************************************************/
/* Iris Product select the type of lighting environment                 */
/************************************************************************/

#define M_LIGHT_INDOOR                                0x0L
#define M_LIGHT_OUTDOOR                               0x1L



/************************************************************************/
/* Buffer ID offset for defaults                                        */
/************************************************************************/
#define M_UNSIGNED                                    0x00000000L
#define M_SIGNED                                      0x08000000L
#define M_FLOAT                                      (0x40000000L | M_SIGNED)
#define M_DOUBLE                                     (0x20000000L | M_SIGNED)
#define M_SIZE_BIT_MASK                               0x000000FFL
#define M_TYPE_MASK                                   0x7FFFFF00L

/************************************************************************/
/* MMX related                                                          */
/************************************************************************/
#define M_READ_PREFETCH_EXTRA_BYTES                   32

// Kept for backward compatibility.
#define M_MMX_EXTRA_BYTES                             M_READ_PREFETCH_EXTRA_BYTES

// Default values for memory allocators. Can be overridden at run-
// time by any OS-specific version of the MIL memory allocator
#define M_MEMORY_ALLOC_PRE_PADDING_VALUE             M_READ_PREFETCH_EXTRA_BYTES
#define M_MEMORY_ALLOC_POST_PADDING_VALUE            M_READ_PREFETCH_EXTRA_BYTES
#define M_MEMORY_ALLOC_PITCH_BYTE_VALUE              1
#define M_MEMORY_ALLOC_ALIGNMENT_VALUE               128

/************************************************************************/
/* Non cachable related                                                 */
/************************************************************************/
#define M_NO_ALIGNMENT                               -1
#define M_4K_ALIGNMENT                                4096


/************************************************************************/
/* Multi thread                                                         */
/************************************************************************/
#define M_HOST_THREAD                                 0x00000002L
#define M_MIL_THREAD                                  0x00000004L
#define M_STATE                                       0x00000008L
#define M_SIGNALED                                    0x00000010L
#define M_NOT_SIGNALED                                0x00000020L
#define M_THREAD_DETACH                               0x00000080L
#define M_AUTO_RESET                                  0x00002000L
#define M_MANUAL_RESET                                0x00004000L

#define M_IDLE                                                 1L
#define M_LOWEST                                               6L
#define M_BELOW_NORMAL                                         7L
#define M_NORMAL                                               8L
#define M_ABOVE_NORMAL                                         9L
#define M_HIGHEST                                             10L
#define M_TIME_CRITICAL                                       15L

#define M_THREAD_PRIORITY                             1019L
#define M_EVENT_ALLOC                                 1700L
#define M_EVENT_FREE                                  1701L
#define M_EVENT_SEND                                  1702L
#define M_EVENT_CONTROL                               1703L

#define M_DEFAULT                                     0x10000000L
#define M_THREAD_WAIT                                 0x01000000L
#define M_EVENT_WAIT                                  0x20000000L
#define M_EVENT_STATE                                 1706L
#define M_EVENT_SET                                   1707L

#define M_THREAD_ALLOC                                1800L
#define M_THREAD_FREE                                 1801L
#define M_THREAD_CONTROL                              1803L
#define M_THREAD_MODE                                 1804L
#define M_THREAD_IO_MODE                              1805L

/************************************************************************/
/* MsysAlloc()                                                          */
/************************************************************************/
/* System type */
#define M_DEFAULT_HOST                                M_MAKE_DEFAULT_ID(1)
#define M_INTERNAL_DEFAULT_HOST                       M_MAKE_DEFAULT_ID(3)
#define M_DEV0                                        0L
#define M_DEV1                                        1L
#define M_DEV2                                        2L
#define M_DEV3                                        3L
#define M_DEV4                                        4L
#define M_DEV5                                        5L
#define M_DEV6                                        6L
#define M_DEV7                                        7L
#define M_DEV8                                        8L
#define M_DEV9                                        9L
#define M_DEV10                                       10L
#define M_DEV11                                       11L
#define M_DEV12                                       12L
#define M_DEV13                                       13L
#define M_DEV14                                       14L
#define M_DEV15                                       15L
#define M_DEV16                                       16L
#define M_DEV17                                       17L
#define M_DEV18                                       18L
#define M_DEV19                                       19L
#define M_DEV20                                       20L
#define M_DEV21                                       21L
#define M_DEV22                                       22L
#define M_DEV23                                       23L
#define M_DEV24                                       24L
#define M_DEV25                                       25L
#define M_DEV26                                       26L
#define M_DEV27                                       27L
#define M_DEV28                                       28L
#define M_DEV29                                       29L
#define M_DEV30                                       30L
#define M_DEV31                                       31L
#define M_DEV32                                       32L
#define M_DEV33                                       33L
#define M_DEV34                                       34L
#define M_DEV35                                       35L
#define M_DEV36                                       36L
#define M_DEV37                                       37L
#define M_DEV38                                       38L
#define M_DEV39                                       39L
#define M_DEV40                                       40L
#define M_DEV41                                       41L
#define M_DEV42                                       42L
#define M_DEV43                                       43L
#define M_DEV44                                       44L
#define M_DEV45                                       45L
#define M_DEV46                                       46L
#define M_DEV47                                       47L
#define M_DEV48                                       48L
#define M_DEV49                                       49L
#define M_DEV50                                       50L
#define M_DEV51                                       51L
#define M_DEV52                                       52L
#define M_DEV53                                       53L
#define M_DEV54                                       54L
#define M_DEV55                                       55L
#define M_DEV56                                       56L
#define M_DEV57                                       57L
#define M_DEV58                                       58L
#define M_DEV59                                       59L
#define M_DEV60                                       60L
#define M_DEV61                                       61L
#define M_DEV62                                       62L
#define M_DEV63                                       63L
#define M_NODE0                                       0x00010000L
#define M_NODE1                                       0x00020000L
#define M_NODE2                                       0x00040000L
#define M_NODE3                                       0x00080000L
#define M_NODE4                                       0x00100000L
#define M_NODE5                                       0x00200000L
#define M_NODE6                                       0x00400000L
#define M_NODE7                                       0x00800000L
#define M_NODE8                                       0x01000000L
#define M_NODE9                                       0x02000000L
#define M_NODE10                                      0x04000000L
#define M_NODE11                                      0x08000000L
#define M_NODE12                                      0x10000000L
#define M_NODE13                                      0x20000000L
#define M_NODE14                                      0x40000000L
#define M_NODE15                                      0x80000000L
#define M_NODE_BITS                                   (M_NODE0|M_NODE1|M_NODE2|M_NODE3|M_NODE4|M_NODE5|   \
   M_NODE6|M_NODE7|M_NODE8|M_NODE9|M_NODE10|M_NODE11| \
   M_NODE12|M_NODE13|M_NODE14|M_NODE15)

#define M_SYSTEM_TYPE_NONE                            0L
#define M_SYSTEM_HOST_TYPE                            1000L //Needs to be the highest value
#define M_SYSTEM_RADIENT_TYPE                         13L
/* Free for future system type                  from  14L*/
/*                                                to  17L*/
#define M_SYSTEM_CORONA_TYPE                          18L
#define M_SYSTEM_METEOR_II_TYPE                       20L
#define M_SYSTEM_METEOR_II_DIG_TYPE                   21L
#define M_SYSTEM_1394_TYPE                            22L
#define M_SYSTEM_METEOR_II_1394_TYPE                  M_SYSTEM_1394_TYPE
#define M_SYSTEM_MMX_TYPE                             23L
#define M_SYSTEM_SSE_TYPE                             24L
/* Free for future system type                        25L*/
#define M_SYSTEM_SSE2_TYPE                            26L
#define M_SYSTEM_AMD_3DNOW_TYPE                       27L
#define M_SYSTEM_AMD_MMX_EXT_TYPE                     28L
#define M_SYSTEM_AMD_3DNOW_EXT_TYPE                   29L
#define M_SYSTEM_CORONA_II_TYPE                       30L
#define M_SYSTEM_REMOTE_HOST_TYPE                     31L
#define M_SYSTEM_METEOR_II_CL_TYPE                    32L
#define M_SYSTEM_ALTIVEC_TYPE                         33L
/* Free for future system type                  from  34L*/
/*                                                to  35L*/
#define M_SYSTEM_ODYSSEY_TYPE                       2000L //Needs to be the higher than M_SYSTEM_HOST_TYPE
#define M_SYSTEM_HELIOS_TYPE                          36L
#define M_SYSTEM_IRIS_TYPE                            37L
#define M_SYSTEM_CRONOSPLUS_TYPE                      38L
#define M_SYSTEM_MORPHIS_TYPE                         39L
#define M_SYSTEM_ODYSSEY_NATIVE_TYPE                  40L
/* Free for future system type                        41L*/
#define M_SYSTEM_SOLIOS_TYPE                          42L
#define M_SYSTEM_SSE3_TYPE                            43L
#define M_SYSTEM_VIO_TYPE                             44L
// !!!ATTENTION!!! Value used for display             45 - 56 See Below
#define M_SYSTEM_NEXIS_TYPE                           57L
#define M_SYSTEM_GPU_TYPE                             58L
#define M_SYSTEM_MORPHISQXT_TYPE                      59L
#define M_SYSTEM_GIGE_VISION_TYPE                     60L
#define M_SYSTEM_SOLIOS_GIGE_TYPE                     61L
#define M_SYSTEM_SSE4_TYPE                            62L
/* Free for future system type                        63L*/
#define M_SYSTEM_MP_TYPE                              64L
/* Free for future system type                        65L*/
#define M_SYSTEM_CONCORD_1394_TYPE                    M_SYSTEM_1394_TYPE
#define M_SYSTEM_MORPHIS_EVO_TYPE                     66L
#define M_SYSTEM_IRIS_GT_TYPE                         67L
#define M_SYSTEM_ORION_HD_TYPE                        68L
#define M_SYSTEM_NEXIS2_TYPE                          69L


//System Type Value used for display
#define M_SYSTEM_DIRECTX_TYPE                         45L
#define M_SYSTEM_MTX0_TYPE                            46L
// Reserve dib section (10 values)
#define M_SYSTEM_DIB_TYPE_START                       47L
#define M_SYSTEM_DRAWDIB_TYPE                         M_SYSTEM_DIB_TYPE_START+0L    // 47
#define M_SYSTEM_BITBLT_TYPE                          M_SYSTEM_DIB_TYPE_START+1L    // 48
#define M_SYSTEM_STRETCHBLT_TYPE                      M_SYSTEM_DIB_TYPE_START+2L    // 49
#define M_SYSTEM_DIBTODEV_TYPE                        M_SYSTEM_DIB_TYPE_START+3L    // 50
#define M_SYSTEM_STRETCHDIB_TYPE                      M_SYSTEM_DIB_TYPE_START+4L    // 51
#define M_SYSTEM_DIB_TYPE_END                         56L
#define M_IS_SYSTEM_DIB_TYPE(t)     ((t)>=M_SYSTEM_DIB_TYPE_START && (t)<=M_SYSTEM_DIB_TYPE_END)

// System type information flags
#define M_SYSTEM_DISTRIBUTED_FLAG                     0x40000000
#define M_SYSTEM_INFORMATION_FLAGS                    0x40000000
#define M_IS_SYSTEM_DISTRIBUTED(t)                    (((t) & M_SYSTEM_DISTRIBUTED_FLAG) == M_SYSTEM_DISTRIBUTED_FLAG)
#define M_REAL_SYSTEM_TYPE(t)                         ((t) & ~M_SYSTEM_INFORMATION_FLAGS)



/* MsysAlloc() flags  */
#define M_APP_ALLOC_INIT_FLAGS                        0x0FF00000L     
#define M_SYS_ALLOC_INIT_FLAGS                        0x00000FFFL     

#define M_COMPLETE                                    0x00000000L
#define M_PARTIAL                                     0x00000001L
#define M_DISPLAY_INTERNAL_USE                        0x00000002L
#define M_INTERNAL_USE                                0x00000004L
#define M_CREATE_SYSTEM                               0x00000008L
#define M_NO_INTERRUPT                                0x00000010L
#define M_NO_FORCE_IP                                 M_NO_INTERRUPT //For GigEVision
#define M_UPDATE_FIRMWARES                            M_NO_INTERRUPT
#define M_ACCELERATOR_DISABLE                         0x00000020L // For Helios and GPU
#define M_REGISTER_EDITOR                             0x00000040L
#define M_SYS_MD_ID                                   0x00000080L
#define M_NO_FPGA_UPGRADE                             0x20000000L

//do not add defines here

//legacy and board-specific flags
#define M_EXTERNAL_CLK_422                            0x00000100L // For corona
#define M_NO_FIELD_START_INTERRUPT                    0x00000200L // For corona
#define M_SYSTEM_METEOR_II_FLAG                       0x00000400L // For corona
#define M_SYSTEM_CORONA_II_FLAG                       0x00000800L // For corona
#define M_SYSTEM_METEOR_II_CL_FLAG                    0x00000100L // For met2nat
#define M_REGISTER                                    0x00000100L // For MorphisEvo
#define M_SCAN                                        0x00000100L // For GigE(including Solios Gige)
#define M_NO_SCAN                                     0x00000200L // For GigE(including Solios Gige)
#define M_SERVICE                                     0x00000400L // For GigE(including Solios Gige)
#define M_TOLERATE_INVALID_FPGA                       0x00000800L // For Solios, Solios Gige and Radient
#define M_SILENT                                      0x00000100L // For GPU

#define M_DEFAULT                                     0x10000000L


/************************************************************************/
/* MsysInquire() / MsysControl() Types                                  */
/************************************************************************/
#define M_CLIENT_ASCII_MODE                          0x10000
#define M_EXECUTE_BUFFER_HOOKS                        1002L
#define M_TYPE                                        1008L
#define M_NUMBER                                      1009L
#define M_INIT_FLAG                                   1012L
#define M_ATTRIBUTE                                   1013L
#define M_NATIVE_ID                                   1016L
#define M_NATIVE_CONTROL_ID                           1017L
#define M_MAP_VIDEO_MEMORY                            1019L
#define M_DETECT_HOOK_THREAD                          1020L
#define M_MAP_VIDEO_RANGE_A_LA_PIECE                  1021L
#define M_GPU_UPDATE_EFFECTS                          1022L
#define M_LOCATION                                    1048L
#define M_MIL_ID_INTERNAL                             1049L
#define M_UPDATE_PERFORMANCE_COUNTERS                 1050L


/***************************************************************/
/* MsysInquire() Types MIL_ID range start                      */
/***************************************************************/
// Inquire value with MIL_ID type must be in that range : 1100-1199
#define M_SYS_INQUIRE_MIL_ID_START                    1100L
#define M_OWNER_APPLICATION                           1100L
#define M_OWNER_SYSTEM                                1101L
#define M_CURRENT_THREAD_ID                           1103L
#define M_OWNER_NODE_ID                               1104L
#define M_SYS_INQUIRE_MIL_ID_END                      1199L
/***************************************************************/
/* MsysInquire() Types MIL_ID range end                        */
/***************************************************************/


#define M_THREAD_MODE                                 1804L

#define M_SYSTEM_TYPE                                 2000L
#define M_DISPLAY_OUTPUT_NUM                          2001L//2001L was use by M_SYSTEM_TYPE_PTR that is no longer supported.
#define M_INTERNAL_SYSTEM_TYPE                        2002L
//2003L was use by M_DISPLAY_TYPE, that is now in the Display reserved area.
#define M_DIGITIZER_NUM                               2004L
#define M_DIGITIZER_TYPE_NUMBER                       2400L
#define M_DIGITIZER_TYPE                              M_DIGITIZER_TYPE_NUMBER
#define M_PROCESSOR_NUM                               2006L
//2007L was use by M_PROCESSOR_TYPE, that is now in the processor specific section.
#define M_PROCESSING_SYSTEM_TYPE                      2009L
#define M_TUNER_NUM                                   2010L
#define M_TUNER_TYPE                                  2011L
#define M_RGB_MODULE_NUM                              2012L
#define M_RGB_MODULE_TYPE                             2013L
#define M_BOARD_TYPE                                  2014L
#define M_BOARD_REVISION                              2015L
#define M_WIN_MODE                                    2017L
//2018L was use by M_DUAL_SCREEN_MODE, that is now in the Display reserved area.
//2019L was use by M_UNDERLAY_SURFACE_AVAILABLE, that is now in the Display reserved area.
#define M_MAX_TILE_SIZE                               2021L
#define M_MAX_TILE_SIZE_X                             2022L
#define M_MAX_TILE_SIZE_Y                             2023L
#define M_LOW_LEVEL_SYSTEM_ID                         2024L
#define M_NATIVE_THREAD_ID                            2026L
#define M_NATIVE_MODE_ENTER                           2027L
#define M_NATIVE_MODE_LEAVE                           2028L
#define M_PHYSICAL_ADDRESS_UNDERLAY                   2029L
//2030L was use by M_PHYSICAL_ADDRESS_VGA, that is now in the Display reserved area.
#define M_PSEUDO_LIVE_GRAB_ON_MGA                     2031L
//2032 was used by M_PSEUDO_LIVE_GRAB, that is no longer supported.
//2033 was used by M_FORCE_PSEUDO_IN_NON_UNDERLAY_DISPLAYS, that is no longer supported
#define M_LIVE_GRAB                                   2034L
#define M_LIVE_GRAB_WHEN_DISPLAY_DOES_NOT_MATCH       2035L
#define M_ADD_BUFFER_INFO                             2036L
#define M_REMOVE_BUFFER_INFO                          2037L
#define M_GRAB_CONTINUOUS_END_TRIGGER                 2038L
//2038 M_LIVE_GRAB_END_TRIGGER is now in OldDefines
//2040 was used by M_STOP_LIVE_GRAB_WHEN_MENU, that is no longer supported
//2041 was used by M_STOP_LIVE_GRAB_WHEN_INACTIVE, that is no longer supported
//2042 was used by M_STOP_LIVE_GRAB_WHEN_DISABLED, that is no longer supported
#define M_GRAB_BY_DISPLAY_CAPTURE                     2043L
#define M_ALLOC_BUF_RGB888_AS_RGB555                  2044L
#define M_RGB555_BUFFER_ALLOCATION                    2045L
//2046 was used by M_LAST_GRAB_IN_TRUE_BUFFER, that is now in the Digitizer reserved area.
#define M_NO_GRAB_WHEN_NO_INPUT_SIGNAL                2047L
#define M_PCI_LATENCY                                 2048L
#define M_FAST_PCI_TO_MEM                             2049L
#define M_DCF_SUPPORTED                               2050L
#define M_DMA_ENABLE                                  2051L
#define M_DMA_DISABLE                                 2052L
#define M_DIB_ONLY                                    2053L
#define M_DIB_OR_DDRAW                                2054L
#define M_FLIP_ONLY                                   2055L
//2057L was use by M_PRIMARY_DDRAW_SURFACE_MEM_PTR, that is now in the Display reserved area.
//2058L was use by M_PRIMARY_DDRAW_SURFACE_PITCH_BYTE, that is now in the Display reserved area.
//2059L was use by M_PRIMARY_DDRAW_SURFACE_SIZE_X, that is now in the Display reserved area.
//2060L was use by M_PRIMARY_DDRAW_SURFACE_SIZE_Y, that is now in the Display reserved area.
//2061L was use by M_PRIMARY_DDRAW_SURFACE_SIZE_BITS, that is now in the Display reserved area.
#define M_INTERNAL_FORMAT_SIZE                        2062L
#define M_INTERNAL_FORMAT_ENUMERATION                 2063L
#define M_INTERNAL_FORMAT_CHECK                       2064L
//2065L was use by M_DDRAW_AVAILABLE, that is now in the Display reserved area.
#define M_BOARD_CODE                                  2066L
#define M_LIVE_GRAB_DDRAW                             2067L
#define M_THREAD_CONTEXT_PTR                          2068L
#define M_PSEUDO_LIVE_GRAB_NB_FRAMES                  2069L
#define M_PSEUDO_LIVE_GRAB_NB_FIELDS                  2070L
//2071L was use by M_DISPLAY_DOUBLE_BUFFERING, that is now in the Display reserved area.
#define M_PSEUDO_LIVE_GRAB_TIME                       2072L
#define M_PCI_BRIDGE_LATENCY                          2073L
#define M_PSEUDO_LIVE_GRAB_WITH_DDRAW                 2074L
#define M_MULTI_DISP_IN_UNDERLAY                      2075L
#define M_MULTI_DISP_FOR_GRAB                         2076L
#define M_TIMEOUT                                     2077L
#define M_AUTO_FLIP_FOR_TRUE_COLOR                    2078L
#define M_PCI_BRIDGE_HOST_WRITE_POSTING               2079L
#define M_FAST_MEM_TO_VGA                             2080L
#define M_ERROR_ASYNCHRONOUS_LOG                      2081L
#define M_LIVE_GRAB_WHEN_NOT_VISIBLE                  2082L
#define M_OVERLAPPED_STRUC                            2085L
#define M_PHYSICAL_ADDRESS_VIA                        2086L
#define M_PCI_MGA_ID                                  2087L
#define M_PCI_VIA_ID                                  2088L
#define M_PCI_BRIDGE_ID                               2089L
#define M_NATIVE_SYSTEM_NUMBER                        2090L
#define M_NATIVE_NODE_NUMBER                          2091L
#define M_JTAG_CHAIN                                  2092L

#define M_CUSTOMER_PRODUCT_ID                         2093L
#define M_UNDERLAY_MEM_SIZE                           2094L
#define M_OVERLAY_MEM_SIZE                            2095L
#define M_VIA_MEM_SIZE                                2096L
#define M_ERROR_CLEAR                                 2099L
#define M_SYS_DEBUG_BUFFER_SIZE                       2100L  // internal use only
#define M_SYS_DEBUG_BUFFER_ID                         2101L  // internal use only
#define M_DEBUG_BUFFER_CLEAR                          M_SYS_DEBUG_BUFFER_SIZE
#define M_DEBUG_BUFFER_TO_FILE                        M_SYS_DEBUG_BUFFER_ID
#define M_USE_NOA                                     2102L
#define M_USE_ACCELERATOR                             M_USE_NOA
#define M_COMPRESSION_MODULE_PRESENT                  2104L
#define M_DIGITAL_MODULE_PRESENT                      2105L
#define M_INTERRUPT_NEW_TECHNIQUE                     2106L
#define M_INTERRUPT_NEW_TECHNIQUE_STAT                2107L
#define M_INTERRUPT_NEW_TECHNIQUE_QUEUE               2108L
#define M_INTERRUPT_MASTER_SWITCH                     2109L
#define M_BUS_MASTER_COPY_TO_HOST                     2110L
#define M_BUS_MASTER_COPY_FROM_HOST                   2111L
#define M_MEMORY_OFF_SCREEN_AVAILABLE                 2112L
#define M_BUFCOPY_SUPPORTED                           2113L
#define M_COMPRESSION_SUPPORTED                       2114L
#define M_UART_BUFFER_INIT                            2115L  // internal use only
#define M_UART_BUFFER_FREE                            2116L  // internal use only
#define M_CLL_UART_PARITY                             2117L  // internal use only
#define M_CLL_UART_IRQ_CALL                           2118L  // internal use only
#define M_SET_DUAL_SCREEN_MODE                        2119L  // internal use only
#define M_RESET_GRAB_INFO                             2120L  // internal use only
#define M_COMPRESSION_BOARD_TYPE                      2121L
#define M_COMPRESSION_BOARD_RESET                     2122L
#define M_COMPACT_PCI_PRESENT                         2123L
#define M_TEST_CACHE_COHERENCE                        2124L
#define M_HARDWARE_COMPRESSION                        2130L
#define M_HARDWARE_DECOMPRESSION                      2131L
#define M_UART_PRESENT                                2132L
#define M_PC104_PRESENT                               2133L
#define M_HARDWARE_COMPRESSION_TYPE                   2134L
//2135L was use by M_USE_DDRAW_UNDERLAY, that is now in the AppInquire display reserved area.
//2136L was use by M_DDRAW_UNDERLAY_SUPPORTED, that is now in the Display reserved area.
#define M_DDRAW_UNDERLAY_FORMAT                       2137L
#define M_ENCODER_PRESENT                             2138L
#define M_COMPRESSION_INTERNAL_BUFFER_SIZE            2139L
//2140L was use by M_PRIMARY_DDRAW_SURFACE_FORMAT, that is now in the Display reserved area.
//2141L was use by M_LIVE_GRAB_NO_TEARING, that is no longer supported
//2153L was use by M_DDRAW_UNDERLAY_FORMAT_SUPPORTED, that is now in the Display reserved area.
#define M_BIOS_REVISION                               2154L
#define M_FPGA_REVISION                               2155L
#define M_FIRMWARE_REVISION                           M_FPGA_REVISION
#define M_INTERNAL_CAMERA_STRUCT_PTR                  2156L
#define M_INTERNAL_CAMERA_STRUCT_SIZE                 2157L
#define M_INTERNAL_DRV_DEBUG                          2158L  // Internal use only
#define M_SUPPORTED_INTERFACE                         2159L
//2160L was use by M_USE_SSE2, that is now in the processor specific section.
//2161L was use by M_USE_AMD_3DNOW, that is now in the processor specific section.
//2162L was use by M_USE_AMD_MMX_EXTENSION, that is now in the processor specific section.
//2163L was use by M_USE_AMD_3DNOW_EXTENSION, that is now in the processor specific section.
//2164L was use by M_CPU_VENDOR_NAME, that is now in the processor specific section.
//2165L was use by M_CPU_FAMILY_NUMBER, that is now in the processor specific section.
//2166L was use by M_CPU_MODEL_NUMBER, that is now in the processor specific section.
//2167L was use by M_CPU_STEPPING_NUMBER, that is now in the processor specific section.
//2168L was use by M_CPU_SERIAL_NUMBER, that is now in the processor specific section.
#define M_SYSTEM_NUM                                  2169L
#define M_ASSOCIATED_VGA_SYSTEM_ID                    2170L  // internal use only
#define M_ASSOCIATED_VGA_DEVICE                       2171L
#define M_GPU_IS_NON_POWER_OF_2_FULLY_SUPPORTED       2177L
#define M_GPU_IS_TEXTURE_BORDER_SUPPORTED             2178L
#define M_GPU_IS_16_BIT_PRECISE                       2179L
#define M_GPU_SERIES                                  2180L
#define M_UNICODE_SUPPORT                             2181L
#define M_BOARD_SUB_REVISION                          2200L
#define M_USER_BIT_CHANGE                             2244L
#define M_USER_BIT_CHANGE_HANDLER_PTR                 2245L
/* Reserve next 18 values                       from  2246L*/
/*                                             to     2264L*/
#define M_USER_BIT_CHANGE_HANDLER_USER_PTR            2266L
/* Reserve next 19 values                       from  2267L*/
/*                                             to     2285L*/
#define M_1394_FORCE_BUS_RESET                        2286L
#define M_1394_GENERATION_COUNT                       2287L
//2288L was use by M_PHYSICAL_SIZE_VGA, that is now in the Display reserved area.
#define M_CURRENTLY_USED_CAMERA                       2289L
#define M_DIGITIZER_MODE                              2290L
#define M_MSG_BUFFER_SIZE                             2291L
#define M_MSG_BUFFER_PHYSICAL_ADDRESS                 2292L
#define M_MSG_LOG_MODE                                2293L
#define M_DEFAULT_PITCH_BYTE                          2294L
#define M_SYS_USE_WINDOWED_CLASS                      2295L
//2296L was used by M_SYSTEM_LICENSE_MODULES that is now equal to M_LICENSE_MODULES. See MappInquire() section.
//2297L was used by M_DUAL_HEAD, which is now a display specific app section (M_APP_DISPLAY_START)
//2298L was used by M_MULTI_MONITOR, which is now a display specific app section (M_APP_DISPLAY_START)
#define M_SUBSYSTEM_ID                                2299L // internal use only
#define M_USE_DDRAW                                   2300L
#define M_PREFERRED_DISPLAY_SYSTEM                    2301L
#define M_USAGE_METER                                 2302L
#define M_GRAB_USAGE                                  2303L
#define M_ACCELERATOR_USAGE                           2304L
#define M_DMA_USAGE                                   2305L
#define M_DMA_WRITE_USAGE                             M_DMA_USAGE
#define M_UTILITY_USAGE                               2306L
#define M_MAX_UNIT_IDLE_TIME                          2307L
#define M_JPEG2000_USAGE                              2308L
#define M_DMA_READ_USAGE                              2309L

#define M_BUFFER_DEFAULT_LOCATION                     2310L
#define M_ON_BOARD_NATIVE_THREAD_ID                   2314L
#define M_COPY_BY_DRIVER                              2315L
#define M_ASSOCIATED_VIDEO_DEVICE_INDEX               2316L

#define M_NATIVE_CLUSTER_NUMBER                       M_NATIVE_SYSTEM_NUMBER
#define M_CPU_SPEED                                   2320L
#define M_ACCELERATOR_SPEED                           2321L
#define M_ACCELERATOR_PRESENT                         2322L
#define M_MEMORY_SIZE                                 2323L
#define M_MEMORY_FREE                                 2324L
#define M_FAST_MEMORY_FREE                            2325L
#define M_SHARED_MEMORY_FREE                          2326L
#define M_HEAP_SIZE                                   2327L
#define M_HEAP_FREE                                   2328L
#define M_SIZE_X_CREATE_RESTRICTION                   2329L
#define M_SHARED_MEMORY_SIZE                          2330L
#define M_DIGITIZER_NUM_ALLOCATED                     2331L
/* Reserve next 4 values                       from   2232L*/
/*                                             to     2235L*/
/* Next 4 values are used to specify device number of the digitizer.*/
#define M_SERIAL_DEVICE_PORT_NUMBERS                  2336L
#define M_FIRMWARE_UPDATE                             2340L
#define M_CURRENTLY_IN_HOOK                           2341L
#define M_FIRMWARE_REVISION_GRAB                      2342L
#define M_FIRMWARE_REVISION_IO                        2343L
#define M_FIRMWARE_REVISION_PROCESSING                2344L
#define M_FIRMWARE_REVISION_JPEG2000                  M_FIRMWARE_REVISION_PROCESSING
#define M_FIRMWARE_BUILDDATE                          2345L
#define M_FIRMWARE_BUILDDATE_GRAB                     2346L
#define M_FIRMWARE_BUILDDATE_IO                       2347L
#define M_FIRMWARE_BUILDDATE_PROCESSING               2348L
#define M_FIRMWARE_BUILDDATE_JPEG2000                 M_FIRMWARE_BUILDDATE_PROCESSING
#define M_MPEG4_USAGE                                 2349L

#define M_MEMORY_SIZE_BANK_0                          2350L
#define M_MEMORY_SIZE_BANK_1                          2351L
#define M_MEMORY_SIZE_BANK_2                          2352L
#define M_MEMORY_SIZE_BANK_3                          2353L

#define M_MEMORY_FREE_BANK_0                          2354L
#define M_MEMORY_FREE_BANK_1                          2355L
#define M_MEMORY_FREE_BANK_2                          2356L
#define M_MEMORY_FREE_BANK_3                          2357L

#define M_SYSTEM_NUM_ALLOCATED                        2360L
#define M_COM_PORT_PCI_BUS_NB                         2361L
#define M_JPEG2000_COMPATIBILITY_CHECKING             2362L
#define M_SET_BACK_TO_ZERO                            2363L
#define M_PROCESSING_FPGA_FAN_RPM                     2364L

// WATCHDOG
#define M_WATCHDOG_MODE                               2370
#define M_WATCHDOG_TIMEOUT                            2371
#define M_WATCHDOG_WARNING                            2372
#define M_WATCHDOG_REBOOT_TIMEOUT                     2373
#define M_WATCHDOG_RESET                              2374
#define M_WATCHDOG_RESET_COUNTER                      2375
#define M_WATCHDOG_WARNING_TIME                       2376
#define M_WATCHDOG_PRESENT                            2378
#define M_OK_TO_FREE                                  2379
// CRYPTOGRAPHY
#define M_CRYPTOGRAPHY_MODE                           2380L
#define M_CRYPTOGRAPHY_P_KEY                          2381L
#define M_CRYPTOGRAPHY_Q_KEY                          2382L
#define M_CRYPTOGRAPHY_PUBLIC_KEY                     2383L
#define M_CRYPTOGRAPHY_PRIVATE_KEY                    2384L
#define M_CRYPTOGRAPHY_RSA                            2385L
#define M_CRYPTOGRAPHY_HMAC_KEY                       2386L
// CRYPTOGRAPHY support old defines
#define M_CRYPTO_MODE                                 M_CRYPTOGRAPHY_MODE
#define M_CRYPTO_P_KEY                                M_CRYPTOGRAPHY_P_KEY
#define M_CRYPTO_Q_KEY                                M_CRYPTOGRAPHY_Q_KEY
#define M_CRYPTO_PUBLIC_KEY                           M_CRYPTOGRAPHY_PUBLIC_KEY
#define M_CRYPTO_PRIVATE_KEY                          M_CRYPTOGRAPHY_PRIVATE_KEY
#define M_CRYPTO_RSA                                  M_CRYPTOGRAPHY_RSA

#define M_DIGITIZER_TYPE_NUMBER                       2400L
/* Reserve next 31 values                      from   2400*/
/* for M_DIGITIZER_TYPE+M_DEVn inquire         to     2432*/


#define M_AGP_TO_PCI_TRANSFER                         2433L
#define M_TRANSFER_PRIORITY                           2434L
#define M_THREAD_CANCEL                               2435L
#define M_THREAD_HALT                                 2436L
#define M_NUMBER_OF_GRAB_BLOCKS                       2437L
/* Reserve next 4 values                        from  2438L*/
/*                                              to    2441L*/
#define M_GRAB_BLOCK_FACTOR                           2442L
/* Reserve next 4 values                        from  2443L*/
/*                                              to    2446L*/
#define M_MODIFIED_BUFFER_HOOK_MODE                   2447L
#define M_GC_CAMERA_SELECT                            2448L

#define M_CAMERA_POWER                                2560  /* 0xA00 */
/* Reserve next 15 values                       from  2560L */
/*                                              to    2576  */
#define M_1394_POWER                                  M_CAMERA_POWER

#define METEOR_II_1394B_BIT_MASK_POWER                 0x7
#define M_BUS_MASTER_PCI_LOCATION                     2580L
/* Reserve next 8 values                       from   2580L*/
/*                                             to     2587L*/
#define M_PCIE_NUMBER_OF_LANES                        2588L
#define M_BUS_MASTER_REQUESTER_ID                     2590L
/* Reserve next 8 values                       from   2580L*/
/*                                             to     2587L*/

#define M_PROCESSING_UNIT_START                       0L
#define M_PROCESSING_UNIT_END                         299L
#define M_PROCESSING_FPGA_USAGE                       2600L
/* Reserve next 300 values                     from   2600L*/
/*                                             to     2899L*/
#define M_DMA_WRITE_UNIT0_USAGE                       2900L
#define M_DMA_WRITE_UNIT1_USAGE                       2901L
#define M_DMA_WRITE_UNIT2_USAGE                       2902L
#define M_DMA_WRITE_UNIT3_USAGE                       2903L

// MPEG4 ENCODER
#define M_STREAM(value)                               ((value + 1) & 0x003f)
#define M_STREAM_EXTRACT_STREAM(value)                ((value & 0x003f) - 1)
#define M_STREAM_EXTRACT_TYPE(value)                  (value & ~0x003f)

// NOTE: For the following defines, the 6 LSBs must be zeros
#define M_STREAM_CONTROL                              3264L // 0x00000CC0
#define M_STREAM_BIT_RATE_MODE                        3328L // 0x00000D00
#define M_STREAM_BIT_RATE                             3392L // 0x00000D40
#define M_STREAM_Q_PARAMETER                          3456L // 0x00000D80
#define M_STREAM_QUALITY                              3520L // 0x00000DC0
#define M_STREAM_BIT_RATE_MAX                         3584L // 0x00000E00
#define M_STREAM_GROUP_OF_PICTURE_SIZE                3648L // 0x00000E40
#define M_STREAM_FRAME_RATE                           3712L // 0x00000E80
#define M_STREAM_FRAME_PERIOD                         3776L // 0x00000EC0
#define M_STREAM_ENCODING_MODE                        3840L // 0x00000F00
// Reserved 3904L to 3967L

#define M_DRIVER_COMPILATION_TYPE                     4362L
#define M_USER_BIT_INQUIRE_START                      4363L
#define M_USER_BIT_COUNT                              4364L
#define M_USER_BIT_OPTOMODULE                         4365L
#define M_USER_BIT_INQUIRE_END                        4366L
#define M_FORCE_PITCH_BYTE_MULTIPLE                   4367L
#define M_ODYSSEY_BEHAVIOUR                           4368L

//EEPROM-related defines
#define M_EEPROM_SIZE                                 4369L
#define M_EEPROM_L_OFFSET                             4370L
#define M_EEPROM_L_SIZE                               4371L

#define M_BOARD_TYPE_STRING                           4372L
#define M_BOARD_TYPE_STRING_SIZE                      4373L

#define M_SUPPORT_START_NO                            4374L
/*Reserve values between M_SUPPORT_START_NO
                          and M_SUPPORT_END_NO*/
#define M_DISPLAY_SUPPORT                             4374L
#define M_MULTITHREAD_SUPPORT                         4375L
#define M_ASYNCHRONOUS_CALL_SUPPORT                   4376L
#define M_COLOR_BUFFERS_PROCESSING_SUPPORT            4377L
#define M_64BIT_RESULT_BUFFERS_SUPPORT                4378L
#define M_MILGRABC_VERSION                            4385L    // Also defined as a MdigInquire
#define M_NETWORKED                                   4386L
#define M_ALL_DEV_ARE_EQUIVALENT                      4387L
#define M_MP_SUPPORT                                  4388L
#define M_REMOTE_MAPPING_SUPPORT                      4389L
#define M_SUPPORT_NEW_CONTROL_FEATURE                 4390L
#define M_GPU_NO_TEARING_SUPPORT                      4391L
#define M_GPU_BILINEAR_SUPPORT                        4392L
#define M_SUPPORT_END_NO                              4439L

#define M_SUPPORT_START_YES                           4440L
/*Reserve values between M_SUPPORT_START_YES and M_SUPPORT_END_YES*/
#define M_CAN_GRAB                                    4441L
#define M_ALLOC_WITH_FORCED_PITCH_SUPPORT             4442L
#define M_WINDOW_ANNOTATIONS_ENABLED                  4443L
#define M_SUPPORT_END_YES                             4500L
#define M_SYS_DISPLAY_START                           4501L
//This section is reserved for displays and defines are in mildisplay.h
#define M_SYS_DISPLAY_END                             4600L
#define M_PERFORMANCE_LOGS                            4601L
#define M_INTERRUPT_LATENCY                           4602L
#define M_ONL_NODE_ID                                 4603L
#define M_DEV_MIN_HEAP_SIZE                           4604L
#define M_DIGITIZER_INTERNAL_BUFFERS_NUM              4605L
#define M_CHECK_ERROR                                 4606L

// Map of UART defines, used by Mdig and Msys
#define M_UART_START                                  4701L
#define M_UART_PARITY                                 4701L
#define M_UART_STOP_BITS                              4702L
#define M_UART_DATA_LENGTH                            4703L
#define M_UART_SPEED                                  4704L
#define M_UART_WRITE_CHAR                             4705L
#define M_UART_READ_CHAR                              4706L
#define M_UART_DATA_PENDING                           4707L
#define M_UART_WRITE_STRING                           4708L
#define M_UART_WRITE_STRING_LENGTH                    4709L
#define M_UART_READ_STRING                            4710L
#define M_UART_READ_STRING_LENGTH                     4711L
#define M_UART_READ_STRING_MAXIMUM_LENGTH             4712L
#define M_UART_STRING_DELIMITER                       4713L
#define M_UART_TIMEOUT                                4714L
#define M_UART_ERROR_MESSAGE                          4715L // internal use only
#define M_UART_OUTPUT                                 4716L
#define M_UART_THREAD_HANDLE                          4717L
#define M_UART_THREAD_ID                              4718L
#define M_UART_DATA_RECEIVED_HANDLER_PTR              4719L
#define M_UART_DATA_RECEIVED_HANDLER_USER_PTR         4720L
#define M_UART_INTERFACE_TYPE                         4721L
#define M_UART_BYTES_WRITTEN                          4722L
#define M_UART_BYTES_READ                             4723L
#define M_COM_PORT_NUMBER                             4724L
#define M_UART_FREE                                   4725L
#define M_UART_END                                    4725L
#define M_UART_NB_MASK_SHIFT                          16L
#define M_MAX_UART_NB                                 0x000000ff
#define M_UART_NB(n)                                  ((unsigned long)((n & M_MAX_UART_NB) << M_UART_NB_MASK_SHIFT))
#define M_UART_CONTROL_VALUE(n)                       (n & (~(M_MAX_UART_NB << M_UART_NB_MASK_SHIFT)))
#define M_IS_IN_UART_RANGE(Type)                      (((M_UART_CONTROL_VALUE((Type)) >= M_UART_START) && \
                                                        (M_UART_CONTROL_VALUE((Type)) <= M_UART_END)))

#define M_FPGA_CONTEXT_SHARED_API                     4800L
#define M_DRIVER_FPGA_CONTEXT_SIZE                    4801L
#define M_PROCESSING_MODULE_COUNT                     4802L
//Unused                                              4803L
#define M_PROCESSING_FPGA_REGISTER_RANGE              4804L
#define M_PF_CLOCK_FREQUENCY                          4805L
#define M_PF_MEMORY_SIZE                              4806L
#define M_IS_DISTRIBUTED_SYSTEM_ON_LOCAL_HOST         4807L
#define M_NETWORK_PORT                                4808L
#define M_NETWORK_HANDLE                              4809L // internal use only

#define M_GC_DISCOVER_DEVICES                         4810L
#define M_NUM_CAMERA_PRESENT                          4811L
// Reserved                                           4812L
#define M_HFPGA_REGISTER_RANGE                        4813L
#define M_FPGA_MEMORY_ARBITER_GRANT                   4814L

#define M_SYS_AUX_START                               6700L
#define M_DUMMY_SYS_INQUIRE                           6701L
#define M_USER_BIT_IN_ACTIVE_LEVEL                    6702L
#define M_USER_BIT_PERFORMANCE_LOGS                   6703L
#define M_SYS_AUX_END                                 7200L

#define M_SYS_INQUIRE_SIZEOF_DOUBLE_START             7300L
// Inquire value with a size of double, must be in that range : 7300-7399


#define M_TEMPERATURE_FPGA                            7301L
#define M_TEMPERATURE_FPGA_MAX_MEASURED               7302L
#define M_VOLTAGE_FGPA_VCCINT                         7303L
#define M_VOLTAGE_FPGA_VCCINT_MIN_MEASURED            7304L
#define M_VOLTAGE_FPGA_VCCINT_MAX_MEASURED            7305L
#define M_VOLTAGE_FPGA_VCCAUX                         7306L
#define M_VOLTAGE_FPGA_VCCAUX_MIN_MEASURED            7307L
#define M_VOLTAGE_FPGA_VCCAUX_MAX_MEASURED            7308L
#define M_TEMPERATURE_FPGA_PROCESSING                 7309L
#define M_TEMPERATURE_FPGA_PROCESSING_MAX_MEASURED    7310L
#define M_GC_GENICAM_VERSION                          7311L


#define M_SYS_INQUIRE_SIZEOF_DOUBLE_END               7399L

#define M_SYS_INQUIRE_SIZEOF_INT64_START              7400L
// Inquire value with a size of 64 bit, must be in that range : 7400-7499
#define M_PROCESSING_FPGA_REGISTER_PHYSICAL_ADDRESS   7401L
#define M_HFPGA_REGISTER_PHYSICAL_ADDRESS             7402L
#define M_SYS_INQUIRE_SIZEOF_INT64_END                7499L

#define M_SYS_INQUIRE_UNKNOWN_SIZEOF_START            7500L
// Inquire value with unknown size of,
//            and require a user array, must be in that range : 7500-7599
#define M_LOGICAL_TO_PHYSICAL_ADDRESS                 7501L
/* Reserve value                                      7502L*/
#define M_SYS_INQUIRE_UNKNOWN_SIZEOF_END              7599L

// Inquire value with string type must be in that range : 7700-7729
#define M_INQUIRE_STRING_SIZE_OFFSET                     30L
#define M_SYS_INQUIRE_STRING_START                       7700L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_GPU_TYPE                                    ((M_SYS_INQUIRE_STRING_START+0L)|M_CLIENT_ASCII_MODE)  //7700
   #define M_SYSTEM_DESCRIPTOR                           ((M_SYS_INQUIRE_STRING_START+1L)|M_CLIENT_ASCII_MODE)  //7701
   #define M_SYSTEM_NAME                                 ((M_SYS_INQUIRE_STRING_START+2L)|M_CLIENT_ASCII_MODE)  //7702
   #define M_SERIAL_NUMBER                               (7703L|M_CLIENT_ASCII_MODE)  //7703
   #define M_NETWORK_ADDRESS                              ((M_SYS_INQUIRE_STRING_START+4L)|M_CLIENT_ASCII_MODE)//7704
   #define M_SYSTEM_TYPE_STRING                          ((M_SYS_INQUIRE_STRING_START+5L)|M_CLIENT_ASCII_MODE) //7705
   #define M_TRANSPORT_PROTOCOL                          ((M_SYS_INQUIRE_STRING_START+6L)|M_CLIENT_ASCII_MODE) //7706
   #define M_GC_GENICAM_UI                               ((M_SYS_INQUIRE_STRING_START+7L)|M_CLIENT_ASCII_MODE) //7707
   #define M_DEBUG_BUFFER_PATH                           ((M_SYS_INQUIRE_STRING_START+8L)|M_CLIENT_ASCII_MODE) //7708
   /*Reserve next values      from                       ((M_SYS_INQUIRE_STRING_START+9L)|M_CLIENT_ASCII_MODE) //7709 */
   /*                         to                         ((M_SYS_INQUIRE_STRING_START+29L)|M_CLIENT_ASCII_MODE)//7729 */
#else
   #define M_GPU_TYPE                                    (M_SYS_INQUIRE_STRING_START+0L)  //7700
   #define M_SYSTEM_DESCRIPTOR                           (M_SYS_INQUIRE_STRING_START+1L)  //7701
   #define M_SYSTEM_NAME                                 (M_SYS_INQUIRE_STRING_START+2L)  //7702
   #define M_SERIAL_NUMBER                               7703L
   #define M_NETWORK_ADDRESS                             (M_SYS_INQUIRE_STRING_START+4L)  //7704
   #define M_SYSTEM_TYPE_STRING                          (M_SYS_INQUIRE_STRING_START+5L)  //7705
   #define M_TRANSPORT_PROTOCOL                          (M_SYS_INQUIRE_STRING_START+6L)  //7706
   #define M_GC_GENICAM_UI                               (M_SYS_INQUIRE_STRING_START+7L)  //7707
   #define M_DEBUG_BUFFER_PATH                           (M_SYS_INQUIRE_STRING_START+8L)  //7708
   /*Reserve next values      from                       (M_SYS_INQUIRE_STRING_START+9L)  //7709 */
   /*                         to                         (M_SYS_INQUIRE_STRING_START+29L) //7729 */
#endif
#define M_SYS_INQUIRE_STRING_END                         (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1) //7729L


// 7730-7759 string size offsets
// Use M_INQUIRE_STRING_SIZE_OFFSET + inquire type
#define M_GPU_TYPE_SIZE                               (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+0)    //7730L
#define M_SYSTEM_DESCRIPTOR_SIZE                      (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+1)    //7731L
#define M_SYSTEM_NAME_INQUIRE_SIZE                    (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+2)    //7732L TBA: MIL should support this inquire
#define M_SERIAL_NUMBER_SIZE                          7733L
#define M_NETWORK_ADDRESS_SIZE                         (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+4)   //7734
#define M_SYSTEM_TYPE_STRING_SIZE                     (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+5)    //7735
#define M_TRANSPORT_PROTOCOL_SIZE                     (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+6)    //7736L */ 
#define M_GC_GENICAM_UI_SIZE                          (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+7)    //7737L */ 
#define M_DEBUG_BUFFER_PATH_SIZE                      (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+8)    //7738L */ 
/*Reserve next values      from                       (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+8)    //7736L */
/*                         to                         (M_SYS_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+29)   //7759L */

#define M_CACHE_FLUSH                                 8192L
/* Reserve next values     from    M_SYS_DISPLAY_RANGE2_START    8500L 
                           to      M_SYS_DISPLAY_RANGE2_END      8699L 
  Display, reserved area in mildisplay.h 
  (this is the second range we have to use, 4501L-4600L is also reserved for the displays)
*/

#define M_APP_INQUIRE_SYS_START                       15000L
/*Reserve values between 5000 and 6699 for AppInquires.
Needed for remote systems                                 */
#define M_APP_INQUIRE_SYS_END                         20000L



#define M_ALLOCATION_OVERSCAN                         0x00008000L    //32768 //This flag is also use as MbufControl/Inquire type and as buffer attribute.
#define M_FAST_OVERSCAN_BUFFER                        M_ALLOCATION_OVERSCAN
#define M_ALLOCATION_OVERSCAN_SIZE                    0x00008001L   //32769

#define M_CLIENT_ASCII_MODE                          0x10000        //65536



///////////////////////////////////////////////////////////////////////////////////////////////////
//Processor specific and optimization MsysInquire/MsysControl type.
//The range between 0x00002800 to 0x00002FFF (10240L to 12287).
///////////////////////////////////////////////////////////////////////////////////////////////////
#define M_CPU_FLAG_RANGE                              0x00002800L    //10240
#define M_CPU_FLAG_RANGE_END                          0x00002FFFL    //12287
#define M_IS_IN_CPU_FLAG_RANGE(n)                     ((n >= M_CPU_FLAG_RANGE) && (n <= M_CPU_FLAG_RANGE_END))

#define M_PROCESSOR_TYPE                              0x00002800L
#define M_INTEL_X86                                   0x00002801L
#define M_INTEL_IA64                                  0x00002802L
#define M_PPC_7400                                    0x00002803L
#define M_AMD_64                                      0x00002804L
//Reserved for future processor type                  0x00002805L
//                                                 to 0x0000281FL
#define M_UNKNOWN_TYPE                                0x00002820L

#define M_USE_FULL_OPTIMIZATION                       0x00002821L
#define M_USE_SIMD                                    0x00002821L

//Intel x86 specific
#define M_USE_MMX                                     0x00002822L
#define M_USE_SSE_INT                                 0x00002823L
#define M_USE_SSE                                     0x00002824L
#define M_USE_SSE2_INT                                0x00002825L
#define M_USE_SSE2                                    0x00002826L
#define M_USE_SSE3                                    0x00002827L
#define M_USE_SSE4_1                                  0x00002828L
#define M_USE_SSE4_2                                  0x00002829L
//Reserved for future Intel instruction set expension 0x0000282AL
//                                                 to 0x00002830L
#define M_USE_AMD_3DNOW                               0x00002831L
#define M_USE_AMD_MMX_EXTENSION                       0x00002832L
#define M_USE_AMD_3DNOW_EXTENSION                     0x00002833L
//Reserved for future AMD instruction set expension   0x00002834L
//                                                 to 0x00002840L
#define M_CPU_FAMILY_NUMBER                           0x00002842L
#define M_CPU_MODEL_NUMBER                            0x00002843L
#define M_CPU_STEPPING_NUMBER                         0x00002844L
#define M_CPU_SERIAL_NUMBER                           0x00002845L
#define M_CPU_SIMD_BITFIELD                           0x00002846L
#if M_MIL_USE_LINUX
#  define M_CPU_FREQUENCY                             0x00002847L
#endif

//Reserve for sysinquire string types
#define M_SYSINQ_CPU_STRING_START                        0x00002848L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_CPU_VENDOR_NAME                             (0x00002848L|M_CLIENT_ASCII_MODE)
   /*Reserve next values      from                       (0x00002849L|M_CLIENT_ASCII_MODE)*/
   /*                         to                         (0x00002865L|M_CLIENT_ASCII_MODE)*/
#else
   #define M_CPU_VENDOR_NAME                             0x00002848L
   /*Reserve next values      from                       0x00002849L*/
   /*                         to                         0x00002865L*/
#endif
#define M_SYSINQ_CPU_STRING_END                          (M_SYSINQ_CPU_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1)

//Reserve 0x2866-0x2883 for sysinquire string type size
//Use M_INQUIRE_STRING_SIZE_OFFSET + inquire type
#define M_CPU_VENDOR_NAME_INQUIRE_SIZE                   (M_SYSINQ_CPU_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+0) //TBA: MIL should support this inquire
/*Reserve next values      from                          (M_SYSINQ_CPU_STRING_END+2L)*/
/*                         to                            (M_SYSINQ_CPU_STRING_END+30L)*/

//Reseved for future string CPU specific inquire      0x00002848L
//                                                 to 0x00002865L
//Reseved for future string size CPU specific inquire 0x00002866L
//                                                 to 0x00002883L
#define M_USE_ALTIVEC                                 0x00002884L
//Reserved for future PPC instruction set expension   0x00002885L
//                                                 to 0x00002900L

#define M_CPU_SUPPORT_RDTSC                           0x00002901L
//Reserved for future processor specific flags        0x00002902L
//                                                 to 0x00002FFFL    //12287

// Define to support
#define M_CC1                                         0x100
#define M_CC2                                         0x101
#define M_CC3                                         0x102
#define M_CC4                                         0x103

//Auxiliary IO defines 4Sight

#define M_USER_IN_FORMAT                              0x08000000L
#define M_USER_OUT_FORMAT                             0x04000000L
#define M_USER_BIT_FORMAT                             0x02000000L
#define M_USER_BIT_PRESENT                            0x40000000L
#define M_AUX_SIGNAL_SOURCE                           0x20000000L
#define M_AUX_SIGNAL                                  0x10000000L
#define M_AUX_SIGNAL_MODE                             MIL_MAKE_CONST(0x80000000L,0x0000000080000000)
#define M_USER_BIT_MODE                               M_AUX_SIGNAL_MODE
#define M_USER_BIT_VALUE                              MIL_MAKE_CONST(0xA0000000L,0x00000000A0000000)
#define M_USER_BIT                                    M_USER_BIT_VALUE
#define M_USER_BIT_VALUE_IN                           (M_USER_BIT_VALUE | M_USER_IN_FORMAT)
#define M_USER_BIT_VALUE_OUT                          (M_USER_BIT_VALUE | M_USER_OUT_FORMAT)
#define M_USER_BIT_INTERRUPT_MODE                     MIL_MAKE_CONST(0xC0000000L,0x00000000C0000000)
#define M_AUX_SIGNAL_DEBOUNCE_TIME                    MIL_MAKE_CONST(0xD0000000L,0x00000000D0000000)
#define M_USER_BIT_INTERRUPT_STATE                    MIL_MAKE_CONST(0xE0000000L,0x00000000E0000000)
#define M_USER_BIT_MASK                               MIL_MAKE_CONST(0xEE000000L,0x00000000EE000000)
#define M_USER_BIT_BIT_MASK_ENABLED                   0x10000000L
#define M_USER_BIT_INVALID_BIT_MASK                   0x01FFFFFFL
#define M_USER_BIT_ALL                                0x000FFFFFL
#define M_BIT_MASK(mask)   ( ((long) (mask) <= M_USER_BIT_ALL) ? (M_USER_BIT_BIT_MASK_ENABLED | ((long) (mask))) : (M_USER_BIT_BIT_MASK_ENABLED | M_USER_BIT_INVALID_BIT_MASK) )
#define M_USER_BIT_CHANGE                             2244L
#define M_USER_BIT_CHANGE_HANDLER_PTR                 2245L
/* Reserve next 19 values                       from  2246L*/
/*                                             to     2264L*/
#define M_USER_BIT_CHANGE_HANDLER_USER_PTR            2266L
/* Reserve next 19 values                       from  2267L*/
/*                                             to     2285L*/
#define M_USER_BIT_COUNT_IN                           (M_USER_BIT_VALUE_IN | M_USER_BIT_COUNT)
#define M_USER_BIT_COUNT_OUT                          (M_USER_BIT_VALUE_OUT| M_USER_BIT_COUNT)

#define M_USER_OUT                                    1L
/* Reserve 31 values for M_USER_OUT             from   2L*/
/*                                              to     32L*/

/* Define macros used with M_AUX_SIGNAL_SOURCE */
#define M_PARAM_MASK                   0x3ff
#define M_PARAM_BIT_COUNT              10
#define M_OP_MASK                      0x1f
#define M_OP_BIT_COUNT                 5
#define M_MARK_EXPOSURE_BIT            0x100
#define M_MARK_HW_PORT_BIT             0x200
#define M_MARK_USER_BIT_BIT            0x300

#define M_PARAM_A_SHIFT                0
#define M_PARAM_B_SHIFT                (M_PARAM_BIT_COUNT+M_OP_BIT_COUNT)
#define M_OP_1_SHIFT                   (M_PARAM_BIT_COUNT)

#define M_PARAM_A_MASK                 (M_PARAM_MASK << M_PARAM_A_SHIFT)
#define M_PARAM_B_MASK                 (M_PARAM_MASK << M_PARAM_B_SHIFT)
#define M_OP_1_MASK                    (M_OP_MASK << M_OP_1_SHIFT)

#define M_IS_EXPOSURE(X)               ( ((X >= M_GRAB_EXPOSURE+M_TIMER1) && (X <= M_GRAB_EXPOSURE+M_TIMER8)) ? M_TRUE : M_FALSE )
#define M_IS_USER_BIT(X)               ( (X & M_USER_BIT) ? M_TRUE : M_FALSE) 
#define M_IS_HW_PORT(X)                ( ((M_IS_EXPOSURE(X) == M_FALSE) && (M_IS_USER_BIT(X) == M_FALSE)) ? M_TRUE : M_FALSE )


#define M_MARK_AS_EXPOSURE(X)          ( (X-M_GRAB_EXPOSURE) | M_MARK_EXPOSURE_BIT)
#define M_MARK_AS_HW_PORT(X)           ( X | M_MARK_HW_PORT_BIT)
#define M_MARK_AS_USER_BIT(X)          ( (X-M_USER_BIT) | M_MARK_USER_BIT_BIT )
#define M_MARK_PARAM(X)                ( (M_IS_EXPOSURE(X) ? M_MARK_AS_EXPOSURE(X) : (M_IS_USER_BIT(X) ? M_MARK_AS_USER_BIT(X) : M_MARK_AS_HW_PORT(X)) ) )

#define M_COMBINE                      0x80000000

#if OldDefinesSupport
#define M_USER_OUT_COMBINE(A, Op1, B)     ( M_COMBINE | ((M_MARK_PARAM(A) & M_PARAM_MASK) << M_PARAM_A_SHIFT) | ((Op1 & M_PARAM_MASK) << M_OP_1_SHIFT) | ((M_MARK_PARAM(B) & M_PARAM_MASK) << M_PARAM_B_SHIFT) )
#endif

#define M_AUX_SIGNAL_COMBINE(A, Op1, B)   ( M_COMBINE | ((M_MARK_PARAM(A) & M_PARAM_MASK) << M_PARAM_A_SHIFT) | ((Op1 & M_PARAM_MASK) << M_OP_1_SHIFT) | ((M_MARK_PARAM(B) & M_PARAM_MASK) << M_PARAM_B_SHIFT) )

/* End define macros used with M_AUX_SIGNAL_SOURCE */

// SysControls for modifying the coefficients used in the Vio and Radient colorspace converter.
#define M_BOARD_TO_HOST_COLOR_CONVERSION_COEFFICIENTS         MIL_MAKE_CONST(0xEF000000L,0x00000000EF000000)
#define M_BOARD_TO_HOST_COLOR_CONVERSION_COEFFICIENTS_MASK    MIL_MAKE_CONST(0xFFFF0000L,0x00000000FFFF0000)

#define M_MONO_TO_MONO                          0x00000001L //MONO source buffer
#define M_MONO_TO_BGR                           0x00000002L
#define M_MONO_TO_RGB                           0x00000003L
#define M_MONO_TO_YUV                           0x00000004L
#define M_MONO_TO_YCBCRSD                       0x00000005L
#define M_MONO_TO_YCRCBSD                       M_MONO_TO_YCBCRSD //Obsolete
#define M_MONO_TO_YCBCRHD                       0x00000006L
#define M_MONO_TO_YCRCBHD                       M_MONO_TO_YCBCRHD //Obsolete
#define M_BGR_TO_MONO                           0x00000007L //BGR source buffer
#define M_BGR_TO_BGR                            0x00000008L
#define M_BGR_TO_YUV                            0x00000009L
#define M_BGR_TO_YCBCRSD                        0x0000000AL
#define M_BGR_TO_YCRCBSD                        M_BGR_TO_YCBCRSD  //Obsolete
#define M_BGR_TO_YCBCRHD                        0x0000000BL
#define M_BGR_TO_YCRCBHD                        M_BGR_TO_YCBCRHD  //Obsolete
#define M_RGB_TO_MONO                           0x0000000CL //RGB source buffer
#define M_RGB_TO_RGB                            0x0000000DL
#define M_RGB_TO_YUV                            0x0000000EL
#define M_RGB_TO_YCBCRSD                        0x0000000FL
#define M_RGB_TO_YCRCBSD                        M_RGB_TO_YCBCRSD  //Obsolete
#define M_RGB_TO_YCBCRHD                        0x00000010L
#define M_RGB_TO_YCRCBHD                        M_RGB_TO_YCBCRHD  //Obsolete
#define M_YUV_TO_MONO                           0x00000011L //YUV source buffer
#define M_YUV_TO_BGR                            0x00000012L
#define M_YUV_TO_RGB                            0x00000013L
#define M_YUV_TO_YUV                            0x00000014L
#define M_YUV_TO_YCBCRSD                        0x00000015L
#define M_YUV_TO_YCRCBSD                        M_YUV_TO_YCBCRSD  //Obsolete
#define M_YUV_TO_YCBCRHD                        0x00000016L
#define M_YUV_TO_YCRCBHD                        M_YUV_TO_YCBCRHD  //Obsolete
#define M_YCBCRSD_TO_MONO                       0x00000017L //YCrCb SDTV source buffer
#define M_YCRCBSD_TO_MONO                       M_YCBCRSD_TO_MONO //Obsolete
#define M_YCBCRSD_TO_BGR                        0x00000018L
#define M_YCRCBSD_TO_BGR                        M_YCBCRSD_TO_BGR  //Obsolete
#define M_YCBCRSD_TO_RGB                        0x00000019L
#define M_YCRCBSD_TO_RGB                        M_YCBCRSD_TO_RGB  //Obsolete
#define M_YCBCRSD_TO_YUV                        0x0000001AL
#define M_YCRCBSD_TO_YUV                        M_YCBCRSD_TO_YUV  //Obsolete
#define M_YCBCRSD_TO_YCRCBSD                    0x0000001BL
#define M_YCRCBSD_TO_YCRCBSD                    M_YCBCRSD_TO_YCRCBSD //Obsolete
#define M_YCBCRHD_TO_MONO                       0x0000001CL //YCrCb HDTV source buffer
#define M_YCRCBHD_TO_MONO                       M_YCBCRHD_TO_MONO //Obsolete
#define M_YCBCRHD_TO_BGR                        0x0000001DL
#define M_YCRCBHD_TO_BGR                        M_YCBCRHD_TO_BGR  //Obsolete
#define M_YCBCRHD_TO_RGB                        0x0000001EL
#define M_YCRCBHD_TO_RGB                        M_YCBCRHD_TO_RGB  //Obsolete
#define M_YCBCRHD_TO_YUV                        0x0000001FL
#define M_YCRCBHD_TO_YUV                        M_YCBCRHD_TO_YUV  //Obsolete
#define M_YCBCRHD_TO_YCBCRHD                    0x00000020L
#define M_YCRCBHD_TO_YCRCBHD                    M_YCBCRHD_TO_YCBCRHD //Obsolete

// !!! MAP FOR OLD DEFINES
#if OldDefinesSupport
#define M_PRIMARY_DDRAW_SURFACE_FORMAT                M_PRIMARY_SURFACE_FORMAT
#define M_PRIMARY_DDRAW_SURFACE_SIZE_BITS             M_PRIMARY_SURFACE_SIZE_BITS
#define M_PRIMARY_DDRAW_SURFACE_SIZE_X                M_PRIMARY_SURFACE_SIZE_X
#define M_PRIMARY_DDRAW_SURFACE_SIZE_Y                M_PRIMARY_SURFACE_SIZE_Y
#define M_PRIMARY_DDRAW_SURFACE_PITCH_BYTE            M_PRIMARY_SURFACE_PITCH_BYTE
#define M_PRIMARY_DDRAW_SURFACE_MEM_PTR               M_PRIMARY_SURFACE_HOST_ADDRESS
#define M_DDRAW_LIVE_VIDEO_FORMAT_SUPPORTED           M_UNDERLAY_LIVE_FORMAT_SUPPORTED
#define M_DDRAW_UNDERLAY_FORMAT_SUPPORTED             M_UNDERLAY_FORMAT_SUPPORTED
#define M_DDRAW_UNDERLAY_SUPPORTED                    M_UNDERLAY_SUPPORTED
#define M_DDRAW_UNDERLAY_ZOOM_MAX                     M_UNDERLAY_ZOOM_MAX
#define M_DDRAW_UNDERLAY_ZOOM_MIN                     M_UNDERLAY_ZOOM_MIN
//#define M_LIVE_VIDEO                                  M_LIVE_GRAB   --> M_LIVE_VIDEO: name reused for buffer attribute
#define M_LIVE_GRAB_END_TRIGGER                       M_GRAB_CONTINUOUS_END_TRIGGER
#define M_LAST_GRAB_IN_ACTUAL_BUFFER                  M_LAST_GRAB_IN_TRUE_BUFFER
#define M_SYS_TYPE                                    M_SYSTEM_TYPE
#define M_SYS_NUMBER                                  M_NUMBER
#define M_SYS_INIT_FLAG                               M_INIT_FLAG
#define M_SYS_DISPLAY_NUM                             M_DISPLAY_NUM
#define M_SYS_DISPLAY_TYPE                            M_DISPLAY_TYPE
#define M_SYS_DIGITIZER_NUM                           M_DIGITIZER_NUM
#define M_SYS_DIGITIZER_TYPE                          M_DIGITIZER_TYPE
#define M_SYS_PROCESSOR_NUM                           M_PROCESSOR_NUM
#define M_SYS_BOARD_TYPE                              M_BOARD_TYPE
#define M_SYS_BOARD_REVISION                          M_BOARD_REVISION
#define M_SYS_TUNER_NUM                               M_TUNER_NUM
#define M_SYS_TUNER_TYPE                              M_TUNER_TYPE
#define M_SYS_RGB_MODULE_NUM                          M_RGB_MODULE_NUM
#define M_SYS_RGB_MODULE_TYPE                         M_RGB_MODULE_TYPE
#if (BW_COMPATIBILY==0x80)
#define M_SYS_DISPLAY_LIST                            M_DISPLAY_LIST
#endif
#define M_SYS_DUAL_SCREEN_MODE                        M_DUAL_SCREEN_MODE
#define M_SYS_UNDERLAY_SURFACE_AVAILABLE              M_UNDERLAY_SURFACE_AVAILABLE
#define M_SYS_UNDERLAY_SURFACE_PHYSICAL_ADDRESS       M_PHYSICAL_ADDRESS_UNDERLAY
#define M_SYS_WIN_MODE                                M_WIN_MODE
#define M_SYS_MAX_TILE_SIZE                           M_MAX_TILE_SIZE
#define M_SYS_MAX_TILE_SIZE_X                         M_MAX_TILE_SIZE_X
#define M_SYS_MAX_TILE_SIZE_Y                         M_MAX_TILE_SIZE_Y
#define M_ON_BOARD_MEM_ADRS                           M_PHYSICAL_ADDRESS_UNDERLAY
#define M_ON_BOARD_VGA_ADRS                           M_PHYSICAL_ADDRESS_VGA
#define MMX_EXTRA_BYTES                               M_MMX_EXTRA_BYTES
#define M_LOCATION_WORK_HOST                          M_SYSTEM_HOST_TYPE
#define M_DMA_POOL_FREE                               M_NON_PAGED_MEMORY_FREE
#define M_DMA_POOL_USED                               M_NON_PAGED_MEMORY_USED
#define M_DMA_POOL_SIZE                               M_NON_PAGED_MEMORY_SIZE
#define M_BOTH_FIELD                                  M_BOTH_FIELDS

#define M_FPGA_TEMPERATURE                            M_TEMPERATURE_FPGA
#define M_FPGA_TEMPERATURE_MAX_MEASURED               M_TEMPERATURE_FPGA_MAX_MEASURED
#define M_FPGA_VOLTAGE_VCCINT                         M_VOLTAGE_FGPA_VCCINT
#define M_FPGA_VOLTAGE_VCCINT_MIN_MEASURED            M_VOLTAGE_FPGA_VCCINT_MIN_MEASURED
#define M_FPGA_VOLTAGE_VCCINT_MAX_MEASURED            M_VOLTAGE_FPGA_VCCINT_MAX_MEASURED
#define M_FPGA_VOLTAGE_VCCAUX                         M_VOLTAGE_FPGA_VCCAUX
#define M_FPGA_VOLTAGE_VCCAUX_MIN_MEASURED            M_VOLTAGE_FPGA_VCCAUX_MIN_MEASURED
#define M_FPGA_VOLTAGE_VCCAUX_MAX_MEASURED            M_VOLTAGE_FPGA_VCCAUX_MAX_MEASURED
#define M_PROCESSING_FPGA_TEMPERATURE                 M_TEMPERATURE_FPGA_PROCESSING
#define M_PROCESSING_FPGA_TEMPERATURE_MAX_MEASURED    M_TEMPERATURE_FPGA_PROCESSING_MAX_MEASURED



#endif // !!! MAP FOR OLD DEFINES

/************************************************************************/
/* MsysInquire() / MsysControl() Values                                 */
/************************************************************************/

#define M_FORCE                                       -9998L
#define M_L1                                              1L
#define M_MIN_ODYSSEY_HEAP_SIZE                          16L

//Values for the M_MPEG_BIT_RATE_MODE
#define M_CONSTANT                                    0x8000L
#define M_VARIABLE                                    2L
#define M_VARIABLE_MAX                                3L
#define M_CONSTANT_QUALITY                            4L

// M_MODIFIED_BUFFER_HOOK_MODE values
#define M_MULTI_THREAD                                0x1000
#define M_SINGLE_THREAD                               0x2000

/************************************************************************/
/* Msys other defines                                                   */
/************************************************************************/
// Maximum string size for M_CPU_VENDOR_NAME inquire value
#define M_CPU_VENDOR_NAME_SIZE                        13L

// Maximum string size for M_SYSTEM_NAME inquire value
#define M_SYSTEM_NAME_SIZE                            64L

/************************************************************************/
/* MsysHookFunction()                                                   */
/************************************************************************/
#define M_1394_BUS_RESET                              2287L
#define M_USER_BIT_CHANGE                             2244L
#define M_USER_BIT_CHANGE_HANDLER_PTR                 2245L
/* Reserve next 19 values                       from  2246L*/
/*                                             to     2264L*/
#define M_USER_BIT_CHANGE_HANDLER_USER_PTR            2266L
/* Reserve next 19 values                       from  2267L*/
/*                                             to     2285L*/
#define M_WATCHDOG_BITE_WARNING                       2377

/************************************************************************/
/* MsysGetHookInfo()                                                    */
/************************************************************************/

#define M_USER_BIT                                    M_USER_BIT_VALUE     // 0xA0000000L
/* Reserve next 31 values                      from   4088L*/
/*                                             to     4118L*/
#define M_USER_BIT_FIELD                              4181L
#define M_USER_BIT_CHANGE                             2244L
#define M_USER_BIT_CHANGE_HANDLER_PTR                 2245L
/* Reserve next 19 values                       from  2246L*/
/*                                             to     2264L*/
#define M_USER_BIT_CHANGE_HANDLER_USER_PTR            2266L
/* Reserve next 19 values                       from  2267L*/
/*                                             to     2285L*/


/************************************************************************/
/* MsysConfigAccess()                                                   */
/************************************************************************/
#define M_PCI_CONFIGURATION_SPACE                     0L
#define M_DETECT_PCI_DEVICE                           1L
#define M_1394_CONFIGURATION_SPACE                    2L
#define M_RESERVED_FOR_INTERNAL_USE_SYS_CONFIG        3L

#define M_DEFAULT                                     0x10000000L
#define M_READ                                        1
#define M_WRITE                                       2
#define M_BIG_ENDIAN                                  0x00000100L
#define M_LITTLE_ENDIAN                               0x00000200L


#define M_PCI_VENDOR_ID                               0x00 // (16 lsb)
#define M_PCI_DEVICE_ID                               0x00 // (16 msb)
#define M_PCI_COMMAND                                 0x01 // (16 lsb)
#define M_PCI_STATUS                                  0x01 // (16 msb)
#define M_PCI_REVISION_ID                             0x02 // (byte 0)
#define M_PCI_CLASS_CODE                              0x02 // (byte 1,2,3)
#define M_PCI_LATENCY_TIMER                           0x03 // (byte 1)
#define M_PCI_BASE_ADRS0                              0x04 //
#define M_PCI_BASE_ADRS1                              0x05 //
#define M_PCI_INT_LINE                                0x0F // (byte 0)
#define M_PCI_INT_PIN                                 0x0F // (byte 1)

//Auxiliary IO values
#define M_OFF                                         0L       // Must be zero
#define M_ON                                          1L
#define M_INPUT                                       2L
#define M_OUTPUT                                      3L
#define M_EDGE_RISING                                 12L
#define M_EDGE_FALLING                                13L
#define M_ANY_EDGE                                    14L
#define M_DISABLE                                     -9999L
#define M_ENABLE                                      -9997L

/************************************************************************/
/* MthrXxxxxx                                                           */
/************************************************************************/
#define M_DEFAULT                                     0x10000000L
#define M_SIGNALED                                    0x00000010L
#define M_NOT_SIGNALED                                0x00000020L
#define M_AUTO_RESET                                  0x00002000L
#define M_MANUAL_RESET                                0x00004000L
#define M_SYNCHRONOUS                                 0x00000001L
#define M_ASYNCHRONOUS                                0x00000002L

#define M_ENABLE                                      -9997L
#define M_DISABLE                                     -9999L

/************************************************************************/
/* MthrAlloc                                                            */
/************************************************************************/
#define M_ALL                                         0x40000000L

#define M_EVENT                                       0x00000080L
#define M_EVENT_CREATE                                0x00000200L
#define M_EVENT_CREATE_ON_NATIVE                      0x00000400L
#define M_THREAD                                      M_SYSTEM_THREAD  // 0x00000100
#define M_SELECTABLE_THREAD                           0x00001000L
#define M_THREAD_CREATE                               0x00000800L
#define M_THREAD_CREATE_ON_ID                         0x00002000L

#define M_INTERNAL_THREAD                             0x00010000L

/************************************************************************/
/* MthrControl only                                                     */
/************************************************************************/
#define M_THREAD_COMMANDS_ABORT                       1810L
#define M_THREAD_SELECT                               1708L
#define M_EVENT_SET                                   1707L

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_LOCK                                        8256
#define M_UNLOCK                                      8288
#else
#define M_LOCK                                        20480L   // 0x00005000
#define M_UNLOCK                                      24576L   // 0x00006000
#endif

#define M_THR_CONT_TYPE_MASK                          0x00FFFFFFL
#define M_THR_CONT_TYPE(n)                            (n&M_THR_CONT_TYPE_MASK)

#define M_THREAD_CURRENT                              0x01000000L
#define M_THREAD_ALL                                  0x02000000L //Used in helios
#define M_QUEUED                                      0x04000000L //To be ORed with M_THREAD_COMMANDS_ABORT
#define M_LOW_LATENCY                                 0x00001000L // Command remove node used in ThreadCancel


/************************************************************************/
/* MthrControl / Inquire                                                */
/************************************************************************/
#define M_THREAD_MODE                                 1804L
#define M_THREAD_TIME_SLICE                           1811L
#define M_THREAD_PRIORITY                             1019L
#define M_ACCELERATOR                                 1813L
#define M_BUS_MASTER_COPY_MODE                        1815L
#define M_NODE_SELECT                                 1816L
#define M_REMOTE_SYSTEM_SELECT                M_NODE_SELECT  //deprecated
#define M_MP_MAX_CORES                                1818L  //deprecated as of Mil9.2
#define M_PU_INSTANCE_NUMBER                          1819L

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_LOCK_TRY                                    8320
#else
#define M_LOCK_TRY                                    28672L   // 0x00007000
#endif

#define M_IDLE                                           1L
#define M_LOWEST                                         6L
#define M_BELOW_NORMAL                                   7L
#define M_NORMAL                                         8L
#define M_ABOVE_NORMAL                                   9L
#define M_HIGHEST                                       10L
#define M_TIME_CRITICAL                                 15L


/************************************************************************/
/* MthrInquire only                                                     */
/************************************************************************/
#define M_NATIVE_ID                                   1016L
#define M_EVENT_STATE                                 1706L
#define M_EVENT_MODE                                  1709L
#define M_MP_MAX_CORES_EFFECTIVE                      1710L  //deprecated as of Mil9.2


/************************************************************************/
/* MthrInquireMp / MthrControlMp                                        */
/*                                                                      */
/* The flags for these functions are the same as for                    */
/* MappControlMp and MappInquireMp and so are not duplicated here.      */
/************************************************************************/


/************************************************************************/
/* MthrWait                                                             */
/************************************************************************/
#define M_THREAD_END_WAIT                             0x40000000L
#define M_EVENT_WAIT                                  0x20000000L
#define M_EVENT_SYNCHRONIZE                           0x08000000L
#define M_THREAD_WAIT                                 0x01000000L
#define M_INFINITE                                    -1L

#define M_MAX_TIMEOUT                                 0xFFFFFFL
#define M_TIMEOUT_MASK                                M_MAX_TIMEOUT
#define M_EVENT_TIMEOUT(Val)                          (((unsigned long)Val >= M_MAX_TIMEOUT) ? 0 : Val)
#define M_THREAD_TIMEOUT(Val)                         M_EVENT_TIMEOUT(Val)
#define M_WAIT_OPTION_WITHOUT_TIMEOUT(WaitOption)     (WaitOption&0xFF000000)
#define M_EXTRACT_TIMEOUT(WaitOption)                 (WaitOption&M_TIMEOUT_MASK)

/************************************************************************/
/* MthrWaitMultiple                                                     */
/************************************************************************/
#define M_THREAD_END_WAIT                             0x40000000L
#define M_EVENT_WAIT                                  0x20000000L
//#define M_DEFAULT                                     0x10000000L
#define M_EVENT_SYNCHRONIZE                           0x08000000L
#define M_ALL_OBJECTS                                 0x04000000L
#define M_EVENT_SYNCHRONIZE_ON_NATIVE                 0x02000000L
//#define M_THREAD_WAIT                                 0x01000000L
#define M_THREAD_END_WAIT_ALL                         M_ALL_OBJECTS+M_THREAD_END_WAIT
#define M_EVENT_WAIT_ALL                              M_ALL_OBJECTS+M_EVENT_WAIT
#define M_EVENT_SYNCRONIZE_ALL                        M_ALL_OBJECTS+M_EVENT_SYNCHRONIZE

#define M_MAX_TIMEOUT                                 0xFFFFFFL
#define M_TIMEOUT_MASK                                M_MAX_TIMEOUT
#define M_EVENT_TIMEOUT(Val) (((unsigned long)Val >= M_MAX_TIMEOUT) ? 0 : Val)
#define M_THREAD_TIMEOUT(Val) M_EVENT_TIMEOUT(Val)
#define M_WAIT_OPTION_WITHOUT_TIMEOUT(WaitOption) (WaitOption&0xFF000000)
#define M_WAIT_OPTION_WITHOUT_TIMEOUT_AND_ALL_OBJECTS(WaitOption) (WaitOption&0xFB000000)
#define M_EXTRACT_TIMEOUT(WaitOption)             (WaitOption&M_TIMEOUT_MASK)

#define M_MAXIMUM_WAIT_OBJECTS                        64L


/************************************************************************/
/* MdigAlloc() defines                                                  */
/************************************************************************/
#define M_GC_DEVICE_IP_ADDRESS                        1
#define M_GC_DEVICE_USER_NAME                         2
#define M_DEV_NUMBER                                  3
//Add non-bitwise values above

#define M_DIG_NON_BITWISE_MASK                        0x0000000FL
#define M_USE_MEMORY_DCF                              0x00000010L
#define M_DCF_REALLOC                                 0x00000020L
#define M_DISPLAY_DIGITIZER                           0x00000040L //corona 
#define M_SHARED_BANDWIDTH                            0x00000200L
#define M_1394_BANDWIDTH_FLAG                         0x00000800L
#define M_1394_BANDWIDTH(percent)   ( (((long) percent > 0) && ((long) percent <= 100)) ? (M_1394_BANDWIDTH_FLAG | ((long) percent)) : 0 )
#define M_EXCLUSIVE_BANDWIDTH                         M_DEFAULT
#define M_FAST                                        0x00002000L
#define M_DEFAULT_1394                                0x00100000L
#define M_GC_BROADCAST_MASTER                         0x00200000L
#define M_GC_MULTICAST_MASTER                         0x00400000L
#define M_GC_SLAVE                                    0x00800000L
#define M_MINIMAL                                     0x00001000L

#define M_DIG_DEV_IS_STRING(X) (((X)==M_GC_DEVICE_IP_ADDRESS) || ((X)==M_GC_DEVICE_USER_NAME))
#define M_GC_CAMERA_ID(X) ((MIL_INT)(X))

#define M_DEV0                                        0L
#define M_DEV1                                        1L
#define M_DEV2                                        2L
#define M_DEV3                                        3L
#define M_DEV4                                        4L
#define M_DEV5                                        5L
#define M_DEV6                                        6L
#define M_DEV7                                        7L
#define M_DEV8                                        8L
#define M_DEV9                                        9L
#define M_DEV10                                       10L
#define M_DEV11                                       11L
#define M_DEV12                                       12L
#define M_DEV13                                       13L
#define M_DEV14                                       14L
#define M_DEV15                                       15L
#define M_DEV16                                       16L
#define M_DEV17                                       17L
#define M_DEV18                                       18L
#define M_DEV19                                       19L
#define M_DEV20                                       20L
#define M_DEV21                                       21L
#define M_DEV22                                       22L
#define M_DEV23                                       23L
#define M_DEV24                                       24L
#define M_DEV25                                       25L
#define M_DEV26                                       26L
#define M_DEV27                                       27L
#define M_DEV28                                       28L
#define M_DEV29                                       29L
#define M_DEV30                                       30L
#define M_DEV31                                       31L
#define M_DEV32                                       32L
#define M_DEV33                                       33L
#define M_DEV34                                       34L
#define M_DEV35                                       35L
#define M_DEV36                                       36L
#define M_DEV37                                       37L
#define M_DEV38                                       38L
#define M_DEV39                                       39L
#define M_DEV40                                       40L
#define M_DEV41                                       41L
#define M_DEV42                                       42L
#define M_DEV43                                       43L
#define M_DEV44                                       44L
#define M_DEV45                                       45L
#define M_DEV46                                       46L
#define M_DEV47                                       47L
#define M_DEV48                                       48L
#define M_DEV49                                       49L
#define M_DEV50                                       50L
#define M_DEV51                                       51L
#define M_DEV52                                       52L
#define M_DEV53                                       53L
#define M_DEV54                                       54L
#define M_DEV55                                       55L
#define M_DEV56                                       56L
#define M_DEV57                                       57L
#define M_DEV58                                       58L
#define M_DEV59                                       59L
#define M_DEV60                                       60L
#define M_DEV61                                       61L
#define M_DEV62                                       62L
#define M_DEV63                                       63L
#define M_NODE0                                       0x00010000L
#define M_NODE1                                       0x00020000L
#define M_NODE2                                       0x00040000L
#define M_NODE3                                       0x00080000L
#define M_NODE4                                       0x00100000L
#define M_NODE5                                       0x00200000L
#define M_NODE6                                       0x00400000L
#define M_NODE7                                       0x00800000L
#define M_NODE8                                       0x01000000L
#define M_NODE9                                       0x02000000L
#define M_NODE10                                      0x04000000L
#define M_NODE11                                      0x08000000L
#define M_NODE12                                      0x10000000L
#define M_NODE13                                      0x20000000L
#define M_NODE14                                      0x40000000L
#define M_NODE15                                      0x80000000L
#define M_NODE_BITS                                   (M_NODE0|M_NODE1|M_NODE2|M_NODE3|M_NODE4|M_NODE5|   \
   M_NODE6|M_NODE7|M_NODE8|M_NODE9|M_NODE10|M_NODE11| \
   M_NODE12|M_NODE13|M_NODE14|M_NODE15)
/************************************************************************/
/* MdigInquire() / MdigControl() Types                                  */
/************************************************************************/

//Used, as combination constants, to target board vs camera with MdigInquire/MdigControl
#define M_BOARD                                       MAKE_INT64(0x4000000000000000)
#define M_CAMERA                                      MAKE_INT64(0x2000000000000000)
#define M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK          (M_CAMERA | M_BOARD | MAKE_INT64(0x9FFF000000000000))
#define M_DIG_STRIP_CAM_BIT(X)                        (X & (~M_CAMERA))
#define M_DIG_STRIP_BRD_BIT(X)                        (X & (~M_BOARD))
#define M_DIG_STRIP_CAM_BRD_BITS(X)                   (X & (~(M_CAMERA | M_BOARD)))
#define M_DIG_CAM_BIT_SET(X)                          ((X & M_CAMERA) ? M_TRUE : M_FALSE)
#define M_DIG_BRD_BIT_SET(X)                          ((X & M_BOARD) ? M_TRUE : M_FALSE)
#define M_DIG_CAM_BRD_BITS_SET(X)                     (((X & (M_CAMERA|M_BOARD)) == (M_CAMERA|M_BOARD)) ? M_TRUE : M_FALSE)


#define M_IRIS                                        160L
/* Reserve next 2 value 131, 132*/
#define M_NO_INPUT_PRESENT                            0x00000080L
#define M_SIZE_BAND                                   1005L
#define M_SIZE_BAND_LUT                               1006L
#define M_SIZE_BIT                                    1007L
#define M_TYPE                                        1008L
#define M_NUMBER                                      1009L
#define M_INIT_FLAG                                   1012L
#define M_ATTRIBUTE                                   1013L
#define M_SIGN                                        1014L
#define M_NATIVE_ID                                   1016L
#define M_NATIVE_CONTROL_ID                           1017L
#define M_COLOR_MODE                                  1018L
#define M_THREAD_PRIORITY                             1019L
#define M_OWNER_SYSTEM_TYPE                           1023L
#define M_LOW_LEVEL_API_OBJECT                        1024L
#define M_EFFECTIVE_SIZE_BIT                          1039L
#define M_MIL_ID_INTERNAL                             1049L


/************************************************************************/
/* MdigInquire() Types MIL_ID range start                               */
/************************************************************************/
// Inquire value with MIL_ID type must be in that range : 1100-1199
#define M_DIG_INQUIRE_MIL_ID_START                    1100L
#define M_OWNER_SYSTEM                                1101L
#define M_LUT_ID                                      1102L

#define M_DRIVER_HOOK_CONTEXT_REMOTE_ID               1170L
/* Reserve next 20 values                      from   1170L*/
/*                                             to     1189L*/
#define M_DRIVER_HOOK_CONTEXT_REMOTE_ID_END           1189L

#define M_DIG_INQUIRE_MIL_ID_END                      1199L

/************************************************************************/
/* MdigInquire() Types MIL_ID range end                                 */
/************************************************************************/


#define M_SIZE_X                                      1536L // 0x600
#define M_SIZE_Y                                      1537L // 0x601
#define M_SIZE_Z                                      1538L // 0x602

#define M_LIVE_GRAB                                   2034L
#define M_GRAB_CONTINUOUS_END_TRIGGER                 2038L
#define M_LAST_GRAB_IN_TRUE_BUFFER                    2046L
#define M_DISPLAY_DOUBLE_BUFFERING                    2071L
#define M_SERIAL_NUMBER_0                             2099L
#define M_SERIAL_NUMBER_1                             2100L

#define M_BLACK_REF_DOUBLE                            3998L
#define M_WHITE_REF_DOUBLE                            3999L
#define M_CHANNEL                                     4000L
/* Reserve next 1 bits                         from  (4000L | 0x00800000L)*/
#define M_CHANNEL_NUM                                 4001L
#define M_BASE_BLACK_REF                              4002L
#define M_BLACK_REF                                   4003L
/* Reserve next 8 bits                         from  (4003L | 0x00000000L)*/
/*                                                   (4003L | 0x10000000L)*/
/*                                                   (4003L | 0x20000000L)*/
/*                                                   (4003L | 0x40000000L)*/
/*                                                   (4003L | 0x80000000L)*/
/*                                                   (4003L | 0x01000000L)*/
/*                                                   (4003L | 0x02000000L)*/
/*                                                   (4003L | 0x04000000L)*/
/*                                             to    (4003L | 0x08000000L)*/
#define M_WHITE_REF                                   4005L
/* Reserve next 8 bits                         from  (4005L | 0x00000000L)*/
/*                                                   (4005L | 0x10000000L)*/
/*                                                   (4005L | 0x20000000L)*/
/*                                                   (4005L | 0x40000000L)*/
/*                                                   (4005L | 0x80000000L)*/
/*                                                   (4005L | 0x01000000L)*/
/*                                                   (4005L | 0x02000000L)*/
/*                                                   (4005L | 0x04000000L)*/
/*                                             to    (4005L | 0x08000000L)*/
#define M_HUE_REF                                     4006L
#define M_SATURATION_REF                              4007L
#define M_BRIGHTNESS_REF                              4008L
#define M_CONTRAST_REF                                4009L
#define M_GRAB_MODE                                   4016L
#define M_GRAB_FRAME_NUM                              4017L
#define M_GRAB_FIELD_NUM                              4018L
#define M_GRAB_INPUT_GAIN                             4019L    // dependent of M_LUMINANCE and M_CHROMINANCE
#define M_INPUT_MODE                                  4020L
#define M_SCAN_MODE                                   4021L
#define M_SOURCE_SIZE_X                               4022L
#define M_SOURCE_SIZE_Y                               4023L
#define M_SOURCE_OFFSET_X                             4024L
#define M_SOURCE_OFFSET_Y                             4025L
#define M_INTERNAL_SOURCE_SIZE_X                      4026L
#define M_INTERNAL_SOURCE_SIZE_Y                      4027L
#define M_INTERNAL_SOURCE_OFFSET_X                    4028L
#define M_INTERNAL_SOURCE_OFFSET_Y                    4029L
#define M_GRAB_END_HANDLER_PTR                        4030L
#define M_GRAB_END_HANDLER_USER_PTR                   4032L
#define M_GRAB_START_HANDLER_PTR                      4033L
#define M_GRAB_START_HANDLER_USER_PTR                 4035L
#define M_GRAB_FIELD_END_HANDLER_PTR                  4036L
#define M_GRAB_FIELD_END_HANDLER_USER_PTR             4037L
#define M_GRAB_FIELD_END_ODD_HANDLER_PTR              4038L
#define M_GRAB_FIELD_END_ODD_HANDLER_USER_PTR         4039L
#define M_GRAB_FIELD_END_EVEN_HANDLER_PTR             4040L
#define M_GRAB_FIELD_END_EVEN_HANDLER_USER_PTR        4041L
#define M_GRAB_FRAME_END_HANDLER_PTR                  4042L
#define M_GRAB_FRAME_END_HANDLER_USER_PTR             4043L
#define M_GRAB_FRAME_START_HANDLER_PTR                4044L
#define M_GRAB_FRAME_START_HANDLER_USER_PTR           4045L
#define M_FIELD_START_HANDLER_PTR                     4046L
#define M_FIELD_START_HANDLER_USER_PTR                4047L
#define M_FIELD_START_ODD_HANDLER_PTR                 4048L
#define M_FIELD_START_ODD_HANDLER_USER_PTR            4049L
#define M_FIELD_START_EVEN_HANDLER_PTR                4050L
#define M_FIELD_START_EVEN_HANDLER_USER_PTR           4051L
#define M_SCALING_Y_AVAILABLE                         4052L
#define M_GRAB_TRIGGER_SOURCE                         4053L
#define M_GRAB_TRIGGER_MODE                           4054L
#define M_SOURCE_OFFSET_BIT                           4055L
#define M_NATIVE_CAMERA_ID                            4060L
#define M_VCR_INPUT_TYPE                              4061L
#define M_CLIP_SRC_SUPPORTED                          4062L
#define M_CLIP_DST_SUPPORTED                          4063L
#define M_HOOK_FUNCTION_SUPPORTED                     4064L
#define M_GRAB_WINDOW_RANGE_SUPPORTED                 4065L
#define M_GRAB_8_BITS_SUPPORTED                       4068L
#define M_GRAB_15_BITS_SUPPORTED                      4069L
#define M_GRAB_32_BITS_SUPPORTED                      4070L
#define M_GRAB_EXTRA_LINE                             4071L
#define M_GRAB_DESTRUCTIVE_IN_PROGRESS                4073L
#define M_GRAB_START_MODE                             4074L
#define M_GRAB_WINDOW_RANGE                           4075L
#define M_INPUT_SIGNAL_PRESENT                        4078L
#define M_INPUT_SIGNAL_SOURCE                         4079L
#define M_FIELD_START_THREAD_ID                       4080L
#define M_GRAB_FIELD_END_ODD_THREAD_ID                4081L
#define M_GRAB_FIELD_END_EVEN_THREAD_ID               4082L
#define M_FIELD_START_THREAD_HANDLE                   4083L
#define M_GRAB_FIELD_END_ODD_THREAD_HANDLE            4084L
#define M_GRAB_FIELD_END_EVEN_THREAD_HANDLE           4085L
#define M_FORMAT_UPDATE                               4086L
#define M_USER_BIT_QUEUE_MODE                         4087L
#define M_USER_BIT                                    M_USER_BIT_VALUE     // 0xA0000000L
/* Reserve next 31 values                      from   4088L*/
/*                                             to     4118L*/
#define M_USER_BIT_STATE                              4119L
#define M_GRAB_FAIL_CHECK                             4120L
#define M_GRAB_FAIL_STATUS                            4121L
#define M_GRAB_FAIL_RETRY_NUMBER                      4122L
#define M_GRAB_ON_ONE_LINE                            4123L
#define M_GRAB_WRITE_FORMAT                           4124L
#define M_GRAB_LUT_PALETTE                            4125L
#define M_GRAB_HALT_ON_NEXT_FIELD                     4126L
#define M_GRAB_TIMEOUT                                4127L
#define M_GRAB_IN_PROGRESS                            4128L
#define M_FIELD_START_HOOK_WHEN_GRAB_ONLY             4129L
#define M_GRAB_PENDING                                4130L
#define M_GRAB_FRAME_RATE                             4131L
#define M_FORCE_RAW_DATA                              4132L
#define M_GC_STREAMING_MODE                           4133L


#define M_EXTERNAL_CHROMINANCE                        4137L
#define M_TUNER_FREQUENCY                             4138L
#define M_TUNER_STANDARD                              4139L
#define M_CLOCK_NOT_ALWAYS_VALID                      4140L
#define M_GRAB_LINESCAN_MODE                          4141L
#define M_GRAB_PERIOD                                 4142L
#define M_OVERRIDE_ROUTER                             4143L
#define M_GRAB_EXPOSURE                               4150L
/* Reserve next 8 values                       from   4151L*/
/*                                             to     4158L*/
#define M_GRAB_EXPOSURE_SOURCE                        4160L
/* Reserve next 8 values                       from   4161L*/
/*                                             to     4168L*/
#define M_GRAB_EXPOSURE_MODE                          4170L
/* Reserve next 8 values                       from   4171L*/
/*                                             to     4178L*/
#define M_GRAB_TRIGGER                                4200L
/* Reserve next 8 values                       from   4201L*/
/*                                             to     4208L*/
#define M_GRAB_EXPOSURE_BYPASS                        4210L
#define M_DCF_REALLOC_HANDLER_PTR                     4211L
#define M_DCF_REALLOC_HANDLER_USER_PTR                4212L
#define M_GRAB_RESTRICTION_CHECK                      4215L
#define M_LAST_GRAB_BUFFER                            4216L
#define M_NATIVE_LAST_GRAB_OSB_ID                     4217L
#define M_SYNCHRONIZE_ON_STARTED                      4218L
#define M_GRAB_WAIT                                   4219L
#define M_GRAB_FIELD_START_HANDLER_PTR                4220L
#define M_GRAB_FIELD_START_HANDLER_USER_PTR           4221L
#define M_GRAB_FIELD_START_ODD_HANDLER_PTR            4222L
#define M_GRAB_FIELD_START_ODD_HANDLER_USER_PTR       4223L
#define M_GRAB_FIELD_START_EVEN_HANDLER_PTR           4224L
#define M_GRAB_FIELD_START_EVEN_HANDLER_USER_PTR      4225L
#define M_GRAB_16_BITS_SUPPORTED                      4226L
#define M_GRAB_24_BITS_SUPPORTED                      4227L
#define M_INPUT_SIGNAL_HSYNC_LOCK                     4228L
#define M_GRAB_BLOCK_SIZE                             4229L
#define M_GRAB_DIRECTION_X                            4230L
#define M_GRAB_DIRECTION_Y                            4231L
#define M_GRAB_FREQ_MAX                               4232L
#define M_GRAB_THREAD_HANDLE                          4233L
#define M_GRAB_THREAD_ID                              4234L
#define M_GRAB_START_THREAD_HANDLE                    4235L
#define M_GRAB_START_THREAD_ID                        4236L
#define M_GRAB_END_THREAD_HANDLE                      4237L
#define M_GRAB_END_THREAD_ID                          4238L
#define M_GRAB_PATH_OVERRIDE                          4239L
#define M_GRAB_PATH_OVERRIDE_DCF                      4240L
#define M_GRAB_PATH_PCI                               4241L
#define M_GRAB_AUTOMATIC_INPUT_GAIN                   4242L
#define M_GRAB_DISPLAY_SCALER_QUALITY                 4243L
#define M_GRAB_VALID                                  4244L
#define M_GRAB_FIELD_START_THREAD_HANDLE              4248L
#define M_GRAB_FIELD_START_THREAD_ID                  4249L
#define M_GRAB_EXPOSURE_TRIGGER_MODE                  4250L
/* Reserve next 8 values                       from   4251L*/
/*                                             to     4258L*/
#define M_GRAB_FIELD_END_THREAD_HANDLE                4259L
#define M_GRAB_FIELD_END_THREAD_ID                    4260L
#define M_GRAB_FRAME_END_THREAD_HANDLE                4261L
#define M_GRAB_FRAME_END_THREAD_ID                    4262L
#define M_SET_VCOUNT                                  4263L
#define M_JPEG_ENCODING_MODE                          4264L
#define M_JPEG_DECODING_MODE                          4265L
#define M_JPEG_MARKERS_ENABLE                         4266L
#define M_JPEG_NUMBER_OF_SCAN_ENCODED                 4267L
#define M_JPEG_INPUT_COLOR_MODE                       4268L
#define M_JPEG_OUTPUT_COLOR_MODE                      4269L
#define M_JPEG_IMAGE_FORMAT                           4270L
#define M_JPEG_NAX                                    4271L
#define M_JPEG_NAY                                    4272L
#define M_JPEG_PAX                                    4273L
#define M_JPEG_PAY                                    4274L
#define M_JPEG_AUTO_START_MODE                        4275L
#define M_JPEG_COMPRESS_MODE                          4276L
#define M_JPEG_HW_PROG_MODE                           4277L
#define M_HOOK_MASTER_THREAD_HANDLE                   4278L
#define M_HOOK_MASTER_THREAD_ID                       4279L
#define M_GRAB_PATH_RR                                4280L
#define M_PIXCLK_JPEG_SIGNAL_PRESENT                  4281L
#define M_GRAB_VM                                     4282L
#define M_GARBAGE_UV_ADDRESS                          4283L
#define M_SET_EXPOSURE_ENABLE                         4290L
/* Reserve next 8 values                       from   4291L*/
/*                                             to     4298L*/
#define M_JPEG_FIRST_FIELD_SIZEBYTE                   4301L
#define M_JPEG_SECOND_FIELD_SIZEBYTE                  4302L
#define M_JPEG_OFFSET_X                               4303L
#define M_JPEG_OFFSET_Y                               4304L
#define M_CURRENT_GRAB_BUFFER_HOST_ADDRESS            4305L
#define M_CURRENT_GRAB_BUFFER_PHYSICAL_ADDRESS        4306L
#define M_RESET_CONTINUOUS_GRABBER                    4307L
#define M_TIMER_INTERRUPT                             4308L
#define M_TIMER_INTERRUPT_LENGHT                      4309L
#define M_TIMER_SET_INTERRUPT                         4310L
#define M_GRAB_SAMPLING_POSITION                      4311L
#define M_JPEG_DMA_TRANSFER                           4312L
#define M_GRAB_FRAME_START_THREAD_HANDLE              4313L
#define M_GRAB_FRAME_START_THREAD_ID                  4314L
#define M_INTERNAL_GRAB_BUFFERS_NB                    4315L
#define M_INTERNAL_GRAB_BUFFERS_FORMAT                4317L
#define M_KS0127_REV_ID                               4318L
#define M_DECODER_REV_ID                              M_KS0127_REV_ID
#define M_GRAB_SCALE_MODE                             4319L
#define M_GRAB_SCALE_MODE_X                           4320L
#define M_GRAB_SCALE_MODE_Y                           4321L
#define M_START_THREAD_HANDLE                         4322L
#define M_START_THREAD_ID                             4323L
#define M_SOURCE_COMPENSATION                         4324L
#define M_GRAB_COLOR                                  4325L
#define M_SYNCHRONIZE_CHANNEL                         4326L
#define M_ODD_EVEN_CORRECTION                         4327L
#define M_POLLING_FOR_END_OF_XFER                     4328L
#define M_FORCE_PSEUDO_LIVE_GRAB                      4329L
#define M_GRAB_END_HOOK                               4330L
#define M_GRAB_START_HOOK                             4331L
/* Free to use                                 from   4332*/
/*                                             to     4339*/
#define M_GRAB_EXPOSURE_CLOCK_SOURCE                  4340L
/* Reserve next 8 values                       from   4341L*/
/*                                             to     4348L*/
#define M_GRAB_EXPOSURE_USAGE                         4350L
/* Reserve next 8 values                       from   4351L*/
/*                                             to     4358L*/

#define M_HOOK_FOR_PSEUDO_LIVE_GRAB                   4360L
#define M_YIELD_FOR_END_OF_XFER                       4361L
#define M_GRAB_SCALE_QUALITY                          4362L
#define M_USER_BIT_INQUIRE_START                      4363L
#define M_USER_BIT                                    M_USER_BIT_VALUE     // 0xA0000000L
/* Reserve next 31 values                      from   4088L*/
/*                                             to     4118L*/
#define M_USER_BIT_COUNT                              4364L
#define M_USER_BIT_OPTOMODULE                         4365L
#define M_USER_BIT_INQUIRE_END                        4366L

#define MAX_USER_BIT_NB                                  20       // Nb of user bits available

#define M_GRAB_LINE_HANDLER_PTR                       4367L
#define M_GRAB_LINE_HANDLER_USER_PTR                  4368L
#define M_GRAB_QUEUE_SIZE                             4369L
#define M_SECONDARY_GRAB_BUFFER                       4370L
#define M_GRAB_FRAME_END_TIME_STAMP_BUFFER            4371L
#define M_GRAB_BUF_MODIFIED                           4372L
#define M_RGB_PIXEL_SWAP                              4373L
#define M_PREFERRED_BUFFER_FORMAT                     4374L
#define M_GRAB_IN_USER_BUFFER                         4375L
#define M_SYNCHRONIZE_GRAB_WITH_DISPLAY_REFRESH       4376L
#define M_LAST_GRAB_BUFFER_INDEX                      4377L
#define M_GRAB_LINE_COUNT                             4378L
#define M_GRAB_LINE_COUNTER                           0x0000111B //4379L
#define M_COUPLING_MODE                               4380L
#define M_LIGHTING_DARK_FIELD                         4381L
#define M_LIGHT_DARK_FIELD                            M_LIGHTING_DARK_FIELD
#define M_LIGHTING_BRIGHT_FIELD                       4382L
#define M_LIGHT_BRIGHT_FIELD                          M_LIGHTING_BRIGHT_FIELD
#define M_GRAB_TRIGGER_OVERLAP                        4383L
#define M_GRAB_TRIGGER_BUFFERING                      4384L
#define M_MILGRABC_VERSION                            4385L    // Also define as a MsysInquire

#define M_CURRENT_LINE_COUNT                          4388L
#define M_GRAB_CONTROL_OFFLOAD                        4390L
/* Reserve next 4 values                       from   4391L*/
/*                                             to     4395L*/

#define M_INPUT_SIGNAL_COLOR_LOCK                     4399L
#define M_SENSOR_RED_GAIN                             4401L
#define M_SENSOR_GREEN_GAIN                           4402L
#define M_SENSOR_BLUE_GAIN                            4403L
#define M_SENSOR_GAIN                                 4404L
#define M_GRAB_EXPOSURE_TRIGGER_MISSED                4405L
/* Reserve next 8 values                       from   4406L*/
/*                                             to     4413L*/

#define M_DECODER_MODE                                  4417L
#define M_LIGHTING_BRIGHT_FIELD_OFFSET                  4418L
#define M_LIGHTING_BRIGHT_FIELD_HIDRIVE                 4419L
#define M_LIGHTING_BRIGHT_FIELD_HIDRIVE_TIME            4420L
#define M_LIGHTING_BRIGHT_FIELD_EFFECTIVE_TIME          4421L
#define M_LIGHTING_BRIGHT_FIELD_OPTIMIZED_EXPOSURE_TIME 4422L
#define M_LIGHTING_BRIGHT_FIELD_OPTIMIZED_INTENSITY     4423L
#define M_LIGHTING_DARK_FIELD_EFFECTIVE_TIME            4424L
#define M_LIGHTING_DARK_FIELD_OPTIMIZED_EXPOSURE_TIME   4425L
#define M_LIGHTING_DARK_FIELD_OPTIMIZED_INTENSITY       4426L
#define M_DIG_OK_TO_BE_FREED                            4427L
#define M_GRAB_END_WAITS_FOR_HOOK_FUNCTION              4428L

#define M_GRAB_EXPOSURE_TRIGGER_MISSED_STATUS         4430L
/* Reserve next 8 values                       from   4431L*/
/*                                             to     4438L*/

// Rotary encoder
#define M_ROTARY_ENCODER_POSITION                     4500L
#define M_ROTARY_ENCODER_POSITION_TRIGGER             4501L
#define M_ROTARY_ENCODER_FRAME_END_POSITION           4502L
#define M_ROTARY_ENCODER_DIRECTION                    4503L
#define M_ROTARY_ENCODER_ON_GRAB_LINE                 4504L
/* Reserve next 6 values                       from   4505L*/
/*                                             to     4510L*/

// Map of UART defines, used by Mdig and Msys
#define M_UART_PARITY                                 4701L
#define M_UART_STOP_BITS                              4702L
#define M_UART_DATA_LENGTH                            4703L
#define M_UART_SPEED                                  4704L
#define M_UART_WRITE_CHAR                             4705L
#define M_UART_READ_CHAR                              4706L
#define M_UART_DATA_PENDING                           4707L
#define M_UART_WRITE_STRING                           4708L
#define M_UART_WRITE_STRING_LENGTH                    4709L
#define M_UART_READ_STRING                            4710L
#define M_UART_READ_STRING_LENGTH                     4711L
#define M_UART_READ_STRING_MAXIMUM_LENGTH             4712L
#define M_UART_STRING_DELIMITER                       4713L
#define M_UART_TIMEOUT                                4714L
#define M_UART_ERROR_MESSAGE                          4715L // internal use only
#define M_UART_OUTPUT                                 4716L
#define M_UART_THREAD_HANDLE                          4717L
#define M_UART_THREAD_ID                              4718L
#define M_UART_DATA_RECEIVED_HANDLER_PTR              4719L
#define M_UART_DATA_RECEIVED_HANDLER_USER_PTR         4720L
#define M_UART_INTERFACE_TYPE                         4721L
#define M_UART_BYTES_WRITTEN                          4722L
#define M_UART_BYTES_READ                             4723L

#define M_NATIVE_LAST_GRAB_THREAD_ID                  4750L

#define M_GRAB_ATTRIBUTE                              4800L
#define M_GRAB_CONTINUOUS_ERROR                       4801L

/* defines for 1394*/
#define M_MIN_VALUE                                   M_MIN
#define M_MAX_VALUE                                   M_MAX
#define M_MODE_CONTROL                                0x00010000L
#define M_ABSOLUTE_CTL_MASK                           0x00080000L

#define M_BRIGHTNESS                                  5100L/* Reserve all values between 5100 and 5159*/
#define M_AUTO_EXPOSURE                               5104L
#define M_SHARPNESS                                   5108L
#define M_WHITE_BALANCE                               5112L
#define M_HUE                                         0x00008000L
#define M_SATURATION                                  0x2000L
#define M_SHUTTER                                     5120L
#define M_GAIN                                        5124L
#define M_FOCUS                                       5132L
#define M_TEMPERATURE                                 5136L
#define M_TRIGGER                                     5140L
#define M_ZOOM                                        5144L
#define M_PAN                                         5148L
#define M_TILT                                        5152L
#define M_OPTICAL_FILTER                              5156L
#define M_CAPTURE_SIZE                                5160L
#define M_CAPTURE_QUALITY                             5164L
#define M_WHITE_BALANCE_U                             5168L
#define M_WHITE_BALANCE_V                             5172L
#define M_TARGET_TEMPERATURE                          5176L
/* Reserve next 3 values                       from   5177L*/
/*                                             to     5179L*/
#define M_FORMAT_SUPPORTED_NUM                        5181L
#define M_TRIGGER_SUPPORTED                           5183L
#define M_INPUT_LOW_PASS_FILTER                       5184L
#define M_PIXCLK_FREQ                                 5185L
#define M_INPUT_FILTER                                5186L
#define M_DIGITIZER_CONTROL_LOG                       5187L
#define M_TARGET_BUFFER_UPDATE                        5188L
#define M_DUMP_REGISTERS                              5189L
#define M_FORMAT7_TILE_SIZE_X                         5190L
#define M_FORMAT7_TILE_SIZE_Y                         5191L
#define M_ADVANCED_FEATURE                            0x80000000L
#define M_ADVANCED_FEATURE_SET_ID                     5192L
#define M_ADVANCED_FEATURE_UNLOCK                     5193L
#define M_CAMERA_VENDOR_ID                            5194L
// 5195 is still free
#define M_TRIGGER_DELAY                               5196L
#define M_GC_PAYLOAD_SIZE                             5197L
#define M_WHITE_SHADING                               5204L
#define M_FRAME_RATE_1394                             5208L
/* Reserve next 3 values                       from   5209L*/
/*                                             to     5211L*/

/* defines for camera link*/
#define M_CAMERALINK_CC1_SOURCE                       5200L
#define M_CAMERALINK_CC2_SOURCE                       5201L
#define M_CAMERALINK_CC3_SOURCE                       5202L
#define M_CAMERALINK_CC4_SOURCE                       5203L

/* defines for channel switch lock mechanism*/
#define M_CAMERA_LOCK                                 5300L
#define M_CAMERA_COLOR_LOCK                           5301L
#define M_CAMERA_LOCK_SENSITIVITY                     5302L
#define M_CAMERA_UNLOCK_SENSITIVITY                   5303L
#define M_CAMERA_LOCKED                               5304L
#define M_CAMERA_COLOR_LOCKED                         5305L
#define M_CAMERA_LOCK_MODE                            5306L

#define M_CAMERA_LOCK_HANDLER_PTR                     5307L
#define M_CAMERA_LOCK_HANDLER_USER_PTR                5308L
#define M_CAMERA_LOCK_THREAD_ID                       5309L
#define M_CAMERA_LOCK_THREAD_HANDLE                   5310L

/* defines for camera detect */
#define M_CAMERA_PRESENT_HANDLER_PTR                  5311L
#define M_CAMERA_PRESENT_HANDLER_USER_PTR             5312L
#define M_CAMERA_PRESENT_THREAD_ID                    5313L
#define M_CAMERA_PRESENT_THREAD_HANDLE                5314L
#define M_CAMERA_PRESENT                              5315L
#define M_CAMERA_PRESENT_SENSITIVITY                  5316L

#define M_WRITE_GRAB_VALIDATION_TAG                   5317L

#define M_INFO_FORMAT                                 5318L
#define M_HV_RESET                                    5319L
#define M_FORCE_INTERNAL_GRAB_BUFFER                  5320L
#define M_INITIALIZATION_DELAY                        5321L
#define M_MODEL_LENGTH                                5325L
#define M_BAYER_CONVERSION                            5326L
#define M_GRAB_PROCESSING                             5327L
#define M_BAYER_COEFFICIENTS_ID                       5328L
#define M_ACQUISITION_PATH                            5329L

#define M_GRAB_LL_SEQ_CONTEXT                         5330L
/* Reserve next value                                 5331L*/

/* Reserve next value                                 5332 */
#define M_PROCESS_FRAME_MISSED_RESET                  5333L
#define M_PROCESS_FRAME_MISSED                        5334L
#define M_PROCESS_FRAME_COUNT                         5335L

#define M_BUF_MODIFIED_HANDLER                        5336L

#define M_DIG_PROCESS_IN_PROGRESS                     5337L
#define M_GRAB_EXPOSURE_FORMAT                        5338L
#define M_EXPOSURE_FORMAT                             M_GRAB_EXPOSURE_FORMAT
/* Reserve next 8 values                       from   5339L*/
/*                                             to     5346L*/

#define M_GRAB_FRAME_MISSED                           5347L
#define M_FRAME_MISSED_COUNTER                        5348L
#define M_GRAB_FRAME_MISSED_RESET                     5349L

#define M_BAYER_DEMOSAICING                           5350L
#define M_PROCESS_GRAB_MONITOR                        5351L
/* Reserve next value                                 5352L */

#define M_PROCESS_NUMBER_OF_FRAME                     5353L

#define M_GRAB_TRIGGER_FORMAT                         5354L
#define M_TRIGGER_FORMAT                              M_GRAB_TRIGGER_FORMAT
/* Reserve next 8 values                       from   5355L*/
/*                                             to     5362L*/

#define M_PROCESS_TIMEOUT                             5364L
#define M_BAYER_PATTERN                               5365L

#define M_LAST_DRIVER_HOOK_CONTEXT_ID                 5366L
#define M_ROTARY_ENCODER_HANDLER_PTR                  5400L
#define M_ROTARY_ENCODER_HANDLER_USER_PTR             5401L
/* Reserve next 4  values                      from   5402*/
/*                                             to     5405L*/

#define M_MOTION_DETECT_SENSITIVITY_LEVEL             5406L
#define M_MOTION_DETECT_SPATIAL_SENSITIVITY_LEVEL     5407L
#define M_MOTION_DETECT_TEMPORAL_SENSITIVITY_LEVEL    5408L
#define M_MOTION_DETECT_VELOCITY_LEVEL                5409L
#define M_MOTION_DETECT_FIELD_SELECT                  5410L
#define M_MOTION_DETECT_MASK_BUFFER_ID                5411L
#define M_MOTION_DETECT_MATRICE_SIZE_X                5412L
#define M_MOTION_DETECT_MATRICE_SIZE_Y                5413L
#define M_MOTION_DETECT_RESULT_BUFFER_ID              5414L

#define M_BLIND_DETECT_SENSITIVITY_LEVEL              5415L
#define M_BLIND_DETECT_TEMPORAL_LEVEL                 5416L

#define M_NIGHT_DETECT_SENSITIVITY_LEVEL              5417L
#define M_NIGHT_DETECT_TEMPORAL_LEVEL                 5418L

#define M_DIG_INQUIRE_SIZEOF_DOUBLE_START             6000L
// Inquire value with a size of double, must be in that range : 6000-6699
#define M_GRAB_EXPOSURE_ARM                           6590L
/* Reserve next 8 values                       from   6591L*/
/*                                             to     6598L*/

#define M_GRAB_SCALE                                  6600L
#define M_GRAB_SCALE_X                                6601L
#define M_GRAB_SCALE_Y                                6602L
#define M_GRAB_SUBSAMPLE                              6603L
#define M_GRAB_SUBSAMPLE_X                            6604L
#define M_GRAB_SUBSAMPLE_Y                            6605L
#define M_SELECTED_FRAME_RATE                         6606L
#define M_PROCESS_FRAME_RATE                          6607L
#define M_GRAB_EXPOSURE_TIME_MAX                      6608L
#define M_GC_THEORETICAL_INTER_PACKET_DELAY           6609L
#define M_GRAB_EXPOSURE_TIME                          6610L
/* Reserve next 8 values                       from   6611L*/
/*                                             to     6618L*/
#define M_GRAB_EXPOSURE_TIME_DELAY                    6620L
/* Reserve next 8 values                       from   6621L*/
/*                                             to     6628L*/
#define M_GRAB_EXPOSURE_CLOCK_FREQUENCY               6630L
/* Reserve next 8 values                       from   6631L*/
/*                                             to     6638L*/
#define M_AUDIO_GAIN                                  6640L
#define M_AUDIO_GAIN_LEFT                             6641L
#define M_AUDIO_GAIN_RIGHT                            6642L
#define M_GRAB_ABORT                                  6643L
#define M_GRAB_FRAME_END_DELAY                        6644L
#define M_GC_FRAME_TIMESTAMP                          6645L

#define M_GRAB_EXPOSURE_ARM_SOURCE                    6650L
/* Reserve next 8 values                       from   6651L*/
/*                                             to     6658L*/
#define M_GRAB_EXPOSURE_ARM_MODE                      6660L
/* Reserve next 8 values                       from   6661L*/
/*                                             to     6668L*/

#define M_GAMMA                                       6672L
/* Reserve next 3 values                       from   6673L*/
/*                                             to     6675L*/

#define M_GRAB_EXPOSURE_TIMEOUT                       6680L
/* Reserve next 8 values                       from   6681L*/
/*                                             to     6688L*/
#define M_GRAB_EXPOSURE_MEASURED                      6690L
/* Reserve next 8 values                       from   6691L*/
/*                                             to     6698L*/

#define M_DIG_INQUIRE_SIZEOF_DOUBLE_END               6699L

#define M_DIG_INQUIRE_SIZEOF_INT64_START              6700L
// Inquire value with a size of 64 bit, must be in that range : 6700-6799
#define M_GC_MAC_ADDRESS                              6701L
#define M_GC_IP_ADDRESS                               6702L
#define M_GC_COUNTER_TICK_FREQUENCY                   6703L
#define M_GC_TOTAL_BYTES_RECEIVED                     6704L

#define M_GRAB_EXPOSURE_START                         6710L
/* Reserve next 8 values                       from   6711L*/
/*                                             to     6718L*/

#define M_GRAB_EXPOSURE_END                           6720L
/* Reserve next 8 values                       from   6721L*/
/*                                             to     6728L*/

#define M_DEFAULT_IO_DEVICE                           6730L
#define M_GC_NIC_MAC_ADDRESS                          6731L
/* Reserve next 7 values                       from   6732L*/
/*                                             to     6738L*/
#define M_GC_NIC_IP_ADDRESS                           6739L
/* Reserve next 7 values                       from   6740L*/
/*                                             to     6746L*/

#define M_DIG_INQUIRE_SIZEOF_INT64_END                6799L

#define M_DIG_INQUIRE_UNKNOWN_SIZEOF_START            6800L
// Inquire value with unknown size of,
//            and require a user array, must be in that range : 6800-6899
#define M_INTERNAL_GRAB_BUFFERS_ID                    6801L
#define M_GRAB_SCALE_X_SUPPORTED                      6802L
#define M_GRAB_SCALE_Y_SUPPORTED                      6803L
#define M_INTERNAL_GRAB_BUFFER_MIL_ID                 6804L

#define M_DIG_INQUIRE_UNKNOWN_SIZEOF_END              6899L

#define M_GC_PACKET_SIZE                              6900L
#define M_GC_HEARTBEAT                                6901L
#define M_GC_COMMAND_TIMEOUT                          6902L
#define M_GC_COMMAND_RETRY                            6903L
#define M_GC_FEATURE_BROWSER                          6905L
#define M_GC_FEATURE_NODEMAP                          6906L
#define M_GC_INTER_PACKET_DELAY                       6907L
#define M_GC_ACQUISITION_MODE                         6908L
#define M_GC_ETHERNET_LINK_SPEED                      6909L
#define M_GC_HEARTBEAT_STATE                          6910L

#define M_GC_PACKET_RESEND                            6911L
#define M_GC_STREAM_PORT                              6912L
#define M_GC_ENUM_PIXEL_FORMAT                        6913L
#define M_GC_READ_REGISTER                            6914L
#define M_GC_WRITE_REGISTER                           6915L
#define M_GC_READ_MEMORY                              6916L
#define M_GC_WRITE_MEMORY                             6917L

#define M_GC_PIXELFORMAT_SWITCHING                    6918L
/* Reserve next values                                6919L
to                                                    6920L*/

#define M_NIC_FILTERING                               6921L
#define M_CORRUPTED_FRAME                             6923L
#define M_CORRUPTED_FRAME_ERROR                       6924L
#define M_PROCESS_FRAME_CORRUPTED                     6925L
#define M_PROCESS_PENDING_GRAB_NUM                    6926L
#define M_PROCESS_TOTAL_BUFFER_NUM                    6927L

#define M_GC_STREAMING_STOP                           6928L
#define M_GC_STREAMING_STOP_CHECK_PERIOD              6929L
#define M_GC_STREAMING_STOP_DELAY                     6930L
#define M_GC_STREAMING_START                          6931L
#define M_GC_NUMBER_OF_STREAM_CHANNELS                6932L

#define M_GC_MAX_NBR_PACKETS_OUT_OF_ORDER             6943L
#define M_GC_FRAME_MAX_RETRIES                        6944L
#define M_GC_PACKET_MAX_TIMEOUT                       6945L
#define M_GC_PACKET_MAX_RETRIES                       6946L
#define M_GC_MAX_LEADING_PACKET_MISSED                6947L
#define M_GC_FRAME_TIMEOUT                            6948L
#define M_GC_PACKET_TIMEOUT                           6949L

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_GS_PACKETS_MISSED                           6950L
#define M_GS_PACKETS_COPIED                           6951L
#define M_GS_RESENDS_SENT                             6952L
#define M_GS_BYTES_COPIED                             6953L
#define M_GS_FRAMES_GRABBED                           6954L
#define M_GS_FRAMES_LOST                              6955L
#endif

#define M_GC_PACKET_TIMEOUT_NUM                       6956L
#define M_GC_PACKETS_MISSED                           6957L
#define M_GC_PACKETS_RECEIVED                         6958L
#define M_GC_PACKETS_RESENDS_NUM                      6959L
#define M_GC_PACKETS_RECOVERED                        6960L
#define M_GC_FRAME_ERROR_CODE                         6961L
#define M_GC_FRAME_LINE_COUNT                         6962L
#define M_GC_FRAME_BLOCK_ID                           6963L
#define M_GC_FRAME_BYTES_RECEIVED                     6964L
#define M_GC_FRAME_OFFSET_X                           6965L
#define M_GC_FRAME_OFFSET_Y                           6966L
#define M_GC_FRAME_SIZE_X                             6967L
#define M_GC_FRAME_SIZE_Y                             6968L
#define M_GC_FRAME_PIXEL_TYPE                         6969L
#define M_GC_TOTAL_FRAMES_GRABBED                     6970L
#define M_GC_TOTAL_FRAMES_CORRUPTED                   6971L
#define M_GC_TOTAL_PACKETS_MISSED                     6972L
#define M_GC_TOTAL_PACKETS_RECEIVED                   6973L
#define M_GC_TOTAL_PACKETS_RESENDS_NUM                6974L
#define M_GC_TOTAL_PACKETS_RECOVERED                  6975L
#define M_GC_TOTAL_PACKETS_TIMEOUT                    6976L
#define M_GC_STATISTICS_RESET                         6977L
#define M_GC_FIREWALL_PRESENT                         6978L
#define M_GC_TOTAL_PACKETS_RECEIVED_OUT_OF_ORDER      6979L

#define M_GRAB_ERROR_HALT_GRAB                        8000L
#define M_GRAB_ERROR_CHECK_PIXEL                      8001L
#define M_GRAB_ERROR_CHECK_SYNC                       8002L
#define M_GRAB_ERROR_RESET                            8003L
#define M_GRAB_ERROR_STATUS                           8004L
#define M_GRAB_ERROR_COUNT                            8005L
#define M_GAIN_AUTO_BALANCE                           8006L

#define M_VIDEO_OUTPUT                                8007L
#define M_VIDEO_OUTPUT_TILE                           8008L
#define M_VIDEO_OUTPUT_CHANNELS                       8009L
#define M_VIDEO_OUTPUT_INTERVAL                       8010L

#define M_INQUIRE_STRING_SIZE_OFFSET                  30L
#define M_DIG_INQUIRE_STRING_START                    7700L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_FORMAT                                   (7701L|M_CLIENT_ASCII_MODE)
   #define M_FORMAT_SUPPORTED                         (7702L|M_CLIENT_ASCII_MODE)
   #define M_SERIAL_NUMBER                            (7703L|M_CLIENT_ASCII_MODE)
   #define M_VENDOR                                   (7704L|M_CLIENT_ASCII_MODE)
   #define M_CAMERA_VENDOR                            M_VENDOR
   #define M_GC_VERSION                               (7705L|M_CLIENT_ASCII_MODE)
   #define M_GC_SPECIFIC_INFO                         (7706L|M_CLIENT_ASCII_MODE)
   #define M_GC_USER_NAME                             (7707L|M_CLIENT_ASCII_MODE)
   #define M_GC_SERIAL_NUMBER                         (7708|M_CLIENT_ASCII_MODE)
   #define M_NIC_DEVICE_NAME                          (7709L|M_CLIENT_ASCII_MODE)
   #define M_FORMAT_DETECTED                          (7710L|M_CLIENT_ASCII_MODE)
   #define M_CAMERA_MODEL                             (7711L|M_CLIENT_ASCII_MODE)
   #define M_GC_GET_STREAMABLE_FEATURES               (7712L|M_CLIENT_ASCII_MODE)
   /*Reserve next values      from                    ((M_DIG_INQUIRE_STRING_START+12L)|M_CLIENT_ASCII_MODE)  //7713 */
   /*                         to                      ((M_DIG_INQUIRE_STRING_START+29L)|M_CLIENT_ASCII_MODE) //7729 */   
#else
   #define M_FORMAT                                   7701L
   #define M_FORMAT_SUPPORTED                         7702L
   #define M_SERIAL_NUMBER                            7703L 
   #define M_VENDOR                                   7704L
   #define M_CAMERA_VENDOR                            M_VENDOR
   #define M_GC_VERSION                               7705L
   #define M_GC_SPECIFIC_INFO                         7706L
   #define M_GC_USER_NAME                             7707L
   #define M_GC_SERIAL_NUMBER                         7708L
   #define M_NIC_DEVICE_NAME                          7709L
   #define M_FORMAT_DETECTED                          7710L
   #define M_CAMERA_MODEL                             7711L
   #define M_GC_GET_STREAMABLE_FEATURES               7712L
   /*Reserve next values      from                    (M_DIG_INQUIRE_STRING_START+12L)  //7713 */
   /*                         to                      (M_DIG_INQUIRE_STRING_START+29L) //7729 */
   
#endif

#define M_DIG_INQUIRE_STRING_END                      (M_DIG_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1) //7729L

// 7730-7759 string size offsets
// Use M_INQUIRE_STRING_SIZE_OFFSET + inquire type
#define M_FORMAT_SIZE                                 7731L
#define M_FORMAT_SUPPORTED_SIZE                       7732L
#define M_FORMAT_SUPPORTED_LENGTH                     M_FORMAT_SUPPORTED_SIZE
#define M_SERIAL_NUMBER_SIZE                          7733L
#define M_VENDOR_SIZE                                 7734L
#define M_VENDOR_LENGTH                               M_VENDOR_SIZE
#define M_CAMERA_VENDOR_LENGTH                        M_VENDOR_SIZE
#define M_GC_VERSION_LENGTH                           7735L
#define M_GC_SPECIFIC_INFO_LENGTH                     7736L
#define M_GC_USER_NAME_LENGTH                         7737L
#define M_GC_SERIAL_NUMBER_LENGTH                     7738L
#define M_NIC_DEVICE_NAME_LENGTH                      7739L
#define M_FORMAT_DETECTED_LENGTH                      7740L
#define M_CAMERA_MODEL_LENGTH                         7741L
#define M_GC_GET_STREAMABLE_FEATURES_LENGTH           7742L
/*Reserve next values      from                       (M_DIG_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+4)  //7741L */
/*                         to                         (M_DIG_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+29) //7759L */

#define M_AUDIO_CONTROL                               8010L
#define M_AUDIO_ENCODING_FORMAT                       8011L
#define M_AUDIO_CHANNEL_MODE                          8012L
#define M_AUDIO_SAMPLING_RATE                         8013L
#define M_AUDIO_VOLUME                                8014L
#define M_AUDIO_VOLUME_LEFT                           8015L
#define M_AUDIO_VOLUME_RIGHT                          8016L
#define M_AUDIO_BUFFERING_SIZE                        8017L

/* Reserve 3 values for M_SATURATION           from   8192*/
/*                                             to     8195*/

#define M_HOOK_EVENT_BACKDOOR_INTERNAL                0x4444L // 17476
#define M_HOOK_CANCEL_EVENT_BACKDOOR_INTERNAL         0x4464L // 17508




/* Reserve 3 values for M_HUE                  from   32768*/
/*                                             to     32771*/
#define M_MODEL                                       0x00010000L   //65536

#define M_START_REGISTER_ADDRESS                   MIL_MAKE_CONST(0xF0000000L,0x00000000F0000000)
/*Reserve the values between 0xF000000 and 0xF0FFFFFF for 1394*/
#define M_END_REGISTER_ADDRESS                     MIL_MAKE_CONST(0xF0FFFFFFL,0x00000000F0FFFFFF) 

// !!! MAP FOR OLD DEFINES
#if OldDefinesSupport
#define M_DIG_TYPE                                    M_TYPE
#define M_DIG_NUMBER                                  M_NUMBER
#define M_DIG_FORMAT                                  M_FORMAT
#define M_DIG_INIT_FLAG                               M_INIT_FLAG
#define M_DIG_CHANNEL_NUM                             M_CHANNEL_NUM

#define M_DIG_REF_BLACK                               M_BLACK_REF
#define M_DIG_REF_WHITE                               M_WHITE_REF
#define M_DIG_REF_HUE                                 M_HUE_REF
#define M_DIG_REF_SATURATION                          M_SATURATION_REF
#define M_DIG_REF_BRIGHTNESS                          M_BRIGHTNESS_REF
#define M_DIG_REF_CONTRAST                            M_CONTRAST_REF
#define M_DIG_BLACK_REF                               M_BLACK_REF
#define M_DIG_WHITE_REF                               M_WHITE_REF
#define M_DIG_HUE_REF                                 M_HUE_REF
#define M_DIG_SATURATION_REF                          M_SATURATION_REF
#define M_DIG_BRIGHTNESS_REF                          M_BRIGHTNESS_REF
#define M_DIG_CONTRAST_REF                            M_CONTRAST_REF
#define M_DIG_INPUT_MODE                              M_INPUT_MODE
#define M_DIG_GRAB_SCALE                              M_GRAB_SCALE
#define M_DIG_GRAB_SCALE_X                            M_GRAB_SCALE_X
#define M_DIG_GRAB_SCALE_Y                            M_GRAB_SCALE_Y
#define M_DIG_GRAB_SUBSAMPLE                          M_GRAB_SUBSAMPLE
#define M_DIG_GRAB_SUBSAMPLE_X                        M_GRAB_SUBSAMPLE_X
#define M_DIG_GRAB_SUBSAMPLE_Y                        M_GRAB_SUBSAMPLE_Y
#define M_DIG_GRAB_MODE                               M_GRAB_MODE
#define M_DIG_GRAB_FRAME_NUM                          M_GRAB_FRAME_NUM
#define M_DIG_GRAB_FIELD_NUM                          M_GRAB_FIELD_NUM
#define M_DIG_SOURCE_SIZE_X                           M_SOURCE_SIZE_X
#define M_DIG_SOURCE_SIZE_Y                           M_SOURCE_SIZE_Y
#define M_DIG_SOURCE_OFFSET_X                         M_SOURCE_OFFSET_X
#define M_DIG_SOURCE_OFFSET_Y                         M_SOURCE_OFFSET_Y
#define M_DIG_USER_BIT                                M_USER_BIT
#define M_DIG_INPUT_SIGNAL_PRESENT                    M_INPUT_SIGNAL_PRESENT
#define M_DIG_INPUT_SIGNAL_SOURCE                     M_INPUT_SIGNAL_SOURCE

#define M_DIG_FORMAT_UPDATE                           M_FORMAT_UPDATE
#define M_DIG_CLIP_SRC_SUPPORTED                      M_CLIP_SRC_SUPPORTED
#define M_DIG_CLIP_DST_SUPPORTED                      M_CLIP_DST_SUPPORTED
#define M_DIG_HOOK_FUNCTION_SUPPORTED                 M_HOOK_FUNCTION_SUPPORTED
#define M_GRAB_INTERLACED_MODE                        M_SCAN_MODE
#define M_GRAB_THREAD_PRIORITY                        M_THREAD_PRIORITY
#define M_HOOK_PRIORITY                               M_THREAD_PRIORITY
#define M_GRAB_WINDOWS_RANGE                          M_GRAB_WINDOW_RANGE
#define M_GRAB_WINDOWS_RANGE_SUPPORTED                M_GRAB_WINDOW_RANGE_SUPPORTED

#define M_HW_TRIGGER                                  M_HARDWARE_PORT0
#define M_SW_TRIGGER                                  M_SOFTWARE
#define M_VSYNC_TRIGGER                               M_VSYNC
#define M_HSYNC_TRIGGER                               M_HSYNC
#define M_USER_BIT_SOURCE                             M_AUX_SIGNAL_SOURCE

#endif

// List of defines for CLLjpegControl
//==============================================================================
#define M_LOSSY                                          1L
#define M_AUTO_BIT_RATE_CONTROL                          2L
#define M_STATISTICAL                                    3L
#define M_BIT_RATE_CONTROL                               4L
#define M_TABLES_ONLY                                    5L
#define M_TABLES_PRELOAD                                 6L
#define M_LOSSLESS                                       7L
#define M_FAST_PREVIEW                                   8L

#define M_APP                                         0x00000001L
#define M_COM                                         0x00000002L
#define M_DRI                                         0x00000004L
#define M_DQT                                         0x00000008L
#define M_DHT                                         0x00000010L
#define M_DNL                                         0x00000020L
#define M_DQTI                                        0x00000040L
#define M_DHTI                                        0x00000080L

#define M_NSCN_1                                         0L
#define M_NSCN_2                                         1L
#define M_NSCN_3                                         2L
#define M_NSCN_4                                         3L
#define M_NSCN_5                                         4L
#define M_NSCN_6                                         5L
#define M_NSCN_7                                         6L
#define M_NSCN_8                                         7L

/* Inquire Values */
#define M_DIGITAL                                     0L
#define M_ANALOG                                      1L
#define M_INTERLACE                                   0L
#define M_PROGRESSIVE                                 1L
#define M_LINESCAN                                    2L
#define M_DEINTERLACE                                 3L
#define M_ACTIVATE                                    1L

/* Inquire Values for the color mode */
#define M_MONOCHROME                                  0L
#define M_COMPOSITE                                   1L
#define M_RGB                                         8L
#define M_YUV                                         4L
#define M_EXTERNAL_CHROMINANCE                        4137L
#define M_MONO8_VIA_RGB                               M_MONO32
#define M_SEPARATE                                    0x8000L

/************************************************************************/
/* Board types                                                          */
/************************************************************************/
#define M_BOARD_TYPE_MASK                             0x000000FFL

// Radient board type
#define M_RADIENT                                     10L

// Corona board type
#define M_CORONA                                      20L
#define M_CORONA_LC                                   21L
#define M_CORONA_VIA                                  22L
#define M_CORONA_RR                                   23L
#define M_METEOR_II_MC                                24L
#define M_CORONA_II                                   25L
#define M_METEOR_II                                   27L
#define M_METEOR_II_STD                               M_METEOR_II
#define M_CORONA_II_WITH_DIG_MODULE                   (M_CORONA_II|M_DIGITAL_MODULE)

// Genesis board type
#define M_METEOR_II_DIG                               33L
#define M_METEOR_II_CL                                35L
#define M_ODYSSEY                                     36L
#define M_ODYSSEY_NATIVE                              37L

/* Free for future board type                         40L*/

// 1394 board type
#define M_IEEE_1394_IIDC                              50L
#define M_NON_MATROX_OHCI_BOARD                       M_IEEE_1394_IIDC

/* Free for future board type                         60L*/

// CronosPlus board type
#define M_CRONOSPLUS                                  70L

// Helios board type
#define M_HELIOS                                      80L

// Morphis Board type
#define M_MORPHIS                                     90L

// Host board type
#define M_HOST                                       100L

/* Free for future board type                        110L*/

// Solios board type
#define M_SOLIOS                                     120L

// Nexis board type
#define M_NEXIS                                      130L

// MtxAuxIo
#define M_MTXAUXILIARY                               140L

// Vio board type
#define M_VIO                                        150L

// Iris board type
#define M_IRIS                                       160L

// MorphisQxt board type
#define M_MORPHISQXT                                 170L

// GigeVision board type
#define M_GIGE_VISION                                180L

// GPU board type
#define M_GPU                                        190L

// SoliosGigE board type
#define M_SOLIOS_GIGE                                200L

/* Free for future board type                        210L*/

// Morphis Evo board type
#define M_MORPHIS_EVO                                220L

// Iris Gt board type
#define M_IRIS_GT                                    230L
#define M_IRIS_GT_DUAL                               231L
#define M_NEXIS2                                     232L

#define M_ORION_HD                                   240L

/* Free for future board type                        250L*/




// Corona and Genesis module type.
#define M_DIGITAL_MODULE                              0x00000100L

// Helios, Solios, Odyssey, Radient module type.
#define M_XPRO_PLUS                                   0x00000400L
#define M_XCL                                         0x00000800L
#define M_CL                                          M_XCL
#define M_XA                                          0x00001000L
#define M_XPRO                                        0x00002000L
#define M_XD                                          0x00008000L
#define M_QBCL                                        0x04000000L // Quad Base CL
#define M_SBCL                                        0x08000000L // Single Base CL
#define M_QHA                                         0x00100000L // Quad High freq. Analog
#define M_SFCL                                        0x00200000L // Single Full CL
#define M_DBCL                                        0x00400000L // Dual Base CL
#define M_QD                                          0x00800000L // Quad Digital
#define M_DA                                          0x00010000L // Dual Analog
#define M_QA                                          0x00020000L // Quad Analog
#define M_SA                                          0x00040000L // Single Analog
#define M_SMCL                                        0x00080000L // Single Medium CL
#define M_DFCL                                        0x00004000L // Dual Full CL
#define M_PF                                          0x01000000L // Processing fpga installed
// Solios only.
#define M_FAST                                        0x00002000L

// SoliosGige module type.
#define M_SCH                                         0x00010000L
#define M_DCH                                         0x00020000L
#define M_TCH                                         0x00040000L
#define M_QCH                                         0x00080000L
#define M_PF                                          0x01000000L // Processing fpga installed

// Morphis and MorphisQxT module type.
#define M_1VD                                         0x00004000L
#define M_2VD                                         0x00008000L
#define M_IO                                          0x00010000L
#define M_4VD                                         0x00020000L
#define M_16VD                                        0x00040000L
#define M_J2K                                         0x00000200L
#define M_JPEG2000                                    M_J2K
#define M_COMPRESSION                                 0x00080000L
#define M_AUDIO_MODULE                                0x00100000L

// Vio module type.
#define M_SDI                                         0x00001000L // Serial Digital Interface
#define M_SA                                          0x00040000L // Single Analog
#define M_DVI                                         0x00100000L // DVI Analog

// 1394 module type.
#define M_METEOR_II_1394                              0x00000100L
#define M_4SIGHT                                      0x00000200L
#define M_4SIGHT_II                                   0x00000400L
#define M_PC104                                       0x00000800L
#define M_CONCORD                                     0x00001000L
#define M_4SIGHT_X                                    0x00002000L

// Iris Camera type
// Suggested format:
// 23:21 0
// 20    Remote 1/Non remote 0
// 19:12 P300 03, P700 07, P1200 12
// 11    Mini head 1/Normal head 0
// 10    High Speed 1/Normal 0
// 9     E model 1/P model 0/GT model 0
// 8     Color 1/Mono 0
// 7:0   0
#define M_P300                                        0x003000L
#define M_P300C                                       0x003100L
#define M_E300                                        0x003200L
#define M_E300C                                       0x003300L
#define M_P300H                                       0x003400L
#define M_E300H                                       0x003600L
#define M_P300HM                                      0x003C00L
#define M_E300HM                                      0x003E00L
#define M_P300R                                       0x103000L
#define M_P300CR                                      0x103100L
#define M_E300R                                       0x103200L
#define M_E300CR                                      0x103300L
#define M_P300HR                                      0x103400L
#define M_E300HR                                      0x103600L
#define M_P300HMR                                     0x103C00L
#define M_E300HMR                                     0x103E00L
#define M_P700                                        0x007000L
#define M_E700                                        0x007200L
#define M_P700W                                       0x007300L
#define M_E700W                                       0x007400L
#define M_P700R                                       0x107000L
#define M_E700R                                       0x107200L
#define M_P700WR                                      0x107300L
#define M_E700WR                                      0x107400L
#define M_P1200                                       0x012000L
#define M_E1200                                       0x012200L
#define M_P1200R                                      0x112000L
#define M_E1200R                                      0x112200L
#define M_P1200H                                      0x013000L
#define M_E1200H                                      0x013200L
#define M_P1200HR                                     0x113000L
#define M_E1200HR                                     0x113200L
#define M_P1200HM                                     0x012C00L
#define M_E1200HM                                     0x012E00L
#define M_P1200HMR                                    0x112C00L
#define M_E1200HMR                                    0x112E00L

// Iris Camera type - For compatibility before define renamed
#define P300                                          M_P300   
#define P300C                                         M_P300C  
#define E300                                          M_E300   
#define E300C                                         M_E300C  
#define P300H                                         M_P300H  
#define E300H                                         M_E300H  
#define P300HM                                        M_P300HM 
#define E300HM                                        M_E300HM 
#define P300R                                         M_P300R  
#define P300CR                                        M_P300CR 
#define E300R                                         M_E300R  
#define E300CR                                        M_E300CR 
#define P300HR                                        M_P300HR 
#define E300HR                                        M_E300HR 
#define P300HMR                                       M_P300HMR
#define E300HMR                                       M_E300HMR
#define P700                                          M_P700   
#define E700                                          M_E700   
#define P700W                                         M_P700W  
#define E700W                                         M_E700W  
#define P700R                                         M_P700R  
#define E700R                                         M_E700R  
#define P700WR                                        M_P700WR 
#define E700WR                                        M_E700WR 
#define P1200                                         M_P1200  
#define E1200                                         M_E1200  
#define P1200R                                        M_P1200R 
#define E1200R                                        M_E1200R 
#define P1200H                                        M_P1200H  
#define E1200H                                        M_E1200H  
#define P1200HR                                       M_P1200HR 
#define E1200HR                                       M_E1200HR 
#define P1200HM                                       M_P1200HM  
#define E1200HM                                       M_E1200HM  
#define P1200HMR                                      M_P1200HMR 
#define E1200HMR                                      M_E1200HMR 

// Nexis Camera type
#define M_S300T                                       M_P300R
#define M_S300CT                                      M_P300CR
#define M_S300HT                                      M_P300HR
#define M_S300HM                                      M_P300HMR
#define M_S700T                                       M_P700R
#define M_S1200T                                      M_P1200R
#define M_S1200HT                                     M_P1200HR
#define M_S1200HM                                     M_P1200HMR

// Iris GT camera type
#define M_GT300                                       0x00001000
#define M_GT1200                                      0x04001000
#define M_GT1900                                      0x08001000
#define M_GT300C                                      0x80001000
#define M_GT1200C                                     0x84001000
#define M_GT1900C                                     0x88001000


/************************************************************************/
/* MdigControl() / MdigInquire() Values                                 */
/************************************************************************/
#define M_WEIGHTED                                    2L
#define M_CONTINUOUS                                 -1L
#define M_ONCE                                        3L
#define M_SINGLE_FRAME                                1L

#define M_TIMER1                                      1L
#define M_TIMER2                                      2L
#define M_TIMER3                                      3L
#define M_TIMER4                                      4L
#define M_TIMER5                                      5L
#define M_TIMER6                                      6L
#define M_TIMER7                                      7L
#define M_TIMER8                                      8L

#define M_TIMER_IO                                    M_TIMER2

#define M_LOW                                         1L
#define M_HIGH                                        3L

#define M_ARM_CONTINUOUS                              9L
#define M_ARM_MONOSHOT                                10L
#define M_ARM_RESET                                   11L
#define M_EDGE_RISING                                 12L
#define M_EDGE_FALLING                                13L
#define M_LEVEL_LOW                                   14L
#define M_LEVEL_HIGH                                  15L
#define M_HARDWARE_PORT0                              16L
#define M_HARDWARE_PORT1                              17L
#define M_HARDWARE_PORT_CAMERA                        18L
#define M_START_EXPOSURE                              19L
#define M_SOFTWARE                                    20L
#define M_USER_DEFINED                                21L
#define M_HSYNC                                       22L
#define M_VSYNC                                       23L
#define M_HARDWARE_PORT2                              24L
#define M_HARDWARE_PORT3                              25L
#define M_SYSCLK                                      26L
#define M_PIXCLK                                      27L
#define M_URGENT                                      28L
#define M_NOW                                         29L
#define M_FRAME                                       30L
#define M_HARDWARE_PORT4                              31L
#define M_HARDWARE_PORT5                              32L
#define M_HARDWARE_PORT6                              33L
#define M_HARDWARE_PORT7                              34L
#define M_HARDWARE_PORT8                              35L
#define M_HARDWARE_PORT9                              36L
#define M_HARDWARE_PORT10                             37L
#define M_HARDWARE_PORT11                             38L
#define M_HARDWARE_PORT12                             39L
#define M_HARDWARE_PORT13                             40L
#define M_HARDWARE_PORT14                             41L
#define M_HARDWARE_PORT15                             42L
#define M_USER_BIT_CC_A                               43L
#define M_USER_BIT_CC_B                               44L
#define M_CC_OUTPUT_A                                 M_USER_BIT_CC_A
#define M_CC_OUTPUT_B                                 M_USER_BIT_CC_B
#define M_ROTARY_ENCODER                              45L
#define M_CLOCK0                                      46L
#define M_CLOCK1                                      47L
#define M_CLOCK2                                      48L
#define M_CLOCK3                                      49L
#define M_CLOCK4                                      50L
#define M_CLOCK5                                      51L
#define M_CLOCK6                                      52L
#define M_CLOCK7                                      53L
#define M_CLOCK8                                      54L
#define M_CLOCK9                                      55L
#define M_CLOCK10                                     56L
#define M_CLOCK11                                     57L
#define M_CLOCK12                                     58L
#define M_CLOCK13                                     59L
#define M_CLOCK14                                     60L
#define M_CLOCK15                                     61L
#define M_CLOCK16                                     62L
#define M_LEVEL_LOW_END_WHEN_INACTIVE                 63L
#define M_LEVEL_HIGH_END_WHEN_INACTIVE                64L
#define M_PULSE_GENERATION                            65L
#define M_PULSE_MEASUREMENT                           66L
#define M_PERIOD_MEASUREMENT                          67L
#define M_HARDWARE_PORT16                             68L
#define M_HARDWARE_PORT17                             69L
#define M_HARDWARE_PORT18                             70L
#define M_HARDWARE_PORT19                             71L
#define M_HARDWARE_PORT20                             72L
#define M_HARDWARE_PORT21                             73L
#define M_HARDWARE_PORT22                             74L
#define M_HARDWARE_PORT23                             75L
#define M_HARDWARE_PORT24                             76L
#define M_HARDWARE_PORT25                             77L
#define M_HARDWARE_PORT26                             78L
#define M_HARDWARE_PORT27                             79L
#define M_HARDWARE_PORT28                             80L
#define M_HARDWARE_PORT29                             81L
#define M_HARDWARE_PORT30                             82L
#define M_HARDWARE_PORT31                             83L

#define M_1394_MODE_MASK                              0x001F0000
#define M_1394_MODE0                                  0x00100000
#define M_1394_MODE1                                  0x00110000
#define M_1394_MODE2                                  0x00120000
#define M_1394_MODE3                                  0x00130000
#define M_1394_MODE4                                  0x00140000
#define M_1394_MODE5                                  0x00150000
#define M_1394_MODE14                                 0x001E0000
#define M_1394_MODE15                                 0x001F0000

#define M_FILL_DESTINATION                            -1
#define M_FILL_DISPLAY                                -2

#define M_SYNCHRONOUS                                 0x00000001L
#define M_ASYNCHRONOUS                                0x00000002L

#define M_ASYNCHRONOUS_QUEUED                         3L

#define M_LUT_PALETTE0                                0L
#define M_LUT_PALETTE1                                1L
#define M_LUT_PALETTE2                                2L
#define M_LUT_PALETTE3                                3L
#define M_LUT_PALETTE4                                4L
#define M_LUT_PALETTE5                                5L
#define M_LUT_PALETTE6                                6L
#define M_LUT_PALETTE7                                7L

#define M_GAIN0                                       0x00010000L
#define M_GAIN1                                       0x00010001L
#define M_GAIN2                                       0x00010002L
#define M_GAIN3                                       0x00010003L
#define M_GAIN4                                       0x00010004L

#define M_OPTO                                        0L
#define M_TTL                                         1L
#define M_RS422                                       2L
#define M_LVDS                                        M_RS422
#define M_TRI_STATE                                   3L
#define M_NO_CONNECT                                  4L

#define M_ENABLE                                      -9997L
#define M_FINAL_GRAB                                  -9998L
#define M_DISABLE                                     -9999L

// M_DECODER_MODE
#define M_ADV7183                                     1L
#define M_ADV7184                                     2L


// M_CAMERA_LOCK
#define M_ENABLE                                      -9997L
#define M_FAST                                   0x00002000L

// Uart parity values
#define M_ODD                                         1L
#define M_EVEN                                        2L

#define M_RS232                                       1L
#define M_RS485                                       2L

#define M_CALCULATE                                   1L

// M_GRAB_ABORT
#define M_IMMEDIATE                                  10L
#define M_NEXT_FRAMES                                11L

// M_GRAB_ERROR_STATUS
#define M_PIXEL_ERROR                                 1L
#define M_HSYNC_ERROR                                 2L
#define M_VSYNC_ERROR                                 4L

// M_AUDIO_ENCODING_FORMAT
#define M_AUDIO_RAW_16                                1L
#define M_AUDIO_ADPCM                                 2L
#define M_AUDIO_MULAW                                 3L
#define M_AUDIO_ALAW                                  4L

// M_AUDIO_CHANNEL_MODE
#define M_AUDIO_MONO                                  1L
#define M_AUDIO_STEREO                                2L

#define M_AUTOMATIC                                   0x00020000L //Must be bitwise with M_CH0_REF-M_CH7_REF AND M_BLACK_REF AND M_WHITE_REF
#define M_MANUAL                                      1L


/************************************************************************/
/* MdigControl(): Grab VM stream ID                                     */
/************************************************************************/
#define M_VM_STREAM_ID_0                              0L
#define M_VM_STREAM_ID_1                              1L
#define M_VM_STREAM_ID_2                              2L
#define M_VM_STREAM_ID_3                              3L
#define M_VM_STREAM_ID_4                              4L
#define M_VM_STREAM_ID_5                              5L
#define M_VM_STREAM_ID_6                              6L
#define M_VM_STREAM_ID_7                              7L
#define M_VM_STREAM_ID_8                              8L
#define M_VM_STREAM_ID_9                              9L
#define M_VM_STREAM_ID_10                            10L
#define M_VM_STREAM_ID_11                            11L
#define M_VM_STREAM_ID_12                            12L
#define M_VM_STREAM_ID_13                            13L
#define M_VM_STREAM_ID_14                            14L


/************************************************************************/
/* MdigControl(): Type of dialog for M_GENICAM_INTERACTIVE              */
/************************************************************************/
#define M_GENICAM_INTERACTIVE_MODAL_DIALOG           15L
#define M_GENICAM_INTERACTIVE_MODELESS_DIALOG        16L


/************************************************************************/
/* MdigChannel()                                                        */
/************************************************************************/
#define M_DEFAULT                                     0x10000000L
#define M_CH0                                         0x40000000L
#define M_CH1                                         0x20000000L
#define M_CH2                                         0x08000000L
#define M_CH3                                         0x01000000L
#define M_CH4                                         0x02000000L
#define M_CH5                                         0x04000000L
#define M_CH6                                         0x00800000L
#define M_CH7                                         0x00400000L
#define M_CH8                                         0x00200000L
#define M_CH9                                         0x00100000L
#define M_CH10                                        0x00080000L
#define M_CH11                                        0x00040000L
#define M_CH12                                        0x00020000L
#define M_CH13                                        0x00010000L
#define M_CH14                                        0x00008000L
#define M_CH15                                        0x00004000L
#define M_AUTOMATIC                                   0x00020000L //Must be bitwise with M_CH0_REF-M_CH7_REF AND M_BLACK_REF AND M_WHITE_REF
#define M_VOLTAGE                                     0x00010000L //Must be bitwise with M_CH0_REF-M_CH7_REF AND M_BLACK_REF AND M_WHITE_REF
#define M_SYNC                                        0x00002000L
#define M_SIGNAL                                      0x00001000L
#define M_AC                                          0x00000004L
#define M_DC                                          0x00000002L
#define M_CHANNEL_COLOR                               0x00000001L
#define M_RGB                                         8L
#define M_YC                                          9L
#define M_ALL_CHANNEL                                 (M_CH0|M_CH1|M_CH2|M_CH3|M_CH4|M_CH5|M_CH6|M_CH7|M_CH8|M_CH9|M_CH10|M_CH11|M_CH12|M_CH13|M_CH14|M_CH15)
#define M_ALL_CHANNELS                                M_ALL_CHANNEL

/************************************************************************/
/* MdigLut()                                                            */
/************************************************************************/
#define M_DEFAULT_LUT                                 (M_PSEUDO_ID+1)

/************************************************************************/
/* MdigReference()                                                      */
/************************************************************************/
#define M_BLACK                                       0L
#define M_WHITE                                       1L
#define M_STEREO                                      0L
#define M_MONO                                        1L

/* See the Inquire for the M_CHx values */
#define M_CH0_REF                                     M_CH0
#define M_CH1_REF                                     M_CH1
#define M_CH2_REF                                     M_CH2
#define M_CH3_REF                                     M_CH3
#define M_CH4_REF                                     M_CH4
#define M_CH5_REF                                     M_CH5
#define M_CH6_REF                                     M_CH6
#define M_CH7_REF                                     M_CH7
#define M_ALL_REF                                     (M_CH0_REF | M_CH1_REF | M_CH2_REF | M_CH3_REF | M_CH4_REF | M_CH5_REF | M_CH6_REF | M_CH7_REF)
#define M_VOLTAGE                                     0x00010000L //Must be bitwise with M_CH0_REF-M_CH7_REF AND M_BLACK_REF AND M_WHITE_REF
#define M_AUTOMATIC                                   0x00020000L //Must be bitwise with M_CH0_REF-M_CH7_REF AND M_BLACK_REF AND M_WHITE_REF
#define M_MIN_LEVEL                                   0L
#define M_MAX_LEVEL                                   255L

/************************************************************************/
/* MdigFocus()                                                          */
/************************************************************************/
#define M_METHOD_1         0x1000
#define M_METHOD_2         0x2000
#define M_NO_FILTER        0x00080000L
#define M_NO_SUBSAMPLING   0x00100000L
#define M_SMART_SCAN       0x00200000L
#define M_SCAN_ALL         0x00400000L
#define M_BISECTION        0x00800000L
#define M_REFOCUS          0x01000000L
#define M_EVALUATE         0x02000000L
#define M_CHANGE           0x00000063L
#define M_ON_FOCUS         0x00000064L
#define M_STOP_FOCUS       0x00000002L

/************************************************************************/
/* MdigGrabWait()                                                       */
/************************************************************************/
#define M_GRAB_NEXT_FRAME                             1L
#define M_GRAB_NEXT_FIELD                             2L
#define M_GRAB_END                                    3L


/************************************************************************/
/* MdigHookFunction()                                                   */
/************************************************************************/
#define M_BOARD_HOOK                                  0x01000000L
#define M_CAMERA_HOOK                                 0x02000000L
#define M_FIRST                                       0x10000000L
#define M_LAST                                        0x20000000L
#define M_UNHOOK                                      0x04000000L
#define M_GC_EVENT                                    0x00400000L

#define M_GRAB_END                                    3L
#define M_GRAB_START                                  4L
#define M_GRAB_FRAME_END                              5L
#define M_GRAB_FIELD_END_ODD                          6L
#define M_GRAB_FIELD_END_EVEN                         7L
#define M_GRAB_FIELD_END                              8L
#define M_FRAME_START                                 9L
#define M_FIELD_START                                 20L
#define M_FIELD_START_ODD                             21L
#define M_FIELD_START_EVEN                            22L
#define M_GRAB_FRAME_START                            13L
#define M_GRAB_FIELD_START                            14L
#define M_GRAB_FIELD_START_ODD                        15L
#define M_GRAB_FIELD_START_EVEN                       16L
#define M_UART_DATA_RECEIVED                          17L
#define M_ROTARY_ENCODER                              45L
#define M_GRAB_LINE                                   0x00100000L
#define M_GRAB_LINE_END                               0x00200000L
#define M_DCF_REALLOC                                 0x00000020L
#define M_CAMERA_LOCK                                 5300L
#define M_CAMERA_PRESENT                              5315L
#define M_NIGHT_DETECT                                23L
#define M_BLIND_DETECT                                24L
#define M_MOTION_DETECT                               25L
#define M_EXPOSURE_START                              26L
/* Reserve next 8 values                       from   27L*/
/*                                             to     34L*/
#define M_EXPOSURE_END                                35L
/* Reserve next 8 values                       from   36L*/
/*                                             to     43L*/

/************************  Values that can be added to M_GC_EVENT*/
#define M_ACQUISITION_TRIGGER                         0x00000011L
#define M_ACQUISITION_START                           0x00000012L
#define M_ACQUISITION_END                             0x00000013L
#define M_ACQUISITION_TRANSFER_START                  0x00000014L
#define M_ACQUISITION_TRANSFER_END                    0x00000015L
#define M_ACQUISITION_ERROR                           0x00008010L
#define M_FRAME_TRIGGER                               0x00000002L
//#define M_FRAME_START                               0x00000009L
#define M_FRAME_END                                   0x0000000aL
#define M_FRAME_TRANSFER_START                        0x00000005L
#define M_FRAME_TRANSFER_END                          0x00000006L
//#define M_EXPOSURE_START                            0x0000001aL //26L
//#define M_EXPOSURE_END                              0x00000023L //35L

/**  Counter/timer indices that are added should start from one!*/
#define M_GC_NUMBERED_EVENTS_MASK                     0x000000FFL
#define M_GC_IS_NUMBERED_EVENT(a)                     (a&(M_COUNTER_START|M_COUNTER_END|M_TIMER_START|M_TIMER_END|M_LINE_RISING_EDGE|M_LINE_FALLING_EDGE|M_LINE_ANY_EDGE))
#define M_COUNTER_START                               0x00000100L
#define M_COUNTER_END                                 0x00000200L
#define M_TIMER_START                                 0x00000300L
#define M_TIMER_END                                   0x00000400L

/************************************   Line numbers are 0 or 1-based*/
#define M_LINE_RISING_EDGE                            0x00000500L
#define M_LINE_FALLING_EDGE                           0x00000600L
#define M_LINE_ANY_EDGE                               0x00000700L

/********************************************  Error event types*/
//#define M_ERROR                                     0x40000000L
#define M_ERROR_NOT_IMPLEMENTED                       0x00008001L
#define M_ERROR_INVALID_PARAMETER                     0x00008002L
#define M_ERROR_INVALID_ADDRESS                       0x00008003L
#define M_ERROR_WRITE_PROTECTED                       0x00008004L
#define M_ERROR_BAD_ALIGNMENT                         0x00008005L
#define M_ERROR_ACCESS_DENIED                         0x00008006L
#define M_ERROR_BUSY                                  0x00008007L
#define M_ERROR_LOCAL_PROBLEM                         0x00008008L
#define M_ERROR_MSG_MISMATCH                          0x00008009L
#define M_ERROR_INVALID_PROTOCOL                      0x0000800AL
#define M_ERROR_NO_MSG                                0x0000800BL
#define M_ERROR_PACKET_UNAVAILABLE                    0x0000800CL
#define M_ERROR_DATA_OVERRUN                          0x0000800DL
#define M_ERROR_INVALID_HEADER                        0x0000800EL
#define M_ERROR_WRONG_CONFIG                          0x0000800FL
#define M_ERROR_PACKET_NOT_YET_AVAILABLE              0x00008010L
#define M_ERROR_PACKET_AND_PREV_REMOVED_FROM_MEMORY   0x00008011L
#define M_ERROR_PACKET_REMOVED_FROM_MEMORY            0x00008012L
#define M_ERROR_GENERIC_ERROR                         0x00008FFFL

#define M_DEVICE_SPECIFIC_EVENT                       0x00009000L

/************************************************************************/
/* MdigProcess()                                                        */
/************************************************************************/

#define M_DIG_PRCSS_COUNT_SHIFT                       0x00000005L

/* Operation bitwise parameters */
#define M_WAIT                                        1L
#define M_START                                       0x00000002L
#define M_STOP                                        0x00000004L
#define M_SEQUENCE                                    0x00000008L
#define M_TRIGGER_FOR_FIRST_GRAB                      0x00000010L
// Reserve bit 0x00000010L
#define M_COUNT(n)                                    ((unsigned long)(n << M_DIG_PRCSS_COUNT_SHIFT))
#define M_FRAMES_PER_TRIGGER(n)                       M_COUNT(n)

/************************************************************************/
/* MdigGetHookInfo()                                                    */
/************************************************************************/
#define M_ASYNC_HOOK                                  0x08000000L
#define M_MODIFIED_BUFFER                             0x40000000L

#define M_BUFFER_ID                                   0x00160000L
#define M_REGION_OFFSET_X                             0x00410000L
#define M_REGION_OFFSET_Y                             0x00420000L
#define M_REGION_SIZE_X                               0x00430000L
#define M_REGION_SIZE_Y                               0x00480000L
#define M_BUFFER_INDEX                                0x001B0000L
#define M_DIGITIZER_ID                                0x001C0000L
#define M_DRIVER_HOOK_CONTEXT_PTR                     0x001D0000L
#define M_GRAB_LINE                                   0x00100000L
#define M_GRAB_LINE_END                               0x00200000L
#define M_GC_CAMERA_TIME_STAMP                        0x00400000L
#define M_GC_EVENT_DATA                               0x00800000L
#define M_GC_EVENT_TYPE                               0x00810000L
#define M_GC_EVENT_DATA_SIZE                          0x00820000L
#define M_GRAB_TIME_STAMP                             0x00000040L //64L
#define M_TIME_STAMP                                  M_GRAB_TIME_STAMP
#define M_GRAB_LINE_COUNTER                           0x0000111B //4379L
#define M_USER_DATA_PTR                               0x00000001
#define M_CORRUPT                                     0x01000000L
#define M_COUNTER_INDEX                               0x00830000L
#define M_TIMER_INDEX                                 0x00840000L
#define M_LINE_INDEX                                  0x00850000L


/************************************************************************/
/* MdigInquireFeature() / MdigControlFeature ControlFlag                */
/************************************************************************/
#define M_DEFAULT                                     0x10000000L
#define M_MIN                                         0x02000000L
#define M_MAX                                         0x04000000L
#define M_LENGTH                                      0x00002000L
#define M_INCREMENT                                   1L
#define M_ELEMENT_COUNT                               0x01000000L
#define M_ELEMENT                                     0x08000000L
#define M_GC_READ_REGISTER                            6914L //0x00001b02
#define M_GC_WRITE_REGISTER                           6915L //0x00001b03
#define M_GC_READ_MEMORY                              6916L //0x00001b04
#define M_GC_WRITE_MEMORY                             6917L //0x00001b05

/************************************************************************/
/* MgenLutFunction()                                                    */
/************************************************************************/
#define M_LOG                                         0x00000000L
#define M_EXP                                         0x00000001L
#define M_SIN                                         0x00000002L
#define M_COS                                         0x00000003L
#define M_TAN                                         0x00000004L
#define M_QUAD                                        0x00000005L

/************************************************************************/
/* MgenWarpParameter()                                                  */
/************************************************************************/
/* 8 bits reserved for number of fractional bits added to M_FIXED_POINT */
#define M_WARP_MATRIX                                 0x00100000L
#define M_WARP_POLYNOMIAL                             0x00200000L
#define M_WARP_LUT                                    0x00400000L
#define M_WARP_4_CORNER                               0x00800000L
#define M_WARP_4_CORNER_REVERSE                       0x01000000L
/* Optional controls */
#define M_FIXED_POINT                                 0x00004000L
#define M_OVERSCAN_ENABLE                             0x00008000L
/*#define M_OVERSCAN_DISABLE                          See previous definition*/
#define M_OVERSCAN_FAST                               0x00040000L
#define M_FAST                                        0x00002000L
#define M_VERY_FAST                                   0x00010000L
#define M_REGULAR                                     0x00020000L

/* Transforms */
#define M_RESIZE                                      1L
#define M_ROTATE                                      2L
#define M_SHEAR_X                                     3L
#define M_SHEAR_Y                                     4L
#define M_TRANSLATE                                   5L
#define M_SCALE                                 0x00008010L

/************************************************************************/
/* MbufBayer() defines                                                  */
/************************************************************************/
#define M_BAYER_GB                                    32L
#define M_BAYER_BG                                    64L
#define M_BAYER_RG                                    96L
#define M_BAYER_GR                                    128L
#define M_BAYER_MASK                                  224L // M_BAYER_GB | M_BAYER_BG | M_BAYER_RG | M_BAYER_GR
#define M_WHITE_BALANCE_CALCULATE                     16L
#define M_BAYER_NORMALIZE                             512L
#define M_COLOR_CORRECTION                            1024L
#define M_ADAPTIVE                                    2048L 
#define M_AVERAGE_2X2                                 4096L
#define M_BAYER_BIT_SHIFT_MASK                        0x001F00000L
#define M_BAYER_EXTRACT_BIT_SHIFT(ControlFlag)        ((ControlFlag & M_BAYER_BIT_SHIFT_MASK) >> 20)
#define M_BAYER_BIT_SHIFT(NbBit)                      (NbBit << 20)
#define M_BAYER_REVERSE                               M_REVERSE
#define M_BAYER_OVERSCAN_ENABLE                       M_OVERSCAN_ENABLE
#define M_BAYER_OVERSCAN_DISABLE                      M_OVERSCAN_DISABLE

/************************************************************************/
/* Buffer attributes                                                    */
/************************************************************************/
#define M_NO_ATTR                                     0x00000000L
#define M_UNKNOWN_OBJECT_TYPE                         0x00000000L
#define M_IN                                          0x00000200L
#define M_OUT                                         0x00000400L
#define M_SRC                                         M_IN
#define M_DEST                                        M_OUT
#define M_GRAB                                        0x00000008L
#define M_PROC                                        0x00000010L
#define M_DISP                                        0x00000020L
#define M_ALLOW_NULL_ID                               0x00000800L
#define M_ALLOW_NULL_VALUE                            M_ALLOW_NULL_ID
#define M_ALLOW_VIRTUAL_ID                            0x00001000L
#define M_HIDDEN                                      0x00002000L 
#define M_PASS_THROUGH                                0x00004000L 
#define M_ALLOW_BUFFER_WITH_REGION                    0x00008000L
#define M_BITS_NOT_PART_OF_BUFFER_ATTRIBUTES          (M_IN+M_OUT+M_ALLOW_NULL_ID+M_ALLOW_VIRTUAL_ID+M_HIDDEN+M_PASS_THROUGH+M_ALLOW_BUFFER_WITH_REGION)

#define M_BITS_TYPE                    0x01FF
#define M_BITS_ATTR                    0xFE00L


// Macro used to identify virtual id.  A virtual id is accepted in parameters accepting
// MIL_ID but does not identify an existing resource having a valid MGObject.
#define M_IS_VIRTUAL_ID(Id)      ((Id) == M_DEFAULT)

/************************************************************************/
/* Buffer attributes                                                    */
/************************************************************************/
#define M_IMAGE                                       0x00000004L
#define M_GRAB                                        0x00000008L
#define M_PROC                                        0x00000010L
#define M_DISP                                        0x00000020L
#define M_ARRAY                                       0x00000040L
#define M_EVENT                                       0x00000080L
#define M_SYSTEM_THREAD                               0x00000100L
#define M_APPLICATION                                 0x00000200L
#define M_THREAD_CONTEXT                              0x00000400L
#define M_EVENT_CONTEXT                               0x00000800L
#define M_STAT_LIST                                   0x00001000L
#define M_HIST_LIST                                   0x00002000L
#define M_PROJ_LIST                                   0x00004000L
#define M_EVENT_LIST                                  0x00008000L
#define M_EXTREME_LIST                                0x00010000L
#define M_COUNT_LIST                                  0x00020000L
#define M_LUT                                         0x00040000L
#define M_WARP_COEFFICIENT                            0x00080000L
#define M_DIGITIZER                                   0x00100000L
#define M_DISPLAY                                     0x00200000L
#define M_KERNEL                                      0x00400000L
#define M_SYSTEM                                      0x00800000L
#define M_GRAPHIC_CONTEXT                             0x01000000L
#define M_CALL_CONTEXT                                0x02000000L
#define M_ERROR_CONTEXT                               0x04000000L
#define M_STRUCT_ELEMENT                              0x08000000L
#define M_MUTEX                                       0x10000000L
#define M_USER_ATTRIBUTE                              0x20000000L
#define M_DEINTERLACE_CONTEXT                         0x40000000L
#define M_THRESHOLD_CONTEXT                           MAKE_INT64(0x0000000100000000)
#define M_GRAPHIC_LIST                                MAKE_INT64(0x0000000200000000)
#define M_FLAT_FIELD_CONTEXT                          MAKE_INT64(0x0000000400000000)
#define M_DEAD_PIXEL_CONTEXT                          MAKE_INT64(0x0000000800000000)
#define M_REARRANGE_CONTEXT                           MAKE_INT64(0x0000001000000000)
#define M_STAT_MULTIPLE_CONTEXT                       MAKE_INT64(0x0000002000000000)
#define M_STAT_MULTIPLE_RESULT                        MAKE_INT64(0x0000004000000000)
#define M_MATCH_CONTEXT                               MAKE_INT64(0x0000008000000000)
#define M_VIDEO_DEVICE_OBJECT                         MAKE_INT64(0x0000010000000000)

#define M_BUF_ALLOC_BUFFER_TYPES                     (M_IMAGE          | \
                                                      M_LUT            | \
                                                      M_KERNEL         | \
                                                      M_STRUCT_ELEMENT | \
                                                      M_ARRAY)

#define M_IM_ALLOC_RESULT_BUFFER_TYPES               (M_HIST_LIST      | \
                                                      M_PROJ_LIST      | \
                                                      M_EVENT_LIST     | \
                                                      M_EXTREME_LIST   | \
                                                      M_STAT_LIST      | \
                                                      M_COUNT_LIST)

#define M_IM_CONTEXT_TYPES                           (M_DEINTERLACE_CONTEXT   | \
                                                      M_THRESHOLD_CONTEXT     | \
                                                      M_FLAT_FIELD_CONTEXT    | \
                                                      M_DEAD_PIXEL_CONTEXT    | \
                                                      M_REARRANGE_CONTEXT     | \
                                                      M_STAT_MULTIPLE_CONTEXT | \
                                                      M_MATCH_CONTEXT)

#define M_IM_RESULT_BUFFER_MEMORY_SPECIFIERS         (M_ON_BOARD         | \
                                                      M_OFF_BOARD        | \
                                                      M_PAGED            | \
                                                      M_NON_PAGED        | \
                                                      M_HOST_MEMORY      | \
                                                      M_VIDEO_MEMORY     | \
                                                      M_PROC_GPU         | \
                                                      M_FPGA_ACCESSIBLE  | \
                                                      M_FAST_MEMORY      | \
                                                      M_MEMORY_BANK_MASK)

#define M_ALL_BUFFER_TYPES                           (M_BUF_ALLOC_BUFFER_TYPES | \
                                                      M_IM_ALLOC_RESULT_BUFFER_TYPES)

/* Use this macro to verify safely if a Mil object is a buffer. */
#define M_IS_BUFFER_TYPE( ParIs )      ( (0                != (ParIs & M_ALL_BUFFER_TYPES)) && \
                                         (M_USER_ATTRIBUTE != (ParIs & M_USER_ATTRIBUTE  )) )

/* Use this macro to verify safely if a Mil object is a display. */
#define M_IS_DISPLAY_TYPE( ParIs )     ( (M_DISPLAY == (ParIs & M_DISPLAY        )) && \
                                         (0         == (ParIs & M_USER_ATTRIBUTE )) && \
                                         (0         == (ParIs & M_ALL_BUFFER_TYPES)) )

/* Use this macro to verify safely if a Mil object is a digitizer. */
#define M_IS_DIGITIZER_TYPE( ParIs )   ( (M_DIGITIZER == (ParIs & M_DIGITIZER      )) && \
                                         (0           == (ParIs & M_USER_ATTRIBUTE )) && \
                                         (0           == (ParIs & M_ALL_BUFFER_TYPES)) )


#define M_USER_OBJECT_1                               (M_USER_ATTRIBUTE       | 0x00010000L)
#define M_USER_OBJECT_2                               (M_USER_ATTRIBUTE       | 0x00020000L)
#define M_BLOB_OBJECT                                 (M_USER_ATTRIBUTE       | 0x00040000L)
#define M_BLOB_FEATURE_LIST                           (M_BLOB_OBJECT          | 0x00000001L)
#define M_BLOB_RESULT                                 (M_BLOB_OBJECT          | 0x00000002L)
#define M_PAT_OBJECT                                  (M_USER_ATTRIBUTE       | 0x00080000L)
#define M_PAT_MODEL                                   (M_PAT_OBJECT           | 0x00000001L)
#define M_PAT_RESULT                                  (M_PAT_OBJECT           | 0x00000002L)
#define M_OCR_OBJECT                                  (M_USER_ATTRIBUTE       | 0x00100000L)
#define M_OCR_FONT                                    (M_OCR_OBJECT           | 0x00000001L)
#define M_OCR_RESULT                                  (M_OCR_OBJECT           | 0x00000002L)
#define M_OCR_MULTILINES_RESULT                       (M_OCR_OBJECT           | 0x00000003L)
#define M_MEAS_OBJECT                                 (M_USER_ATTRIBUTE       | 0x00200000L)
#define M_MEAS_MARKER                                 (M_MEAS_OBJECT          | 0x00000001L)
#define M_MEAS_RESULT                                 (M_MEAS_OBJECT          | 0x00000002L)
#define M_MEAS_CONTEXT                                (M_MEAS_OBJECT          | 0x00000004L)
#define M_CAL_OBJECT                                  (M_USER_ATTRIBUTE       | 0x00400000L)
#define M_CAL_PARENT                                  (M_CAL_OBJECT           | 0x00000001L)
#define M_CAL_CHILD                                   (M_CAL_OBJECT           | 0x00000002L)
#define M_CAL_FIXTURING_OFFSET                        (M_CAL_OBJECT           | 0x00000004L)
#define M_CODE_OBJECT                                 (M_USER_ATTRIBUTE       | 0x00800000L)
#define M_CODE_CONTEXT                                (M_CODE_OBJECT          | 0x00000001L)
#define M_CODE_RESULT                                 (M_CODE_OBJECT          | 0x00000002L)
#define M_OLD_CODE_CONTEXT                            (M_CODE_OBJECT          | 0x00000003L)
#define M_CODE_MODEL                                  (M_CODE_OBJECT          | 0x00000004L)
#define M_BGA_OBJECT                                  (M_USER_ATTRIBUTE       | 0x01000000L)
#define M_BGA_CONTEXT                                 (M_BGA_OBJECT           | 0x00000001L)
#define M_STR_OBJECT                                  (M_USER_ATTRIBUTE       | 0x02000000L)
#define M_STR_FEATURE_BASED_CONTEXT                   (M_STR_OBJECT           | 0x00000001L) //DEPRECATED, replaced by M_STR_CONTEXT
#define M_STR_CONTEXT                                 (M_STR_OBJECT           | 0x00000001L)
#define M_STR_RESULT                                  (M_STR_OBJECT           | 0x00000002L)
#define M_MOD_OBJECT                                  (M_USER_ATTRIBUTE       | 0x04000000L)
#define M_MOD_GEOMETRIC                               (M_MOD_OBJECT           | 0x00000001L)
#define M_MOD_RESULT                                  (M_MOD_OBJECT           | 0x00000004L)
#define M_MOD_GEOMETRIC_CONTROLLED                    (M_MOD_OBJECT           | 0x00000008L)
#define M_EDGE_OBJECT                                 (M_USER_ATTRIBUTE       | 0x08000000L)
#define M_EDGE_CONTOUR                                (M_EDGE_OBJECT          | 0x00000001L)
#define M_EDGE_CREST                                  (M_EDGE_OBJECT          | 0x00000002L)
#define M_EDGE_RESULT                                 (M_EDGE_OBJECT          | 0x00000004L)
#define M_FUTURE_OBJECT                               (M_USER_ATTRIBUTE       | 0x10000000L)
#define M_HOOK_CONTEXT_OBJECT                         (M_USER_ATTRIBUTE       | 0x40000000L)
#define M_HOOK_CONTEXT                                (M_HOOK_CONTEXT_OBJECT  | 0x00000001L)
#define M_DRIVER_HOOK_CONTEXT                         (M_HOOK_CONTEXT_OBJECT  | 0x00000002L)
#define M_REG_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000000800000000))
#define M_REG_CONTEXT                                 (M_REG_OBJECT           | 0x00000001L )
#define M_REG_RESULT                                  (M_REG_OBJECT           | 0x00000002L )
#define M_MET_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000000100000000))
#define M_MET_CONTEXT                                 (M_MET_OBJECT           | 0x00000001L )
#define M_MET_RESULT                                  (M_MET_OBJECT           | 0x00000002L )
#define M_COL_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000000200000000))
#define M_COL_MATCH_CONTEXT                           (M_COL_OBJECT           | 0x00000001L )
#define M_COL_SPACE_DEF_CONTEXT                       (M_COL_OBJECT           | 0x00000002L )
#define M_COL_PROJECT_CONTEXT                         (M_COL_OBJECT           | 0x00000004L )
#define M_COL_MATCH_RESULT                            (M_COL_OBJECT           | 0x00000008L )
#define M_3DMAP_OBJECT                                (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000000400000000))
#if OldDefinesSupport
#define M_3DPR_OBJECT                                  M_3DMAP_OBJECT
#endif
#define M_3DMAP_LASER_CONTEXT                         (M_3DMAP_OBJECT         | 0x00000001L )
#define M_3DMAP_LASER_DATA                            (M_3DMAP_OBJECT         | 0x00000002L )
#define M_3DMAP_GEOMETRY                              (M_3DMAP_OBJECT         | 0x00000004L )
#define M_3DMAP_STAT_RESULT                           (M_3DMAP_OBJECT         | 0x00000008L )
#define M_BEAD_OBJECT                                 (M_MEAS_OBJECT)
#define M_BEAD_CONTEXT                                (M_BEAD_OBJECT          | 0x00000010L )
#define M_BEAD_RESULT                                 (M_BEAD_OBJECT          | 0x00000020L )
#define M_R10_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000001000000000))
#define M_R11_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000002000000000))
#define M_R12_OBJECT                                  (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000004000000000))
#define M_CLAS_OBJECT                                 (M_USER_ATTRIBUTE       | MAKE_INT64(0x0000200000000000))
#define M_CLAS_CONTEXT                                (M_CLAS_OBJECT | 0x00000001L ) 
#define M_CLAS_RESULT                                 (M_CLAS_OBJECT | 0x00000002L ) 

#define M_VIDEO_DEVICE_OBJECT                         MAKE_INT64(0x0000010000000000)
#define M_USER_DEFINE_LOW_ATTRIBUTE                   0x0000FFFFL

#define M_INTERNAL_ALLOCATION   0         //TBR should no longer be used. Has never been functional

#define M_SYSTEM_ALLOCATED                            0x00000001L
#define M_USER_ALLOCATED                              MIL_MAKE_CONST(0xFFFFFFFEL,0x00000000FFFFFFFE)

#define M_SIGNED                                      0x08000000L
#define M_FLOAT                                      (0x40000000L | M_SIGNED)
#define M_DOUBLE                                     (0x20000000L | M_SIGNED)


// For M_IMAGE buffers:
#define M_IMAGE                                       0x00000004L
#define M_GRAB                                        0x00000008L
#define M_PROC                                        0x00000010L
#define M_DISP                                        0x00000020L
// 0x40 to used
#define M_OVR                                         0x00000080L
#define M_OFFSCREEN                                   M_OVR
#define M_INTERNAL_FORMAT                             0x00003F00L
#define M_COMPRESS                                    0x00004000L
#define M_ALLOCATION_OVERSCAN                         0x00008000L              // This flag is also use as MbufControl/Inquire type and as MsysControl/Inquire type.
#define M_FAST_OVERSCAN                               M_ALLOCATION_OVERSCAN
#define M_FLIP                                        0x00010000L
#define M_PACKED                                      0x00020000L
#define M_PLANAR                                      0x00040000L
#define M_ON_BOARD                                    0x00080000L
#define M_OFF_BOARD                                   0x00100000L
#define M_NON_PAGED                                   0x00200000L
// 0x00400000 used with M_COMPRESS
#define M_UND                                         0x00800000L // value also used with M_COMPRESS
#define M_UNDERLAY                                    M_UND
#define M_SINGLE                                      0x01000000L
#define M_VIA                                         M_SINGLE
#define M_PAGED                                       0x02000000L
#define M_NO_FLIP                                     0x04000000L
#define M_OVERSCAN_BUFFER                             0x08000000L // value also used with M_COMPRESS
#define M_READ_PREFETCH_ENABLED                       0x10000000L
//Keep only for backward compatibility.
#define M_MMX_ENABLED                                 M_READ_PREFETCH_ENABLED
#define M_SSE_ENABLED                                 M_READ_PREFETCH_ENABLED
#define M_USER_ATTRIBUTE                              0x20000000L
#define M_DDRAW                                       0x40000000L
#define M_DIRECTX                                     M_DDRAW
// 0x8000000 reserved

#if !M_MIL_USE_LINUX
#define M_NON_LOCAL_MEMORY      ((BUFATTRTYPE)MAKE_INT64(0x0000000800000000))
#define M_BITMAP_HANDLE         ((BUFATTRTYPE)MAKE_INT64(0x0000008000000000))
#endif
// New define place in the 32 higher bits of the attribute
#define M_GDI                   ((BUFATTRTYPE)MAKE_INT64(0x0000000100000000))
#define M_HOST_MEMORY           ((BUFATTRTYPE)MAKE_INT64(0x0000000200000000))
#define M_VIDEO_MEMORY          ((BUFATTRTYPE)MAKE_INT64(0x0000000400000000))
#define M_FAST_MEMORY           ((BUFATTRTYPE)MAKE_INT64(0x0000001000000000))
#define M_D3D_BUFFER            M_FAST_MEMORY
#define M_SHARED                ((BUFATTRTYPE)MAKE_INT64(0x0000002000000000))
#define M_PRIMARY_SURFACE       ((BUFATTRTYPE)MAKE_INT64(0x0000004000000000))

// BITS RESERVED FOR COMPLEX BUFFERS                     0x0000070000000000
#define M_LIVE_VIDEO            ((BUFATTRTYPE)MAKE_INT64(0x0000080000000000))
#define M_AUDIO                 ((BUFATTRTYPE)MAKE_INT64(0x0000080000000000))
#define M_MTX0                  ((BUFATTRTYPE)MAKE_INT64(0x0000100000000000))
#define M_NON_CACHABLE          MAKE_INT64(0x0000200000000000)
//Linux specific buffer attribute
#if M_MIL_USE_LINUX
#define M_LINUX_MXIMAGE         ((BUFATTRTYPE)MAKE_INT64(0x0800000000000000)) // Same value as M_DIB
#define M_LINUX_MXVMIL          ((BUFATTRTYPE)MAKE_INT64(0x0000000800000000)) // Same value as M_NON_LOCAL_MEMORY
#define M_LINUX_MXDGA           ((BUFATTRTYPE)MAKE_INT64(0x0000008000000000)) // Same value as M_BITMAP_HANDLE
#endif

#define M_MAPPABLE              ((BUFATTRTYPE)MAKE_INT64(0x0001000000000000))
//End of Linux specific buffer attribute
#define M_AUX_VISIBLE           ((BUFATTRTYPE)MAKE_INT64(0x0002000000000000))
#define M_AUX                   M_AUX_VISIBLE
#define M_DISPLAY_AS_RGB10BIT   ((BUFATTRTYPE)MAKE_INT64(0x0004000000000000))
#define M_DISPLAY_AS_YUV32      ((BUFATTRTYPE)MAKE_INT64(0x0080000000000000))
#define M_NO_MEMORY             ((BUFATTRTYPE)MAKE_INT64(0x0008000000000000))
#define M_MEMORY_BANK_DEFAULT   ((BUFATTRTYPE)MAKE_INT64(0x0000000000000000))
#define M_MEMORY_BANK_0         ((BUFATTRTYPE)MAKE_INT64(0x0010000000000000))
#define M_MEMORY_BANK_1         ((BUFATTRTYPE)MAKE_INT64(0x0020000000000000))
#define M_MEMORY_BANK_2         ((BUFATTRTYPE)MAKE_INT64(0x0030000000000000))
#define M_MEMORY_BANK_3         ((BUFATTRTYPE)MAKE_INT64(0x0040000000000000))
#define M_MEMORY_BANK_4         ((BUFATTRTYPE)MAKE_INT64(0x0050000000000000))
#define M_MEMORY_BANK_5         ((BUFATTRTYPE)MAKE_INT64(0x0060000000000000))
#define M_MEMORY_BANK_6         ((BUFATTRTYPE)MAKE_INT64(0x0070000000000000))
#define M_MEMORY_BANK_MASK      ((BUFATTRTYPE)MAKE_INT64(0x0070000000000000))
#define M_FPGA_ACCESSIBLE       ((BUFATTRTYPE)MAKE_INT64(0x0100000000000000))
#define M_DYNAMIC_TEXTURE       M_FPGA_ACCESSIBLE
#define M_FPGA_MEMORY           M_FPGA_ACCESSIBLE //Obsolete, use M_FPGA_ACCESSIBLE
#define M_OPENCL_COMPATIBLE     ((BUFATTRTYPE)MAKE_INT64(0x0200000000000000))
// Available                    ((BUFATTRTYPE)MAKE_INT64(0x0400000000000000))
#define M_DIB                   ((BUFATTRTYPE)MAKE_INT64(0x0800000000000000))
#define M_PROC_GPU              ((BUFATTRTYPE)MAKE_INT64(0x1000000000000000))
#define M_DISPATTRIB_RESERVED   ((BUFATTRTYPE)MAKE_INT64(0x2000000000000000))
#define M_DISP_EXTERNAL         ((BUFATTRTYPE)MAKE_INT64(0x4000000000000000))
#define M_FPGA_MEMORY           M_FPGA_ACCESSIBLE //Obsolete, use M_FPGA_ACCESSIBLE
#define M_DIB                   ((BUFATTRTYPE)MAKE_INT64(0x0800000000000000))
#define M_UNUSED_BITS           ((BUFATTRTYPE)MAKE_INT64(0x8000000000000000)) //Update when reusing bits for new defines

#define M_IS_FAST_MEMORY(attrib)                      ((((attrib)&M_FAST_MEMORY) != 0) && (((attrib)&M_VIDEO_MEMORY) == 0))
#define M_IS_FPGA_ACCESSIBLE(attrib)                  ((((attrib)&M_FPGA_ACCESSIBLE) != 0) && (((attrib)&M_VIDEO_MEMORY) == 0))

#define M_COMPLEX_OFFSET                                     (40)
#define M_COMPLEX_MASK                                (((BUFATTRTYPE)0x7)<<M_COMPLEX_OFFSET)
#define M_IS_COMPLEX(attrib)                          ((((attrib)&M_COMPLEX_MASK) != 0) && (((attrib)&M_COMPRESS) == 0) && (((attrib)&M_VIDEO_MEMORY) != 0))
#define M_COMPLEX(_nb)                                ((((BUFATTRTYPE)(_nb))<<M_COMPLEX_OFFSET)&M_COMPLEX_MASK)
#define M_COMPLEX_NB_BUFFER(attrib)                   ((((attrib)&M_COMPRESS) != 0)?0:((long)(((BUFATTRTYPE)(attrib)&M_COMPLEX_MASK)>>M_COMPLEX_OFFSET)))

#define M_MEMORY_BANK_OFFSET                          52
#define M_MEMORY_BANK_TO_USE(attrib)                  ((((attrib)&M_MEMORY_BANK_MASK)>>M_MEMORY_BANK_OFFSET)-1)

#define M_COMPRESSION_FORMAT_MASK                     0x08C08000L

#define M_JPEG_LOSSLESS                               0x00400000L
#define M_JPEG_LOSSY                                  0x00800000L
#define M_JPEG_LOSSLESS_INTERLACED                    0x00C00000L
#define M_JPEG_LOSSY_INTERLACED                       0x08000000L
#define M_JPEG2000_LOSSY                              0x08400000L
#define M_JPEG2000_LOSSLESS                           0x08800000L
#define M_MPEG4                                       0x08C00000L
#define M_H264                                        0x00008000L

/*
Reserved compression format                           0x00408000L
Reserved compression format                           0x00808000L
Reserved compression format                           0x00C08000L
Reserved compression format                           0x08008000L
Reserved compression format                           0x08408000L
Reserved compression format                           0x08808000L
Reserved compression format                           0x08C08000L
*/

#define M_IS_LOSSY(a)                                 (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSY) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSY_INTERLACED) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG2000_LOSSY) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_MPEG4) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_H264)))
#define M_IS_LOSSLESS(a)                              (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSLESS) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSLESS_INTERLACED) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG2000_LOSSLESS)))
#define M_IS_JPEG(a)                                  (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSLESS) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSY) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSLESS_INTERLACED) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSY_INTERLACED)))
#define M_IS_JPEG2000(a)                              (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG2000_LOSSY) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG2000_LOSSLESS)))
#define M_IS_MPEG4(a)                                 (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_MPEG4)))
#define M_IS_H264(a)                                  (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_H264)))
#define M_IS_INTERLACED(a)                            (M_IS_COMPRESSED(a) && \
                                                       ((((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSY_INTERLACED) || \
                                                        (((a) & M_COMPRESSION_FORMAT_MASK) == M_JPEG_LOSSLESS_INTERLACED)))
#define M_COMPRESSION_FORMAT(a)                       (M_IS_COMPRESSED(a) ? ((a) & M_COMPRESSION_FORMAT_MASK) : 0)
#define M_IS_COMPRESSED(a)                            ((((a) & M_IMAGE) != 0) && (((a) & M_COMPRESS) != 0))
#define M_IS_AUDIO(a)                                 ((((a) & M_ARRAY) != 0) && (((a) & M_AUDIO) != 0))
#define M_IS_PACKED_LUT(a)                            (((a&M_IMAGE)==0) && ((a&~(M_MMX_ENABLED|M_READ_PREFETCH_ENABLED|M_DIRECTX|M_VIDEO_MEMORY|M_HOST_MEMORY|M_PROC_GPU|M_NON_PAGED)) == (M_LUT|M_PACKED|M_BGR32)))
#define M_IS_ON_BOARD(a)                              (((a) & M_HOST_MEMORY) ? M_FALSE : (((a) & M_ON_BOARD) ? M_TRUE : (((a) & M_MEMORY_BANK_MASK) ? M_TRUE : (M_IS_FPGA_ACCESSIBLE(a) ? M_TRUE : M_FALSE))))
#define M_IS_ON_BOARD_OR_VIDEO_MEMORY(a)              (M_IS_ON_BOARD(a) || (((a) & M_VIDEO_MEMORY) != 0))

/* 6 bits reserved for buffer internal format and format definitions */
#define M_INTERNAL_FORMAT             0x00003F00L
#define M_INTERNAL_FORMAT_SHIFT       8L
#define M_INTERNAL_COMPLETE_FORMAT    0x7FFFFF80L
#define M_ANY_INTERNAL_FORMAT         (0   << M_INTERNAL_FORMAT_SHIFT)

// Range for MONO formats : 1 to 5.
#define M_MONO_RANGE_START                (1   << M_INTERNAL_FORMAT_SHIFT)
#define M_MONO1                           (1   << M_INTERNAL_FORMAT_SHIFT)   // Force  1 bit  pixels in monochrome format
#define M_MONO8                           (2   << M_INTERNAL_FORMAT_SHIFT)   // Force  8 bits pixels in monochrome format
#define M_MONO16                          (3   << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits pixels in monochrome format
#define M_MONO32                          (4   << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in monochrome format
#define M_MONO10                          (5   << M_INTERNAL_FORMAT_SHIFT)   // Force 10 bits pixels in monochrome format => use with displays to describe 10-bits grayscale monitor (medical)
#define M_MONO_RANGE_END                  (5   << M_INTERNAL_FORMAT_SHIFT)

// Extended range for MONO formats : 41 to 47.
#define M_MONO_EXTENDED_RANGE_START       (41  << M_INTERNAL_FORMAT_SHIFT)
#define M_MONO64                          (41  << M_INTERNAL_FORMAT_SHIFT)   // Force 64 bits pixels in monochrome format
#define M_MONO12                          (42  << M_INTERNAL_FORMAT_SHIFT)   // Force 12 bits pixels in monochrome format => for GVSP 12-bit packed alignment
/* AVAILABLE                              (42 to 47) */
#define M_MONO_EXTENDED_RANGE_END         (47  << M_INTERNAL_FORMAT_SHIFT)

// Range for RGB and BGR formats : 6 to 20.
#define M_RGB_BGR_RANGE_START             (6   << M_INTERNAL_FORMAT_SHIFT)
#define M_RGB15                           (6   << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits pixels in color XRGB  1.5.5.5  format
#define M_RGB16                           (7   << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits pixels in color RGB   5.6.5    format
#define M_RGB24                           (8   << M_INTERNAL_FORMAT_SHIFT)   // Force 24 bits pixels in color RGB   8.8.8    format
#define M_RGBX32                          (9   << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in color RGBX  8.8.8.8  format
#define M_RGB32                           M_RGBX32
#define M_XRGB32                          (10  << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in color XRGB  8.8.8.8  format
#define M_RGB48                           (11  << M_INTERNAL_FORMAT_SHIFT)   // Force 48 bits pixels in color RGB  16.16.16  format
#define M_RGB96                           (12  << M_INTERNAL_FORMAT_SHIFT)   // Force 96 bits pixels in color RGB  32.32.32  format
#define M_RGB3                            (13  << M_INTERNAL_FORMAT_SHIFT)   // Force  3 bits pixels in color RGB   1.1.1    format
#define M_BGR15                           (14  << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits pixels in color BGRX  5.5.5.1  format
#define M_BGR16                           (15  << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits pixels in color BGR   5.6.5    format
#define M_BGR24                           (16  << M_INTERNAL_FORMAT_SHIFT)   // Force 24 bits pixels in color BGR   8.8.8    format
#define M_BGRX32                          (17  << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in color BGRX  8.8.8.8  format
#define M_BGR32                           M_BGRX32
#define M_XBGR32                          (18  << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in color XBGR  8.8.8.8  format
#define M_BGR30                           (19  << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits pixels in color XBGR  2.10.10.10  format
#define M_RGB192                          (20  << M_INTERNAL_FORMAT_SHIFT)   // Force 192 bits pixels in color RGB  64.64.64  format
#define M_RGB_BGR_RANGE_END               (20  << M_INTERNAL_FORMAT_SHIFT)

// Extended range for RGB and BGR formats : 48 to 55.
#define M_RGB_BGR_EXTENDED_RANGE_START    (48  << M_INTERNAL_FORMAT_SHIFT)
/* AVAILABLE                              (48 to 55) */
#define M_RGB_BGR_EXTENDED_RANGE_END      (55  << M_INTERNAL_FORMAT_SHIFT)

// Range for YUV formats : 21 to 40.
#define M_YUV_RANGE_START                 (21  << M_INTERNAL_FORMAT_SHIFT)
#define M_YUV9                            (21  << M_INTERNAL_FORMAT_SHIFT)   // Force  9 bits YUV pixels in color YUV 16:1:1 format
#define M_YUV1611                         M_YUV9
#define M_YUV12                           (22  << M_INTERNAL_FORMAT_SHIFT)   // Force 12 bits YUV pixels in color YUV  4:1:1 format
#define M_YUV411                          M_YUV12
#define M_YUV16                           (23  << M_INTERNAL_FORMAT_SHIFT)   // Force 16 bits YUV pixels in color YUV  4:2:2 format
#define M_YUV422                          M_YUV16
/* AVAILABLE                              (24 to 26) */
#define M_YUV24                           (27  << M_INTERNAL_FORMAT_SHIFT)   // Force 24 bits YUV pixels in color YUV  4:4:4 format
#define M_YUV444                          M_YUV24
#define M_YUV16_YUYV                      (28  << M_INTERNAL_FORMAT_SHIFT)   // Force YUV16 packed buffers into a YUYV memory layout ( meteor, corona, meteor2 ) (FOURCC: YUY2).
#define M_YUV422_YUYV                     M_YUV16_YUYV
#define M_YUV16_UYVY                      (29  << M_INTERNAL_FORMAT_SHIFT)   // Force YUV16 packed buffers into a UYVY memory layout ( meteor ) (FOURCC: UYVY).
#define M_YUV16_1394                      M_YUV16_UYVY
#define M_YUV422_UYVY                     M_YUV16_UYVY
#define M_YUV422_1394                     M_YUV16_1394
/* AVAILABLE                              (30) */
#define M_YUV12_1394                      (31  << M_INTERNAL_FORMAT_SHIFT)   // Force YUV12 packed buffers with the special memory layout of the 1394.
#define M_YUV411_1394                     M_YUV12_1394
#define M_YUV32                           (32  << M_INTERNAL_FORMAT_SHIFT)   // Force 32 bits YUV pixels in color (8(X)-8(Y)-8(U)-8(V))
/* AVAILABLE                              (33 to 40) */
#define M_YUV_RANGE_END                   (40  << M_INTERNAL_FORMAT_SHIFT)

// Extended range for YUV formats : 56 to 63.
#define M_YUV_EXTENDED_RANGE_START        (56  << M_INTERNAL_FORMAT_SHIFT)
/* AVAILABLE                              (56 to 63) */
#define M_YUV_EXTENDED_RANGE_END          (63 << M_INTERNAL_FORMAT_SHIFT)

#define M_SINGLE_BAND                     (255 << M_INTERNAL_FORMAT_SHIFT)   // PutColor and GetColor specification for a single band

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))

#define M_COMPRESSED_DATA                 M_COMPRESS

#else

#define M_COMPRESSED_DATA                 1

#endif // ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))

#define M_IS_FORMAT_MONO(f)               ((((f & M_INTERNAL_FORMAT) >= M_MONO_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_MONO_RANGE_END)) || \
                                           (((f & M_INTERNAL_FORMAT) >= M_MONO_EXTENDED_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_MONO_EXTENDED_RANGE_END)))

#define M_IS_FORMAT_RGB_BGR(f)            ((((f & M_INTERNAL_FORMAT) >= M_RGB_BGR_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_RGB_BGR_RANGE_END)) || \
                                           (((f & M_INTERNAL_FORMAT) >= M_RGB_BGR_EXTENDED_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_RGB_BGR_EXTENDED_RANGE_END)))

#define M_IS_FORMAT_YUV(f)                ((((f & M_INTERNAL_FORMAT) >= M_YUV_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_YUV_RANGE_END)) || \
                                           (((f & M_INTERNAL_FORMAT) >= M_YUV_EXTENDED_RANGE_START) && \
                                            ((f & M_INTERNAL_FORMAT) <= M_YUV_EXTENDED_RANGE_END)))

#define M_BIT_FIELD_FORMAT(f)             (((MIL_INT) 1) << (((f & M_INTERNAL_FORMAT) >> M_INTERNAL_FORMAT_SHIFT) - 1))

// The following MACRO keep only attribute used by the host.
#define M_KEEP_HO_ATTRIBUTES(a)                                                               \
   ((a&M_IMAGE) ?                                                                             \
      (a&(M_INTERNAL_FORMAT|M_IMAGE|M_PACKED|M_PLANAR|M_COMPRESS|M_COMPRESSION_FORMAT_MASK|   \
          M_FLIP|M_NO_FLIP|M_NON_PAGED|M_PAGED|M_READ_PREFETCH_ENABLED|                       \
          M_HOST_MEMORY))                                                                     \
   :  (a))

//Attributes accepted by all non-M_IMAGE buffers on the Host
#define MIL_MEMORY_SPECIFIERS (M_PAGED | M_NON_PAGED | M_OFF_BOARD | M_HOST_MEMORY | M_MAPPABLE)

// The following MACRO takes a data format as input and returns the number
// of bits per pixel that it implies as an output.
// For an unknown data format, it returns M_INVALID.
#define NB_OF_BITS_PER_PIXEL(DataFormat,NbOfBits)             \
   switch( ((DataFormat) & M_INTERNAL_FORMAT) )               \
      {                                                       \
      case M_MONO1:        NbOfBits = 1;         break;       \
      case M_MONO8:        NbOfBits = 8;         break;       \
      case M_MONO16:       NbOfBits = 16;        break;       \
      case M_MONO32:       NbOfBits = 32;        break;       \
      case M_MONO64:       NbOfBits = 64;        break;       \
      case M_RGB15:        NbOfBits = 16;        break;       \
      case M_RGB16:        NbOfBits = 16;        break;       \
      case M_RGB24:        NbOfBits = 24;        break;       \
      case M_RGBX32:       NbOfBits = 32;        break;       \
      case M_XRGB32:       NbOfBits = 32;        break;       \
      case M_RGB48:        NbOfBits = 48;        break;       \
      case M_RGB96:        NbOfBits = 96;        break;       \
      case M_RGB192:       NbOfBits = 192;       break;       \
      case M_RGB3:         NbOfBits = 3;         break;       \
      case M_BGR15:        NbOfBits = 16;        break;       \
      case M_BGR16:        NbOfBits = 16;        break;       \
      case M_BGR24:        NbOfBits = 24;        break;       \
      case M_BGRX32:       NbOfBits = 32;        break;       \
      case M_XBGR32:       NbOfBits = 32;        break;       \
      case M_BGR30:        NbOfBits = 32;        break;       \
                                                              \
      case M_YUV9:         NbOfBits = 9;         break;       \
      case M_YUV12:        NbOfBits = 12;        break;       \
      case M_YUV16:        NbOfBits = 16;        break;       \
      case M_YUV24:        NbOfBits = 24;        break;       \
      case M_YUV16_YUYV:   NbOfBits = 16;        break;       \
      case M_YUV16_UYVY:   NbOfBits = 16;        break;       \
      case M_YUV12_1394:   NbOfBits = 12;        break;       \
      default:             NbOfBits = M_INVALID; break;       \
      }

// The following MACRO takes a data format as input and returns the number
// of bits per pixel per plane that it implies as an output.
// For an unknown data format, it returns M_INVALID.
// It is better to compare the format with M_PACKED, because M_PLANAR is
// not always present on planar buffers.
#define M_NB_BITS_PER_PIXEL_PER_PLANE(DataFormat,NbOfBits)       \
  switch( ((DataFormat) & M_INTERNAL_FORMAT)  )                  \
     {                                                           \
     /* M_PACKED is implicit */                                  \
     case M_MONO1:        NbOfBits = 1;         break;           \
     case M_MONO8:        NbOfBits = 8;         break;           \
     case M_MONO16:       NbOfBits = 16;        break;           \
     case M_MONO32:       NbOfBits = 32;        break;           \
     case M_MONO64:       NbOfBits = 64;        break;           \
     case M_RGB15:        NbOfBits = 16;        break;           \
     case M_RGB16:        NbOfBits = 16;        break;           \
     case M_RGBX32:       NbOfBits = 32;        break;           \
     case M_XRGB32:       NbOfBits = 32;        break;           \
     case M_BGR15:        NbOfBits = 16;        break;           \
     case M_BGR16:        NbOfBits = 16;        break;           \
     case M_BGR24:        NbOfBits = 24;        break;           \
     case M_BGRX32:       NbOfBits = 32;        break;           \
     case M_XBGR32:       NbOfBits = 32;        break;           \
     case M_BGR30:        NbOfBits = 32;        break;           \
     case M_YUV16_YUYV:   NbOfBits = 16;        break;           \
     case M_YUV16_UYVY:   NbOfBits = 16;        break;           \
     /* M_PLANAR is implicit */                                  \
     case M_RGB3:         NbOfBits = 1;         break;           \
     case M_RGB96:        NbOfBits = 32;        break;           \
     case M_RGB192:       NbOfBits = 64;        break;           \
     /* Ambiguous internal format */                             \
     default:                                                    \
        if((DataFormat)&M_PACKED)                                \
           {                                                     \
           switch(((DataFormat) & M_INTERNAL_FORMAT))            \
              {                                                  \
              case M_RGB24:        NbOfBits = 24;        break;  \
              case M_RGB48:        NbOfBits = 48;        break;  \
              case M_YUV9:         NbOfBits = 9;         break;  \
              case M_YUV12:        NbOfBits = 12;        break;  \
              case M_YUV16:        NbOfBits = 16;        break;  \
              case M_YUV24:        NbOfBits = 24;        break;  \
              case M_YUV12_1394:   NbOfBits = 12;        break;  \
              default:             NbOfBits = M_INVALID; break;  \
              }                                                  \
           }                                                     \
        /* If packed is not present, consider planar */          \
        else                                                     \
           {                                                     \
           switch(((DataFormat) & M_INTERNAL_FORMAT))            \
              {                                                  \
              case M_RGB24:        NbOfBits = 8;         break;  \
              case M_RGB48:        NbOfBits = 16;        break;  \
              case M_YUV9:         NbOfBits = 8;         break;  \
              case M_YUV12:        NbOfBits = 8;         break;  \
              case M_YUV16:        NbOfBits = 8;         break;  \
              case M_YUV24:        NbOfBits = 8;         break;  \
              case M_YUV12_1394:   NbOfBits = 8;         break;  \
              default:             NbOfBits = M_INVALID; break;  \
              }                                                  \
           }                                                     \
        break;                                                   \
     }

#define MONO_FORMAT_FROM_SIZEBIT(MonoFormat, NbOfBits)             \
   switch( NbOfBits)                                               \
      {                                                            \
      case 1:        MonoFormat = M_MONO1;         break;          \
      case 8:        MonoFormat = M_MONO8;         break;          \
      case 16:       MonoFormat = M_MONO16;        break;          \
      case 32:       MonoFormat = M_MONO32;        break;          \
      case 64:       MonoFormat = M_MONO64;        break;          \
      default:       MonoFormat = M_INVALID;       break;          \
      }

// The following MACRO takes a data format as input and returns 
// the buffer type that is associated with it.
// For an unknown data format, it returns M_INVALID.
#define M_TYPE_FROM_FORMAT(DataFormat,Type)                 \
   switch( ((DataFormat) & M_INTERNAL_FORMAT) )             \
      {                                                     \
      case M_MONO1:        Type = 1+M_UNSIGNED;     break;  \
      case M_MONO8:        Type = 8+M_UNSIGNED;     break;  \
      case M_MONO16:       Type = 16+M_UNSIGNED;    break;  \
      case M_MONO32:       Type = 32+M_UNSIGNED;    break;  \
      case M_MONO64:       Type = 64+M_UNSIGNED;    break;  \
                                                            \
      case M_RGB15:        Type = 8+M_UNSIGNED;     break;  \
      case M_RGB16:        Type = 8+M_UNSIGNED;     break;  \
      case M_RGB24:        Type = 8+M_UNSIGNED;     break;  \
      case M_RGBX32:       Type = 8+M_UNSIGNED;     break;  \
      case M_XRGB32:       Type = 8+M_UNSIGNED;     break;  \
      case M_RGB48:        Type = 16+M_UNSIGNED;    break;  \
      case M_RGB96:        Type = 32+M_UNSIGNED;    break;  \
      case M_RGB192:       Type = 64+M_UNSIGNED;    break;  \
      case M_RGB3:         Type = 1+M_UNSIGNED;     break;  \
                                                            \
      case M_BGR15:        Type = 8+M_UNSIGNED;     break;  \
      case M_BGR16:        Type = 8+M_UNSIGNED;     break;  \
      case M_BGR24:        Type = 8+M_UNSIGNED;     break;  \
      case M_BGRX32:       Type = 8+M_UNSIGNED;     break;  \
      case M_XBGR32:       Type = 8+M_UNSIGNED;     break;  \
      case M_BGR30:        Type = 10+M_UNSIGNED;    break;  \
                                                            \
      case M_YUV9:         Type = 8+M_UNSIGNED;     break;  \
      case M_YUV12:        Type = 8+M_UNSIGNED;     break;  \
      case M_YUV16:        Type = 8+M_UNSIGNED;     break;  \
      case M_YUV24:        Type = 8+M_UNSIGNED;     break;  \
      case M_YUV16_YUYV:   Type = 8+M_UNSIGNED;     break;  \
      case M_YUV16_UYVY:   Type = 8+M_UNSIGNED;     break;  \
      case M_YUV12_1394:   Type = 8+M_UNSIGNED;     break;  \
      default:             Type = M_INVALID;        break;  \
      }


// The following MACRO compare 2 attribute and return (boolean)
//  if the internal format are equivalent. Two internal format
//  are equivalent if the internal format is equal. The YUV16
//  is a special case since M_YUV16 is used to define one
//  of the 2 YUV16 type: YUYV and UYVY
#define M_EQUIVALENT_INTERNAL_FORMAT(a,b)                                              \
   (  (a&M_INTERNAL_FORMAT) == (b&M_INTERNAL_FORMAT)                             ||    \
      ((a&M_INTERNAL_FORMAT)==M_YUV16  &&  (b&M_INTERNAL_FORMAT)==M_YUV16_YUYV)  ||    \
      ((a&M_INTERNAL_FORMAT)==M_YUV16  &&  (b&M_INTERNAL_FORMAT)==M_YUV16_UYVY)  ||    \
      ((b&M_INTERNAL_FORMAT)==M_YUV16  &&  (a&M_INTERNAL_FORMAT)==M_YUV16_YUYV)  ||    \
      ((b&M_INTERNAL_FORMAT)==M_YUV16  &&  (a&M_INTERNAL_FORMAT)==M_YUV16_UYVY)    )   \

// !!! MAP FOR OLD DEFINES
#if OldDefinesSupport
#define M_CHAR                        (M_MONO8     | M_SIGNED)
#define M_UCHAR                       (M_MONO8)
#define M_SHORT                       (M_MONO16    | M_SIGNED)
#define M_USHORT                      (M_MONO16)
#define M_LONG                        (M_MONO32    | M_SIGNED)
#define M_ULONG                       (M_MONO32)
#define M_RGB555                      (M_RGB15     | M_SIGNED)
#define M_URGB555                     (M_RGB15)
#define M_URGB888                     (M_RGB24)
#define M_RGB161616                   (M_RGB48     | M_SIGNED)
#define M_URGB161616                  (M_RGB48)
#define M_RGB323232                   (M_RGB96     | M_SIGNED)
#define M_URGB323232                  (M_RGB96)
#define M_YUV9_PLANAR                 (M_YUV9      | M_PLANAR)
#define M_YUV12_PLANAR                (M_YUV12     | M_PLANAR)
#define M_YUV16_PLANAR                (M_YUV16     | M_PLANAR)
#define M_YUV16_PACKED                (M_YUV16     | M_PACKED)
#define M_BGR15_PACKED                (M_BGR15     | M_PACKED)
#define M_RGB24_PACKED                (M_RGB24     | M_PACKED)
#define M_RGB32_PACKED                (M_RGB32     | M_PACKED)
#define M_BGR24_PACKED                (M_BGR24     | M_PACKED)
#define M_NODIBFLIP                   (M_FLIP)
#if !M_MIL_USE_LINUX
#define M_DIB_BGR24_PACKED            (M_BGR24     | M_PACKED | M_FLIP | M_DIB)
#else
#define M_DIB_BGR24_PACKED            (M_BGR24     | M_PACKED | M_FLIP )
#endif
#define M_BGR32_PACKED                (M_BGR32     | M_PACKED)
#endif

/************************************************************************/
/* MbufCreateColor() ControlFlags                                       */
/************************************************************************/
#define M_ALIGNMENT_RESERVED_BITS                     0x000000FFL
#define M_VIDEO_DEVICE_MASK                           0x00000F00L
#if M_MIL_USE_64BIT
#define M_NO_64MEG_BORDERS                            0x00000000L
#define M_NO_4GB_BORDERS                              0x00001000L
#else
#define M_NO_64MEG_BORDERS                            0x00001000L
#define M_NO_4GB_BORDERS                              0x00000000L
#endif
#define M_NO_PARSING                                  0x00002000L
#define M_WRITE_COMBINING                             16384L      // 0x00004000L
#define M_64BIT_PHYSICAL_ADDRESS                      0x00008000L
#define M_HOST_ADDRESS                                0x00010000L // Was 0x80000000L
#define M_MIL_ID                                      0x00020000L
#define M_FIRST_MIL_BUFFER                            0x00040000L
#define M_HOST_ADDRESS_REMOTE                         0x00080000L
#define M_ALLOCATION                                  0x00100000L
#define M_64BIT_HOST_ADDRESS                          0x00200000L
#define M_PHYSICAL_ADDRESS_REMOTE                     0x00400000L
#define M_DIRECTX_CREATION                            0x00800000L
#define M_CACHABLE                                    0x01000000L
#define M_LL_ID                                       0x02000000L // Was 0x00010000L
#define M_NO_MAP                                      0x04000000L
#define M_PITCH_BYTE                                  0x08000000L
#define M_DEFAULT                                     0x10000000L
#define M_PITCH                                       0x20000000L
#define M_PHYSICAL_ADDRESS                            0x40000000L

// MAKE_INT64(0x0000000080000000) // Reserved
#define M_BELOW_4GB                                   MAKE_INT64(0x0000000100000000)
#define M_ABOVE_4GB                                   MAKE_INT64(0x0000000200000000)
// MAKE_INT64(0x0000000400000000)
// MAKE_INT64(0x0000000800000000)
// MAKE_INT64(0x0000001000000000)
// MAKE_INT64(0x0000002000000000)
// MAKE_INT64(0x0000004000000000)
// MAKE_INT64(0x0000008000000000)
// MAKE_INT64(0x0000010000000000)
// MAKE_INT64(0x0000020000000000)
// MAKE_INT64(0x0000040000000000)
// MAKE_INT64(0x0000080000000000)
// MAKE_INT64(0x0000100000000000)
#define M_NON_CACHABLE                                MAKE_INT64(0x0000200000000000)
// MAKE_INT64(0x0000400000000000)
// MAKE_INT64(0x0000800000000000)
// MAKE_INT64(0x0001000000000000)
// MAKE_INT64(0x0002000000000000)
// MAKE_INT64(0x0004000000000000)
// MAKE_INT64(0x0008000000000000)
// MAKE_INT64(0x0010000000000000)
// MAKE_INT64(0x0020000000000000)
// MAKE_INT64(0x0040000000000000)
// MAKE_INT64(0x0080000000000000)
// MAKE_INT64(0x0100000000000000)
// MAKE_INT64(0x0200000000000000)
// MAKE_INT64(0x0400000000000000)
// MAKE_INT64(0x0800000000000000)
// MAKE_INT64(0x1000000000000000)
// MAKE_INT64(0x2000000000000000)
// MAKE_INT64(0x4000000000000000)
// MAKE_INT64(0x8000000000000000)


#define M_ADDRESS_ALIGNMENT(n)                                (n)

#define M_VIDEO_DEVICE_OFFSET                         8L
#define M_VIDEO_DEVICE(dev)                           ((((dev)+1)<<M_VIDEO_DEVICE_OFFSET)&M_VIDEO_DEVICE_MASK)
#define M_VIDEO_DEVICE_TO_USE(cf)                     ((((cf)&M_VIDEO_DEVICE_MASK)>>M_VIDEO_DEVICE_OFFSET)-1)

#define M_INFINITE                                    -1L
/************************************************************************/
/* MbufBlit() Values                                                    */
/************************************************************************/

// A combination of flags that determine the valid members of the MBLTDESC structure.
#define M_BLT_REGION       0x00000001L  // Uses the lRegion member of the MBLTDESC structure to determine which region to copy.
#define M_BLT_MODE         0x00000002L  // Uses the lMode member of the MBLTDESC structure to determine if the blit is synchronous or not.
#define M_BLT_TYPE         0x00000004L  // Uses the lType member of the MBLTDESC structure to determine the type of the copy.
#define M_BLT_DESTRECT     0x00000008L  // Uses the lDestRect member of the MBLTDESC structure to determine the valid destination rectangle.
#define M_BLT_SRCRECT      0x00000010L  // Uses the lSrcRect member of the MBLTDESC structure to determine the valid source rectangle.



// Indicate which region (M_BLT_REGION) to copy from the source buffer to the destination buffer (the default is M_BLT_FRAME).
// The valid values for this member are:
#define M_BLT_FRAME        1  // Blit all lines of the source buffer in the destination buffer. ***DEFAULT***
#define M_BLT_ODD          2  // Blit all lines from the sources buffer to ODD lines of the destination buffer.
#define M_BLT_EVEN         3  // Blit all lines from the sources buffer to EVEN lines of the destination buffer.
#define M_BLT_ODD_ODD      4  // Blit ODD lines from the sources buffer to ODD lines of the destination buffer.
#define M_BLT_EVEN_EVEN    5  // Blit EVEN lines from the sources buffer to EVEN lines of the destination buffer.

// Indicate if the blit (M_BLT_MODE) is done asynchronously or synchronously (the default is synchronously). The valid value are:
#define M_BLT_ASYNC        10  // Performs this blit asynchronously.
#define M_BLT_SYNC         11  // Performs this blit synchronously. ***DEFAULT***

// Indicate which type (M_BLT_TYPE) of copy is performed (the default is a normal blit, M_SCRCOPY). The valid values are:
#define M_BLT_SRCCOPY               20  // Performs a normal blit. (only supported by M_BLT_FRAME) ***DEFAULT***
#define M_BLT_SRCKEYONBLACK         21  // Performs a blit with black keying. (only supported by M_BLT_FRAME)
#define M_BLT_SRCMIRRORLEFTRIGHT    22 // This blit mirrors the surface from left to right (y-axis).
#define M_BLT_SRCMIRRORUPDOWN       23 // This blit mirrors the surface from top to bottom (x-axis).
#define M_BLT_SRCMIRRORLRUPDN       24 // This blit mirrors the surface from top to bottom and from left to right.
#define M_BLT_SCALELINEAR           25
#define M_BLT_SCALENEAR             26
#define M_BLT_SCALECONSTANT         27
#define M_BLT_SCALEYUV2BGR          28
#define M_BLT_SCALEYUV2Y            29
#define M_BLT_SCALEYUV              30

#ifdef M_USE_MBUFBLIT
// ****************************************************************************
//
// Description of the MBLTDESC_VER1 structure :
//
//    lSize :        Size of the structure, in bytes. This member must be
//                   initialized before the structure is used.
//    lValidMembers: A combination of flags that determine the valid members of
//                   the MBLTDESC structure.
//    lRegion:       Indicate which region to copy from the source buffer to
//                   the destiantion buffer (the default is M_BLT_FRAME).
//    lMode:         Indicate if the blit is done asynchronously or
//                   synchronously (the default is synchronously).
//    lType:         Indicate which type of copy is performed (the default
//                   is a normal blit, M_SCR_COPY).
//    DestRect:      RECT structure that defines the upper-left and lower-right
//                   points of the rectangle to blit to on the destination
//                   surface. If this parameter is set to ZERO, the entire
//                   destination surface is used.
//    SrcRect:       RECT structure that defines the upper-left and lower-right
//                   points of the rectangle to blit from on the source surface.
//                   If this parameter is set to ZERO, the entire source surface
//                   is used.
//    lpDDDestSurface: Address of the destination direct draw surface used for
//                   the copy. MIL will fill automaticaly this member is the blit
//                   is valid. Use this member if you want to know if an
//                   asynchronously blit is done (GetBltStatus(DDGBS_ISBLTDONE)).
//    lSrcType:      Indicate which type of protocole to use for the source (FB, PCI or AGP)
//    lDestType:     Indicate which type of protocole to use for the destination (FB, PCI or AGP)
//
// ****************************************************************************

#if !(M_MIL_USE_PPC || M_MIL_USE_LINUX)
typedef struct _MBLTDESC_VER1 {
   long        lSize;
   long        lValidMembers;
   long        lRegion;
   long        lMode;
   long        lType;
   RECT        DestRect;
   RECT        SrcRect;
   LPDIRECTDRAWSURFACE lpDDDestSurface;
   long        lSrcType;
   long        lDestType;
   } MBLTDESC_VER1;
typedef MBLTDESC_VER1 *LPMBLTDESC_VER1;

typedef MBLTDESC_VER1 MBLTDESC;

typedef MBLTDESC *LPMBLTDESC;
#endif // M_MIL_USE_PPC

#define M_INIT_STRUCT(x) (memset(&x,0,sizeof(x)), x.lSize=sizeof(x))
#endif // M_USE_MBUFBLIT



/************************************************************************/
/* MbufCopyCond  conditions                                             */
/************************************************************************/
#define M_EQUAL                                       3L
#define M_NOT_EQUAL                                   4L
#define M_BGRX32_COMPOSITION                          5L

/************************************************************************/
/* MbufGet(), MbufPut(), MbufChild(), ...                               */
/************************************************************************/
#define M_RED                                         0x08L
#define M_GREEN                                       0x10L
#define M_BLUE                                        0x20L
#define M_ALL_BAND                                    -1L
#define M_ALL_BANDS                                   M_ALL_BAND
#define M_HUE                                         0x00008000L
#define M_SATURATION                                  0x2000L
#define M_LUMINANCE                                   0x00020000L   // M_GRAB_INPUT_GAIN
#define M_CHROMINANCE                                 0x00040000L   // M_GRAB_INPUT_GAIN
#define M_Y                                           M_RED
#define M_U                                           M_GREEN
#define M_V                                           M_BLUE
#define M_DITHERING                                   0x2000L
#define M_CBCR                                        0x4000L

#define M_ALL_BITS                                    -1L
#define M_DONT_CARE                                   0x00008000L
#if !M_MIL_USE_LINUX
#define M_CHILD_ALLOC_LOSABLE_ATTRIBUTE               (M_DIRECTX|M_DIB|M_GDI|M_BITMAP_HANDLE|M_MTX0)
#else
#define M_CHILD_ALLOC_LOSABLE_ATTRIBUTE               (M_GDI|M_MTX0|M_LINUX_MXIMAGE|M_LINUX_MXVMIL|M_LINUX_MXDGA)
#endif

/************************************************************************/
/* MbufTransfer()                                                       */
/************************************************************************/
/*Transfer function value*/
#define M_DEFAULT                                     0x10000000L
#define M_CLEAR                                       0x00000001L
#define M_AUTO_SCALE                            2L  //0x00000002L
#define M_BIT_SHIFT                             3L  //0x00000003L
#define M_WINDOW_RANGE                       3072L  //0x00000C00L
#define M_COMPOSITION                                 0x00001000L
#define M_COPY_EVEN                                   0x00002000L
#define M_COPY_ODD                                    0x00004000L
#define M_COPY_TO_HWND                                0x00010000L
#define M_COPY                                        0x00020000L
#define M_REPLICATE                                   0x00040000L
#define M_SCALE                                       0x00008010L    // Can be added to some functions like M_COPY
#define M_BYTE_SWAP                                   0x00080000L
#define M_BINARIZE                                    0x00100000L
#define M_LUT_MAP                                     0x00200000L
#define M_COLOR_MATCH                                 0x00400000L
#define M_ALPHA_BLENDING                              0x00800000L
/*Transfer type*/
#define M_DEFAULT                                     0x10000000L
#define M_MIL_METHOD                                  0x01000000L
#define M_DRIVER_METHOD                               0x02000000L
#define M_DIRECTX_METHOD                              0x00001000L
#define M_MTX0_METHOD                                 0x00002000L
#define M_DRAWDIB_METHOD                              0x00004000L
#define M_BITBLT_METHOD                               0x00008000L
#define M_STRETCHBLT_METHOD                           0x00010000L
#define M_DIBTODEV_METHOD                             0x00020000L
#define M_STRETCHDIB_METHOD                           0x00040000L
#define M_DIB_METHOD                                  (M_DRAWDIB_METHOD|M_BITBLT_METHOD|M_STRETCHBLT_METHOD|M_DIBTODEV_METHOD|M_STRETCHDIB_METHOD)
#define M_LINUX_METHOD                                0x00080000L
#define M_LINUX_DGA_METHOD                            0x00100000L
#define M_NON_DISPLAY_METHOD                          MIL_MAKE_CONST(0xEF000000L,0x00000000EF000000)
#define M_DISPLAY_METHOD                              0x00FFF000L
/*Double name for the documentation*/
#define M_MIL_MODE                                    M_MIL_METHOD
#define M_DRIVER_MODE                                 M_DRIVER_METHOD
#define M_DIRECTX_MODE                                M_DIRECTX_METHOD
#define M_MTX0_MODE                                   M_MTX0_METHOD
#define M_DRAWDIB_MODE                                M_DRAWDIB_METHOD
#define M_BITBLT_MODE                                 M_BITBLT_METHOD
#define M_STRETCHBLT_MODE                             M_STRETCHBLT_METHOD
#define M_DIBTODEV_MODE                               M_DIBTODEV_METHOD
#define M_STRETCHDIB_MODE                             M_STRETCHDIB_METHOD
#define M_DIB_MODE                                    M_DIB_METHOD   /*NOTE: DibMode is also a BufInquire (old displays)*/
#define M_LINUX_MODE                                  M_LINUX_METHOD

#define M_SYNCHRONOUS                                 0x00000001L
#define M_ASYNCHRONOUS                                0x00000002L

#define M_ALLOW_LARGER_RECT                           0x00000100L
#define M_CAN_GROW_RECT                               M_ALLOW_LARGER_RECT
#define M_USE_REGION                                  0x00000200L
#define M_BILINEAR                                    0x00000008L
#define M_BICUBIC                                     0x00000010L
#define M_NEAREST_NEIGHBOR                            0x00000040L
#define M_USE_MP_FOR_TRANSFER                         0x00000080L
#define M_BILINEAR_RENDERING                          0x00000400L

/*Mask used to retreive field in the transfer type*/
#define M_ALL_METHOD                                  MIL_MAKE_CONST(0xEFFFF000L,0x00000000EFFFF000)    // M_DISPLAY_METHOD | M_NON_DISPLAY_METHOD
#define M_NB_OF_TRANSFER_METHOD                               19L    // Must be equal to CountSetBit(M_ALL_METHOD)
#define M_TRANSFER_METHOD                             MIL_MAKE_CONST(0xFFFFF000L,0x00000000FFFFF000)
#define M_SCALING_METHOD                              (M_BILINEAR|M_BILINEAR_RENDERING|M_BICUBIC|M_NEAREST_NEIGHBOR)
#define M_TRANSFER_TYPE_KNOWN_BITS                    (M_TRANSFER_METHOD|M_SCALING_METHOD|M_USE_REGION|M_ALLOW_LARGER_RECT|M_SYNCHRONOUS|M_ASYNCHRONOUS|M_USE_MP_FOR_TRANSFER)
/*Structure used with autoscale in internal mode (passed to the function*/
/* via the extended void pointer*/
typedef struct _MBTAUTOSCALE {
   double      Minimum;
   double      Maximum;
   MIL_ID      LutId;
   } MBTAUTOSCALE;
typedef MBTAUTOSCALE *LPMBTAUTOSCALE;


/************************************************************************/
/* MbufImport(), MbufExport()                                           */
/************************************************************************/
#define M_RESTORE                                     0x10L

#define M_LOAD                                        1L


#define M_MIL                                         1L
#define M_RAW                                         2L
#define M_TIFF                                        4L
#define M_BMP                                         64L
#define M_JPEG                                        5L // Internal use only
#define M_RIFF                                        6L // Internal use only
#define M_JPEG2K_RAW                                  7L // Internal use only
#define M_JPEG2K_JP2                                  8L // Internal use only
#define M_TIFF_COMPRESS                               16L
#define M_TIFF_COMPRESS_2                             32L

// Compression type
#define M_TIFF_NO_COMPRESSION                         1L
#define M_TIFF_CCITT_3                                2L
#define M_TIFF_CCITT_3_T4_ENCODING                    3L
#define M_TIFF_CCITT_4_T6_ENCODING                    4L
#define M_TIFF_PACK_BITS                              32773L

#define M_JPEG_LOSSLESS                               0x00400000L
#define M_JPEG_LOSSY                                  0x00800000L
#define M_JPEG_LOSSLESS_INTERLACED                    0x00C00000L
#define M_JPEG_LOSSY_INTERLACED                       0x08000000L
#define M_JPEG2000_LOSSY                              0x08400000L
#define M_JPEG2000_LOSSLESS                           0x08800000L

// Special file formats for import and export.
#define M_JPEG_LOSSY_RGB                              0x01000000L
#define M_JPEG2000_LOSSY_JP2                          M_JPEG2000_LOSSY+M_JPEG2K_JP2
#define M_JPEG2000_LOSSLESS_JP2                       M_JPEG2000_LOSSLESS+M_JPEG2K_JP2

#define M_PLANAR                                      0x00040000L

#define M_WITH_CALIBRATION                            0x00020000L
#define M_NO_REGION                                   0x00010000L

#define M_INTERACTIVE                                 M_NULL


/************************************************************************/
/* MbufImportSequence(), MbufExportSequence()                           */
/************************************************************************/
#define M_RESTORE                                     0x10L

#define M_LOAD                                        1L

#define M_AVI_MIL                                     128L
#define M_AVI_DIB                                     256L // Standard Windows AVI files.
#define M_AVI_MJPG                                    512L
#define M_AVI_MJPEG                                   M_AVI_MJPG
#define M_AVI_MPG4                                    1024L
#define M_AVI_MPEG4                                   M_AVI_MPG4
#define M_AVI_H264                                    2048L
#define M_DEFAULT                                     0x10000000L

// Import/Export Control Flags.
#define M_DEFAULT                                     0x10000000L         /* Create a file-Write/Read-Close           */
#define M_APPEND                                      0x20000000L         /* Open-Append-Close                        */
#define M_READ                                        1                   /* Read from an opened file.                */
#define M_WRITE                                       2                   /* Write into an opened file.               */
#define M_OPEN                                        0x00000010L         /* Open a file to Read/Write( with create ) */
#define M_CLOSE                                       0x00000020L         /* Close an open file.                      */
#define M_OPEN_APPEND                                 (M_OPEN + M_APPEND) /* Open an existing file to append into.    */

#define M_INTERACTIVE                                 M_NULL


/************************************************************************/
/* MbufLoad()                                                           */
/************************************************************************/
#define M_INTERACTIVE                                 M_NULL


/************************************************************************/
/* MbufSave()                                                           */
/************************************************************************/
#define M_INTERACTIVE                                 M_NULL


/************************************************************************/
/* MbufRestore()                                                        */
/************************************************************************/
#define M_INTERACTIVE                                 M_NULL


/************************************************************************/
/* MbufControlNeighborhood()                                            */
/************************************************************************/
#define M_ABSOLUTE_VALUE                              50L
#define M_NORMALIZATION_FACTOR                        52L
#define M_OVERSCAN                                    53L
#define M_OVERSCAN_REPLACE_VALUE                      54L
#define M_OFFSET_CENTER_X                             55L
#define M_OFFSET_CENTER_Y                             56L
#define M_FILTER_MODE                                 122L     // Already defined in miledge.h
#define M_FILTER                                      1046L    // Already defined in miledge.h
#define M_FILTER_TYPE                                 M_FILTER // Already defined in miledge.h
#define M_FILTER_OPERATION                            57L
#define M_SMOOTHNESS                                  108L         // Already defined in    milmod.h, milmeas.h, mil.h
#define M_FILTER_SMOOTHNESS                           M_SMOOTHNESS // Already defined in    mil.h, milmeas.h
#define M_ENABLE                                      -9997L
#define M_DISABLE                                     -9999L
#define M_TRANSPARENT                                 0x01000059L
#define M_REPLACE                                     0x01000060L
#define M_MIRROR                                      0x01000061L
#define M_REPLACE_MAX                                 0x01000063L
#define M_REPLACE_MIN                                 0x01000064L
#define M_SATURATION                                  0x2000L


/************************************************************************/
/* MbufInquire() / MbufControl() Types                                  */
/************************************************************************/
#define M_SIZE_BAND                                   1005L
#define M_SIZE_BAND_LUT                               1006L
#define M_SIZE_BIT                                    1007L
#define M_TYPE                                        1008L
#define M_NUMBER                                      1009L
#define M_INIT_FLAG                                   1012L
#define M_ATTRIBUTE                                   1013L
#define M_SIGN                                        1014L
#define M_NATIVE_ID                                   1016L
#define M_NATIVE_CONTROL_ID                           1017L
#define M_MAP                                         1018L
#define M_DISPLAY_STRUCT_FOR_MAPPABLE_BUFFER          1019L
#define M_MAP_REMOTE                                  1020L
#define M_SURFACE                                     1021L
//1022L was used by M_DDRAW_SURFACE, that is now in the Buffer Display reserved area.
#define M_OWNER_SYSTEM_TYPE                           1023L
//#if M_MIL_USE_64BIT
#define M_EXTENDED_FORMAT                             1026L
#define M_EXTENDED_ATTRIBUTE                          1027L
//#else
//#define M_EXTENDED_FORMAT                             M_FORMAT
//#define M_EXTENDED_ATTRIBUTE                          M_ATTRIBUTE
//#endif
#define M_INTER_SYSTEM_COPY                           1029L
#define M_DEST_INTER_SYSTEM_COPY                      1029L
#define M_BUF_MODIFIED_HOOKED                         1030L
#define M_MAP_HOST_ADDRESS                            1031L
#define M_REFRESH_REMOTE_GRAB_BUFFERS                 1032L
#define M_REMOTE_GRAB_BUFFERS                         1033L
#define M_CALL_HOOKS                                  1034L
#define M_CALL_STATE_MACHINE_PRE_BUF_MODIFIED_HOOKS   1035L
#define M_CALL_STATE_MACHINE_POST_BUF_MODIFIED_HOOKS  1036L
#define M_REFRESH_REMOTE_GRAB_BUFFERS_AFTER_SET_SCHEME 1037L
#define M_DRIVER_ASYNC_CALL_BW                        1038L
#define M_EFFECTIVE_SIZE_BIT                          1039L
#define M_DIG_PROCESS_PTR                             1040L
#define M_DATA_FORMAT                                 1041L
#define M_SET_MODIFIED_RECT_EMPTY                     1042L
#define M_IS_INTERNALLY_ALLOCATED                     1043L
#define M_SRC_INTER_SYSTEM_COPY                       1044L
#define M_SATURATION_SIZE_BIT                         1045L
//1046L is used by M_FILTER_TYPE, in the MbufControlNeighborhood area.
#define M_SATURATION_TYPE                             1047L
#define M_LOCATION                                    1048L
#define M_SYSTEM_LOCATION                             M_LOCATION
#define M_MIL_ID_INTERNAL                             1049L
#define M_REAL_FORMAT                                 1050L
#define M_SET_LOCKED_BUFFER_HOST_ADDRESS              1051L
#define M_SET_LOCKED_BUFFER_PHYSICAL_ADDRESS          1052L
#define M_GPU_ACCESS_ONLY                             1053L
#define M_DATA_STORAGE_MODE                           1054L
#define M_REGION_STREAM_SIZE_BYTE                     1055L
#define M_REGION_COPY                                 1056L
#define M_REGION_COMBINATION                          1057L
#define M_REGION_TYPE                                 1058L
#define M_DRIVER_ASYNC_CALL                           1060L

/************************************************************************/
/* MbufInquire() Types MIL_ID range start                               */
/************************************************************************/
// Inquire value with MIL_ID type must be in that range : 1100-1199
#define M_BUF_INQUIRE_MIL_ID_START                    1100L
#define M_OWNER_SYSTEM                                1101L
#define M_LUT_ID                                      1102L
#define M_PARENT_ID                                   1103L
#define M_ANCESTOR_ID                                 1104L
#define M_PROC_HOST_ID                                1105L
#define M_HOST_ID                                     1106L
#define M_DRIVER_ID                                   1107L
#define M_ASSOCIATED_AUDIO_BUFFER_ID                  1108L/////ADDED//////
#define M_ASSOCIATED_LUT                              1110L
#define M_REGION_GRAPHIC_LIST_ID                      1111L
#define M_REGION_BUFFER_ID                            1112L
#define M_REGION_BUFFER_IN_SYNC                       1113L

#define M_HUFFMAN_DC_LUMINANCE                        1120L // Buffer M_COMPRESS Jpeg
#define M_HUFFMAN_AC_LUMINANCE                        1121L // Buffer M_COMPRESS Jpeg
#define M_HUFFMAN_DC_CHROMINANCE                      1122L // Buffer M_COMPRESS Jpeg
#define M_HUFFMAN_AC_CHROMINANCE                      1123L // Buffer M_COMPRESS Jpeg
#define M_HUFFMAN_DC                                  1124L // Buffer M_COMPRESS Jpeg
#define M_HUFFMAN_AC                                  1125L // Buffer M_COMPRESS Jpeg
#define M_QUANTIZATION_LUMINANCE                      1126L // Buffer M_COMPRESS Jpeg
#define M_QUANTIZATION_CHROMINANCE                    1127L // Buffer M_COMPRESS Jpeg

// M_QUANTIZATION + M_ALL_BAND                        1151L
#define M_QUANTIZATION                                1152L
// M_QUANTIZATION + M_RED                             1160L // 1152+0x08
// M_QUANTIZATION + M_GREEN                           1168L // 1152+0x10
// M_QUANTIZATION + M_BLUE                            1184L // 1152+0x20

#define M_BUF_INQUIRE_MIL_ID_END                      1199L

/************************************************************************/
/* MbufInquire() Types MIL_ID range end                                 */
/************************************************************************/

#define M_GNL_ID                                      1230L
#define M_ONL_ID                                      M_GNL_ID

#define M_SIZE_X                                      1536L // 0x600
#define M_SIZE_Y                                      1537L // 0x601
#define M_SIZE_Z                                      1538L // 0x602

#define M_SIZE_X_RED                                  M_SIZE_X + M_RED // 1544L or 0x608
#define M_SIZE_Y_RED                                  M_SIZE_Y + M_RED // 1545L or 0x609
#define M_SIZE_Z_RED                                  M_SIZE_Z + M_RED // 1546L or 0x60A

#define M_SIZE_X_GREEN                                M_SIZE_X + M_GREEN // 1552L or 0x610
#define M_SIZE_Y_GREEN                                M_SIZE_Y + M_GREEN // 1553L or 0x611
#define M_SIZE_Z_GREEN                                M_SIZE_Z + M_GREEN // 1554L or 0x612

#define M_SIZE_X_BLUE                                 M_SIZE_X + M_BLUE // 1568L or 0x620
#define M_SIZE_Y_BLUE                                 M_SIZE_Y + M_BLUE // 1569L or 0x621
#define M_SIZE_Z_BLUE                                 M_SIZE_Z + M_BLUE // 1570L or 0x622


// The difference between the following defines must be >= 2. The bits
// M_RED, M_GREEN, M_BLUE, i.e. 4, 5 and 6 (zero-based) of the flags
// must also always be cleared.

// M_NUMBER_SUBBAND + M_ALL_BAND                      2559L
#define M_NUMBER_SUBBAND                              2560L
// M_NUMBER_SUBBAND + M_RED                           2568L // 2560+0x08
// M_NUMBER_SUBBAND + M_GREEN                         2576L // 2560+0x10
// M_NUMBER_SUBBAND + M_BLUE                          2592L // 2560+0x20

// M_DECOMPOSITION_LEVEL + M_ALL_BAND                 2561L
#define M_DECOMPOSITION_LEVEL                         2562L
// M_DECOMPOSITION_LEVEL + M_RED                      2570L // 2562+0x08
// M_DECOMPOSITION_LEVEL + M_GREEN                    2578L // 2562+0x10
// M_DECOMPOSITION_LEVEL + M_BLUE                     2594L // 2562+0x20

// Note : also used in JPEG.
// M_Q_FACTOR + M_ALL_BAND                            2563L
#define M_Q_FACTOR                                    2564L
// M_Q_FACTOR + M_RED                                 2572L // 2564+0x08
// M_Q_FACTOR + M_GREEN                               2580L // 2564+0x10
// M_Q_FACTOR + M_BLUE                                2596L // 2564+0x20

// M_CODE_BLOCK_SIZE_X + M_ALL_BAND                   2565L
#define M_CODE_BLOCK_SIZE_X                           2566L
// M_CODE_BLOCK_SIZE_X + M_RED                        2574L // 2566+0x08
// M_CODE_BLOCK_SIZE_X + M_GREEN                      2582L // 2566+0x10
// M_CODE_BLOCK_SIZE_X + M_BLUE                       2598L // 2566+0x20

// M_CODE_BLOCK_SIZE_Y + M_ALL_BAND                   2599L
#define M_CODE_BLOCK_SIZE_Y                           2600L
// M_CODE_BLOCK_SIZE_Y + M_RED                        2608L // 2600+0x08
// M_CODE_BLOCK_SIZE_Y + M_GREEN                      2616L // 2600+0x10
// M_CODE_BLOCK_SIZE_Y + M_BLUE                       2632L // 2600+0x20

// M_QUANTIZATION_INTERNAL + M_ALL_BAND               2601L
#define M_QUANTIZATION_INTERNAL                       2602L
// M_QUANTIZATION_INTERNAL + M_RED                    2610L // 2602+0x08
// M_QUANTIZATION_INTERNAL + M_GREEN                  2618L // 2602+0x10
// M_QUANTIZATION_INTERNAL + M_BLUE                   2634L // 2602+0x20

// M_QUANTIZATION_MODIFIED + M_ALL_BAND               2603L
#define M_QUANTIZATION_MODIFIED                       2604L
// M_QUANTIZATION_MODIFIED + M_RED                    2612L // 2604+0x08
// M_QUANTIZATION_MODIFIED + M_GREEN                  2620L // 2604+0x10
// M_QUANTIZATION_MODIFIED + M_BLUE                   2636L // 2604+0x20

// M_PRECINCT_SIZE_X + M_ALL_BAND                     2605L
#define M_PRECINCT_SIZE_X                             2606L
// M_PRECINCT_SIZE_X + M_RED                          2614L // 2606+0x08
// M_PRECINCT_SIZE_X + M_GREEN                        2622L // 2606+0x10
// M_PRECINCT_SIZE_X + M_BLUE                         2638L // 2606+0x20

// M_PRECINCT_SIZE_Y + M_ALL_BAND                     2639L
#define M_PRECINCT_SIZE_Y                             2640L
// M_PRECINCT_SIZE_Y + M_RED                          2648L // 2640+0x08
// M_PRECINCT_SIZE_Y + M_GREEN                        2656L // 2640+0x10
// M_PRECINCT_SIZE_Y + M_BLUE                         2672L // 2640+0x20

// M_QUANTIZATION_STYLE + M_ALL_BAND                  2641L
#define M_QUANTIZATION_STYLE                          2642L
// M_QUANTIZATION_STYLE + M_RED                       2650L // 2642+0x08
// M_QUANTIZATION_STYLE + M_GREEN                     2658L // 2642+0x10
// M_QUANTIZATION_STYLE + M_BLUE                      2674L // 2642+0x20



#define M_MODIFIED                                    4096L  //bitwise value 0x00001000

#define M_INTER_SYSTEM_ID                             5000L
#define M_PARENT_OFFSET_X                             5003L
#define M_PARENT_OFFSET_Y                             5004L
#define M_ANCESTOR_OFFSET_X                           5005L
#define M_ANCESTOR_OFFSET_Y                           5006L
#define M_PARENT_OFFSET_BAND                          5007L
#define M_ANCESTOR_OFFSET_BAND                        5008L
#define M_NB_CHILD                                    5009L
#define M_MODIFICATION_COUNT                          5010L
#define M_ANCESTOR_SIZE_X                             5012L
#define M_HOST_ADDRESS_FAR                            5013L
#define M_CURRENT_BUF_ID                              5015L
#define M_ASSOCIATED_BUFFER_ID                        5016L
#define M_MAP_BUFFER_TO_HOST                          5017L
#define M_DMA_BUFFER                                  5021L
#define M_DMA_BUFFER_PTR                              5022L
#define M_DMA_BUFFER_PHYSICAL_PTR                     5023L
#define M_VALID_GRAB_BUFFER                           5025L
#define M_VALID_GRAB_BUFFER_OFFSET                    5026L
#define M_LOW_LEVEL_BUFFER_ID                         5027L
#define M_BUFFER_INFO_OLD                             5028L
#define M_MEMBANK                                     5029L // Pulsar internal use only
#define M_LOCPOS_X                                    5030L // Pulsar internal use only
#define M_LOCPOS_Y                                    5031L // Pulsar internal use only
#define M_LOCPOS_BIT                                  5032L // Pulsar internal use only
#define M_ON_BOARD_DISP_BUFFER_NATIVE_ID              5033L // Pulsar internal use only
#define M_ON_BOARD_DISP_BUFFER_MIL_ID                 5034L // Pulsar internal use only
#define M_VGA_DISP_BUFFER_ID                          5035L // Pulsar internal use only
#define M_OVR_DISP_BUFFER_ID                          5036L // Pulsar internal use only
#define M_MEMORG                                      5037L // Pulsar internal use only
#define M_ANCESTOR_OFFSET_BIT                         5038L
#define M_DIB_MODE                                    M_DIB_METHOD // 0x0007C000
#define M_FLIP_MODE                                   5040L
#define M_COMPRESSION_TYPE                            5045L
#define M_PREDICTOR                                   5052L // Buffer M_COMPRESS Jpeg
#define M_Q_FACTOR_LUMINANCE                          5056L // Buffer M_COMPRESS Jpeg
#define M_Q_FACTOR_CHROMINANCE                        5057L // Buffer M_COMPRESS Jpeg
#define M_RESTART_INTERVAL                            5059L // Buffer M_COMPRESS Jpeg
#define M_JPEG_HW_PROG                                5060L // Buffer M_COMPRESS Jpeg
#define M_SIZE_BYTE                                   5061L
#define M_INTERNAL_COMPRESSION_BUFFER_ID              5063L
#define M_INTERNAL_BUFFER_HOST_ADDRESS                5064L
#define M_INTERNAL_JPEG_FRAME_SIZEBYTE                5065L
#define M_INTERNAL_COMPRESSION_BUFFER_SIZE_DIVISION_FACTOR  5066L
#define M_SIZE_BYTE_FIRST_FIELD                       5067L
#define M_SIZE_BYTE_SECOND_FIELD                      5068L
#define M_JPEG_COMPRESS                               5069L // Buffer M_COMPRESS Jpeg
#define M_JPEG_DECOMPRESS                             5070L // Buffer M_COMPRESS Jpeg
#define M_REGENERATE_HEADER                           5071L // Internal Use Only.
#define M_PARSE_JPEG_DATA                             5072L // Internal Use Only.
#define M_PARSE_JPEG2000_DATA                         M_PARSE_JPEG_DATA
#define M_PARSE_MPEG4_DATA                            M_PARSE_JPEG_DATA
#define M_PARSE_H264_DATA                             M_PARSE_JPEG_DATA
#define M_PARSE_COMPRESSED_DATA                       M_PARSE_JPEG_DATA
#define M_HEADER_MODIFIED                             5073L // Internal Use Only.
#define M_TARGET_SIZE                                 5074L // Set internal compression buffer size in byte
#define M_ATTACHED_BUFFER_0_ID                        5076L
#define M_ATTACHED_BUFFER_1_ID                        5077L
#define M_ASSOCIATED_VGA_BUFFER_ID                    5078L
#define M_FIELD_UPDATE_MODE                           5079L
#define M_YCRCB_RANGE                                 5080L // Obsolete, use M_YCBCR_RANGE, M_YCBCR_SD or M_YCBCR_HD instead.
#define M_MODIFICATION_HOOK                           5082L
#define M_FIELD_ORDER                                 5083L
#define M_YCBCR_RANGE                                 5085L
#define M_REVERSE_X                                   5087L
#define M_REVERSE_Y                                   5088L
#define M_SUBSAMPLE_X                                 5089L
#define M_SUBSAMPLE_Y                                 5090L
#define M_SUBSAMPLE                                   5091L
#if !M_MIL_USE_UNIFIED_MILBUFFERINFO || ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_BUFFER_INFO_BW                              5092L
#endif
#define M_BUFFER_DISPLAY_INFO_PTR                     5093L
#define M_NUMBER_OF_BUFFERS                           5094L // Used with complex surface
#define M_GRAB_BUFFERS                                5095L // Internal Use Only.
#define M_USED_IN_CONTINUOUS_GRAB                     5096L
#define M_GRAB_TYPE                                   5097L
#define M_BUF_TRANSPARENT_COLOR                       5098L

#define M_HOOK_TO_BUFFER_MODIFICATIONS                5201L
#if !M_MIL_USE_UNIFIED_MILBUFFERINFO || ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_BUFFER_INFO_COPY_BW                         5202L
#endif
#define M_CACHE_CONTROL                               5204L
#define M_HOST_ADDRESS_BAND                           5205L
/* Reserve next 16 values               from          5206L*/
/*                                      to            5221L*/
#define M_PHYS_ADDRESS_BAND                           5222L
/* Reserve next 16 values               from          5223L*/
/*                                      to            5237L*/
#define M_GRAB_BUFFERS_AFTER_SET_SCHEME               5238L
#define M_IS_PHYSICALLY_IN_CACHE                      5239L
#define M_NB_CHILD_SELECTED_ON_DISPLAY                5240L
#define M_UNSUPPORTED_FORMAT                          5241L
#define M_PREFERRED_DIGITIZER_FORMAT                  5242L
#define M_RESET_ASSOCIATED_LUT                        5243L
#define M_64BIT_HOST_ADDRESS_BAND                     5244L
/* Reserve next 16 values               from          5245L*/
/*                                      to            5259L*/
#define M_64BIT_PHYSICAL_ADDRESS_BAND                 5260
/* Reserve next 16 values               from          5261L*/
/*                                      to            5275L*/
#define M_GRAB_BUFFERS_AFTER_SET_SCHEME_NO_LOCK       5276
#define M_GRAB_BUFFERS_USED                           5277L
#define M_BGRX_ALPHA_VALUE                            5278L
#if !M_MIL_USE_UNIFIED_MILBUFFERINFO || (!M_COMPILING_MILDLL && ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x91)))
#define M_BUFFER_INFO_COPY                            M_BUFFER_INFO_COPY_BW
#define M_BUFFER_INFO                                 M_BUFFER_INFO_BW
#else
#define M_BUFFER_INFO_COPY                            5279L
#define M_BUFFER_INFO                                 5280L
#endif

#define M_IS_NO_MAP                                   5300L
#define M_CRYPTOGRAPHY                                5301L
#define M_CRYPTO                                      M_CRYPTOGRAPHY

#define M_BUF_INQUIRE_SIZEOF_INT64_START              6700L
#define M_PHYSICAL_ADDRESS_ON_BOARD                   6700L
#define M_64BIT_PHYSICAL_ADDRESS_REMOTE               6701L
//#define M_PHYSICAL_ADDRESS_ON_BOARD+M_RED             6708L
//#define M_PHYSICAL_ADDRESS_ON_BOARD+M_BLUE            6716L
//#define M_PHYSICAL_ADDRESS_ON_BOARD+M_GREEN           6732L

#define M_64BIT_PHYSICAL_ADDRESS_BAND_REMOTE          6733L
/* Reserve next 16 values               from          6733L*/
/*                                      to            6749L*/

// Inquire value with a size of 64 bit, must be in that range : 6700-6799
#define M_BUF_INQUIRE_SIZEOF_INT64_END                6799L
#define M_BUF_INQUIRE_UNKNOWN_SIZEOF_START            6800L
// Inquire value with unknown size of,
//            and require a user array, must be in that range : 6800-6899
#define M_REGION_STREAM                               6801L
#define M_BUF_INQUIRE_UNKNOWN_SIZEOF_END              6899L

#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL) 
// M_FORMAT is not a string when used with MbufInquire but the define
// is shared with MdispInquire and MdigInquire
#define M_FORMAT                                      (7701L|M_CLIENT_ASCII_MODE)
#else
// M_FORMAT is not a string when used with MbufInquire but the define
// is shared with MdispInquire and MdigInquire
#define M_FORMAT                                      7701L
#endif

#define M_CACHE_FLUSH                                 8192L

// Flags related to JPEG2000.

/* Reserve next 10 values               from          8193L */
/*                                      to            8202L */

#define M_OPERATION_MODE                              8203L

#define M_REGULAR                                     0x00020000L /* already defined elsewhere in mil.h */
#define M_PRECISE                                     0x00040000L

#define M_DEFAULT_QUANTIZATION_TABLE                  8204L

#define M_LEGACY                                      1L
#define M_STANDARD                                    2L

#define M_USER_DATA_SIZE                              8205L

// Note : also used in JPEG.
#define M_ALLOCATE_MEMORY                             8206L
#define M_SHRINK_MEMORY                               8207L
#define M_ALLOCATED_SIZE_BYTE                         8208L
#define M_COMPRESSED_DATA_SIZE_BYTE                   8209L

#define M_CODESTREAM_FORMAT                           8210L

#define M_READ                                        1
#define M_WRITE                                       2
#define M_LOCK_ACCESS_MASK                            (M_READ|M_WRITE)

// DirectX Lock Types
#define M_RT_GPU_ACCESS                               0x00000004L
#define M_HOST_ACCESS                                 0x00000008L
#define M_GPU_ACCESS                                  0x00000010L

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_LOCK_TYPE_MASK                              (M_GPU_ACCESS|M_HOST_ACCESS|M_RT_GPU_ACCESS)
#else
#define M_DMA_ACCESS                                  0x00000020L
/* Following bitwise values are reserved for future DirectX Lock Types
                                                      0x00000040L
                                                      0x00000080L
                                                      0x00000100L
                                                      0x00000200L
                                                      0x00000400L
                                                      0x00000800L */
#define M_LOCK_TYPE_MASK                              0x00000FFCL
#endif

#define M_LOCK_UNLOCK_MASK                            (M_LOCK_TYPE_MASK|M_LOCK_ACCESS_MASK)

#define M_RAW_FORMAT                                  0L
#define M_JP2_FORMAT                                  2L

#define M_BATCH_COUNT                                 8211L
#define M_BATCH_FLAGS                                 8212L
#define M_BATCH_INQUIRE                               8213L
#define M_PROGRESSION_ORDER                           8214L

#define M_LAYER_RES_COMP_POS                          0L
#define M_RES_LAYER_COMP_POS                          1L
#define M_RES_POS_COMP_LAYER                          2L
#define M_POS_COMP_RES_LAYER                          3L
#define M_COMP_POS_RES_LAYER                          4L

#define M_IMAGE_OFFSET_X                              8215L
#define M_IMAGE_OFFSET_Y                              8216L
#define M_TILE_OFFSET_X                               8217L
#define M_TILE_OFFSET_Y                               8218L
#define M_TILE_SIZE_X                                 8219L
#define M_TILE_SIZE_Y                                 8220L
#define M_SOP_MARKERS                                 8221L
#define M_EPH_MARKERS                                 8222L

#define M_CODESTREAM_OFFSET                           8223L
#define M_CODESTREAM_SIZE                             8224L

//Mpeg4 related inquire
#define M_FRAME_TYPE                                  8225L
#define M_ASSOCIATED_STREAM                           8226L

#define M_LOCKABLE                                    8255

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_LOCK                                        8256
/*Reserve next 31 for other flags*/
#define M_UNLOCK                                      8288
/*Reserve next 31 for other flags*/
#define M_LOCK_TRY                                    8320
/*Reserve next 31 for other flags*/
#endif // ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))


#define M_LOCK_TYPE                                   8452
#define M_FLAGS                                       8453


// Display reserved area
#define M_BUF_DISPLAY_START                           9000L
#define M_IS_IN_DISPLAY_BUF_RANGE(X)     ((X>=M_BUF_DISPLAY_START) && (X<=M_BUF_DISPLAY_END))
#define M_DC_ALLOC                                    M_BUF_DISPLAY_START+0L  // 9000
#define M_DC_FREE                                     M_BUF_DISPLAY_START+1L  // 9001
#define M_DC_HANDLE                                   M_BUF_DISPLAY_START+2L  // 9002
#define M_XPIXMAP_ALLOC                               M_DC_ALLOC
#define M_XPIXMAP_FREE                                M_DC_FREE
#define M_XPIXMAP_HANDLE                              M_DC_HANDLE 
#define M_ENHANCE_FORMAT                              M_BUF_DISPLAY_START+3L  // 9003
#define M_DDRAW_SURFACE                               M_BUF_DISPLAY_START+4L  // 9004
#define M_DIRECTX_OWNER_COMPATIBLE                    M_BUF_DISPLAY_START+5L  // 9005
#define M_MTX0_CAPABLE_DIRECTX_OWNER                  M_BUF_DISPLAY_START+6L  // 9006
#define M_DIRECTX_OWNER                               M_BUF_DISPLAY_START+7L  // 9007
#define M_ENHANCE_FROM_ID                             M_BUF_DISPLAY_START+8L  // 9008
#define M_ENHANCE_MAX_DISPLAY_FORMAT                  M_BUF_DISPLAY_START+9L  // 9009
#define M_VIDEO_SYSTEM_ID                             M_BUF_DISPLAY_START+10L // 9010
#define M_NEXT_FREE_BUFFER                            M_BUF_DISPLAY_START+11L // 9011
#define M_OLDEST_READY_BUFFER                         M_BUF_DISPLAY_START+12L // 9012
#define M_WAIT_ON_BUFFER_FREED                        M_BUF_DISPLAY_START+13L // 9013
#define M_ENHANCE_SYSTEM_CREATE                       M_BUF_DISPLAY_START+14L // 9014
#define M_ENHANCE_GRAB_CREATE                         M_BUF_DISPLAY_START+15L // 9015
#define M_FREE_ENHANCED_BUFFER                        M_BUF_DISPLAY_START+16L // 9016
#define M_ENHANCED_BUFFER                             M_BUF_DISPLAY_START+17L // 9017
#define M_INVALID_RECT                                M_BUF_DISPLAY_START+18L // 9018
#define M_VALID_RECT                                  M_BUF_DISPLAY_START+19L // 9019
#define M_STATE_MACHINE                               M_BUF_DISPLAY_START+20L // 9020
#define M_INTERNAL_BUFFERS                            M_BUF_DISPLAY_START+21L // 9021
#define M_NB_INTERNAL_BUFFERS                         M_BUF_DISPLAY_START+22L // 9022
#define M_STATE_MACHINE_MODE                          M_BUF_DISPLAY_START+23L // 9023
#define M_REGISTER_SELECT_FIELD                       M_BUF_DISPLAY_START+24L // 9024
#define M_UNREGISTER_SELECT_FIELD                     M_BUF_DISPLAY_START+25L // 9025
#define M_BITMAPINFO                                  M_BUF_DISPLAY_START+26L // 9026
#define M_LAST_MODIFIED_BUFFER                        M_BUF_DISPLAY_START+27L // 9027
#define M_DIRECTX_SURFACE                             M_BUF_DISPLAY_START+28L // 9028
#define M_REGISTER_SELECT_FIELD_DATA                  M_BUF_DISPLAY_START+29L // 9029
#define M_UNREGISTER_SELECT_FIELD_DATA                M_BUF_DISPLAY_START+30L // 9030
#define M_DIB_HANDLE                                  M_BUF_DISPLAY_START+31L // 9031 // Also in MdispInquire section, don't change the value
#define M_DC_FREE_NO_MODIFIED_CHECK                   M_BUF_DISPLAY_START+32L // 9032
#define M_ACTIVE_BUFFER                               M_BUF_DISPLAY_START+33L // 9033

#define M_DIRECTX_SURFACE_MAPPED                      M_BUF_DISPLAY_START+35L // 9035
#define M_DIRECTX_SURFACE_MAPPABLE                    M_BUF_DISPLAY_START+36L // 9036
#define M_DIRECTX_SUB_SURFACE_INDEX                   M_BUF_DISPLAY_START+37L // 9037
#define M_NEXT_FREE_BUFFER_NO_SKIP_OR_DELAY           M_BUF_DISPLAY_START+38L // 9038
#define M_STATE_MACHINE_SKIP_MODE                     M_BUF_DISPLAY_START+39L // 9039
#define M_RELEASE_FREE_BUFFER                         M_BUF_DISPLAY_START+40L // 9040
#define M_UNENHANCE_FORMAT                            M_BUF_DISPLAY_START+41L // 9041
#define M_VIDEO_DEVICE_INDEX                          M_BUF_DISPLAY_START+42L // 9042
#define M_EXTERNAL_BUFFER_ID                          M_BUF_DISPLAY_START+43L // 9043
#define M_EXTERNAL_LL_MD_ID                           M_BUF_DISPLAY_START+44L // 9044
#define M_RESTORE_VIDEO_MEMORY                        M_BUF_DISPLAY_START+45L // 9045
#define M_DDRAW7_HANDLE                               M_DDRAW_SURFACE
#define M_D3D9_HANDLE                                 M_BUF_DISPLAY_START+46L // 9046
#define M_D3D9_SURFACE                                M_BUF_DISPLAY_START+47L // 9047
#define M_D3D9_TEXTURE                                M_BUF_DISPLAY_START+48L // 9048
#define M_D3D9_SURFACE_UP                             M_BUF_DISPLAY_START+49L // 9049
#define M_D3D9_TEXTURE_UP                             M_BUF_DISPLAY_START+50L // 9050
#define M_D3D9_SURFACE_MP                             M_BUF_DISPLAY_START+51L // 9051
#define M_D3D9_TEXTURE_MP                             M_BUF_DISPLAY_START+52L // 9052
#define M_D3D9_SURFACE_RT                             M_BUF_DISPLAY_START+53L // 9053
#define M_D3D9_SURFACE_LK                             M_BUF_DISPLAY_START+54L // 9054
#define M_D3D9_TEXTURE_LK                             M_BUF_DISPLAY_START+55L // 9055
#define M_D3D10_HANDLE                                M_BUF_DISPLAY_START+56L // 9056
#define M_REAL_HOST_ADDRESS                           M_BUF_DISPLAY_START+57L // 9057
#define M_XVIDEO_ADAPTOR_INDEX                        M_BUF_DISPLAY_START+58L // 9058
#define M_D3D10_TEXTURE                               M_BUF_DISPLAY_START+59L // 9059
#define M_D3D10_TEXTURE_UP                            M_BUF_DISPLAY_START+60L // 9060
#define M_D3D10_TEXTURE_MP                            M_BUF_DISPLAY_START+61L // 9061
#define M_D3D10_TEXTURE_LK                            M_BUF_DISPLAY_START+62L // 9062
#define M_SET_GDI_PALETTE_FROM_LUT                    M_BUF_DISPLAY_START+63L // 9063
#define M_D3D9_SURFACE_INTER                          M_BUF_DISPLAY_START+64L // 9064
#define M_D3D9_TEXTURE_INTER                          M_BUF_DISPLAY_START+65L // 9065
#define M_D3D10_TEXTURE_INTER                         M_BUF_DISPLAY_START+66L // 9066
#define M_D3D11_HANDLE                                M_BUF_DISPLAY_START+67L // 9067
#define M_D3D11_TEXTURE                               M_BUF_DISPLAY_START+68L // 9068
#define M_D3D11_TEXTURE_UP                            M_BUF_DISPLAY_START+69L // 9069
#define M_D3D11_TEXTURE_MP                            M_BUF_DISPLAY_START+70L // 9070
#define M_D3D11_TEXTURE_LK                            M_BUF_DISPLAY_START+71L // 9071
#define M_D3D11_TEXTURE_INTER                         M_BUF_DISPLAY_START+72L // 9072
#define M_D3D11_BUFFER                                M_BUF_DISPLAY_START+73L // 9073
#define M_D3D11_BUFFER_LK                             M_BUF_DISPLAY_START+74L // 9074

//////////////MAXIMAL VALUE//////////////////////////////////////////////+193L // 9193
#define M_BUF_DISPLAY_END                             9193L


// MTXDMA reserved area
#define M_BUF_MTXDMA_START                            16384L
#define M_WRITE_COMBINING                             16384L // Must be bitwise
#define M_BUFFER_CACHE                                16385L
#define M_BUFFER_CACHE_FLUSH                          16386L
#define M_BUFFER_AGP_CAPABLE                          16387L
#define M_BUFFER_KERNEL_MAP                           16388L
// Reserved 16390 to 16434 for other MTXDMA controls
#define M_BUF_MTXDMA_END                              16434L


#if !((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_BUF_DX_LOCK_UNLOCK_START                    20480L
#define M_LOCK                                        20480L   // 0x00005000
/*Reserved next 0xfff (4095) for other bitwise flags*/
#define M_UNLOCK                                      24576L   // 0x00006000
/*Reserved next 0xfff (4095) for other bitwise flags*/
#define M_LOCK_TRY                                    28672L   // 0x00007000
/*Reserved next 0xfff (4095) for other bitwise flags*/
#define M_BUF_DX_LOCK_UNLOCK_END                      32767L
#endif // !((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))

#define M_NO_QUANTIZATION                             0L
#define M_SCALAR_IMPLICIT                             1L
#define M_SCALAR_EXPLICIT                             2L

#define M_HOST_ADDRESS                                0x00010000L
#define M_HOST_ADDRESS_RED                            M_HOST_ADDRESS + M_RED    // 0x00010008L
#define M_HOST_ADDRESS_GREEN                          M_HOST_ADDRESS + M_GREEN  // 0x00010010L
#define M_HOST_ADDRESS_BLUE                           M_HOST_ADDRESS + M_BLUE   // 0x00010020L
#define M_HOST_ADDRESS_REMOTE                         0x00080000L
#define M_HOST_ADDRESS_REMOTE_RED                     M_HOST_ADDRESS_REMOTE + M_RED    // 0x00080008L
#define M_HOST_ADDRESS_REMOTE_GREEN                   M_HOST_ADDRESS_REMOTE + M_GREEN  // 0x00080010L
#define M_HOST_ADDRESS_REMOTE_BLUE                    M_HOST_ADDRESS_REMOTE + M_BLUE   // 0x00080020L
#define M_PHYSICAL_ADDRESS                            0x40000000L
#define M_PHYSICAL_ADDRESS_RED                        M_PHYSICAL_ADDRESS + M_RED    // 0x40000008L
#define M_PHYSICAL_ADDRESS_GREEN                      M_PHYSICAL_ADDRESS + M_GREEN  // 0x40000010L
#define M_PHYSICAL_ADDRESS_BLUE                       M_PHYSICAL_ADDRESS + M_BLUE   // 0x40000020L

#define M_SIZE_X                                      1536L // 0x600
#define M_SIZE_X_RED                                  M_SIZE_X + M_RED     // 1544L or 0x608
#define M_SIZE_X_GREEN                                M_SIZE_X + M_GREEN   // 1552L or 0x610
#define M_SIZE_X_BLUE                                 M_SIZE_X + M_BLUE    // 1568L or 0x620

#define M_SIZE_Y                                      1537L // 0x601
#define M_SIZE_Y_RED                                  M_SIZE_Y + M_RED     // 1545L or 0x609
#define M_SIZE_Y_GREEN                                M_SIZE_Y + M_GREEN   // 1553L or 0x611
#define M_SIZE_Y_BLUE                                 M_SIZE_Y + M_BLUE    // 1569L or 0x621

// 0x00008000L Reserved for M_ALLOCATION_OVERSCAN that is MsysControl\Inquire type and as buffer attribute.
#define M_ALLOCATION_OVERSCAN_SIZE                    0x00008001L
#define M_PHYSICAL_ADDRESS                            0x40000000L
#define M_PITCH                                       0x20000000L
#define M_DEFAULT                                     0x10000000L
#define M_PITCH_BYTE                                  0x08000000L

// MbufControl and MbufInquire double range start
#define M_MIN                                         0x02000000L
#define M_MAX                                         0x04000000L
// MbufControl and MbufInquire double range end

// !!! MAP FOR OLD DEFINES
#if OldDefinesSupport
#define M_DMA_READ_HOST_ID                            M_HOST_ID
#define M_BUF_ASSOCIATED_BUFFER_ID                    M_ASSOCIATED_BUFFER_ID
#define M_WINDOW_DDRAW_SURFACE                        M_DDRAW_SURFACE
#define M_WINDOW_DC_ALLOC                             M_DC_ALLOC
#define M_WINDOW_DC_FREE                              M_DC_FREE
#define M_WINDOW_DC                                   M_DC_HANDLE
#endif



/************************************************************************/
/* MbufControl() MbufInquire() Values                                   */
/************************************************************************/
#define M_MAX_INTERNAL_BUFFERS                        8L
#define M_MAX_NB_GRAB_BUFFERS                         8L

#define M_MEGABUFFER_GRAB                    0x08000000L

#define M_ODD_FIELD                                   1L
#define M_EVEN_FIELD                                  2L
#define M_BOTH_FIELDS                                 3L
#define M_NO_HOOK                            0x00000004L
#define M_GRAB_TYPE_PSEUDO                            5L
#define M_GRAB_TYPE_LIVE                              6L
#define M_GRAB_TYPE_PSEUDO_MULTIPLE_BUFFERS           7L
#define M_GRAB_TYPE_NO_TEARING                        8L
#define M_GRAB_TYPE_ENCODER                           9L
#define M_GRAB_TYPE_PSEUDO_SINGLE_BUFFER              10L
#define M_GRAB_FORCE_IN_USER_BUFFER                   11L
#define M_GRAB_FORCE_WITHOUT_UNDERLAY                 12L
#define M_UNCONDITIONAL                               0L

#define M_CONDITIONAL                                 1L
#define M_NOT_IN_CACHE                                0L
#define M_IN_CACHE                                    1L
#define M_NOT_CACHABLE                                2L
#define M_CACHABLE                                    0x01000000L

// State machine type
#define M_INVALID                                     -1
#define M_DEFAULT                            0x10000000L
#define M_WITH_VSYNC                                  1L
#define M_WITHOUT_VSYNC                               2L
#define M_WITHOUT_STATE                               3L
// State machine mode
#define M_FRAME                                       30L
#define M_FIELD                               0x001C0000L


#define M_IS_PHYSICALLY_IN_CACHE                    5239L

#define  M_YCBCR_SD                                   1L
#define  M_YCBCR_HD                                   2L

#define M_MPEG_P_FRAME                                0L
#define M_MPEG_I_FRAME                                1L
#define M_MPEG_B_FRAME                                2L

#define M_ODD_EVEN                                    1L
#define M_EVEN_ODD                                    2L

#define M_INCREMENT                                   1L
#define M_DECREMENT                                   2L
#define M_INTERNAL_THREAD_CALL               0x00000004L

#define M_LUT_REPLICATE_2X                            1L
#define M_LUT_REPLICATE_4X                            2L
#define M_LUT_ADDRESS_ZOOM_2X                         3L
#define M_WARP_TILE                                   4L
#define M_STREAM_COPY                                 5L

#define M_USE_ALL_REGIONS                             1L
#define M_IGNORE_ALL_REGIONS                          2L

#define M_NONE                               0x08000000L // Also defined in milcal.h, milcolor.h
#define M_VECTOR                                   1411L
#define M_RASTER                                   1416L
#define M_VECTOR_AND_RASTER                        1417L

/************************************************************************/
/* MbufControlRegion() ControlTypes                                     */
/************************************************************************/
#define M_CACHE_CONTROL                            5204L
#define M_MODIFIED                                 4096L  //bitwise value 0x00001000


#define M_GRAB_TIME_STAMP                    0x00000040L
#define M_ALWAYS_SYNCHRONOUS                 0x40000000L
#define M_MODIFIED_WITH_ERROR                0x20000000L
#define M_DRIVER_ASYNC_CALL_CANCELLED        0x10000000L
#define M_DRIVER_ASYNC_CALL_END              0x08000000L
#define M_DRIVER_RESET_HOOK_CONTEXT_ID       0x04000000L
#define M_MODIFIED_DIGITIZER                 0x02000000L
#define M_MODIFIED_DIGITIZER_WITH_ERROR      0x01000000L
#define M_MODIFIED_DIGITIZER_CORRUPT         0x00800000L
#define M_MODIFIED_BY_DIRECTX                      5400L

/************************************************************************/
/* MbufControlRegion() ControlValues                                    */
/************************************************************************/
#define M_NOT_IN_CACHE                                0L
#define M_IN_CACHE                                    1L

#define M_NO_HOOK                            0x00000004L
#define M_NO_MODIFIED_HOOK                   0x00000008L

#define M_ODD_FIELD                                   1L
#define M_EVEN_FIELD                                  2L
#define M_BOTH_FIELDS                                 3L
#define M_ANY_FIELD                                   4L

/************************************************************************/
/* MbufSetRegion()                                                      */
/************************************************************************/
#define M_NO_RASTERIZE                                1L
#define M_RASTERIZE_AND_DISCARD_LIST               1414L
#define M_RASTERIZE                                1415L

/************************************************************************/
/* MbufDiskInquire()                                                    */
/************************************************************************/
#define M_LUT_PRESENT                                 6000L
#define M_ASPECT_RATIO                                6001L
#define M_FRAME_RATE                                  6002L
#define M_NUMBER_OF_IMAGES                            6003L
#define M_CALIBRATION_PRESENT                         1400L
#define M_CALIBRATION_CONTEXT_PRESENT                 1401L
#define M_REGION_PRESENT                              1461L

/* Common with other Inquire/Control */
#define M_ABSOLUTE_VALUE                              50L
#define M_NORMALIZATION_FACTOR                        52L
#define M_OVERSCAN                                    53L
#define M_OVERSCAN_REPLACE_VALUE                      54L
#define M_OFFSET_CENTER_X                             55L
#define M_OFFSET_CENTER_Y                             56L
#define M_SIZE_X                                      1536L // 0x600
#define M_SIZE_Y                                      1537L // 0x601
#define M_SIZE_BAND                                   1005L
#define M_SIZE_BIT                                    1007L
#define M_TYPE                                        1008L
#define M_ATTRIBUTE                                   1013L
#define M_SIGN                                        1014L
#define M_GREEN                                       0x10L
#define M_SATURATION                                  0x2000L

#define M_FILE_FORMAT                                 1015L
#define M_LUT                                         0x00040000L
// Reserved M_SIZE_X+M_LUT                            0x00040600L or 263680L

/************************************************************************/
/* Lattice values                                                       */
/************************************************************************/
#define M_4_CONNECTED                                 0x00000010L
#define M_8_CONNECTED                                 0x00000020L


/************************************************************************/
/* Data types for results                                               */
/************************************************************************/
#define M_TYPE_COMMAND                                0x00008000L       // used in drivers (gigevision)
#define M_TYPE_CHAR                                   0x00010000L       // used in highlvl modules
#define M_TYPE_SHORT                                  0x00020000L       // used in highlvl modules
#define M_TYPE_MIL_INT32                              0x00040000L       // used in highlvl modules and mil
#define M_TYPE_FLOAT                                  0x00080000L       // used in highlvl modules
#define M_TYPE_DOUBLE                                 0x00100000L       // used in highlvl modules and mil
#define M_TYPE_MIL_DOUBLE                             M_TYPE_DOUBLE
#define M_TYPE_PTR                                    0x00200000L       // used in mil (MappGetHookInfo), in drivers and in dmil
#define M_TYPE_MIL_ID                                 0x00400000L       // used in highlvl modules, drivers and mil
#define M_TYPE_STRING                                 0x00800000L       // used in mil, dmil, drivers
#define M_TYPE_STRING_PTR                             M_TYPE_STRING     // used in mil, dmil, drivers
//#define M_TYPE_ASCII                                  M_TYPE_STRING   // TBR deprecated
//#define M_TYPE_BINARY                                 0x01000000L     // TBR deprecated
#define M_TYPE_BOOLEAN                                0x01000000L       // used in drivers (gigevision)
#define M_TYPE_HEX                                    0x02000000L       // used internally by highlvl ocr
#define M_TYPE_INT64                                  0x04000000L       // used in mil.h and used as M_TYPE_MIL_INT64 in highlvl modules
#define M_TYPE_FILENAME                               0x08000000L       // used in mil (MappGetHookInfo)
#define M_TYPE_ARRAY_ID_PTR                           0x10000000L       // used in mil (MappGetHookInfo)
#define M_TYPE_ID_PTR                                 0x20000000L       // used internally in mil
#define M_TYPE_ENUMERATION                            0x40000000L       // see M_TYPE_INTEGER_ENUMERATION and M_TYPE_STRING_ENUMERATION
#define M_TYPE_INTEGER_ENUMERATION                    M_TYPE_ENUMERATION + M_TYPE_MIL_INT32 // used indirectly in mil, drivers (gigevision)
#define M_TYPE_STRING_ENUMERATION                     M_TYPE_ENUMERATION + M_TYPE_STRING    // used indirectly in mil, drivers (gigevision)
#define M_TYPE_ENUMERATION_FROM_STRING                M_TYPE_STRING_ENUMERATION             // used indirectly in mil, drivers (gigevision)
#define M_TYPE_REGISTER                               0x80000000L
#define M_TYPE_REGISTER_FROM_STRING                   M_TYPE_REGISTER + M_TYPE_STRING

#define M_MAX_BYTE_COUNT                              0x00007FFCL  //Maximum payload of a M_TYPE_REGISTER.
#define M_BYTE_COUNT(n)                               (n)  //Used in combination with M_TYPE_REGISTER for GigE Vision

/* Type switch for 32/64 bits support */
#define M_TYPE_MIL_INT64                           0x00140000L

#if M_MIL_USE_64BIT
   #define M_TYPE_MIL_INT                             M_TYPE_MIL_INT64
#else
   #define M_TYPE_MIL_INT                             M_TYPE_MIL_INT32
#endif
#if M_MIL_USE_LINUX && M_MIL_USE_64BIT
   #define M_TYPE_LONG                                M_TYPE_MIL_INT64
#else
   #define M_TYPE_LONG                                M_TYPE_MIL_INT32
#endif

#if   M_MIL_USE_CE || (M_MIL_USE_UNICODE && M_MIL_UNICODE_API)
   #define M_TYPE_TEXT_CHAR                           M_TYPE_SHORT
#elif M_MIL_USE_WINDOWS || M_MIL_USE_PPC || M_MIL_USE_LINUX
   #define M_TYPE_TEXT_CHAR                           M_TYPE_CHAR
#else
   #error Operating system not supported in Milos.h!
#endif


/* Bit encoded image types */
#define M_GREYSCALE                                   0x0200L
#define M_GRAYSCALE                                   M_GREYSCALE

/************************************************************************/
/* MgraAlloc()                                                           */
/************************************************************************/
#define M_DEFAULT_GRAPHIC_CONTEXT                     M_MAKE_DEFAULT_ID(2)

/************************************************************************/
/* MgraAllocList()                                                      */
/************************************************************************/
#define M_ROI_LIST                              1021L
#define M_DRAW_LIST                             1022L

/************************************************************************/
/* MgraLines()                                                          */
/************************************************************************/
#define M_LINE_LIST                                   0x00000010L
#define M_POLYLINE                                    0x00000020L
#define M_POLYGON                                     0x00000040L
#define M_FILLED                                      0x00000080L
#define M_PACKED                                      0x00020000L

/************************************************************************/
/* MgraRectAngle                                                        */
/************************************************************************/
#define M_CORNER_AND_DIMENSION                        0x00000001L
#define M_CENTER_AND_DIMENSION                        0x00000002L
#define M_BOTH_CORNERS                                0x00000004L
#define M_FILLED                                      0x00000080L

/************************************************************************/
/* MgraImage                                                            */
/************************************************************************/
#define M_DRAW_REGION                                 0x00000010L
#define M_NO_ERROR_ON_MISSING_CALIBRATION             0x00000020L
#define M_DRAW_ERROR_ON_MISSING_CALIBRATION           0x00000040L

/************************************************************************/
/* MgraFont()                                                           */
/************************************************************************/
#define M_FONT_DEFAULT_SMALL                          1L
#define M_FONT_DEFAULT_MEDIUM                         2L
#define M_FONT_DEFAULT_LARGE                          3L
#define M_FONT_DEFAULT                                M_FONT_DEFAULT_SMALL
#define M_FONT_TTF                                    4L

#define MIL_FONT_NAME(name)                          ((MIL_INT)(name))
/* Using TrueType Font */
#if M_MIL_USE_LINUX
#define M_TTF_FONT_DEFAULT                            MIL_FONT_NAME(MIL_TEXT("DejaVu Sans"))
#define M_TTF_FONT_DEFAULT_ASIAN                      MIL_FONT_NAME(MIL_TEXT("Baekmuk Batang"))
#else
#define M_TTF_FONT_DEFAULT                            MIL_FONT_NAME(MIL_TEXT("Arial"))
#define M_TTF_FONT_DEFAULT_ASIAN                      MIL_FONT_NAME(MIL_TEXT("Arial Unicode MS"))
#endif
#define M_TTF_FONT_DEFAULT_SIZE                       12L //12pt

/************************************************************************/
/* Used by MgraControl() / MgraInquire() / MgraControlList() / MgraInquireList() Types */
/************************************************************************/

/* Index modifiers for list */
#define M_DEFAULT                                     0x10000000L
#define M_LIST                                        0x08000000L
#define M_ALL                                         0x40000000L

/* ControlType, InquireType applicable to graphic contexts and graphic lists */
#define M_COLOR                                       256L
// Reserved values with M_COLOR
// M_COLOR+M_RED                                      264L  // 256L+0x8
// M_COLOR+M_GREEN                                    272L  // 256L+0x10
// M_COLOR+M_BLUE                                     288L  // 256L+0x20
#define M_BACKCOLOR                                   512L
// M_BACKCOLOR+M_RED                                  520L  // 512L+0x8
// M_BACKCOLOR+M_GREEN                                528L  // 512L+0x10
// M_BACKCOLOR+M_BLUE                                 544L  // 512L+0x20
#define M_BACK_COLOR                                  M_BACKCOLOR
#define M_SELECTED_COLOR                              768L
// M_SELECTED_COLOR+M_RED                             776L  // 768L+0x8
// M_SELECTED_COLOR+M_GREEN                          .784L  // 768L+0x10
// M_SELECTED_COLOR+M_BLUE                            800L  // 768L+0x20
#define M_FONT                                        7L
#define M_FONT_X_SCALE                                8L
#define M_FONT_Y_SCALE                                9L
#define M_THICKNESS                                   10L
#define M_BACKGROUND_MODE                             12L
#define M_FONT_SIZE                                   0x01000060L
#define M_TEXT_DIRECTION                              0x01000061L
#define M_TEXT_ANTIALIASING                           0x01000062L
#define M_FONT_FILENAME                               0x01000063L
#define M_FONT_AUTO_SELECT                            0x01000064L
#define M_SCAN_ALL_FONTS                              0x01000065L
#define M_FILLED                                      0x00000080L
#define M_TEXT_ALIGN_HORIZONTAL                       58L
#define M_TEXT_ALIGN_VERTICAL                         71L
#define M_ACCURACY                                    106L
#define M_INPUT_UNITS                                 121L        // Also defined in milcal.h, milmeas.h
#define M_GRAPHIC_INDEX_TAG                           0x01000000L
#define M_GRAPHIC_INDEX(a)                            (M_GRAPHIC_INDEX_TAG + (a))
#define M_GRAPHIC_LABEL_TAG                           0x02000000L
#define M_GRAPHIC_LABEL(a)                            (M_GRAPHIC_LABEL_TAG + (a))

#define M_GRA_INQUIRE_MIL_ID_RANGE_START        1100L
#define M_GRA_INQUIRE_MIL_ID_RANGE_END          1199L

#define M_GRA_INQUIRE_DOUBLE_RANGE_START             1200L
#define M_DRAW_ZOOM_X                                1203L       
#define M_DRAW_ZOOM_Y                                1204L      
#define M_DRAW_OFFSET_X                              1205L
#define M_DRAW_OFFSET_Y                              1206L
#define M_RADIUS_X                                   1210L                  
#define M_RADIUS_Y                                   1211L
#define M_RECTANGLE_WIDTH                            1212L
#define M_RECTANGLE_HEIGHT                           1213L
#define M_GRA_INQUIRE_DOUBLE_RANGE_END               1299L

/* Should be in double range, but are already defined elsewhere. */
#define M_POSITION_X                           0x00003400L          
#define M_POSITION_Y                           0x00004400L   
#define M_ANGLE                                0x00000800L
#define M_ANGLE_START                          0x00000801L
#define M_ANGLE_END                            0x00000802L

/* ControlType, InquireType only applicable to list objects */

/* ControlType, InquireType only applicable to attribute context or list */
#define M_LIST_TYPE                                   201L
             
/* ControlType only */
#define M_DELETE                                      3L   // 3   Also defined in Milblob.h

/* Inquire Types only */
#define M_GRAPHIC_TYPE                               1518L
#define M_NUMBER_OF_GRAPHICS                         1519L
#define M_LAST_LABEL                                 1520L
#define M_INDEX                                       217L
#define M_INDEX_VALUE                                 M_INDEX
#define M_LABEL_VALUE                                   1L

/* Graphic manipulation controls */
#define M_TRANSLATE_X                         1521L
#define M_TRANSLATE_Y                         1522L
#define M_APPLY_SCALE                         1523L
#define M_ROTATE                                 2L
#define M_POSITION_TYPE                       1524L
#define M_NUMBER_OF_SUB_ELEMENTS              1525L

/* Control values for M_BACKGROUND_MODE */
#define M_OPAQUE                                      0x01000058L
#define M_TRANSPARENT                                 0x01000059L

/* Control values for M_COLOR */
#define M_RGB_COLOR                                   0x40000000L
#define M_RGB888(r,g,b)                               (M_RGB_COLOR|((MIL_INT32)(((unsigned char)(r)|((MIL_INT32)((unsigned char)(g))<<8))|(((MIL_INT32)(unsigned char)(b))<<16))))
#define M_RGB888_r(color)                             ((MIL_INT32)color&0x000000FF)
#define M_RGB888_g(color)                             (((MIL_INT32)color&0x0000FF00)>>8)
#define M_RGB888_b(color)                             (((MIL_INT32)color&0x00FF0000)>>16)
#define M_IS_RGB888(color)                            (((color)&0xFF000000) == M_RGB_COLOR)
#define M_BGR888(b,g,r)                               (M_RGB_COLOR|((MIL_INT32)(((unsigned char)(b)|((MIL_INT32)((unsigned char)(g))<<8))|(((MIL_INT32)(unsigned char)(r))<<16))))
#define M_BGR888_b(color)                             ((MIL_INT32)color&0x000000FF)
#define M_BGR888_g(color)                             (((MIL_INT32)color&0x0000FF00)>>8)
#define M_BGR888_r(color)                             (((MIL_INT32)color&0x00FF0000)>>16)
#define M_BGR888_B(color)                              M_BGR888_b(color)
#define M_BGR888_G(color)                              M_BGR888_g(color)
#define M_BGR888_R(color)                              M_BGR888_r(color)
#define M_RGB888_R(color)                              M_RGB888_r(color)
#define M_RGB888_G(color)                              M_RGB888_g(color)
#define M_RGB888_B(color)                              M_RGB888_b(color)

/* Control values for M_INPUT_UNITS */
#define M_DISPLAY                               0x00200000L
#define M_PIXEL                                     0x1000L
#define M_WORLD                                     0x2000L

/* Control values for M_TEXT_ALIGN_HORIZONTAL and display positions values */
#define M_LEFT                                  0x00000100L
#define M_RIGHT                                 0x00000200L

/* Control values for M_TEXT_ALIGN_VERTICAL and display positions values  */
#define M_TOP                                   0x00000400L
#define M_BOTTOM                                0x00000800L

/* Graphic primitive type */
#define M_GRAPHIC_TYPE_ARC                          1505L                                                                 
#define M_GRAPHIC_TYPE_DOT                          1506L
#define M_GRAPHIC_TYPE_DOTS                         1507L
#define M_GRAPHIC_TYPE_LINE                         1508L    
#define M_GRAPHIC_TYPE_LINES                        1509L    
#define M_GRAPHIC_TYPE_POLYGON                      1510L
#define M_GRAPHIC_TYPE_POLYLINE                     1511L
#define M_GRAPHIC_TYPE_RECT                         1512L                 
#define M_GRAPHIC_TYPE_TEXT                         1513L

#define M_RGB_COLOR_MODE                              13L
#define M_RED_8_BIT                                   14L
#define M_GREEN_8_BIT                                 15L
#define M_BLUE_8_BIT                                  16L
#define M_BACK_RED_8_BIT                              17L
#define M_BACK_GREEN_8_BIT                            18L
#define M_BACK_BLUE_8_BIT                             19L
#define M_LEFT_TO_RIGHT                               20L
#define M_RIGHT_TO_LEFT                               21L
  
#define M_PIXEL_TO_WORLD                          1L
#define M_WORLD_TO_PIXEL                          2L

/**************************************************************************/
/* Used by MgraDraw()                                                     */
/**************************************************************************/
#define M_DRAW_IN_CACHE                         600L
#define M_NO_ERROR_ON_MISSING_CALIBRATION       0x00000020L
#define M_DRAW_ERROR_ON_MISSING_CALIBRATION     0x00000040L

/************************************************************************/
/* Used by MgraHookFunction                                             */
/************************************************************************/
#define M_LIST_MODIFIED                         1531L
#define M_UNHOOK                                0x04000000L

/**************************************************************************/
/* Used by MgraGetBoundingBox()                                           */
/**************************************************************************/
#define M_NO_ERROR_ON_MISSING_CALIBRATION       0x00000020L
#define M_NO_ERROR_ON_EMPTY_LIST                0x00000080L

/**************************************************************************/
/* Used by MgraProcess()                                                  */
/**************************************************************************/
#define M_CONVERT_TO_PIXEL                      1500L
#define M_CONVERT_TO_WORLD                      1501L

/********************************************************************/
/* Predefined colors                                                */
/********************************************************************/
#define M_COLOR_BLACK                                 M_RGB888(0,0,0)
#define M_COLOR_RED                                   M_RGB888(255,0,0)
#define M_COLOR_GREEN                                 M_RGB888(0,255,0)
#define M_COLOR_BLUE                                  M_RGB888(0,0,255)
#define M_COLOR_YELLOW                                M_RGB888(255,255,0)
#define M_COLOR_MAGENTA                               M_RGB888(255,0,255)
#define M_COLOR_CYAN                                  M_RGB888(0,255,255)
#define M_COLOR_WHITE                                 M_RGB888(255,255,255)
#define M_COLOR_GRAY                                  M_RGB888(128,128,128)
#define M_COLOR_BRIGHT_GRAY                           M_RGB888(192,192,192)
#define M_COLOR_LIGHT_GRAY                            M_RGB888(160,160,164)
#define M_COLOR_LIGHT_GREEN                           M_RGB888(192,220,192)
#define M_COLOR_LIGHT_BLUE                            M_RGB888(166,202,240)
#define M_COLOR_LIGHT_WHITE                           M_RGB888(255,251,240)
#define M_COLOR_DARK_RED                              M_RGB888(128,0,0)
#define M_COLOR_DARK_GREEN                            M_RGB888(0,128,0)
#define M_COLOR_DARK_BLUE                             M_RGB888(0,0,128)
#define M_COLOR_DARK_YELLOW                           M_RGB888(128,128,0)
#define M_COLOR_DARK_MAGENTA                          M_RGB888(128,0,128)
#define M_COLOR_DARK_CYAN                             M_RGB888(0,128,128)

/* McalTransformCoordinates() related flags */
#define M_INVALID_POINT                  1.7976931348623158e+308
#define M_ALLOW_INVALID_POINT_OUTPUT     0x00040000L

/************************************************************************/
/* MappGetError()                                                       */
/************************************************************************/
#define M_NULL_ERROR                                  0L
#define M_NO_ERROR                                    0L

#define M_SYNCHRONOUS                                 0x00000001L
#define M_CURRENT                                     0x00000002L
#define M_CURRENT_FCT                                 0x00030000L
#define M_CURRENT_FCT_FULL                            0x00040000L
#define M_CURRENT_SUB_NB                              0x00000004L
#define M_CURRENT_SUB                                 0x00050000L
#define M_CURRENT_SUB_1                               0x00050000L
#define M_CURRENT_SUB_2                               0x00060000L
#define M_CURRENT_SUB_3                               0x00070000L
#define M_GLOBAL                                      0x00000008L
#define M_GLOBAL_FCT                                  0x00090000L
#define M_GLOBAL_SUB_NB                               0x000A0000L
#define M_GLOBAL_SUB                                  0x000B0000L
#define M_GLOBAL_SUB_1                                0x000B0000L
#define M_GLOBAL_SUB_2                                0x000C0000L
#define M_GLOBAL_SUB_3                                0x000D0000L
#define M_INTERNAL                                    0x000E0000L
#define M_INTERNAL_FCT                                0x000F0000L
#define M_INTERNAL_SUB_NB                             0x00100000L
#define M_INTERNAL_SUB                                0x00110000L
#define M_INTERNAL_SUB_1                              0x00110000L
#define M_INTERNAL_SUB_2                              0x00120000L
#define M_INTERNAL_SUB_3                              0x00130000L
#define M_PARAM_NB                                    0x00140000L
#define M_FATAL                                       0x00150000L
#define M_CLIENT_ERROR_ASCII_MODE                     0x00000100L
#define M_ERROR_UNUSED_BITS                           0x0AE0FEF0L
#define M_UNHOOK                                      0x04000000L
#define M_FROM_HOOK                                   0x10000000L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
#define M_MESSAGE                                     (0x20000000L|M_CLIENT_ERROR_ASCII_MODE)
#else
#define M_MESSAGE                                     0x20000000L
#endif
#define M_ERROR                                       0x40000000L
#define M_USER                                        0x00000001L

//#define M_NATIVE_ERROR                                MIL_MAKE_CONST(0x80000000L,0x0000000080000000)
#define M_THREAD_RECURSIVE                            0x00800000L /* Bit field exclusive to M_TRACE  to M_PROCESSING      (3L to 6L) */
#define M_THREAD_CURRENT                              0x01000000L /*                        M_TRACE_START                       (1L) */
                                                                  /*                        M_TRACE_END                         (2L) */
                                                                  /*                        M_ERROR                     (0x40000000) */
                                                                  /*                        M_MESSAGE                   (0x20000000) */
                                                                  /*                        M_CURRENT to M_REGION_SIZE_Y (1L to 44L) */
                                                                  /*                        M_UNHOOK                    (0x04000000) */
#define M_ERROR_CURRENT                               (M_ERROR|M_CURRENT)
#define M_ERROR_GLOBAL                                (M_ERROR|M_GLOBAL)
#define M_ERROR_FATAL                                 (M_ERROR|M_FATAL)


/************************************************************************/
/* MbufLink() Values (Option)                                           */
/************************************************************************/
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_ENABLE                          -9997L   // 0xFFFFD8F3
#define M_DISABLE                         -9999L   // 0xFFFFD8F1
#define M_MODIFIED_DEST_BUFFER                        0x00000004L
#endif
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_LINK                                        M_ENABLE
#define M_UNLINK                                      M_DISABLE
#else
#define M_LINK                                        0x00000001L
#define M_UNLINK                                      0x00000002L
#endif
#define M_MODIFIED_REGION                                     25L

/************************************************************************/
/* MbufGetHookInfo()  //MbufHookFunction()                              */
/************************************************************************/
#define M_BUFFER_ID                                   0x00160000L
#define M_REGION_OFFSET_X                             0x00410000L
#define M_REGION_OFFSET_Y                             0x00420000L
#define M_REGION_SIZE_X                               0x00430000L
#define M_REGION_SIZE_Y                               0x00480000L
#define M_OBJECT_ID                                   0x001B0000L
#define M_FIELD                                       0x001C0000L
#define M_BAND                                        0x001D0000L
#define M_DONE_BY_DIRECTX                             0x001E0000L
#define M_MOVED                                       0x001F0000L

#define M_RESIZED                                     0x00000001L

// Reserve next value for M_BUFFER_INDEX
// used by MdigGetHookInfo                                    49L
#define M_GRAB_TIME_STAMP                             0x00000040L //64L
#define M_EVENT_TYPE                            M_REGION_OFFSET_X
#define M_PARAM1                                M_REGION_OFFSET_Y
#define M_PARAM2                                  M_REGION_SIZE_X
#define M_PARAM3                                  M_REGION_SIZE_Y

#define M_PRE_GRAB_BUFFER_CHANGE                              10L
#define M_POST_GRAB_BUFFER_CHANGE                             11L
#define M_MODIFIED_BUFFER_INTERNAL                            12L
#define M_REMOTE_GRAB_BUFFERS_REQUEST                         13L //TBR
#define M_REMOTE_GRAB_BUFFERS_SET                             14L //TBR
#define M_STATE_MACHINE_PRE_BUFFER_MODIFIED                   15L
#define M_STATE_MACHINE_POST_BUFFER_MODIFIED                  16L
#define M_REMOTE_GRAB_BUFFERS_REQUEST_AFTER_SET_SCHEME        17L //TBR
#define M_REMOTE_BUFFER_EVENT                                 18L //TBR
#define M_MODIFIED_BUFFER_ERROR                               19L
#define M_DX_SURFACE_RESTORED                                 20L
#define M_MODIFIED_BUFFER_DIGITIZER                           21L
#define M_MODIFIED_BUFFER_DIGITIZER_ERROR                     22L
#define M_MODIFIED_BUFFER_DIGITIZER_CORRUPT                   23L
#define M_MODIFIED_CALIBRATION                                24L
#define M_MODIFIED_REGION                                     25L
#define M_MODIFIED_BUFFER                             0x40000000L
#define M_UNHOOK                                      0x04000000L
#define M_ASYNC_HOOK                                  0x08000000L
#define M_GRAB_LINE                                   0x00100000L
#define M_GRAB_LINE_END                               0x00200000L
#define M_CHILD_BUFFER_MOVED                          0x00400000L
#define M_DISP_BUF_HOOK                               0x00800000L // Hook redirected to the displays (use the M_DISP_BUF_HOOK flag)
#define M_PRE_FLIP_COMPLEX_BUFFER                    (M_DISP_BUF_HOOK + 01L)
#define M_POST_FLIP_COMPLEX_BUFFER                   (M_DISP_BUF_HOOK + 02L)

//Remote Event types
#define M_EVENT_REMOTE_GRAB_BUFFERS_REQUEST                         1L
#define M_EVENT_REMOTE_GRAB_BUFFERS_SET                             2L
#define M_EVENT_REMOTE_GRAB_BUFFERS_REQUEST_AFTER_SET_SCHEME        3L
#define M_EVENT_REMOTE_GRAB_BUFFERS_UNSUPPORTED_FORMAT              4L

/************************************************************************/
/* MappAlloc                                                            */
/* Bits used here are shared with MsysAlloc thru MappAllocDefault       */
/************************************************************************/
#define M_APP_ALLOC_INIT_FLAGS                        0x0FF00000L     
#define M_SYS_ALLOC_INIT_FLAGS                        0x00000FFFL     

// Linux support only 1 or 0
#define M_X11_ACCELERATION(X)                         ((X == M_X11_ACC_NONE)?(M_DX_VERSION(X)):(M_DX_VERSION(M_DIRECTX_DDRAW7)))

// Useful
#define M_DX_VERSION(X)                               ((X == M_DEFAULT)?(M_DIRECTX_VERSION_FLAG + (1 << M_DIRECTX_VERSION_OFFSET)):\
                                                      (M_DIRECTX_VERSION_FLAG + (X<<M_DIRECTX_VERSION_OFFSET)))
#define M_DX_VERSION_NUMBER(X)                        ((M_INTERNAL_GET_DX_VERSION_NUMBER(X) == 1)? M_DEFAULT: M_INTERNAL_GET_DX_VERSION_NUMBER(X))
#if !M_MIL_USE_LINUX
#define M_IS_DIRECTX_VERSION_VALID(X)                 ((X == M_DIRECTX_DDRAW7) || (X == M_DIRECTX_D3D9) || (X == M_DIRECTX_D3D10) || (X == M_DIRECTX_D3D11) || (X == M_DIRECTX_NONE))
#else
#define M_IS_DIRECTX_VERSION_VALID(X)                 ((X == M_DIRECTX_DDRAW7) || (X == M_DIRECTX_NONE)) 
#endif
// Internal
// Note that M_DEFAULT is also possible but not considered valid. mildisplay.dll should replace M_DEFAULT depending on context.
#define M_DIRECTX_VERSION_MASK                        0X000F0000L
#define M_DIRECTX_VERSION_OFFSET                      16L
#define M_INTERNAL_GET_DX_VERSION_NUMBER(X)           ((X&M_DIRECTX_VERSION_FLAG)?(((X)&M_DIRECTX_VERSION_MASK)>>M_DIRECTX_VERSION_OFFSET):M_INVALID)

#define M_NEW_DISPLAYS                                0L

#define M_DIRECTX_VERSION_FLAG                        0x00800000L
#define M_UNICODE_CLIENT                              0x01000000L
#define M_SPECIAL                                     0x02000000L
#define M_ASCII_CLIENT                                0x04000000L
#define M_QUIET                                       0x08000000L
#define M_DEFAULT                                     0x10000000L

#if M_MIL_USE_INT64_ID
#define M_SET_CLUSTER_NODE_MASK                       MAKE_INT64(0X00000FFF00000000)
#define M_SET_CLUSTER_NODE_OFFSET                             32L
#define M_INTERNAL_GET_SET_CLUSTER_NODE(X)           (((X)&M_SET_CLUSTER_NODE_MASK)>>M_SET_CLUSTER_NODE_OFFSET)
#else
#define M_SET_CLUSTER_NODE_MASK                       0X0000F000L
#define M_SET_CLUSTER_NODE_OFFSET                             12L
#define M_INTERNAL_GET_SET_CLUSTER_NODE(X)           (((X)&M_SET_CLUSTER_NODE_MASK)>>M_SET_CLUSTER_NODE_OFFSET)
#endif
#define M_CLUSTER_NODE(X)                             ((((MIL_INT)X)<<M_SET_CLUSTER_NODE_OFFSET)&M_SET_CLUSTER_NODE_MASK)

#define M_FUNCTION_NAME_SIZE                          32L
#define M_ERROR_FUNCTION_NAME_SIZE                    M_FUNCTION_NAME_SIZE
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_ERROR_MESSAGE_SIZE                          128L
#else
#define M_ERROR_MESSAGE_SIZE                          320L
#endif

#define M_NBFCTNAMEMAX                                445 /* max number of function codes     */
#define M_NBERRMSGMAX                                 150 /* max number of error messages     */
#define M_NBSUBERRMSGMAX                              10  /* max number of sub error messages */

#define M_ASYNC_ERROR                                 0x40000000

#define M_SYSTEMS_ERROR_START                           200
#define M_SYSTEMS_ERROR_END                           19999  
#define M_HIGHLVL_ERR_OFFSET                          20000L
#define M_HIGHLVL_ERR_OFFSET_MAX                      M_HIGHLVL_ERR_OFFSET + 28999L //48999
#define M_FUNC_ERROR                                  49000      //User error numbers
#define M_DISPLAY_DLL_ERROR_START                     50000


#define M_DIRECTX_NONE                                    M_NULL
#define M_DIRECTX_DDRAW7                                  7L
#define M_DIRECTX_D3D9                                    9L
#define M_DIRECTX_D3D10                                   10L
#define M_DIRECTX_D3D11                                   11L

#define M_X11_ACC_NONE                                    M_NULL
#define M_X11_ACC_DEFAULT                                 1L

/************************************************************************/
/* MappHookFunction()                                                   */
/************************************************************************/
#define M_ERROR_CURRENT                               (M_ERROR|M_CURRENT)
#define M_ERROR_GLOBAL                                (M_ERROR|M_GLOBAL)
#define M_TRACE_START                                 1L
#define M_TRACE_END                                   2L
#define M_DMIL_CLIENT_CONNECTED                       4L
#define M_DMIL_CLIENT_DISCONNECTED                    5L
#define M_DMIL_CONNECTION_LOST                        6L
#define M_ERROR_FATAL                                 (M_ERROR|M_FATAL)
#define M_UNHOOK                                      0x04000000L
#define M_THREAD_RECURSIVE                            0x00800000L /* Bit field exclusive to M_TRACE  to M_PROCESSING      (3L to 6L) */
#define M_THREAD_CURRENT                              0x01000000L /*                        M_TRACE_START                       (1L) */
#if OldDefinesSupport
#define M_INTERNAL_ALLOC                              0x00200000L /*                        M_TRACE_END                         (2L) */
#define M_INTERNAL_FREE                               0x00400000L /*                        M_ERROR                     (0x40000000) */
#endif
#define M_OBJECT_FREE                                 0x00010000L /*                        M_MESSAGE                   (0x20000000) */
#define M_OBJECT_FREE_REMOTE                          0x00010001L /*                        M_CURRENT to M_REGION_SIZE_Y (1L to 44L) */
                                                                  /*                        M_UNHOOK                    (0x04000000) */
#define M_VSYNC_SIGNAL                                0x00000100L /* For hook when a vsync occured on a host                         */
                                                                  /*  Range use: 0x00000100 to 0x0000010F                            */
                                                                  /*  The host system to use (device number) must be added to        */
                                                                  /*  M_VSYNC.  Exemple: to hook on the vsync of the 3rd host        */

                                                                  /*                system, use the hook type M_VSYNC_SIGNAL+M_DEV2  */

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_MAX_VGA_DEVICE                              16L
#endif
#define M_VSYNC_HOOK_SYSTEM_NUM(hooktype)             (hooktype&0x0000000F)   /* IMPORTANT these macros are base on the value of M_MAX_VIDEO_DEVICE */
#define M_IS_VSYNC_HOOK(hooktype)                     ((hooktype&(~(M_UNHOOK|0x0000000F)))==M_VSYNC_SIGNAL)
#define M_MIL_DISPLAY_DLL_LOAD                        0x000000200L
#define M_IS_DMIL_HOOK(hooktype)                      ((hooktype==M_DMIL_CLIENT_CONNECTED) || (hooktype==M_DMIL_CLIENT_DISCONNECTED) || (hooktype==M_DMIL_CONNECTION_LOST))

/************************************************************************/
/* MappGetHookInfo()                                                    */
/************************************************************************/
#define M_NULL_ERROR                                  0L
#define M_NO_ERROR                                    0L

#define M_CURRENT                                     0x00000002L
#define M_CURRENT_FCT                                 0x00030000L
#define M_CURRENT_SUB_NB                              0x00000004L
#define M_CURRENT_SUB                                 0x00050000L
#define M_CURRENT_SUB_1                               0x00050000L
#define M_CURRENT_SUB_2                               0x00060000L
#define M_CURRENT_SUB_3                               0x00070000L
#define M_GLOBAL                                      0x00000008L
#define M_GLOBAL_FCT                                  0x00090000L
#define M_GLOBAL_SUB_NB                               0x000A0000L
#define M_GLOBAL_SUB                                  0x000B0000L
#define M_GLOBAL_SUB_1                                0x000B0000L
#define M_GLOBAL_SUB_2                                0x000C0000L
#define M_GLOBAL_SUB_3                                0x000D0000L
#define M_PARAM_NB                                    0x00140000L
#define M_BUFFER_ID                                   0x00160000L
#define M_REGION_OFFSET_X                             0x00410000L
#define M_REGION_OFFSET_Y                             0x00420000L
#define M_REGION_SIZE_X                               0x00430000L
#define M_REGION_SIZE_Y                               0x00480000L
#define M_OBJECT_ID                                   0x001B0000L
#define M_PARAM_VALUE                                 0x08000000L
#define M_PARAM_TYPE                                  0x10000000L
#define M_PARAM_ATTRIBUTES                            0x00400000L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
#define M_MESSAGE                                     (0x20000000L|M_CLIENT_ERROR_ASCII_MODE)
#else
#define M_MESSAGE                                     0x20000000L
#endif
#define M_DATAGRAM_PTR                                0x00000003L




/************************************************************************/
/* MappInquire() / MappControl() Types                                  */
/* NB: All values in this range must be included between
                       M_APP_INQUIRE_SYS_START and M_APP_INQUIRE_SYS_END*/
/************************************************************************/
#define M_APP_INQUIRE_SYS_START                       15000L
/*Reserve values betwen 5000 and 6699 for AppInquires.
Needey for remote systems                                 */
#define M_APP_INQUIRE_SYS_END                         20000L

#define M_VERSION                                     (M_APP_INQUIRE_SYS_START+1L)
#define M_TRACE_HOOKS                                 (M_APP_INQUIRE_SYS_START+2L)
#define M_TRACE                                       (M_APP_INQUIRE_SYS_START+3L)
#define M_PARAMETER                                   (M_APP_INQUIRE_SYS_START+4L)
//#define Unused                                      (M_APP_INQUIRE_SYS_START+5L)
#define M_PROCESSING                                  (M_APP_INQUIRE_SYS_START+6L)
#define M_LAST_PLATFORM_USE                           (M_APP_INQUIRE_SYS_START+7L)
#define M_CURRENT_ERROR_HANDLER_PTR                   (M_APP_INQUIRE_SYS_START+8L)
#define M_CURRENT_ERROR_HANDLER_USER_PTR              (M_APP_INQUIRE_SYS_START+9L)
#define M_GLOBAL_ERROR_HANDLER_PTR                    (M_APP_INQUIRE_SYS_START+10L)
#define M_GLOBAL_ERROR_HANDLER_USER_PTR               (M_APP_INQUIRE_SYS_START+11L)
#define M_FATAL_ERROR_HANDLER_PTR                     (M_APP_INQUIRE_SYS_START+12L)
#define M_FATAL_ERROR_HANDLER_USER_PTR                (M_APP_INQUIRE_SYS_START+13L)
#define M_TRACE_START_HANDLER_PTR                     (M_APP_INQUIRE_SYS_START+14L)
#define M_TRACE_START_HANDLER_USER_PTR                (M_APP_INQUIRE_SYS_START+15L)
#define M_TRACE_END_HANDLER_PTR                       (M_APP_INQUIRE_SYS_START+16L)
#define M_TRACE_END_HANDLER_USER_PTR                  (M_APP_INQUIRE_SYS_START+17L)
#define M_IRQ_CONTROL                                 (M_APP_INQUIRE_SYS_START+18L)
#define M_ERROR_HANDLER_PTR                           (M_APP_INQUIRE_SYS_START+19L)
#define M_ERROR_HANDLER_USER_PTR                      (M_APP_INQUIRE_SYS_START+20L)
#define M_CURRENT_APPLICATION                         (M_APP_INQUIRE_SYS_START+21L)
#define M_ERROR_HOOKS                                 (M_APP_INQUIRE_SYS_START+22L)
#define M_MIL_UNIQUE_NUMBER                           (M_APP_INQUIRE_SYS_START+23L)
#define M_MIL_TRACE_FILENAME                          (M_APP_INQUIRE_SYS_START+24L)
#define M_FREE_ALL_DEFAULT                            (M_APP_INQUIRE_SYS_START+25L)
#define M_LICENSE_VALID_MODULES                       (M_APP_INQUIRE_SYS_START+26L)
#define M_LICENSE_UNLOCKED_MODULES                    M_LICENSE_VALID_MODULES

#define M_LCR_NUM                                     (M_APP_INQUIRE_SYS_START+28L)
#define M_LICENSE_TEMP_UNLOCKED_MODULES               (M_APP_INQUIRE_SYS_START+29L)
#define M_FORCE_DO_JOB                                (M_APP_INQUIRE_SYS_START+30L)
#define M_LST                                         (M_APP_INQUIRE_SYS_START+31L)
#define M_LSSTR                                       (M_APP_INQUIRE_SYS_START+32L)
#define M_LICENSE_PERMIT_MODULES                      (M_APP_INQUIRE_SYS_START+33L)
#define M_IN_VERSION                                  (M_APP_INQUIRE_SYS_START+34L)
#define M_ERROR_CODE_PTR                              (M_APP_INQUIRE_SYS_START+38L)
#define M_INTERNAL_CALL_MODE                          (M_APP_INQUIRE_SYS_START+39L)
#define M_MILCE_ALLOC_IN_DMA_SIZE                     (M_APP_INQUIRE_SYS_START+40L)
#define M_MILCE_ALLOC_IN_MMF_SIZE                     (M_APP_INQUIRE_SYS_START+41L)
#define M_MILCE_ALLOC_IN_MMF_AUTO_COMMIT              (M_APP_INQUIRE_SYS_START+42L)
#define M_X86_FPU_FLAGS                               (M_APP_INQUIRE_SYS_START+43L)
#define M_REAL_TRACE_LEVEL                            (M_APP_INQUIRE_SYS_START+44L)
#define M_NON_PAGED_COMMUNICATION_BUFFER              (M_APP_INQUIRE_SYS_START+45L)
#define M_FORCE_THREAD_DETACH                         (M_APP_INQUIRE_SYS_START+46L)
#define M_BUFTRANSFER_METHOD                          (M_APP_INQUIRE_SYS_START+47L)
#define M_DISABLE_BUFTRANSFER_METHOD                  (M_APP_INQUIRE_SYS_START+48L)
#define M_RESET_DEFAULTS                              (M_APP_INQUIRE_SYS_START+49L)
#define M_USE_WINDOWED_CLASS                          (M_APP_INQUIRE_SYS_START+50L)
#define M_CACHE_AUTO_FLUSH                            (M_APP_INQUIRE_SYS_START+51L)
#define M_IN_HIGHLEVEL_MODULE                         (M_APP_INQUIRE_SYS_START+52L)
#define M_USING_OLD_DISP                              (M_APP_INQUIRE_SYS_START+53L)
#define M_MIL_DISPLAY_DLL_LOADED                      (M_APP_INQUIRE_SYS_START+54L)
#define M_LICENSE_NON_TEMP_MODULES                    (M_APP_INQUIRE_SYS_START+55L)
#define M_ASSERT_NOT_OWNING_APP                       (M_APP_INQUIRE_SYS_START+56L)
#define M_TEMP_LICENSE_DAYS_LEFT                      (M_APP_INQUIRE_SYS_START+57L)
#define M_PANEL                                       (M_APP_INQUIRE_SYS_START+58L)
#define M_DRIVER_IS_CALLED_INTERNALLY                 (M_APP_INQUIRE_SYS_START+59L)
#define M_NEED_LAST_PLATFORM_USE                      (M_APP_INQUIRE_SYS_START+60L)
#define M_CREATE_REGCONTROL                           (M_APP_INQUIRE_SYS_START+61L)
#define M_ERROR_POP                                   (M_APP_INQUIRE_SYS_START+62L)
#define M_NUMBER_OF_BOARD_TYPES                       (M_APP_INQUIRE_SYS_START+63L)
#define M_INSTALLED_SYSTEM_COUNT                       M_NUMBER_OF_BOARD_TYPES
#define M_KEY_CUSTOM_VALUE                            (M_APP_INQUIRE_SYS_START+64L)
#define M_SAFE_FLOATING_POINT_CONTROL                 (M_APP_INQUIRE_SYS_START+65L)
#define M_RESET_SYSDETECT                             (M_APP_INQUIRE_SYS_START+66L)
/* Reserve next 31 values               from          (M_APP_INQUIRE_SYS_START+67L)*/
/*                                      to            (M_APP_INQUIRE_SYS_START+95)*/
#define M_SUPERSIGHT_DRIVER_VERSION                   (M_APP_INQUIRE_SYS_START+118L)
#define M_EXECUTING_ON_SUPERSIGHT_MASTER              (M_APP_INQUIRE_SYS_START+119L)
#define M_MEMORY                                      (M_APP_INQUIRE_SYS_START+120L) /*5120*/ //Only 2 bits set. Used in bitwise operations
#define M_CLIENT_UNICODE                              (M_APP_INQUIRE_SYS_START+121L)
#define M_APPLICATION_ALLOCATED                       (M_APP_INQUIRE_SYS_START+122L)
#define M_FREE_DISPLAY                                (M_APP_INQUIRE_SYS_START+123L)
// Unused                                             (M_APP_INQUIRE_SYS_START+124L)
// Unused                                             (M_APP_INQUIRE_SYS_START+125L)
// Unused                                             (M_APP_INQUIRE_SYS_START+126L)
#define M_MP_ACTIVE_THREAD                            (M_APP_INQUIRE_SYS_START+127L) // Deprecated as of MIL9.2 
#define M_MP_USE                                      (M_APP_INQUIRE_SYS_START+128L) // Moved to different section below for PP2
// Unused                                             (M_APP_INQUIRE_SYS_START+129L)
#define M_MP_MAX_CORES_PER_THREAD                     (M_APP_INQUIRE_SYS_START+130L) // Deprecated as of MIL9.2 
#define M_MP_PRE_PROCESS                              (M_APP_INQUIRE_SYS_START+131L) // Deprecated as of MIL9.2 
// Unused                                             (M_APP_INQUIRE_SYS_START+132L)
#define M_MP_CORES_NUM                                (M_APP_INQUIRE_SYS_START+133L) // Deprecated as of MIL9.2 
#define M_MP_PHYSICAL_CORES_NUM                       (M_APP_INQUIRE_SYS_START+134L) // Deprecated as of MIL9.2 
// RESERVED. DO NOT USE.                              (M_APP_INQUIRE_SYS_START+135L)
#define M_SUPERSIGHT_DESC                             (M_APP_INQUIRE_SYS_START+136L)

#define M_LCCF                                        (M_APP_INQUIRE_SYS_START+287L)
#define M_RESERVE_WORKSPACE                           (M_APP_INQUIRE_SYS_START+288L)
#define M_FREE_WORKSPACE                              (M_APP_INQUIRE_SYS_START+289L)
#define M_DEFAULT_HOST_FROM_ID                        (M_APP_INQUIRE_SYS_START+290L)
#define M_DEFAULT_WORKSPACE                           (M_APP_INQUIRE_SYS_START+291L)
/* Reserve for error to prevent previous inquire + n  (M_APP_INQUIRE_SYS_START+293L)*/
/* Reserve for error to prevent previous inquire + n  (M_APP_INQUIRE_SYS_START+295L)*/
#define M_DISABLE_RECURSIVE_HOOKS                     (M_APP_INQUIRE_SYS_START+297L)
#define M_WORKSPACE_FROM_ID                           (M_APP_INQUIRE_SYS_START+298L)
#define M_SET_ODYSSEY_DEFAULTS                        (M_APP_INQUIRE_SYS_START+299L) 
/* Reserved for display app inquires                  (M_APP_INQUIRE_SYS_START+300L)*/
/* Reserved for display app inquires                  (M_APP_INQUIRE_SYS_START+450L)*/


#define M_NON_PAGED_MEMORY_FREE                      (M_APP_INQUIRE_SYS_START+500L)
#define M_NON_PAGED_MEMORY_USED                      (M_APP_INQUIRE_SYS_START+501L)
#define M_NON_PAGED_MEMORY_SIZE                      (M_APP_INQUIRE_SYS_START+502L)
// Unused                                            (M_APP_INQUIRE_SYS_START+503L)
#define M_TRACE_TAG                                  (M_APP_INQUIRE_SYS_START+504L)
#define M_ANCESTOR_APPLICATION                       (M_APP_INQUIRE_SYS_START+505L)

#define M_USE_NEW_DISPLAYS                           (M_APP_INQUIRE_SYS_START+0x00000200L) /*512L*/
#define M_MEMORY_ALLOC_PRE_PADDING                   (M_APP_INQUIRE_SYS_START+513L)
#define M_MEMORY_ALLOC_POST_PADDING                  (M_APP_INQUIRE_SYS_START+514L)
#define M_MEMORY_ALLOC_PITCH_BYTE                    (M_APP_INQUIRE_SYS_START+515L)
#define M_MEMORY_ALLOC_ALIGNMENT                     (M_APP_INQUIRE_SYS_START+516L)
#define M_DMIL_CONNECTION_PORT                       (M_APP_INQUIRE_SYS_START+517L)
#define M_DMIL_CONNECTION                            (M_APP_INQUIRE_SYS_START+518L)
#define M_DMIL_AUTO_PUBLISH_ALL                      (M_APP_INQUIRE_SYS_START+519L)

#define M_MTX_MEM_MANAGER_INFO_START                 (M_APP_INQUIRE_SYS_START+600L)
#define M_MTX_MEM_MANAGER_ADDRESS                    (M_MTX_MEM_MANAGER_INFO_START)
#define M_MTX_MEM_MANAGER_MEM_SIZE                   (M_MTX_MEM_MANAGER_INFO_START+1L)
#define M_MTX_MEM_MANAGER_FREE_MEM_SIZE              (M_MTX_MEM_MANAGER_INFO_START+2L)
#define M_MTX_MEM_MANAGER_USED_MEM_SIZE              (M_MTX_MEM_MANAGER_INFO_START+3L)
#define M_MTX_MEM_MANAGER_VERSION                    (M_MTX_MEM_MANAGER_INFO_START+4L)
#define M_MTX_MEM_MANAGER_NUM_OF_BANK                (M_MTX_MEM_MANAGER_INFO_START+5L)
#define M_MTX_MEM_MANAGER_BANK_FLAGS                 (M_MTX_MEM_MANAGER_INFO_START+6L)
#define M_MTX_MEM_MANAGER_NON_PAGED_FLAGS            (M_MTX_MEM_MANAGER_INFO_START+7L)
#define M_MTX_MEM_MANAGER_KERNEL_ADDRESS             (M_MTX_MEM_MANAGER_INFO_START+8L)
#define M_MTX_MEM_MANAGER_STARTUP_DMA_MODE           (M_MTX_MEM_MANAGER_INFO_START+9L)
#define M_MTX_MEM_MANAGER_STARTUP_DMA_SIZE           (M_MTX_MEM_MANAGER_INFO_START+10L)
#define M_MTX_MEM_MANAGER_STARTUP_CHUNK_SIZE         (M_MTX_MEM_MANAGER_INFO_START+11L)
#define M_MTX_MEM_MANAGER_OS_MEMORY_SIZE             (M_MTX_MEM_MANAGER_INFO_START+12L)
#define M_MTX_MEM_MANAGER_BOOT_FLAGS                 (M_MTX_MEM_MANAGER_INFO_START+13L)
#define M_MTX_MEM_MANAGER_THRESHOLD                  (M_MTX_MEM_MANAGER_INFO_START+14L)
#define M_MTX_MEM_MANAGER_REG_DMA_MODE               (M_MTX_MEM_MANAGER_INFO_START+15L)
#define M_MTX_MEM_MANAGER_REG_CHUNK_SIZE             (M_MTX_MEM_MANAGER_INFO_START+16L)
#define M_MTX_MEM_MANAGER_REG_DMA_SIZE               (M_MTX_MEM_MANAGER_INFO_START+17L)

#define M_MTX_MEM_DRIVER_INFORMATION_STRUCT          (M_MTX_MEM_MANAGER_INFO_START+18L)
#define M_MTX_MEM_MANAGER_STRUCT_VERSION             (M_MTX_MEM_MANAGER_INFO_START+19L)
#define M_MTX_MEM_MANAGER_STRUCT_SIZE                (M_MTX_MEM_MANAGER_INFO_START+20L)
#define M_MTX_MEM_MANAGER_BASE_ADDRESS               (M_MTX_MEM_MANAGER_ADDRESS)
#define M_MTX_MEM_MANAGER_SIZE_IN_BYTE               (M_MTX_MEM_MANAGER_MEM_SIZE)
#define M_MTX_MEM_MANAGER_FREE_MEM_SIZE_IN_BYTE      (M_MTX_MEM_MANAGER_FREE_MEM_SIZE)
#define M_MTX_MEM_MANAGER_USED_MEM_SIZE_IN_BYTE      (M_MTX_MEM_MANAGER_USED_MEM_SIZE)
#define M_MTX_MEM_MANAGER_DMA_MODE                   (M_MTX_MEM_MANAGER_INFO_START+21L)             
#define M_MTX_MEM_MANAGER_CHUNK_SIZE                 (M_MTX_MEM_MANAGER_INFO_START+22L)
#define M_MTX_MEM_MANAGER_NUM_USER_BANKS             (M_MTX_MEM_MANAGER_INFO_START+23L)

/* Reserve next values                  from         (M_APP_INQUIRE_SYS_START+713L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+639L)*/
#define M_MTX_MEM_MANAGER_INFO_END                   (M_APP_INQUIRE_SYS_START+639L)

/* Reserve next values                  from         (M_APP_INQUIRE_SYS_START+713L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+719L)*/

#define M_BH_BASE_BUFFER_TYPE                        (M_APP_INQUIRE_SYS_START+705L)
#define M_BH_NEEDED_BUFFER_ATTRIBUTE                 (M_APP_INQUIRE_SYS_START+706L)
#define M_BH_INCOMPATIBLE_BUFFER_ATTRIBUTE           (M_APP_INQUIRE_SYS_START+707L)
#define M_BH_TRANSFER_METHOD                         (M_APP_INQUIRE_SYS_START+708L)
#define M_BH_TRANSFER_FUNCTION_SUPPORTED             (M_APP_INQUIRE_SYS_START+709L)
#define M_BH_IS_ALLOCATOR                            (M_APP_INQUIRE_SYS_START+710L)
#define M_BH_IS_CREATOR                              (M_APP_INQUIRE_SYS_START+711L)
#define M_BH_KNOWN_DISPLAY_ATTRIBUTE                 (M_APP_INQUIRE_SYS_START+712L)
/* Reserve next values                  from         (M_APP_INQUIRE_SYS_START+713L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+719L)*/
#define M_DMA_MANAGER_TYPE                           (M_APP_INQUIRE_SYS_START+720L)
#define M_FREE_EMPTY_WORKSPACE                       (M_APP_INQUIRE_SYS_START+721L)
#define M_RESERVE_CLUSTER_NODE                       (M_APP_INQUIRE_SYS_START+722L)
#define M_FREE_CLUSTER_NODE                          (M_APP_INQUIRE_SYS_START+723L)
#define M_DEFAULT_CLUSTER_NODE                       (M_APP_INQUIRE_SYS_START+724L)
#define M_FREE_EMPTY_CLUSTER_NODE                    (M_APP_INQUIRE_SYS_START+725L)
#define M_CLUSTER_NODE_FROM_ID                       (M_APP_INQUIRE_SYS_START+726L)
#define M_EXPIRATION_DATE                            (M_APP_INQUIRE_SYS_START+727L)
#define M_FREE_DEFAULT_SHADOWS                       (M_APP_INQUIRE_SYS_START+728L)
#define M_FREE_REMAINING_TUBES                       (M_APP_INQUIRE_SYS_START+729L)
#define M_INSTALLED_SYSTEM_TYPE                      (M_APP_INQUIRE_SYS_START+728L)                
/* Reserved the 15 next values               from    (M_APP_INQUIRE_SYS_START+729L)*/
/*                                        to         (M_APP_INQUIRE_SYS_START+744L)*/
#define M_IGNORED_EXP_DATE                           (M_APP_INQUIRE_SYS_START+745L)

#define M_INSTALLED_SYSTEM_CAN_GRAB                   (M_APP_INQUIRE_SYS_START+800L)
/* Reserved the next values               from        (M_APP_INQUIRE_SYS_START + 801L)*/
/*                                        to          (M_APP_INQUIRE_SYS_START + 815L)*/
#define M_IS_DISTRIBUTED_BOARD                        (M_APP_INQUIRE_SYS_START + 816L)
/* Reserve next 15 values                from         (M_APP_INQUIRE_SYS_START + 817L)*/
/*                                       to           (M_APP_INQUIRE_SYS_START + 831L)*/


#define M_DIRECT_ACCESS_START                        (M_APP_INQUIRE_SYS_START+832L)
#define M_PROCESSING_PACK_REVISION                   (M_APP_INQUIRE_SYS_START+833L)
/* The next values are available          from       (M_DIRECT_ACCESS_START + 2L)*/
/*                                        to         (M_DIRECT_ACCESS_START + 57L)*/

#define M_APP_INQUIRE_STRING_DIRECT_ACCESS_START     (M_APP_INQUIRE_SYS_START+890L)
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL) 
#define M_REG_DRIVERS_PATH                           (M_APP_INQUIRE_SYS_START+890L+M_CLIENT_ASCII_MODE)
#define M_REG_INSTALL_DIR                            (M_APP_INQUIRE_SYS_START+891L+M_CLIENT_ASCII_MODE)
#define M_REG_SERVICE_PACK                           (M_APP_INQUIRE_SYS_START+892L+M_CLIENT_ASCII_MODE)
#define M_REG_SERVICE_PACK_REVISION                  (M_APP_INQUIRE_SYS_START+893L+M_CLIENT_ASCII_MODE)
#define M_REG_SERVICE_PACK_NO_COMPENSATE             (M_APP_INQUIRE_SYS_START+894L+M_CLIENT_ASCII_MODE)
#define M_REG_MIL_REVISION                           (M_APP_INQUIRE_SYS_START+895L+M_CLIENT_ASCII_MODE)
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+896L+M_CLIENT_ASCII_MODE)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+919L+M_CLIENT_ASCII_MODE)*/
#else
#define M_REG_DRIVERS_PATH                           (M_APP_INQUIRE_SYS_START+890L)
#define M_REG_INSTALL_DIR                            (M_APP_INQUIRE_SYS_START+891L)
#define M_REG_SERVICE_PACK                           (M_APP_INQUIRE_SYS_START+892L)
#define M_REG_SERVICE_PACK_REVISION                  (M_APP_INQUIRE_SYS_START+893L)
#define M_REG_SERVICE_PACK_NO_COMPENSATE             (M_APP_INQUIRE_SYS_START+894L)
#define M_REG_MIL_REVISION                           (M_APP_INQUIRE_SYS_START+895L)
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+896L)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+919L)*/
#endif
#define M_APP_INQUIRE_STRING_DIRECT_ACCESS_END       (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET-1)
/*Reserve next M_INQUIRE_STRING_SIZE_OFFSET values for string sizes*/
#define M_REG_DRIVERS_PATH_SIZE                      (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+0L) //TBA: MIL should support this inquire
#define M_REG_INSTALL_DIR_SIZE                       (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+1L) //TBA: MIL should support this inquire
#define M_REG_SERVICE_PACK_SIZE                      (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+2L) //TBA: MIL should support this inquire
#define M_REG_SERVICE_PACK_REVISION_SIZE             (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+3L) //TBA: MIL should support this inquire
#define M_REG_SERVICE_PACK_NO_COMPENSATE_SIZE        (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+4L) //TBA: MIL should support this inquire
#define M_REG_MIL_REVISION_SIZE                      (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+5L) //TBA: MIL should support this inquire

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_REG_DMA_MANAGER_TYPE                       M_DMA_MANAGER_TYPE
#else
#define M_REG_DMA_MANAGER_TYPE                       (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+6L) 
#endif
#define M_REG_DX_DISPLAY_SUPPORT                     (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+7L)

/* Reserve values from                               (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+8L) */
/*                to                                 (M_APP_INQUIRE_STRING_DIRECT_ACCESS_START+M_INQUIRE_STRING_SIZE_OFFSET+29L)*/   


#define M_START_LICENSE_MANAGER                      (M_APP_INQUIRE_SYS_START+950L)
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
#define M_DUMP_ID_TABLE                              (M_APP_INQUIRE_SYS_START+951L+M_CLIENT_ASCII_MODE)
#else
#define M_DUMP_ID_TABLE                              (M_APP_INQUIRE_SYS_START+951L)
#endif
#define M_DEFAULT_SYSTEM_ID                          (M_APP_INQUIRE_SYS_START+952L)
#define M_REG_DEF_RESET                              (M_APP_INQUIRE_SYS_START+953L)
#define M_DUMP_ALL_ID_INFO                           (M_APP_INQUIRE_SYS_START+954L)
#define M_REG_FREE_INSTANCE                          (M_APP_INQUIRE_SYS_START+955L)
#define M_MIL_DLL_COMPILATION_TYPE                   (M_APP_INQUIRE_SYS_START+956L)
#define M_MILUTIL_COMPILATION_TYPE                   (M_APP_INQUIRE_SYS_START+957L)
#define M_IS_DISTRIBUTED_MIL_INSTALLED               (M_APP_INQUIRE_SYS_START+958L)
#define M_IS_DISTRIBUTED_MIL_SERVER_INSTALLED        (M_APP_INQUIRE_SYS_START+959L)
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+960L)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+975L)*/   

/*Reserve values between M_REG_DEF_START and M_REG_DEF_END*/
#define M_REG_DEF_START                              (M_APP_INQUIRE_SYS_START+976L)
   /*Reserve for strings between M_REG_DEF_STRING_START and M_REG_DEF_STRING_END*/
   #define M_APP_INQUIRE_STRING_REG_DEF_START           (M_APP_INQUIRE_SYS_START+977L)
   #if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_REG_DEF_BOARD_NAME                         (M_APP_INQUIRE_SYS_START+ 977L+M_CLIENT_ASCII_MODE)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+ 978L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+ 992L+M_CLIENT_ASCII_MODE)*/  
   #define M_REG_DEF_SYSTEM_NAME                        (M_APP_INQUIRE_SYS_START+ 993L+M_CLIENT_ASCII_MODE)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+ 994L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1008L+M_CLIENT_ASCII_MODE)*/  
   #define M_REG_DEF_SYSTEM_DISPLAYABLE_NAME            (M_APP_INQUIRE_SYS_START+1009L+M_CLIENT_ASCII_MODE)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1010L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1024L+M_CLIENT_ASCII_MODE)*/  
   #define M_REG_DEF_DISPLAY_FORMAT                     (M_APP_INQUIRE_SYS_START+1025L+M_CLIENT_ASCII_MODE)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1026L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1040L+M_CLIENT_ASCII_MODE)*/  
   #define M_REG_DEF_DIG_FORMAT                         (M_APP_INQUIRE_SYS_START+1041L+M_CLIENT_ASCII_MODE)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1042L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1056L+M_CLIENT_ASCII_MODE)*/   
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1057L+M_CLIENT_ASCII_MODE)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1136L+M_CLIENT_ASCII_MODE)*/   
   #else
   #define M_REG_DEF_BOARD_NAME                         (M_APP_INQUIRE_SYS_START+ 977L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+ 978L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+ 992L)*/  
   #define M_REG_DEF_SYSTEM_NAME                        (M_APP_INQUIRE_SYS_START+ 993L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+ 994L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1008L)*/  
   #define M_REG_DEF_SYSTEM_DISPLAYABLE_NAME            (M_APP_INQUIRE_SYS_START+1009L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1010L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1024L)*/  
   #define M_REG_DEF_DISPLAY_FORMAT                     (M_APP_INQUIRE_SYS_START+1025L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1026L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1040L)*/  
   #define M_REG_DEF_DIG_FORMAT                         (M_APP_INQUIRE_SYS_START+1041L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1042L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1056L)*/   
   #define M_REG_DEF_DIG_DEV_NAME                       (M_APP_INQUIRE_SYS_START+1057L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1058L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1072L)*/   

   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1073L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1136L)*/   
   #endif
   #define M_APP_INQUIRE_STRING_REG_DEF_END             (M_APP_INQUIRE_SYS_START+1136L)
   /*Reserve next M_APP_INQUIRE_STRING_REG_DEF_END - M_APP_INQUIRE_STRING_REG_DEF_START values for string sizes */
   #define M_REG_DEF_BOARD_NAME_SIZE                    (M_APP_INQUIRE_STRING_REG_DEF_END+  1L) //TBA: MIL should support this inquire
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+  2L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+ 16L)*/  
   #define M_REG_DEF_SYSTEM_NAME_SIZE                   (M_APP_INQUIRE_STRING_REG_DEF_END+ 17L) //TBA: MIL should support this inquire
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+ 18L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+ 32L)*/  
   #define M_REG_DEF_SYSTEM_DISPLAYABLE_NAME_SIZE       (M_APP_INQUIRE_STRING_REG_DEF_END+ 33L) //TBA: MIL should support this inquire
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+ 34L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+ 48L)*/  
   #define M_REG_DEF_DISPLAY_FORMAT_SIZE                (M_APP_INQUIRE_STRING_REG_DEF_END+ 49L) //TBA: MIL should support this inquire
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+ 50L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+ 64L)*/  
   #define M_REG_DEF_DIG_FORMAT_SIZE                    (M_APP_INQUIRE_STRING_REG_DEF_END+ 65L) //TBA: MIL should support this inquire
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+ 66L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+ 80L)*/  
   /* Reserve values from                               (M_APP_INQUIRE_STRING_REG_DEF_END+ 81L)*/
   /*                to                                 (M_APP_INQUIRE_STRING_REG_DEF_END+160L)*/  
   
   #define M_REG_DEF_SYSTEM_DEV                         (M_APP_INQUIRE_SYS_START+1297L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1298L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1312L)*/ 
   #define M_REG_DEF_BUFFER_SIZEBAND                    (M_APP_INQUIRE_SYS_START+1313L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1314L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1328L)*/ 
   #define M_REG_DEF_BUFFER_SIZEX                       (M_APP_INQUIRE_SYS_START+1329L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1330L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1344L)*/ 
   #define M_REG_DEF_BUFFER_SIZEY                       (M_APP_INQUIRE_SYS_START+1345L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1346L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1360L)*/ 
   #define M_REG_DEF_DISPLAY_DEV                        (M_APP_INQUIRE_SYS_START+1361L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1362L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1376L)*/ 
   #define M_REG_DEF_DISPLAY_TYPE                       (M_APP_INQUIRE_SYS_START+1377L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1378L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1392L)*/ 
   #define M_REG_DEF_DIG_DEV                            (M_APP_INQUIRE_SYS_START+1393L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1394L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1408L)*/ 
   #define M_REG_DEF_SYSTEM_CAN_GRAB                    (M_APP_INQUIRE_SYS_START+1409L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1410L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1424L)*/ 
   #define M_REG_DEF_SYSTEM_SUPPORTS_AUX_DISPLAY        (M_APP_INQUIRE_SYS_START+1425L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1426L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1440L)*/ 
   #define M_REG_DEF_DIG_INIT_FLAG                      (M_APP_INQUIRE_SYS_START+1441L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1442L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1456L)*/ 
   #define M_REG_DEF_SYSTEM_SUPPORTS_DEV_NAME           (M_APP_INQUIRE_SYS_START+1457L)
   /* Reserve values from                               (M_APP_INQUIRE_SYS_START+1458L)*/
   /*                to                                 (M_APP_INQUIRE_SYS_START+1472L)*/ 


   #define M_REG_DEF_NUMBER_OF_BOARDS                   (M_APP_INQUIRE_SYS_START+1521L)
#define M_REG_DEF_END                                (M_APP_INQUIRE_SYS_START+1521L)


#define M_DIRECT_ACCESS_END                          (M_APP_INQUIRE_SYS_START+1522L)



#define M_INSTALLATION_TYPE                          (M_APP_INQUIRE_SYS_START+1523L)
#define M_NEED_NETWORK_TUBE_DECODER                  (M_APP_INQUIRE_SYS_START+1524L)
#define M_SUPPORT_INTERSYSTEM_CALL                   (M_APP_INQUIRE_SYS_START+1525L)
#define M_SUPPORT_MIXED_CLUSTER                      (M_APP_INQUIRE_SYS_START+1526L)
#define M_NEED_DEFAULT_COMPENSATION                  (M_APP_INQUIRE_SYS_START+1527L)
#define M_CLUSTER_MASK                               (M_APP_INQUIRE_SYS_START+1528L)
#define M_INTRA_CLUSTER_NODE_MASK                    (M_APP_INQUIRE_SYS_START+1529L)
#define M_IDEMPOTENT_FOR_WORKSPACE                   (M_APP_INQUIRE_SYS_START+1530L)

#define M_SYSTEM_OFFSET                              (M_APP_INQUIRE_SYS_START+1531L)   // Undocumented inquire type
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+1532L)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+1546L)*/ 
#define M_SYSTEM_ODYSSEY_OFFSET                      (M_APP_INQUIRE_SYS_START+1547L)   // Undocumented inquire type
// This inquire type initialises a BoardInfo struct with the defaults values of the specified system
// A pointer to this struct is then returned. To select a specified system, inquire its offset using M_SYSTEM_OFFSET
// and then simply added it to M_SET_SYSTEM_DEFAULTS.
#define M_BOARD_DEFAULTS_PTR                         (M_APP_INQUIRE_SYS_START+1548L)   // Undocumented inquire type 
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+1549L)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+1563L)*/ 
#define M_BOARD_DEFAULTS_SIZE                        (M_APP_INQUIRE_SYS_START+1564L)   // Undocumented inquire type 
/* Reserve values from                               (M_APP_INQUIRE_SYS_START+1565L)*/
/*                to                                 (M_APP_INQUIRE_SYS_START+1579L)*/ 
#define M_BOARD_DEFAULT_ASCII                        (M_APP_INQUIRE_SYS_START+1580L)
#define M_ID_TABLE_SIZE                              (M_APP_INQUIRE_SYS_START+1581L)

// Common App and Sys string types, next 200 values
#define M_SYS_APP_INQUIRE_STRING_START                   (M_APP_INQUIRE_SYS_START+1800L)
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)  
   #define M_NAME_OF_BOARD_TYPE                          (M_APP_INQUIRE_SYS_START+1800L|M_CLIENT_ASCII_MODE)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1801L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1815L)*/
   #define M_DISPLAY_NAME_OF_BOARD_TYPE                  (M_APP_INQUIRE_SYS_START+1816L|M_CLIENT_ASCII_MODE)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1817L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1831L)*/
   #define M_REG_KEY_NAME_OF_BOARD_TYPE                  (M_APP_INQUIRE_SYS_START+1832L|M_CLIENT_ASCII_MODE)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1833L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1847L)*/
   #define M_IMAGING_BOARD_TYPE                          (M_APP_INQUIRE_SYS_START+1848L+M_CLIENT_ASCII_MODE)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1849L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1863L)*/
#else   
   #define M_NAME_OF_BOARD_TYPE                          (M_APP_INQUIRE_SYS_START+1800L)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1801L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1815L)*/
   #define M_DISPLAY_NAME_OF_BOARD_TYPE                  (M_APP_INQUIRE_SYS_START+1816L)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1817L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1831L)*/
   #define M_REG_KEY_NAME_OF_BOARD_TYPE                  (M_APP_INQUIRE_SYS_START+1832L)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1833L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1847L)*/
   #define M_IMAGING_BOARD_TYPE                          (M_APP_INQUIRE_SYS_START+1848L)
   /* Reserve next 15 values               from          (M_APP_INQUIRE_SYS_START+1849L)*/
   /*                                      to            (M_APP_INQUIRE_SYS_START+1863L)*/
#endif
#define M_INSTALLED_SYSTEM_DESCRIPTOR   M_NAME_OF_BOARD_TYPE
#define M_INSTALLED_SYSTEM_PRINT_NAME   M_DISPLAY_NAME_OF_BOARD_TYPE
#define M_INSTALLED_SYSTEM_REG_KEY_NAME M_REG_KEY_NAME_OF_BOARD_TYPE
#define M_SYS_APP_INQUIRE_STRING_END                     (M_APP_INQUIRE_SYS_START+1899L)

#define M_APP_INQUIRE_STRING_SIZE_OFFSET              ((M_SYS_APP_INQUIRE_STRING_END-M_SYS_APP_INQUIRE_STRING_START)+1) //offset of 100

// Inquire value size
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_INSTALLED_SYSTEM_DESCRIPTOR_SIZE            (M_INSTALLED_SYSTEM_DESCRIPTOR      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_INSTALLED_SYSTEM_PRINT_NAME_SIZE            (M_INSTALLED_SYSTEM_PRINT_NAME      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_INSTALLED_SYSTEM_REG_KEY_NAME_SIZE          (M_INSTALLED_SYSTEM_REG_KEY_NAME    +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_IMAGING_BOARD_TYPE_SIZE                     (M_IMAGING_BOARD_TYPE               +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#else
#define M_INSTALLED_SYSTEM_DESCRIPTOR_SIZE            (M_APP_INQUIRE_SYS_START+1800L      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_INSTALLED_SYSTEM_PRINT_NAME_SIZE            (M_APP_INQUIRE_SYS_START+1816L      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_INSTALLED_SYSTEM_REG_KEY_NAME_SIZE          (M_APP_INQUIRE_SYS_START+1832L      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#define M_IMAGING_BOARD_TYPE_SIZE                     (M_APP_INQUIRE_SYS_START+1832L      +M_APP_INQUIRE_STRING_SIZE_OFFSET) 
#endif
//Reserved for sizes up to M_SYS_APP_INQUIRE_STRING_END + M_APP_INQUIRE_STRING_SIZE_OFFSET   //1999

#define M_LIC_RANGE_START                            (M_APP_INQUIRE_SYS_START+2000L)  
#define M_LIC_ADD_RES                                (M_APP_INQUIRE_SYS_START+2001L)
#define M_LICENSE_MODULES                            (M_APP_INQUIRE_SYS_START+2002L)
#define M_SYSTEM_LICENSE_MODULES                     M_LICENSE_MODULES
#define M_LST_STR                                    (M_APP_INQUIRE_SYS_START+2003L+M_CLIENT_ASCII_MODE)
#define M_MIL_LIC                                    (M_APP_INQUIRE_SYS_START+2004L+M_CLIENT_ASCII_MODE)
#define M_LIC_ADD_RES_STR                            (M_APP_INQUIRE_SYS_START+2005L)
#define M_LST_STR_SIZE                               (M_APP_INQUIRE_SYS_START+2006L)
#define M_MIL_LIC_SIZE                               (M_APP_INQUIRE_SYS_START+2007L)
#define M_MSERIES                                    (M_APP_INQUIRE_SYS_START+2008L)
#define M_REMIND_TODAY                               (M_APP_INQUIRE_SYS_START+2009L)
#define M_DONT_REMIND_TODAY                          (M_APP_INQUIRE_SYS_START+2010L)
#define M_HW_TEMP_ARMED                              (M_APP_INQUIRE_SYS_START+2011L)
#define M_MTXHW                                      (M_APP_INQUIRE_SYS_START+2012L)
#define M_HW_TEMP_ARMED_DATE                         (M_APP_INQUIRE_SYS_START+2013L)
#define M_L_EE_RESET                                 (M_APP_INQUIRE_SYS_START+2014L)
#define M_TEMP_MODULES_IF_ACTIVE                     (M_APP_INQUIRE_SYS_START+2015L)
#define M_DISABLE_LICENSERS                          (M_APP_INQUIRE_SYS_START+2016L)
#define M_DISABLE_LICENSERS_HI                       (M_APP_INQUIRE_SYS_START+2017L)
#define M_ENABLE_LICENSERS                           (M_APP_INQUIRE_SYS_START+2018L)
#define M_ENABLE_LICENSERS_HI                        (M_APP_INQUIRE_SYS_START+2019L)
#define M_DISABLED_LICENSERS                         (M_APP_INQUIRE_SYS_START+2020L)
#define M_SPRO_VERS                                  (M_APP_INQUIRE_SYS_START+2021L)
#define M_TPH_STATE                                  (M_APP_INQUIRE_SYS_START+2022L)
#define M_VALIDATE_MESRN                             (M_APP_INQUIRE_SYS_START+2023L)

#define IS_LIC_INQ_STRING_TYPE(X) (((X&~M_CLIENT_ASCII_MODE)==(M_LST_STR&~M_CLIENT_ASCII_MODE)) ||   \
                                   ((X&~M_CLIENT_ASCII_MODE)==(M_MIL_LIC&~M_CLIENT_ASCII_MODE)))
#define M_LIC_VAL_END                                (M_APP_INQUIRE_SYS_START+2048L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2048L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2111L)*/
#define M_LIC_VAL_START                              (M_APP_INQUIRE_SYS_START+2112L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2112L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2175L)*/
#define M_LICENSE_HW_BK                              (M_APP_INQUIRE_SYS_START+2176L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2176L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2239L)*/
#define M_LCRID                                      (M_APP_INQUIRE_SYS_START+2240L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2241L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2303L)*/
#define M_LCRHM                                      (M_APP_INQUIRE_SYS_START+2304L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2305L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2367L)*/
#define M_LCRT                                       (M_APP_INQUIRE_SYS_START+2368L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2369L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2431L)*/
#define M_LICENSE_FINGERPRINT                        (M_APP_INQUIRE_SYS_START+2432L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2433L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2495L)*/
#define M_LICENSER_LONG_NAME                         (M_APP_INQUIRE_SYS_START+2496L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2497L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2559L)*/
#define M_LICENSER_SHORT_NAME                        (M_APP_INQUIRE_SYS_START+2560L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2561L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2623L)*/ 
#define M_LICENSER_SCORE                             (M_APP_INQUIRE_SYS_START+2624L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2625L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2687L)*/
#define M_LCRPM                                      (M_APP_INQUIRE_SYS_START+2688L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2689L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2751L)*/
#define M_LICENSER_OFFSET                            (M_APP_INQUIRE_SYS_START+2752L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2753L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2815L)*/
#define M_LCRTM                                      (M_APP_INQUIRE_SYS_START+2816L)
/* Reserve next 63 values               from         (M_APP_INQUIRE_SYS_START+2817L)*/
/*                                      to           (M_APP_INQUIRE_SYS_START+2879L)*/


#define M_LIC_RANGE_END                              (M_APP_INQUIRE_SYS_START+2999L)



/************************************************************************/
/* MappInquireMp() / MappControlMp() Types                              */
/* MthrInquireMp() / MthrControlMp() Types                              */
/************************************************************************/
#define M_CORE_MAX                                    1587L
#define M_MP_USER_THREAD                              1588L
#define M_MP_PRIORITY                                 1589L
#define M_CORE_AFFINITY_MASK                          1590L
#define M_CORE_SHARING                                1591L
#define M_MP_USE                                      (M_APP_INQUIRE_SYS_START+128L) // 15128

// MappInquireMp only
#define M_CORE_NUM_PROCESS                            1592L
#define M_MP_FORCED_DISABLE                           1593L
#define M_CORE_NUM_HARDWARE                           1594L
#define M_MEMORY_BANK_NUM                             1595L
#define M_MEMORY_BANK_AFFINITY_MASK                   1596L
#define M_MEMORY_BANK_CORE_AFFINITY_MASK              1597L
#define M_CORE_MEMORY_BANK                            1598L
#define M_CORE_MEMORY_BANK_AFFINITY_MASK              1599L
//#define unused                                      1600L
#define M_CORE_AFFINITY_MASK_ARRAY_SIZE               1601L
#define M_MEMORY_BANK_AFFINITY_MASK_ARRAY_SIZE        1602L
#define M_CORE_AFFINITY_MASK_PROCESS                  1642L
#define M_CORE_AFFINITY_MASK_HARDWARE                 1647L
//#define unused                                      1650L
#define M_CORE_NUM_OS                                 1651L

// MxxxControlMp only
#define M_CORE_FORCE_NB                               1603L
#define M_MP_POOL_SIZE                                1604L
#define M_MP_SPIN_LOOP_COUNT                          1605L
#define M_CORE_FORCE_ONE                              1606L
#define M_MP_USE_INTERNAL                             1607L
#define M_MP_USE_INTERNAL_FORCED                      1608L
#define M_MP_THRESHOLD_RESTRICTION                    1609L

// MthrInquireMp only
//#define unused                                      1652L
#define M_CORE_NUM_EFFECTIVE                          M_CORE_NUM_PROCESS

#if OldDefinesSupport
#define M_CORE_NUM                                    M_CORE_NUM_PROCESS            // To support Mil9PP2 EA users
#define M_MP_FORCE_DISABLE                            M_MP_FORCED_DISABLE           // To support Mil9PP2 EA users
#define M_APPLICATION_CORE_AFFINITY_MASK              M_CORE_AFFINITY_MASK_PROCESS  // To support Mil9PP2 EA users
#endif


/************************************************************************/
/* Licensing: Module information                                        */
/************************************************************************/
#define M_LICENSE_LITE               0x00000001L //0L
#define M_LICENSE_DEBUG              0x00000002L //1L
#define M_LICENSE_IM                 0x00000004L //2L
#define M_LICENSE_CODE               0x00000008L //3L
#define M_LICENSE_MEAS               0x00000010L //4L
#define M_LICENSE_PAT                0x00000020L //5L
#define M_LICENSE_MOD                0x00000040L //6L
#define M_LICENSE_JPEG2000           0x00000080L //7L
#define M_LICENSE_BGA                0x00000100L //8L
#define M_LICENSE_BLOB               0x00000200L //9L
#define M_LICENSE_CAL                0x00000400L //10L
#define M_LICENSE_OCR                0x00000800L //11L
#define M_LICENSE_JPEGSTD            0x00001000L //12L
#define M_LICENSE_STR                0x00002000L //13L
#define M_LICENSE_MET                0x00004000L //14L
#define M_LICENSE_COL                0x00008000L //15L
#define M_LICENSE_3DMAP              0x00010000L //16L
#if OldDefinesSupport
#define M_LICENSE_3DPR               M_LICENSE_3DMAP
#endif
#define M_LICENSE_R11                0x00020000L //17L
#define M_LICENSE_REG                0x00040000L //18L
#define M_LICENSE_R12                0x00080000L //19L
#define M_LICENSE_R13                0x00100000L //20L
#define M_LICENSE_DMILC              0x00200000L //21L
#define M_LICENSE_INSPECTOR          0x00400000L //22L
#define M_LICENSE_INSP40             M_LICENSE_INSPECTOR          
#define M_LICENSE_SER                0x00800000L //23L
#define M_LICENSE_INTERFACE          M_LICENSE_SER
#define M_LICENSE_EDGE               0x01000000L //24L
#define M_LICENSE_FUTURE             0x02000000L //25L
#define M_LICENSE_DMIL               0x04000000L //26L
#define M_LICENSE_3DCA               0x08000000L //27L
#define M_LICENSE_R10                0x10000000L //28L
#define M_LICENSE_GPU                0x20000000L //29L
#define M_LICENSE_R7                 0x40000000L //30L
#define M_LICENSE_DA0                MAKE_INT64(0x0000000100000000) //32L
#define M_LICENSE_DA1                MAKE_INT64(0x0000000200000000) //33L

#define M_MTX_ID_KEY_FINGERPRINT                      (M_LICENSE_FINGERPRINT+3)
#define M_HARD_ID_KEY_FINGERPRINT                     M_MTX_ID_KEY_FINGERPRINT
#define M_HW_LIC_KEY_FINGERPRINT                      M_MTX_ID_KEY_FINGERPRINT
#define M_ETHERNET_FINGERPRINT                        (M_LICENSE_FINGERPRINT+7)
#define M_SOLIOS_GIGE_FINGERPRINT                     (M_LICENSE_FINGERPRINT+14)
#define M_GIGE_FINGERPRINT                            (M_LICENSE_FINGERPRINT+15)
#define M_MORPHISQXT_FINGERPRINT                      (M_LICENSE_FINGERPRINT+16)
#define M_NEXIS_FINGERPRINT                           (M_LICENSE_FINGERPRINT+17)
#define M_VIO_FINGERPRINT                             (M_LICENSE_FINGERPRINT+18)
#define M_4SIGHTM_FINGERPRINT                         (M_LICENSE_FINGERPRINT+19)
#define M_SOLIOS_FINGERPRINT                          (M_LICENSE_FINGERPRINT+20)
#define M_1394_FINGERPRINT                            (M_LICENSE_FINGERPRINT+21)
#define M_CONCORD_1394_FINGERPRINT                    M_1394_FINGERPRINT
#define M_ORION_FINGERPRINT                           (M_LICENSE_FINGERPRINT+22)
#define M_CORONA_II_FINGERPRINT                       (M_LICENSE_FINGERPRINT+23)
#define M_ODYSSEY_FINGERPRINT                         (M_LICENSE_FINGERPRINT+26)
#define M_CRONOSPLUS_FINGERPRINT                      (M_LICENSE_FINGERPRINT+27)
#define M_HELIOS_FINGERPRINT                          (M_LICENSE_FINGERPRINT+28)
#define M_MORPHIS_FINGERPRINT                         (M_LICENSE_FINGERPRINT+29)
#define M_IRIS_FINGERPRINT                            (M_LICENSE_FINGERPRINT+30)
#define M_ORIONHD_FINGERPRINT                         (M_LICENSE_FINGERPRINT+32)
#define M_CONCORD_GIGE_FINGERPRINT                    (M_LICENSE_FINGERPRINT+33)
#define M_METEOR_II_MC_FINGERPRINT                    (M_LICENSE_FINGERPRINT+34)
#define M_4SIGHTX_FINGERPRINT                         (M_LICENSE_FINGERPRINT+35)
#define M_MORPHISEVO_FINGERPRINT                      (M_LICENSE_FINGERPRINT+36)
#define M_IRISGT_FINGERPRINT                          (M_LICENSE_FINGERPRINT+37)
#define M_RADIENT_FINGERPRINT                         (M_LICENSE_FINGERPRINT+38)
#define M_SUPERSIGHT_FINGERPRINT                      (M_LICENSE_FINGERPRINT+39)
#define M_CUSTOM_FINGERPRINT                          (M_LICENSE_FINGERPRINT+49)
#define M_HW_ID_KEY_FINGERPRINT                       (M_LICENSE_FINGERPRINT+50)
#define M_HW_ID_KEY_PLUS_FINGERPRINT                  (M_LICENSE_FINGERPRINT+51)
#define M_MSERIES_FINGERPRINT                         (M_LICENSE_FINGERPRINT+53)
#define M_MATROX_BOARD_FINGERPRINT                    (M_LICENSE_FINGERPRINT+62)
#define M_ANY_FINGERPRINT                             M_MATROX_BOARD_FINGERPRINT

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_MODIFIED_BUFFER_HANDLER_PTR                 0x10000000L   // Must not interfere with M_ERROR
#define M_MODIFIED_BUFFER_HANDLER_USER_PTR            0x20000000L   // Must not interfere with M_ERROR
#endif
/************************************************************************/
/* License type info                                                    */
/************************************************************************/
#define M_SIMPLE_TYPE_MAX_SIZE                                      50
#define MAX_COMPANY_SIZE                                            25
#define MAX_FEATURE_SIZE                                            25
#define MAX_VERSION_SIZE                                             5
#define M_TYPE_LITE                                                  1
#define M_TYPE_FULL                                                  2
/************************************************************************/
/* MWrite() / MpatRead() Types                                          */
/************************************************************************/
#define M_FILE                                        25L


/************************************************************************/
/* MappInquire() / MappControl() Values                                 */
/************************************************************************/
#define M_PARAMETER_CHECK                    0x00000001L
#define M_PRINT_DISABLE                               0L
#define M_PRINT_ENABLE                                1L
#define M_CHECK_DISABLE                               2L
#define M_CHECK_ENABLE                                3L
#define M_COMPENSATION_DISABLE                        4L
#define M_COMPENSATION_ENABLE                         5L
#define M_HOOK_CONTEXT_SIZE                           6L
#define M_ENABLE_FOR_ALL_FUNCTIONS                    7L
#define M_DISABLE_FOR_ALL_FUNCTIONS                   8L
#define M_DISABLE_FOR_SOME_FUNCTIONS                  9L
#define M_DISP_HOOK_CONTEXT_SIZE                     10L
#define M_THROW_EXCEPTION                            11L          /* Value to enable exceptions in the MIL .NET wrapper (.NET only)  */
#define M_ADVANCE_MODE_DUMP                           1L

#define M_DMIL_CONTROL                                1L
#define M_DMIL_MONITOR                                2L

#define M_INTERNAL_USE                       0x00000004L
#define M_READ_WRITE                         0x00000010L
#define M_READ_ONLY                          0x00000020L

#define M_THREAD_RECURSIVE                            0x00800000L /* Bit field exclusive to M_TRACE  to M_PROCESSING      (3L to 6L) */
#define M_THREAD_CURRENT                              0x01000000L /*                        M_TRACE_START                       (1L) */
                                                                  /*                        M_TRACE_END                         (2L) */
                                                                  /*                        M_ERROR                     (0x40000000) */
                                                                  /*                        M_MESSAGE                   (0x20000000) */
                                                                  /*                        M_CURRENT to M_REGION_SIZE_Y (1L to 44L) */
                                                                  /*                        M_UNHOOK                    (0x04000000) */

// Possible value for the M_PANEL control
#define M_ENABLE                                      -9997L
#define M_DISABLE                                     -9999L
#define M_UPDATE_PANEL                                   1L
#define M_CLOSE_FROM_DLL                                 64L

// Values returned by MappInquire(M_DMA_MANAGER_TYPE)
#define DMA_MANAGER_TYPE_MTXDMA                                1
#define DMA_MANAGER_TYPE_MEMMAN                                2
#define DMA_MANAGER_TYPE_SERVMAN                               4


/************************************************************************/
/* MappInquireConnection()                                              */
/************************************************************************/
#define M_DMIL_PUBLISHED_LIST                   1
#define M_DMIL_PUBLISHED_LIST_SIZE              2
#define M_DMIL_PUBLISHED_NAME                   3


/************************************************************************/
/* MappTimer()                                                          */
/************************************************************************/
#define M_TIMER_MODE_MASK                             0x000F0000L
#define M_FIRST_TIMER_MODE                            0x00010000L
#define M_TIMER_ALLOC                                 0x00010000L
#define M_TIMER_FREE                                  0x00020000L
#define M_TIMER_RESOLUTION                            0x00030000L
#define M_TIMER_RESET                                 0x00040000L
#define M_TIMER_READ                                  0x00050000L
#define M_TIMER_WAIT                                  0x00060000L
#define M_TIMER_COMPENSATION                          0x00070000L
#define M_TIMER_WAIT_EXACT                            0x00080000L
#define M_TIMER_LOCK_TO_CPU                           0x00090000L
#define M_TIMER_UNLOCK_FROM_CPU                       0x000A0000L
#define M_TIMER_USE_CPU                               0x000B0000L
#define M_TIMER_USE_OS                                0x000C0000L
#define M_LAST_TIMER_MODE                             M_TIMER_USE_OS       // Update this define if other modes are added.

// Following defines are bitwise
#define M_TIMER_MIL_NOP                               0x00008000L
#define M_GLOBAL                                      0x00000008L
#define M_SYNCHRONOUS                                 0x00000001L


// Utility macro
#define M_TIMER_MODE_IS_VALID(m)                      ( ((m&(~M_TIMER_MODE_MASK)) == 0) &&                  \
                                                        ((m&M_TIMER_MODE_MASK) >= M_FIRST_TIMER_MODE) &&    \
                                                        ((m&M_TIMER_MODE_MASK) <= M_LAST_TIMER_MODE) )

/************************************************************************/
/* MappFileOperation()                                                  */
/************************************************************************/
#define M_FILE_EXECUTE                                      0x100
#define M_FILE_DELETE                                       0x200
#define M_FILE_COPY                                         0x300
#define M_FILE_COPY_DMILDLL                                 0x400
#define M_FILE_MAKE_DIR                                     0x500
#define M_FILE_DELETE_DIR                                   0x600
#define M_FILE_DISPATCH                                     0x700
#define M_FILE_OPERATIONS                                   0xF00
#define M_SYNCHRONOUS                                 0x00000001L
#define M_ASYNCHRONOUS                                0x00000002L

/************************************************************************/
/* MappModify()                                                         */
/************************************************************************/
#define M_SWAP_ID                1L

/************************************************************************/
/* Binary functions in BLOB module.                                     */
/************************************************************************/
#define M_LENGTH                                      0x00002000L

/************************************************************************/
/* MmeasCalculate(), MmeasGetResult(), MpatGetResult() */
/************************************************************************/
#define M_ANGLE                                       0x00000800L
#define M_ORIENTATION                                 0x00002400L

/************************************************************************/
/* MblobControl() and/or MblobInquire() values and MmeasControl()       */
/************************************************************************/
#define M_PIXEL_ASPECT_RATIO                          5L

/***********************************************************************/
/* MfuncParam... defines                                               */
/***********************************************************************/
#define M_FILE_READ                                   M_IN
#define M_FILE_WRITE                                  M_OUT
#define M_PA_FUNC_MAX_NB_PARAM                        M_NB_MAX_PARAMETER

/***********************************************************************/
/* MfuncDriverCall... defines                                          */
/***********************************************************************/
#define M_DONT_CONVERT_ID                             1L

/************************************************************************/
/* MfuncPrintMessage() defines                                          */
/************************************************************************/
// Return Value
#define M_RESP_YES                                    1L
#define M_RESP_NO                                     2L
#define M_RESP_CANCEL                                 4L
#define M_RESP_OK                                     8L

// Mode
#define M_RESP_OK                                     8L
#define M_RESP_YES_NO                                 (M_RESP_YES|M_RESP_NO)
#define M_RESP_YES_NO_CANCEL                          (M_RESP_YES|M_RESP_NO|M_RESP_CANCEL)
#define M_RESP_BUTTONS_MASK                         0xFL
// Additional Mode
#define M_ICON_STOP                          0x00000010L
#define M_ICON_EXCLAMATION                   0x00000030L
#define M_ICON_MASK                          0x000000F0L


/************************************************************************/
/* MfuncCalibrationInfo() defines                                       */
/************************************************************************/


#define M_CALIBRATION_STREAM_SIZE            0L    // already defined in mcalinfo.h
#define M_GET_CALIBRATION_INFO               1L    // already defined in mcalinfo.h
#define M_SET_CALIBRATION_INFO               2L    // already defined in mcalinfo.h
#define M_COPY_CALIBRATION_INFO              3L    // already defined in mcalinfo.h
#define M_GET_CALIBRATION_ID                 4L    // already defined in mcalinfo.h
#define M_SET_CALIBRATION_ID                 5L    // already defined in mcalinfo.h
#define M_CHANGE_ID_IN_CAL_STREAM            6L    // already defined in mcalinfo.h

#define M_ADD_CALIBRATION_USE                17L   // already defined in mcalinfo.h
#define M_REMOVE_CALIBRATION_USE             18L   // already defined in mcalinfo.h
#define M_USE_CALIBRATION                    19L   // already defined in mcalinfo.h
// other defines in mcalinfo.h

#define M_WORLD                         0x2000L
#define M_OUTPUT_UNITS                     122L
#define M_OUTPUT_COORDINATE_SYSTEM            M_OUTPUT_UNITS      /* deprecated name */
#define M_SAVE                           0x100L
#define M_ACCORDING_TO_CALIBRATION        1301L
#define M_ACCORDING_TO_RESULT             1302L

/************************************************************************/
/* MfuncAlloc defines                                                   */
/************************************************************************/

#define M_USER_FUNCTION                     0x4000E000
#define M_USER_MODULE_1                     0x4000E200
#define M_USER_MODULE_2                     0x4000E400
#define M_USER_MODULE_3                     0x4000E600
#define M_USER_MODULE_4                     0x4000E800
#define M_USER_MODULE_5                     0x4000EA00
#define M_USER_MODULE_6                     0x4000EC00
#define M_USER_MODULE_7                     0x4000EE00
#define M_USER_MODULE_PA                    0x4000F000
#define M_USER_PA_FUNCTION                  M_USER_MODULE_PA
#define M_USER_MODULE_FPGA                  0x4000FC00
#define M_USER_FPGA_FUNCTION                M_USER_MODULE_FPGA

// InitFlag values
#define M_ALLOC                             0x00010000   // Update opcodes.h accordingly
#define M_FREE                              0x00020000   // Update opcodes.h accordingly
#define M_SYNCHRONOUS_FUNCTION              0x00080000   // Update opcodes.h accordingly
#define M_ASYNCHRONOUS_FUNCTION             0x00000000
#define M_LOCAL                             0x01000000   // Update opcodes.h accordingly
#define M_REMOTE                            0x00000000
// Reserved: 0x00000001
#define M_DONT_ADD_ALWAYS_LOCAL             0x00000002L
#define M_INTERNAL_CALL                     0x00000004L  // Update decstatus.h accordingly
#define M_NON_PORTABLE_CALL                 0x00000008L  // Update decstatus.h accordingly
#define M_CONTROL_FLAG_MASK                 0x00000012L
#define M_STATUS_MASK                       0x0000000CL
#define M_STACK_BASED_FUNCTION              0x00000010L

#define M_NB_MAX_PARAMETER                  16L
#define M_NUMBER_OF_USER_MODULES            16L

#define M_CACHE_FLUSH                       8192L
#define M_NON_PAGED                         0x00200000L
#define M_PAGED                             0x02000000L
#define M_DEFAULT                           0x10000000L

/************************************************************************/
/* MfuncControl/MfuncInquire() defines                                  */
/************************************************************************/
#define M_CLIENT_ASCII_MODE           0x10000

#define M_USER_DATA_PTR            0x00000001
#define M_DRIVER_INFO_PTR                   2

/*Reserve                                   6
   and                                      7 8,11,12,14,15,16,17 */
#define M_RESULT_Q_PTR                      9
#define M_OBJECT_PTR                       10
#define M_SLAVE_FUNCTION_PTR               13
#define M_SLAVE_FUNCTION_OPCODE            18
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_INITFLAG                         19
#endif
#define M_PARAM_NUMBER                     20
#define M_USING_MODULES                    21
#define M_OBJECT_LOCK                      22
#define M_PUSH_TRACE_LEVEL                 23
#define M_POP_TRACE_LEVEL                  24
#define M_DRIVER_HOOK_CONTEXT_ID           25
#define M_ACTIVEMIL_TEMP_POPUP             27
#define M_ACTIVEMIL_INVALID_MODULE         28
#define M_OBJECT_TYPE_EXTENDED             29
/*Reserve                                  30*/
#define M_IS_NOT_INTERNAL_OBJECT           31
#define M_FUNCTION_NAME_SIZE               32L
#define M_DATAGRAM                         33
#define M_TRACE_LEVEL                      34
#define M_HI_PERM                          35
#define M_POP_HLVL_INFO                    36
#define M_ACCELERATED_MODE                 37
#define M_MIL_DLL_IN_DEBUG_MODE            38
#define M_LIC_DATA_BLOB                    39
#define M_LIC_DATA_BLOB_SIZE               40
#define M_IS_CLIENT_UNICODE                41
#define M_LIC_TRACE_INFO                   42
#define M_SPECIAL_DATA_PTR                 44
#define M_HLVL_TRACE_PTR                   45
#define M_EXP_DATE                         46
//47 and up are used by strings range(see below)
/***********************************************************************
 * FuncInquire string types
 ***********************************************************************/
#define M_FUNC_INQUIRE_STRING_START             47
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_ASSOCIATED_NAME                 ((M_FUNC_INQUIRE_STRING_START+0)|M_CLIENT_ASCII_MODE)
   #define M_FUNCTION_NAME_FROM_OPCODE       ((M_FUNC_INQUIRE_STRING_START+1)|M_CLIENT_ASCII_MODE)
   #define M_FUNCTION_NAME                   ((M_FUNC_INQUIRE_STRING_START+2)|M_CLIENT_ASCII_MODE)
   #define M_SLAVE_DLL_NAME                  ((M_FUNC_INQUIRE_STRING_START+3)|M_CLIENT_ASCII_MODE)
   #define M_SLAVE_FUNCTION_NAME             ((M_FUNC_INQUIRE_STRING_START+4)|M_CLIENT_ASCII_MODE)
   /* Reserve next values  from              ((M_FUNC_INQUIRE_STRING_START+5)|M_CLIENT_ASCII_MODE)
                           to                ((M_FUNC_INQUIRE_STRING_START+29)|M_CLIENT_ASCII_MODE)*/
#else
   #define M_ASSOCIATED_NAME                 (M_FUNC_INQUIRE_STRING_START+0)
   #define M_FUNCTION_NAME_FROM_OPCODE       (M_FUNC_INQUIRE_STRING_START+1)
   #define M_FUNCTION_NAME                   (M_FUNC_INQUIRE_STRING_START+2)
   #define M_SLAVE_DLL_NAME                  (M_FUNC_INQUIRE_STRING_START+3)
   #define M_SLAVE_FUNCTION_NAME             (M_FUNC_INQUIRE_STRING_START+4)
   /* Reserve next values  from              (M_FUNC_INQUIRE_STRING_START+5)  52
                           to                (M_FUNC_INQUIRE_STRING_START+29) 76 */
#endif
#define M_FUNC_INQUIRE_STRING_END            (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1)
/* Reserve next values for MappInquire string type sizes */
#define M_ASSOCIATED_NAME_SIZE                 (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+0) //TBA: MIL should support this inquire
#define M_FUNCTION_NAME_FROM_OPCODE_SIZE       (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+1) //TBA: MIL should support this inquire
#define M_FUNCTION_NAME_STR_SIZE               (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+2) //TBA: MIL should support this inquire
#define M_SLAVE_DLL_NAME_SIZE                  (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+3)
#define M_SLAVE_FUNCTION_NAME_SIZE             (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+4)
/* Reserve next values  from                   (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+5)  81 
                        to                     (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+29) 105 */
#define M_DMIL_CONNECT_TO_CE               106

#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_DMIL_CONNECT_TO_NON_CE           107
#endif
#define M_MAYBE_USING_MODULES              108
#define M_PUSH_APP_CONTROLS                109
#define M_POP_APP_CONTROLS                 110
#define M_DELETE_STACK_BASED_CALL_CONTEXT  111
#define M_DMIL_CONNECT_TO_REMOTE           112
#define M_HAS_DMILC                        113
#define M_DMIL_CONNECT_TO_REMOTE_DMILC     114
#define M_GET_GE_INFO                      115
#define M_CONNECT_TO_GE                    116
#define M_CONNECT_TO_OC                    117
#define M_PERM_OK_CAL_LITE                 118
#define M_PERM_OK_CAL_CAL                  119
#define M_PERM_OK_CAL_CAL3D                120

#define M_USING_PERMISSION         0x00010000
#define M_CONNECTING_TO_GE                 (M_USING_PERMISSION+M_CONNECT_TO_GE)
#define M_CONNECTING_TO_OC                 (M_USING_PERMISSION+M_CONNECT_TO_OC)
#define M_DMIL_CONNECTING_TO_CE            (M_USING_PERMISSION+M_DMIL_CONNECT_TO_CE)
#define M_DMIL_CONNECTING_TO_REMOTE        (M_USING_PERMISSION+M_DMIL_CONNECT_TO_REMOTE)
#define M_DMIL_CONNECTING_TO_REMOTE_DMILC  (M_USING_PERMISSION+M_DMIL_CONNECT_TO_REMOTE_DMILC)
#define M_PERM_USING_CAL_LITE              (M_USING_PERMISSION+M_PERM_OK_CAL_LITE)
#define M_PERM_USING_CAL_CAL               (M_USING_PERMISSION+M_PERM_OK_CAL_CAL)  
#define M_PERM_USING_CAL_CAL3D             (M_USING_PERMISSION+M_PERM_OK_CAL_CAL3D)

#define M_OBJECT_TYPE                      162 // Cannot be changed, because was used in milmod, now report an error (see milmod)
#define M_CUSTOM_TASK                      163
#define M_DMIL_MONITORING_MODE             164


#define M_OBJECT_VALID                   1038L
#define M_IS_INTERNALLY_ALLOCATED        1043L 
#define M_LOCATION                       1048L  // Cannot be changed, used by MsysInquire
#if !M_MIL_USE_UNIFIED_MILBUFFERINFO || (!M_COMPILING_MILDLL && ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x91)))
#define M_BUFFER_INFO                    M_BUFFER_INFO_BW
#else
#define M_BUFFER_INFO                    5280L
#endif

#define M_PARAM_TYPE               0x10000000L
/* Reserve next 15 values   from   0x10000001L*/
/*                          to     0x1000000FL*/

#define M_TRACE_HOOKS                                 (M_APP_INQUIRE_SYS_START+2L)  //15002L

/************************************************************************/
/* MappInquireObject()/MappControlObject() defines                      */
/************************************************************************/
#define M_DMIL_PUBLISH                        12L
#define M_OBJECT_TYPE_EXTENDED                29
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_ASSOCIATED_NAME                 ((M_FUNC_INQUIRE_STRING_START+0)|M_CLIENT_ASCII_MODE) //47
#else
   #define M_ASSOCIATED_NAME                 (M_FUNC_INQUIRE_STRING_START+0)
#endif
#define M_FUNC_INQUIRE_STRING_END            (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1)
#define M_OBJECT_NAME                        M_ASSOCIATED_NAME

#define M_ASSOCIATED_NAME_SIZE               (M_FUNC_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+0)
#define M_OBJECT_NAME_SIZE                   M_ASSOCIATED_NAME_SIZE
#define M_OBJECT_TYPE                        162 


#define M_APP_INQUIRE_OBJ_DOUBLE_RANGE_START    10000
#define M_APP_INQUIRE_OBJ_DOUBLE_RANGE_END      20000

#define M_APP_INQUIRE_OBJ_INT64_RANGE_START    20001
#define M_APP_INQUIRE_OBJ_INT64_RANGE_END      21000

//////////////////////////////////////////////////////////////////////////
// MappInquireObject (InquireType range values)
#define M_IN_APP_INQUIRE_OBJ_DOUBLE_RANGE(X)       (((X) >= M_APP_INQUIRE_OBJ_DOUBLE_RANGE_START) &&\
                                                    ((X) <= M_APP_INQUIRE_OBJ_DOUBLE_RANGE_END))
#define M_IN_APP_INQUIRE_OBJ_STRING_RANGE(X)       ((X) == M_ASSOCIATED_NAME)

#define M_IN_APP_INQUIRE_OBJ_INT64_RANGE(X)       ((((X) >= M_APP_INQUIRE_OBJ_INT64_RANGE_START) && ((X) <= M_APP_INQUIRE_OBJ_INT64_RANGE_END)) || \
                                                   (((X)==M_OBJECT_TYPE) || ((X)==M_OBJECT_TYPE_EXTENDED)))
#if M_MIL_USE_64BIT
#define M_APP_INQUIRE_OBJ_MUST_HAVE_USER_PTR(X)    M_IN_APP_INQUIRE_OBJ_STRING_RANGE((X)& ~M_CLIENT_ASCII_MODE)
#else
#define M_APP_INQUIRE_OBJ_MUST_HAVE_USER_PTR(X)    (M_IN_APP_INQUIRE_OBJ_STRING_RANGE((X)& ~M_CLIENT_ASCII_MODE) || M_IN_APP_INQUIRE_OBJ_INT64_RANGE(X))
#endif

/************************************************************************/
/* MilGPU                                                               */
/************************************************************************/
  /* Vertex processing type */
#define M_SOFTWARE                                    20L
#define M_HARDWARE                                    21L
#define M_MIXED                                       22L

  /* GPU specific errors */
#define M_GPU_ERROR_START                             0x710
#define M_GPU_ERROR_DIRECTX_NOTSUPPORTED              (M_GPU_ERROR_START+1)
#define M_GPU_ERROR_INVALID_DECODER                   (M_GPU_ERROR_START+2)
#define M_GPU_ERROR_D3D9_NOTLOADED                    (M_GPU_ERROR_START+3)
#define M_GPU_ERROR_D3D10_NOTLOADED                   (M_GPU_ERROR_START+4)
/* Reserve next 5 values                       from   (M_GPU_ERROR_START+5)*/
/*                                             to     (M_GPU_ERROR_START+9)*/
#define M_GPU_ERROR_END                               (M_GPU_ERROR_START+10)

#define M_IS_GPU_SPECIFIC_ERROR(x)                    ((x > M_GPU_ERROR_START) && (x < M_GPU_ERROR_END))
#define M_GPU_ERROR_GET_CODE(x)                       (x >> 4)
#define M_GPU_ERROR_GET_SUBMSG(x)                     (x - M_GPU_ERROR_START)


/************************************************************************/
/* MobjControl()/MobjInquire() defines                                  */
/************************************************************************/
#define M_MAP_HOOK_CONTEXT                             1L
#define M_INIT_HOOK_CONTEXT                            2L
#define M_COPY_CALIBRATION_INFO                        3L   // already defined in mcalinfo.h
#define M_CALIBRATION_ID                               4L
#define M_CORRECTED_SCALES                             5L
#define M_CALIBRATION_TRANSLATIONS                     6L
#define M_COMPARE_CALIBRATION_INFO                     7L   // already defined in mcalinfo.h
#define M_COMPARE_CALIBRATION_INFO_NO_OFFSET           8L   // already defined in mcalinfo.h
#define M_REAL_OWNER_SYSTEM                            9L
#define M_COPY_DISP_HOOK_CONTEXT                      10L
#define M_CAL_PARENT_OFFSETS                          11L
#define M_DMIL_PUBLISH                                12L
#define M_ASSOCIATED_CALIBRATION                     125L   // already defined in milcal.h
#define M_COPY_HOOK_CONTEXT                          103L
#define M_COPY_NEIGHBORHOOD_INFO                     104L
#define M_NEIGHBORHOOD_INFO_SIZE                     105L
#define M_CALIBRATION_STREAM_SIZE_WITH_CONTEXT      1405L
#define M_CALIBRATION_STREAM_WITH_CONTEXT           1406L





// Used in MfuncControl/MfuncInquire
#define M_OBJECT_TYPE                                162 // Cannot be change, because was used in milmod, now report an error (see milmod)

#define M_OBJECT_TYPE_EXTENDED                        29  // Used in MfuncControl/MfuncInquire
#define M_OWNER_SYSTEM                              1101L // Used in many places
#define M_IS_INTERNALLY_ALLOCATED                   1043L // Used by MbufControl/MbufInquire but kept in MGObject
#define M_OBJECT_ID                           0x001B0000L // MbufGetHookInfo, MbufHookFunction
#define M_GRAB_LINE                           0x00100000L // MdigHookFunction
#define M_GRAB_LINE_END                       0x00200000L // MdigHookFunction

/************************************************************************/
/* Special defines required to pass a pointer to a function that needs  */
/* a double. (use in McalControl to set a user string in the context)   */
/************************************************************************/
#if !M_MIL_USE_64BIT
#define M_PTR_TO_DOUBLE(ptr)            ((double) MPtrToInt((void*)(ptr)))
#define M_STRING_TO_DOUBLE(ptr)         M_PTR_TO_DOUBLE((ptr))
#else
#define M_PTR_TO_DOUBLE(ptr)            (MIL_INT64)(ptr)
#define M_STRING_TO_DOUBLE(ptr)         M_PTR_TO_DOUBLE(ptr)
#endif //!M_MIL_USE_64BIT
#define M_DOUBLE_TO_PTR(val)            ((void *)((MIL_UINT)val))

/************************************************************************/
/* Reserved MIL_IDs                                                     */
/************************************************************************/
#define M_DEFAULT_HOST                                M_MAKE_DEFAULT_ID(1)
#define M_DEFAULT_GRAPHIC_CONTEXT                     M_MAKE_DEFAULT_ID(2)
#define M_INTERNAL_DEFAULT_HOST                       M_MAKE_DEFAULT_ID(3)
#define M_VIDEO_DEVICE_ID                             M_MAKE_DEFAULT_ID(4)
//Reserve next M_MAX_VIDEO_DEVICE IDs (reserved 64)   -> 68
#define M_RESERVED_ID_END                             M_MAKE_DEFAULT_ID(4 + M_MAX_VIDEO_DEVICE)


/************************************************************************/
/* MIL OPTIONAL COMPILE DEFINES prefixes */
/************************************************************************/

#if M_MIL_USE_WINDOWS
   #define MFTYPE        _stdcall         // Exported Function type (32 bits)
   #define MFHOOKTYPE    _stdcall         // Same as MFTYPE, for internal use only.
   #define MFTYPE32                       // Exported Function type (32 bits)
   #define MFCTYPE       _stdcall         // Exported C Function type (32 bits)
   #define MFCTYPE32                      // Exported C Function type (32 bits)
   #define MFTYPEHT      _stdcall         // Non Exported Function type
   #define MPTYPE                         // Pointer and Reference type
   #define MFINLINE      inline           // Inline function type
   #define MHUGETYPE                      // To force HUGE pointers
   #define MFARTYPE                       // To force FAR type pointers
   #define MINTFTYPE     _stdcall         // Interrupt Function type (16 bits)
   #define MREGTYPE      register         // Register type variables
#elif M_MIL_USE_PPC || M_MIL_USE_LINUX
// Much more to define for MIL generation on PPC
   #define MFTYPE                         // Exported Function type (16 bits)
   #define MFHOOKTYPE                     // Same as MFTYPE, for internal use only.
   #define MFTYPE32                       // Exported Function type (32 bits)
   #define MFCTYPE                        // Exported C Function type (16 bits)
   #define MFCTYPE32                      // Exported C Function type (32 bits)
   #define MFTYPEHT                       // Non Exported Function type
   #define MPTYPE                         // Pointer and Reference type
   #define MFINLINE      inline           // Inline function type
   #define MHUGETYPE                      // To force HUGE pointers
   #define MFARTYPE                       // To force FAR type pointers
   #define MINTFTYPE     MFTYPE           // Interrupt Function type (16 bits)
   #define MREGTYPE      register         // Register type variables
#else
   #error Operating system not supported in Mil.h!
#endif


/************************************************************************/
/* Temporary define                                                     */
/************************************************************************/
/* Also in milim.h.  Needed to compile mil.h. */
#define M_OVERSCAN_CLEAR                              0x00000080L

#define M_POLAR                                       5L

#define M_REVERSE                                     4L

#define M_IN_RANGE                                    1L
#define M_OUT_RANGE                                   2L

#define M_ADD                                         0x0000L
#define M_ADD_CONST                                   (M_ADD  | M_CONSTANT)
#define M_SUB                                         0x0001L
#define M_SUB_CONST                                   (M_SUB | M_CONSTANT)
#define M_MULT                                        0x0100L
#define M_MULT_CONST                                  (M_MULT | M_CONSTANT)
#define M_DIV                                         0x0101L
#define M_DIV_CONST                                   (M_DIV  | M_CONSTANT)

#define M_BINARY                                      0x00001000L
#define M_AVERAGE                                     0x00000020L
#define M_INTERPOLATE                                 0x00000004L

#define M_MIN_ABS_VALUE                               4L
#define M_MAX_ABS_VALUE                               5L

#define M_MASK                                        0x00001000L

#define M_SHEN                                        0x802L

#define M_DERICHE                                     M_ID_OFFSET_OF_DEFAULT_KERNEL + 10L

#define M_SMOOTH                                      (M_ID_OFFSET_OF_DEFAULT_KERNEL +  0L)
#define M_LAPLACIAN_EDGE                              (M_ID_OFFSET_OF_DEFAULT_KERNEL +  1L)
#define M_SHARPEN                                     (M_ID_OFFSET_OF_DEFAULT_KERNEL +  3L)
#define M_HORIZ_EDGE                                  (M_ID_OFFSET_OF_DEFAULT_KERNEL +  5L)
#define M_VERT_EDGE                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL +  6L)
#define M_EDGE_DETECT                                 (M_ID_OFFSET_OF_DEFAULT_KERNEL +  7L)
#define M_EDGE_DETECT2                                (M_ID_OFFSET_OF_DEFAULT_KERNEL +  8L)
#define M_EDGE_DETECT_SQR                             (M_ID_OFFSET_OF_DEFAULT_KERNEL +  9L)
#define M_FIRST_DERIVATIVE_X                          (M_ID_OFFSET_OF_DEFAULT_KERNEL + 10L)
#define M_FIRST_DERIVATIVE_Y                          (M_ID_OFFSET_OF_DEFAULT_KERNEL + 11L)
#define M_SECOND_DERIVATIVE_X                         (M_ID_OFFSET_OF_DEFAULT_KERNEL + 12L)
#define M_SECOND_DERIVATIVE_Y                         (M_ID_OFFSET_OF_DEFAULT_KERNEL + 13L)
#define M_SECOND_DERIVATIVE_XY                        (M_ID_OFFSET_OF_DEFAULT_KERNEL + 14L)

/* Also in milim.h.  Needed to compile drivers. */
#define M_FORWARD                                     0x01
#define M_BACKWARD                                    0x02

#define M_ID_OFFSET_OF_DEFAULT_CONVERT                (0x00200000L|M_PSEUDO_ID)

#define M_RGB_TO_HSL                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 1L)     // Same as Milim.h
#define M_RGB_TO_HLS                                  M_RGB_TO_HSL                              // Obsolete
#define M_RGB_TO_L                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 2L)     // Same as Milim.h
#define M_HSL_TO_RGB                                  (M_ID_OFFSET_OF_DEFAULT_CONVERT + 3L)     // Same as Milim.h
#define M_HLS_TO_RGB                                  M_HSL_TO_RGB                              // Obsolete
#define M_L_TO_RGB                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 4L)     // Same as Milim.h
#define M_RGB_TO_Y                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 5L)     // Same as Milim.h
#define M_RGB_TO_H                                    (M_ID_OFFSET_OF_DEFAULT_CONVERT + 6L)     // Same as Milim.h

#define M_RGB_TO_YUV16                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 101L)   // Same as Milim.h, mildev.h
#define M_RGB_TO_YCBCR                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 7L)
#define M_RGB_TO_YCRCB                                M_RGB_TO_YCBCR                            //Obsolete
#define M_RGB_TO_YCLIP                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 8L)
#define M_YUV16_TO_RGB                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 301L)   // Same as Milim.h, mildev.h
#define M_YCBCR_TO_RGB                                (M_ID_OFFSET_OF_DEFAULT_CONVERT + 9L)
#define M_YCRCB_TO_RGB                                M_YCBCR_TO_RGB                            //Obsolete

#define M_FLIP_VERTICAL                               1L
#define M_FLIP_HORIZONTAL                             2L

#define M_NOT_WRITE_ANGLE                             1L
#define M_NOT_WRITE_INT                               2L
#define M_FAST_ANGLE                                  4L
#define M_FAST_GRADIENT                               8L
#define M_FAST_EDGE_DETECT                            (M_FAST_ANGLE + M_FAST_GRADIENT)
#define M_REGULAR_ANGLE                               16L
#define M_REGULAR_GRADIENT                            64L
#define M_REGULAR_EDGE_DETECT                         (M_REGULAR_ANGLE + M_REGULAR_GRADIENT)
#define M_USE_RESERVED_ANGLE_VALUE                    128L

#define M_MEDIAN                                      0x10000L
#define M_3X3_RECT                                    (M_ID_OFFSET_OF_DEFAULT_KERNEL + 20L)
#define M_3X3_CROSS                                   (M_ID_OFFSET_OF_DEFAULT_KERNEL + 21L)

#define M_TO_SKELETON                                 -1L
#define M_TO_IDEMPOTENCE                              M_TO_SKELETON

#define M_CHAMFER_3_4                                 0x01
#define M_CITY_BLOCK                                  0x02
#define M_CHESSBOARD                                  0x04

#define M_HIT_OR_MISS                                 5L
#define M_HIT_THRESHOLD                              16L

/************************************************************************/
/* M_MISC_DATA_TRANSFER related defines */
#define M_REGISTER_HOOK_THREAD                        1L
#define M_INTERNAL_THREAD_ERROR_TOOLS                 2L

#define M_HAS_BUFTRANSFER_FORMAT1(X) ( (M_DIRECTX|M_MTX0) & (X) )
#define M_HAS_BUFTRANSFER_FORMAT(X,Y) ((M_HAS_BUFTRANSFER_FORMAT1(X) & M_HAS_BUFTRANSFER_FORMAT1(Y)) != 0)


//////////////////////////////////////////////////////////////////////////
// MbufControl (ControlType range values)
#define M_BUF_CONTROL_DOUBLE_RANGE_START 0x02000000L // M_MIN
#define M_BUF_CONTROL_DOUBLE_RANGE_END   0x04000000L // M_MAX
#define M_IN_BUF_CONTROL_DOUBLE_RANGE(X) ((X >= M_BUF_CONTROL_DOUBLE_RANGE_START) && (X <= M_BUF_CONTROL_DOUBLE_RANGE_END))

//////////////////////////////////////////////////////////////////////////
// MbufInquire (InquireType range values)
#define M_BUF_INQUIRE_DOUBLE_RANGE_START 0x02000000L // M_MIN
#define M_BUF_INQUIRE_DOUBLE_RANGE_END   0x04000000L // M_MAX

#define M_IN_BUF_INQUIRE_DOUBLE_RANGE(X) ((X >= M_BUF_INQUIRE_DOUBLE_RANGE_START) && (X <= M_BUF_INQUIRE_DOUBLE_RANGE_END))

#define M_IN_BUF_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) ((InquireType >= M_BUF_INQUIRE_UNKNOWN_SIZEOF_START) &&     \
                                                             (InquireType <= M_BUF_INQUIRE_UNKNOWN_SIZEOF_END)    )


#define M_IN_BUF_INQUIRE_MIL_ID_RANGE(X) ((X >= M_BUF_INQUIRE_MIL_ID_START) &&     \
                                          (X <= M_BUF_INQUIRE_MIL_ID_END)    )

#define M_IN_BUF_INQUIRE_MIL_INT64_RANGE(X) (X == M_EXTENDED_FORMAT    || \
                                             X == M_EXTENDED_ATTRIBUTE || \
                                             X == M_64BIT_HOST_ADDRESS || \
                                             ((X>=M_64BIT_HOST_ADDRESS_BAND) && (X<(M_64BIT_HOST_ADDRESS_BAND+16))) ||\
                                             ((X>=M_64BIT_PHYSICAL_ADDRESS_BAND) && (X<(M_64BIT_PHYSICAL_ADDRESS_BAND+16))) ||\
                                             X == M_FLAGS              || \
                                             X == M_64BIT_PHYSICAL_ADDRESS || \
                                             ((X >= M_BUF_INQUIRE_SIZEOF_INT64_START) && (X <= M_BUF_INQUIRE_SIZEOF_INT64_END)    ))

#if M_MIL_USE_64BIT
#define M_BUF_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_BUF_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType)  )
#else
#define M_BUF_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_BUF_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) || \
                                                       M_IN_BUF_INQUIRE_MIL_INT64_RANGE(InquireType)        )
#endif

//////////////////////////////////////////////////////////////////////////
// MdigInquire (InquireType range values)
#define M_IN_DIG_INQUIRE_STRING_RANGE(InquireType) (((InquireType&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == M_MODEL)                                            || \
                                                    (((InquireType&~(M_CLIENT_ASCII_MODE|M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) >= M_DIG_INQUIRE_STRING_START) && \
                                                    ((InquireType&~(M_CLIENT_ASCII_MODE|M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) <= M_DIG_INQUIRE_STRING_END)   ) )

#define M_IN_DIG_INQUIRE_MIL_ID_RANGE(X) (((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) >= M_DIG_INQUIRE_MIL_ID_START) &&     \
                                          ((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) <= M_DIG_INQUIRE_MIL_ID_END)    )

#define M_IN_DIG_INQUIRE_DOUBLE_RANGE(X)   ((((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK|M_MAX_VALUE|M_MIN_VALUE)) >= M_DIG_INQUIRE_SIZEOF_DOUBLE_START) &&            \
                                             ((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK|M_MAX_VALUE|M_MIN_VALUE)) <= M_DIG_INQUIRE_SIZEOF_DOUBLE_END)     )        || \
                                            ((X & ~(M_ALL_REF | M_VOLTAGE | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == M_BLACK_REF_DOUBLE)  || \
                                            ((X & ~(M_ALL_REF | M_VOLTAGE | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == M_WHITE_REF_DOUBLE)  || \
                                            ((X & ~(M_ALL_REF | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == (M_BLACK_REF | M_VOLTAGE))       || \
                                            ((X & ~(M_ALL_REF | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == (M_WHITE_REF | M_VOLTAGE))       || \
                                            ((X & ~(M_MAX | M_MIN | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK | M_MODE_CONTROL | M_ABSOLUTE_CTL_MASK)) == M_GAMMA)  )

#if DIG_CONTROL_TYPE_IS_INT64
#define M_IN_DIG_INQUIRE_MIL_INT64_RANGE(X)   (((((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) >= M_DIG_INQUIRE_SIZEOF_INT64_START) &&     \
                                                ((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) <= M_DIG_INQUIRE_SIZEOF_INT64_END)))  ||     \
                                                ((X&~(M_SIGNAL | M_SYNC | M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) == M_CHANNEL)       )
#else
#define M_IN_DIG_INQUIRE_MIL_INT64_RANGE(X)   ((((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) >= M_DIG_INQUIRE_SIZEOF_INT64_START) &&     \
                                                ((X&~(M_DIG_CONTROL_TYPE_RESERVED_BIT_MASK)) <= M_DIG_INQUIRE_SIZEOF_INT64_END)))
#endif


//////////////////////////////////////////////////////////////////////////
// MdispInquire (InquireType range values)
#define M_IN_DISP_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) ((InquireType == M_GRAB_BUFFERS)     || \
                                                              (InquireType == M_ROI_RECT_BUFFER)  || \
                                                              (InquireType == M_ROI_RECT_DISPLAY) || \
                                                              (InquireType == M_NEAREST_COLOR)    || \
                                                              ((M_ORIGINAL_DISPLAY_CONTROL(InquireType) >= M_DISP_INQUIRE_UNKNOWN_SIZEOF_START) && \
                                                               (M_ORIGINAL_DISPLAY_CONTROL(InquireType) <= M_DISP_INQUIRE_UNKNOWN_SIZEOF_END)    ) )

#define M_IN_DISP_INQUIRE_STRING_RANGE(InquireType) ((((M_ORIGINAL_DISPLAY_CONTROL(InquireType)&~M_CLIENT_ASCII_MODE) >= M_DISP_INQUIRE_STRING_START)  &&       \
                                                      ((M_ORIGINAL_DISPLAY_CONTROL(InquireType)&~M_CLIENT_ASCII_MODE) <= M_DISP_INQUIRE_STRING_END)     )   || \
                                                     ((InquireType&~M_CLIENT_ASCII_MODE) == M_VIDEO_DEVICE_DESCRIPTION_STRING)  || \
													              ((InquireType&~M_CLIENT_ASCII_MODE) == M_SUPPORTED_DISPLAY_TYPE_STRING)     )

#if OldDefinesSupport 
   #define M_IN_DISP_INQUIRE_MIL_ID_RANGE(X)((X == M_OWNER_SYSTEM)                     || \
                                             (X == M_SELECTED)                         || \
                                             (X == M_SYSTEM_ASSOCIATED_TO_DX_OBJECT)   || \
                                             (X == M_VGA_DEVICE_SYSTEM)                || \
                                             (X == M_VGA_SYSTEM_FROM_PHYSICAL_ADDRESS) || \
                                             (X == M_DDRAW_UNDERLAY_ID)                || \
                                             (X == M_LUT_ID)                           || \
                                             (X == M_OVERLAY_LUT)                      || \
                                             (X == M_WINDOW_BUF_ID)                    || \
                                             (X == M_ASSOCIATED_LUT)                   || \
                                             (X == M_OVERLAY_ID))
#else
   #define M_IN_DISP_INQUIRE_MIL_ID_RANGE(X)(((M_ORIGINAL_DISPLAY_CONTROL(X) >= M_DISP_INQUIRE_MIL_ID_START) && (M_ORIGINAL_DISPLAY_CONTROL(X) <= M_DISP_INQUIRE_MIL_ID_END))    || \
                                             ((M_ORIGINAL_DISPLAY_CONTROL(X) >= M_VGA_DEVICE_SYSTEM) && (M_ORIGINAL_DISPLAY_CONTROL(X) <= M_VGA_DEVICE_SYSTEM+M_MAX_VIDEO_DEVICE)) || \
                                             (X == M_SYSTEM_ASSOCIATED_TO_DX_OBJECT)   || \
                                             (X == M_VGA_SYSTEM_FROM_PHYSICAL_ADDRESS) || \
                                             (X == M_CUSTOM_DISPLAY)                   || \
                                             (X == M_ENCODER_OVR_BUF_ID)                )
 
#endif

#define M_IN_DISP_INQUIRE_DOUBLE_RANGE(X) (((M_ORIGINAL_DISPLAY_CONTROL(X) >= M_DISP_INQUIRE_SIZEOF_DOUBLE_START) &&      \
                                            (M_ORIGINAL_DISPLAY_CONTROL(X) <= M_DISP_INQUIRE_SIZEOF_DOUBLE_END)    )   || \
                                           ((M_ORIGINAL_DISPLAY_CONTROL(X) >= M_UNDERLAY_DOUBLE_RANGE_START)      &&      \
                                            (M_ORIGINAL_DISPLAY_CONTROL(X) <= M_UNDERLAY_DOUBLE_RANGE_END)         )    ) \



#define M_IN_DISP_INQUIRE_MIL_INT64_RANGE(X) ((M_ORIGINAL_DISPLAY_CONTROL(X) >= M_DISP_INQUIRE_SIZEOF_INT64_START) && \
                                              (M_ORIGINAL_DISPLAY_CONTROL(X) <= M_DISP_INQUIRE_SIZEOF_INT64_END)    )

#if M_MIL_USE_64BIT
#define M_DISP_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_DISP_INQUIRE_STRING_RANGE(InquireType)          || \
                                                        M_IN_DISP_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType)  )
#else
#define M_DISP_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_DISP_INQUIRE_STRING_RANGE(InquireType)          || \
                                                        M_IN_DISP_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) || \
                                                        M_IN_DISP_INQUIRE_MIL_INT64_RANGE(InquireType)        )
#endif


#define M_IN_DISP_INQUIRE_MIL_INT_RANGE(X) (!M_IN_DISP_INQUIRE_DOUBLE_RANGE(X) && \
                                            !M_IN_DISP_INQUIRE_MIL_ID_RANGE(X)     && \
                                            !M_DISP_INQUIRE_MUST_HAVE_USER_PTR(X)            )

#define M_IN_DISP_CONTROL_DOUBLE_RANGE(X)   M_IN_DISP_INQUIRE_DOUBLE_RANGE(X)
#define M_IN_DISP_CONTROL_STRING_RANGE(X)   M_IN_DISP_INQUIRE_STRING_RANGE(X)
#define M_IN_DISP_CONTROL_MIL_ID_RANGE(X)   M_IN_DISP_INQUIRE_MIL_ID_RANGE(X)



//////////////////////////////////////////////////////////////////////////
// MsysInquire (InquireType range values)

#define M_IN_SYS_INQUIRE_STRING_RANGE(InquireType) ( (                                                                                                                                                         \
                                                       ((InquireType&M_CLIENT_ASCII_MODE) == M_CLIENT_ASCII_MODE )          &&                                                                                 \
                                                       (                                                                                                                                                       \
                                                        (((InquireType&~M_CLIENT_ASCII_MODE) >= M_SYS_INQUIRE_STRING_START)      && ((InquireType&~M_CLIENT_ASCII_MODE) <= M_SYS_INQUIRE_STRING_END))       || \
                                                        (((InquireType&~M_CLIENT_ASCII_MODE) >= M_SYSINQ_CPU_STRING_START)       && ((InquireType&~M_CLIENT_ASCII_MODE) <= M_SYSINQ_CPU_STRING_END))        || \
                                                        (((InquireType&~M_CLIENT_ASCII_MODE) >= M_SYS_APP_INQUIRE_STRING_START)  && ((InquireType&~M_CLIENT_ASCII_MODE) <= M_SYS_APP_INQUIRE_STRING_END))      \
                                                       )                                                                                                                                                       \
                                                     )                                                                                                                                                         \
                                                     ||                                                                                                                                                        \
                                                     ( !(InquireType&M_CLIENT_ASCII_MODE) &&                                                                                                                   \
                                                        (                                                                                                                                                      \
                                                        ((InquireType >= M_SYS_INQUIRE_STRING_START)        && (InquireType <= M_SYS_INQUIRE_STRING_END))      ||                                              \
                                                        ((InquireType >= M_SYSINQ_CPU_STRING_START)         && (InquireType <= M_SYSINQ_CPU_STRING_END ))      ||                                              \
                                                        ((InquireType >= M_SYS_APP_INQUIRE_STRING_START)    && (InquireType <= M_SYS_APP_INQUIRE_STRING_END ))                                                 \
                                                         )                                                                                                                                                     \
                                                     )                                                                                                                                                         \
                                                   )

#define M_IN_SYS_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) ((InquireType >= M_SYS_INQUIRE_UNKNOWN_SIZEOF_START) && \
                                                             (InquireType <= M_SYS_INQUIRE_UNKNOWN_SIZEOF_END)   )

#define M_IN_SYS_INQUIRE_MIL_ID_RANGE(InquireType) ((InquireType >= M_SYS_INQUIRE_MIL_ID_START) && \
                                                    (InquireType <= M_SYS_INQUIRE_MIL_ID_END)    )

#define M_IN_SYS_INQUIRE_DOUBLE_RANGE(InquireType) (((InquireType >= M_SYS_INQUIRE_SIZEOF_DOUBLE_START) && \
                                                    (InquireType <= M_SYS_INQUIRE_SIZEOF_DOUBLE_END))   ||\
                                                       (InquireType == M_TEMPERATURE)  )

#define M_IN_SYS_INQUIRE_MIL_INT64_RANGE(InquireType) (((InquireType >= M_SYS_INQUIRE_SIZEOF_INT64_START) && \
                                                        (InquireType <= M_SYS_INQUIRE_SIZEOF_INT64_END)    ) ||\
                                                       (InquireType == M_GC_TOTAL_BYTES_RECEIVED))

#if M_MIL_USE_64BIT
#define M_IN_SYS_INQUIRE_MIL_INT_RANGE(InquireType) ((!M_IN_SYS_INQUIRE_MIL_ID_RANGE(InquireType)          &&     \
                                                      !M_IN_SYS_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) &&     \
                                                      !M_IN_SYS_INQUIRE_STRING_RANGE(InquireType)           )  || \
                                                       M_IN_SYS_INQUIRE_MIL_INT64_RANGE(InquireType)              )
#else
#define M_IN_SYS_INQUIRE_MIL_INT_RANGE(InquireType) ((!M_IN_SYS_INQUIRE_MIL_ID_RANGE(InquireType)          && \
                                                      !M_IN_SYS_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) && \
                                                      !M_IN_SYS_INQUIRE_STRING_RANGE(InquireType)           ) )
#endif

#if !M_MIL_USE_64BIT
#define M_SYS_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_SYS_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) || \
                                                       M_IN_SYS_INQUIRE_STRING_RANGE(InquireType)          || \
                                                       M_IN_SYS_INQUIRE_MIL_INT64_RANGE(InquireType)        )
#else
#define M_SYS_INQUIRE_MUST_HAVE_USER_PTR(InquireType) (M_IN_SYS_INQUIRE_UNKNOWN_SIZE_OF_RANGE(InquireType) || \
                                                       M_IN_SYS_INQUIRE_STRING_RANGE(InquireType)           )
#endif

//////////////////////////////////////////////////////////////////////////
// MgraInquire / MgraInquireList (InquireType range values)
#define M_IN_GRA_INQUIRE_DOUBLE_RANGE(X) (((X & ~(M_RED+M_GREEN+M_BLUE)) == M_COLOR         ) || \
                                          ((X & ~(M_RED+M_GREEN+M_BLUE)) == M_BACKCOLOR     ) || \
                                          ((X & ~(M_RED+M_GREEN+M_BLUE)) == M_SELECTED_COLOR) || \
                                          (X == M_FONT_X_SCALE     ) || \
                                          (X == M_FONT_Y_SCALE     ) || \
                                          (X == M_RED_8_BIT        ) || \
                                          (X == M_GREEN_8_BIT      ) || \
                                          (X == M_BLUE_8_BIT       ) || \
                                          (X == M_BACK_RED_8_BIT   ) || \
                                          (X == M_BACK_GREEN_8_BIT ) || \
                                          (X == M_BACK_BLUE_8_BIT  ) || \
                                          (X == M_POSITION_X      ) || \
                                          (X == M_POSITION_Y      ) || \
                                          (X == M_ANGLE           ) || \
                                          (X == M_ANGLE_START     ) || \
                                          (X == M_ANGLE_END       ) || \
                                          ((M_GRA_INQUIRE_DOUBLE_RANGE_START <= X) && (X <= M_GRA_INQUIRE_DOUBLE_RANGE_END)))

#define M_IN_GRA_INQUIRE_MIL_ID_RANGE(X) ((X == M_OWNER_SYSTEM)     || \
                                          ((M_GRA_INQUIRE_MIL_ID_RANGE_START <= X) && (X <= M_GRA_INQUIRE_MIL_ID_RANGE_END)))


/************************************************************************/
/* Miltracer defines                                                   */
/************************************************************************/
#define M_TRACE_STRING_LENGTH                         512

/************************************************************************/
/* MIL command decoder functions */
#include <mildec.h>

/************************************************************************/
/* MIL library prototypes */
#include <milproto.h>

/************************************************************************/
/* MIL custom-made header file*/
#include <mildyn.h>

/************************************************************************/
/* MIL low-level DTK prototypes */
#include <milfuncll.h>

/************************************************************************/
/* Make sure that M_MIL_USE_NT_WINDOWS is not defined (obsolete)        */
#ifdef M_MIL_USE_NT_WINDOWS
   #error M_MIL_USE_NT_WINDOWS is obsolete use M_MIL_USE_WINDOWS instead
#endif

/************************************************************************/
/* DistributedMIL path                                                  */
#define M_REMOTE_PATH            MIL_TEXT("remote:///")
#define M_IS_REMOTE_PATH(Path)   (MOs_strncmp((Path), \
                                              M_REMOTE_PATH, \
                                              sizeof(M_REMOTE_PATH) / sizeof(MIL_TEXT_CHAR) - 1) == 0)

#endif
