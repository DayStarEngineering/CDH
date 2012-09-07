#include <gtk/gtk.h>
#include "mainframe.h"
#include "childframe.h"
#include "mdispgtkview.h"
#include "roidlg.h"
#include <mil.h>
#include "mdispgtk.h"

// Menu & Toolbar definition
static const gchar *ui_info = 
"<ui>"
"  <menubar name='MenuBar'>"
"    <menu action='FileMenu'>"
"      <menuitem action='New'/>"
"      <menuitem action='Open'/>"
"      <menuitem action='Close'/>"
"      <menuitem action='Save'/>"
"      <menuitem action='SaveAs'/>"
"      <separator/>"
"      <menuitem action='SaveRoiAs'/>"
"      <separator/>"
"      <menuitem action='Quit'/>"
"    </menu>"
"    <menu action='ViewMenu'>"
"      <menuitem action='StdToolbar'/>"
"      <menuitem action='DispToolbar'/>"
"      <menuitem action='StatusBar'/>"
"     </menu>"
"    <menu action='DisplayMenu'>"
"      <menuitem action='Overlay'/>"
"      <menuitem action='FillDisplay'/>"
"      <menuitem action='NoTearing'/>"
"      <menuitem action='X11Annotation'/>"
"      <menuitem action='GraphicsAnnotations'/>"
"     <menu action='InterpolationModeMenu'>"
"	      <menuitem action='Nearest'/>"
"	      <menuitem action='Fast'/>"
"	      <menuitem action='Default2'/>"
"     </menu>"
"     <menu action='ViewModeMenu'>"
"	      <menuitem action='Default'/>"
"	      <menuitem action='Transparent'/>"
"	      <menuitem action='AutoScale'/>"
"	      <menuitem action='MultiBytes'/>"
"	      <menuitem action='BitShift2'/>"
"	      <menuitem action='BitShift4'/>"
"	      <menuitem action='BitShift8'/>"
"     </menu>"
"     <menu action='ZoomMenu'>"
"	      <menuitem action='NoZoom'/>"
"	      <menuitem action='ZoomIn'/>"
"	      <menuitem action='ZoomOut'/>"
"     </menu>"
"      <separator/>"
"     <menu action='DMILMenu'>"
"        <menu action='DMILASyncMenu'>"
"	         <menuitem action='Disabled'/>"
"	         <menuitem action='1'/>"
"	         <menuitem action='5'/>"
"	         <menuitem action='10'/>"
"	         <menuitem action='15'/>"
"	         <menuitem action='30'/>"
"	         <menuitem action='MaxRate'/>"
"        </menu>"
"        <menu action='DMILCompressMenu'>"
"	         <menuitem action='None'/>"
"	         <menuitem action='Lossy'/>"
"	         <menuitem action='Lossless'/>"
"        </menu>"
"        <menu action='DMILQFactorMenu'>"
"	         <menuitem action='60'/>"
"	         <menuitem action='70'/>"
"	         <menuitem action='75'/>"
"	         <menuitem action='80'/>"
"	         <menuitem action='82'/>"
"	         <menuitem action='85'/>"
"	         <menuitem action='87'/>"
"	         <menuitem action='90'/>"
"	         <menuitem action='92'/>"
"	         <menuitem action='95'/>"
"	         <menuitem action='99'/>"
"        </menu>"
"     </menu>"
"     <separator/>"
"     <menuitem action='RoiDefine'/>"
"     <menuitem action='RoiShow'/>"
"     <menuitem action='RoiPref'/>"
"      <separator/>"
"     <menu action='ExclusiveMenu'>"
"	     <menuitem action='RestrictCursor'/>"
"     </menu>"
"    </menu>"
"    <menu action='GrabMenu'>"
"      <menuitem action='GrabStart'/>"
"      <menuitem action='GrabStop'/>"
"    </menu>"
"    <menu action='HelpMenu'>"
"      <menuitem action='About'/>"
"    </menu>"
"  </menubar>"
"  <toolbar  name='ToolBarStd'>"
"    <toolitem action='New'/>"
"    <toolitem action='Open'/>"
"    <toolitem action='Save'/>"
"    <toolitem action='GrabStart'/>"
"    <toolitem action='GrabStop'/>"
"  </toolbar>"
"  <toolbar  name='ToolBarDisp'>"
"    <toolitem action='Overlay'/>"
"    <toolitem action='ZoomIn'/>"
"    <toolitem action='ZoomOut'/>"
"    <toolitem action='NoZoom'/>"
"    <toolitem action='FillDisplay'/>"
"    <toolitem action='X11Annotation'/>"
"    <toolitem action='GraphicsAnnotations'/>"
"    <toolitem action='NoTearing'/>"
"    <toolitem action='RoiDefine'/>"
"    <toolitem action='RoiShow'/>"
"  </toolbar>"
"</ui>";

// Actions
static GtkToggleActionEntry display_entries[] = {
   { "StdToolbar",NULL, "Standard _Toolbar", NULL, "Standard Toolbar", G_CALLBACK (MainFrame::viewStandardToolbar), true},
   { "DispToolbar",NULL,  "_Display Toolbar", NULL, "Display Toolbar", G_CALLBACK (MainFrame::viewDisplayToolbar), true},
   { "StatusBar",NULL,  "_Status Bar", NULL, "Status Bar", G_CALLBACK (MainFrame::viewStatusBar),true },
   { "Overlay","mil-stock-overlay", "_Overlay", "<control><shift>O","Overlay",G_CALLBACK (MainFrame::dispOverlay),false},
   { "FillDisplay","mil-stock-filldisplay", "_Fill Display", "<control><shift>F","Fill Display",G_CALLBACK (MainFrame::dispFillDisplay),false },
   { "NoTearing","mil-stock-no-tearing", "_No Tearing", "<control><shift>T","No Tearing",G_CALLBACK (MainFrame::dispNoTearing),false },
   { "X11Annotation","mil-stock-annotations", "_X11 Annotations", "<control><shift>X","X11 Annotations",G_CALLBACK (MainFrame::dispX11Annotations),false },
   { "GraphicsAnnotations","mil-stock-graphics", "Graphics Annotations", "<control><shift>G","Graphics Annotations",G_CALLBACK (MainFrame::dispGraphicsAnnotations),false },
   { "RoiDefine","mil-stock-roi", "ROI Define", "","Define ROI",G_CALLBACK (MainFrame::dispRoiDefine),false},
   { "RoiShow","mil-stock-roi-show", "ROI Show", "","Show ROI",G_CALLBACK (MainFrame::dispRoiShow),true },
   { "RestrictCursor",NULL, "Restrict Cursor", "","Restrcit Cursor",G_CALLBACK (MainFrame::dispRestrictCursor),true },

}; 
static guint n_display_entries = G_N_ELEMENTS (display_entries);

static GtkRadioActionEntry interpolation_mode_entries[] = {
   { "Nearest",   NULL,"M__NEAREST__NEIGHBOR", "<control><alt>N","M_NEAREST_NEIGHBOR", INTERPOLATION_MODE_NEAREST_NEIGHBOR }, 
   { "Fast",     NULL, "M__FAST",    "<control><shift>F","M_FAST",INTERPOLATION_MODE_FAST },      
   { "Default2", NULL, "M__DEFAULT", "<control><alt>D","M_DEFAULT", INTERPOLATION_MODE_DEFAULT },                  
};
static guint n_interpolation_mode_entries = G_N_ELEMENTS (interpolation_mode_entries);

static  GtkRadioActionEntry view_mode_entries[] = {
   { "Default", NULL,    "M__DEFAULT",      NULL,"M_DEFAULT", VIEW_MODE_DEFAULT },                  
   { "Transparent", NULL,"M__TRANSPARENT",  NULL,"M_TRANSPARENT", VIEW_MODE_TRANSPARENT }, 
   { "AutoScale", NULL,  "M__AUTO__SCALE",  NULL,"M_AUTO_SCALE",VIEW_MODE_AUTO_SCALE },      
   { "MultiBytes", NULL, "M__MULTI__BYTES", NULL,"M_MULTI_BYTES",VIEW_MODE_MULTI_BYTES },      
   { "BitShift2", NULL,  "M__BIT__SHIFT:2", NULL,"M_BIT_SHIFT:2 ",VIEW_MODE_BIT_SHIFT2 },      
   { "BitShift4", NULL,  "M__BIT__SHIFT:4", NULL,"M_BIT_SHIFT:4",VIEW_MODE_BIT_SHIFT4 },      
   { "BitShift8", NULL,  "M__BIT__SHIFT:8", NULL,"M_BIT_SHIFT:8",VIEW_MODE_BIT_SHIFT8 },      

};
static guint n_view_mode_entries = G_N_ELEMENTS (view_mode_entries);


static  GtkRadioActionEntry dmil_asynchronous_entries[] = {
   { "Disabled", NULL, "Disabled",     "<control><shift>D", "Disable asynchronous mode", DMIL_ASYNC_DISABLE },
   { "1"       , NULL, "1 fps",        "<control><shift>1", "Update to display is limited to 1 fps in asynchronous mode", DMIL_ASYNC_1  }, 
   { "5"       , NULL, "5 fps",        "<control><shift>2", "Update to display is limited to 5 fps in asynchronous mode", DMIL_ASYNC_5  },
   { "10"      , NULL, "10 fps",       "<control><shift>3", "Update to display is limited to 10 fps in asynchronous mode", DMIL_ASYNC_10 },
   { "15"      , NULL, "15 fps",       "<control><shift>4", "Update to display is limited to 15 fps in asynchronous mode", DMIL_ASYNC_15 },
   { "30"      , NULL, "30 fps",       "<control><shift>5", "Update to display is limited to 30 fps in asynchronous mode", DMIL_ASYNC_30 },
   { "MaxRate" , NULL, "Mamimum rate", "<control><shift>0", "Asyncghronous update as fast as possible", DMIL_ASYNC_MAX },

};
static guint n_dmil_asynchronous_entries = G_N_ELEMENTS (dmil_asynchronous_entries);

static  GtkRadioActionEntry dmil_compress_entries[] = {
   { "None"      , NULL, "None",     "<control><shift>N", "No Compression", DMIL_COMPRESS_NONE },                  
   { "Lossy"     , NULL, "Lossy",    "<control><shift>Y", "Lossy JPEG compression", DMIL_COMPRESS_LOSSY  }, 
   { "Lossless"  , NULL, "Lossless", "<control><shift>L", "Lossless JPEG compression", DMIL_COMPRESS_LOSSLESS  },      
};
static guint n_dmil_compress_entries = G_N_ELEMENTS (dmil_compress_entries);

static  GtkRadioActionEntry dmil_qfactor_entries[] = {
   { "60", NULL, "60",NULL, "Q factor of 60 for lossy compression", DMIL_QFACTOR_60 },                  
   { "70", NULL, "70",NULL, "Q factor of 70 for lossy compression", DMIL_QFACTOR_70 },                  
   { "75", NULL, "75",NULL, "Q factor of 75 for lossy compression", DMIL_QFACTOR_75 },                  
   { "80", NULL, "80",NULL, "Q factor of 80 for lossy compression", DMIL_QFACTOR_80 },                  
   { "82", NULL, "82",NULL, "Q factor of 82 for lossy compression", DMIL_QFACTOR_82 },                  
   { "85", NULL, "85",NULL, "Q factor of 85 for lossy compression", DMIL_QFACTOR_85 },                  
   { "87", NULL, "87",NULL, "Q factor of 87 for lossy compression", DMIL_QFACTOR_87 },                  
   { "90", NULL, "90",NULL, "Q factor of 90 for lossy compression", DMIL_QFACTOR_90 },                  
   { "92", NULL, "92",NULL, "Q factor of 92 for lossy compression", DMIL_QFACTOR_92 },                  
   { "95", NULL, "95",NULL, "Q factor of 95 for lossy compression", DMIL_QFACTOR_95 },                  
   { "99", NULL, "99",NULL, "Q factor of 99 for lossy compression", DMIL_QFACTOR_99 },                  
};
static guint n_dmil_qfactor_entries = G_N_ELEMENTS (dmil_qfactor_entries);


static GtkActionEntry entries[] = {
  { "FileMenu", NULL, "_File" },
  { "ViewMenu", NULL, "_View" },
  { "DisplayMenu", NULL, "_Display" },
  { "GrabMenu", NULL, "_Grab" },
  { "HelpMenu", NULL, "_Help" },
  { "InterpolationModeMenu", NULL, "Interpolation Mode "},
  { "ViewModeMenu", NULL, "View Mode "},
  { "ZoomMenu", NULL, "Zoom "},
  { "DMILMenu", NULL, "Distributed MIL"},
  { "DMILASyncMenu", NULL, "Asynchronous Mode"},
  { "DMILCompressMenu", NULL, "Compression"},
  { "DMILQFactorMenu", NULL, "Q Factor"},
  { "ExclusiveMenu", NULL, "Exclusive Display"},
  { "New",   GTK_STOCK_NEW,  "_New",  "<control>N","New Image..."  ,G_CALLBACK (MainFrame::fileNew) },      
  { "Open",  GTK_STOCK_OPEN, "_Open", "<control>O","Open Image ...", G_CALLBACK (MainFrame::fileOpen) }, 
  { "Close", GTK_STOCK_CLOSE,"_Close","<control>C","Close Image",G_CALLBACK (MainFrame::fileClose) },
  { "Save",  GTK_STOCK_SAVE, "_Save", "<control>S","Save current file",G_CALLBACK (MainFrame::fileSave) },
  { "SaveAs",GTK_STOCK_SAVE, "Save _As...", NULL,  "Save to a file", G_CALLBACK (MainFrame::fileSaveAs) },
  { "SaveRoiAs",GTK_STOCK_SAVE, "Save _ROI As...", NULL,  "Save to ROI a file", G_CALLBACK (MainFrame::fileSaveRoiAs) },
  { "Quit",  GTK_STOCK_QUIT, "_Quit", "<control>Q","Quit",G_CALLBACK (MainFrame::fileQuit) },

  { "NoZoom","mil-stock-no-zoom", "_No Zoom ", "<control><shift>W","Zoom 1:1",G_CALLBACK (MainFrame::dispNoZoom)},
  { "ZoomIn","mil-stock-zoom-in", "Zoom In", "minus","Zoom In",G_CALLBACK (MainFrame::dispZoomIn)},
  { "ZoomOut","mil-stock-zoom-out", "Zoom Out", "plus","Zoom Out",G_CALLBACK (MainFrame::dispZoomOut)},
  
  { "GrabStart","mil-stock-grab-start", "Grab Start", "<control><shift>G","Grab Start",G_CALLBACK (MainFrame::dispGrabStart)},
  { "GrabStop","mil-stock-grab-stop", "Grab Stop", "<control><shift>H","Grab Stop",G_CALLBACK (MainFrame::dispGrabStop)},

  { "RoiPref",NULL, "ROI Preferences ...", "","ROI Preferences",G_CALLBACK (MainFrame::dispRoiPrefs) },

  { "About", NULL,"_About", "<control>A","About", G_CALLBACK (MainFrame::about) },
};
static guint n_entries = G_N_ELEMENTS (entries);

// Icons
static struct { 
  const gchar *filename;
  const gchar *stock_id;
} stock_icons[] = {
  { "about.png",       "mil-stock-about" },
  { "annotations.png", "mil-stock-annotations" },
  { "graphics.png",    "mil-stock-graphics" },
  { "filldisplay.png", "mil-stock-filldisplay" },
  { "grabstart.png",   "mil-stock-grab-start" },
  { "grabstop.png",    "mil-stock-grab-stop" },
  { "notearing.png",   "mil-stock-no-tearing" },
  { "nozoom.png",      "mil-stock-no-zoom" },
  { "overlay.png",     "mil-stock-overlay" },
  { "roi.png",         "mil-stock-roi" },
  { "roishow.png",     "mil-stock-roi-show" },
  { "zoomin.png",      "mil-stock-zoom-in" },
  { "zoomout.png",     "mil-stock-zoom-out" },
  { "imaging.png",     "mil-stock-imaging" },
};
static gint n_stock_icons = G_N_ELEMENTS (stock_icons);

/////////////////////////////////////////////////////////////////////////////
// MainFrame
// Create the Main Window
//
MainFrame::MainFrame()
   {
   m_ChildList              = NULL;
   m_cf                     = NULL;
   m_Update                 = true;
   GtkWidget* vbox          = NULL;
   GtkWidget* bar           = NULL;
   //GtkToolItem* item_inter  = NULL;
   GtkToolItem* item_view   = NULL;
   GdkPixbuf*   pixbufIcon  = NULL;
   gchar*       filename    = NULL;
   GError*      error       = NULL;
   GdkWindowTypeHint hint = GDK_WINDOW_TYPE_HINT_UTILITY;
   
   m_MainFrame = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(m_MainFrame), "MdispGtk");
   gtk_window_set_default_size (GTK_WINDOW (m_MainFrame), 600, 100);
   gtk_window_set_type_hint (GTK_WINDOW (m_MainFrame), hint);

   // main window properties
   filename = g_strdup_printf("%s/examples/mdispgtk/images/imaging.png",g_getenv("MILDIR"));
   pixbufIcon = gdk_pixbuf_new_from_file(filename,NULL);
   g_free(filename);

   // Register some icons
   RegisterMilStockIcons();

   vbox = gtk_vbox_new (false, 0);
   gtk_container_add (GTK_CONTAINER (m_MainFrame), vbox);

   m_StatusBar = gtk_statusbar_new ();
   gtk_box_pack_end (GTK_BOX (vbox), m_StatusBar, false, false, 0);

   // Add Actions
   m_actions = gtk_action_group_new ("AppWindowActions");
   gtk_action_group_add_actions (m_actions, 
                                 entries, 
                                 n_entries, 
                                 this);
   gtk_action_group_add_toggle_actions (m_actions, 
                                        display_entries, 
                                        n_display_entries, 
                                        this); 
   gtk_action_group_add_radio_actions (m_actions, 
                                       interpolation_mode_entries, 
                                       n_interpolation_mode_entries,
                                       INTERPOLATION_MODE_DEFAULT,
                                       G_CALLBACK (MainFrame::OnInterpolationModeAction),
                                       this);

   gtk_action_group_add_radio_actions (m_actions,
                                       view_mode_entries, n_view_mode_entries,
                                       VIEW_MODE_DEFAULT,
                                       G_CALLBACK (MainFrame::OnViewModeAction),
                                       this);

   gtk_action_group_add_radio_actions (m_actions,
                                       dmil_asynchronous_entries, n_dmil_asynchronous_entries,
                                       DMIL_ASYNC_DISABLE,
                                       G_CALLBACK (MainFrame::OnDMILAsyncModeAction),
                                       this);

   gtk_action_group_add_radio_actions (m_actions,
                                       dmil_compress_entries, n_dmil_compress_entries,
                                       DMIL_COMPRESS_NONE,
                                       G_CALLBACK (MainFrame::OnDMILCompressModeAction),
                                       this);
   gtk_action_group_add_radio_actions (m_actions,
                                       dmil_qfactor_entries, n_dmil_qfactor_entries,
                                       DMIL_QFACTOR_60,
                                       G_CALLBACK (MainFrame::OnDMILQFactorModeAction),
                                       this);

   m_MergeUI = gtk_ui_manager_new ();
   g_signal_connect (m_MergeUI, "connect-proxy", G_CALLBACK (MainFrame::OnConnectProxy), this);
   g_object_set_data_full (G_OBJECT (m_MainFrame), "ui-manager", m_MergeUI, g_object_unref);
   gtk_ui_manager_insert_action_group (m_MergeUI, m_actions, 0);
   gtk_window_add_accel_group (GTK_WINDOW (m_MainFrame), 
                               gtk_ui_manager_get_accel_group (m_MergeUI));
   
   if (!gtk_ui_manager_add_ui_from_string (m_MergeUI, ui_info, -1, &error))
      {
      g_message ("building menus failed: %s", error->message);
      g_error_free (error);
      }

   bar = gtk_ui_manager_get_widget (m_MergeUI, "/MenuBar");
   gtk_box_pack_start (GTK_BOX (vbox), bar, false, false, 0);

   // put standard toolbar in a handle box
   m_HandleBoxStd = gtk_handle_box_new ();
   gtk_box_pack_start (GTK_BOX (vbox), m_HandleBoxStd, true, true, 1);

   bar = gtk_ui_manager_get_widget (m_MergeUI, "/ToolBarStd");
   gtk_toolbar_set_tooltips (GTK_TOOLBAR (bar), true);
   gtk_toolbar_set_style (GTK_TOOLBAR (bar),  GTK_TOOLBAR_ICONS);
   gtk_container_add (GTK_CONTAINER (m_HandleBoxStd), bar);

   // put display toolbar in a handle box
   m_HandleBoxDisp = gtk_handle_box_new ();
   gtk_box_pack_start (GTK_BOX (vbox), m_HandleBoxDisp, true, true, 1);

   bar = gtk_ui_manager_get_widget (m_MergeUI, "/ToolBarDisp");
   gtk_toolbar_set_tooltips (GTK_TOOLBAR (bar), true);
   gtk_toolbar_set_style (GTK_TOOLBAR (bar),  GTK_TOOLBAR_ICONS);
   gtk_container_add (GTK_CONTAINER (m_HandleBoxDisp), bar);

   // interpolation mode 
   m_InterpolationComboBox = gtk_combo_box_new_text();
   for (int i=0 ; i< (int) n_interpolation_mode_entries; i++)
      {
      gtk_combo_box_append_text(GTK_COMBO_BOX(m_InterpolationComboBox),interpolation_mode_entries[i].label);
      }
   gtk_combo_box_set_active (GTK_COMBO_BOX(m_InterpolationComboBox),0);


   // view mode
   m_ViewComboBox = gtk_combo_box_new_text();
   for (int i=0 ; i< (int) n_view_mode_entries; i++)
      {
      gtk_combo_box_append_text(GTK_COMBO_BOX(m_ViewComboBox),view_mode_entries[i].label);
      }
   gtk_combo_box_set_active (GTK_COMBO_BOX(m_ViewComboBox),0);

#if 0
   item_inter = gtk_tool_item_new();
   gtk_container_add(GTK_CONTAINER(item_inter),m_InterpolationComboBox);
   gtk_toolbar_insert(GTK_TOOLBAR(bar),GTK_TOOL_ITEM(item_inter),6);
#endif
   item_view = gtk_tool_item_new();
   gtk_container_add(GTK_CONTAINER(item_view),m_ViewComboBox);
   gtk_toolbar_insert(GTK_TOOLBAR(bar),GTK_TOOL_ITEM(item_view),-1);

   // attach callbscks
   g_signal_connect (m_InterpolationComboBox,"changed",G_CALLBACK(MainFrame::OnCbInterpolationChanged),this);
   g_signal_connect (m_ViewComboBox,"changed",G_CALLBACK(MainFrame::OnCbViewChanged),this);
   
   g_signal_connect (m_MainFrame,"destroy",G_CALLBACK(MainFrame::OnDestroy),this);

   gtk_widget_show_all (m_MainFrame);
   updateActions(0);
   }

/////////////////////////////////////////////////////////////////////////////
// MainFrame
// Destructor
//
MainFrame::~MainFrame()
   {
   g_object_unref(G_OBJECT(m_MergeUI));
   }

/////////////////////////////////////////////////////////////////////////////
// setActive
// Activate action
//
void MainFrame::setActive(const gchar* name, bool newvalue)
   {
   GtkAction *action = NULL;
   bool oldvalue;
   action = gtk_action_group_get_action(m_actions,name);
   if(action)
      {
      oldvalue =  gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
      if(oldvalue != newvalue)
         {
         Update(false);
         gtk_toggle_action_set_active(GTK_TOGGLE_ACTION(action),newvalue);
         Update(true);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// setEnable
// Enable action
//
void MainFrame::setEnable(const gchar* name, bool value)
   {
   GtkAction* action = NULL;
   action = gtk_action_group_get_action(m_actions,name);
   if(action)
      {
      g_object_set(G_OBJECT(action), "sensitive", value, NULL);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// setcf
// set current child frame
//
void MainFrame::setcf(ChildFrame* cf)
   {
   m_cf= cf; 
   updateActions(cf);
   }
/////////////////////////////////////////////////////////////////////////////
// dispGtkApp
// Get App 
// 
MdispGtkApp* MainFrame::dispGtkApp()
   {
   void *UserData = g_object_get_data(G_OBJECT(m_MainFrame),"App");
   return (MdispGtkApp *) UserData;
   }

/////////////////////////////////////////////////////////////////////////////
// action_status_destroy
// used for tooltips
//
static void action_status_destroy (gpointer data)
   {
   ActionStatus *action_status = (ActionStatus *) data;
   
   g_object_unref (action_status->action);
   g_object_unref (action_status->statusbar);
   
   g_free (action_status);
   }
/////////////////////////////////////////////////////////////////////////////
// RegisterMilStockIcons
// register some icons
//
void MainFrame::RegisterMilStockIcons()
   {
   GtkIconFactory *icon_factory;
   GtkIconSet *icon_set; 
   GtkIconSource *icon_source;
   gint i;
   const gchar *mildir = g_getenv("MILDIR");
   
   icon_factory = gtk_icon_factory_new ();
   
   for (i = 0; i < n_stock_icons; i++) 
      {
      gchar *filename;
      filename = g_strdup_printf("%s/%s/%s",mildir,GTK_MIL_IMAGES_DIR,stock_icons[i].filename);
      icon_set = gtk_icon_set_new ();
      icon_source = gtk_icon_source_new ();
      gtk_icon_source_set_filename (icon_source, filename);
      gtk_icon_set_add_source (icon_set, icon_source);
      gtk_icon_source_free (icon_source);
      gtk_icon_factory_add (icon_factory, stock_icons[i].stock_id, icon_set);
      gtk_icon_set_unref (icon_set);
      g_free(filename);
      }
   
   gtk_icon_factory_add_default (icon_factory); 
   g_object_unref (icon_factory);
   }
/////////////////////////////////////////////////////////////////////////////
// set_tip
// set tooltip
//
static void set_tip (GtkWidget *widget)
   {
   ActionStatus *data;
   gchar *tooltip;
  
   data = (ActionStatus *) g_object_get_data (G_OBJECT (widget), "action-status");
   
   if (data) 
      {
      g_object_get (data->action, "tooltip", &tooltip, NULL);
      gtk_statusbar_push (GTK_STATUSBAR (data->statusbar), 0,  tooltip ? tooltip : "");
      g_free (tooltip);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// unset_tip
// unset tooltip
//
static void unset_tip (GtkWidget *widget)
   {
   ActionStatus *data;
   
   data = (ActionStatus *) g_object_get_data (G_OBJECT (widget), "action-status");
   
   if (data)
      {
      gtk_statusbar_pop (GTK_STATUSBAR (data->statusbar), 0);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// OnConnectProxy
// Connect Tooltips to StatusBar
//
void MainFrame::OnConnectProxy(GtkUIManager *uimanager, GtkAction *action, GtkWidget *proxy, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   if (GTK_IS_MENU_ITEM (proxy)) 
      {
      ActionStatus *data;
      
      data = (ActionStatus *) g_object_get_data (G_OBJECT (proxy), "action-status");
      if (data)
         {
         g_object_unref (data->action);
         g_object_unref (data->statusbar);

         data->action    = (GtkAction *) g_object_ref (action);
         data->statusbar = (GtkWidget *) g_object_ref (mf->m_StatusBar);
         }
      else
         {
         data = g_new0 (ActionStatus, 1);

         data->action    = (GtkAction *) g_object_ref (action);
         data->statusbar = (GtkWidget *) g_object_ref (mf->m_StatusBar);

         g_object_set_data_full (G_OBJECT (proxy), "action-status",  data, action_status_destroy);
	  
         g_signal_connect (proxy, "select",  G_CALLBACK (set_tip), NULL);
         g_signal_connect (proxy, "deselect", G_CALLBACK (unset_tip), NULL);
         }
      }   
   }
/////////////////////////////////////////////////////////////////////////////
// OnInterpolationModeAction
// user choose new Interpolation Mode
//
void MainFrame::OnInterpolationModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data)
   {
   MainFrame* UserData = (MainFrame *) user_data;
   const gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
   if(value <= (gint) n_interpolation_mode_entries)
      {
      gtk_combo_box_set_active (GTK_COMBO_BOX(UserData->m_InterpolationComboBox),value); 
      switch(value)
         {
         case INTERPOLATION_MODE_DEFAULT :
            UserData->dispInterMode((GtkAction *)current, UserData, M_DEFAULT);
            break;
         case INTERPOLATION_MODE_FAST:
            UserData->dispInterMode((GtkAction *)current, UserData, M_FAST);
            break;
         case INTERPOLATION_MODE_NEAREST_NEIGHBOR:
            UserData->dispInterMode((GtkAction *)current, UserData, M_NEAREST_NEIGHBOR);
            break;
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// OnViewModeAction
// user choose new View Mode
//
void MainFrame::OnViewModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data)
   {
   MainFrame* UserData = (MainFrame *) user_data;
   const gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
   if(value <= (gint) n_view_mode_entries)
      {
      gtk_combo_box_set_active (GTK_COMBO_BOX(UserData->m_ViewComboBox),value); 
      switch(value)
         {
         case VIEW_MODE_BIT_SHIFT8 :
            UserData->dispViewModeShift((GtkAction *)current, UserData,8);
            break;
         case VIEW_MODE_BIT_SHIFT4:
            UserData->dispViewModeShift((GtkAction *)current, UserData,4);
            break;
         case VIEW_MODE_BIT_SHIFT2:
            UserData->dispViewModeShift((GtkAction *)current, UserData,2);
            break;
         case VIEW_MODE_MULTI_BYTES:
            UserData->dispViewMode((GtkAction *) current, UserData, M_MULTI_BYTES);
            break;
         case VIEW_MODE_AUTO_SCALE:
            UserData->dispViewMode((GtkAction *) current, UserData, M_AUTO_SCALE);
            break;
         case VIEW_MODE_TRANSPARENT:
            UserData->dispViewMode((GtkAction *) current, UserData, M_TRANSPARENT);
         break;
         case VIEW_MODE_DEFAULT:
            UserData->dispViewMode((GtkAction *) current, UserData, M_DEFAULT);
            break;
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// OnDMILAsyncAction
// user choose Distributed MIL Asynchronous  Mode
//
void MainFrame::OnDMILAsyncModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data)
   {
   MainFrame* UserData = (MainFrame *) user_data;
   const gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
   if(value <= (gint) n_dmil_asynchronous_entries)
      {
      switch(value)
         {
         case DMIL_ASYNC_DISABLE :
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, M_DISABLE);
            break;
         case DMIL_ASYNC_1:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, 1);
            break;
         case DMIL_ASYNC_5:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, 5);
            break;
         case DMIL_ASYNC_10:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, 10);
            break;
         case DMIL_ASYNC_15:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, 15);
            break;
         case DMIL_ASYNC_30:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, 30);
            break;
         case DMIL_ASYNC_MAX:
            UserData->dispDMILAsynchronousMode((GtkAction *)current, UserData, M_INFINITE);
            break;
         }
      }
   }

/////////////////////////////////////////////////////////////////////////////
// OnDMILAsyncAction
// user choose Distributed MIL Compress  Mode
//
void MainFrame::OnDMILCompressModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data)
   {
   MainFrame* UserData = (MainFrame *) user_data;
   g_return_if_fail(UserData);
   const gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
   if(value <= (gint) n_dmil_compress_entries)
      {
      switch(value)
         {
         case DMIL_COMPRESS_NONE :
            UserData->dispDMILCompressMode((GtkAction *)current, UserData, M_NULL);
            break;
         case DMIL_COMPRESS_LOSSY:
            UserData->dispDMILCompressMode((GtkAction *)current, UserData, M_JPEG_LOSSY);
            break;
         case DMIL_COMPRESS_LOSSLESS:
            UserData->dispDMILCompressMode((GtkAction *)current, UserData, M_JPEG_LOSSLESS);
            break;
         }
      }
   }


/////////////////////////////////////////////////////////////////////////////
// OnDMILAsyncAction
// user choose Distributed MIL Q Factor Mode
//
void MainFrame::OnDMILQFactorModeAction(GtkAction *action, GtkRadioAction *current, gpointer user_data)
   {
   MainFrame* UserData = (MainFrame *) user_data;
   g_return_if_fail(UserData);
   const gint value = gtk_radio_action_get_current_value (GTK_RADIO_ACTION (current));
   if(value <= (gint) n_dmil_qfactor_entries)
      {
      switch(value)
         {
         case DMIL_QFACTOR_60 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 60);
            break;
         case DMIL_QFACTOR_70 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 70);
            break;
         case DMIL_QFACTOR_75 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 75);
            break;
         case DMIL_QFACTOR_80 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 80);
            break;
         case DMIL_QFACTOR_82 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 82);
            break;
         case DMIL_QFACTOR_85 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 85);
            break;
         case DMIL_QFACTOR_87 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 87);
            break;
         case DMIL_QFACTOR_90 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 90);
            break;
         case DMIL_QFACTOR_92 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 92);
            break;
         case DMIL_QFACTOR_95 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 95);
            break;
         case DMIL_QFACTOR_99 :
            UserData->dispDMILQFactorMode((GtkAction *)current, UserData, 99);
            break;
         }
      }
   }


/////////////////////////////////////////////////////////////////////////////
// OnCbInterpolationChanged
// 
//
void MainFrame::OnCbInterpolationChanged(GtkWidget* widget, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;  
   g_return_if_fail(mf);
   gint i = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
   GtkAction *action;

   action= gtk_action_group_get_action(mf->m_actions,interpolation_mode_entries[i].name); 
   if(action) 
      gtk_action_activate(action); 
   }
/////////////////////////////////////////////////////////////////////////////
// OnCbViewChanged
// 
//
void MainFrame::OnCbViewChanged(GtkWidget *widget, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;   
   g_return_if_fail(mf);
   gint i = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
   GtkAction *action;
   
  action= gtk_action_group_get_action(mf->m_actions,view_mode_entries[i].name); 
  if(action) 
     gtk_action_activate(action); 
   }
/////////////////////////////////////////////////////////////////////////////
// remove
// remove child frame from the list
// 
void MainFrame::remove(ChildFrame *cf)
   {
   m_ChildList = g_list_remove(m_ChildList,cf);
   if(g_list_length(m_ChildList))
      {
      GList* l = g_list_last(m_ChildList);
      setcf((ChildFrame *) l->data);
      }
   else
      {
      setcf(NULL);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// add
// add child frame tio list of childs
//
void MainFrame::add(ChildFrame *cf)
   {
   if(cf)
      {
      m_ChildList = g_list_append(m_ChildList,cf);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// fileNew
// 
//
void MainFrame::fileNew (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = new ChildFrame(mf);

   if(!cf->View()->newDoc())
      {
      GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_CLOSE,
                                                         "Could not create new document");
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      cf->close();
      }
   else
      {
      mf->add(cf);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// fileOpen
//
//
void MainFrame::fileOpen (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   GtkWidget *dialog = gtk_file_selection_new("Open file"); 
   if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK) 
      { 
      const gchar *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (dialog)); 
      if(filename)
         {
         ChildFrame* cf = new ChildFrame(mf);
         if ( !cf->View()->load(filename) )
            {
            GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_CLOSE,
                                                        "Could not load image from %s", filename);
            gtk_dialog_run (GTK_DIALOG (dialog));
            gtk_widget_destroy (dialog);
            cf->close();
            }
         else
            {
            cf->setTitle(g_path_get_basename(filename));
            mf->add(cf);
            }
         mf->updateActions(cf); 
         }
      }

   gtk_widget_destroy (dialog);
   }
/////////////////////////////////////////////////////////////////////////////
// fileSave
// 
//
void MainFrame::fileSave (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf)
      mf->fileSaveAs(action, user_data);
   }

/////////////////////////////////////////////////////////////////////////////
// fileClose
// 
//
void MainFrame::fileClose (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->close();
      }
   
   }
/////////////////////////////////////////////////////////////////////////////
// fileSaveAs
// 
//
void MainFrame::fileSaveAs (GtkAction *action, gpointer user_data)
   {
   MainFrame*  mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if(cf)
      {
      GtkWidget *dialog = gtk_file_selection_new("Save file"); 
      gtk_file_selection_set_filename(GTK_FILE_SELECTION (dialog),cf->View()->filename()); 
      if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK) 
         { 
         const gchar *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (dialog)); 
         if(filename) 
            { 
            cf->View()->save(filename); 
            cf->setTitle(g_path_get_basename(filename)); 
            }
         }
      gtk_widget_destroy (dialog);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// fileSaveRoiAs
// 
//
void MainFrame::fileSaveRoiAs (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if(cf)
      {
      GtkWidget *dialog = gtk_file_selection_new("Save ROI As"); 
      if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK) 
         { 
         const gchar *filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (dialog)); 
         if(filename) 
            { 
            cf->View()->saveROIAs(filename); 
            } 
         }
      gtk_widget_destroy (dialog);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// fileQuit
// 
//
void MainFrame::fileQuit (GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf)
      {
      mf->OnDestroy(NULL,mf);
      }

   }
/////////////////////////////////////////////////////////////////////////////
// dispNoZoom
// 
//
void MainFrame::dispNoZoom(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->NoZoom();
      mf->updateActions(cf);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispZoomIn
// 
//
void MainFrame::dispZoomIn(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ZoomIn();
      mf->updateActions(cf);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispZoomOut
// 
//
void MainFrame::dispZoomOut(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ZoomOut();
      mf->updateActions(cf);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispGrabStart
//
//
void MainFrame::dispGrabStart(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->GrabStart();
      mf->updateActions(cf);
      }

   }
/////////////////////////////////////////////////////////////////////////////
// dispGrabStop
//
//
void MainFrame::dispGrabStop(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->GrabStop();
      mf->updateActions(cf);
      }

   }
/////////////////////////////////////////////////////////////////////////////
// dispRoiPrefs
// 
//
void MainFrame::dispRoiPrefs(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      ROIDialog* roidlg = new ROIDialog(cf->View()->MilDisplay());
      roidlg->show();
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispOverlay
// 
//
void MainFrame::dispOverlay(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->Overlay(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispFillDisplay
// 
//
void MainFrame::dispFillDisplay(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->FillDisplay(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispNoTearing
// 
//
void MainFrame::dispNoTearing(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->NoTearing(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispX11Annotations
// 
//
void MainFrame::dispX11Annotations(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->X11Annotations(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispGraphicsAnnotations
// 
//
void MainFrame::dispGraphicsAnnotations(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->GraphicsAnnotations(on);
         mf->updateActions(cf);
         }
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispRoiDefine
// 
//
void MainFrame::dispRoiDefine(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->ROIDefine(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispRoiShow
// 
//
void MainFrame::dispRoiShow(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->ROIShow(on);
         mf->updateActions(cf);
         }
      }
   }
/////////////////////////////////////////////////////////////////////////////
// dispRestrictCursor
// 
//
void MainFrame::dispRestrictCursor(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   if(mf->Update())
      {
      ChildFrame* cf = (ChildFrame*) mf->cf();
      if (cf)
         {
         bool on = gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action));
         cf->View()->RestrictCursor(on);
         mf->updateActions(cf);
         }
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispViewModeShift
// 
//
void MainFrame::dispViewModeShift(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeViewMode(M_BIT_SHIFT,Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispViewMode
// 
//
void MainFrame::dispViewMode(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeViewMode(Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispInter
// 
//
void MainFrame::dispInterMode(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeInterpolationMode(Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispDMILASynchronous Mode
// 
//
void MainFrame::dispDMILAsynchronousMode(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeAsynchronousMode(Val!=M_DISABLE, Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispDMILCompress Mode
// 
//
void MainFrame::dispDMILCompressMode(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeCompressionType(Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// dispDMILQFactor Mode
// 
//
void MainFrame::dispDMILQFactorMode(GtkAction *action, gpointer user_data, glong Val)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   ChildFrame* cf = (ChildFrame*) mf->cf();
   if (cf)
      {
      cf->View()->ChangeQFactor(Val);
      mf->updateActions(cf);
      }
   }

/////////////////////////////////////////////////////////////////////////////
// viewStandardToolbar
// 
//
void MainFrame::viewStandardToolbar(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   gboolean active = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));
   if(active)
      {
      gtk_widget_show(mf->m_HandleBoxStd);
      }
   else
      {
      gtk_widget_hide(mf->m_HandleBoxStd);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// viewDisplayToolbar
// 
//
void MainFrame::viewDisplayToolbar(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   gboolean active = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));
   if(active)
      {
      gtk_widget_show(mf->m_HandleBoxDisp);
      }
   else
      {
      gtk_widget_hide(mf->m_HandleBoxDisp);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// viewStatusBar
//
//
void MainFrame::viewStatusBar(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   gboolean active = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));
   if(active)
      {
      gtk_widget_show(mf->m_StatusBar);
      }
   else
      {
      gtk_widget_hide(mf->m_StatusBar);
      }
   }
/////////////////////////////////////////////////////////////////////////////
// About
// 
//
void MainFrame::about(GtkAction *action, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;
   g_return_if_fail(mf);
   GtkWidget *hbox;
   GtkWidget *dialog;
   GtkWidget *label;
   GtkWidget *milLogo;
   gchar     *filename;

   filename = g_strdup_printf("%s/%s/imaging.png",g_getenv("MILDIR"),GTK_MIL_IMAGES_DIR);
   GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename,NULL);
   g_free(filename);
   
   dialog = gtk_dialog_new_with_buttons("MDispGtk",
                                        GTK_WINDOW(mf->m_MainFrame),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_STOCK_OK,
                                        GTK_RESPONSE_NONE,
                                        NULL);
   hbox = gtk_hbox_new(false,10);
   gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox,true, true,0);
   
   milLogo = gtk_image_new_from_pixbuf(pixbuf);
   gtk_box_pack_start(GTK_BOX(hbox),milLogo,false, false,0);
   
   label = gtk_label_new("MDispGtk\n(C) 2006 Matrox Electronic Systems Ltd");
   gtk_label_set_justify(GTK_LABEL(label),GTK_JUSTIFY_LEFT);
   gtk_box_pack_start(GTK_BOX(hbox),label, true, true,0);

   g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);
   gtk_widget_show_all (dialog);
   }
/////////////////////////////////////////////////////////////////////////////
// Ondestroy
// when the window is closed
//
void MainFrame::OnDestroy(GtkWidget *widget, gpointer user_data)
   {
   MainFrame* mf = (MainFrame *) user_data;

   if(mf)
      {
      for(GList* l = mf->m_ChildList; l != NULL; l = l->next)
         {
         ChildFrame* cf = (ChildFrame *)l->data;
         delete cf; 
         }
      g_list_free(mf->m_ChildList);
      }
   gtk_main_quit ();
   }
/////////////////////////////////////////////////////////////////////////////
// updateActions
// 
//
void MainFrame::updateActions(ChildFrame *cf)
   {
   guint InterValue;
   guint ViewValue;

   gtk_widget_set_sensitive(GTK_WIDGET(m_InterpolationComboBox),cf != NULL);
   gtk_widget_set_sensitive(GTK_WIDGET(m_ViewComboBox), cf != NULL);

   setEnable("Close",cf != NULL);
   setEnable("Save",cf != NULL);
   setEnable("SaveAs",cf != NULL);
   setEnable("Overlay",cf != NULL);
   setEnable("X11Annotation",cf != NULL);
   setEnable("GraphicsAnnotations",cf != NULL);
   setEnable("InterpolationModeMenu",cf != NULL);
   setEnable("ViewModeMenu",cf != NULL);
   setEnable("DMILMenu",cf != NULL);
   setEnable("ExclusiveMenu",cf != NULL);
   setEnable("RoiDefine",cf != NULL);
   setEnable("RoiShow",cf != NULL);
   setEnable("RoiPref",cf != NULL);
   setEnable("SaveRoiAs",cf != NULL);
   setEnable("NoTearing",cf != NULL);   

    if (cf)
       {
       MdispGtkApp* app = (MdispGtkApp*) dispGtkApp();
       MdispGtkView* view = cf->View();
       setEnable("GrabStart",app->m_numberOfDigitizer != 0 && !(app->m_pGrabView && app->m_isGrabStarted));
       setEnable("GrabStop", app->m_pGrabView && app->m_isGrabStarted );
       setActive("FillDisplay", cf->View()->IsFillDisplayEnabled() );
       setActive("Overlay",cf->View()->IsOverlayEnabled() );
       setActive("X11Annotation", cf->View()->IsX11AnnotationsEnabled() );
       setActive("GraphicsAnnotations", cf->View()->IsGraphicsAnnotationsEnabled() );

       if(cf->View()->IsROISupported() && 
          cf->View()->IsWindowed()     && 
          !cf->View()->IsFillDisplayEnabled())
          { 
          setEnable("SaveRoiAs",cf->View()->IsFileSaveRoiAsEnabled());
          setEnable("RoiPref", true);
          setEnable("RoiDefine", true);
          setEnable("RoiShow", true);
          setActive("RoiDefine", cf->View()->IsInROIDefineMode());
          setActive("RoiShow",cf->View()->IsInROIShowMode());
          }
       else
          {
          setEnable("SaveRoiAs",false);
          setEnable("RoiPref",false);
          setEnable("RoiDefine",false);
          setEnable("RoiShow", false);
          }

       if ( view->IsFillDisplayEnabled() || cf->View()->IsExclusive())
          {
          setEnable("NoZoom",false);
          setEnable("ZoomIn",false);
          setEnable("ZoomOut",false);
          }
       else
          {
          setEnable("ZoomIn",  cf->View()->CurrentZoomFactor() < 16.0 );
          setEnable("ZoomOut", cf->View()->CurrentZoomFactor() > 1.0/16.0 );
          setEnable("NoZoom", true);
          }
       setEnable("FillDisplay", ((cf->View()->CurrentZoomFactor() == 1.0) && (!cf->View()->IsExclusive())));

       if(cf->View()->IsExclusive())
          {
          setEnable("ExclusiveMenu", true);
          }
       else
          {
          setEnable("ExclusiveMenu", false);
          }

       // Update  Interpolation Mode Combo Box 
       InterValue = INTERPOLATION_MODE_DEFAULT;
       switch(view->CurrentInterpolationMode())
         {
         case M_DEFAULT: 
            InterValue = INTERPOLATION_MODE_DEFAULT;
            break;
         case M_NEAREST_NEIGHBOR: 
            InterValue = INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            break;
         case M_FAST: 
            InterValue = INTERPOLATION_MODE_FAST;
            break;
         }
       gtk_combo_box_set_active (GTK_COMBO_BOX(m_InterpolationComboBox),InterValue);
       
       ViewValue = VIEW_MODE_DEFAULT;
       switch(view->CurrentViewMode())
          {
          case M_DEFAULT: 
             ViewValue = VIEW_MODE_DEFAULT;
             break;
          case M_TRANSPARENT: 
            ViewValue = VIEW_MODE_TRANSPARENT;
            break;
          case M_AUTO_SCALE: 
             ViewValue = VIEW_MODE_AUTO_SCALE;
             break;
          case M_MULTI_BYTES:
             ViewValue = VIEW_MODE_MULTI_BYTES;
             break;
          case M_BIT_SHIFT:
             {
             if(view->CurrentShiftValue() == 2)
                ViewValue = VIEW_MODE_BIT_SHIFT2;
             else if(view->CurrentShiftValue() == 4)
                ViewValue = VIEW_MODE_BIT_SHIFT4;
             else if(view->CurrentShiftValue() == 8)
                ViewValue = VIEW_MODE_BIT_SHIFT8;
             }
             break;
          }
       gtk_combo_box_set_active (GTK_COMBO_BOX(m_ViewComboBox),ViewValue);
       
       // DMILs menu
       if(view->IsNetworkedSystem())
          {
          setEnable("DMILMenu", true);
          if(!view->IsInAsynchronousMode())
             setActive("Disabled", true);
          else
             {
             switch(view->AsynchronousFrameRate())
                {
                case 1:
                   setActive("1", true);
                   break;
                case 5:
                   setActive("5", true);
                   break;
                case 10:
                   setActive("10", true);
                   break;
                case 15:
                   setActive("15", true);
                   break;
                case 30:
                   setActive("30", true);
                   break;
                case M_INFINITE:
                   setActive("MaxRate", true);
                   break;
                }
             }

          switch(view->CompressionType())
             {
             case M_NULL:
                setActive("None", true);
                break;
             case M_JPEG_LOSSY:
                setActive("Lossy", true);
                break;
             case M_JPEG_LOSSLESS:
                setActive("Lossless", true);
                break;
             }

          switch(view->QFactor())
             {
             case 60:
                setActive("60",true);
                break;
             case 70:
                setActive("70",true);
                break;
             case 75:
                setActive("75",true);
                break;                
             case 80:
                setActive("80",true);
                break;
             case 82:
                setActive("82",true);
                break;
             case 85:
                setActive("85",true);
                break;                
             case 87:
                setActive("87",true);
                break;
             case 90:
                setActive("90",true);
                break;
             case 92:
                setActive("92",true);
                break;       
             case 95:
                setActive("95",true);
                break;
             case 99:
                setActive("99",true);
                break;
             }
          }
       else
          setEnable("DMILMenu", false);

       if ( view->CurrentZoomFactor() == 1.0 )
          {
           setActive("NoTearing",true);
           if (view->IsNoTearingEnabled() )
             {
             setActive("NoTearing",true);
             gtk_widget_set_sensitive(GTK_WIDGET(m_InterpolationComboBox),false);
             }
          }
       else
          {
          setEnable("NoTearing",false);
          setActive("NoTearing",false);
          }
       }
    else
       {
       setEnable("New",true);
       setEnable("Open",true);
       setEnable("Save",false);
       setEnable("Close",false);
       setEnable("SaveAs",false);
       setEnable("GrabStart",false);
       setEnable("GrabStop",false);
       setEnable("Overlay",false);
       setEnable("X11Annotation",false);
       setEnable("GraphicsAnnotations",false);
       setEnable("ZoomMenu",false);
       setEnable("ZoomIn",false);
       setEnable("NoZoom",false);
       setEnable("ZoomOut",false);
       setEnable("FillDisplay",false);
       setEnable("NoTearing",false);
       setEnable("RoiDefine",false);
       setEnable("RoiShow",false);
       setEnable("RoiPref",false);
       setEnable("SaveRoiAs",false);
       setEnable("ViewModeMenu",false);      
       setEnable("DMILMenu",false);      
       setEnable("InterpolationModeMenu",false);
       }   
   }
