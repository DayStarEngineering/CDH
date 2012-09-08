#ifndef MDISPGTK_H
#define MDISPGTK_H

class MdispGtkView;
class MdispGtkApp
   {
   public:
      MdispGtkApp();
      virtual ~MdispGtkApp();

      virtual bool InitInstance();
      virtual bool ExitInstance();

   public:
      
      long     m_digitizerSizeX;    // Digitizer input width
      long     m_digitizerSizeY;    // Digitizer input heigh
      long     m_digitizerNbBands;  // Number of input color bands of the digitizer
      bool     m_isGrabStarted;     // State of the grab
      MdispGtkView* m_pGrabView;     // Pointer to the view that has the grab
      long     m_numberOfDigitizer; // Number of digitizers available on the system
      
      MIL_ID   m_MilApplication;    // Application identifier.
      MIL_ID   m_MilSystem;         // System identifier.
      MIL_ID   m_MilDigitizer;      // Digitizer identifier.

   protected:

      long MFTYPE DisplayError(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserDataPtr);
      void HookedOnErrors(bool IsHooked){m_isCurrentlyHookedOnErrors = IsHooked;}

   private:
      static long MFTYPE DisplayErrorExt(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr);
      bool m_isCurrentlyHookedOnErrors;
      
   };
#endif
