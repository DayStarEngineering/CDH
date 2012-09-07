#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <mil.h>
#include "mdispgtk.h"
#include "mainframe.h"


static gint MessageBox(const gchar *text,GtkMessageType messagetype,GtkButtonsType buttonstype)
   {
   GtkWidget *dialog;
   gint result;
   dialog = gtk_message_dialog_new (NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    messagetype,
                                    buttonstype,
                                    "%s",text);
   gtk_window_set_title(GTK_WINDOW(dialog),"MIL Error");
   result=gtk_dialog_run (GTK_DIALOG (dialog));
   gtk_widget_destroy (dialog);
   return result;
   }

MdispGtkApp::MdispGtkApp()
   {
   m_isCurrentlyHookedOnErrors = false;
   InitInstance();
   
   MainFrame* mf = new MainFrame();
   g_object_set_data(G_OBJECT(mf->MainWindow()),"App",(void *)this);
   }

MdispGtkApp::~MdispGtkApp()
   {
   ExitInstance();
   }

bool MdispGtkApp::InitInstance()
   {
   // Allocate an application and system [CALL TO MIL]
   MappAllocDefault(M_DEFAULT, &m_MilApplication, &m_MilSystem, M_NULL, M_NULL, M_NULL);

   // Hook MIL error on function DisplayError() [CALL TO MIL]
   MappHookFunction(M_ERROR_CURRENT,DisplayErrorExt,this);

   m_isCurrentlyHookedOnErrors = true;
	
   // Disable MIL error message to be displayed as the usual way [CALL TO MIL]
   MappControl(M_ERROR,M_PRINT_DISABLE);
 
   // Inquire number of digitizers available on the system [CALL TO MIL]
   MsysInquire(m_MilSystem,M_DIGITIZER_NUM,&m_numberOfDigitizer);
	
   // Digitizer is available
   if (m_numberOfDigitizer)	
      {
      // Allocate a digitizer [CALL TO MIL]
      MdigAlloc(m_MilSystem,M_DEFAULT,M_CAMERA_SETUP,M_DEFAULT,&m_MilDigitizer);
		
      // Stop live grab when window is disable [CALL TO MIL]
    	//TBM MIL 8.0 MsysControl(MilSystem,M_STOP_LIVE_GRAB_WHEN_DISABLED,M_ENABLE);

		// Inquire digitizer informations [CALL TO MIL]
      MdigInquire(m_MilDigitizer,M_SIZE_X,&m_digitizerSizeX);
      MdigInquire(m_MilDigitizer,M_SIZE_Y,&m_digitizerSizeY);  	
      MdigInquire(m_MilDigitizer,M_SIZE_BAND,&m_digitizerNbBands);
   
      if (m_digitizerSizeX > M_DEF_IMAGE_SIZE_X_MAX) 
         m_digitizerSizeX = M_DEF_IMAGE_SIZE_X_MAX;
      if (m_digitizerSizeY > M_DEF_IMAGE_SIZE_Y_MAX) 
         m_digitizerSizeY = M_DEF_IMAGE_SIZE_Y_MAX;
      }
   else 
      {
      m_MilDigitizer=0;
      m_digitizerNbBands =	M_DEF_IMAGE_NUMBANDS_MIN;
      }

   // Initialize the state of the grab
   m_isGrabStarted = false;
   return true;
   }

bool MdispGtkApp::ExitInstance()
   {
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write your code that will be executed on application exit
   /////////////////////////////////////////////////////////////////////////	
       
   //Free the digitizer [CALL TO MIL]
   if(m_MilDigitizer)    
      MdigFree (m_MilDigitizer);	
   
   //Free the system [CALL TO MIL]
   if(m_MilSystem)
      MsysFree (m_MilSystem);
   
   
   if(m_MilApplication)  
      {
      // Enable MIL error message to be displayed as the usual way [CALL TO MIL]
      MappControl(M_ERROR,M_PRINT_ENABLE);
      
      // Unhook MIL error on function DisplayError() [CALL TO MIL]
      if(m_isCurrentlyHookedOnErrors)
         {
         //MappHookFunction(M_ERROR_CURRENT+M_UNHOOK,DisplayErrorExt,pMdispGtkView);
         m_isCurrentlyHookedOnErrors = false;
         }
      
      // Free the application [CALL TO MIL]
      MappFree(m_MilApplication);
      }
   
   /////////////////////////////////////////////////////////////////////////
   // MIL: Write your code that will be executed on application exit
   /////////////////////////////////////////////////////////////////////////
   return true;
   }

long MFTYPE MdispGtkApp::DisplayErrorExt(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr)
   {
   MdispGtkApp* UserData = (MdispGtkApp *) UserDataPtr;
   //If user clicks NO on error message, unhook to errors.
   if(UserData->DisplayError(HookType,EventId, UserDataPtr) == M_NO_ERROR)
      {
      MappHookFunction(M_ERROR_CURRENT+M_UNHOOK,DisplayErrorExt,UserDataPtr);
      UserData->HookedOnErrors(false);
      }

   return M_NULL;
}

long MFTYPE MdispGtkApp::DisplayError(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserDataPtr)
   {
   char  ErrorMessageFunction[M_ERROR_MESSAGE_SIZE] = "";
   char  ErrorMessage[M_ERROR_MESSAGE_SIZE]         = "";
   char  ErrorSubMessage1[M_ERROR_MESSAGE_SIZE]     = "";
   char  ErrorSubMessage2[M_ERROR_MESSAGE_SIZE]     = "";
   char  ErrorSubMessage3[M_ERROR_MESSAGE_SIZE]     = "";
   long  NbSubCode;
   GString  *GErrorMessage;
   gint result;

   GErrorMessage=g_string_new(NULL);
   //Retrieve error message [CALL TO MIL]
   MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_FCT,ErrorMessageFunction);
   MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT,ErrorMessage);
   MappGetHookInfo(EventId,M_CURRENT_SUB_NB,&NbSubCode);

   if (NbSubCode > 2)
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_3,ErrorSubMessage3);
   if (NbSubCode > 1)
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_2,ErrorSubMessage2);
   if (NbSubCode > 0)
      MappGetHookInfo(EventId,M_MESSAGE+M_CURRENT_SUB_1,ErrorSubMessage1);

   GErrorMessage = g_string_append(GErrorMessage,ErrorMessageFunction);
   GErrorMessage = g_string_append(GErrorMessage ,"\n");
   GErrorMessage = g_string_append(GErrorMessage ,ErrorMessage);

   if(NbSubCode > 0)
      {
      GErrorMessage = g_string_append(GErrorMessage , "\n");
      GErrorMessage = g_string_append(GErrorMessage , ErrorSubMessage1);
      }
   
   if(NbSubCode > 1)
      {
      GErrorMessage = g_string_append(GErrorMessage , "\n");
      GErrorMessage = g_string_append(GErrorMessage , ErrorSubMessage2);
      }
   
   if(NbSubCode > 2)
      {
      GErrorMessage = g_string_append(GErrorMessage , "\n");
      GErrorMessage = g_string_append(GErrorMessage , ErrorSubMessage3);
      }
   
   GErrorMessage = g_string_append(GErrorMessage , "\n\n");
   GErrorMessage = g_string_append(GErrorMessage , "Do you want to continue error print?");
   
   result = MessageBox(GErrorMessage->str,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO);
   g_string_free(GErrorMessage,TRUE);
   
   if(result==GTK_RESPONSE_NO)
      {
      return M_NO_ERROR;
      }
   else
      {
      return M_ERROR;
      }
   }

int main(int argc, char *argv[])
   {
   /* init  xlib thread */
   XInitThreads();

    /* init Gtk */
   gtk_init(&argc, &argv);

   MdispGtkApp app;

   gtk_main();
   return 0;
   }
