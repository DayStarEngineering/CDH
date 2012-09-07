#include <gtk/gtk.h>
#include <mil.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include "mdispgtkview.h"
#include "mdispgtk.h"
#include "childframe.h"

#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("BaboonRGB.mim")

// User pass his display connection to MIL to do annotations and ROI
#define USE_ANNOTATION 1

#if USE_ANNOTATION
// Do not grab display inside gtk libs
// this prevent Xserver freeze when annotation is enabled
#if (GTK_MAJOR_VERSION == 2 && GTK_MINOR_VERSION >= 18)
int XGrabServer(Display *dpy)   { return 1;}
int XUngrabServer(Display *dpy) { return 1;}
#endif
#endif



MIL_INT MFTYPE MouseFct(MIL_INT /*HookType*/, MIL_ID EventID, void MPTYPE *UserDataPtr)
   {
   MdispGtkView* pCurrentView = (MdispGtkView *)UserDataPtr;
   
   if(pCurrentView)
      {
      MOUSEPOSITION MousePosition;
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_X,         &MousePosition.m_DisplayPositionX);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_Y,         &MousePosition.m_DisplayPositionY);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_X,  &MousePosition.m_BufferPositionX);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_Y,  &MousePosition.m_BufferPositionY);

      pCurrentView->SetMousePosition(MousePosition);
      pCurrentView->UpdateStatusBarWithMousePosition();
      }
   return 0;
   }

MIL_INT ROIChangeEndFct(MIL_INT /*HookType*/, MIL_ID /*EventID*/, void MPTYPE *UserDataPtr)
   {
   MdispGtkView* pCurrentView = (MdispGtkView *)UserDataPtr;
   if(pCurrentView)
      {
      pCurrentView->UpdateROIWithCurrentState();
      }
   return 0;
   }

MIL_INT MFTYPE ROIChangeFct(MIL_INT /*HookType*/, MIL_ID /*EventID*/, void MPTYPE *UserDataPtr)
   {
   MdispGtkView *pCurrentView = (MdispGtkView *)UserDataPtr;
   if(pCurrentView)
      {
      MIL_ID DisplayID  = pCurrentView->m_MilDisplay;
      MIL_INT OffsetX   = MdispInquire(DisplayID, M_ROI_BUFFER_OFFSET_X, M_NULL);
      MIL_INT OffsetY   = MdispInquire(DisplayID, M_ROI_BUFFER_OFFSET_Y, M_NULL);
      MIL_INT SizeX     = MdispInquire(DisplayID, M_ROI_BUFFER_SIZE_X, M_NULL);
      MIL_INT SizeY     = MdispInquire(DisplayID, M_ROI_BUFFER_SIZE_Y, M_NULL);
      pCurrentView->UpdateStatusBarWithROI(OffsetX, OffsetY, SizeX, SizeY);
      }
   return 0;
   }

MdispGtkView::MdispGtkView(ChildFrame* cf)
   {
   m_cf                         = cf;
   m_Modified                   = false;
   m_window                     = cf->DrawingArea();
   m_MilOverlayImage            = M_NULL;   // Overlay image buffer identifier
   m_MilDisplay                 = M_NULL;   // Display identifier.
   m_MilGraphContext            = M_NULL;
   m_MilGraphList               = M_NULL;

   static int viewNumber = 0;
   m_filename = g_strdup_printf("Image%d.mim",++viewNumber);


   m_currentZoomFactor          = 1.0;
   m_isWindowed                 = true;
   m_isExclusive                = false;
   m_isOverlayEnabled           = false;    // Overlay state
   m_isOverlayInitialized       = false;
   m_isFillDisplayEnabled       = false;
   m_isX11AnnotationsEnabled    = false;
   m_isGraphicsAnnotationsEnabled = false;
   m_isNoTearingEnabled         = false;
   m_currentInterpolationMode   = M_NEAREST_NEIGHBOR;
   m_currentViewMode            = M_TRANSPARENT;
   m_currentShiftValue          = M_NULL;
   m_isInROIDefineMode          = false;
   m_isInROIShowMode            = false;
   m_isROISupported             = false;
   m_isInAsynchronousMode          = false;
   m_currentCompressionType        = M_NULL;
   m_currentAsynchronousFrameRate  = M_INFINITE;
   m_currentQFactor                = M_DEFAULT;
   m_currentRestrictCursor         = M_ENABLE;

   m_FrameTimeOutTag            = g_timeout_add(500,MdispGtkView::timerEvent,this);

   m_imageSizeX                = DEFAULTSIZEX;
   m_imageSizeY                = DEFAULTSIZEY;

   // Allocation another XDisplay Connection ( used for Window annotation)
   m_XDisplay                  = XOpenDisplay("");

   XColor exact, AnnotationColor;
   if(!XAllocNamedColor(m_XDisplay, DefaultColormap(m_XDisplay,DefaultScreen(m_XDisplay)),"green", &AnnotationColor, &exact))
      m_AnnotationColorPixel = BlackPixel(m_XDisplay,DefaultScreen(m_XDisplay));
   else
      m_AnnotationColorPixel = AnnotationColor.pixel;

   XFlush(m_XDisplay);


   UpdateContentSize();

   }

MdispGtkView::~MdispGtkView()
   {
   // Halt the grab, deselected the display, free the display and the image buffer
   // only if MbufAlloc was successful
   if (m_MilImage)
      {
      // Make sure display is deselected and grab is halt
      RemoveFromDisplay();

      // Free image buffer [CALL TO MIL]
      MbufFree(m_MilImage);
      }

   // remove timer
   g_source_remove(m_FrameTimeOutTag);
   
   // Close Annotation XDisplay
   if(m_XDisplay)
      XCloseDisplay(m_XDisplay);
   }

MdispGtkApp* MdispGtkView::dispGtkApp()
   {
   void *UserData = g_object_get_data(G_OBJECT(m_window),"App");
   return (MdispGtkApp *) UserData;
   }

void MdispGtkView::GrabStart()
   {
   // TODO: Add your command handler code here
	
	/////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab start
	/////////////////////////////////////////////////////////////////////////

   // If there is a grab in a view, halt the grab before starting a new one
   if(((MdispGtkApp*)dispGtkApp())->m_isGrabStarted)
      ((MdispGtkApp*)dispGtkApp())->m_pGrabView->GrabStop();

   // Start a continuous grab in this view
   MdigGrabContinuous(((MdispGtkApp*)dispGtkApp())->m_MilDigitizer, m_MilImage);

   // Update the variable GrabIsStarted
   ((MdispGtkApp*)dispGtkApp())->m_isGrabStarted = true;

   // GrabInViewPtr is now a pointer to m_pGrabView view
   ((MdispGtkApp*)dispGtkApp())->m_pGrabView = this;

   // Document has been modified
   m_Modified = true;

	/////////////////////////////////////////////////////////////////////////	
	// MIL: Write code that will be executed on a grab start
	/////////////////////////////////////////////////////////////////////////

   }
void MdispGtkView::GrabStop()
   {
   // TODO: Add your command handler code here
 
   /////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab stop 
	/////////////////////////////////////////////////////////////////////////
   // Halt the grab
   MdigHalt(((MdispGtkApp*)dispGtkApp())->m_MilDigitizer);
   ((MdispGtkApp*)dispGtkApp())->m_isGrabStarted = false;

   /////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab stop 
	/////////////////////////////////////////////////////////////////////////

   }

void MdispGtkView::Overlay(bool on)
   {
   // Enable overlay
   if (on && !m_isOverlayEnabled)
      {
      MdispControl(m_MilDisplay, M_OVERLAY, M_ENABLE);

      //If overlay buffer as not been initialized yet, do it now.
      if(!m_isOverlayInitialized)
         InitializeOverlay();

      m_isOverlayEnabled = true;
      }

   // Disable overlay
   else if (!on && m_isOverlayEnabled)
      {
      // Disable the overlay display. [CALL TO MIL]
      MdispControl(m_MilDisplay, M_OVERLAY, M_DISABLE);

      m_isOverlayInitialized = false;
      m_isOverlayEnabled     = false;
      }

   /////////////////////////////////////////////////////////////////////////
   // MIL: Write code that will be executed when 'add overlay' is selected
   /////////////////////////////////////////////////////////////////////////
   }



void MdispGtkView::Initialize()
   {
   // Allocate a display [CALL TO MIL]
   MdispAlloc(((MdispGtkApp*)dispGtkApp())->m_MilSystem, M_DEFAULT, "M_DEFAULT", M_DEFAULT, &m_MilDisplay);

   if(m_MilDisplay)
      {
      MIL_INT DisplayType = MdispInquire(m_MilDisplay, M_DISPLAY_TYPE, M_NULL);
      
      // Check display type [CALL TO MIL]
      if((DisplayType&(M_WINDOWED|M_EXCLUSIVE)) !=M_WINDOWED)
         m_isWindowed = false;

      if(DisplayType&(M_EXCLUSIVE))
         m_isExclusive = true;

      // ROI are supported with windowed display
       m_isROISupported = (DisplayType&M_WINDOWED) != 0;

      // Initially set interpolation mode and view mode to default
      ChangeInterpolationMode(M_DEFAULT);
      ChangeViewMode(M_DEFAULT);
       
      if(m_isWindowed)
         {
#if USE_ANNOTATION
         // The connection to the X display must be given to Mil so it
         // can update the window when ROI is enabled
         MdispControl(m_MilDisplay,M_WINDOW_ANNOTATIONS,M_PTR_TO_DOUBLE(GDK_WINDOW_XDISPLAY(m_window->window)));
#else
         m_isROISupported = false;
#endif
         }
      
      if(m_isROISupported)
         {
         
         // Set ROI-show mode.
         ROIShow(m_isInROIShowMode);
 	      
         // Install hooks for ROI info in status bar and to keep current status
         // in toolbar
         MdispHookFunction(m_MilDisplay, M_ROI_CHANGE, ROIChangeFct, (void*)this);
         MdispHookFunction(m_MilDisplay, M_ROI_CHANGE_END, ROIChangeEndFct, (void*)this);
         }

      if(IsNetworkedSystem())
         {
         // Check compression type [CALL TO MIL]
         MdispInquire(m_MilDisplay, M_COMPRESSION_TYPE, &m_currentCompressionType);
         
         // Check asynchronous mode [CALL TO MIL]
         m_isInAsynchronousMode = (MdispInquire(m_MilDisplay, M_ASYNC_UPDATE, M_NULL) == M_ENABLE);

         // Check asynchronous frame rate [CALL TO MIL]
         MdispInquire(m_MilDisplay, M_UPDATE_RATE_MAX, &m_currentAsynchronousFrameRate);
         
         // Check Q factor [CALL TO MIL]
         MdispInquire(m_MilDisplay, M_Q_FACTOR, &m_currentQFactor);
         }

      if(m_isExclusive)
         {
         MdispInquire(m_MilDisplay, M_RESTRICT_CURSOR,    &m_currentRestrictCursor);
         }

      //Select the buffer from it's display object and given window [CALL TO MIL]
      MdispSelectWindow(m_MilDisplay, m_MilImage, m_isWindowed?GDK_WINDOW_XID(m_window->window):0);
      
      }

   // Hook a function to mouse-movement event, to update cursor position in status bar.
   MdispHookFunction(m_MilDisplay, M_MOUSE_MOVE, MouseFct, (void*)this);

   /////////////////////////////////////////////////////////////////////////
   // MIL: Code that will be executed when a view is first attached to the document
   /////////////////////////////////////////////////////////////////////////
   }

void MdispGtkView::RemoveFromDisplay()
   {
   //Halt grab if in process in THIS view
   if ((((MdispGtkApp*)dispGtkApp())->m_pGrabView == this) &&
       ((MdispGtkApp*)dispGtkApp())->m_isGrabStarted)
      {
      //Ask the digitizer to halt the grab [CALL TO MIL]
      MdigHalt(((MdispGtkApp*)dispGtkApp())->m_MilDigitizer);

      ((MdispGtkApp*)dispGtkApp())->m_isGrabStarted = false;
      }

   if (m_MilImage && m_MilDisplay)
      {
      //Deselect the buffer from it's display object and given window [CALL TO MIL]
      MdispDeselect(m_MilDisplay,m_MilImage);

      if(m_isROISupported)
         {
         // Uninstall hooks for ROI info in status bar and to keep current status
         // in toolbar [CALL TO MIL]
         MdispHookFunction(m_MilDisplay, M_ROI_CHANGE+M_UNHOOK, ROIChangeFct, (void*)this);
         MdispHookFunction(m_MilDisplay, M_ROI_CHANGE_END+M_UNHOOK, ROIChangeEndFct, (void*)this);
         }


      // Hook from mouse-movement event.
      MdispHookFunction(m_MilDisplay, M_MOUSE_MOVE+M_UNHOOK, MouseFct, (void*)this);

      //Free the display [CALL TO MIL]
      if(m_MilGraphList)
         {
         MgraFree(m_MilGraphList);
         m_MilGraphList = M_NULL;
         }
      if(m_MilGraphContext)
         {
         MgraFree(m_MilGraphContext);
         m_MilGraphContext = M_NULL;
         }
      
      //Free the display [CALL TO MIL]
      MdispFree(m_MilDisplay);
      m_MilDisplay = M_NULL;
      }
   }
bool MdispGtkView::newDoc()
   {
    // Set buffer attributes
   if(((MdispGtkApp*)dispGtkApp())->m_numberOfDigitizer)
      {
      m_bufferAttributes=M_IMAGE+M_DISP+M_GRAB+M_PROC;
      m_imageSizeX = ((MdispGtkApp*)dispGtkApp())->m_digitizerSizeX;
      m_imageSizeY = ((MdispGtkApp*)dispGtkApp())->m_digitizerSizeY;
      m_NbBands    = ((MdispGtkApp*)dispGtkApp())->m_digitizerNbBands;

      // Allocate a buffer [CALL TO MIL]
      MbufAllocColor(((MdispGtkApp*)dispGtkApp())->m_MilSystem,
                     m_NbBands,
                     m_imageSizeX,
                     m_imageSizeY,
                     M_DEF_IMAGE_TYPE,
                     m_bufferAttributes,
                     &m_MilImage);

      // Clear the buffer [CALL TO MIL] 
      MbufClear(m_MilImage,M_COLOR_BLACK);
      }
   else
      {
      //Import image in buffer [CALL TO MIL]
      MbufImport(IMAGE_FILE,M_DEFAULT,M_RESTORE,((MdispGtkApp*)dispGtkApp())->m_MilSystem,&m_MilImage);

      // Set SizeX and SizeY variable to the size of the buffer [CALL TO MIL]
      if (m_MilImage) 
         {
         m_imageSizeX   = MbufInquire(m_MilImage, M_SIZE_X, M_NULL);
         m_imageSizeY   = MbufInquire(m_MilImage, M_SIZE_Y, M_NULL);
         m_NbBands      = MbufInquire(m_MilImage, M_SIZE_BAND, M_NULL);
         }
      }

   UpdateContentSize();

   // If not able to allocate a buffer, do not create a new document
   if(!m_MilImage)
      return false;

   Initialize();

   return true;
   }

bool MdispGtkView::load(const char *filename)
   {
   //Import image in buffer [CALL TO MIL]
   MbufImport(filename,M_DEFAULT,M_RESTORE,((MdispGtkApp*)dispGtkApp())->m_MilSystem,&m_MilImage);

   // Set SizeX and SizeY variable to the size of the buffer [CALL TO MIL]
   if (m_MilImage)
      {
      Initialize();
      m_imageSizeX = MbufInquire(m_MilImage,M_SIZE_X,M_NULL);
      m_imageSizeY = MbufInquire(m_MilImage,M_SIZE_Y,M_NULL);
      m_filename = g_strdup(g_path_get_basename(filename));
      UpdateContentSize();
      return true;
      }
   else
      {
      return false;
      }
   }

bool MdispGtkView::save(const char *filename)
   {
   gboolean SaveStatus;
   gchar * TempPath;
   long FileFormat = M_MIL;
   gchar *tmp;
   
   // Get extension for file format determination
   TempPath = g_ascii_strup(filename,-1);
   //Set the file format to M_MIL when the filepath extension is ".MIM"
   if (g_str_has_suffix(TempPath,".MIM"))
      FileFormat = M_MIL;
   //Set the file format to M_TIFF when the filepath extension is ".TIF"
   else if (g_str_has_suffix(TempPath,".TIF"))
      FileFormat = M_TIFF;
   //Set the file format to M_BMP when the filepath extension is ".BMP"
   else if (g_str_has_suffix(TempPath,".BMP"))
      FileFormat = M_BMP;
   //Set the file format to M_JPEG_LOSSY when the filepath extension is ".JPG"
   else if (g_str_has_suffix(TempPath,".JPG"))
      FileFormat = M_JPEG_LOSSY;
   //Set the file format to M_JPEG2000_LOSSLESS when the filepath extension is ".JP2"
   else if (g_str_has_suffix(TempPath,".JP2"))
      FileFormat = M_JPEG2000_LOSSLESS;
   //Set the file format to M_RAW when the filepath extension is ".RAW"
   else if (g_str_has_suffix(TempPath,".RAW"))
      FileFormat = M_RAW;
   
   // Halt the grab if the current view has it [CALL TO MIL]
   if((((MdispGtkApp*)dispGtkApp())->m_pGrabView == this) &&
      (((MdispGtkApp*)dispGtkApp())->m_isGrabStarted == true))
      MdigHalt(((MdispGtkApp*)dispGtkApp())->m_MilDigitizer);
   
   // Save the current buffer [CALL TO MIL]
   tmp = g_strdup(filename); 
   MbufExport(tmp, FileFormat,m_MilImage);
   g_free(tmp);
   
   // Verify if save operation was successful [CALL TO MIL]
   SaveStatus = (MappGetError(M_CURRENT,M_NULL) == M_NULL_ERROR);

   // Document has been saved
   if (!((((MdispGtkApp*)dispGtkApp())->m_pGrabView == this) &&
         (((MdispGtkApp*)dispGtkApp())->m_isGrabStarted == true)))
      m_Modified = false;

   // Restart the grab if the current view had it [CALL TO MIL]
   if((((MdispGtkApp*)dispGtkApp())->m_pGrabView == this) &&
      (((MdispGtkApp*)dispGtkApp())->m_isGrabStarted == true))
      MdigGrabContinuous(((MdispGtkApp*)dispGtkApp())->m_MilDigitizer, m_MilImage);

   return SaveStatus;

   }

   
bool MdispGtkView::saveROIAs(const char *filename)
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Get current ROI in buffer-related coordinates.
   /////////////////////////////////////////////////////////////////////////
   MIL_INT OffsetX   = MdispInquire(m_MilDisplay, M_ROI_BUFFER_OFFSET_X, M_NULL);
   MIL_INT OffsetY   = MdispInquire(m_MilDisplay, M_ROI_BUFFER_OFFSET_Y, M_NULL);
   MIL_INT SizeX     = MdispInquire(m_MilDisplay, M_ROI_BUFFER_SIZE_X, M_NULL);
   MIL_INT SizeY     = MdispInquire(m_MilDisplay, M_ROI_BUFFER_SIZE_Y, M_NULL);
      
   /////////////////////////////////////////////////////////////////////////
   // MIL: Create a child of the selected buffer, with the ROI coordinates.
   /////////////////////////////////////////////////////////////////////////
   MIL_ID ChildBuffer = MbufChildColor2d(m_MilImage,
                                         M_ALL_BANDS, 
                                         OffsetX, 
                                         OffsetY, 
                                         SizeX, 
                                         SizeY,
                                         M_NULL);

   /////////////////////////////////////////////////////////////////////////
   // MIL: Save the buffer in the path given by the user.
   /////////////////////////////////////////////////////////////////////////
   MbufSave(filename, ChildBuffer);
   MbufFree(ChildBuffer);
   return true;
   }


void MdispGtkView::ChangeInterpolationMode(long InterpolationMode)
   {
   if(m_MilDisplay)
      {
      //Apply interpolation mode on display [CALL TO MIL]
      MdispControl(m_MilDisplay, M_INTERPOLATION_MODE, InterpolationMode);

      //Check if control worked correctly before considering it as successful [CALL TO MIL]
      if(MdispInquire(m_MilDisplay, M_INTERPOLATION_MODE,M_NULL)==InterpolationMode)
         {
         //Make sure Interpolation Mode combo box shows current interpolation mode
         m_currentInterpolationMode = InterpolationMode;
         }
      }
   }

void MdispGtkView::ChangeViewMode(long ViewMode,long ShiftValue)
   {
   if(m_MilDisplay)
      {
      //Apply view mode on display [CALL TO MIL]
      MdispControl(m_MilDisplay, M_VIEW_MODE, ViewMode);

      if(ViewMode == M_BIT_SHIFT)
         MdispControl(m_MilDisplay, M_VIEW_BIT_SHIFT, ShiftValue);

      //Check if control worked correctly before considering it as successful [CALL TO MIL]
      if(MdispInquire(m_MilDisplay, M_VIEW_MODE,M_NULL)==ViewMode)
         {
         //Make sure ViewMode Mode combo box shows current interpolation mode
         m_currentViewMode   = ViewMode;
         m_currentShiftValue = ShiftValue;
         }
      }
   }

void MdispGtkView::ChangeCompressionType(MIL_INT CompressionType)
   {
   if(m_MilDisplay)
      {
      // Apply compression type to display [CALL TO MIL]
      MdispControl(m_MilDisplay, M_COMPRESSION_TYPE, CompressionType);
   
      // Check if control worked correctly before considering it successful [CALL TO MIL]
      if(MdispInquire(m_MilDisplay, M_COMPRESSION_TYPE, M_NULL) == CompressionType)
         {
         m_currentCompressionType = CompressionType;
         }
      }
   }

void MdispGtkView::ChangeAsynchronousMode(bool Enabled, MIL_INT FrameRate)
   {
   if(Enabled && (FrameRate != m_currentAsynchronousFrameRate))
      {
      if(m_MilDisplay)
         {
         // Apply asynchronous frame rate to display [CALL TO MIL]
         MdispControl(m_MilDisplay, M_UPDATE_RATE_MAX, FrameRate);
      
         // Check if control worked correctly before considering it successful [CALL TO MIL]
         if(MdispInquire(m_MilDisplay, M_UPDATE_RATE_MAX, M_NULL) == FrameRate)
            {
            m_currentAsynchronousFrameRate = FrameRate;
            }
         }
      }

   if((Enabled && !m_isInAsynchronousMode) ||
      (!Enabled && m_isInAsynchronousMode))
      {
      if(m_MilDisplay)
         {
         // Apply asynchronous update to display [CALL TO MIL]
         MdispControl(m_MilDisplay, M_ASYNC_UPDATE, (Enabled ? M_ENABLE : M_DISABLE));
      
         // Check if control worked correctly before considering it successful [CALL TO MIL]
         if(MdispInquire(m_MilDisplay, M_ASYNC_UPDATE, M_NULL) == (Enabled ? M_ENABLE : M_DISABLE))
            {
            m_isInAsynchronousMode = Enabled;
            }
         }
      }
   }

void MdispGtkView::ChangeQFactor(MIL_INT QFactor)
   {
   if(m_MilDisplay)
      {
      // Apply Q factor to display [CALL TO MIL]
      MdispControl(m_MilDisplay, M_Q_FACTOR, QFactor);
   
      // Check if control worked correctly before considering it successful [CALL TO MIL]
      if(MdispInquire(m_MilDisplay, M_Q_FACTOR, M_NULL) == QFactor)
         {
         m_currentQFactor = QFactor;
         }
      }
   }

bool MdispGtkView::IsNetworkedSystem()
   {
   bool NetworkedSystem = false;
   MIL_ID SystemId = ((MdispGtkApp*)dispGtkApp())->m_MilSystem;

   // Check if system is networked (DistributedMIL) [CALL TO MIL]
   if(SystemId)
      NetworkedSystem = (MsysInquire(SystemId, M_NETWORKED, M_NULL) == M_YES);

   return NetworkedSystem;
   }

void MdispGtkView::ZoomIn()
   {
   //Perform zooming with MIL (using MdispZoom)
   Zoom( m_currentZoomFactor * 2.0 );
   }

void MdispGtkView::ZoomOut()
   {
   //Perform zooming with MIL (using MdispZoom)
   Zoom( m_currentZoomFactor / 2.0 );
   }

void MdispGtkView::NoZoom()
   {
   //Perform zooming with MIL
   Zoom(1.0);
   }

void MdispGtkView::Zoom( MIL_DOUBLE ZoomFactorToApply )
   {
   if( m_MilDisplay
         && ZoomFactorToApply <= 16.0 && ZoomFactorToApply >= 1.0/16.0 )
      {
      if (m_currentZoomFactor != ZoomFactorToApply)
         {
         //Apply zoom  [CALL TO MIL]
         MdispZoom(m_MilDisplay, ZoomFactorToApply, ZoomFactorToApply);
         
         m_currentZoomFactor = ZoomFactorToApply;
         
         //Update scroll bars
         m_cf->UpdateScrollBar();
         g_signal_emit(G_OBJECT(m_cf->Window()), m_cf->zoomFactorChangedSignal(), 0, m_currentZoomFactor);
         }
      }
   }
void MdispGtkView::NoTearing( bool on )
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write code that will be executed when 'No Tearing' button or menu is clicked
   /////////////////////////////////////////////////////////////////////////

   // No Notearing in windowed mode in linux
   if(m_isWindowed)
      return;

   if(m_MilDisplay)
      {
      //Enable/disable No-Tearing mode on display [CALL TO MIL]
      MdispControl(m_MilDisplay, M_NO_TEARING, on ? M_ENABLE : M_DISABLE);

      //Check if it worked before considering it as enabled [CALL TO MIL]
      if(MdispInquire(m_MilDisplay, M_NO_TEARING, M_NULL) == on ? M_ENABLE : M_DISABLE)
         {
         m_isNoTearingEnabled = on;
         }
      }
   }   
void MdispGtkView::FillDisplay( bool on )
   {
   if(m_MilDisplay)
      {
      // Fill display is incompatible with pan.
      pan( 0, 0 );
      if(on)
         {
         // disable temporary using user's XDisplay
         // filldisplay can generate excessive expose ( paint) event
         // this can freeze main menu window 
         MdispControl(m_MilDisplay,M_WINDOW_ANNOTATIONS,M_NULL);
         }
      else
         {
         MdispControl(m_MilDisplay,M_WINDOW_ANNOTATIONS,M_PTR_TO_DOUBLE(GDK_WINDOW_XDISPLAY(m_window->window)));
         }
      //Using MIL, enable/disable Fill Display Mode [CALL TO MIL]
      MdispControl(m_MilDisplay, M_FILL_DISPLAY, on ? M_ENABLE : M_DISABLE);

      m_isFillDisplayEnabled = on;

      UpdateContentSize();
      }
   }
void MdispGtkView::X11Annotations( bool on )
   {
   m_isX11AnnotationsEnabled = on;
   if(on)
      {
      gtk_widget_queue_draw_area(m_window,0,0,1,1);
      }
   // make sur the window is mapped
   else if(m_window->window)
      {
      XEvent ev;
      ev.type = Expose;
      ev.xexpose.window = GDK_WINDOW_XID(m_window->window);
      ev.xexpose.x = 0;
      ev.xexpose.y = 0;
      ev.xexpose.width  = m_window->allocation.width;
      ev.xexpose.height = m_window->allocation.height;
      XSendEvent(GDK_WINDOW_XDISPLAY(m_window->window),GDK_WINDOW_XID(m_window->window), true, ExposureMask, &ev);
      }
	
   }

void MdispGtkView::GraphicsAnnotations( bool on )
   {
   if(m_MilDisplay)
      {
      m_isGraphicsAnnotationsEnabled = on;
      
      if(m_isGraphicsAnnotationsEnabled)
         {
         if(!m_MilGraphContext && !m_MilGraphList)
            {
            MIL_INT BufSizeX  = 0, BufSizeY = 0;
            MIL_INT LogoCellSize = 12;
            MIL_INT LogoSize  = 6 * LogoCellSize;
            MIL_INT Offset    = 10;

            MgraAlloc(((MdispGtkApp*)dispGtkApp())->m_MilSystem, &m_MilGraphContext);
            MgraAllocList(((MdispGtkApp*)dispGtkApp())->m_MilSystem, M_DEFAULT, &m_MilGraphList);
            MdispControl(m_MilDisplay, M_DISPLAY_GRAPHIC_LIST, m_MilGraphList);

            MdispControl(m_MilDisplay, M_UPDATE_GRAPHIC_LIST, M_DISABLE);
            MbufInquire(m_MilImage, M_SIZE_X, &BufSizeX);
            MbufInquire(m_MilImage, M_SIZE_Y, &BufSizeY);

            MgraClear(m_MilGraphContext, m_MilGraphList);

            GraphicLogo(Offset                 , Offset           , LogoCellSize);
            GraphicLogo(BufSizeX - (LogoSize/2), Offset           , LogoCellSize);
            GraphicLogo(Offset                 , BufSizeY + Offset, LogoCellSize);

            MgraColor(m_MilGraphContext, M_COLOR_LIGHT_BLUE);
            MgraLine(m_MilGraphContext, m_MilGraphList, Offset + (LogoSize/2), Offset + LogoSize, Offset + LogoSize/2, BufSizeY + Offset);
            MgraLine(m_MilGraphContext, m_MilGraphList, Offset + LogoSize,  Offset + (LogoSize/2), BufSizeX - (LogoSize/2), Offset + (LogoSize/2));

            MgraColor(m_MilGraphContext, M_COLOR_GRAY);
            MgraText(m_MilGraphContext, m_MilGraphList, Offset, (2*Offset)+LogoSize, MT("Mil Graphic"));
            MgraText(m_MilGraphContext, m_MilGraphList, Offset, (4*Offset)+LogoSize, MT("Annotations"));

            MdispControl(m_MilDisplay, M_UPDATE_GRAPHIC_LIST, M_ENABLE);
            }
         }
      else
         {
         MdispControl(m_MilDisplay, M_DISPLAY_GRAPHIC_LIST, M_NULL);
         
         if(m_MilGraphList)
            {
            MgraFree(m_MilGraphList);
            m_MilGraphList = M_NULL;
            }
         if(m_MilGraphContext)
            {
            MgraFree(m_MilGraphContext);
            m_MilGraphContext = M_NULL;
            }
         }
      }
   }

void MdispGtkView::pan( int x, int y )
   {
   if (m_MilDisplay)
      {
      //Apply a pan on display to scroll the image in window, according to scroll position
      MdispPan( m_MilDisplay, x / m_currentZoomFactor, y / m_currentZoomFactor );
      }
   }


void MdispGtkView::InitializeOverlay()
   {
   MIL_TEXT_CHAR chText[80]; 

   // Initialize overlay if not already done
   if ((!m_isOverlayInitialized) && (m_MilDisplay))
      {
      //Only do it on a valid windowed display [CALL TO MIL]
      if (m_MilImage && m_MilDisplay )
         {
         // Prepare overlay buffer //
         ////////////////////////////

         // Enable display overlay annotations.
         MdispControl(m_MilDisplay, M_OVERLAY, M_ENABLE);

         // Inquire the Overlay buffer associated with the displayed buffer [CALL TO MIL]
         MdispInquire(m_MilDisplay, M_OVERLAY_ID, &m_MilOverlayImage);

         // Clear the overlay to transparent.
         MdispControl(m_MilDisplay, M_OVERLAY_CLEAR, M_DEFAULT);
         
         // Disable the overlay display update to accelerate annotations.
         MdispControl(m_MilDisplay, M_OVERLAY_SHOW, M_DISABLE);


         // Draw MIL monochrome overlay annotation *
         //*****************************************

         // Inquire MilOverlayImage size x and y [CALL TO MIL]
         long imageWidth  = MbufInquire(m_MilOverlayImage,M_SIZE_X,M_NULL);
         long imageHeight = MbufInquire(m_MilOverlayImage,M_SIZE_Y,M_NULL);

         // Set graphic text to transparent background. [CALL TO MIL]
         MgraControl(M_DEFAULT, M_BACKGROUND_MODE, M_TRANSPARENT);

         // Set drawing color to white. [CALL TO MIL]
         MgraColor(M_DEFAULT, M_COLOR_WHITE);

         // Print a string in the overlay image buffer. [CALL TO MIL]
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageHeight/5,    " -------------------- ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageHeight/5+25, " - MIL Overlay Text - ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageHeight/5+50, " -------------------- ");

         // Print a green string in the green component overlay image buffer. [CALL TO MIL]
         MgraColor(M_DEFAULT, M_COLOR_GREEN);
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth*11/18, imageHeight/5,    " -------------------- ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth*11/18, imageHeight/5+25, " - MIL Overlay Text - ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth*11/18, imageHeight/5+50, " -------------------- ");

         // Draw GDI color overlay annotation *
         //************************************

         // Disable hook to MIL error because control might not be supported
         MappControl(M_ERROR_HOOKS, M_DISABLE);

         // Create a device context to draw in the overlay buffer with GDI.  [CALL TO MIL]
         MbufControl(m_MilOverlayImage, M_XPIXMAP_ALLOC, M_COMPENSATION_ENABLE);

         // Reenable hook to MIL error
         MappControl(M_ERROR_HOOKS, M_ENABLE);

         // Retrieve the XPIXMAP of the overlay [CALL TO MIL]
         Pixmap XPixmap = (Pixmap)MbufInquire(m_MilOverlayImage, M_XPIXMAP_HANDLE, M_NULL);

         /* convert it to gdkpixmap */
         GdkPixmap *gdkpixmap = gdk_pixmap_foreign_new(XPixmap);
            
         if(gdkpixmap)
            {
            GdkPoint Hor[2];
            GdkPoint Ver[2];
            GdkColor color[3];               
            GdkFont *font = NULL;
            font = gdk_font_load ("-misc-*-*-r-*-*-*-140-*-*-*-*-*-1");
            int i;
            
            /* get graphic context from pixmap*/
            GdkGC *gc = gdk_gc_new(gdkpixmap);
            
            /* allocate colors */
            gdk_color_parse("blue",&color[0]);
            gdk_color_parse("red",&color[1]);
            gdk_color_parse("yellow",&color[2]);
            for(i=0;i<3;i++)
               gdk_color_alloc(gdk_colormap_get_system(), &color[i]);
            
            /* set the foreground to our color */
            gdk_gc_set_foreground(gc, &color[0]);
            // Draw a blue cross in the overlay buffer.
            Hor[0].x = 0;
            Hor[0].y = imageHeight/2;
            Hor[1].x = imageWidth;
            Hor[1].y = imageHeight/2;
            gdk_draw_lines(gdkpixmap,gc,Hor,2);
            
            Ver[0].x = imageWidth/2;
            Ver[0].y = 0;
            Ver[1].x = imageWidth/2;
            Ver[1].y = imageHeight;
            gdk_draw_lines(gdkpixmap,gc,Ver,2);
            

            // Write Red text in the overlay buffer. 
            MosStrcpy(chText, 80, "X Overlay Text "); 
            gdk_gc_set_foreground(gc, &color[1]);
            gdk_draw_string(gdkpixmap, 
                            font,
                            gc, 
                            imageWidth*3/18,
                            imageHeight*4/6,
                            chText);
            
            // Write Yellow text in the overlay buffer. 
            gdk_gc_set_foreground(gc, &color[2]);
            gdk_draw_string(gdkpixmap, 
                            font,
                            gc, 
                            imageWidth*12/18,
                            imageHeight*4/6,
                            chText);
            
            /* flush */
            gdk_display_flush(gdk_display_get_default());
            
            /* Free graphic context.*/
            g_object_unref(gc);

            // Delete created Pixmap.  [CALL TO MIL]
            MbufControl(m_MilOverlayImage, M_XPIXMAP_FREE, M_DEFAULT);
            
            // Signal MIL that the overlay buffer was modified. [CALL TO MIL]
            MbufControl(m_MilOverlayImage, M_MODIFIED, M_DEFAULT);
            }

         // Now that overlay buffer is correctly prepared, we can show it [CALL TO MIL]
         MdispControl(m_MilDisplay, M_OVERLAY_SHOW, M_ENABLE);

         // Overlay is now initialized
         m_isOverlayInitialized = true;
         }
      }
   }


gboolean MdispGtkView::timerEvent(gpointer user_data)
   {
   MdispGtkView* pCurrentView = (MdispGtkView *) user_data;
   if(pCurrentView && pCurrentView->m_MilDisplay)
      {
      MIL_DOUBLE CurrentFrameRate = M_NULL;
      MdispInquire(pCurrentView->m_MilDisplay, M_UPDATE_RATE, &CurrentFrameRate);
      g_signal_emit(G_OBJECT(pCurrentView->m_cf->Window()), pCurrentView->m_cf->frameRateChangedSignal(), 0, CurrentFrameRate);
      }
   return true;
   }

void MdispGtkView::ROIDefine(bool on)
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write code that will be executed when 'ROI Define ' 
   //      menu is clicked. State toggles.
   /////////////////////////////////////////////////////////////////////////
   if(m_MilDisplay && m_isROISupported)
      {
      MdispControl(m_MilDisplay, M_ROI_DEFINE, on?(M_START+M_RESET):M_STOP);
      
      m_isInROIDefineMode = on;
      
      // Make sure Interpolation Mode combo box shows current interpolation mode
      m_currentInterpolationMode = MdispInquire(m_MilDisplay, M_INTERPOLATION_MODE, M_NULL);
      if(MdispInquire(m_MilDisplay, M_DISPLAY_TYPE, M_NULL) & M_EXCLUSIVE) 
         { 
	      //when ROI mode is active, allow the mouse to be used in the exclusive display monitor 
         if(m_isInROIDefineMode) 
	         { 
            MdispControl(m_MilDisplay, M_RESTRICT_CURSOR, M_DISABLE); 
            } 
	      else 
	         { 
	         MdispControl(m_MilDisplay, M_RESTRICT_CURSOR, M_ENABLE); 
            } 
         } 
      }
   }

void MdispGtkView::ROIShow(bool on)
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write code that will be executed when 'ROI Show ' 
   //      menu is clicked. State toggles.
   /////////////////////////////////////////////////////////////////////////
   if(m_MilDisplay && m_isROISupported)
      {
      MdispControl(m_MilDisplay, M_ROI_SHOW, on?M_ENABLE:M_DISABLE);
      m_isInROIShowMode = on;
      }
   }

void MdispGtkView::RestrictCursor(bool on)
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write code that will be executed when 'Restrict Cursor' menu item is clicked
   /////////////////////////////////////////////////////////////////////////

   if(m_MilDisplay)
      {
      MdispControl(m_MilDisplay, M_RESTRICT_CURSOR,on?M_ENABLE:M_DISABLE);

      // Check if control worked correctly before considering it successful [CALL TO MIL]
      MdispInquire(m_MilDisplay, M_RESTRICT_CURSOR, &m_currentRestrictCursor);

      }
   }


void MdispGtkView::UpdateROIWithCurrentState()
   {
   if(m_MilDisplay)
      {
      if(MdispInquire(m_MilDisplay, M_ROI_DEFINE, M_NULL) == M_STOP)
         m_isInROIDefineMode = false;
      else
         m_isInROIDefineMode = true;
      }
   }
bool MdispGtkView::IsFileSaveRoiAsEnabled()
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: If no ROI exist, we do not allow user to select this item.
   /////////////////////////////////////////////////////////////////////////
   if(m_MilDisplay)
      {
      if(MdispInquire(m_MilDisplay, M_ROI_BUFFER_SIZE_X, M_NULL)&&
         MdispInquire(m_MilDisplay, M_ROI_BUFFER_SIZE_Y, M_NULL))
         {
         return true;
         }
      }
   return false;
   }
void MdispGtkView::UpdateContentSize()
   {
   int sizeX, sizeY;
   sizeX = int( m_imageSizeX * m_currentZoomFactor );
   sizeY = int( m_imageSizeY * m_currentZoomFactor );
   // tell this child frame to update the window and scrollbars
   if(m_cf)
      m_cf->UpdateContentSize(sizeX, sizeY);
   }

void MdispGtkView::UpdateStatusBarWithROI(long OffsetX, long OffsetY, long SizeX, long SizeY)
   {
   // tell this child frame to update status bar
   if(m_cf)
      {
      g_signal_emit(G_OBJECT(m_cf->Window()), m_cf->roiPositionChangedSignal(), 0, 
                    OffsetX, 
                    OffsetY, 
                    SizeX, 
                    SizeY);
      }
   }

void MdispGtkView::UpdateStatusBarWithMousePosition()
   {
   // tell this child frame to update status bar
   if(m_cf)
      {

      g_signal_emit(G_OBJECT(m_cf->Window()), m_cf->mousePositionChangedSignal(), 0, 
                    m_LastMousePosition.m_DisplayPositionX,
                    m_LastMousePosition.m_DisplayPositionY,
                    m_LastMousePosition.m_BufferPositionX,
                    m_LastMousePosition.m_BufferPositionY);

      // Reset mouse position
      m_LastMousePosition.Set(M_INVALID, M_INVALID, M_INVALID, M_INVALID);
      }
   }

void MdispGtkView::Paint()
   {
   GdkColor textColor;
   if(!m_MilDisplay)
      {
      /* red color */
      textColor.red  = 65535;
      textColor.green = 0;
      textColor.blue = 0;
      gdk_window_clear(GDK_WINDOW(m_window->window));
      m_cf->DrawText("Display Allocation Failed",(m_imageSizeX/2),10,textColor);
      }
   else if(m_isWindowed)
      {
      if(m_isX11AnnotationsEnabled)
         {
         /* pink color */
         textColor.red  = 65535;
         textColor.green = 0;
         textColor.blue = 65535;         
         m_cf->DrawText("Window Annotation",
                        (m_isFillDisplayEnabled)?(m_window->allocation.width/2):(m_imageSizeX/2),
                        10,
                        textColor);
         }
      }
   else
      {
      /* black color */
      textColor.red  = 0;
      textColor.green = 0;
      textColor.blue = 0;         
      gdk_window_clear(GDK_WINDOW(m_window->window));
      m_cf->DrawText("Image Displayed on external Screen",(m_imageSizeX/2),10,textColor);
      }
   }

void MdispGtkView::GraphicLogo(MIL_INT PosX, MIL_INT PosY, MIL_INT CellSize)
   {
   MIL_DOUBLE MILYellow1 = M_RGB888(255, 201,  10);
   MIL_DOUBLE MILYellow2 = M_RGB888(254, 189,  17);
   MIL_DOUBLE MILYellow3 = M_RGB888(255, 230,   0);
   MIL_DOUBLE MILYellow4 = M_RGB888(246, 139,  31);

   MIL_DOUBLE MILGreen1  = M_RGB888(  0, 141,  76);
   MIL_DOUBLE MILGreen2  = M_RGB888(  0, 101,  49);
   MIL_DOUBLE MILGreen3  = M_RGB888(  0, 151,  78);
   MIL_DOUBLE MILGreen4  = M_RGB888(  0, 167, 115);

   MIL_DOUBLE MILRed1    = M_RGB888(209,  24,  32);
   MIL_DOUBLE MILRed2    = M_RGB888(238,  49,  36);
   MIL_DOUBLE MILRed3    = M_RGB888(189,  20,  27);
   MIL_DOUBLE MILRed4    = M_RGB888(137,   3,   4);

   MIL_DOUBLE MILPurple1 = M_RGB888(126,  69, 154);
   MIL_DOUBLE MILPurple2 = M_RGB888( 76,  42, 125);
   MIL_DOUBLE MILPurple3 = M_RGB888(111, 116, 182);
   MIL_DOUBLE MILPurple4 = M_RGB888( 85,  79, 162);

   MgraColor(m_MilGraphContext, MILYellow1);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX           , PosY           , CellSize*3, CellSize*3, 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILYellow2);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize  , PosY+CellSize  , CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILYellow3);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*2, PosY+CellSize  , CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILYellow4);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize  , PosY+CellSize*2, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);

   MgraColor(m_MilGraphContext, MILGreen1);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*3, PosY           , CellSize*3, CellSize*3, 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILGreen2);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*3, PosY+CellSize  , CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILGreen3);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*4, PosY+CellSize  , CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILGreen4);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*4, PosY+CellSize*2, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);

   MgraColor(m_MilGraphContext, MILRed1);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX           , PosY+CellSize*3, CellSize*3, CellSize*3, 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILRed2);               
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize  , PosY+CellSize*3, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILRed3);               
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*2, PosY+CellSize*4, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILRed4);               
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize  , PosY+CellSize*4, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);

   MgraColor(m_MilGraphContext, MILPurple1);
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*3, PosY+CellSize*3, CellSize*3, CellSize*3, 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILPurple2);                         
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*4, PosY+CellSize*3, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILPurple3);                         
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*3, PosY+CellSize*4, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   MgraColor(m_MilGraphContext, MILPurple4);                         
   MgraRectAngle(m_MilGraphContext, m_MilGraphList, PosX+CellSize*4, PosY+CellSize*4, CellSize  , CellSize  , 0, M_CORNER_AND_DIMENSION+M_FILLED);
   }
