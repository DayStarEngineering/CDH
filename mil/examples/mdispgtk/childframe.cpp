#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <mil.h>
#include "mdispgtk.h"
#include <gdk/gdkx.h>
#include "childframe.h"
#include "mdispgtkview.h"
#include "mainframe.h"
#include "mdispgtkmarshal.h"

gint ChildFrame::SignalId = 0;

ChildFrame::ChildFrame(MainFrame* mf):m_mf(mf)
   {
   m_View                 = NULL;
   m_FrameStr[0]          ='\0';
   m_ScaleStr[0]          ='\0';
   m_RoiStr  [0]          ='\0';
   m_MouseStr[0]          ='\0';

   GtkWidget* vbox        = NULL;
   GtkWidget* hbox        = NULL;

   SignalId++;
   m_roiPositionChangedSignalName   =  g_strdup_printf("frame-rate-changed-%d", SignalId);
   m_frameRateChangedSignalName     =  g_strdup_printf("roi-position-changed-%d",SignalId);
   m_zoomFactorChangedSignalName    =  g_strdup_printf("zoom-factor-changed-%d",SignalId);
   m_mousePositionChangedSignalName =  g_strdup_printf("mouse-position-changed-%d",SignalId);

   m_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   
   m_frameRateChangedSignal = g_signal_new(m_frameRateChangedSignalName,
                                           G_TYPE_OBJECT,
                                           G_SIGNAL_RUN_LAST,
                                           0,
                                           NULL,
                                           NULL,
                                           mdispgtk_marshal_VOID__DOUBLE,       
                                           G_TYPE_NONE,
                                           1,
                                           G_TYPE_DOUBLE);


   m_zoomFactorChangedSignal = g_signal_new(m_zoomFactorChangedSignalName,
                                            G_TYPE_OBJECT,
                                            G_SIGNAL_RUN_LAST,
                                            0,
                                            NULL,
                                            NULL,
                                            mdispgtk_marshal_VOID__DOUBLE,       
                                            G_TYPE_NONE,
                                            1,
                                            G_TYPE_DOUBLE);


   m_roiPositionChangedSignal = g_signal_new(m_roiPositionChangedSignalName,
                                             G_TYPE_OBJECT,
                                             G_SIGNAL_RUN_LAST,
                                             0,
                                             NULL,
                                             NULL,
                                             mdispgtk_marshal_VOID__INT_INT_INT_INT,       
                                             G_TYPE_NONE,
                                             4,
                                             G_TYPE_INT,
                                             G_TYPE_INT,
                                             G_TYPE_INT,
                                             G_TYPE_INT);

   m_mousePositionChangedSignal = g_signal_new(m_mousePositionChangedSignalName,
                                             G_TYPE_OBJECT,
                                             G_SIGNAL_RUN_LAST,
                                               0,
                                             NULL,
                                             NULL,
                                             mdispgtk_marshal_VOID__INT_INT_DOUBLE_DOUBLE, 
                                             G_TYPE_NONE,
                                             4,
                                             G_TYPE_INT,
                                             G_TYPE_INT,
                                             G_TYPE_DOUBLE,
                                             G_TYPE_DOUBLE);

   // if we want to make image child window in the center 
   // gtk_window_set_position(GTK_WINDOW(m_window), GTK_WIN_POS_CENTER);    

   vbox = gtk_vbox_new (false, 0);
   gtk_container_add (GTK_CONTAINER (m_window), vbox); 

   hbox = gtk_hbox_new (false, 0);
   gtk_box_pack_start (GTK_BOX (vbox), hbox, true, true, 0);

   m_DrawingArea = gtk_drawing_area_new ();
   gtk_container_add (GTK_CONTAINER (hbox), m_DrawingArea);

   // for each child frame drawin area attach parent frame
   GtkWidget* mainWindow =  m_mf->MainWindow();
   MdispGtkApp* App = (MdispGtkApp *) g_object_get_data(G_OBJECT(mainWindow),"App");
   g_object_set_data(G_OBJECT(m_DrawingArea),"App",(void *) App);
   g_object_set_data(G_OBJECT(m_DrawingArea),"MainWindow",(void *) mainWindow);

   // create the view and set it's parent
   m_View = new MdispGtkView(this); 

   gtk_window_set_title(GTK_WINDOW(m_window), m_View->filename());
   
   m_vadj = GTK_ADJUSTMENT (gtk_adjustment_new (0.0, 0.0, (gdouble)m_View->ImageSizeY(), 1.0, (gdouble)m_View->ImageSizeY(), (gdouble)m_View->ImageSizeY()));
   m_vscrollbar = gtk_vscrollbar_new (m_vadj);
   gtk_box_pack_end (GTK_BOX (hbox), m_vscrollbar, FALSE, TRUE, 0);

   m_hadj = GTK_ADJUSTMENT (gtk_adjustment_new (0.0, 0.0, (gdouble)m_View->ImageSizeX(), 1.0, (gdouble)m_View->ImageSizeX(), (gdouble)m_View->ImageSizeX()));
   m_hscrollbar = gtk_hscrollbar_new (m_hadj);
   gtk_box_pack_start (GTK_BOX (vbox), m_hscrollbar, FALSE, TRUE, 0);


   m_StatusBar = gtk_statusbar_new ();
   gtk_box_pack_end (GTK_BOX (vbox), m_StatusBar, false, false, 0);

   gtk_widget_set_events (m_DrawingArea, GDK_EXPOSURE_MASK | GDK_SCROLL_MASK);

   /* !!! very important to get drawing area repaint correctly in Gtk2 !!! */
   gtk_widget_set_double_buffered(m_DrawingArea,FALSE);


   // attach callbacks to events 
   g_signal_connect (G_OBJECT (m_window), "focus-in-event", G_CALLBACK (ChildFrame::OnChildGetFocus),this);
   g_signal_connect (G_OBJECT (m_window), "delete_event",   G_CALLBACK (ChildFrame::OnChildDelete),this);
   g_signal_connect (G_OBJECT (m_window), "delete_event",   G_CALLBACK (ChildFrame::OnChildDelete),this);
   g_signal_connect (G_OBJECT (m_window), "destroy",        G_CALLBACK (ChildFrame::OnChildDestroy),this);
   g_signal_connect (G_OBJECT (m_DrawingArea), "configure_event", G_CALLBACK (ChildFrame::OnChildConfigure),this);
   g_signal_connect (G_OBJECT (m_DrawingArea), "expose_event", G_CALLBACK (ChildFrame::OnChildExpose),this);
   g_signal_connect (G_OBJECT (m_hadj), "value_changed", G_CALLBACK (ChildFrame::OnChildScroll),this);
   g_signal_connect (G_OBJECT (m_vadj), "value_changed", G_CALLBACK (ChildFrame::OnChildScroll),this);

   g_signal_connect (G_OBJECT (m_window), m_roiPositionChangedSignalName, G_CALLBACK (ChildFrame::OnRoiPositionChanged),this);
   g_signal_connect (G_OBJECT (m_window), m_frameRateChangedSignalName, G_CALLBACK (ChildFrame::OnFrameRateChanged),this);
   g_signal_connect (G_OBJECT (m_window), m_zoomFactorChangedSignalName, G_CALLBACK (ChildFrame::OnZoomFactorChanged),this);
   g_signal_connect (G_OBJECT (m_window), m_mousePositionChangedSignalName, G_CALLBACK (ChildFrame::OnMousePositionChanged),this);


   gtk_widget_show_all(m_window);
   gdk_display_flush(gdk_display_get_default());

   // set this child as current child frame
   m_mf->setcf(this);

   UpdateStatusBarWithFrameRate(0.0);
   UpdateStatusBarWithScale(1.0);
   UpdateStatusBarWithROI(0,0,0,0);
   UpdateStatusBarWithMousePosition(0,0,0.0,0.0);

   m_layout = gtk_widget_create_pango_layout(m_DrawingArea,NULL);

   }

ChildFrame::~ChildFrame()
   {
   if(m_View)  delete m_View;
   g_free(m_roiPositionChangedSignalName);
   g_free(m_frameRateChangedSignalName);
   g_free(m_zoomFactorChangedSignalName);
   }

MdispGtkView* ChildFrame::View()
   {
   return m_View;
   }

void ChildFrame::close()
   {
   gtk_widget_destroy(m_window);
   }

void ChildFrame::setTitle(const gchar* title)
   {
   if(title)
      gtk_window_set_title(GTK_WINDOW(m_window),title);
   }
void ChildFrame::show()
   {
   gtk_widget_show_all(m_window);
   }
void ChildFrame::OnChildDestroy(GtkWidget *widget, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   if(cf)
      {
      cf->OnChildDelete(widget,NULL, user_data);
      }
   }
gboolean ChildFrame::OnChildDelete(GtkWidget *widget, GdkEvent  *event, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   MainFrame* mf = cf->m_mf;
   gint result;
   
   if(cf->View() && cf->View()->IsModified()) 
      {
      GtkWidget *dialog = gtk_message_dialog_new (NULL,
                                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                                  GTK_MESSAGE_QUESTION,
                                                  GTK_BUTTONS_YES_NO,
                                                  " MdispGtk Save Image ?");
      gtk_window_set_title(GTK_WINDOW(dialog),"MdispGtk Message");
      result = gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      switch(result)
         {
         case GTK_RESPONSE_YES:
            mf->fileSaveAs(NULL,mf);            
            break;
         case GTK_RESPONSE_NO:
            break;
         }
      }
   if(mf)
      {
      
      mf->remove(cf);
      }
   // remove the view
   if(cf->m_View) delete cf->m_View;
   cf->m_View = NULL;               
   return false;
    }

gboolean ChildFrame::OnChildGetFocus(GtkWidget *widget, GdkEventFocus  *event, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   MainFrame* mf = cf->m_mf;
   if(mf)
      mf->setcf(cf);
   return true;
   }

gboolean ChildFrame::OnChildConfigure(GtkWidget *widget, GdkEventConfigure  *event, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   if(cf)
      {

      cf->UpdateScrollBar();
      }
   return true;
   }

gboolean ChildFrame::OnChildExpose(GtkWidget *widget, GdkEventExpose  *event, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   if(cf)
      {
      cf->m_View->Paint();
      }
   return true;
   }
void ChildFrame::OnChildScroll(GtkAdjustment *adjustment, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   
   if(cf && GTK_WIDGET_VISIBLE(cf->m_window))
      {
      gdouble  x = gtk_adjustment_get_value(GTK_ADJUSTMENT(cf->m_hadj));
      gdouble  y = gtk_adjustment_get_value(GTK_ADJUSTMENT(cf->m_vadj));
      
      if (!cf->m_View->IsFillDisplayEnabled())
         cf->m_View->pan ((int)x, (int)y); 
      }
   }

void ChildFrame::UpdateStatusBar()
   {
   if(GTK_WIDGET_VISIBLE(m_window))
      {
      gchar *text;
      gint context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR (m_StatusBar), "ChildStatusBar");
      text = g_strdup_printf("%s      | %s   |  %s  | %s",
                             m_FrameStr,
                             m_ScaleStr,
                             m_RoiStr,
                             m_MouseStr);
      
      gtk_statusbar_push (GTK_STATUSBAR(m_StatusBar), GPOINTER_TO_INT (context_id), text);
      g_free(text);
      }
   }

void ChildFrame::UpdateStatusBarWithFrameRate(MIL_DOUBLE CurrentRate)
   {
   if(CurrentRate == M_INVALID)
      {
      g_snprintf(m_FrameStr,STRING_SIZE,"%s","Display Updates Not Available");
      }
   else
      {
      g_snprintf(m_FrameStr,STRING_SIZE,"Display Updates :%.2f fps",CurrentRate);
      }
   UpdateStatusBar();
   }

void ChildFrame::UpdateStatusBarWithScale(MIL_DOUBLE CurrentScale)
   {
   g_snprintf(m_ScaleStr,STRING_SIZE,"%.4f",CurrentScale);
   UpdateStatusBar();
   }

void ChildFrame::UpdateStatusBarWithROI(long OffsetX, long OffsetY, long SizeX, long SizeY)
   {
   if(!OffsetX && !OffsetY && !SizeX && !SizeY)
      {
      g_snprintf(m_RoiStr,STRING_SIZE,"%s","No ROI Set");
      }
   else
      {
      g_snprintf(m_RoiStr, STRING_SIZE, "ROI:(%d,%d)->(%d,%d)",(gint)OffsetX, (gint)OffsetY, (gint)(OffsetX+SizeX),(gint)(OffsetY+SizeY));
      }
   UpdateStatusBar();
   }

void ChildFrame::UpdateStatusBarWithMousePosition(long DispX, long DispY, double BufX, double BufY)
   {
   g_snprintf(m_MouseStr,STRING_SIZE,"M:(%d,%d)->(%.2f,%.2f)",(gint)DispX, (gint)DispY, BufX, BufY);
   UpdateStatusBar();
   }

void ChildFrame::DrawText(const gchar *text, gint x, gint y, GdkColor textColor)
   {
   PangoAttrList *attrs = NULL;
   PangoAttribute *attr = NULL;
   gint text_width;
   gint text_height;
   
   attr  = pango_attr_foreground_new(textColor.red,textColor.green,textColor.blue);
   attrs = pango_layout_get_attributes(m_layout);
   if(!attrs)
      {
      attrs = pango_attr_list_new();
      }
   pango_attr_list_insert(attrs,attr);
   attr->start_index=0;
   attr->end_index = G_MAXINT;

   pango_layout_set_attributes(m_layout,attrs);
   pango_layout_set_text(m_layout, text, -1);
   pango_layout_get_pixel_size(m_layout, &text_width, &text_height);
   /* draw text */
   gdk_draw_layout(m_DrawingArea->window, m_DrawingArea->style->black_gc, x-text_width/2,y, m_layout);
   }

void ChildFrame::UpdateScrollBar()
   {
   if(GTK_WIDGET_VISIBLE(m_window))
      {
      int      SizeX;
      int      SizeY;
      bool     bValueChangedX = false;
      bool     bValueChangedY = false;
      
      /* clear the drawing area */
      gdk_window_clear_area_e(GDK_WINDOW(m_DrawingArea->window), 
                              0, 0,
                              m_window->allocation.width,
                              m_window->allocation.height);

      
      /* Horizontal scrollbar adjustment */
      SizeX = (int)(m_View->ImageSizeX() * m_View->ZoomFactor());
      m_hadj->page_size = m_window->allocation.width;
      m_hadj->upper = SizeX;
      
      if (m_hadj->value > m_hadj->upper - m_hadj->page_size)
      {
      m_hadj->value = m_hadj->upper - m_hadj->page_size;
      bValueChangedX = true;
      }
      if (m_hadj->value < 0)
         {
         m_hadj->value = 0;
         bValueChangedX = true;
         }
      
      /* Vertical scrollbar adjustment */
      SizeY = (int)(m_View->ImageSizeY() * m_View->ZoomFactor());
      m_vadj->page_size = m_window->allocation.height;
      m_vadj->upper = SizeY;
      
      if (m_vadj->value > m_vadj->upper - m_vadj->page_size)
         {
         m_vadj->value = m_vadj->upper - m_vadj->page_size;
         bValueChangedY = true;
         }
      if (m_vadj->value < 0)
         {
         m_vadj->value = 0;
         bValueChangedY = true;
         }
      
      gtk_adjustment_changed(m_hadj);
      gtk_adjustment_changed(m_vadj);
      
      if (bValueChangedX)
         gtk_adjustment_value_changed(m_hadj);
      
      if (bValueChangedY)
         gtk_adjustment_value_changed(m_vadj);
      }
   }

void ChildFrame::UpdateContentSize(long SizeX, long SizeY)
   {
   long NewSizeX = SizeX; 
   long NewSizeY = SizeY;
   
   if(GTK_WIDGET_VISIBLE(m_window))
      {
      /* clear the drawing area */
      gdk_window_clear_area_e(GDK_WINDOW(m_DrawingArea->window), 
                              0, 0,
                              m_window->allocation.width,
                              m_window->allocation.height);

      NewSizeY+= m_StatusBar->allocation.height;
      
      if (!m_View->IsFillDisplayEnabled())
         {
         gtk_widget_show(m_hscrollbar);
         gtk_widget_show(m_vscrollbar);
         NewSizeX += m_vscrollbar->allocation.width;
         NewSizeY += m_hscrollbar->allocation.height;
         }
      else
         {
         gtk_widget_hide(m_hscrollbar);
         gtk_widget_hide(m_vscrollbar);
         }
      //UpdateStatusBar();
      }
   
   gtk_window_resize(GTK_WINDOW(m_window),NewSizeX,NewSizeY);
   }

void ChildFrame::OnRoiPositionChanged(GtkWidget *widget, gint OffsetX, gint OffsetY, gint SizeX, gint SizeY, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   cf->UpdateStatusBarWithROI(OffsetX, OffsetY, SizeX, SizeY);
   }

void ChildFrame::OnFrameRateChanged(GtkWidget *widget, gdouble Rate, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   cf->UpdateStatusBarWithFrameRate(Rate);
   }

void ChildFrame::OnZoomFactorChanged(GtkWidget *widget, gdouble Scale, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   cf->UpdateStatusBarWithScale(Scale);
   }

void ChildFrame::OnMousePositionChanged(GtkWidget *widget, gint DispX, gint DispY, gdouble BufX, gdouble BufY, gpointer user_data)
   {
   ChildFrame* cf = (ChildFrame *) user_data;
   cf->UpdateStatusBarWithMousePosition(DispX, DispY, BufX, BufY);
   }
