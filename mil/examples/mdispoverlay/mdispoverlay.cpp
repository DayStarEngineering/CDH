/*************************************************************************************/
/*
 * File name: MDispOverlay.c
 *
 * Synopsis:  This program shows how to display an image while creating
 *            text and graphics annotations on top of it using MIL
 *            graphic functions and windows GDI drawing under Windows.
 *            If the target system supports grabbing, the annotations
 *            are done on top of a continuous grab.
 *
 */
#include <mil.h>
#include <stdlib.h>
#include <X11/Xlib.h>

/* Target image. */
#define IMAGE_FILE     M_IMAGE_PATH MIL_TEXT("Board.mim")

/* Title for the display window. */
#define WINDOW_TITLE   MIL_TEXT("Custom Title")

/* Overlay drawing function prototype. */
void OverlayDraw(MIL_ID Display);

int main(void)
   {
   MIL_ID MilApplication,            /* Application identifier. */
      MilSystem,                 /* System identifier.      */
      MilDisplay,                /* Display identifier.     */
      MilDigitizer=0,            /* Digitizer identifier.   */
      MilImage;                  /* Image identifier.       */

   /* Allocate defaults */
   MappAllocDefault(M_SETUP, &MilApplication, &MilSystem, &MilDisplay, M_NULL, M_NULL);

   /* If the system have a digitizer, use it. */
   if (MsysInquire(MilSystem, M_DIGITIZER_NUM, M_NULL))
      {
      MdigAlloc(MilSystem, M_DEFAULT, MIL_TEXT("M_DEFAULT"), M_DEFAULT, &MilDigitizer);
      MbufAllocColor(MilSystem,
                     MdigInquire(MilDigitizer,M_SIZE_BAND,M_NULL),
                     MdigInquire(MilDigitizer,M_SIZE_X,M_NULL),
                     MdigInquire(MilDigitizer,M_SIZE_Y,M_NULL),
                     8+M_UNSIGNED,
                     M_IMAGE+M_DISP+M_PROC+M_GRAB,
                     &MilImage);
      MbufClear(MilImage, 0);
      }
   else
      {
      /* Restore a static image. */
      MbufRestore(IMAGE_FILE, MilSystem, &MilImage);
      }

   /* Change display window title. */
   MdispControl(MilDisplay, M_TITLE, M_PTR_TO_DOUBLE(WINDOW_TITLE));

   /* Display the image buffer. */
   MdispSelect(MilDisplay, MilImage);

   /* Draw text and graphics annotations in the display overlay. */
   OverlayDraw(MilDisplay);

   /* If the system supports it, grab continuously in the displayed image. */
   if (MilDigitizer)
      MdigGrabContinuous(MilDigitizer, MilImage);

   /* Pause to show the image. */
   printf("\nOVERLAY ANNOTATIONS:\n");
   printf("--------------------\n\n");
   printf("Displaying an image with overlay annotations.\n");
   printf("Press <Enter> to continue.\n\n");
   MosGetchar();

   /* Stop the continuous grab and free digitizer if needed. */
   if (MilDigitizer)
      {
      MdigHalt(MilDigitizer);
      MdigFree(MilDigitizer);

      /* Pause to show the result. */
      printf("Displaying the last grabbed image.\n");
      printf("Press <Enter> to end.\n\n");
      MosGetchar();
      }

   /* Free image. */
   MbufFree(MilImage);

   /* Free default allocations. */
   MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, M_NULL);

   return 0;	
   }


/* --------------------------------------------------------------- */
/* Name:      OverlayDraw
 * Synopsis:  This function draws annotations in the display overlay.
 */
void OverlayDraw(MIL_ID MilDisplay)
   {
   MIL_ID   MilOverlayImage;
   long     ImageWidth, ImageHeight;
   long     Count;
   MIL_TEXT_CHAR chText[80];
   
   Pixmap XPixmap=M_NULL;

   /* Prepare overlay buffer. */
   /***************************/

   /* Enable the display of overlay annotations. */
   MdispControl(MilDisplay, M_OVERLAY, M_ENABLE);

   /* Inquire the overlay buffer associated with the display. */
   MdispInquire(MilDisplay, M_OVERLAY_ID, &MilOverlayImage);

   /* Clear the overlay to transparent. */
   MdispControl(MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);

   /* Disable the overlay display update to accelerate annotations. */
   MdispControl(MilDisplay, M_OVERLAY_SHOW, M_DISABLE);

   /* Inquire overlay size. */
   ImageWidth  = MbufInquire(MilOverlayImage, M_SIZE_X, M_NULL);
   ImageHeight = MbufInquire(MilOverlayImage, M_SIZE_Y, M_NULL);

   /* Draw MIL overlay annotations. */
   /*********************************/

   /* Set the graphic text background to transparent. */
   MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);

   /* Print a white string in the overlay image buffer. */
   MgraColor(M_DEFAULT, M_COLOR_WHITE);
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth/9, ImageHeight/5,    MIL_TEXT(" -------------------- "));
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth/9, ImageHeight/5+25, MIL_TEXT(" - MIL Overlay Text - "));
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth/9, ImageHeight/5+50, MIL_TEXT(" -------------------- "));

   /* Print a green string in the overlay image buffer. */
   MgraColor(M_DEFAULT, M_COLOR_GREEN);
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth*11/18, ImageHeight/5,    MIL_TEXT(" ---------------------"));
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth*11/18, ImageHeight/5+25, MIL_TEXT(" - MIL Overlay Text - "));
   MgraText(M_DEFAULT, MilOverlayImage, ImageWidth*11/18, ImageHeight/5+50, MIL_TEXT(" ---------------------"));

   /* Re-enable the overlay display after all annotations are done. */
   MdispControl(MilDisplay, M_OVERLAY_SHOW, M_ENABLE);

   /* Draw GDI/XLIB color overlay annotation */
   /*************************************/

   /* Disable error printing for the inquire might not be supported */
   MappControl(M_ERROR, M_PRINT_DISABLE);

   /* Create an XPixmap to draw in the overlay buffer with XLib. */   
   MbufControl(MilOverlayImage, M_XPIXMAP_ALLOC, M_COMPENSATION_ENABLE);

   /* Inquire the XPixmap. */
   XPixmap=((Pixmap)MbufInquire(MilOverlayImage, M_XPIXMAP_HANDLE, M_NULL));


      if(XPixmap)
         {
         /* init X */
         Display *dpy = XOpenDisplay("");
         int screen = DefaultScreen(dpy);
         GC gc = XCreateGC(dpy,XPixmap,0,0);
         XColor xcolors[3],exact;
         XPoint Hor[2];
         XPoint Ver[2];
         int i;
         const char *color_names[] = {
            "red",
            "yellow",
            "blue",
         };
         
         /* allocate colors */
         for(i=0;i<3;i++)
            {
            if(!XAllocNamedColor(dpy,DefaultColormap(dpy,screen),color_names[i], &xcolors[i],&exact))
               {
               fprintf(stderr, "cant't alloc color %s\n", color_names[i]);
               exit (1);
               }
            }

         /* Write a blue cross. */
         XSetForeground(dpy,gc, xcolors[2].pixel);
         Hor[0].x = 0;
         Hor[0].y = ImageHeight/2;
         Hor[1].x = ImageWidth;
         Hor[1].y = ImageHeight/2;
         XDrawLines(dpy,XPixmap,gc,Hor, 2, CoordModeOrigin);

         Ver[0].x = ImageWidth/2;
         Ver[0].y = 0;
         Ver[1].x = ImageWidth/2;
         Ver[1].y = ImageHeight;
         XDrawLines(dpy,XPixmap,gc,Ver, 2, CoordModeOrigin);

         /* Write Red text. */
         XSetForeground(dpy,gc, xcolors[0].pixel);
         MosStrcpy(chText, 80, MIL_TEXT("X Overlay Text"));
         Count = MosStrlen(chText);
         XDrawString(dpy,XPixmap,gc,
                     ImageWidth*3/18, ImageHeight*17/24,
                     chText,Count);

          /* Write yellow text. */
         XSetForeground(dpy,gc, xcolors[1].pixel);
         XDrawString(dpy,XPixmap,gc,
                     ImageWidth*12/18, ImageHeight*17/24,
                     chText,Count);
         
         XSetForeground(dpy,gc, BlackPixel(dpy,screen));
         XFlush(dpy);
         XFreeGC(dpy,gc);
         XCloseDisplay(dpy);
      }

   /* Delete device context. */
   MbufControl(MilOverlayImage, M_XPIXMAP_FREE, M_DEFAULT);
   /* Signal MIL that the overlay buffer was modified. */
   MbufControl(MilOverlayImage, M_MODIFIED, M_DEFAULT);

}

