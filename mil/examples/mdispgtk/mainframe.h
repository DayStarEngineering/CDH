#ifndef MAINFRAME_H
#define MAINFRAME_H

#define GTK_MIL_IMAGES_DIR  "examples/mdispgtk/images"

enum {
  INTERPOLATION_MODE_NEAREST_NEIGHBOR,
  INTERPOLATION_MODE_FAST,
  INTERPOLATION_MODE_DEFAULT

};

enum {
   VIEW_MODE_DEFAULT,
   VIEW_MODE_TRANSPARENT,
   VIEW_MODE_AUTO_SCALE,
   VIEW_MODE_MULTI_BYTES,
   VIEW_MODE_BIT_SHIFT2,
   VIEW_MODE_BIT_SHIFT4,
   VIEW_MODE_BIT_SHIFT8,
};

enum {
   DMIL_ASYNC_DISABLE,
   DMIL_ASYNC_1,
   DMIL_ASYNC_5,
   DMIL_ASYNC_10,
   DMIL_ASYNC_15,
   DMIL_ASYNC_30,
   DMIL_ASYNC_MAX,
};

enum {
   DMIL_COMPRESS_NONE,
   DMIL_COMPRESS_LOSSY,
   DMIL_COMPRESS_LOSSLESS,
};

enum {
   DMIL_QFACTOR_60,                  
   DMIL_QFACTOR_70,                  
   DMIL_QFACTOR_75,                  
   DMIL_QFACTOR_80,                  
   DMIL_QFACTOR_82,                  
   DMIL_QFACTOR_85,                  
   DMIL_QFACTOR_87,                  
   DMIL_QFACTOR_90,                  
   DMIL_QFACTOR_92,                  
   DMIL_QFACTOR_95,                  
   DMIL_QFACTOR_99,                  
};

// Used to display Tooltiop in StatusBar
typedef struct _ActionStatus ActionStatus;
struct _ActionStatus 
   {
      GtkAction *action;
      GtkWidget *statusbar;
   };

class ChildFrame;
class MdispGtkApp;

class MainFrame
   {
   public:
      MainFrame();
      virtual ~MainFrame();
      
      GtkWidget* MainWindow() { return m_MainFrame;}
      bool Update() { return m_Update;}
      void Update (bool val) { m_Update = val;}
      void setcf(ChildFrame* cf);
      ChildFrame* cf() { return m_cf;}
      void remove(ChildFrame *cf);
      void add(ChildFrame *cf);

      static void fileNew(GtkAction *action, gpointer user_data);
      static void fileOpen(GtkAction *action, gpointer user_data);
      static void fileSave(GtkAction *action, gpointer user_data);
      static void fileClose(GtkAction *action, gpointer user_data);
      static void fileSaveAs(GtkAction *action, gpointer user_data);
      static void fileSaveRoiAs(GtkAction *action, gpointer user_data);
      static void fileQuit(GtkAction *action, gpointer user_data);

      static void dispNoZoom(GtkAction *action, gpointer user_data);
      static void dispZoomIn(GtkAction *action, gpointer user_data);
      static void dispZoomOut(GtkAction *action, gpointer user_data);
      static void dispGrabStart(GtkAction *action, gpointer user_data);
      static void dispGrabStop(GtkAction *action, gpointer user_data);
      static void dispRoiPrefs(GtkAction *action, gpointer user_data);
      static void dispOverlay(GtkAction *action, gpointer user_data);
      static void dispFillDisplay(GtkAction *action, gpointer user_data);
      static void dispNoTearing(GtkAction *action, gpointer user_data);
      static void dispX11Annotations(GtkAction *action, gpointer user_data);
      static void dispGraphicsAnnotations(GtkAction *action, gpointer user_data);
      static void dispRoiDefine(GtkAction *action, gpointer user_data);
      static void dispRoiShow(GtkAction *action, gpointer user_data);
      static void dispRestrictCursor(GtkAction *action, gpointer user_data);

      void dispViewModeShift(GtkAction *action, gpointer user_data, glong Val);
      void dispViewMode(GtkAction *action, gpointer user_data, glong Val);
      void dispInterMode(GtkAction *action, gpointer user_data, glong Val);
      void dispDMILAsynchronousMode(GtkAction *action, gpointer user_data, glong Val);
      void dispDMILCompressMode(GtkAction *action, gpointer user_data, glong Val);
      void dispDMILQFactorMode(GtkAction *action, gpointer user_data, glong Val);

      static void viewStandardToolbar(GtkAction *action, gpointer user_data);
      static void viewDisplayToolbar(GtkAction *action, gpointer user_data);
      static void viewStatusBar(GtkAction *action, gpointer user_data);
      static void about(GtkAction *action, gpointer user_data);

      static void OnDestroy(GtkWidget *widget, gpointer user_data);
      static void OnCbInterpolationChanged(GtkWidget *widget, gpointer user_data);
      static void OnCbViewChanged(GtkWidget *widget, gpointer user_data);
      static void OnInterpolationModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data);
      static void OnViewModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data);
      static void OnDMILQFactorModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data);
      static void OnDMILAsyncModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data);
      static void OnDMILCompressModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data);
      static void OnConnectProxy(GtkUIManager *uimanager, GtkAction *action, GtkWidget *proxy, gpointer user_data); 

   private:
      
      void setActive(const gchar* name, bool value);
      void setEnable(const gchar* name, bool value);
      void RegisterMilStockIcons();
      void updateActions(ChildFrame *cf);
      MdispGtkApp* dispGtkApp();

      bool             m_Update;
      ChildFrame *     m_cf;        //current frame;
      GtkWidget*       m_MainFrame;
      GtkWidget*       m_StatusBar;
      GtkWidget*       m_ViewComboBox;
      GtkWidget*       m_HandleBoxStd;
      GtkWidget*       m_HandleBoxDisp;
      GtkWidget*       m_InterpolationComboBox;
      GtkUIManager*    m_MergeUI;
      GtkActionGroup*  m_actions;
      GList*           m_ChildList; 
   };
#endif
