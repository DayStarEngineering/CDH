#ifndef CHILDFRAME_H
#define CHILDFRAME_H

#define STRING_SIZE    1024

class MdispGtkView;
class MainFrame;

class ChildFrame
   {
   public:

      ChildFrame(MainFrame *parentFrame);
      virtual ~ChildFrame();
      MdispGtkView* View();
      void close();
      void show();
      void setTitle(const gchar* title);
      
      inline GtkWidget* DrawingArea() { return m_DrawingArea;}
      inline GtkWidget* Window() { return m_window;}

      void UpdateContentSize(long SizeX, long SizeY);
      void UpdateScrollBar();
      void DrawText(const gchar *text, gint x, gint y, GdkColor textColor);

      inline gint roiPositionChangedSignal() const { return m_roiPositionChangedSignal;}
      inline gint zoomFactorChangedSignal() const { return m_zoomFactorChangedSignal;}
      inline gint frameRateChangedSignal() const { return m_frameRateChangedSignal;}
      inline gint mousePositionChangedSignal() const { return m_mousePositionChangedSignal;}
      

   private:
      
      void UpdateStatusBarWithROI(long OffsetX, long OffsetY, long SizeX, long SizeY);
      void UpdateStatusBarWithMousePosition(long DispX, long DispY, double BufX, double BufY);
      void UpdateStatusBarWithScale(double Scale);
      void UpdateStatusBarWithFrameRate(double Scale);
      void UpdateStatusBar();

      static gboolean OnChildDelete(GtkWidget *widget, GdkEvent  *event, gpointer user_data);
      static gboolean OnChildGetFocus(GtkWidget *widget, GdkEventFocus *event, gpointer user_data);
      static gboolean OnChildConfigure(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data);
      static gboolean OnChildExpose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data);
      static void     OnChildScroll(GtkAdjustment *adjustment, gpointer user_data);
      static void     OnChildDestroy(GtkWidget *widget, gpointer user_data);
      static void     OnRoiPositionChanged(GtkWidget *widget, gint OffsetX, gint OffsetY, gint SizeX, gint SizeY, gpointer user_data);
      static void     OnFrameRateChanged(GtkWidget *widget, gdouble Rate, gpointer user_data);
      static void     OnZoomFactorChanged(GtkWidget *widget, gdouble Scale, gpointer user_data);
      static void     OnMousePositionChanged(GtkWidget *widget, gint DispX, gint DispY, gdouble BufX, gdouble BufY, gpointer user_data);
      

      MdispGtkView*  m_View;
      MainFrame*     m_mf;
      GtkWidget*     m_window;
      GtkWidget*     m_DrawingArea;
      GtkWidget*     m_StatusBar;
      PangoLayout*   m_layout;
      GtkAdjustment* m_hadj;
      GtkAdjustment* m_vadj;
      GtkWidget*     m_hscrollbar;
      GtkWidget*     m_vscrollbar;

      // Signals
      static gint    SignalId;
      gchar*         m_roiPositionChangedSignalName;
      gchar*         m_frameRateChangedSignalName;
      gchar*         m_zoomFactorChangedSignalName;
      gchar*         m_mousePositionChangedSignalName;
      gint           m_roiPositionChangedSignal;
      gint           m_frameRateChangedSignal;
      gint           m_zoomFactorChangedSignal;
      gint           m_mousePositionChangedSignal;
      
      gchar         m_FrameStr[STRING_SIZE];
      gchar         m_ScaleStr[STRING_SIZE];
      gchar         m_RoiStr[STRING_SIZE];
      gchar         m_MouseStr[STRING_SIZE];
         

   };
#endif
