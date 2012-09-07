#ifndef ROIDLG_H
#define ROIDLG_H

class ROIDialog
   {
   public:
      ROIDialog(MIL_INT MilDisplay);
      virtual ~ROIDialog();
      void show();

   private:
      static void OnDestroy(GtkWidget *widget, gpointer user_data);
      static void OnClose(GtkWidget *widget, gpointer user_data);
      static void OnROILineColorChange(GtkColorButton *widget, gpointer  user_data); 
      static void OnROIAnchorColorChange(GtkColorButton *widget, gpointer  user_data);
 
      MIL_INT     m_MilDisplay;
      GdkColor    m_LineColor;
      GdkColor    m_AnchorColor;
      GtkWidget*  m_window; 
      
      
   };
#endif
