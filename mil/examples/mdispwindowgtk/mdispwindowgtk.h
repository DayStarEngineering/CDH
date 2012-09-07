#ifndef MDISPWINDOWGTK_H
#define MDISPWINDOWGTK_H
#include <mil.h>

#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>

typedef struct  MilWindow
   {
      GtkWidget* Window;
      GtkWidget* Area;
      GtkWidget* HBox;
   } MilWindow;
#endif // MDISPWINDOWGTK_H
