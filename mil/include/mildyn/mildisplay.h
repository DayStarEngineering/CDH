/************************************************************************/
/*
*
* Filename     :  MILDISPLAY.H
* Revision     :  9.02.0812
* Content      :  This file contains the defines necessary to use the
*                 Matrox Imaging Library display module
* Comments     :  
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2011.
* All Rights Reserved
*************************************************************************/

/************************************************************************/
/* MdispAlloc() for Windowed system                                     */
/************************************************************************/
#define M_MIL_DISPLAY_WND_CLASS_NAME MT("MIL Default Window")

// Maximum number of display that can be managed
#if (BW_COMPATIBILITY >= 0x090) && (BW_COMPATIBILITY <= 0x095)
#define M_MAX_VIDEO_DEVICE                            16L
#else
#define M_MAX_VIDEO_DEVICE                            64L
#endif

/* DispNum */
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
#define M_CRTC0                                       0x00010000L
#define M_CRTC1                                       0x00020000L
#define M_CRTC2                                       0x00030000L
#define M_CRTC3                                       0x00040000L
#define M_CRTC4                                       0x00050000L
#define M_CRTC5                                       0x00060000L
#define M_CRTC6                                       0x00070000L
#define M_CRTC_MASK                                   0x00070000L
#define M_CRTC_OFFSET                                 (16)
#define M_CRTC_INDEX(a)                               (((a&M_CRTC_MASK)>>M_CRTC_OFFSET)-1)
#define M_DEVICE_NUMBER(a)                            (a&0x0000003F)
#define M_DISPLAY_NUMBER(devindex,crtcindex)          (devindex|((crtcindex+1)<<M_CRTC_OFFSET))
#define M_CENTER                                      0x00000080L
/* display positions values */
#define M_LEFT                                        0x00000100L
#define M_RIGHT                                       0x00000200L
#define M_TOP                                         0x00000400L
#define M_BOTTOM                                      0x00000800L
#define M_MONITOR_BITS                                0x00000F80
#define M_MONITOR_POSITION(p)                         ((M_NULL == (p&(~M_MONITOR_BITS)))? (p&M_MONITOR_BITS): M_NULL)
#define M_DESKTOP_INDEX_FLAG                          0x01000000L
#define M_DESKTOP_INDEX(i)                            ((i >= 0) && (i&M_DESKTOP_INDEX_FLAG)? (i&(~M_DESKTOP_INDEX_FLAG)): M_INVALID)
#define M_MOUSE_RESTRICTED                            0x00000001L

/* Init Flag */
#define M_REMOTE_DISPLAY                              0x00000001L
#define M_ASYNC_CUSTOM                                0x00000002L              
#define M_DISPLAY_PROGRESSIVE                         0x00000004L
#define M_DISPLAY_INTERLACED                          0x00000008L
#define M_LOCAL_DISPLAY                               0x00000010L
#define M_USE_EXTERNAL_CLOCK                          0x00000020L
#define M_USE_INTERNAL_CLOCK                          0x00000040L
//#define  AVAILABLE                                  0x00000080L
#define M_GRAB_BASED                                  0x00000100L
#define M_NETWORK                                     0x00000200L
#define M_EXCLUSIVE                                   0x00000400L
//#define  AVAILABLE                                  0x00000800L
#define M_XDUAL_SCREEN                                0x00001000L
#define M_VIDEO_HD                                    0x00002000L
#define M_DUAL_SCREEN                                 0x00004000L
#define M_VIDEO_ENCODER                               0x00008000L
#define M_AUXILIARY                                   0x00010000L
#define M_DIRECTSHOW                                  0x00020000L
#define M_EXTERNAL                                    0x00040000L
#define M_VIDEO_HARDWARE_DEVICE                       0x00080000L
//#define  AVAILABLE                                  0x00100000L
#define M_IN_BUFFER_DISPLAY                           0x00200000L
#define M_DESKTOP_DESTRUCTIVE                         0x00400000L
//#define  AVAILABLE                                  0x00800000L
#define M_WINDOWED                                    0x01000000L
//#define  AVAILABLE                                  0x02000000L
//#define  AVAILABLE                                  0x04000000L
#define M_MIL_WINDOW                                  0x08000000L
#define M_USER_WINDOW                                 0x10000000L
#define M_GDI_OVERLAY                                 0x20000000L
#define M_DESKTOP_NON_DESTRUCTIVE                     0x40000000L
#define M_FULL_SCREEN                                 0x80000000L
#define M_DESKTOP                                     (M_DESKTOP_DESTRUCTIVE|M_DESKTOP_NON_DESTRUCTIVE)
#define M_ALL_INIT_FLAGS                              0xF967D71FL
#define M_DOCUMENTED_INIT_FLAGS                       (M_WINDOWED|M_AUXILIARY|M_DUAL_SCREEN|M_VIDEO_ENCODER|M_EXCLUSIVE)
#define M_DISPLAY_LOCATION                            (M_LOCAL_DISPLAY|M_REMOTE_DISPLAY)
#define M_IS_EXCLUSIVE(InitFlag)                      (InitFlag&M_EXCLUSIVE)     

#if ((BW_COMPATIBILITY >= 0x090) && (BW_COMPATIBILITY <= 0x095))
#define M_NON_WINDOWED                                0x02000000L
#endif
/************************************************************************/
/* MdispInquire() / MdispControl() Types                                */
/************************************************************************/
#define M_LOCAL_DISPLAY_CONTROL                       0X40000000L
#define M_REMOTE_DISPLAY_CONTROL                      0X20000000L
#define M_FORCED_LOCAL_DISPLAY_CONTROL                0x10000000L
#define M_FORCED_REMOTE_DISPLAY_CONTROL               0x08000000L
#define M_POST_CONTROL                                0x04000000L
#define M_IS_POST_CONTROL(X)                          (((X) != M_FILL_DISPLAY) && ((X)&M_POST_CONTROL))
#define M_IS_LOCAL_DISPLAY_CONTROL(X)                 (((X)&M_LOCAL_DISPLAY_CONTROL) || (M_IS_SHARED_LOCAL_CONTROL_TYPE(X)))
#define M_IS_REMOTE_DISPLAY_CONTROL(X)                (((X) != M_FILL_DISPLAY) && (((X)&M_REMOTE_DISPLAY_CONTROL) || (M_IS_SHARED_REMOTE_CONTROL_TYPE(X))))
#define M_ORIGINAL_DISPLAY_CONTROL(X)                 (((X) == M_FILL_DISPLAY) ? M_FILL_DISPLAY : (X)&~(M_LOCAL_DISPLAY_CONTROL|M_REMOTE_DISPLAY_CONTROL|M_FORCED_LOCAL_DISPLAY_CONTROL|M_FORCED_REMOTE_DISPLAY_CONTROL))
#define M_FORCE_ON_LOCAL_DISPLAY(X)                   ((X) | M_FORCED_LOCAL_DISPLAY_CONTROL)
#define M_FORCE_ON_REMOTE_DISPLAY(X)                  ((X) | M_FORCED_REMOTE_DISPLAY_CONTROL)
#define M_IS_FORCED_ON_LOCAL_DISPLAY(X)               (((X) != M_FILL_DISPLAY) && ((X) & M_FORCED_LOCAL_DISPLAY_CONTROL))
#define M_IS_FORCED_ON_REMOTE_DISPLAY(X)              (((X) != M_FILL_DISPLAY) && ((X) & M_FORCED_REMOTE_DISPLAY_CONTROL))
#define M_IS_SHARED_REMOTE_CONTROL_TYPE(X)            (((X) == M_OWNER_SYSTEM) ||       \
                                                       ((X) == M_SIZE_BAND) ||          \
                                                       ((X) == M_SIZE_BAND_LUT) ||      \
                                                       ((X) == M_SIZE_BIT) ||           \
                                                       ((X) == M_TYPE) ||               \
                                                       ((X) == M_ATTRIBUTE) ||          \
                                                       ((X) == M_SIGN) ||               \
                                                       ((X) == M_LUT_ID) ||             \
                                                       ((X) == M_ASSOCIATED_LUT) ||     \
                                                       ((X) == M_COMPRESSION_TYPE) ||   \
                                                       ((X) == M_MODIFICATION_COUNT) || \
                                                       ((X) == M_Q_FACTOR))

#define M_IS_SHARED_LOCAL_CONTROL_TYPE(X)             (((X) == M_FILTER) ||                           \
                                                       ((X) == M_FORMAT_SIZE) ||                      \
                                                       (((X) & ~M_CLIENT_ASCII_MODE) == M_FORMAT) ||  \
                                                       ((X) == M_SIZE_X) ||                           \
                                                       ((X) == M_SIZE_Y) ||                           \
                                                       ((X) == M_SIZE_Z) ||                           \
                                                       ((X) == M_NUMBER) ||                           \
                                                       ((X) == M_INIT_FLAG) ||                        \
                                                       ((X) == M_FILL_DISPLAY) ||                     \
                                                       ((X) == M_THREAD_PRIORITY) ||                  \
                                                       ((X) == M_WINDOW_RANGE) ||                     \
                                                       ((X) == M_FULL_SCREEN))

// Shared controls/inquires with other modules (not all listed)
#define M_SIZE_X                                      1536L // 0x600
#define M_SIZE_Y                                      1537L // 0x601
#define M_SIZE_Z                                      1538L // 0x602
#define M_SIZE_BAND                                   1005L
#define M_SIZE_BAND_LUT                               1006L
#define M_SIZE_BIT                                    1007L
#define M_TYPE                                        1008L
#define M_NUMBER                                      1009L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_FORMAT                                   (7701L|M_CLIENT_ASCII_MODE)   // Already defined in mil.h
#else
   #define M_FORMAT                                   7701L // Already defined in mil.h
#endif
#define M_FORMAT_SIZE                                 7731L // Already defined in mil.h
#define M_INIT_FLAG                                   1012L
#define M_ATTRIBUTE                                   1013L
#define M_SIGN                                        1014L
#define M_THREAD_PRIORITY                             1019L // Already defined in mil.h
#define M_NEED_UPDATE                                 (1020L + M_REMOTE_DISPLAY_CONTROL)
#define M_ENCODER_START                               (1025L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER                                     M_ENCODER_START
#define M_ENCODER_MODE                                (1026L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_TYPE                                (1027L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_SYNC_SOURCE                         (1028L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_SYNC                                M_ENCODER_SYNC_SOURCE
#define M_ENCODER_PEDESTAL                            (1029L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_FILTER                              (1030L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_RGB_SYNC                            (1031L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_INFO_MODE                           (1032L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_RESET                               (1033L + M_LOCAL_DISPLAY_CONTROL)   //1034 reseved
#define M_ENCODER_SELECT_FIELD_ODD                    (1037L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_SELECT_FIELD_EVEN                   (1038L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_CONTRAST                            (1039L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_BRIGHTNESS                          (1040L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_SATURATION                          (1041L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_HUE                                 (1042L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_OVR_SHOW                            (1043L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_OVR_LUT                             (1044L + M_LOCAL_DISPLAY_CONTROL)
#define M_ENCODER_OVR_BUF_ID                          (1045L + M_LOCAL_DISPLAY_CONTROL)
#define M_FILTER                                      1046L // Already defined in mil.h/miledge.h

#define M_ENCODER_STATE                               M_ENCODER
#define M_SYNC_TYPE                                   M_ENCODER_RGB_SYNC
#define M_ENCODER_SYNC_LOCK                           M_ENCODER_SYNC_SOURCE
#define M_ENCODER_SYNC_FIELDS                         (1047L + M_REMOTE_DISPLAY_CONTROL)
#define M_ENCODER_CLOCK                               (1048L + M_REMOTE_DISPLAY_CONTROL)
#define M_ENCODER_END                                 (1048L + M_REMOTE_DISPLAY_CONTROL)
#define M_Q_FACTOR                                    2564L    // Already defined in mil.h

/************************************************************************/
/* MdispInquire() Types MIL_ID range start                              */
/************************************************************************/

#define M_DISP_INQUIRE_MIL_ID_START                   1100L
// Inquire value with MIL_ID type must be in that range : 1100-1199
#define M_OWNER_SYSTEM                                1101L // Already define in mil.h
#define M_LUT_ID                                      1102L // Already define in mil.h
#define M_SELECTED                                    (1103L + M_REMOTE_DISPLAY_CONTROL)
#define M_OVERLAY_LUT                                 (1104L + M_REMOTE_DISPLAY_CONTROL)
#define M_WINDOW_BUF_ID                               (1105L + M_REMOTE_DISPLAY_CONTROL)
#define M_OVERLAY_ID                                  (1106L + M_REMOTE_DISPLAY_CONTROL)
#define M_ASSOCIATED_LUT                              1110L
#define M_AUXILIARY_BUF_ID                            (1115L + M_LOCAL_DISPLAY_CONTROL) // internal use only
#define M_BASIC_DISPLAY_BUFFER                        (1116L + M_LOCAL_DISPLAY_CONTROL) // internal use only
#define M_BUFFER_TO_RECYCLE                           1117L
#define M_COMPLEX_BUFFER                              1118L
#define M_MEGA_BUFFER_CHILD                           1119L
#define M_UNDERLAY_ID                                 (1120L + M_LOCAL_DISPLAY_CONTROL)
#define M_DISPLAY_SURFACE                             (1121L + M_LOCAL_DISPLAY_CONTROL)
#define M_PRIMARY_SURFACE_ID                          (1122L + M_REMOTE_DISPLAY_CONTROL)
#define M_USER_OVERLAY_ID                             (1123L + M_REMOTE_DISPLAY_CONTROL)
#define M_USER_BUFFER_SHARED_WITH_SCHEME              1124L
#define M_COMPRESSED_DISPLAY_SURFACE                  (1125L + M_REMOTE_DISPLAY_CONTROL)
#define M_ASYNCHRONOUS_DISPLAY_SURFACE                (1126L + M_REMOTE_DISPLAY_CONTROL)
#define M_DISP_INQUIRE_MIL_ID_END                     1199L


/************************************************************************/
/* MdispInquire() Types MIL_ID range end                                */
/************************************************************************/

#define M_PAN_X                                       (3000L + M_LOCAL_DISPLAY_CONTROL)
#define M_PAN_Y                                       (3001L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_X                                      (3002L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_Y                                      (3003L + M_LOCAL_DISPLAY_CONTROL)
#define M_HARDWARE_PAN                                (3004L + M_LOCAL_DISPLAY_CONTROL)
#define M_HARDWARE_ZOOM                               (3005L + M_LOCAL_DISPLAY_CONTROL)
#define M_KEY_MODE                                    (3007L + M_REMOTE_DISPLAY_CONTROL)
#define M_KEY_CONDITION                               (3008L + M_REMOTE_DISPLAY_CONTROL)
#define M_KEY_MASK                                    (3009L + M_REMOTE_DISPLAY_CONTROL)
#define M_KEY_SUPPORTED                               (3011L + M_REMOTE_DISPLAY_CONTROL)
#define M_VGA_BUF_ID                                  (3012L + M_LOCAL_DISPLAY_CONTROL)
#define M_TRANSPARENT_COLOR                           (0x01000060L + M_LOCAL_DISPLAY_CONTROL)
#define M_OVERLAY                                     (M_OVR + M_REMOTE_DISPLAY_CONTROL) // 0x00000080
#define M_INTERPOLATION_MODE                          (3018L + M_LOCAL_DISPLAY_CONTROL)
#define M_HOOK_OFFSET                                 3019L
#define M_FRAME_START_HANDLER_PTR                     3020L//needed for mil.dll? -applicationinfo
#define M_FRAME_START_HANDLER_USER_PTR                3021L//needed for mil.dll? -applicationinfo
#define M_OVERLAY_SHOW                                (3023L + M_REMOTE_DISPLAY_CONTROL)
#define M_DISPLAY_MODE                                (3029L + M_LOCAL_DISPLAY_CONTROL)
#define M_PIXEL_FORMAT                                (3032L + M_LOCAL_DISPLAY_CONTROL)
#define M_LUT_SUPPORTED                               (3033L + M_REMOTE_DISPLAY_CONTROL)
#define M_WINDOW_ZOOM                                 (3051L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_RESIZE                               (3052L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_OVERLAP                              (3053L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SCROLLBAR                            (3054L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_PROTECT_AREA                         (3056L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TITLE_BAR                            (3057L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MENU_BAR                             (3058L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TITLE_BAR_CHANGE                     (3059L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MENU_BAR_CHANGE                      (3060L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MOVE                                 (3061L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SYSBUTTON                            (3062L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MINBUTTON                            (3063L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MAXBUTTON                            (3064L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_PALETTE_NOCOLLAPSE                   (3069L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_RANGE                                3072L // Already defined in mil.h
#define M_TRANSFER_INTERPOLATION_MODE                 (3075L + M_LOCAL_DISPLAY_CONTROL)
//#define M_WINDOW_SNAP_Y                               (3076L + M_LOCAL_DISPLAY_CONTROL) obsolete - not documented anymore
#define M_WINDOW_UPDATE_ON_PAINT                      (3081L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_PAINT                                (3083L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_INITIAL_POSITION_X                   (3088L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_INITIAL_POSITION_Y                   (3089L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_HANDLE                               (3110L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_OFFSET_X                             (3111L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_OFFSET_Y                             (3112L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SIZE_X                               (3113L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SIZE_Y                               (3114L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_PAN_X                                (3115L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_PAN_Y                                (3116L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ZOOM_X                               (3117L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ZOOM_Y                               (3118L + M_LOCAL_DISPLAY_CONTROL)
#define M_INTERNAL_EXCLUSIVE_WINDOW_HANDLE            (3119L + M_LOCAL_DISPLAY_CONTROL)
#define M_SQA_EXCLUSIVE_WINDOW_HANDLE                 M_INTERNAL_EXCLUSIVE_WINDOW_HANDLE
#define M_WINDOW_TITLE_NAME                           M_TITLE
#define M_WINDOW_VISIBLE_OFFSET_X                     (3141L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_VISIBLE_OFFSET_Y                     (3142L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_VISIBLE_SIZE_X                       (3145L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_VISIBLE_SIZE_Y                       (3146L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ACTIVE                               (3149L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ENABLE                               (3150L + M_LOCAL_DISPLAY_CONTROL)
#define M_PALETTE_HANDLE                              (3151L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_THREAD_HANDLE                        (3152L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_THREAD_ID                            (3153L + M_LOCAL_DISPLAY_CONTROL)
#define M_KEYBOARD_USE                                (3155L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SYNC_UPDATE                          (3165L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TITLE_NAME_SIZE                      M_TITLE_SIZE
#define M_WINDOW_PAINT_MESSAGES                       (3172L + M_LOCAL_DISPLAY_CONTROL)
#define M_VIEW_MODE                                   (3182L + M_REMOTE_DISPLAY_CONTROL)
#define M_VIEW_BIT_SHIFT                              (3183L + M_REMOTE_DISPLAY_CONTROL)
#define M_NO_TEARING                                  (3188L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_MAX_X                                  (3190L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_MIN_X                                  (3191L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_MAX_Y                                  (3192L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_MIN_Y                                  (3193L + M_LOCAL_DISPLAY_CONTROL)
#define M_DUAL_ZOOM                                   (3197L + M_LOCAL_DISPLAY_CONTROL)
#define M_DUAL_ZOOM_SUPPORTED                         (3198L + M_LOCAL_DISPLAY_CONTROL)
#define M_UPDATE                                      (3199L + M_REMOTE_DISPLAY_CONTROL)
#define M_SYNCHRONOUS                                 0x00000001L
#define M_ASYNCHRONOUS                                0x00000002L
//      M_UPDATE + M_SYNCHRONOUS                      3200L
//      M_UPDATE + M_ASYNCHRONOUS                     3201L
#define M_WINDOW_VISIBLE                              (3202L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_SUBCLASSING_RESISTANT                (3205L + M_LOCAL_DISPLAY_CONTROL) // internal use only
#define M_AUXILIARY_KEEP_DISPLAY_ALIVE                (3207L + M_LOCAL_DISPLAY_CONTROL)
#define M_AUXILIARY_KEEP_UNDERLAY_ALIVE               (3211L + M_LOCAL_DISPLAY_CONTROL)
#define M_SELECT_VIDEO_SOURCE                         (3210L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TRANSPARENCY                         (3212L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TRANSPARENT_COLOR                    (3213L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ALPHA_BLENDING                       (3214L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ALPHA_VALUE                          (3215L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_LAYERED                              (3216L + M_LOCAL_DISPLAY_CONTROL)
#define M_RESTRICTED_MOUSE_ACTIVATED                  (3217L + M_LOCAL_DISPLAY_CONTROL)
#define M_INTERACTIVE_MODE                            (3218L + M_LOCAL_DISPLAY_CONTROL)
#define M_MOUSE_USE                                   (3219L + M_LOCAL_DISPLAY_CONTROL)
#define M_SOMEONE_HOOKED_TO_ANNOTATIONS_DRAW          (3220L + M_LOCAL_DISPLAY_CONTROL)
#define M_REGION_OUTSIDE_SHOW                         (3221L + M_REMOTE_DISPLAY_CONTROL)
#define M_REGION_INSIDE_SHOW                          (3222L + M_REMOTE_DISPLAY_CONTROL)
#define M_REGION_OUTSIDE_COLOR                        (3223L + M_REMOTE_DISPLAY_CONTROL)
#define M_REGION_INSIDE_COLOR                         (3224L + M_REMOTE_DISPLAY_CONTROL)
#define M_UNIFIED_ZOOM                                (3225L + M_LOCAL_DISPLAY_CONTROL)
#define M_ACTUAL_SIZE                                 (3226L + M_LOCAL_DISPLAY_CONTROL)
#define M_USE_DX_FULL_SCREEN_FOR_NO_TEARING           (3228L + M_LOCAL_DISPLAY_CONTROL)

/******************************************************************************/

#if OldDefinesSupport
#define M_KEY_COLOR                                   M_TRANSPARENT_COLOR
#define M_WINDOW_OVR_WRITE                            M_OVERLAY
#define M_WINDOW_OVR_BUF_ID                           M_OVERLAY_ID
#define M_WINDOW_OVR_SHOW                             M_OVERLAY_SHOW
#define M_WINDOW_OVR_LUT                              M_OVERLAY_LUT
#define M_WINDOW_UPDATE                               M_UPDATE
#define M_DISP_NUMBER                                 M_NUMBER
#define M_DISP_FORMAT                                 M_FORMAT
#define M_DISP_INIT_FLAG                              M_INIT_FLAG
#define M_DISP_PAN_X                                  M_PAN_X
#define M_DISP_PAN_Y                                  M_PAN_Y
#define M_DISP_ZOOM_X                                 M_ZOOM_X
#define M_DISP_ZOOM_Y                                 M_ZOOM_Y
#define M_DISP_HARDWARE_PAN                           M_HARDWARE_PAN
#define M_DISP_HARDWARE_ZOOM                          M_HARDWARE_ZOOM
#define M_DISP_KEY_MODE                               M_KEY_MODE
#define M_DISP_KEY_CONDITION                          M_KEY_CONDITION
#define M_DISP_KEY_MASK                               M_KEY_MASK
#define M_DISP_KEY_COLOR                              M_KEY_COLOR
#define M_DISP_MODE                                   M_DISPLAY_MODE
#define M_DISP_THREAD_PRIORITY                        M_THREAD_PRIORITY
#define M_DISP_INTERPOLATION_MODE                     M_INTERPOLATION_MODE
#define M_DISP_HOOK_OFFSET                            M_HOOK_OFFSET
#define M_DISP_KEY_SUPPORTED                          M_KEY_SUPPORTED
#define M_DISP_WINDOW_ZOOM                            M_WINDOW_ZOOM
#define M_DISP_WINDOW_RESIZE                          M_WINDOW_RESIZE
#define M_DISP_WINDOW_OVERLAP                         M_WINDOW_OVERLAP
#define M_DISP_WINDOW_SCROLLBAR                       M_WINDOW_SCROLLBAR
#define M_DISP_WINDOW_UPDATE                          M_WINDOW_UPDATE
#define M_DISP_WINDOW_PROTECT_AREA                    M_WINDOW_PROTECT_AREA
#define M_DISP_WINDOW_TITLE_BAR                       M_WINDOW_TITLE_BAR
#define M_DISP_WINDOW_MENU_BAR                        M_WINDOW_MENU_BAR
#define M_DISP_WINDOW_TITLE_BAR_CHANGE                M_WINDOW_TITLE_BAR_CHANGE
#define M_DISP_WINDOW_MENU_BAR_CHANGE                 M_WINDOW_MENU_BAR_CHANGE
#define M_DISP_WINDOW_MOVE                            M_WINDOW_MOVE
#define M_DISP_WINDOW_SYSBUTTON                       M_WINDOW_SYSBUTTON
#define M_DISP_WINDOW_MINBUTTON                       M_WINDOW_MINBUTTON
#define M_DISP_WINDOW_MAXBUTTON                       M_WINDOW_MAXBUTTON
#define M_DISP_WINDOW_PALETTE_NOCOLLAPSE              M_WINDOW_PALETTE_NOCOLLAPSE
#define M_DISP_WINDOW_UPDATE_WITH_MESSAGE             M_WINDOW_UPDATE_WITH_SEND_MESSAGE
#define M_DISP_WINDOW_PAINT                           M_WINDOW_PAINT
#define M_DISP_WINDOW_RANGE                           M_WINDOW_RANGE
#define M_DISP_WINDOW_HANDLE                          M_WINDOW_HANDLE
#define M_DISP_WINDOW_OFFSET_X                        M_WINDOW_OFFSET_X
#define M_DISP_WINDOW_OFFSET_Y                        M_WINDOW_OFFSET_Y
#define M_DISP_WINDOW_SIZE_X                          M_WINDOW_SIZE_X
#define M_DISP_WINDOW_SIZE_Y                          M_WINDOW_SIZE_Y
#define M_DISP_WINDOW_PAN_X                           M_WINDOW_PAN_X
#define M_DISP_WINDOW_PAN_Y                           M_WINDOW_PAN_Y
#define M_DISP_WINDOW_ZOOM_X                          M_WINDOW_ZOOM_X
#define M_DISP_WINDOW_ZOOM_Y                          M_WINDOW_ZOOM_Y
#define M_DISP_WINDOW_TITLE_NAME                      M_WINDOW_TITLE_NAME
#define M_DISP_VISIBLE_OFFSET_X                       M_WINDOW_VISIBLE_OFFSET_X
#define M_DISP_VISIBLE_OFFSET_Y                       M_WINDOW_VISIBLE_OFFSET_Y
#define M_DISP_VISIBLE_SIZE_X                         M_WINDOW_VISIBLE_SIZE_X
#define M_DISP_VISIBLE_SIZE_Y                         M_WINDOW_VISIBLE_SIZE_Y
#define M_VISIBLE_OFFSET_X                            M_WINDOW_VISIBLE_OFFSET_X
#define M_VISIBLE_OFFSET_Y                            M_WINDOW_VISIBLE_OFFSET_Y
#define M_VISIBLE_SIZE_X                              M_WINDOW_VISIBLE_SIZE_X
#define M_VISIBLE_SIZE_Y                              M_WINDOW_VISIBLE_SIZE_Y
#define M_DISP_WINDOW_ACTIVE                          M_WINDOW_ACTIVE
#define M_DISP_WINDOW_ENABLE                          M_WINDOW_ENABLE
#define M_DISP_PALETTE_HANDLE                         M_PALETTE_HANDLE
#define M_DISP_WINDOW_THREAD_HANDLE                   M_WINDOW_THREAD_HANDLE
#define M_DISP_WINDOW_THREAD_ID                       M_WINDOW_THREAD_ID
#define M_WINDOW_DIB_HEADER                           M_BITMAPINFO
#define M_WINDOW_UPDATE_WITH_SEND_MESSAGE             M_UPDATE_WITH_PAINT_MESSAGE
#define M_DDRAW_UNDERLAY_ID                           M_UNDERLAY_ID
#define M_DDRAW_UNDERLAY_SHOW                         M_UNDERLAY_SHOW
#if ((BW_COMPATIBILITY >= 0x90) && (BW_COMPATIBILITY<=0x95))
#define M_MAX_VGA_DEVICE                              16L
#else
#define M_MAX_VGA_DEVICE                              M_MAX_VIDEO_DEVICE
#endif
#define M_WINDOW_KEYBOARD_USE                         M_KEYBOARD_USE
#endif //OldDefinesSupport

// Display reserved area for Sys or Dev Inquire/Control
#define M_SYS_DISPLAY_START                           4501L
//M_IS_IN_DISPLAY_SYS_RANGE macro has a different definition in mil.h (in backward only)
#define M_IS_IN_DISPLAY_SYS_RANGE(X)     (((X>=M_SYS_DISPLAY_START) && (X<=M_SYS_DISPLAY_END)) || \
                                          ((X>=M_SYS_DISPLAY_RANGE2_START) && (X<=M_SYS_DISPLAY_RANGE2_END)) || \
                                          M_IS_IN_DISPLAY_APP_RANGE(X))
#define M_MAIN_DDRAW_OBJECT                           M_SYS_DISPLAY_START+0L     //4501
#define M_DIRECTX_OBJECT                              M_SYS_DISPLAY_START+1L     //4502
#define M_DDRAW_AVAILABLE                             M_SYS_DISPLAY_START+2L     //4503
#define M_DX_CAPS_STRUCT_SIZE                         M_SYS_DISPLAY_START+3L     //4504
#define M_DX_CAPS_STRUCT                              M_SYS_DISPLAY_START+4L     //4505
#define M_DX_DEVICE_IDENTIFIER_SIZE                   M_SYS_DISPLAY_START+5L     //4506
#define M_DX_DEVICE_IDENTIFIER                        M_SYS_DISPLAY_START+6L     //4507
#define M_PHYSICAL_ADDRESS_VGA                        M_SYS_DISPLAY_START+7L     //4508
#define M_PHYSICAL_SIZE_VGA                           M_SYS_DISPLAY_START+8L     //4509
#define M_PRIMARY_SURFACE_FORMAT                      M_SYS_DISPLAY_START+9L     //4510
#define M_PRIMARY_SURFACE_SIZE_BITS                   M_SYS_DISPLAY_START+10L    //4511
#define M_PRIMARY_SURFACE_SIZE_X                      M_SYS_DISPLAY_START+11L    //4512
#define M_PRIMARY_SURFACE_SIZE_Y                      M_SYS_DISPLAY_START+12L    //4513
#define M_PRIMARY_SURFACE_PITCH_BYTE                  M_SYS_DISPLAY_START+13L    //4514
#define M_PRIMARY_SURFACE_HOST_ADDRESS                M_SYS_DISPLAY_START+14L    //4515
#define M_PRIMARY_DDRAW_SURFACE                       M_SYS_DISPLAY_START+15L    //4516
#define M_UNDERLAY_SURFACE_AVAILABLE                  M_SYS_DISPLAY_START+16L    //4517
#define M_DUAL_SCREEN_MODE                            M_SYS_DISPLAY_START+17L    //4518
#define M_NB_MATROX_DISPLAY_OUTPUT                    M_SYS_DISPLAY_START+18L    //4519
#define M_WINDOWED_DISPLAY_AVAILABLE                  M_SYS_DISPLAY_START+19L    //4520
#define M_EXTERN_DISPLAY_AVAILABLE                    M_SYS_DISPLAY_START+20L    //4521
#define M_EXTERN_DISPLAY_OBJECT                       M_SYS_DISPLAY_START+21L    //4522
#define M_EXTERN_DISPLAY_API_MODULE                   M_SYS_DISPLAY_START+22L    //4523
#define M_EXTERN_DISPLAY_SUPPORTED_FORMAT             M_SYS_DISPLAY_START+23L    //4524
#define M_VSYNCH_DIRECTX_MAX_WAIT                     M_SYS_DISPLAY_START+24L    //4525
#define M_MEMORY_MANAGER                              M_SYS_DISPLAY_START+25L    //4526
#define M_UNDERLAY_LIVE_FORMAT_SUPPORTED              M_SYS_DISPLAY_START+26L    //4527
#define M_SYSTEM_GPU_ID                               M_SYS_DISPLAY_START+27L    //4528
#define M_UNDERLAY_FORMAT_SUPPORTED                   M_SYS_DISPLAY_START+28L    //4529
#define M_UNDERLAY_SUPPORTED                          M_SYS_DISPLAY_START+29L    //4530
#define M_UNDERLAY_ZOOM_MAX                           M_SYS_DISPLAY_START+30L    //4531
#define M_UNDERLAY_ZOOM_MIN                           M_SYS_DISPLAY_START+31L    //4532
#define M_IS_A_PARHELIA                               M_SYS_DISPLAY_START+32L    //4533

#define M_UNDERLAY_DOUBLE_RANGE_START                 M_SYS_DISPLAY_START+33L    //4534
#define M_UNDERLAY_ZOOM_X_MAX                         M_SYS_DISPLAY_START+33L    //4534
#define M_UNDERLAY_ZOOM_X_MIN                         M_SYS_DISPLAY_START+34L    //4535
#define M_UNDERLAY_ZOOM_Y_MAX                         M_SYS_DISPLAY_START+35L    //4536
#define M_UNDERLAY_ZOOM_Y_MIN                         M_SYS_DISPLAY_START+36L    //4537
#define M_UNDERLAY_LIVE_ZOOM_X_MAX                    M_SYS_DISPLAY_START+37L    //4538
#define M_UNDERLAY_LIVE_ZOOM_X_MIN                    M_SYS_DISPLAY_START+38L    //4539
#define M_UNDERLAY_LIVE_ZOOM_Y_MAX                    M_SYS_DISPLAY_START+39L    //4540
#define M_UNDERLAY_LIVE_ZOOM_Y_MIN                    M_SYS_DISPLAY_START+40L    //4541
#define M_UNDERLAY_DOUBLE_RANGE_END                   M_SYS_DISPLAY_START+40L    //4541

#define M_MTX0_TRANSFER_SUPPORTED                     M_SYS_DISPLAY_START+41L    //4542
#define M_MTX0_CAPS                                   M_SYS_DISPLAY_START+42L    //4543
#define M_IS_IN_10_BITS_MODE                          M_SYS_DISPLAY_START+43L    //4544
#define M_IS_IN_10_BITS_COLOR_MODE                    M_SYS_DISPLAY_START+44L    //4545
#define M_IS_IN_10_BITS_GRAYSCALE_MODE                M_SYS_DISPLAY_START+45L    //4546
#define M_CAN_OFFSET_IN_UNDERLAY_LIVE                 M_SYS_DISPLAY_START+46L    //4547
#define M_DISPLAY_NUM                                 M_SYS_DISPLAY_START+47L    //4548
#define M_VENDOR_ID                                   M_SYS_DISPLAY_START+48L    //4549
#define M_DEVICE_ID                                   M_SYS_DISPLAY_START+49L    //4550
#define M_VGA_INFO_OBJECT                             M_SYS_DISPLAY_START+50L    //4551 Obsolete
#define M_SYSTEM_INDEX_OF_VGA                         M_MATROX_VGA_BOARD_INDEX

#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL) 
#define M_SUPPORTED_DISPLAY_TYPE_STRING				   M_SYS_DISPLAY_START+52L+M_CLIENT_ASCII_MODE    //4553
#else
#define M_SUPPORTED_DISPLAY_TYPE_STRING		         M_SYS_DISPLAY_START+52L    //4553
#endif
#define M_SUPPORTED_DISPLAY_TYPE_STRING_SIZE          M_SYS_DISPLAY_START+53L    //4554
#define M_NEED_LOCK_UNLOCK                            M_SYS_DISPLAY_START+54L    //4555
#define M_EXTERN_UNDERLAY_AVAILABLE                   M_SYS_DISPLAY_START+55L    //4556
#define M_CAN_ALLOCATE_VIDEO_MEMORY                   M_SYS_DISPLAY_START+56L    //4557
#define M_PHYSICAL_WRITE_COMBINING_NEEDED             M_SYS_DISPLAY_START+57L    //4558
#define M_EXTERN_DISPLAY_API_CLASS                    M_SYS_DISPLAY_START+58L    //4559
#define M_REFRESH_RATE                                M_SYS_DISPLAY_START+59L    //4560
#define M_VGA_BOARD_INDEX                             M_SYS_DISPLAY_START+60L    //4561
#define M_MATROX_VGA_BOARD_INDEX                      M_SYS_DISPLAY_START+61L    //4562
#define M_VGA_CRTC_INDEX                              M_SYS_DISPLAY_START+62L    //4563
#define M_RESOLUTION_CHANGED                          M_SYS_DISPLAY_START+63L    //4564
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL) 
#define M_VIDEO_DEVICE_DESCRIPTION_STRING             M_SYS_DISPLAY_START+64L+M_CLIENT_ASCII_MODE    //4565
#else
#define M_VIDEO_DEVICE_DESCRIPTION_STRING             M_SYS_DISPLAY_START+64L    //4565
#endif
#define M_VIDEO_DEVICE_DESCRIPTION_STRING_SIZE        M_SYS_DISPLAY_START+65L    //4566
#define M_SUB_SYSTEM_ID                               M_SYS_DISPLAY_START+66L    //4567
#define M_VIDEO_DEVICE_DRIVER_VERSION_PRODUCT         M_SYS_DISPLAY_START+67L    //4568
#define M_VIDEO_DEVICE_DRIVER_VERSION_VERSION         M_SYS_DISPLAY_START+68L    //4569
#define M_VIDEO_DEVICE_DRIVER_VERSION_SUB_VERSION     M_SYS_DISPLAY_START+69L    //4570
#define M_VIDEO_DEVICE_DRIVER_VERSION_BUILD           M_SYS_DISPLAY_START+70L    //4571
#define M_VIDEO_BUFFER_MAX_SIZE_X                     M_SYS_DISPLAY_START+71L    //4572
#define M_VIDEO_BUFFER_MAX_SIZE_Y                     M_SYS_DISPLAY_START+72L    //4573
#define M_SIGNAL_DEVICE_LOST                          M_SYS_DISPLAY_START+73L    //4574
#define M_CHECK_DEVICE_LOST                           M_SYS_DISPLAY_START+74L    //4575
#define M_CAN_ALLOCATE_MONO8_IN_VIDEO_MEMORY          M_SYS_DISPLAY_START+75L    //4576
#define M_NON_LOCAL_MEMORY_SUPPORTED                  M_SYS_DISPLAY_START+76L    //4577
#define M_D3D_AVAILABLE                               M_SYS_DISPLAY_START+77L    //4578
#define M_MAIN_D3D9_OBJECT                            M_SYS_DISPLAY_START+78L    //4579
#define M_PART_OF_DESKTOP                             M_SYS_DISPLAY_START+79L    //4580
#define M_DEVICE_LOST_THREAD_PRIORITY                 M_SYS_DISPLAY_START+80L    //4581
#define M_DEVICE_LOST_THREAD_SLEEP                    M_SYS_DISPLAY_START+81L    //4582
#define M_CHECK_DEVICE_LOST_THREAD_PRIORITY           M_SYS_DISPLAY_START+82L    //4583
#define M_CHECK_DEVICE_LOST_THREAD_SLEEP              M_SYS_DISPLAY_START+83L    //4584
#define M_XVIDEO_AVAILABLE                            M_SYS_DISPLAY_START+84L    //4585
#define M_XVIDEO_FORMAT_SUPPORTED                     M_SYS_DISPLAY_START+85L    //4586
#define M_XVIDEO_AUTOPAINT_SUPPORTED                  M_SYS_DISPLAY_START+86L    //4587
#define M_XDUAL_SCREEN_SUPPORT                        M_SYS_DISPLAY_START+87L    //4588
#define M_XDGA_OBJECT                                 M_SYS_DISPLAY_START+88L    //4589
#define M_XSCREEN_INDEX                               M_SYS_DISPLAY_START+89L    //4590
#define M_XINERAMA_SCREEN_INDEX                       M_SYS_DISPLAY_START+90L    //4591
#define M_INFORMATION_CRITICAL_SECTION                M_SYS_DISPLAY_START+91L    //4592
#define M_IS_LOST                                     M_SYS_DISPLAY_START+92L    //4593
#define M_UNIQUE_ID                                   M_SYS_DISPLAY_START+93L    //4594
#define M_CAN_ALLOCATE_CONTIGUOUS_VIDEO_MEMORY        M_SYS_DISPLAY_START+94L    //4595
#define M_REVISION                                    M_SYS_DISPLAY_START+95L    //4596
#define M_XVMIL_ADAPTOR_PRESENT                       M_SYS_DISPLAY_START+96L    //4597

#define M_SYS_BUFFER_HANDLER_START                    M_SYS_DISPLAY_START+96L       // 4597
#define M_REGISTER_EXTERN_BUFFER_API_MODULE           M_SYS_BUFFER_HANDLER_START+0L // 4598
#define M_UNREGISTER_EXTERN_BUFFER_API_MODULE         M_SYS_BUFFER_HANDLER_START+1L // 4599
#define M_SYS_BUFFER_HANDLER_END                      M_SYS_DISPLAY_START+99L       // 4600
#define M_IS_IN_BUFFER_HANDLER_SYS_RANGE(X)     ((X>=M_SYS_BUFFER_HANDLER_START) && (X<=M_SYS_BUFFER_HANDLER_END))
////////////// MAXIMUM FOR THE FIRST DISPLAY RANGE /////////+99L    //4600
#define M_SYS_DISPLAY_END                             4600L

#define M_COMPRESSION_TYPE                            5045L // already defined in mil.h
#define M_GRAB_BUFFERS                                5095L // internal use only
#define M_GRAB_BUFFERS_NO_LOCK                        5096L // internal use only
#define M_NUMBER_OF_GRAB_IN_PROGRESS                  5097L

// Display reserved area for AppInquire/Control
/*Reserve values between M_APP_DISPLAY_START and M_APP_DISPLAY_END*/
#define M_APP_DISPLAY_START                          (M_APP_INQUIRE_SYS_START+300L)

// Value reserved for AppInquire/AppControl to the hardware manager (300 to 349)
#define M_APP_HM_DISPLAY_START                        M_APP_DISPLAY_START
#define M_MTX0_CAPABLE_DIRECTX_OBJECT                (M_APP_HM_DISPLAY_START+0L)      // 300
#define M_MTX0_CAPABLE_DIRECTX_OBJECT_COUNT          (M_APP_HM_DISPLAY_START+1L)      // 301
#define M_SYSTEM_ASSOCIATED_TO_DX_OBJECT             (M_APP_HM_DISPLAY_START+2L)      // 302
#define M_CLIENT_TO_MONITOR_RECT                     (M_APP_HM_DISPLAY_START+3L)      // 303
#if ((BW_COMPATIBILITY >= 0x090) && (BW_COMPATIBILITY <= 0x095))
#define M_VGA_DEVICE_SYSTEM                          (M_APP_HM_DISPLAY_START+4L)      // 304 to 319
//5L to 19L reserved for M_VGA_DEVICE_SYSTEM
#endif
#define M_DUAL_HEAD                                  (M_APP_HM_DISPLAY_START+20L)     // 320
#define M_MULTI_MONITOR                              (M_APP_HM_DISPLAY_START+21L)     // 321
#define M_NB_OF_VIDEO_DEVICE                         (M_APP_HM_DISPLAY_START+22L)     // 322
#define M_NB_OF_VGA_DEVICE                           M_NB_OF_VIDEO_DEVICE
#define M_VGA_SYSTEM_FROM_PHYSICAL_ADDRESS           (M_APP_HM_DISPLAY_START+23L)     // 323
#define M_USE_UNDERLAY_IN_ALL_DISPLAY                (M_APP_HM_DISPLAY_START+24L)     // 324
#define M_USE_DDRAW_UNDERLAY                         M_USE_UNDERLAY_IN_ALL_DISPLAY
#define M_DESKTOP_SIZE_BIT                           (M_APP_HM_DISPLAY_START+25L)     // 325
#define M_DESKTOP_FORMAT                             (M_APP_HM_DISPLAY_START+26L)     // 326
#define M_RESET_CRTC                                 (M_APP_HM_DISPLAY_START+27L)     // 327
#define M_CHECK_ALL_DEVICE_LOST                      (M_APP_HM_DISPLAY_START+28L)     // 328
#define M_NB_OF_DESKTOP_VGA_DEVICE                   (M_APP_HM_DISPLAY_START+29L)     // 329
#define M_IS_ONE_DISPLAY_8_BITS                      (M_APP_HM_DISPLAY_START+30L)     // 330
#define M_IS_ONE_DISPLAY_16_BITS                     (M_APP_HM_DISPLAY_START+31L)     // 331
#define M_IS_ONE_DISPLAY_24_BITS                     (M_APP_HM_DISPLAY_START+32L)     // 332
#define M_IS_ONE_DISPLAY_32_BITS                     (M_APP_HM_DISPLAY_START+33L)     // 333
#define M_IS_ONE_DISPLAY_15_BITS                     (M_APP_HM_DISPLAY_START+34L)     // 334
#define M_EXTERNAL_DISPLAY_NUMBER                    (M_APP_HM_DISPLAY_START+35L)     // 335
#define M_NEW_VIDEO_DEVICE_INDEX                     (M_APP_HM_DISPLAY_START+36L)     // 336
#define M_VIDEO_DEVICE_INDEX_FROM_DX_OBJ             (M_APP_HM_DISPLAY_START+37L)     // 337
#define M_NB_OF_PCI_VIDEO_DEVICE                     (M_APP_HM_DISPLAY_START+38L)     // 338
#define M_USE_BASIC_VGA_INFO                         (M_APP_HM_DISPLAY_START+39L)     // 339
#define M_FIRST_VIDEO_DEVICE_ON_DESKTOP              (M_APP_HM_DISPLAY_START+40L)     // 340
#define M_CONFIG_CHANGE_THREAD_PRIORITY              (M_APP_HM_DISPLAY_START+41L)     // 341
#define M_UPDATE_CONFIGURATION                       (M_APP_HM_DISPLAY_START+42L)     // 342
#define M_ENUM_PCI_VIDDEV_MEMORY_RANGE               (M_APP_HM_DISPLAY_START+43L)     // 343
#define M_BEST_DESKTOP_FORMAT                        (M_APP_HM_DISPLAY_START+44L)     // 344
#define M_GENERATE_CAPS_FILE                         (M_APP_HM_DISPLAY_START+45L)     // 345
#define M_MONITORS_RECTS_LIST                        (M_APP_HM_DISPLAY_START+46L)     // 346
#define M_DELETE_VIDEO_DEVICE_INDEX                  (M_APP_HM_DISPLAY_START+47L)     // 347
#define M_MED_SERIES_IS_PRESENT                      (M_APP_HM_DISPLAY_START+48L)     // 348
#define M_APP_HM_DISPLAY_END                         (M_APP_HM_DISPLAY_START+49L)
// available                                          M_APP_HM_DISPLAY_END            // 349
// Value reserved for AppInquire/AppControl to the DirectX display wrapper (350 to 374)
#define M_APP_DX_DISPLAY_START                       M_APP_HM_DISPLAY_END+1L
//#define M_DIRECTX_VERSION                            M_APP_DX_DISPLAY_START+0L         // 350
#define M_DIRECTX_CAN_CREATE_OVER_HOST_MEMORY        M_APP_DX_DISPLAY_START+1L         // 351
#define M_MTX0_SERVICE                               M_APP_DX_DISPLAY_START+2L         // 352
#define M_DIRECTX_VIDEO_BUFFER_MAPPABLE              M_APP_DX_DISPLAY_START+3L         // 353
#define M_KEEP_POLLING_ON_MODE_CHANGED               M_APP_DX_DISPLAY_START+4L         // 354
#define M_APP_DX_DISPLAY_END                         M_APP_DX_DISPLAY_START+24L        // 374
// General purpose AppInquire/AppControl for MilDisplay (375 to 399)
#define M_APP_GENERAL_DISPLAY_START                  (M_APP_DX_DISPLAY_END+1L)         // 375
#define M_CAN_ALLOC_MTX0                             (M_APP_GENERAL_DISPLAY_START+0L)  // 375
#define M_DISPLAY_CONTROL_PANEL                      (M_APP_GENERAL_DISPLAY_START+1L)  // 376
#define M_DISPLAY_BUF_TRANSFER_SUPPORTED_FUNCTIONS   (M_APP_GENERAL_DISPLAY_START+2L)  // 377
#define M_DISPLAY_NUMBER_ALLOCATED                   (M_APP_GENERAL_DISPLAY_START+3L)  // 378
#define M_DEFAULT_3BITS_3BANDS_DISP_BUFFER_FORMAT    (M_APP_GENERAL_DISPLAY_START+4L)  // 379
#define M_LOCK_ALL_DISPLAYS                          (M_APP_GENERAL_DISPLAY_START+5L)  // 380
#define M_DIRECTX_VERSION                            (M_APP_GENERAL_DISPLAY_START+6L)  // 381

#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL) //Within ASCII client apps
   #define M_TRACE_INFORMATION                    M_TRACE_ASCII_INFORMATION
#else //Inside MIL and in Backward
   #define M_TRACE_INFORMATION                    (M_APP_GENERAL_DISPLAY_START+6L)  // 381
#endif

#define M_PAUSE_TRACES                               (M_APP_GENERAL_DISPLAY_START+7L)  // 382
#define M_TRACE_ENABLED                              (M_APP_GENERAL_DISPLAY_START+8L)  // 383
#define M_DISPLAY_DUMP                               M_TRACE_ENABLED
#define M_TRY_LOCK_ALL_DISPLAYS                      (M_APP_GENERAL_DISPLAY_START+9L)  // 384
#define M_KILL_SCHEME                                (M_APP_GENERAL_DISPLAY_START+10L) // 385
#define M_DISP_BUFFER_NUMBER_ALLOCATED               (M_APP_GENERAL_DISPLAY_START+11L) // 386
#define M_READY_TO_BE_FREED                          (M_APP_GENERAL_DISPLAY_START+12L) // 387
#define M_NUMBER_OF_DISPLAY_SCHEME                   (M_APP_GENERAL_DISPLAY_START+13L) // 388
#define M_DISPLAY_SCHEME_ID_LIST                     (M_APP_GENERAL_DISPLAY_START+14L) // 389
#define M_USER_TRACE_TEXT                            (M_APP_GENERAL_DISPLAY_START+15L) // 390
#define M_USER_TRACE_VALUE                           (M_APP_GENERAL_DISPLAY_START+16L) // 391
#define M_RESUSCITATE_SCHEME                         (M_APP_GENERAL_DISPLAY_START+17L) // 392
#define M_NB_EXTERN_BUFFER_API_MODULE                (M_APP_GENERAL_DISPLAY_START+18L) // 393
#define M_WANT_TO_HANDLE_AUXILIARY_UPDATE            (M_APP_GENERAL_DISPLAY_START+19L) // 394
#define M_NEW_VIDEO_DEVICE_ADDED                     (M_APP_GENERAL_DISPLAY_START+20L) // 395
#define M_FLUSH_CTRACES                              (M_APP_GENERAL_DISPLAY_START+21L) // 396
#define M_START_CTRACES                               M_TRACE_ENABLED
#define M_STOP_CTRACES                                M_TRACE_ENABLED
#define M_PAUSE_CTRACES                               M_PAUSE_TRACES
#define M_TRACE_ASCII_INFORMATION                    (M_APP_GENERAL_DISPLAY_START+22L) // 397
#define M_CAN_ALLOC_NON_PAGED_IN_VIDEO_MEMORY        (M_APP_GENERAL_DISPLAY_START+23L) // 398
#define M_DESKTOP_COMPOSITION                        (M_APP_GENERAL_DISPLAY_START+24L) // 399
#define M_DESKTOP_INTERACTIVE                        (M_APP_GENERAL_DISPLAY_START+25L) // 400
#define M_XORG_ACCELERATION                          (M_APP_GENERAL_DISPLAY_START+26L) // 401
#define M_EXCLUSIVE_ON_LAST_MONITOR                  (M_APP_GENERAL_DISPLAY_START+27L) // 405
#define M_MILDISPLAY_DLL_IN_DEBUG_MODE               (M_APP_GENERAL_DISPLAY_START+28L) // 406

// End of reserved value for display
#define M_APP_DISPLAY_END                            (M_APP_INQUIRE_SYS_START+450L)
#define M_IS_IN_DISPLAY_APP_HM_RANGE(X)              (((X>=M_APP_HM_DISPLAY_START) && (X<=M_APP_HM_DISPLAY_END))   || \
                                                      ((X>=M_APP_HM_DISPLAY_START2) && (X<=M_APP_HM_DISPLAY_END2)) || \
                                                      ((X>=M_APP_HM_DISPLAY_START3) && (X<=M_APP_HM_DISPLAY_END3)))
#define M_IS_IN_DISPLAY_APP_DX_RANGE(X)              ((X>=M_APP_DX_DISPLAY_START) && (X<=M_APP_DX_DISPLAY_END))
#define M_IS_IN_DISPLAY_APP_RANGE(X)                 (((X>=M_APP_DISPLAY_START) && (X<=M_APP_DISPLAY_END))         || \
                                                      ((X>=M_APP_HM_DISPLAY_START3) && (X<=M_APP_HM_DISPLAY_END3)))


#define M_DISP_INQUIRE_SIZEOF_DOUBLE_START            6600L
// Inquire value with a size of double, must be in that range : 6600-6699
#define M_SCALE_X                                     (6601L + M_LOCAL_DISPLAY_CONTROL)
#define M_SCALE_Y                                     (6602L + M_LOCAL_DISPLAY_CONTROL)
#define M_PAN_OFFSET_X                                (6603L + M_LOCAL_DISPLAY_CONTROL)
#define M_PAN_OFFSET_Y                                (6604L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_FACTOR_X                               (6605L + M_LOCAL_DISPLAY_CONTROL)
#define M_ZOOM_FACTOR_Y                               (6606L + M_LOCAL_DISPLAY_CONTROL)
#define M_REAL_ZOOM_FACTOR_X                          (6607L + M_LOCAL_DISPLAY_CONTROL)
#define M_REAL_ZOOM_FACTOR_Y                          (6608L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MAXIMUM_ZOOM_FACTOR                  (6609L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_MINIMUM_ZOOM_FACTOR                  (6610L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ZOOM_FACTOR_X                        (6611L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_ZOOM_FACTOR_Y                        (6612L + M_LOCAL_DISPLAY_CONTROL)
#define M_UPDATE_RATE                                 (6613L + M_LOCAL_DISPLAY_CONTROL)
#define M_REAL_OFFSET_X                               (6614L + M_LOCAL_DISPLAY_CONTROL)
#define M_REAL_OFFSET_Y                               (6615L + M_LOCAL_DISPLAY_CONTROL)
#define M_DISP_INQUIRE_SIZEOF_DOUBLE_END              6699L


#define M_DISP_INQUIRE_SIZEOF_INT64_START             6700L
// Inquire value with a size of 64 bit, must be in that range : 6700-6799
#define M_EXTENDED_DISPLAY_SCHEME                     ((M_DISP_INQUIRE_SIZEOF_INT64_START+0L) + M_LOCAL_DISPLAY_CONTROL)  //6700
#define M_DISP_INQUIRE_SIZEOF_INT64_END               6799L

#define M_DISP_INQUIRE_UNKNOWN_SIZEOF_START           6800L
// Inquire value with unknown size of,
//            and require a user array, must be in that range : 6800-6899
#define M_DISP_INQUIRE_UNKNOWN_SIZEOF_END             6899L


#define M_INQUIRE_STRING_SIZE_OFFSET                  30L
#define M_DISP_INQUIRE_STRING_START                   7700L
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
   #define M_FORMAT                                   (7701L|M_CLIENT_ASCII_MODE)   // Already defined in mil.h, considered as a shared control
   #define M_TITLE                                    ((7702L|M_CLIENT_ASCII_MODE) + M_LOCAL_DISPLAY_CONTROL)
   #define M_WINDOW_TITLE_NAME                        M_TITLE
   /*Reserve next values      from                    ((M_DISP_INQUIRE_STRING_START+2L)|M_CLIENT_ASCII_MODE)  //7703 */
   /*                         to                      ((M_DISP_INQUIRE_STRING_START+29L)|M_CLIENT_ASCII_MODE) //7729 */
#else
   #define M_FORMAT                                   7701L // Already defined in mil.h, considered as a shared control
   #define M_TITLE                                    (7702L + M_LOCAL_DISPLAY_CONTROL)
   #define M_WINDOW_TITLE_NAME                        M_TITLE
   /*Reserve next values      from                    (M_DISP_INQUIRE_STRING_START+2L)  //7702 */
   /*                         to                      (M_DISP_INQUIRE_STRING_START+29L) //7729 */
#endif
#define M_DISP_INQUIRE_STRING_END                     (M_DISP_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET-1) //7729L


// 7730-7759 string size offsets
// Use M_INQUIRE_STRING_SIZE_OFFSET + inquire type
#define M_FORMAT_SIZE                                 7731L // Already defined in mil.h, considered as a shared control
#define M_TITLE_SIZE                                  (7732L + M_LOCAL_DISPLAY_CONTROL)
#define M_WINDOW_TITLE_NAME_SIZE                      M_TITLE_SIZE
/*Reserve next values      from                       (M_DISP_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+2)  //7732L */
/*                         to                         (M_DISP_INQUIRE_STRING_START+M_INQUIRE_STRING_SIZE_OFFSET+29) //7759L */

// MdispControl(M_REMAP_TYPE)
#define M_MULTI_BYTES                                    1L
#define M_AUTO_SCALE                                     2L
#define M_BIT_SHIFT                                      3L
#define M_LOGARITHMIC                                    4L
#define M_PIXEL_VALUES                                   5L
#define M_OPAQUE                                         0x01000058L
#define M_TRANSPARENT                                    0x01000059L
#define M_MED_SERIES                                     6L

//Pseudo-ID to apply a control on all displays
#define M_ALL_DISPLAYS                                (M_PSEUDO_ID+3)

// Value to represent all scheme id. Used with M_RESUSCITATE_SCHEME control
#define M_ALL_DISPLAY_SCHEMES                         (0x80000000)

//Second range that is reseved for Display Sys or Dev Inquire/Control
/* Reserve next values     from    M_SYS_DISPLAY_RANGE2_START    8500L 
                           to      M_SYS_DISPLAY_RANGE2_END      8699L */
#define M_SYS_DISPLAY_RANGE2_START                    8500L 
#define M_D3D_SUPPORTED_NO_TEARING_MODE               8501L
#define M_RESET_D3D_DEVICE                            8502L
#define M_RELEASE_D3D_DEVICE                          8503L
#define M_CAN_ALLOCATE_CONTIGUOUS_VIDEO_MEMORY_WITH_LOCK 8504L
#define M_NO_TEARING_DEVICE                           8505L
#define M_NO_TEARING_ACTIVE_DEVICE                    8506L
#define M_VGA_INFO_DISPLAY_RECT                       8507L
#define M_VGA_INFO_DISPLAY_FORMAT                     8508L
#define M_VGA_INFO_DISPLAY_DEPTH                      8509L
#define M_VGA_INFO_DISPLAY_DEVICE_NAME                8510L
#define M_VGA_INFO_DISPLAY_DEVICE_NAME_SIZE           8511L
#define M_CURRENT_MONITOR_RECT                        8512L
#define M_CURRENT_MONITOR_WORK_RECT                   8513L
#define M_IS_EXTERNAL_DISPLAY                         8514L
#define M_BOARD_PART_OF_DESKTOP                       8515L
#define M_IS_66_MHZ_CAPABLE                           8516L
#define M_REALLOC_D3D_DEVICE                          8517L
#define M_IS_PCIX_OR_LESS                             8518L
#define M_MAIN_D3D10_OBJECT                           8519L
//8520L to 8529L reserved for M_APP_HM_DISPLAY_START2
#define M_APP_HM_DISPLAY_START2                       8520L
#define M_PHYS_SHOW_TASKBAR                           8521L
#define M_BEST_EXCLUSIVE_MONITOR                      8522L
#define M_BEST_DESKTOP_MONITOR                        8523L
#define M_BEST_DESKTOP_RECT                           8524L
#define M_NB_OF_GRAPHIC_ADAPTER                       8525L
#define M_APP_HM_DISPLAY_END2                         8529L
#define M_D3D_CREATE_SWAP_CHAIN                       8530L
#define M_D3D_RELEASE_SWAP_CHAIN                      8531L
#define M_D3D_RESIZE_SWAP_CHAIN                       8532L
#define M_IS_EXCLUSIVE_MONITOR_AVAILABLE              8533L
#define M_DESKTOP_RESOLUTION                          8534L
#define M_DESKTOP_DEVICE_NAME                         8535L
#define M_DESKTOP_DEVICE_NAME_SIZE                    8536L
#define M_IS_VIRTUAL_DEVICE                           8537L
#define M_VIDEO_DEVICE_IS_ORION_HD                    8538L
#define M_MAIN_D3D11_OBJECT                           8539L
#define M_TEST_DESKTOP_RESOLUTION                     8541L
#define M_PERMANENT_DESKTOP_RESOLUTION                8542L
#define M_D3D_NO_TEARING                              8543L
#define M_NO_TEARING_DEVICE_FULL_SCREEN               8544L
#define M_D3D11_DEVICE_LOCK                           8545L
#define M_ALLOW_NONPAGED_BUFFERS_IN_VIDEO_MEMORY      8548L

#define M_APP_HM_DISPLAY_START3                       8600L
#if !((BW_COMPATIBILITY >= 0x090) && (BW_COMPATIBILITY <= 0x095))
#define M_VGA_DEVICE_SYSTEM                          (M_APP_HM_DISPLAY_START3)      // 8600 to 8663
//8600L to 8663L reserved for M_VGA_DEVICE_SYSTEM
#endif
#define M_GPU_NO_TEARING_AVAILABLE                    8664
#define M_GPU_BILINEAR_SUPPORTED                      8665

////////////// MAXIMUM FOR THE SECOND DISPLAY RANGE //////   8699L
#define M_SYS_DISPLAY_RANGE2_END                      8699L
#define M_APP_HM_DISPLAY_END3                         M_SYS_DISPLAY_RANGE2_END

#define M_DIB_HANDLE                                  M_BUF_DISPLAY_START+31L // 9031

//Reserved values for DispControl
#define M_DISP_CONTROL_START                          10000L
#define M_NO_TEARING_SKIP_MODE                        ((M_DISP_CONTROL_START+1L) + M_LOCAL_DISPLAY_CONTROL)    // 10001
#define M_NO_SKIP                                     ((M_DISP_CONTROL_START+2L) + M_LOCAL_DISPLAY_CONTROL)    // 10002
#define M_SKIP_OLDEST                                 ((M_DISP_CONTROL_START+3L) + M_LOCAL_DISPLAY_CONTROL)    // 10003
#define M_SKIP_NEWEST                                 ((M_DISP_CONTROL_START+4L) + M_LOCAL_DISPLAY_CONTROL)    // 10004
#define M_DISPLAY_SCHEME                              ((M_DISP_CONTROL_START+5L) + M_LOCAL_DISPLAY_CONTROL)    // 10005
#define M_OVERLAY_CLEAR                               ((M_DISP_CONTROL_START+6L) + M_REMOTE_DISPLAY_CONTROL)    // 10006
#define M_FORCE_MONO_OVR                              ((M_DISP_CONTROL_START+7L) + M_REMOTE_DISPLAY_CONTROL)    // 10007
#define M_D3D_VSYNC_INTERVAL_ONE                      ((M_DISP_CONTROL_START+8L) + M_LOCAL_DISPLAY_CONTROL)    // 10008
#define M_D3D_VSYNC_INTERVAL_TWO                      ((M_DISP_CONTROL_START+9L) + M_LOCAL_DISPLAY_CONTROL)    // 10009
#define M_D3D_VSYNC_INTERVAL_THREE                    ((M_DISP_CONTROL_START+10L) + M_LOCAL_DISPLAY_CONTROL)   // 10010
#define M_D3D_VSYNC_INTERVAL_FOUR                     ((M_DISP_CONTROL_START+11L) + M_LOCAL_DISPLAY_CONTROL)   // 10011
#define M_VGA_INDEX                                   ((M_DISP_CONTROL_START+12L) + M_LOCAL_DISPLAY_CONTROL)   // 10012
#define M_GDI_COMPATIBLE_OVERLAY                      ((M_DISP_CONTROL_START+13L) + M_REMOTE_DISPLAY_CONTROL)  // 10013
#define M_HSCROLL_VISIBLE                             ((M_DISP_CONTROL_START+14L) + M_LOCAL_DISPLAY_CONTROL)   // 10014
#define M_VSCROLL_VISIBLE                             ((M_DISP_CONTROL_START+15L) + M_LOCAL_DISPLAY_CONTROL)   // 10015
#define M_SRC_UPDATE_REGION_OFFSET_X                  ((M_DISP_CONTROL_START+16L) + M_LOCAL_DISPLAY_CONTROL)   // 10016
#define M_SRC_UPDATE_REGION_OFFSET_Y                  ((M_DISP_CONTROL_START+17L) + M_LOCAL_DISPLAY_CONTROL)   // 10017
#define M_NEAREST_COLOR                               ((M_DISP_CONTROL_START+18L) + M_LOCAL_DISPLAY_CONTROL)   // 10018
#define M_CENTER_DISPLAY                              ((M_DISP_CONTROL_START+19L) + M_LOCAL_DISPLAY_CONTROL)   // 10019
#define M_USE_RESERVED_COLOR                          ((M_DISP_CONTROL_START+20L) + M_LOCAL_DISPLAY_CONTROL)   // 10020
#define M_LOWER_RESERVED_COLOR_START                  ((M_DISP_CONTROL_START+21L) + M_LOCAL_DISPLAY_CONTROL)   // 10021
#define M_LOWER_RESERVED_COLOR_END                    ((M_DISP_CONTROL_START+22L) + M_LOCAL_DISPLAY_CONTROL)   // 10022
#define M_HIGHER_RESERVED_COLOR_START                 ((M_DISP_CONTROL_START+23L) + M_LOCAL_DISPLAY_CONTROL)   // 10023
#define M_HIGHER_RESERVED_COLOR_END                   ((M_DISP_CONTROL_START+24L) + M_LOCAL_DISPLAY_CONTROL)   // 10024
#define M_PREFERED_DISPLAY_FORMAT                     ((M_DISP_CONTROL_START+25L) + M_LOCAL_DISPLAY_CONTROL)   // 10025
#define M_SAVE_INTERNAL_BUFFERS                       ((M_DISP_CONTROL_START+26L) + M_LOCAL_DISPLAY_CONTROL)   // 10026
#define M_HARDWARE_LUT_AVAILABLE                      ((M_DISP_CONTROL_START+27L) + M_LOCAL_DISPLAY_CONTROL)   // 10027
#define M_IS_IN_MEGA_BUFFER_MODE                      ((M_DISP_CONTROL_START+28L) + M_LOCAL_DISPLAY_CONTROL)   // 10028
#define M_UPDATE_THREAD_PRIORITY                      ((M_DISP_CONTROL_START+29L) + M_LOCAL_DISPLAY_CONTROL)   // 10029
#define M_VISIBLE_BUFFER_RECT_SIZE_X                  ((M_DISP_CONTROL_START+30L) + M_LOCAL_DISPLAY_CONTROL)   // 10030
#define M_VISIBLE_BUFFER_RECT_SIZE_Y                  ((M_DISP_CONTROL_START+31L) + M_LOCAL_DISPLAY_CONTROL)   // 10031
#define M_NO_TEARING_ACTIVE                           ((M_DISP_CONTROL_START+32L) + M_LOCAL_DISPLAY_CONTROL)   // 10032
#define M_FORCE_DISPLAY_RESOLUTION                    ((M_DISP_CONTROL_START+33L) + M_LOCAL_DISPLAY_CONTROL)   // 10033
#define M_USE_INTERNAL_BUFFER_FOR_GRAB_CONTINUOUS     ((M_DISP_CONTROL_START+34L) + M_REMOTE_DISPLAY_CONTROL)  // 10034
#define M_NO_TEARING_MODE                             ((M_DISP_CONTROL_START+35L) + M_REMOTE_DISPLAY_CONTROL)  // 10035
#define M_UNDERLAY_UPDATE_STATE                       ((M_DISP_CONTROL_START+36L) + M_LOCAL_DISPLAY_CONTROL)   // 10036
#define M_USE_PRIMARY_SURFACE                         ((M_DISP_CONTROL_START+37L) + M_LOCAL_DISPLAY_CONTROL)   // 10037
#define M_UPDATE_RATE_DIVIDER                         ((M_DISP_CONTROL_START+38L) + M_REMOTE_DISPLAY_CONTROL)  // 10038
#define M_STOP_UPDATE                                 ((M_DISP_CONTROL_START+39L) + M_REMOTE_DISPLAY_CONTROL)  // 10039
#define M_CAN_DO_HARDWARE_COMPOSITION                 ((M_DISP_CONTROL_START+40L) + M_REMOTE_DISPLAY_CONTROL)  // 10040
#define M_MIN_MAX_OF_SELECTED_BUFFER_CHANGED          ((M_DISP_CONTROL_START+41L) + M_REMOTE_DISPLAY_CONTROL)  // 10041
#define M_UPDATE_MEGA_BUFFER_CHILD_POSITION           ((M_DISP_CONTROL_START+42L) + M_LOCAL_DISPLAY_CONTROL)   // 10042
#define M_DISPLAY_TYPE_SUPPORTED                      ((M_DISP_CONTROL_START+43L) + M_LOCAL_DISPLAY_CONTROL)   // 10043
#define M_DEBUG_COLOR                                 ((M_DISP_CONTROL_START+44L) + M_LOCAL_DISPLAY_CONTROL)   // 10044
#define M_LOSING_VIDEO_MEMORY                         ((M_DISP_CONTROL_START+45L) + M_LOCAL_DISPLAY_CONTROL)   // 10045
#define M_VIDEO_MEMORY_RESTORED                       ((M_DISP_CONTROL_START+46L) + M_LOCAL_DISPLAY_CONTROL)   // 10046
#define M_VIDEO_DEVICE_LOST                           ((M_DISP_CONTROL_START+47L) + M_LOCAL_DISPLAY_CONTROL)   // 10047
#define M_DISPLAY_USAGE                               ((M_DISP_CONTROL_START+48L) + M_REMOTE_DISPLAY_CONTROL)  // 10048
#define M_USE_YCRCB_RANGE                             ((M_DISP_CONTROL_START+49L) + M_REMOTE_DISPLAY_CONTROL)  // 10049 //obsolete
#define M_UPDATE_GRAB_TYPE                            ((M_DISP_CONTROL_START+50L) + M_REMOTE_DISPLAY_CONTROL)  // 10050
#define M_GRAB_TYPE_ON_TITLE_BAR                      ((M_DISP_CONTROL_START+51L) + M_LOCAL_DISPLAY_CONTROL)   // 10051
#define M_VIDEO_DEVICE_WAS_MODIFIED                   ((M_DISP_CONTROL_START+52L) + M_LOCAL_DISPLAY_CONTROL)   // 10052
#define M_PAR_ENCODER_WAIT_FIELD                      ((M_DISP_CONTROL_START+53L) + M_LOCAL_DISPLAY_CONTROL)   // 10053
#define M_USE_YCBCR_RANGE                             ((M_DISP_CONTROL_START+54L) + M_REMOTE_DISPLAY_CONTROL)  // 10054
#define M_RESTRICT_CURSOR                             ((M_DISP_CONTROL_START+55L) + M_LOCAL_DISPLAY_CONTROL)   // 10055
#define M_RESTRICT_FOCUS                              ((M_DISP_CONTROL_START+56L) + M_LOCAL_DISPLAY_CONTROL)   // 10056
#define M_SHOW_TASKBAR                                ((M_DISP_CONTROL_START+57L) + M_LOCAL_DISPLAY_CONTROL)   // 10057
#define M_EXCLUSIVE_MODE                              ((M_DISP_CONTROL_START+58L) + M_LOCAL_DISPLAY_CONTROL)   // 10058
#define M_PRE_DISPSELECT_OPERATIONS                   ((M_DISP_CONTROL_START+59L) + M_LOCAL_DISPLAY_CONTROL)   // 10059
#define M_POST_DISPSELECT_OPERATIONS                  ((M_DISP_CONTROL_START+60L) + M_LOCAL_DISPLAY_CONTROL)   // 10060
#define M_PRE_DISPDESELECT_OPERATIONS                 ((M_DISP_CONTROL_START+61L) + M_LOCAL_DISPLAY_CONTROL)   // 10061
#define M_POST_DISPDESELECT_OPERATIONS                ((M_DISP_CONTROL_START+62L) + M_LOCAL_DISPLAY_CONTROL)   // 10062
#define M_PROPAGATE_CALIBRATION_TO_OVERLAY            ((M_DISP_CONTROL_START+63L) + M_REMOTE_DISPLAY_CONTROL)  // 10063
#define M_SAVE_BASIC_SELECTED_BUFFER                  ((M_DISP_CONTROL_START+64L) + M_LOCAL_DISPLAY_CONTROL)   // 10064
#define M_ACQUIRE_WINDOW_FOCUS                        ((M_DISP_CONTROL_START+65L) + M_LOCAL_DISPLAY_CONTROL)   // 10065
#define M_BACKGROUND_COLOR                            ((M_DISP_CONTROL_START+66L) + M_LOCAL_DISPLAY_CONTROL)   // 10066

#define M_VGA_DEVICE_SYSTEM_ID                        ((M_DISP_CONTROL_START+100L) + M_LOCAL_DISPLAY_CONTROL)  // 10100

#define M_DISPLAY_RESOLUTION                          ((M_DISP_CONTROL_START+107L) + M_LOCAL_DISPLAY_CONTROL)  // 10107
#define M_DEFAULT_DISPLAY_RESOLUTION                  ((M_DISP_CONTROL_START+108L) + M_LOCAL_DISPLAY_CONTROL)  // 10108
#define M_SAFE_MODE                                   ((M_DISP_CONTROL_START+109L) + M_LOCAL_DISPLAY_CONTROL)  // 10109
#define M_USE_VIDEO_MEMORY_BUFFER                     ((M_DISP_CONTROL_START+110L) + M_LOCAL_DISPLAY_CONTROL)  // 10110
#define M_SELECT_USER_BUFFER_DIRECTLY_ON_DISPLAY      ((M_DISP_CONTROL_START+111L) + M_LOCAL_DISPLAY_CONTROL)  // 10111
#define M_DISPLAY_FORMAT                              ((M_DISP_CONTROL_START+112L) + M_LOCAL_DISPLAY_CONTROL)  // 10112
#define M_DISPLAY_FORMAT_SUPPORTED                    ((M_DISP_CONTROL_START+113L) + M_LOCAL_DISPLAY_CONTROL)  // 10113
#define M_DISPLAY_TYPE                                ((M_DISP_CONTROL_START+114L) + M_LOCAL_DISPLAY_CONTROL)  // 10114
#define M_USE_UNDERLAY                                ((M_DISP_CONTROL_START+115L) + M_LOCAL_DISPLAY_CONTROL)  // 10115
#define M_USE_DDRAW_UNDERLAY_SURFACE                  M_USE_UNDERLAY
#define M_USE_UNDERLAY_IN_DUALHEAD                    ((M_DISP_CONTROL_START+116L) + M_LOCAL_DISPLAY_CONTROL)  // 10116
#define M_DISPLAY_SCHEME_ON_TITLEBAR                  ((M_DISP_CONTROL_START+117L) + M_LOCAL_DISPLAY_CONTROL)  // 10117
#define M_UPDATE_SYNCHRONIZATION                      ((M_DISP_CONTROL_START+118L) + M_LOCAL_DISPLAY_CONTROL)  // 10118
#define M_UNDERLAY_ALWAYS_ON_TOP                      ((M_DISP_CONTROL_START+119L) + M_LOCAL_DISPLAY_CONTROL)  // 10119

#define M_USER_WINDOW_HANDLE                          ((M_DISP_CONTROL_START+121L) + M_LOCAL_DISPLAY_CONTROL)  // 10121
#define M_USE_HOST_OVERLAY                            ((M_DISP_CONTROL_START+122L) + M_REMOTE_DISPLAY_CONTROL)  // 10122
#define M_SELECTED_LINK_COPY                          ((M_DISP_CONTROL_START+123L) + M_LOCAL_DISPLAY_CONTROL)  // 10123
#define M_HOOK_ON_ERROR                               ((M_DISP_CONTROL_START+124L) + M_LOCAL_DISPLAY_CONTROL)  // 10124
#define M_USE_LIVE_UNDERLAY                           ((M_DISP_CONTROL_START+125L) + M_LOCAL_DISPLAY_CONTROL)  // 10125
#define M_UPDATE_WITH_PAINT_MESSAGE                   ((M_DISP_CONTROL_START+126L) + M_LOCAL_DISPLAY_CONTROL)  // 10126

#define M_DISPLAY_SCHEME_COUNT                        ((M_DISP_CONTROL_START+131L) + M_LOCAL_DISPLAY_CONTROL)  // 10131
#define M_USE_DOUBLE_BUFFERING_SCHEME                 ((M_DISP_CONTROL_START+132L) + M_LOCAL_DISPLAY_CONTROL)  // 10132
#define M_UPDATE_STATE                                ((M_DISP_CONTROL_START+133L) + M_LOCAL_DISPLAY_CONTROL)  // 10133
#define M_FORCE_DISPLAY_SCHEME_CHANGE                 ((M_DISP_CONTROL_START+134L) + M_LOCAL_DISPLAY_CONTROL)  // 10134
//#define M_DISPLAY_DUMP                                ((M_DISP_CONTROL_START+135L)  // 10135  //May be reused

#define M_UNDERLAY_SHOW                               ((M_DISP_CONTROL_START+137L) + M_LOCAL_DISPLAY_CONTROL)  // 10137
#define M_MINIMUM_DISPLAY_SIZE_X                      ((M_DISP_CONTROL_START+138L) + M_LOCAL_DISPLAY_CONTROL)  // 10138
#define M_MINIMUM_DISPLAY_SIZE_Y                      ((M_DISP_CONTROL_START+139L) + M_LOCAL_DISPLAY_CONTROL)  // 10139
#define M_WINDOW_SHOW                                 ((M_DISP_CONTROL_START+140L) + M_LOCAL_DISPLAY_CONTROL)  // 10140
#define M_BUFFER_FORMAT_TO_SELECT_DIRECTLY            ((M_DISP_CONTROL_START+141L) + M_LOCAL_DISPLAY_CONTROL)  // 10141

#define M_USE_USER_BUFFER_FOR_UNDERLAY                ((M_DISP_CONTROL_START+144L) + M_REMOTE_DISPLAY_CONTROL)  // 10144
#define M_USE_CREATE_OVER_USER_BUFFER                 ((M_DISP_CONTROL_START+145L) + M_REMOTE_DISPLAY_CONTROL)  // 10145
#define M_USE_FLICKER_FREE_BUFFER                     ((M_DISP_CONTROL_START+146L) + M_REMOTE_DISPLAY_CONTROL)  // 10146
#define M_USE_CONVERT_TO_COLOR_DIB                    ((M_DISP_CONTROL_START+147L) + M_REMOTE_DISPLAY_CONTROL)  // 10147
#define M_USE_SOFTWARE_COMPOSITION                    ((M_DISP_CONTROL_START+148L) + M_REMOTE_DISPLAY_CONTROL)  // 10148
#define M_USE_HOST_ENTRY_BUFFER                       ((M_DISP_CONTROL_START+149L) + M_REMOTE_DISPLAY_CONTROL)  // 10149
#define M_DISPLAY_SCHEME_BASE                         ((M_DISP_CONTROL_START+150L) + M_REMOTE_DISPLAY_CONTROL)  // 10150

#define M_USE_DISPLAY_SIZE_BUFFER                     ((M_DISP_CONTROL_START+153L) + M_REMOTE_DISPLAY_CONTROL)  // 10153
#define M_USE_MEGA_BUFFER                             ((M_DISP_CONTROL_START+154L) + M_REMOTE_DISPLAY_CONTROL)  // 10154
#define M_UPDATE_TRANSFER_TYPE                        ((M_DISP_CONTROL_START+155L) + M_REMOTE_DISPLAY_CONTROL)  // 10155
#define M_SURFACE_LUT_FLAG                            ((M_DISP_CONTROL_START+156L) + M_REMOTE_DISPLAY_CONTROL)  // 10156

#define M_DEFAULT_MEGA_DISPLAY_SIZE_X                 ((M_DISP_CONTROL_START+158L) + M_LOCAL_DISPLAY_CONTROL)  // 10158
#define M_DEFAULT_MEGA_DISPLAY_SIZE_Y                 ((M_DISP_CONTROL_START+159L) + M_LOCAL_DISPLAY_CONTROL)  // 10159
#define M_WINDOW_INITIAL_SIZE_X                       ((M_DISP_CONTROL_START+160L) + M_LOCAL_DISPLAY_CONTROL)  // 10160
#define M_WINDOW_INITIAL_SIZE_Y                       ((M_DISP_CONTROL_START+161L) + M_LOCAL_DISPLAY_CONTROL)  // 10161
#define M_PREFER_COLOR_DISPLAY_RESOLUTION             ((M_DISP_CONTROL_START+162L) + M_LOCAL_DISPLAY_CONTROL)  // 10162
#define M_VERIFY_UPDATE                               ((M_DISP_CONTROL_START+163L) + M_LOCAL_DISPLAY_CONTROL)  // 10163
#define M_UPDATE_ON_OVERLAY_MODIFIED_INTERNAL         ((M_DISP_CONTROL_START+164L) + M_REMOTE_DISPLAY_CONTROL) // 10164
#define M_USE_GIGACOLOR_SCHEME                        ((M_DISP_CONTROL_START+165L) + M_LOCAL_DISPLAY_CONTROL)  // 10165
#define M_MEGA_BUFFER_CHILD_OFFSET_X                  ((M_DISP_CONTROL_START+166L) + M_LOCAL_DISPLAY_CONTROL)  // 10166
#define M_MEGA_BUFFER_CHILD_OFFSET_Y                  ((M_DISP_CONTROL_START+167L) + M_LOCAL_DISPLAY_CONTROL)  // 10167
#define M_ZOOMED_DESTINATION_OUT_DESKTOP              ((M_DISP_CONTROL_START+168L) + M_LOCAL_DISPLAY_CONTROL)  // 10168
#define M_VALIDATE_DISPLAY                            ((M_DISP_CONTROL_START+169L) + M_LOCAL_DISPLAY_CONTROL)  // 10169
#define M_HOOKS                                       ((M_DISP_CONTROL_START+170L) + M_LOCAL_DISPLAY_CONTROL)  // 10170
#define M_HOOK_ON_OUT_OF_MONITOR                      ((M_DISP_CONTROL_START+171L) + M_LOCAL_DISPLAY_CONTROL)  // 10171
#define M_HOOK_ON_ZOOM_CHANGE                         ((M_DISP_CONTROL_START+172L) + M_LOCAL_DISPLAY_CONTROL)  // 10172
#define M_HOOK_ON_MB_CHILD_RESIZE                     ((M_DISP_CONTROL_START+173L) + M_LOCAL_DISPLAY_CONTROL)  // 10173
#define M_DISPLACE_WINDOWS                            ((M_DISP_CONTROL_START+174L) + M_LOCAL_DISPLAY_CONTROL)  // 10174
#define M_UPDATE_TITLE                                ((M_DISP_CONTROL_START+175L) + M_LOCAL_DISPLAY_CONTROL)  // 10175
#define M_RESET_WINDOW_SIZE                           ((M_DISP_CONTROL_START+176L) + M_LOCAL_DISPLAY_CONTROL)  // 10176
#define M_WINDOW_CURRENTLY_MAXIMIZED                  ((M_DISP_CONTROL_START+177L) + M_LOCAL_DISPLAY_CONTROL)  // 10177
#define M_WINDOW_CURRENTLY_MINIMIZED                  ((M_DISP_CONTROL_START+178L) + M_LOCAL_DISPLAY_CONTROL)  // 10178
#define M_MEGA_BUFFER_LOW_LIMIT                       ((M_DISP_CONTROL_START+179L) + M_LOCAL_DISPLAY_CONTROL)  // 10179
#define M_MAXIMUM_VISIBLE_DEST_SIZE_X                 ((M_DISP_CONTROL_START+180L) + M_LOCAL_DISPLAY_CONTROL)  // 10180
#define M_MAXIMUM_VISIBLE_DEST_SIZE_Y                 ((M_DISP_CONTROL_START+181L) + M_LOCAL_DISPLAY_CONTROL)  // 10181
#define M_DO_SELECT                                   ((M_DISP_CONTROL_START+182L) + M_LOCAL_DISPLAY_CONTROL)  // 10182
#define M_RESTRICT_WINDOWS                            ((M_DISP_CONTROL_START+183L) + M_LOCAL_DISPLAY_CONTROL)  // 10183
#define M_NUMBER_OF_BASIC_IMPLEMENTATIONS             ((M_DISP_CONTROL_START+185L) + M_LOCAL_DISPLAY_CONTROL)  // 10185

#define M_WINDOW_CURRENTLY_VISIBLE                    ((M_DISP_CONTROL_START+187L) + M_LOCAL_DISPLAY_CONTROL)  // 10187
#define M_VIRTUAL_GRAB                                ((M_DISP_CONTROL_START+188L) + M_LOCAL_DISPLAY_CONTROL)  // 10188
#define M_WINDOW_RESIZE_ON_ZOOM                       ((M_DISP_CONTROL_START+189L) + M_LOCAL_DISPLAY_CONTROL)  // 10189
#define M_DISPLAY_SYNC                                ((M_DISP_CONTROL_START+190L) + M_LOCAL_DISPLAY_CONTROL)  // 10190
#define M_USE_NO_VIDEO_OVERLAY_BUFFER                 ((M_DISP_CONTROL_START+191L) + M_LOCAL_DISPLAY_CONTROL)  // 10191
#define M_USE_YUV16_UYVY_SCHEME                       (M_DISP_CONTROL_START+192L)  // 10192
#define M_FILL_COLOR                                  ((M_DISP_CONTROL_START+193L) + M_LOCAL_DISPLAY_CONTROL)  // 10193
#define M_CURRENTLY_CENTERED_X                        ((M_DISP_CONTROL_START+194L) + M_LOCAL_DISPLAY_CONTROL)  // 10194
#define M_XDISPLAY                                    (M_DISP_CONTROL_START+195L)  // 10195
#define M_WINDOW_TASKBAR                              ((M_DISP_CONTROL_START+196L) + M_LOCAL_DISPLAY_CONTROL)  // 10196
#define M_SHOW_WINDOW_IN_TASKBAR                      M_WINDOW_TASKBAR
#define M_WINDOW_TASKBAR_ON_FULLSCREEN                ((M_DISP_CONTROL_START+197L) + M_LOCAL_DISPLAY_CONTROL)  // 10197
#define M_CURRENTLY_CENTERED_Y                        ((M_DISP_CONTROL_START+198L) + M_LOCAL_DISPLAY_CONTROL)  // 10198
#define M_WINDOW_CURSOR                               ((M_DISP_CONTROL_START+199L) + M_LOCAL_DISPLAY_CONTROL)  // 10199
#define M_WINDOW_ROI_BUTTONS                          ((M_DISP_CONTROL_START+200L) + M_LOCAL_DISPLAY_CONTROL)  // 10200
#define M_ROI_AUTO_RESET                              ((M_DISP_CONTROL_START+201L) + M_LOCAL_DISPLAY_CONTROL)  // 10201
#define M_COPY_TO_CLIPBOARD                           ((M_DISP_CONTROL_START+202L) + M_LOCAL_DISPLAY_CONTROL)  // 10202
#if (M_MIL_USE_UNICODE && !M_MIL_UNICODE_API && !M_COMPILING_MILDLL)
#define M_SAVE_TO_FILE                                ((M_DISP_CONTROL_START+203L)|M_LOCAL_DISPLAY_CONTROL|M_CLIENT_ASCII_MODE)  // 75739
#else
#define M_SAVE_TO_FILE                                ((M_DISP_CONTROL_START+203L) + M_LOCAL_DISPLAY_CONTROL)  // 10203
#endif
#define M_COPY_DISPLAY_TO_ID                          ((M_DISP_CONTROL_START+204L) + M_LOCAL_DISPLAY_CONTROL)  // 10204
#define M_SAVE_TO_BUFFER                              M_COPY_DISPLAY_TO_ID
#define M_UPDATE_RATE_MAX                             ((M_DISP_CONTROL_START+205L) + M_REMOTE_DISPLAY_CONTROL) // 10205
#define M_ASYNC_UPDATE                                ((M_DISP_CONTROL_START+206L) + M_REMOTE_DISPLAY_CONTROL) // 10206
#define M_MEGA_BUFFER_LOW_LIMIT_X                     ((M_DISP_CONTROL_START+207L) + M_LOCAL_DISPLAY_CONTROL)  // 10207
#define M_COMMON_VGA_INDEX                            ((M_DISP_CONTROL_START+208L) + M_LOCAL_DISPLAY_CONTROL)  // 10208
#define M_FAST_SELECT                                 ((M_DISP_CONTROL_START+209L) + M_REMOTE_DISPLAY_CONTROL) // 10209
#define M_FAST_UNDERLAY_MODE						         ((M_DISP_CONTROL_START+210L) + M_LOCAL_DISPLAY_CONTROL)  // 10210	
#define M_CUSTOM_SCHEME_CHANGING                      ((M_DISP_CONTROL_START+211L) + M_REMOTE_DISPLAY_CONTROL) // 10211

#define M_ROI_DISPCONTROL_START                       (M_DISP_CONTROL_START+500L)  // 10500
#define M_ROI_DEFINE                                  ((M_DISP_CONTROL_START+500L) + M_LOCAL_DISPLAY_CONTROL)  // 10500
#define M_ROI_SHOW                                    ((M_DISP_CONTROL_START+501L) + M_LOCAL_DISPLAY_CONTROL)  // 10501
#define M_ROI_SUPPORT                                 ((M_DISP_CONTROL_START+502L) + M_LOCAL_DISPLAY_CONTROL)  // 10502
#define M_ROI_LINE_COLOR                              ((M_DISP_CONTROL_START+503L) + M_LOCAL_DISPLAY_CONTROL)  // 10503
#define M_ROI_RESET                                   ((M_DISP_CONTROL_START+504L) + M_LOCAL_DISPLAY_CONTROL)  // 10504
#define M_ROI_RECT_DISPLAY                            ((M_DISP_CONTROL_START+505L) + M_LOCAL_DISPLAY_CONTROL)  // 10505
#define M_ROI_RECT_BUFFER                             ((M_DISP_CONTROL_START+506L) + M_LOCAL_DISPLAY_CONTROL)  // 10506
#define M_ROI_SET_POINT                               ((M_DISP_CONTROL_START+507L) + M_LOCAL_DISPLAY_CONTROL)  // 10507
#define M_ROI_LINE_WIDTH                              ((M_DISP_CONTROL_START+508L) + M_LOCAL_DISPLAY_CONTROL)  // 10508
#define M_ROI_HANDLE_COLOR                            ((M_DISP_CONTROL_START+509L) + M_LOCAL_DISPLAY_CONTROL)  // 10509
#define M_ROI_HANDLE_SIZE                             ((M_DISP_CONTROL_START+510L) + M_LOCAL_DISPLAY_CONTROL)  // 10510
#define M_ROI_DISPLAY_OFFSET_X                        ((M_DISP_CONTROL_START+511L) + M_LOCAL_DISPLAY_CONTROL)  // 10511
#define M_ROI_DISPLAY_OFFSET_Y                        ((M_DISP_CONTROL_START+512L) + M_LOCAL_DISPLAY_CONTROL)  // 10512
#define M_ROI_DISPLAY_SIZE_X                          ((M_DISP_CONTROL_START+513L) + M_LOCAL_DISPLAY_CONTROL)  // 10513
#define M_ROI_DISPLAY_SIZE_Y                          ((M_DISP_CONTROL_START+514L) + M_LOCAL_DISPLAY_CONTROL)  // 10514
#define M_ROI_BUFFER_OFFSET_X                         ((M_DISP_CONTROL_START+515L) + M_LOCAL_DISPLAY_CONTROL)  // 10515
#define M_ROI_BUFFER_OFFSET_Y                         ((M_DISP_CONTROL_START+516L) + M_LOCAL_DISPLAY_CONTROL)  // 10516
#define M_ROI_BUFFER_SIZE_X                           ((M_DISP_CONTROL_START+517L) + M_LOCAL_DISPLAY_CONTROL)  // 10517
#define M_ROI_BUFFER_SIZE_Y                           ((M_DISP_CONTROL_START+518L) + M_LOCAL_DISPLAY_CONTROL)  // 10518
#define M_ROI_SHAPE                                   ((M_DISP_CONTROL_START+519L) + M_LOCAL_DISPLAY_CONTROL)  // 10519
#define M_ROI_MINIMUM_SIZE                            ((M_DISP_CONTROL_START+520L) + M_LOCAL_DISPLAY_CONTROL)  // 10521
#define M_ROI_DISPCONTROL_END                         (M_DISP_CONTROL_START+550L)  // 10550
#define M_IS_IN_ROI_DISPLAY_RANGE(X)                  ((M_ORIGINAL_DISPLAY_CONTROL(X)>=M_ROI_DISPCONTROL_START) && (M_ORIGINAL_DISPLAY_CONTROL(X)<=M_ROI_DISPCONTROL_END))
#define M_CONTEXTUAL_MENU                             ((M_DISP_CONTROL_START+551L) + M_LOCAL_DISPLAY_CONTROL)  // 10551
#define M_CHANGE_MODE_BETWEEN_MONITORS                ((M_DISP_CONTROL_START+552L) + M_LOCAL_DISPLAY_CONTROL)  // 10552
#define M_DISPLAY_IS_INTERNALLY_ALLOCATED             ((M_DISP_CONTROL_START+553L) + M_LOCAL_DISPLAY_CONTROL)  // 10553
#define M_HOOK_ON_DEVICE_LOSING                       ((M_DISP_CONTROL_START+554L) + M_LOCAL_DISPLAY_CONTROL)   // 10554

#define M_WINDOW_ANNOTATIONS                          ((M_DISP_CONTROL_START+556L) + M_LOCAL_DISPLAY_CONTROL)  // 10556
#define M_SCALE_DISPLAY                               ((M_DISP_CONTROL_START+557L) + M_LOCAL_DISPLAY_CONTROL)  // 10557
#define M_WINDOW_ANNOTATIONS_STATE                    ((M_DISP_CONTROL_START+558L) + M_LOCAL_DISPLAY_CONTROL)  // 10558
#define M_NO_TEARING_ALLOWED                          ((M_DISP_CONTROL_START+559L) + M_LOCAL_DISPLAY_CONTROL)  // 10559
#define M_ZOOM_ACCURACY                               ((M_DISP_CONTROL_START+560L) + M_LOCAL_DISPLAY_CONTROL)  // 10560
#define M_USE_EXTERNAL_NO_TEARING                     ((M_DISP_CONTROL_START+561L) + M_LOCAL_DISPLAY_CONTROL)  // 10561
#define M_ASSOCIATED_GRAPHIC_LIST_ID                  ((M_DISP_CONTROL_START+562L) + M_REMOTE_DISPLAY_CONTROL) // 10562
#define M_DISPLAY_GRAPHIC_LIST                        M_ASSOCIATED_GRAPHIC_LIST_ID
#define M_ZOOM_PAN_HANDLED_BY_SCHEME                  ((M_DISP_CONTROL_START+563L) + M_LOCAL_DISPLAY_CONTROL)  // 10563
#define M_UPDATE_GRAPHIC_LIST                         ((M_DISP_CONTROL_START+564L) + M_REMOTE_DISPLAY_CONTROL) // 10564
#define M_MEGA_BUFFER_SIZE_X_TO_USE                   ((M_DISP_CONTROL_START+565L) + M_LOCAL_DISPLAY_CONTROL)  // 10565
#define M_MEGA_BUFFER_SIZE_Y_TO_USE                   ((M_DISP_CONTROL_START+566L) + M_LOCAL_DISPLAY_CONTROL)  // 10566
#define M_GRAPHIC_LIST_INTERACTIVE                    ((M_DISP_CONTROL_START+567L) + M_REMOTE_DISPLAY_CONTROL) // 10567
#define M_USE_GDI_TO_APPLY_LUT                        ((M_DISP_CONTROL_START+568L) + M_LOCAL_DISPLAY_CONTROL)  // 10568
#define M_APPLY_LUT_WITH_GDI                          ((M_DISP_CONTROL_START+569L) + M_LOCAL_DISPLAY_CONTROL)  // 10569
#define M_GRAPHIC_LIST_BOUNDING_RECT                  ((M_DISP_CONTROL_START+570L) + M_REMOTE_DISPLAY_CONTROL) // 10570
#define M_ASSOCIATED_REMOTE_DISPLAY_ID                ((M_DISP_CONTROL_START+572L) + M_LOCAL_DISPLAY_CONTROL)  // 10571
#define M_DMIL_REALLOC_SURFACE                        ((M_DISP_CONTROL_START+571L) + M_REMOTE_DISPLAY_CONTROL)  // 10571

//Reserved for future AMIL custom display controls    10990L
//                                                 to 11000L
#define M_ACTIVEMIL_RESERVED_DISPCONTROL_START        (M_DISP_CONTROL_START+990L)  // 10990
#define M_ACTIVEMIL_RESERVED_DISPCONTROL_STOP         (M_DISP_CONTROL_START+1000L) // 11000




#define M_DISP_CONTROL_DIRECT_STOP                    11000L

#define M_APP_BH_DISPLAY_START                        12000L
#define M_DESCRIPTOR_LOCK                             (M_APP_BH_DISPLAY_START+00L)     // 12000
#define M_APP_BH_DISPLAY_END                          12099L
#define M_IS_IN_DISPLAY_APP_BH_RANGE(X)               ((X>=M_APP_BH_DISPLAY_START) && (X<=M_APP_BH_DISPLAY_END))


#define M_SCALE                                       0x00008010L
#define M_CUSTOM_DISPLAY                              M_IN_BUFFER_DISPLAY
#define M_CUSTOM_DISPLAY_BUFFER                       M_DISPLAY_SURFACE

/************************************************************************/
/* MdispControl() / MdispInquire() Values                               */
/************************************************************************/

#define M_FULL_SIZE                      0L
#define M_NORMAL_SIZE                    1L

#define M_BENCHMARK_IN_DEBUG_ON          0x00000001L
#define M_BENCHMARK_IN_DEBUG_OFF         0
#define M_BENCHMARK_IN_DEBUG_TRACE       0x00000002L
#define M_BENCHMARK_IN_DEBUG_NOTRACE     0
#define M_BENCHMARK_IN_DEBUG_ALLSIZE     0x00000004L
#define M_BENCHMARK_IN_DEBUG_CSTSIZE     0

#define M_DISPLAY_SCAN_LINE_START        0x00000000L
#define M_DISPLAY_SCAN_LINE_END                   -1

#define M_SLAVE                          0L
#define M_MASTER                         1L

#define M_FILTER_LOW_PASS_TYPE_A         1L
#define M_FILTER_NOTCH                   2L
#define M_FILTER_EXTENDED                3L
#define M_FILTER_LOW_PASS_TYPE_B         4L
#define M_BYPASS                         5L
#define M_LOW_PASS_0                     M_FILTER_LOW_PASS_TYPE_A
#define M_LOW_PASS_1                     M_FILTER_LOW_PASS_TYPE_B
#define M_LOW_PASS_2                     M_FILTER_EXTENDED
#define M_NOTCH                          M_FILTER_NOTCH

#define M_TRANSPARENT_COLOR              (0x01000060L + M_LOCAL_DISPLAY_CONTROL)
#define M_TEST_UPDATE_IF_ASYNCHRONOUS    0x00000010L

//For M_NO_TEARING dispControl
#define M_ENABLE                                      -9997L
#define M_FULL_UPDATE                                 -9998L
#define M_DISABLE                                     -9999L
#define M_DEFAULT                                     0x10000000L
#define M_GRAB_CONTINUOUS_ONLY                        0x00100000L
#define M_BASIC                                       0x00200000L
#define M_ADVANCED                                    0x00400000L
#define M_NO_SKIP                                     ((M_DISP_CONTROL_START+2L) + M_LOCAL_DISPLAY_CONTROL)    // 10002
#define M_SKIP_OLDEST                                 ((M_DISP_CONTROL_START+3L) + M_LOCAL_DISPLAY_CONTROL)    // 10003
#define M_SKIP_NEWEST                                 ((M_DISP_CONTROL_START+4L) + M_LOCAL_DISPLAY_CONTROL)    // 10004
#define M_NO_TEARING_SKIP_MODE_MASK                   (0x000FFFFFL + M_LOCAL_DISPLAY_CONTROL)
#define M_NO_TEARING_MODE_MASK                        0x00F00000L
#define M_CURRENT_RESOLUTION                          MT("M_CURRENT_RESOLUTION")
#define M_RESET_RESOLUTION                            MT("M_RESET_RESOLUTION")
#define M_RESTORE_RESOLUTION                          MT("M_RESTORE_RESOLUTION")

#define BIN_TO_MIL(b)                                 ( ((M_DEFAULT==b)||(M_ENABLE==b)||(M_DISABLE==b)||(M_FULL_UPDATE==b))?(b):(b?M_ENABLE:M_DISABLE) )

#define M_ON_SELECT                      1L
#define M_ON_DESELECT                    2L

// For the control M_GRAB_BUFFERS
#define M_DRIVER_ERROR_PENDING                        0x40000000L

// For the M_STOP_UPDATE control/inquire
#define M_WHEN_MINIMIZED                              0x00000001L
#define M_WHEN_NOT_VISIBLE                            0x00000002L

// For M_VIDEO_DEVICE_LOST control/inquire
#define M_SIGNAL_OFF                                  0x00000000L
#define M_CLEAR                                       0x00000001L
#define M_NO_CLEAR                                    0x00000002L

// For M_ROI_DEFINE control
#define M_START                                       0x00000002L
#define M_STOP                                        0x00000004L
#define M_RESET                                       9L
#define M_RECTANGULAR                                 0x00000010L                      

// For M_VGA_INDEX inquire
#define M_INVALID_VGA_INDEX                           -1L
#define M_SHARED_VGA_INDEX                            -2L
#define M_IS_SPECIAL_VGA_INDEX(X)                     ((X==M_INVALID_VGA_INDEX)||(X==M_SHARED_VGA_INDEX))

// For M_CAN_ALLOCATE_CONTIGUOUS_VIDEO_MEMORY inquire
#define M_CONTIGUOUS                    0x00000001L
#define M_START_IN_VIDEO_MEMORY         0x00000010L
#define M_END_IN_VIDEO_MEMORY           0x00000020L
#define M_START_IN_HOST_MEMORY          0x00000040L
#define M_END_IN_HOST_MEMORY            0x00000080L
#define M_NO_PHYSICAL_ADDRESS           0x00000100L
#define M_IN_VIDEO_MEMORY(x)               ((x&M_START_IN_VIDEO_MEMORY) && (x&M_END_IN_VIDEO_MEMORY))
#define M_IN_HOST_MEMORY(x)                ((x&M_START_IN_HOST_MEMORY) && (x&M_END_IN_HOST_MEMORY))
#define M_CONTIGUOUS_AND_IN_VIDEO_MEMORY(x)((x&M_CONTIGUOUS) && M_IN_VIDEO_MEMORY(x))

// For M_ZOOM_ACCURACY
#define M_MEDIUM                                2L
#define M_HIGH                                  3L


// For M_INTERACTIVE_MODE
//M_LEGACY
#define M_MOUSE_DRIVEN                          0x00000002L
/************************************************************************/
/* MdispLut()                                                           */
#define M_PSEUDO                                       M_PSEUDO_LUT //(M_PSEUDO_ID+2)


/************************************************************************/
/* MdispHook()                                                          */
/************************************************************************/
#define M_ASYNC_HOOK                  0x08000000L

/* Defines for hook to modification to bitmap and window */
#define M_NOT_MODIFIED                0 /* No changed at all              */
#define M_MODIFIED_LUT                1 /* Disp lut is changed            */
#define M_MODIFIED_DIB                2 /* Disp buffer data is changed    */
#define M_MODIFIED_ZOOM               3 /* Disp is zoomed                 */
#define M_MODIFIED_PAN                4 /* Disp is panned                 */
#define M_MODIFIED_DIB_CREATION       5 /* Disp receives a new buffer ID  */
#define M_MODIFIED_DIB_DESTRUCTION    6 /* Disp receives a buffer ID 0    */
#define M_MODIFIED_WINDOW_CREATION    7 /* Wnd is created                 */
#define M_MODIFIED_WINDOW_DESTRUCTION 8 /* Wnd is destroyed               */
#define M_MODIFIED_WINDOW_LOCATION    9 /* Wnd size is changed            */
#define M_MODIFIED_WINDOW_OVERLAP    11 /* Wnd overlap is changed         */
#define M_MODIFIED_WINDOW_ICONIZED   12 /* Wnd is changed to iconic state */
#define M_MODIFIED_WINDOW_ZOOM       13 /* Wnd is zoomed                  */
#define M_MODIFIED_WINDOW_PAN        14 /* Wnd is panned                  */
#define M_MODIFIED_WINDOW_MENU       15 /* Wnd menu pulled-down           */
#define M_MODIFIED_WINDOW_PAINT      16 /* Wnd is painted with image      */
#define M_MODIFIED_WINDOW_ACTIVE     17 /* Wnd activation state changed   */
#define M_MODIFIED_WINDOW_ENABLE     18 /* Wnd enable state changed       */
#define M_MODIFIED_WINDOW_CLIP_LIST  19 /* Wnd clip list changed          */

/* M_MODIFIED_WINDOW_MENU modification hook defines */
#define M_MODIFIED_SYS_MENU            0x00100L
#define M_MODIFIED_APP_MENU            0x00200L
#define M_MODIFIED_USER_APP_MENU       0x10000L
#define M_MODIFIED_RESTORE_MENUITEM    0x00001L
#define M_MODIFIED_MOVE_MENUITEM       0x00002L
#define M_MODIFIED_SIZE_MENUITEM       0x00003L
#define M_MODIFIED_MINIMIZE_MENUITEM   0x00004L
#define M_MODIFIED_MAXIMIZE_MENUITEM   0x00005L
#define M_MODIFIED_CLOSE_MENUITEM      0x00006L
#define M_MODIFIED_TASKLIST_MENUITEM   0x00007L
#define M_MODIFIED_MENUBAR_MENUITEM    0x00008L
#define M_MODIFIED_TITLEOFF_MENUITEM   0x00009L
#define M_MODIFIED_ZOOMIN_MENUITEM     0x0000AL
#define M_MODIFIED_ZOOMOUT_MENUITEM    0x0000BL
#define M_MODIFIED_NOZOOM_MENUITEM     0x0000CL

/* M_MODIFIED_WINDOW_ACTIVE modification hook defines */
/* M_MODIFIED_WINDOW_ENABLE modification hook defines */
#define M_MODIFIED_STATE_FROM_WINDOW   0
#define M_MODIFIED_STATE_FROM_PARENT   0x00000010L
#define M_MODIFIED_OFF                 0
#define M_MODIFIED_ON                  0x00000001L

/* M_MODIFIED_WINDOW_CLIP_LIST modification hook defines */
/* M_MODIFIED_WINDOW_CLIP_LIST modification hook defines */
#define M_MODIFIED_ACCESS_RECTANGULAR_OFF 0
#define M_MODIFIED_ACCESS_RECTANGULAR_ON  0x00000001L
#define M_MODIFIED_ACCESS_OFF             0
#define M_MODIFIED_ACCESS_ON              0x00000002L
#define M_MODIFIED_ACCESS_COMMAND_PROMPT  0x00000004L

/* Type of event to hook for a display */
#define M_HOOK_AFTER                0x10000000L          /* For hook after modification      */
#define M_HOOK_BEFORE               0x20000000L          /* For hook before modification     */
#define M_LOCAL_HOOK_RANGE1_START   M_HOOK_MODIFIED_DIB  /* Start of first range of local hooks */
#define M_HOOK_MODIFIED_DIB         1L                   /* For buffer bitmap modification   */
#define M_HOOK_MODIFIED_WINDOW      2L                   /* For disp window modification     */
#define M_HOOK_MESSAGE_LOOP         4L                   /* For disp window modification     */
#define M_LOCAL_HOOK_RANGE1_END     M_HOOK_MESSAGE_LOOP  /* End of first range of local hooks */
#define M_FRAME_START               9L                   /* For disp frame start             */
#define M_PRE_GRAB_BUFFER_CHANGE    10L                  /* For hook before the display scheme change when it imply the change of the grab buffers */
#define M_POST_GRAB_BUFFER_CHANGE   11L                  /* For hook after the display scheme change when it imply the change of the grab buffers  */
#define M_PRE_SCHEME_CHANGE         M_PRE_GRAB_BUFFER_CHANGE   /* Old Name */
#define M_POST_SCHEME_CHANGE        M_POST_GRAB_BUFFER_CHANGE  /* Old Name */
#define M_LOCAL_HOOK_RANGE2_START   (M_BASIC_DISPLAY_EVENT & ~M_ASYNC_HOOK)   /* Start of second range of local hooks */
#define M_BASIC_DISPLAY_EVENT       (12L | M_ASYNC_HOOK) /* For hook when disp window is displayed in another VGA,or between, or unsupported zoom or more (new MIL8) */
#define M_SURFACE_LOST              (14L | M_ASYNC_HOOK) /* For hook when DirectX surface is lost (new event for MIL8.0)     */
#define M_LOCAL_HOOK_RANGE2_END     (M_SURFACE_LOST & ~M_ASYNC_HOOK) /* End of second range of local hooks */
#define M_INVALIDATE_DISPLAY        (16L | M_ASYNC_HOOK) /* For hook when a full internal update is needed (new event for MIL8.0)     */
#define M_LOCAL_HOOK_RANGE3_START   M_WINDOW_CLOSE_BEFORE   /* Start of third range of local hooks */
#define M_WINDOW_CLOSE_BEFORE       17L
#define M_WINDOW_CLOSE_AFTER        18L
#define M_WINDOW_MINIMIZE_BEFORE    19L
#define M_WINDOW_MINIMIZE_AFTER     20L
#define M_WINDOW_MAXIMIZE_BEFORE    21L
#define M_WINDOW_MAXIMIZE_AFTER     22L
#define M_WINDOW_RESTORE_BEFORE     23L
#define M_WINDOW_RESTORE_AFTER      24L
#define M_WINDOW_POSCHANGE_BEFORE   25L
#define M_WINDOW_POSCHANGE_AFTER    26L
#define M_WINDOW_ZOOM_BEFORE        27L
#define M_WINDOW_ZOOM_AFTER         28L
#define M_WINDOW_SCROLL_BEFORE      29L
#define M_WINDOW_SCROLL_AFTER       30L
#define M_WINDOW_PAINT_BEFORE       31L
#define M_WINDOW_PAINT_AFTER        32L
#define M_WINDOW_ACTIVE_BEFORE      33L
#define M_WINDOW_ACTIVE_AFTER       34L
#define M_WINDOW_ENABLE_BEFORE      35L
#define M_WINDOW_ENABLE_AFTER       36L
#define M_WINDOW_SHOW_BEFORE        37L
#define M_WINDOW_SHOW_AFTER         38L
#define M_MODIFIED_DISPLAY          39L
#define M_LOCAL_HOOK_RANGE3_END     M_MODIFIED_DISPLAY   /* End of third range of local hooks */
#define M_DISPLAY_SCHEME_CHANGED    40L
#define M_PRE_OVERLAY_ID_CHANGE     41L
#define M_POST_OVERLAY_ID_CHANGE    42L
#define M_LOCAL_HOOK_RANGE4_START   M_WINDOW_VISIBLE_CHANGE /* Start of fourth range of local hooks */
#define M_WINDOW_VISIBLE_CHANGE     43L
#define M_LOCAL_HOOK_RANGE4_END     M_WINDOW_VISIBLE_CHANGE /* End of fourth range of local hooks */
#define M_PRIMARY_SURFACE_ID_CHANGED 44L
#define M_LOCAL_HOOK_RANGE5_START   M_DEVICE_LOSING   /* Start of fifth range of local hooks */
#define M_DEVICE_LOSING             45L
#define M_DEVICE_LOST               46L
#define M_DEVICE_RESTORING          47L
#define M_DEVICE_RESTORED           48L
#define M_ROI_CHANGE                49L
#define M_ROI_CHANGE_END            50L
#define M_ROI_HANDLE_RELEASE        51L
#define M_VIDEO_DEVICE_MODIFIED_BEFORE 52L
#define M_VIDEO_DEVICE_MODIFIED_AFTER  53L
#define M_DEVICE_LEAVEVT            54L
#define M_DEVICE_ENTERVT            55L
#define M_MOUSE_LEFT_BUTTON_DOWN    56L
#define M_MOUSE_RIGHT_BUTTON_DOWN   57L
#define M_MOUSE_LEFT_BUTTON_UP      58L
#define M_MOUSE_RIGHT_BUTTON_UP     59L
#define M_MOUSE_MOVE                64L
#define M_ANNOTATIONS_DRAW          60L
#define M_LOCAL_HOOK_RANGE5_END     M_ANNOTATIONS_DRAW   /* End of fifth of local hooks */
#define M_WINDOW_ACTION             61L
#define M_WINDOW_RESIZED            62L
#define M_LOCAL_HOOK_RANGE6_START   M_MOUSE_MOVE /* Start of sixth range of local hooks */
#define M_MOUSE_MOVE                64L
//#define RESERVED                  65 to 99L
//#define RESERVED                  66L
//#define RESERVED                  67L
//#define RESERVED                  68L
//#define RESERVED                  69L
#define M_LOCAL_HOOK_RANGE6_END     M_MOUSE_MOVE   /* End of sixth of local hooks */

#define M_IS_LOCAL_HOOK(HookType)   (((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE1_START) &&  \
                                      (((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE1_END)) ||   \
                                     ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE2_START) &&  \
                                      (((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE2_END)) ||   \
                                     ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE3_START) &&  \
                                      (((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE3_END)) ||   \
                                     ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE4_START) &&  \
                                      (((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE4_END)) ||   \
                                      ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE5_START) &&  \
                                     ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE5_END)) ||   \
                                     ((((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) >= M_LOCAL_HOOK_RANGE6_START) &&  \
                                      (((HookType) & ~(M_HOOK_AFTER | M_HOOK_BEFORE)) <= M_LOCAL_HOOK_RANGE6_END))))

//Old names
#if !((BW_COMPATIBILITY >= 0x090) && (BW_COMPATIBILITY <= 0x095))
#define M_WINDOW_LBUTTONDOWN        M_MOUSE_LEFT_BUTTON_DOWN
#define M_WINDOW_RBUTTONDOWN        M_MOUSE_RIGHT_BUTTON_DOWN
#define M_WINDOW_LBUTTONUP          M_MOUSE_LEFT_BUTTON_UP
#define M_WINDOW_RBUTTONUP          M_MOUSE_RIGHT_BUTTON_UP
#define M_PRE_SCHEME_CHANGE         M_PRE_GRAB_BUFFER_CHANGE 
#define M_POST_SCHEME_CHANGE        M_POST_GRAB_BUFFER_CHANGE
#endif

// TBR MIL 9.0 Temporary pseudo device-hook to allow user to be hooked to device-lost 
// even if device-object does not exist in mil.dll
#if BW_COMPATIBILITY == 0x080
   #define M_DISPLAY_DEVICE_LOST       98L
   #define M_DISPLAY_DEVICE_RESTORED   99L
   #define M_DISPLAY_DEVICE_LOSING    100L
#endif

#if OldDefinesSupport
#define M_ROI_ANCHOR_COLOR    M_ROI_HANDLE_COLOR
#define M_ROI_ANCHOR_SIZE     M_ROI_HANDLE_SIZE
#define M_ROI_ANCHOR_RELEASE  M_ROI_HANDLE_RELEASE
#define M_WINDOW_ROI          M_WINDOW_ROI_BUTTONS
#endif


// Flag passed via the EventId of the hook
#define M_INVALIDATE_OVERLAY     (0x00000001)
#define M_INVALIDATE_UNDERLAY    (0x00000002)
#define M_INVALIDATE_ALL_DISPLAY (M_INVALIDATE_OVERLAY|M_INVALIDATE_UNDERLAY)

/************************************************************************/
/* MdispGetHookInfo() Info types                                        */
/************************************************************************/
#define M_DISPLAY                0x00200000L
#define M_MOUSE_POSITION_X       1L
#define M_MOUSE_POSITION_Y       2L
#define M_ANNOTATIONS_DC         3L
#define M_ANNOTATIONS_PIXMAP     M_ANNOTATIONS_DC // Pixmap for Linux 
#define M_MOUSE_POSITION_BUFFER_X  4L
#define M_MOUSE_POSITION_BUFFER_Y  5L

/************************************************************************/
/* MdispOverlayKey()                                                    */
/************************************************************************/
#define M_KEY_ON_COLOR                                1L
#define M_KEY_OFF                                     2L
#define M_KEY_ALWAYS                                  3L


      /* -------------------------------------------------------------- */
      /* -------------------------------------------------------------- */

      /* FUNCTION PROTOTYPES */

      /* -------------------------------------------------------------- */

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
   {
#endif

typedef MIL_HOOK_FUNCTION_PTR MDISPHOOKFCTPTR;
typedef MIL_HOOK_FUNCTION_PTR MIL_DISP_HOOK_FUNCTION_PTR;

MFTYPE32 void MFTYPE    MdispHookFunction    (MIL_ID DisplayId,
                                              MIL_INT HookType,
                                              MIL_DISP_HOOK_FUNCTION_PTR HookHandlerPtr,
                                              void MPTYPE * UserDataPtr);


#if M_MIL_USE_UNICODE
MFTYPE32 MIL_ID MFTYPE  MdispAllocA          (MIL_ID SystemId,
                                              MIL_INT DispNum,
                                              MIL_API_CONST char* DispFormat,
                                              MIL_INT InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);
MFTYPE32 MIL_ID MFTYPE  MdispAllocW          (MIL_ID SystemId,
                                              MIL_INT DispNum,
                                              MIL_API_CONST_TEXT_PTR DispFormat,
                                              MIL_INT InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);
#if M_MIL_UNICODE_API
#define MdispAlloc MdispAllocW
#else
#define MdispAlloc MdispAllocA
#endif
#else

MFTYPE32 MIL_ID MFTYPE  MdispAlloc           (MIL_ID SystemId,
                                              MIL_INT DispNum,
                                              MIL_API_CONST_TEXT_PTR DispFormat,
                                              MIL_INT InitFlag,
                                              MIL_ID MPTYPE *IdVarPtr);

#endif


MFTYPE32 void MFTYPE    MdispFree            (MIL_ID DisplayId);

MFTYPE32 void MFTYPE    MdispSelect          (MIL_ID DisplayId,
                                              MIL_ID ImageId);

#define MdispDeselect(DisplayId, ImageId) MdispSelect(DisplayId, M_NULL)

MFTYPE32 MIL_INT MFTYPE MdispInquire         (MIL_ID DisplayId,
                                              MIL_INT inquire_type,
                                              void MPTYPE *result_ptr);

MFTYPE32 void MFTYPE    MdispPan             (MIL_ID DisplayId,
                                              MIL_DOUBLE XOffset,
                                              MIL_DOUBLE YOffset);
MFTYPE32 void MFTYPE    MdispZoom            (MIL_ID DisplayId,
                                              MIL_DOUBLE XFactor,
                                              MIL_DOUBLE YFactor);

MFTYPE32 void MFTYPE    MdispLut             (MIL_ID DisplayId,
                                              MIL_ID LutBufId);


#if M_MIL_USE_64BIT
// Prototypes for 64 bits OSs

MFTYPE32 void MFTYPE    MdispControlInt64        (MIL_ID DisplayId,
                                                  MIL_INT ControlType,
                                                  MIL_INT64 ControlValue);

MFTYPE32 void MFTYPE    MdispControlDouble       (MIL_ID DisplayId,
                                                  MIL_INT ControlType,
                                                  MIL_DOUBLE ControlValue);
#else
// Prototypes for 32 bits OSs

#define MdispControlDouble MdispControl
#define MdispControlInt64  MdispControl
MFTYPE32 void MFTYPE       MdispControl         (MIL_ID DisplayId,
                                                 MIL_INT ControlType,
                                                 MIL_DOUBLE ControlValue);
#endif


MFTYPE32 void MFTYPE    MdispUpdate         (MIL_ID DisplayId,
                                             MIL_INT OffsetX,
                                             MIL_INT OffsetY,
                                             MIL_INT SizeX,
                                             MIL_INT SizeY,
                                             MIL_INT ControlFlag
                                             );

MFTYPE32 MIL_INT MFTYPE    MdispGetHookInfo    (MIL_ID EventId,
                                             MIL_INT InfoType,
                                             void MPTYPE *UserPtr);

MFTYPE32 void MFTYPE    MdispSelectWindow    (MIL_ID DisplayId,
                                              MIL_ID ImageId,
                                              MIL_WINDOW_HANDLE ClientWindowHandle);


/* C++ directive if needed */
#ifdef __cplusplus
}
#endif


#if M_MIL_USE_64BIT
#ifdef __cplusplus

//////////////////////////////////////////////////////////////
// MdispControl function definition when compiling c++ files
//////////////////////////////////////////////////////////////
#if !M_MIL_USE_LINUX
inline void MdispControl(MIL_ID DisplayId,
                         MIL_INT ControlType,
                         int ControlValue)
   {
   MdispControlInt64(DisplayId, ControlType, ControlValue);
   };
#endif
inline void MdispControl(MIL_ID DisplayId,
                         MIL_INT ControlType,
                         MIL_INT32 ControlValue)
   {
   MdispControlInt64(DisplayId, ControlType, ControlValue);
   };

inline void MdispControl(MIL_ID DisplayId,
                         MIL_INT ControlType,
                         MIL_INT64 ControlValue)
   {
   MdispControlInt64(DisplayId, ControlType, ControlValue);
   };

inline void MdispControl(MIL_ID DisplayId,
                         MIL_INT ControlType,
                         MIL_DOUBLE ControlValue)
   {
   MdispControlDouble(DisplayId, ControlType, ControlValue);
   };

#else // __cplusplus

#define MdispControl MdispControlInt64

#endif // __cplusplus
#endif // M_MIL_USE_64BIT

//////////////////////////////////////////////////////////////
// SafeType functions.
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// See milos.h for explanation about these functions.
//////////////////////////////////////////////////////////////

// M_MIL_USE_SAFE_TYPE defined in milos.h.
#if M_MIL_USE_SAFE_TYPE

// ----------------------------------------------------------
// MdispInquire

inline MFTYPE32 MIL_INT MFTYPE MdispInquireUnsafe  (MIL_ID DisplayId, MIL_INT InquireType, void          MPTYPE *ResultPtr);
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, int                   ResultPtr);
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_TEXT_CHAR MPTYPE *ResultPtr);
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_INT       MPTYPE *ResultPtr);
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_DOUBLE    MPTYPE *ResultPtr);
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_UINT      MPTYPE *ResultPtr);
#endif
#if   M_MIL_USE_WINDOWS
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_WINDOW_HANDLE MPTYPE *ResultPtr);
#endif
#if !M_MIL_USE_64BIT
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_INT64     MPTYPE *ResultPtr);
#endif

inline MIL_INT MdispInquireRequiredType(MIL_INT InquireType)
   {
   if (M_IN_DISP_INQUIRE_MIL_ID_RANGE(InquireType))
      return M_TYPE_MIL_ID;

   if (M_IN_DISP_INQUIRE_DOUBLE_RANGE(InquireType))
      return M_TYPE_DOUBLE;

   if (M_IN_DISP_INQUIRE_STRING_RANGE(InquireType))
      return M_TYPE_TEXT_CHAR;

   if (M_IN_DISP_INQUIRE_MIL_INT64_RANGE(InquireType))
      return M_TYPE_MIL_INT64;

   return M_TYPE_MIL_INT;
   }

inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, int UserVarPtr)
   {
   if (UserVarPtr || M_DISP_INQUIRE_MUST_HAVE_USER_PTR(InquireType))
      SafeTypeError(MT("MdispInquire"));

   return MdispInquire(DisplayId, InquireType, NULL);
   }

inline MFTYPE32 MIL_INT MFTYPE MdispInquireExecute (MIL_ID DisplayId, MIL_INT InquireType, void       MPTYPE *ValuePtr, MIL_INT GivenType)
   {
   MIL_INT RequiredType = MdispInquireRequiredType(InquireType);
   ReplaceTypeMilIdByTypeMilIntXX(&RequiredType);

   if (RequiredType != GivenType)
      SafeTypeError(MT("MdispInquire"));

   return MdispInquire(DisplayId, InquireType, ValuePtr);
   }

inline MFTYPE32 MIL_INT MFTYPE MdispInquireUnsafe  (MIL_ID DisplayId, MIL_INT InquireType, void          MPTYPE *UserVarPtr) {return MdispInquire       (DisplayId, InquireType, UserVarPtr                  );}
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_TEXT_CHAR MPTYPE *UserVarPtr) {return MdispInquireExecute(DisplayId, InquireType, UserVarPtr, M_TYPE_TEXT_CHAR);}
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_INT       MPTYPE *UserVarPtr) {return MdispInquireExecute(DisplayId, InquireType, UserVarPtr, M_TYPE_MIL_INT  );}
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_DOUBLE    MPTYPE *UserVarPtr) {return MdispInquireExecute(DisplayId, InquireType, UserVarPtr, M_TYPE_DOUBLE   );}
#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_UINT      MPTYPE *UserVarPtr) {return MdispInquireExecute(DisplayId, InquireType, UserVarPtr, M_TYPE_MIL_INT  );}
#endif
#if !M_MIL_USE_64BIT
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_INT64     MPTYPE *UserVarPtr) {return MdispInquireExecute(DisplayId, InquireType, UserVarPtr, M_TYPE_MIL_INT64);}
#endif

#if   M_MIL_USE_WINDOWS
inline MFTYPE32 MIL_INT MFTYPE MdispInquireSafeType(MIL_ID DisplayId, MIL_INT InquireType, MIL_WINDOW_HANDLE MPTYPE *ResultPtr)
   {
   if (InquireType != M_WINDOW_HANDLE)
      SafeTypeError(MT("MdispInquire"));

   return MdispInquire(DisplayId, InquireType, ResultPtr);
   }
#endif

#define MdispInquire         MdispInquireSafeType

#else // #if M_MIL_USE_SAFE_TYPE

#define MdispInquireUnsafe         MdispInquire

#endif
