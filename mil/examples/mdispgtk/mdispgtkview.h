#ifndef MDISPGTKVIEW_H
#define MDISPGTKVIEW_H
#include <mil.h>
#include <X11/Xlib.h>

#define DEFAULTSIZEX 640
#define DEFAULTSIZEY 480

typedef struct _MOUSEPOSITION
   {
   void Set(MIL_INT DisplayPositionX, MIL_INT DisplayPositionY, MIL_DOUBLE BufferPositionX, MIL_DOUBLE BufferPositionY)
      {
      m_DisplayPositionX = DisplayPositionX;
      m_DisplayPositionY = DisplayPositionY;
      m_BufferPositionX = BufferPositionX;
      m_BufferPositionY = BufferPositionY;
      }
   _MOUSEPOSITION()
      {
      Set(M_INVALID, M_INVALID, M_INVALID, M_INVALID);
      }
   _MOUSEPOSITION& operator=(const _MOUSEPOSITION& MousePosition)
      {
      Set(MousePosition.m_DisplayPositionX, 
         MousePosition.m_DisplayPositionY,
         MousePosition.m_BufferPositionX,
         MousePosition.m_BufferPositionY);

      return *this;
      }
   MIL_INT     m_DisplayPositionX;
   MIL_INT     m_DisplayPositionY;
   MIL_DOUBLE  m_BufferPositionX;
   MIL_DOUBLE  m_BufferPositionY;
   }MOUSEPOSITION;

class MdispGtkApp;
class ChildFrame;
class MdispGtkView
   {
   public:
      MdispGtkView(ChildFrame* cf);
      virtual ~MdispGtkView();

      bool newDoc();
      bool load(const char *filename);
      bool save(const char *filename);
      bool saveROIAs(const char *filename);
      
      void Overlay(bool on);
      void X11Annotations( bool on );
      void GraphicsAnnotations( bool on );
      void ZoomIn();
      void ZoomOut();
      void NoZoom();
      
      void FillDisplay( bool on );
      void ChangeInterpolationMode(MIL_INT InterpolationMode);
      void ChangeViewMode(MIL_INT ViewMode, MIL_INT ShiftValue=M_NULL);
      void ChangeAsynchronousMode(bool Enabled, MIL_INT FrameRate);
      void ChangeCompressionType(MIL_INT CompressionType);
      void ChangeQFactor(MIL_INT QFactor);
      void ROIDefine(bool on);
      void ROIShow(bool on);
      void RestrictCursor(bool on);
      void NoTearing( bool on );
      void GrabStart();
      void GrabStop();
      void Paint();
      void pan( int x, int y );
      bool IsNetworkedSystem();
      bool IsFileSaveRoiAsEnabled();
      void SetMousePosition(const MOUSEPOSITION& MousePosition){m_LastMousePosition = MousePosition;}
      static gboolean timerEvent(gpointer data);

      inline MIL_ID MilDisplay() {return m_MilDisplay;}
      inline bool IsROISupported() const { return m_isROISupported ;}
      inline bool IsWindowed() const { return m_isWindowed ;}
      inline bool IsExclusive() const { return m_isExclusive ;}
      inline bool IsInROIDefineMode() const { return m_isInROIDefineMode;}
      inline bool IsInROIShowMode() const { return m_isInROIShowMode;}
      inline bool IsNoTearingEnabled() const { return m_isNoTearingEnabled; }
      inline MIL_INT CurrentShiftValue() const { return m_currentShiftValue; }
      inline MIL_INT CurrentViewMode() const { return m_currentViewMode;}
      inline MIL_INT CurrentInterpolationMode() const { return m_currentInterpolationMode;}
      inline bool IsX11AnnotationsEnabled() const { return m_isX11AnnotationsEnabled;}
      inline bool IsGraphicsAnnotationsEnabled() const { return m_isGraphicsAnnotationsEnabled;}
      inline bool IsFillDisplayEnabled() const { return m_isFillDisplayEnabled;}
      inline MIL_DOUBLE CurrentZoomFactor() const {return m_currentZoomFactor; }
      inline bool IsOverlayEnabled() const { return m_isOverlayEnabled; }
      inline bool IsModified() const {return m_Modified;}
      inline gchar *filename() const { return m_filename;}
      inline MIL_INT ImageSizeX() const { return m_imageSizeX;}
      inline MIL_INT ImageSizeY() const { return m_imageSizeY;}
      inline MIL_DOUBLE ZoomFactor() const {return  m_currentZoomFactor;}      
      inline MIL_INT CompressionType() const {return  m_currentCompressionType;}      
      inline bool IsInAsynchronousMode() const {return  m_isInAsynchronousMode;}      
      inline MIL_INT AsynchronousFrameRate() const {return  m_currentAsynchronousFrameRate;}      
      inline MIL_INT QFactor() const {return  m_currentQFactor;}      

      inline GtkWidget* Window() const { return m_window;}
      inline Display *XDisplay() const { return m_XDisplay;}
      inline MIL_INT AnnotationColor() const { return m_AnnotationColorPixel;}

      MdispGtkApp* dispGtkApp();

      friend MIL_INT MFTYPE ROIChangeEndFct(MIL_INT HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);
      friend MIL_INT MFTYPE ROIChangeFct(MIL_INT HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);
      friend MIL_INT MFTYPE MouseFct(MIL_INT HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);

   private:
      void Initialize();
      void InitializeOverlay();
      void RemoveFromDisplay();
      void UpdateContentSize();
      void UpdateROIWithCurrentState();
      void Zoom( MIL_DOUBLE ZoomFactorToApply );
      void UpdateStatusBarWithROI(MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY);
      void UpdateStatusBarWithMousePosition();
      void GraphicLogo(MIL_INT PosX, MIL_INT PosY, MIL_INT CellSize);

      gchar*       m_filename;

      MIL_INT64    m_bufferAttributes;  // Buffer attributes that will be allocated
      bool         m_Modified;
      MIL_INT      m_imageSizeX;
      MIL_INT      m_imageSizeY;
      MIL_INT      m_NbBands;
      MIL_ID       m_MilImage;
      MIL_ID       m_MilDisplay;
      MIL_ID       m_MilOverlayImage;
      MIL_ID       m_MilGraphContext;
      MIL_ID       m_MilGraphList;
      
      MIL_DOUBLE   m_currentZoomFactor;
      MIL_INT      m_currentInterpolationMode;
      MIL_INT      m_currentViewMode;
      MIL_INT      m_currentShiftValue;
      MIL_INT      m_currentCompressionType;        //Current compression type (M_COMPRESSION_TYPE dispControl)
      bool         m_isInAsynchronousMode;          //Current asynchronous mode (M_ASYNC_UPDATE dispControl)
      MIL_INT      m_currentAsynchronousFrameRate;  //Current asynchronous frame rate (M_MAX_FRATE_RATE dispControl)
      MIL_INT      m_currentQFactor;                //Current Q factor (M_Q_FACTOR dispControl)
      MIL_INT      m_currentRestrictCursor;         //Current cursor restriction (M_RESTRICT_CURSOR dispControl)

      bool         m_isFillDisplayEnabled;
      bool         m_isNoTearingEnabled;
      bool         m_isX11AnnotationsEnabled;
      bool         m_isGraphicsAnnotationsEnabled;
      bool         m_isOverlayInitialized;
      bool         m_isOverlayEnabled;              //Overlay show state
      bool         m_isInROIDefineMode;
      bool         m_isInROIShowMode;
      bool         m_isROISupported;
      
      bool         m_isWindowed;
      bool         m_isExclusive;
      guint        m_FrameTimeOutTag; /* timer tag */

      ChildFrame*  m_cf;
      GtkWidget*   m_window; // Drawing Area
      Display*     m_XDisplay;
      MIL_INT      m_AnnotationColorPixel;

      MOUSEPOSITION m_LastMousePosition;
   };
#endif
