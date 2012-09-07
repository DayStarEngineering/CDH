#include <gtk/gtk.h>
#include <mil.h>
#include "roidlg.h"

ROIDialog::ROIDialog(MIL_INT MilDisplay):m_MilDisplay(MilDisplay)
   {
   GtkWidget *pickerLine;
   GtkWidget *pickerAnchor;
   GtkWidget *closeButton;
   GtkWidget *vbox;
   GtkWidget *hbox;
   GtkWidget *label;
   
   MIL_INT linecolor = MdispInquire(m_MilDisplay, M_ROI_LINE_COLOR, M_NULL);
   MIL_INT anchorcolor= MdispInquire(m_MilDisplay, M_ROI_HANDLE_COLOR, M_NULL);
   
   m_LineColor.red   = M_RGB888_R(linecolor)<<8;
   m_LineColor.green = M_RGB888_G(linecolor)<<8;
   m_LineColor.blue  = M_RGB888_B(linecolor)<<8;

   m_AnchorColor.red   = M_RGB888_R(anchorcolor)<<8;
   m_AnchorColor.green = M_RGB888_G(anchorcolor)<<8;
   m_AnchorColor.blue  = M_RGB888_B(anchorcolor)<<8;

   m_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(m_window), "ROI Preferences");
			     
   gtk_container_set_border_width (GTK_CONTAINER (m_window), 0);

   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (m_window), vbox);
      
   label = gtk_label_new ("Color :");
   gtk_container_add (GTK_CONTAINER (vbox), label);

   hbox = gtk_hbox_new (FALSE, 8);
   gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
   gtk_container_add (GTK_CONTAINER (vbox), hbox);
      
   label = gtk_label_new ("Line Color");
   gtk_container_add (GTK_CONTAINER (hbox), label);

   pickerLine = gtk_color_button_new ();
   gtk_color_button_set_use_alpha (GTK_COLOR_BUTTON (pickerLine), TRUE);
   gtk_container_add (GTK_CONTAINER (hbox), pickerLine);

   gtk_color_button_set_color(GTK_COLOR_BUTTON(pickerLine),&m_LineColor);
      
   hbox = gtk_hbox_new (FALSE, 8);
   gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
   gtk_container_add (GTK_CONTAINER (vbox), hbox);

   label = gtk_label_new ("Anchor Color");
   gtk_container_add (GTK_CONTAINER (hbox), label);

   pickerAnchor = gtk_color_button_new ();
   gtk_color_button_set_use_alpha (GTK_COLOR_BUTTON (pickerAnchor), TRUE);
   gtk_container_add (GTK_CONTAINER (hbox), pickerAnchor);
   
   gtk_color_button_set_color(GTK_COLOR_BUTTON(pickerAnchor),&m_AnchorColor);

   closeButton = gtk_button_new_with_label("Close");
   gtk_container_add (GTK_CONTAINER (vbox), closeButton);
   
   //signals
   g_signal_connect (closeButton,"clicked",G_CALLBACK(ROIDialog::OnClose),this);
   g_signal_connect (pickerAnchor,"color-set",G_CALLBACK(ROIDialog::OnROIAnchorColorChange),this);
   g_signal_connect (pickerLine,"color-set",G_CALLBACK(ROIDialog::OnROILineColorChange),this);
   g_signal_connect (m_window, "destroy",  G_CALLBACK(ROIDialog::OnDestroy), this);
  
   }

ROIDialog::~ROIDialog()
   {
   }

void ROIDialog::show()
   {
   gtk_widget_show_all(m_window);
   }

void ROIDialog::OnDestroy(GtkWidget *widget, gpointer user_data)
   {
   ROIDialog* rd = (ROIDialog *) user_data;
   gtk_widget_destroy(rd->m_window);
   }

void ROIDialog::OnClose(GtkWidget *widget, gpointer user_data)
   {
   ROIDialog* rd = (ROIDialog *) user_data;
   gtk_widget_destroy(rd->m_window);
   }

void ROIDialog::OnROIAnchorColorChange(GtkColorButton *widget, gpointer  user_data) 
   {
   ROIDialog* rd = (ROIDialog *) user_data;
   if(rd)
      {
      gtk_color_button_get_color(widget,&(rd->m_AnchorColor));
      MIL_INT anchorcolor = M_RGB888(rd->m_AnchorColor.red>>8,
                                     rd->m_AnchorColor.green>>8,
                                     rd->m_AnchorColor.blue>>8);
      MdispControl(rd->m_MilDisplay, M_ROI_HANDLE_COLOR, anchorcolor);
      MdispControl(rd->m_MilDisplay, M_UPDATE, M_NULL);
      }
   }

void ROIDialog::OnROILineColorChange(GtkColorButton *widget, gpointer  user_data) 
   {
   ROIDialog* rd = (ROIDialog *) user_data;
   if(rd)
      {
      gtk_color_button_get_color(widget,&(rd->m_LineColor));
      MIL_INT linecolor = M_RGB888(rd->m_LineColor.red>>8,
                                   rd->m_LineColor.green>>8, 
                                   rd->m_LineColor.blue>>8);
      MdispControl(rd->m_MilDisplay, M_ROI_LINE_COLOR, linecolor);
      MdispControl(rd->m_MilDisplay, M_UPDATE, M_NULL);
      }
   }
