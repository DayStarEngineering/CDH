#include "mdispqtview.h"
#include "mdispqtapp.h"
#include "childframe.h"

#include <QtGui>
#include <QX11Info>
#include <cmath>
#include <cstdlib>
#include <X11/Xlib.h> // For XClearArea, XSendEvent...

#define IMAGE_FILE   M_IMAGE_PATH MIL_TEXT("BaboonRGB.mim")

MIL_INT MFTYPE MouseFct(MIL_INT /*HookType*/, MIL_ID EventID, void MPTYPE *UserDataPtr)
   {
   MdispQtView* pCurrentView = (MdispQtView *)UserDataPtr;

   if(pCurrentView)
      {
      MOUSEPOSITION MousePosition;
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_X,         &MousePosition.m_DisplayPositionX);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_Y,         &MousePosition.m_DisplayPositionY);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_X,  &MousePosition.m_BufferPositionX);
      MdispGetHookInfo(EventID, M_MOUSE_POSITION_BUFFER_Y,  &MousePosition.m_BufferPositionY);

      pCurrentView->SetMousePosition(MousePosition);
      ((MdispQtApp*)qApp)->postEvent( pCurrentView, new MilMouseEvent(MousePosition));
      }
   return 0;
   }

MIL_INT MFTYPE ROIChangeEndFct(MIL_INT /*HookType*/, MIL_ID /*EventID*/, void MPTYPE *UserDataPtr)
   {
   MdispQtView* pCurrentView = (MdispQtView*)UserDataPtr;
   if(pCurrentView)
      {
      pCurrentView->UpdateROIWithCurrentState();
      }
   return 0;
   }

MIL_INT MFTYPE ROIChangeFct(MIL_INT /*HookType*/, MIL_ID /*EventID*/, void MPTYPE *UserDataPtr)
   {
   MdispQtView* pCurrentView = (MdispQtView*)UserDataPtr;
   if(pCurrentView)
      {
      MIL_ID DisplayID  = pCurrentView->MilDisplay();
      MIL_INT OffsetX   = MdispInquire(DisplayID, M_ROI_BUFFER_OFFSET_X, M_NULL);
      MIL_INT OffsetY   = MdispInquire(DisplayID, M_ROI_BUFFER_OFFSET_Y, M_NULL);
      MIL_INT SizeX     = MdispInquire(DisplayID, M_ROI_BUFFER_SIZE_X, M_NULL);
      MIL_INT SizeY     = MdispInquire(DisplayID, M_ROI_BUFFER_SIZE_Y, M_NULL);
      ((MdispQtApp*)qApp)->postEvent( pCurrentView, new MilROIEvent(OffsetX, OffsetY,SizeX, SizeY));
     }
   return 0;
   }

MdispQtView::MdispQtView( QWidget* parent )
   :m_Parent(parent)
   , m_Modified(false)
   {
   setAttribute(Qt::WA_OpaquePaintEvent);
   setAttribute(Qt::WA_PaintOnScreen);
   m_ScrollArea = new QScrollArea;
   m_ScrollArea->setWidget(this);
   m_ScrollArea->setWidgetResizable(false);

   m_MilOverlayImage            = M_NULL;   // Overlay image buffer identifier
   m_MilDisplay                 = M_NULL;   // Display identifier.
   m_MilGraphContext            = M_NULL;
   m_MilGraphList               = M_NULL;

   static int viewNumber = 0;
   m_Filename = QString(tr("Image%1")).arg(++viewNumber);
   m_FilenameValid = false;

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

   m_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   m_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

   m_FrameRateTimer = startTimer(500);

   // Allocation another XDisplay Connection ( used for Window annotation)
   m_XDisplay                  = XOpenDisplay("");

   XColor exact, AnnotationColor;
   if(!XAllocNamedColor(m_XDisplay, DefaultColormap(m_XDisplay,DefaultScreen(m_XDisplay)),"green", &AnnotationColor, &exact))
       m_AnnotationColorPixel = BlackPixel(m_XDisplay,DefaultScreen(m_XDisplay));
    else
      m_AnnotationColorPixel = AnnotationColor.pixel;

   XFlush(m_XDisplay);
   
   }

MdispQtView::~MdispQtView()
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

   // Close Annotation XDisplay
   if(m_XDisplay)
      XCloseDisplay(m_XDisplay);

   }

void MdispQtView::GrabStart()
   {
    // TODO: Add your command handler code here
	
	/////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab start
	/////////////////////////////////////////////////////////////////////////

   // If there is a grab in a view, halt the grab before starting a new one
   if(((MdispQtApp*)qApp)->m_isGrabStarted)
      ((MdispQtApp*)qApp)->m_pGrabView->GrabStop();

   // Start a continuous grab in this view
   MdigGrabContinuous(((MdispQtApp*)qApp)->m_MilDigitizer, m_MilImage);

   // Update the variable GrabIsStarted
   ((MdispQtApp*)qApp)->m_isGrabStarted = TRUE;

   // GrabInViewPtr is now a pointer to m_pGrabView view
   ((MdispQtApp*)qApp)->m_pGrabView = this;

   // Document has been modified
   m_Modified = true;

	/////////////////////////////////////////////////////////////////////////	
	// MIL: Write code that will be executed on a grab start
	/////////////////////////////////////////////////////////////////////////
   
   }

void MdispQtView::GrabStop()
   {
   // TODO: Add your command handler code here
 
   /////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab stop 
	/////////////////////////////////////////////////////////////////////////
   // Halt the grab
   MdigHalt(((MdispQtApp*)qApp)->m_MilDigitizer);
   ((MdispQtApp*)qApp)->m_isGrabStarted = FALSE;

   /////////////////////////////////////////////////////////////////////////
	// MIL: Write code that will be executed on a grab stop 
	/////////////////////////////////////////////////////////////////////////
   }

void MdispQtView::Overlay( bool on )
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


void MdispQtView::Initialize()
   {
   // Allocate a display [CALL TO MIL]
   MdispAlloc(((MdispQtApp*)qApp)->m_MilSystem, M_DEFAULT, "M_DEFAULT", M_DEFAULT, &m_MilDisplay);

   if(m_MilDisplay)
      {
      MIL_INT DisplayType = MdispInquire(m_MilDisplay, M_DISPLAY_TYPE, M_NULL);
      
      // Check display type [CALL TO MIL]
      if((DisplayType&(M_WINDOWED|M_EXCLUSIVE)) !=M_WINDOWED)
         m_isWindowed = false;

      if(DisplayType&(M_EXCLUSIVE))
         m_isExclusive = true;
 
      // ROI are supported with windowed display
       m_isROISupported = m_isWindowed;

      // Initially set interpolation mode and view mode to default
      ChangeInterpolationMode(M_DEFAULT);
      ChangeViewMode(M_DEFAULT);

      if(m_isROISupported)
         {
         if(m_isWindowed)
            {
            // The connection to the X display must be given to Mil so it
            // can update the window when ROI is enabled
            Display *dpy = x11Info().display();
            MdispControl(m_MilDisplay, M_WINDOW_ANNOTATIONS, M_PTR_TO_DOUBLE(dpy));
            }


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

      // Hook a function to mouse-movement event, to update cursor position in status bar.
      MdispHookFunction(m_MilDisplay, M_MOUSE_MOVE, MouseFct, (void*)this);
      }
   /////////////////////////////////////////////////////////////////////////
   // MIL: Code that will be executed when a view is first attached to the document
   /////////////////////////////////////////////////////////////////////////
   }



void MdispQtView::RemoveFromDisplay()

   {
   //Halt grab if in process in THIS view
   if ((((MdispQtApp*)qApp)->m_pGrabView == this) &&
        ((MdispQtApp*)qApp)->m_isGrabStarted)
      {
      //Ask the digitizer to halt the grab [CALL TO MIL]
      MdigHalt(((MdispQtApp*)qApp)->m_MilDigitizer);


      ((MdispQtApp*)qApp)->m_isGrabStarted = FALSE;
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

      //Free GraphicList [CALL TO MIL]
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


void MdispQtView::paintEvent( QPaintEvent* )
   {
   QPainter p( this);
   QFont font;

   font.setStyleStrategy( QFont::NoAntialias );
   font.setBold(true);
   p.setFont(font);
   
   if(!m_MilDisplay)
      {
      p.setPen( QColor(255,0,0) );
      p.drawText( 0, 0, width() , p.fontMetrics().height(), Qt::AlignCenter,
                  tr("Display Allocation Failed!") );
      }
   // In external mode, write message in window
   else if (m_isWindowed)
      {
      if (m_isX11AnnotationsEnabled)
         {
         p.setPen( QColor(255,0,255) );
         p.drawText( 0, 0, contentsRect().width(), p.fontMetrics().height(), Qt::AlignCenter,
                     tr("Window Annotations") );
         }
      }
   else
      {
      p.setPen( QColor(0,0,0) );
      p.drawText( 0, 0, m_isFillDisplayEnabled ? width() :
                  contentsRect().width(), p.fontMetrics().height(), Qt::AlignLeft,
                  tr("Image Displayed on external screen") );
      }
   }

void MdispQtView::pan( int x, int y )
   {
   if (m_MilDisplay)
      {
      //Apply a pan on display to scroll the image in window, according to scroll position
      MdispPan( m_MilDisplay, x / m_currentZoomFactor, y / m_currentZoomFactor );
      }
   }



void MdispQtView::timerEvent( QTimerEvent* e )
   {
   if ( e->timerId() == m_FrameRateTimer )
      {
      MIL_DOUBLE CurrentFrameRate = M_NULL;
      MdispInquire(m_MilDisplay, M_UPDATE_RATE, &CurrentFrameRate);
      emit frameRateChanged(CurrentFrameRate);
      }
   }

void MdispQtView::ZoomIn()
   {
   //Perform zooming with MIL (using MdispZoom)
   Zoom( m_currentZoomFactor * 2.0 );
   }

void MdispQtView::ZoomOut()
   {
   //Perform zooming with MIL (using MdispZoom)
   Zoom( m_currentZoomFactor / 2.0 );
   }

void MdispQtView::NoZoom()
   {
   //Perform zooming with MIL
   Zoom(1.0);
   }

void MdispQtView::Zoom( MIL_DOUBLE ZoomFactorToApply )
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
         UpdateContentSize();
         
         emit zoomFactorChanged(m_currentZoomFactor);
         }
      }
   }


void MdispQtView::FillDisplay( bool on )
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
         MdispControl(m_MilDisplay, M_WINDOW_ANNOTATIONS, M_NULL);          
         }
      else
         {
         MdispControl(m_MilDisplay, M_WINDOW_ANNOTATIONS, M_PTR_TO_DOUBLE(x11Info().display())); 
         }
      //Using MIL, enable/disable Fill Display Mode [CALL TO MIL]
      MdispControl(m_MilDisplay, M_FILL_DISPLAY, on ? M_ENABLE : M_DISABLE);

      m_isFillDisplayEnabled = on;

      m_ScrollArea->setHorizontalScrollBarPolicy(on ? Qt::ScrollBarAlwaysOff:Qt::ScrollBarAsNeeded);
      m_ScrollArea->setVerticalScrollBarPolicy(on ? Qt::ScrollBarAlwaysOff:Qt::ScrollBarAsNeeded);


      // clear contents
      repaint();

      UpdateContentSize();

      if(m_isFillDisplayEnabled)
         setMinimumSize(10, 10);

      }
   }


void MdispQtView::X11Annotations( bool on )
   {
   m_isX11AnnotationsEnabled = on;
	
   if (on)
      {
      repaint();
      }
   else
      {
      // When the annotations are disabled, an X event has to be sent
      // for Mil to be able to repaint the window.  This approach
      // could also be used when the annotations are enabled, but it
      // is not necessary.
      
      // This is an option, but it would clear the window before the refresh
      //XClearArea(viewport()->x11Display(), viewport()->winId(), 0,0,0,0, true);
      
      // This is the other option.  Take note that this would also
      // work when disabling annotations
      XExposeEvent TheEvent = { Expose,
                                0,
                                true,
                                x11Info().display(),
                                winId(),
                                0,
                                0,
                                contentsRect().width(),
                                contentsRect().height(),
                                0};
      
      XSendEvent(x11Info().display(), winId(), true, ExposureMask, (XEvent*)&TheEvent);
      }
   }

void MdispQtView::GraphicsAnnotations( bool on )
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

            MgraAlloc(((MdispQtApp*)qApp)->m_MilSystem, &m_MilGraphContext);
            MgraAllocList(((MdispQtApp*)qApp)->m_MilSystem, M_DEFAULT, &m_MilGraphList);
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

void MdispQtView::ChangeInterpolationMode(long InterpolationMode)
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

void MdispQtView::ChangeViewMode(long ViewMode,long ShiftValue)
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

void MdispQtView::ChangeCompressionType(MIL_INT CompressionType)
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

void MdispQtView::ChangeAsynchronousMode(bool Enabled, MIL_INT FrameRate)
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

void MdispQtView::ChangeQFactor(MIL_INT QFactor)
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

bool MdispQtView::IsNetworkedSystem()
   {
   bool NetworkedSystem = false;
   MIL_ID SystemId = ((MdispQtApp*)qApp)->m_MilSystem;

   // Check if system is networked (DistributedMIL) [CALL TO MIL]
   if(SystemId)
      NetworkedSystem = (MsysInquire(SystemId, M_NETWORKED, M_NULL) == M_YES);

   return NetworkedSystem;
   }

void MdispQtView::NoTearing( bool on )
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

void MdispQtView::InitializeOverlay()
   {
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
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageWidth/5,    " -------------------- ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageWidth/5+25, " - MIL Overlay Text - ");
         MgraText(M_DEFAULT, m_MilOverlayImage, imageWidth/9, imageWidth/5+50, " -------------------- ");

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
         
         if(XPixmap != M_NULL)
            {
            /* init X */
            Display *dpy = x11Info().display();
            GC gc        = XCreateGC (dpy, XPixmap,0,0);
            int screen   = DefaultScreen(dpy);
            XColor xcolors[3],exact;
            XPoint Hor[2];
            XPoint Ver[2];
            const char *color_names[] = {
               "red",
               "yellow",
               "blue",
            };

            /* allocate colors */
            for( int i=0; i < 3; i++) 
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
            Hor[0].y = imageHeight/2;
            Hor[1].x = imageWidth;
            Hor[1].y = imageHeight/2;
            XDrawLines(dpy,XPixmap,gc,Hor, 2, CoordModeOrigin);

            Ver[0].x = imageWidth/2;
            Ver[0].y = 0;
            Ver[1].x = imageWidth/2;
            Ver[1].y = imageHeight;
            XDrawLines(dpy,XPixmap,gc,Ver, 2, CoordModeOrigin);

            /* Write Red text. */
            MIL_TEXT_CHAR chText[80];
            XSetForeground(dpy,gc, xcolors[0].pixel);
            MosStrcpy(chText, 80, MIL_TEXT("X Overlay Text"));
            XDrawString(dpy,XPixmap,gc,
                        imageWidth*3/18, imageHeight*17/24,
                        chText,MosStrlen(chText));

            /* Write yellow text. */
            XSetForeground(dpy,gc, xcolors[1].pixel);
            XDrawString(dpy,XPixmap,gc,
                        imageWidth*12/18, imageHeight*17/24,
                        chText,MosStrlen(chText));

            XSetForeground(dpy,gc, BlackPixel(dpy,screen));
            XFlush(dpy);
            XFreeGC(dpy,gc);

            // Delete created Pixmap.  [CALL TO MIL]
            MbufControl(m_MilOverlayImage, M_XPIXMAP_FREE, M_DEFAULT);
            
            // Signal MIL that the overlay buffer was modified. [CALL TO MIL]
            MbufControl(m_MilOverlayImage, M_MODIFIED, M_DEFAULT);
            }

         // Now that overlay buffer is correctly prepared, we can show it [CALL TO MIL]
         MdispControl(m_MilDisplay, M_OVERLAY_SHOW, M_ENABLE);

         // Overlay is now initialized
         m_isOverlayInitialized = TRUE;
         }
      }
   }


void MdispQtView::ROIDefine(bool on)
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
void MdispQtView::RestrictCursor(bool on)
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

void MdispQtView::ROIShow(bool on)
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

bool MdispQtView::newDoc()
   {
   // Set buffer attributes
   if(((MdispQtApp*)qApp)->m_numberOfDigitizer)
   {
      m_bufferAttributes=M_IMAGE+M_DISP+M_GRAB+M_PROC;

      m_bufferAttributes=M_IMAGE+M_DISP+M_GRAB+M_PROC;
      m_imageSizeX = ((MdispQtApp*)qApp)->m_digitizerSizeX;
      m_imageSizeY = ((MdispQtApp*)qApp)->m_digitizerSizeY;
      m_NbBands    = ((MdispQtApp*)qApp)->m_digitizerNbBands;

      // Allocate a buffer [CALL TO MIL]
      MbufAllocColor(((MdispQtApp*)qApp)->m_MilSystem,
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
      MbufImport(IMAGE_FILE,M_DEFAULT,M_RESTORE,((MdispQtApp*)qApp)->m_MilSystem,&m_MilImage);

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
      return FALSE;

   Initialize();

   return true;
}

bool MdispQtView::load( const QString& fn )
   {
   //Import image in buffer [CALL TO MIL]
   char* tmp = new char[ fn.length() + 1 ];
   strncpy( tmp, fn.toAscii(), fn.length() );
   tmp[ fn.length() ] = 0;
   MbufImport(tmp,M_DEFAULT,M_RESTORE,((MdispQtApp*)qApp)->m_MilSystem,&m_MilImage);
   delete[] tmp;

   // Set SizeX and SizeY variable to the size of the buffer [CALL TO MIL]
   if (m_MilImage)
      {
      Initialize();
      m_imageSizeX = MbufInquire(m_MilImage,M_SIZE_X,M_NULL);
      m_imageSizeY = MbufInquire(m_MilImage,M_SIZE_Y,M_NULL);
      UpdateContentSize();

      m_Filename = QFileInfo(fn).fileName();
      m_FilenameValid = true;
      emit filenameChanged(m_Filename);
      return TRUE;
      }
   else
      {
      return FALSE;
      }
   }

bool MdispQtView::saveROIAs()
   {
   QString fn = QFileDialog::getSaveFileName(this,
                                             tr("Save File"),
                                             tr("."));
   
   if ( !fn.isEmpty() )
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
      char* tmp = new char[ fn.length() + 1 ];
      strncpy( tmp, fn.toAscii(), fn.length() );
      tmp[ fn.length() ] = 0;
      MbufSave(tmp, ChildBuffer);
      MbufFree(ChildBuffer);
      return true;
      }
   else
      {
      return false;
      }
   }
bool MdispQtView::save()
   {
   if ( !m_FilenameValid )
      {
      return saveAs();
      }

   bool SaveStatus;
   QString TempPath;
   long FileFormat = M_MIL;

   // Get extension for file format determination
   TempPath = m_Filename.toUpper();
   //Set the file format to M_MIL when the filepath extension is ".MIM"
   if (TempPath.endsWith(".MIM"))
      FileFormat = M_MIL;
   //Set the file format to M_TIFF when the filepath extension is ".TIF"
   else if (TempPath.endsWith(".TIF"))
      FileFormat = M_TIFF;
   //Set the file format to M_BMP when the filepath extension is ".BMP"
   else if (TempPath.endsWith(".BMP"))
      FileFormat = M_BMP;
   //Set the file format to M_JPEG_LOSSY when the filepath extension is ".JPG"
   else if (TempPath.endsWith(".JPG"))
      FileFormat = M_JPEG_LOSSY;
   //Set the file format to M_JPEG2000_LOSSLESS when the filepath extension is ".JP2"
   else if (TempPath.endsWith(".JP2"))
      FileFormat = M_JPEG2000_LOSSLESS;
   //Set the file format to M_RAW when the filepath extension is ".RAW"
   else if (TempPath.endsWith(".RAW"))
      FileFormat = M_RAW;

   // Halt the grab if the current view has it [CALL TO MIL]
   if((((MdispQtApp*)qApp)->m_pGrabView == this) &&
      (((MdispQtApp*)qApp)->m_isGrabStarted == TRUE))
      MdigHalt(((MdispQtApp*)qApp)->m_MilDigitizer);

   // Save the current buffer [CALL TO MIL]
   char* tmp = new char[ m_Filename.length() + 1 ];
   strncpy( tmp, m_Filename.toAscii(), m_Filename.length() );
   tmp[ m_Filename.length() ] = 0;
   MbufExport(tmp, FileFormat,m_MilImage);
   delete[] tmp;

   // Verify if save operation was successful [CALL TO MIL]
   SaveStatus = (MappGetError(M_CURRENT,M_NULL) == M_NULL_ERROR);

   // Document has been saved
   if (!((((MdispQtApp*)qApp)->m_pGrabView == this) &&
         (((MdispQtApp*)qApp)->m_isGrabStarted == TRUE)))
      m_Modified = false;

   // Restart the grab if the current view had it [CALL TO MIL]
   if((((MdispQtApp*)qApp)->m_pGrabView == this) &&
     (((MdispQtApp*)qApp)->m_isGrabStarted == TRUE))
     MdigGrabContinuous(((MdispQtApp*)qApp)->m_MilDigitizer, m_MilImage);

   return SaveStatus;
   }

bool MdispQtView::saveAs()
   {
   QString showName = strippedName(m_Filename);
   QString fn = QFileDialog::getSaveFileName(this, tr("Save File"),
                                             tr("%1.mim").arg(showName));

   if ( !fn.isEmpty() )
      {
      m_Filename = fn;
      m_FilenameValid = true;
      emit filenameChanged(strippedName(m_Filename));
      return save();
      }
   else
      {
      return false;
     }
   }

const QString& MdispQtView::filename() const
   {
   return m_Filename;
   }


void MdispQtView::closeEvent( QCloseEvent* e )
   {
   if ( IsModified() )
      {
      switch ( QMessageBox::warning( this, tr("MdispQt Message"),
               tr("Save changes to %1?").arg(m_Filename),
               QMessageBox::Yes | QMessageBox::Default,
               QMessageBox::No,
               QMessageBox::Cancel | QMessageBox::Escape ) )
         {
         case QMessageBox::Yes:
            if ( save() )
               e->accept();
            else
               e->ignore();
            break;
         case QMessageBox::No:
            e->accept();
            break;
         default:
            e->ignore();
            break;
         }
      }
   else
      {
      e->accept();
      }
   }

QSize MdispQtView::sizeHint() const
   {
   int sizeX, sizeY;
   sizeX = int( m_imageSizeX * m_currentZoomFactor );
   sizeY = int( m_imageSizeY * m_currentZoomFactor );
   int f = 2 * m_ScrollArea->frameWidth();
   QSize sz( f, f );
   sz += QSize(width(), height());
   return sz;
   }

void MdispQtView::UpdateContentSize()
   {

   int sizeX, sizeY;
   sizeX = int( m_imageSizeX * m_currentZoomFactor );
   sizeY = int( m_imageSizeY * m_currentZoomFactor );
   resize( sizeX, sizeY );
   setMinimumSize(sizeX, sizeY);
   m_ScrollArea->setWidgetResizable(true);
   if(sizeX <= m_imageSizeX)
      emit sizeChanged((long)(sizeX + 2 * m_ScrollArea->frameWidth()) , (long)(sizeY +2 * m_ScrollArea->frameWidth()));
   }

void MdispQtView::UpdateROIWithCurrentState()
   {
   if(m_MilDisplay)
      {
      if(MdispInquire(m_MilDisplay, M_ROI_DEFINE, M_NULL) == M_STOP)
         m_isInROIDefineMode = false;
      else
         m_isInROIDefineMode = true;
      }
   }

void MdispQtView::UpdateMousePosition()
   {
   emit mousePositionChanged(m_LastMousePosition.m_DisplayPositionX,
                             m_LastMousePosition.m_DisplayPositionY,
                             m_LastMousePosition.m_BufferPositionX,
                             m_LastMousePosition.m_BufferPositionY);
   // Reset mouse position
   m_LastMousePosition.Set(M_INVALID, M_INVALID, M_INVALID, M_INVALID);
   }

void MdispQtView::customEvent(QEvent* e)
   {
   if(e->type() == QEvent::User +7)
   {
      MilROIEvent* re = (MilROIEvent*)e;
      emit roiPositionChanged(re->OffsetX(),
                              re->OffsetY(), 
                              re->SizeX(), 
                              re->SizeY());
   }
   else if (e->type() == QEvent::User +8)
   {

      MilMouseEvent* re = (MilMouseEvent*)e;
      MOUSEPOSITION Pos = re->MousePostion();
      emit mousePositionChanged(Pos.m_DisplayPositionX,
                                Pos.m_DisplayPositionY,
                                Pos.m_BufferPositionX,
                                Pos.m_BufferPositionY);
      // Reset mouse position
      m_LastMousePosition.Set(M_INVALID, M_INVALID, M_INVALID, M_INVALID);
   }
}

void MdispQtView::SelectWindow()
   {
   //Select the buffer from its display object and given window [CALL TO MIL]
   if(m_MilDisplay && m_MilImage)
      {
      MdispSelectWindow(m_MilDisplay, m_MilImage, m_isWindowed?winId():0);   
      }
   }

void MdispQtView::GraphicLogo(MIL_INT PosX, MIL_INT PosY, MIL_INT CellSize)
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
