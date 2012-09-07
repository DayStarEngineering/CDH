#include "mdispqtapp.h"
#include "mainframe.h"
#include <QtGui>

class MilErrorEvent : public QEvent
   {
   public:
      MilErrorEvent( MIL_ID EventId );

      inline MIL_ID EventId() const;

      static const int TYPE = QEvent::User + 1;

   private:
      MIL_ID m_EventId;
   };

MilErrorEvent::MilErrorEvent( MIL_ID EventId )
   : QEvent(QEvent::Type(TYPE))
   , m_EventId( EventId )
   {
   }

MIL_ID MilErrorEvent::EventId() const
   {
   return m_EventId;
   }

MdispQtApp::MdispQtApp( int& argc, char** argv )
   : QApplication( argc, argv )
   , m_isCurrentlyHookedOnErrors(false)
   , m_ErrorEventSemaphore(1)
   , m_CreatorThread( QThread::currentThreadId() )
{
   // Set semaphore to initial state (no error event available).
   m_ErrorEventSemaphore.acquire();

   // Allocate an application and system [CALL TO MIL]
   MappAllocDefault(M_DEFAULT, &m_MilApplication, &m_MilSystem, M_NULL, M_NULL, M_NULL);

   // Hook MIL error on function DisplayError() [CALL TO MIL]
   MappHookFunction(M_ERROR_CURRENT,DisplayErrorExt,M_NULL);

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
   // Digitizer is not available
   else
   {
      m_MilDigitizer = 0;
      m_digitizerNbBands  =   M_DEF_IMAGE_NUMBANDS_MIN;
   }


   // Initialize the state of the grab
   m_isGrabStarted = FALSE;

   // Initialize GUI
   MainFrame* mf = new MainFrame();
   //setMainWidget(mf);

   mf->show();

}

MdispQtApp::~MdispQtApp()
{
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
         MappHookFunction(M_ERROR_CURRENT+M_UNHOOK,DisplayErrorExt,M_NULL);
         m_isCurrentlyHookedOnErrors = false;
      }

      // Free the application [CALL TO MIL]
      MappFree(m_MilApplication);
   }
}

void MdispQtApp::customEvent( QEvent* e )
{
   switch (e->type())
   {
   case MilErrorEvent::TYPE:
      milErrorEvent( (MilErrorEvent*) e );
      break;
   default:
      QMessageBox::critical( 0, tr("MdispQt"),
                             QString("Unknown event type: %1").arg(e->type()),
                             QMessageBox::Ok, QMessageBox::NoButton );
      exit(1);
   }
}

void MdispQtApp::milErrorEvent( MilErrorEvent* e )
{
   //If user clicks NO on error message, unhook to errors.
   if( DisplayError( e->EventId() ) == M_NO_ERROR )
   {
      MappHookFunction(M_ERROR_CURRENT+M_UNHOOK,DisplayErrorExt,M_NULL);
      ((MdispQtApp*) qApp)->HookedOnErrors(false);
   }
   // Release MIL thread after error processing is done.
   m_ErrorEventSemaphore.release();
}

/////////////////////////////////////////////////////////////////////////
// MIL: Hook-handler function: DisplayError()
/////////////////////////////////////////////////////////////////////////

long MFTYPE MdispQtApp::DisplayErrorExt(long /*HookType*/, MIL_ID EventId, void MPTYPE* /*UserDataPtr*/)
{
   if ( QThread::currentThreadId() != ((MdispQtApp*) qApp)->m_CreatorThread )
   {
      // Have the GUI thread process the event.
      QApplication::postEvent( qApp, new MilErrorEvent(EventId) );

      // Wait for error event to be processed by GUI thread.
      ((MdispQtApp*) qApp)->m_ErrorEventSemaphore.acquire();
   }
   else
   {
      // Do the work in this thread.
      qApp->notify( qApp, new MilErrorEvent(EventId) );
   }

   return M_NULL;
}

long MFTYPE MdispQtApp::DisplayError( MIL_ID EventId )
{
   char  ErrorMessageFunction[M_ERROR_MESSAGE_SIZE] = "";
   char  ErrorMessage[M_ERROR_MESSAGE_SIZE]         = "";
   char  ErrorSubMessage1[M_ERROR_MESSAGE_SIZE]     = "";
   char  ErrorSubMessage2[M_ERROR_MESSAGE_SIZE]     = "";
   char  ErrorSubMessage3[M_ERROR_MESSAGE_SIZE]     = "";
   long  NbSubCode;
   QString  QErrorMessage;

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

   QErrorMessage = ErrorMessageFunction;
   QErrorMessage = QErrorMessage + "\n";
   QErrorMessage = QErrorMessage + ErrorMessage;

   if(NbSubCode > 0)
   {
      QErrorMessage = QErrorMessage + "\n";
      QErrorMessage = QErrorMessage + ErrorSubMessage1;
   }

   if(NbSubCode > 1)
   {
      QErrorMessage = QErrorMessage + "\n";
      QErrorMessage = QErrorMessage + ErrorSubMessage2;
   }

   if(NbSubCode > 2)
   {
      QErrorMessage = QErrorMessage + "\n";
      QErrorMessage = QErrorMessage + ErrorSubMessage3;
   }

   QErrorMessage = QErrorMessage + "\n\n";
   QErrorMessage = QErrorMessage + "Do you want to continue error print?";

   if ( QMessageBox::warning( 0, tr("MIL Error"), QErrorMessage, QMessageBox::Yes,
                              QMessageBox::No ) == QMessageBox::No )
      return M_NO_ERROR;

   else
      return M_ERROR;
}
