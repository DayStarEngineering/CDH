#include "mdispwindowgtk.h"

/* Window title. */
#define MIL_APPLICATION_NAME      "MIL Application"
#define MIL_APPLICATION_NAME_SIZE  128

/* Default image dimensions. */
#define DEFAULT_IMAGE_SIZE_X       640
#define DEFAULT_IMAGE_SIZE_Y       480
#define DEFAULT_IMAGE_SIZE_BAND      1

void GtkMessageBox(const gchar *,GtkMessageType);


/***************************************************************************/
/*
 * Name:         MilApplication()
 *
 * synopsis:     This function is the core of the MIL application that
 *               is executed when this program is started. See main() below for
 *               the program entry point.
 *
 *               It uses MIL to display a welcoming message in the
 *               specified user window and to grab in it if it is supported
 *               by the target system.
 *
 */

void MilApplication(MilWindow* MainWindow)
   {
   /* MIL variables */
   MIL_ID MilApplication,  /* MIL Application identifier.  */
      MilSystem,       /* MIL System identifier.       */
      MilDisplay,      /* Display identifier.      */
      MilDigitizer,    /* MIL Digitizer identifier.    */
      MilImage;        /* MIL Image buffer identifier. */

   long BufSizeX;
   long BufSizeY;
   long BufSizeBand;


   /* Allocate a MIL application. */
   MappAlloc(M_DEFAULT, &MilApplication);

   /* Allocate a MIL system. */
   MsysAlloc("M_DEFAULT", M_DEFAULT, M_DEFAULT, &MilSystem);

   /* Allocate a MIL display. */
   MdispAlloc(MilSystem, M_DEFAULT, "M_DEFAULT", M_WINDOWED, &MilDisplay);

   /* Allocate a MIL digitizer if supported and sets the target image size. */
   if (MsysInquire(MilSystem, M_DIGITIZER_NUM, M_NULL) > 0)
      {
      MdigAlloc(MilSystem, M_DEFAULT, "M_DEFAULT", M_DEFAULT, &MilDigitizer);
      MdigInquire(MilDigitizer, M_SIZE_X,    &BufSizeX);
      MdigInquire(MilDigitizer, M_SIZE_Y,    &BufSizeY);
      MdigInquire(MilDigitizer, M_SIZE_BAND, &BufSizeBand);

      /* Resize the display window */
      if((BufSizeX > DEFAULT_IMAGE_SIZE_X) || (BufSizeY > DEFAULT_IMAGE_SIZE_Y))
         {
         gtk_window_resize(GTK_WINDOW(MainWindow->Window),
                           BufSizeX,
                           BufSizeY + MainWindow->HBox->allocation.height);
         }
      }
   else
      {
      MilDigitizer = M_NULL;
      BufSizeX     = DEFAULT_IMAGE_SIZE_X;
      BufSizeY     = DEFAULT_IMAGE_SIZE_Y;
      BufSizeBand  = DEFAULT_IMAGE_SIZE_BAND;
      }

   /* Do not allow example to run in auxiliary mode. */
   if(MdispInquire(MilDisplay, M_DISPLAY_MODE, M_NULL) != M_WINDOWED)
      {
      GtkMessageBox("This example does not run in auxiliary mode.",GTK_MESSAGE_ERROR);
      goto end;
      }

   /* Allocate a MIL buffer. */
   MbufAllocColor(MilSystem, BufSizeBand, BufSizeX, BufSizeY, 8+M_UNSIGNED,
                  (MilDigitizer ? M_IMAGE+M_DISP+M_GRAB : M_IMAGE+M_DISP), &MilImage);

   /* Clear the buffer */
   MbufClear(MilImage,0);

   /* Select the MIL buffer to be displayed in the user-specified window */
   MdispSelectWindow(MilDisplay, MilImage, GDK_WINDOW_XWINDOW(MainWindow->Area->window));

   /* Print a string in the image buffer using MIL.
      Note: When a MIL buffer is modified using a MIL command, the display
      automatically updates the window passed to MdispSelectWindow().
   */
   MgraFont(M_DEFAULT, M_FONT_DEFAULT_LARGE);
   MgraText(M_DEFAULT, MilImage, (BufSizeX/8)*2, BufSizeY/2,
            MIL_TEXT(" Welcome to MIL !!! "));
   MgraRect(M_DEFAULT, MilImage, ((BufSizeX/8)*2)-60, (BufSizeY/2)-80,
            ((BufSizeX/8)*2)+370, (BufSizeY/2)+100);
   MgraRect(M_DEFAULT, MilImage, ((BufSizeX/8)*2)-40, (BufSizeY/2)-60,
            ((BufSizeX/8)*2)+350, (BufSizeY/2)+80);
   MgraRect(M_DEFAULT, MilImage, ((BufSizeX/8)*2)-20, (BufSizeY/2)-40,
            ((BufSizeX/8)*2)+330, (BufSizeY/2)+60);

   /* Open a message box to wait for a key. */

   GtkMessageBox("Welcome to MIL !!! was printed",GTK_MESSAGE_INFO);

   /* Grab in the user window if supported. */
   if (MilDigitizer)
      {
      /* Grab continuously. */
      MdigGrabContinuous(MilDigitizer, MilImage);

      /* Open a message box to wait for a key. */
      GtkMessageBox("Continuous grab in progress",GTK_MESSAGE_INFO);
      /* Stop continuous grab. */
      MdigHalt(MilDigitizer);
      }

   /* Remove the MIL buffer from the display. */
   MdispSelect(MilDisplay, M_NULL);

   /* Free allocated objects. */
   MbufFree(MilImage);

   end:

   if (MilDigitizer)
      MdigFree(MilDigitizer);
   MdispFree(MilDisplay);
   MsysFree(MilSystem);
   MappFree(MilApplication);
   }

/***************************************************************************/
/*
 *
 * synopsis:     This is Gtk2 part
 *               Utility functions and
 *               callback functions.
 */


/***************************************************************************
 * Name:         GtkMessageBox
 *
 * synopsis:     Display a Gtk Modal MessageBox.
 *
 */

void GtkMessageBox(const gchar *msg,GtkMessageType msgtype)
   {
   GtkWidget *dialog=NULL;

   dialog = gtk_message_dialog_new (NULL,
                                    (GtkDialogFlags)(GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT),
                                    msgtype,
                                    (GTK_BUTTONS_CLOSE),
                                    "%s",
                                    msg);

   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);
   }


/***************************************************************************
 * Name:         gtk_start_callback
 *
 * synopsis:     Called when user click Start button.
 *
 *
 */

gboolean gtk_start_callback(GtkWidget       *widget,
                            gpointer         data)
   {

   MilWindow *MainWindow=(MilWindow *)data;
   gtk_widget_set_sensitive(widget,FALSE);
   MilApplication(MainWindow);
   /* end of MIlApplication */
   gtk_widget_set_sensitive(widget,TRUE);
   return TRUE;
   }

/***************************************************************************
 * Name:         main application (Gtk2)
 *
 * synopsis:     Create widgets attach callbacks and loop.
 *
 *
 */

int main(int argc, char *argv[])
   {
   XInitThreads();

   /* some gtkwidgets */
   GtkWidget *button=NULL;
   GtkWidget *vbox=NULL;
   MilWindow MainWindow;
   gtk_init(&argc, &argv);
   
   /* main window */
   MainWindow.Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   
   gtk_window_set_title(GTK_WINDOW(MainWindow.Window), MIL_APPLICATION_NAME);
   gtk_signal_connect (GTK_OBJECT (MainWindow.Window), "destroy", gtk_main_quit,NULL);
   gtk_window_set_default_size(GTK_WINDOW(MainWindow.Window),
                               DEFAULT_IMAGE_SIZE_X,
                               DEFAULT_IMAGE_SIZE_Y);
   vbox = gtk_vbox_new (FALSE, 0);
   gtk_container_add (GTK_CONTAINER (MainWindow.Window), vbox);
   gtk_widget_show (vbox);
   
   MainWindow.HBox=gtk_hbox_new(FALSE,0);
   gtk_box_pack_start (GTK_BOX (vbox), MainWindow.HBox, FALSE, FALSE, 0);
   gtk_widget_show (MainWindow.HBox);

   button=gtk_button_new_with_label ("Start");
   gtk_box_pack_start (GTK_BOX (MainWindow.HBox), button, FALSE, FALSE, 0);
   gtk_widget_show(button);

   /* drawing area */
   MainWindow.Area = gtk_drawing_area_new ();
   gtk_widget_set_size_request (MainWindow.Area,
                                DEFAULT_IMAGE_SIZE_X,
                                DEFAULT_IMAGE_SIZE_Y);
   gtk_box_pack_start (GTK_BOX (vbox), MainWindow.Area, TRUE, TRUE, 0);

   g_signal_connect (GTK_OBJECT (button),
                     "clicked",
                     G_CALLBACK (gtk_start_callback),
                     (gpointer) &MainWindow);

   // !!! very important to get drawing area repaint correctly in Gtk2 */
   gtk_widget_set_double_buffered(MainWindow.Area,False);

   gtk_widget_show(MainWindow.Area);

   gtk_widget_show (MainWindow.Window);

   /* enter the GTK main loop */
   gtk_main();
   return 0;
   }

