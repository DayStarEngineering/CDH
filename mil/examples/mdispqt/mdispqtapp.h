#ifndef MDISPQTAPP_H
#define MDISPQTAPP_H

#include <mil.h>
#include <QApplication>
#include <QSemaphore>

class MdispQtView;
class MilErrorEvent;

class MdispQtApp : public QApplication
{
   Q_OBJECT

public:
   MdispQtApp( int& argc, char** argv );
   virtual ~MdispQtApp();

   long     m_digitizerSizeX;    // Digitizer input width
   long     m_digitizerSizeY;    // Digitizer input heigh
   long     m_digitizerNbBands;  // Number of input color bands of the digitizer
   bool     m_isGrabStarted;     // State of the grab
   MdispQtView* m_pGrabView;     // Pointer to the view that has the grab
   long     m_numberOfDigitizer; // Number of digitizers available on the system

   MIL_ID   m_MilApplication;    // Application identifier.
   MIL_ID   m_MilSystem;         // System identifier.
   MIL_ID   m_MilDigitizer;      // Digitizer identifier.

   long MFTYPE DisplayError( MIL_ID EventId );
   void HookedOnErrors(bool IsHooked){m_isCurrentlyHookedOnErrors = IsHooked;}

protected:
   virtual void customEvent( QEvent* e );
   virtual void milErrorEvent( MilErrorEvent* e );

private:
   static long MFTYPE DisplayErrorExt(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr);

   bool m_isCurrentlyHookedOnErrors;
   QSemaphore m_ErrorEventSemaphore;

   const Qt::HANDLE m_CreatorThread;
};

#endif // MDISPQTAPP_H
