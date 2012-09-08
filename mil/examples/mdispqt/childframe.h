#ifndef CHILDFRAME_H
#define CHILDFRAME_H

#include <QMainWindow>

class MdispQtView;
class QLabel;

class ChildFrame : public QMainWindow
   {
   Q_OBJECT

   public:
      ChildFrame( QWidget* parent = 0 );
      MdispQtView* view();
      QSize sizeHint() const;
   protected:
      virtual void closeEvent( QCloseEvent* e );
      virtual void paintEvent(QPaintEvent* e);
      // needed to prevent OWorkSpace to drag the child window ( default behavior)
      virtual void mouseMoveEvent ( QMouseEvent * /*event */) {;} 

   private slots:
      void UpdateStatusBarWithFrameRate(double CurrentRate);
      void UpdateStatusBarWithScale(double CurrentScale);
      void UpdateStatusBarWithROI(long OffsetX, long OffsetY, long SizeX, long SizeY);
      void UpdateStatusBarWithMousePosition(long DispX, long DispY, double BufX, double BufY);
      void UpdateContentSize(long SizeX, long SizeY);

   private:
      MdispQtView* m_View;
      bool m_Ready;
      QLabel* m_FramerateIndicator;
      QLabel* m_ScaleIndicator;
      QLabel* m_ROIIndicator;
      QLabel* m_MouseIndicator;
   };

#endif
