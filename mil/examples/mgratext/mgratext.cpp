/******************************************************************************/
/*
/* File name: MgraText.cpp
/*
/* Synopsis:  This program allocates a MIL application and system, then displays
/*            messages using TrueType fonts. It also shows how to check for errors.
*/
#include <mil.h>
#if M_MIL_USE_LINUX
#define TrueTypeFont1Regular       MIL_TEXT("Monospace")
#define TrueTypeFont1Italic        MIL_TEXT("Font1:Italic")
#define TrueTypeFont1Bold          MIL_TEXT("Font1:Bold")
#define TrueTypeFont1BoldItalic    MIL_TEXT("Font1:Bold:italic")
#define TrueTypeFont2Regular       MIL_TEXT("Font2")
/* Font1 and Font2 are fonts alias to system fonts */
#else
#define TrueTypeFont1Regular       MIL_TEXT("Arial")
#define TrueTypeFont1Italic        MIL_TEXT("Arial:Italic")
#define TrueTypeFont1Bold          MIL_TEXT("Arial:Bold")
#define TrueTypeFont1BoldItalic    MIL_TEXT("Arial:Bold:Italic")
#define TrueTypeFont2Regular       MIL_TEXT("Courier New")
#endif         

int MosMain(void)
{
   MIL_ID MilApplication,  /* Application identifier.  */
          MilSystem,       /* System identifier.       */
          MilDisplay,      /* Display identifier.      */
          MilImage;        /* Image buffer identifier. */

   /* Allocate a default MIL application, system, display and image. */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem, &MilDisplay, M_NULL, &MilImage);

   /* Perform graphic operations in the display image. */
   MgraColor(M_DEFAULT, 0xF0);
   MgraFont(M_DEFAULT, M_FONT_DEFAULT_LARGE);
   MgraText(M_DEFAULT, MilImage, 160L, 20L, MIL_TEXT(" Welcome to MIL !!! "));

   if (MsysInquire(MilSystem, M_SYSTEM_TYPE, M_NULL) != M_SYSTEM_ODYSSEY_TYPE)
      {
      MgraControl(M_DEFAULT,M_FONT_SIZE, 20);
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont1Regular));
      MgraText(M_DEFAULT, MilImage, 40L, 80L, MIL_TEXT("English"));

      MappControl(M_ERROR, M_PRINT_DISABLE);

      MgraControl(M_DEFAULT,M_FONT_SIZE, 30);
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont1Bold));
#if M_MIL_USE_LINUX
      MgraText(M_DEFAULT, MilImage, 40L, 140L, MIL_TEXT("FranÃ§ais"));
#else
      MgraText(M_DEFAULT, MilImage, 40L, 140L, MIL_TEXT("Français"));
#endif

      MgraControl(M_DEFAULT,M_FONT_SIZE, 40);
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont1Italic));
      MgraText(M_DEFAULT, MilImage, 40L, 220L, MIL_TEXT("Italiano"));

      MgraControl(M_DEFAULT,M_FONT_SIZE, 60);
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont1BoldItalic));
      MgraText(M_DEFAULT, MilImage, 40L ,300L, MIL_TEXT("Deutsch"));

      MgraControl(M_DEFAULT,M_FONT_SIZE, 70);
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont2Regular));
#if M_MIL_USE_LINUX
      MgraText(M_DEFAULT, MilImage, 40L ,380L, MIL_TEXT("EspaÃ±ol"));
#else
      MgraText(M_DEFAULT, MilImage, 40L ,380L, MIL_TEXT("Español"));
#endif

#if M_MIL_USE_TTF_UNICODE
      /* Draw Greek, Japanese and Korean*/
      MgraFont(M_DEFAULT, MIL_FONT_NAME(TrueTypeFont1Regular));
      MgraControl(M_DEFAULT,M_FONT_SIZE, 20);
      MgraText(M_DEFAULT, MilImage, 400L,  80L, MIL_TEXT("\u03b5\u03bb\u03bb\u03b7\u03bd\u03b9\u03ba"));

      MgraControl(M_DEFAULT,M_FONT_SIZE, 30);
      MgraText(M_DEFAULT, MilImage, 400L,  140L, MIL_TEXT("\ud55c\uad6d\uc5b4"));
      
      MgraControl(M_DEFAULT,M_FONT_SIZE, 40);
      MgraText(M_DEFAULT, MilImage, 400L, 220L, MIL_TEXT("\u65e5\u672c\u8a9e"));
      
      /* Draw Arabic and Hebrew */
      MgraControl(M_DEFAULT,M_TEXT_DIRECTION, M_RIGHT_TO_LEFT);
      MgraControl(M_DEFAULT,M_FONT_SIZE, 60);
      MgraText(M_DEFAULT, MilImage, 400L, 320L, MIL_TEXT("\u05e2\u05d1\u05e8\u05d9\u05ea"));
      
      MgraControl(M_DEFAULT,M_FONT_SIZE, 70);
      MgraText(M_DEFAULT, MilImage, 400L,  380L, MIL_TEXT("\ufecb\ufeae\ufe91\ufef2"));
 #endif     
      if(MappGetError(M_GLOBAL, 0) != M_NULL_ERROR)
         MosPrintf(MIL_TEXT("Some Unicode fonts are not available\n\n"));
      }
   else
      MosPrintf(MIL_TEXT("The TrueType text is not supported on Odyssey system.\n\n"));

   /* Wait for a key press. */
   MosPrintf(MIL_TEXT("Press <Enter> to end.\n"));
   MosGetch();

   /* Free defaults. */
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, MilImage);

   return 0;
}


 
 

 
