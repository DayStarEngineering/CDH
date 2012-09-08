#ifndef PAINTAREA_H
#define PAINTAREA_H
#include <mil.h>
#include <QtGui>
#include <QCustomEvent>

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


// Events sent when ROI Position changed
class MilROIEvent : public QEvent
{
public:
   MilROIEvent( MIL_INT OffsetX, MIL_INT OffsetY, MIL_INT SizeX, MIL_INT SizeY )
      : QEvent(QEvent::Type(TYPE))
      , m_OffsetX( OffsetX )
      , m_OffsetY( OffsetY )
      , m_SizeX( SizeX )
      , m_SizeY( SizeY )
   {
   }


   inline MIL_INT OffsetX() const { return m_OffsetX;}
   inline MIL_INT OffsetY() const { return m_OffsetY;}
   inline MIL_INT SizeX()   const { return m_SizeX;}
   inline MIL_INT SizeY()   const { return m_SizeY;}

   static const int TYPE = QEvent::User + 7;

private:
   MIL_INT m_OffsetX;
   MIL_INT m_OffsetY;
   MIL_INT m_SizeX;
   MIL_INT m_SizeY;

};

// Events sent when Mouse Position changed
class MilMouseEvent : public QEvent
{
public:
   MilMouseEvent( MOUSEPOSITION Pos)
      : QEvent(QEvent::Type(TYPE))
      , m_MousePosition(Pos)
   {
   }

   inline MOUSEPOSITION MousePostion() const { return m_MousePosition;}
   static const int TYPE = QEvent::User + 8;

private:
   MOUSEPOSITION m_MousePosition;

};



#include <QWidget>
#include <mil.h>

class QScrollArea;
class ChildFrame;

class MdispQtView : public QWidget
   {
   Q_OBJECT

   public:
      MdispQtView( QWidget* parent );
      ~MdispQtView();

      bool newDoc();
      bool load( const QString& filename );
      bool save();
      bool saveAs();
      bool saveROIAs();

      const QString& filename() const;

      void GrabStart();
      void GrabStop();

      void Overlay( bool on );
      void X11Annotations( bool on );
      void GraphicsAnnotations( bool on );
      void ZoomIn();
      void ZoomOut();
      void NoZoom();
      void FillDisplay( bool on );
      void ChangeInterpolationMode(long InterpolationMode);
      void ChangeViewMode(long ViewMode, long ShiftValue=M_NULL);
      void ChangeAsynchronousMode(bool Enabled, MIL_INT FrameRate);
      void ChangeCompressionType(MIL_INT CompressionType);
      void ChangeQFactor(MIL_INT QFactor);
      void ROIDefine(bool on);
      void ROIShow(bool on);
      void NoTearing( bool on );
      bool IsNetworkedSystem();
      void RestrictCursor(bool on);
      void SelectWindow();
      void UpdateMousePosition();

      inline QScrollArea* ScrollArea() const {return m_ScrollArea;}
      inline MIL_ID MilDisplay() const {return m_MilDisplay;}
      inline bool IsROISupported() const { return m_isROISupported ;}
      inline bool IsWindowed() const { return m_isWindowed ;}
      inline bool IsExclusive() const { return m_isExclusive ;}
      inline bool IsInROIDefineMode() const { return m_isInROIDefineMode;}
      inline bool IsInROIShowMode() const { return m_isInROIShowMode;}
      inline bool IsNoTearingEnabled() const { return m_isNoTearingEnabled; }
      inline long CurrentShiftValue() const { return m_currentShiftValue; }
      inline long CurrentViewMode() const { return m_currentViewMode;}
      inline long CurrentInterpolationMode() const { return m_currentInterpolationMode;}
      inline long CurrentRestrictCursor() const { return m_currentRestrictCursor;}
      bool IsX11AnnotationsEnabled() { return m_isX11AnnotationsEnabled;}
      bool IsGraphicsAnnotationsEnabled() { return m_isGraphicsAnnotationsEnabled;}
      inline bool IsFillDisplayEnabled() const { return m_isFillDisplayEnabled;}
      inline MIL_DOUBLE CurrentZoomFactor() const {return m_currentZoomFactor; }
      inline bool IsOverlayEnabled() const { return m_isOverlayEnabled; }
      inline bool IsModified() const {return m_Modified;}
      inline MIL_INT CompressionType() const {return  m_currentCompressionType;}      
      inline bool IsInAsynchronousMode() const {return  m_isInAsynchronousMode;}      
      inline MIL_INT AsynchronousFrameRate() const {return  m_currentAsynchronousFrameRate;}      
      inline MIL_INT QFactor() const {return  m_currentQFactor;}      
      inline Display *XDisplay() const { return m_XDisplay;}
      inline MIL_INT AnnotationColor() const { return m_AnnotationColorPixel;}
      inline MIL_INT ImageSizeX() const { return m_imageSizeX;}
      inline MIL_INT ImageSizeY() const { return m_imageSizeY;}
      inline void SetMousePosition(const MOUSEPOSITION& MousePosition){m_LastMousePosition = MousePosition;}
      inline QString strippedName(const QString& fullPath) const { return QFileInfo(fullPath).fileName();}
      QSize sizeHint() const;

      friend long MFTYPE FrameEndHookHandler(long HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);
      friend long MFTYPE ROIChangeEndFct(long HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);
      friend long MFTYPE ROIChangeFct(long HookType, MIL_ID EventId, void MPTYPE* UserDataPtr);

   signals:
      void zoomFactorChanged( double zoomFactor );
      void frameRateChanged( double frameRate );
      void filenameChanged( const QString& filename );
      void roiPositionChanged(long, long, long, long);
      void mousePositionChanged(long, long, double, double);
      void sizeChanged(long, long);
   protected:
      virtual void closeEvent( QCloseEvent* e );
      virtual void timerEvent( QTimerEvent* e );
      virtual void paintEvent(QPaintEvent *event);
      virtual void customEvent(QEvent* e);

   private slots:
      void pan( int x, int y );


   private:
      void Initialize();
      void InitializeOverlay();
      void RemoveFromDisplay();
      void UpdateContentSize();
      void UpdateROIWithCurrentState();
      void GraphicLogo(MIL_INT PosX, MIL_INT PosY, MIL_INT CellSize);

      void OnRoiShow();
      void Zoom( MIL_DOUBLE ZoomFactorToApply );

      QWidget*     m_Parent;
      QScrollArea* m_ScrollArea;

      bool m_Modified;
      QString m_Filename;
      bool m_FilenameValid;

      MIL_ID   m_MilImage;          // Image buffer identifier.

      long     m_imageSizeX;        // Buffer Size X
      long     m_imageSizeY;        // Buffer Size Y
      long     m_NbBands;

      int m_FrameRateTimer;

      //Attributes
      MIL_ID   m_MilOverlayImage;               //Overlay image buffer identifier
      MIL_ID   m_MilDisplay;                    //Display identifier.
      MIL_ID   m_MilGraphContext;
      MIL_ID    m_MilGraphList;

      MIL_DOUBLE   m_currentZoomFactor;             //Current zoom factor
      MIL_INT      m_currentInterpolationMode;      //Current interpolation mode (M_INTERPOLATION_MODE dispControl)
      MIL_INT      m_currentViewMode;               //Current view mode (M_VIEW_MODE dispControl)
      MIL_INT      m_currentShiftValue;             //Current bit-shift value(M_VIEW_BIT_SHIFT dispControl)
      MIL_INT      m_currentCompressionType;        //Current compression type (M_COMPRESSION_TYPE dispControl)
      bool         m_isInAsynchronousMode;          //Current asynchronous mode (M_ASYNC_UPDATE dispControl)
      MIL_INT      m_currentAsynchronousFrameRate;  //Current asynchronous frame rate (M_MAX_FRATE_RATE dispControl)
      MIL_INT      m_currentQFactor;                //Current Q factor (M_Q_FACTOR dispControl)
      MIL_INT      m_currentRestrictCursor;         //Current cursor restriction (M_RESTRICT_CURSOR dispControl)
      bool     m_isFillDisplayEnabled;          //Fill Display state(M_FILL_DISPLAY dispControl)
      bool     m_isNoTearingEnabled;            //No-Tearing state(M_NO_TEARING dispControl)
      bool     m_isX11AnnotationsEnabled;         //X11 Annotations state
      bool     m_isGraphicsAnnotationsEnabled;    //Graphics Annotations state
      bool     m_isOverlayEnabled;              //Overlay show state
      bool     m_isOverlayInitialized;          //Overlay initialization state
      bool     m_isInROIDefineMode;
      bool     m_isInROIShowMode;
      bool     m_isROISupported;

      bool     m_isWindowed;
      bool     m_isExclusive;
      

      MIL_INT64   m_bufferAttributes;  // Buffer attributes that will be allocated
      Display*    m_XDisplay;
      MIL_INT     m_AnnotationColorPixel;

      MOUSEPOSITION m_LastMousePosition;
   };

#endif
