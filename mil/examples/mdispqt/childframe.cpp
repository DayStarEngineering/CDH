#include "childframe.h"
#include "mdispqtview.h"

#include <QtGui>

ChildFrame::ChildFrame( QWidget* parent )
   : QMainWindow(parent)
   {
   m_Ready = false;
   setAttribute(Qt::WA_DeleteOnClose);
   setWindowIcon(QIcon(":/images/imaging.png"));

   // create the view and set it's parent
   m_View = new MdispQtView(this);
   setWindowTitle(m_View->filename());
   
   //vbox->addWidget(m_View);
   //setLayout(vbox);
   //setCentralWidget(m_View);
   setCentralWidget(m_View->ScrollArea());

   m_FramerateIndicator = new QLabel( statusBar() );
   statusBar()->addWidget(m_FramerateIndicator);

   m_ScaleIndicator = new QLabel( statusBar() );
   statusBar()->addWidget(m_ScaleIndicator);

   m_ROIIndicator = new QLabel ( statusBar());
   statusBar()->addWidget(m_ROIIndicator);
   
   m_MouseIndicator = new QLabel ( statusBar());
   statusBar()->addWidget(m_MouseIndicator);

   UpdateStatusBarWithFrameRate(0.0);
   UpdateStatusBarWithScale(1.0);
   UpdateStatusBarWithROI(0,0,0,0);
   UpdateStatusBarWithMousePosition(0, 0, 0.0, 0.0);

   connect( view(), SIGNAL(zoomFactorChanged(double)),   SLOT(UpdateStatusBarWithScale(double))     );
   connect( view(), SIGNAL(frameRateChanged(double)),    SLOT(UpdateStatusBarWithFrameRate(double)) );
   connect( view(), SIGNAL(filenameChanged(const QString&)), SLOT(setWindowTitle(const QString&))           );
   connect( view(), SIGNAL(roiPositionChanged(long, long, long, long)), SLOT(UpdateStatusBarWithROI(long, long, long, long)));
   connect( view(), SIGNAL(mousePositionChanged(long, long, double, double)), SLOT(UpdateStatusBarWithMousePosition(long, long, double, double)));
   connect( view(), SIGNAL(sizeChanged(long, long)), SLOT(UpdateContentSize(long, long)));
   connect( view(), SIGNAL(filenameChanged(const QString& )), SLOT(setWindowTitle(QString)));

   }

MdispQtView* ChildFrame::view()
   {
   return m_View;
   }

void ChildFrame::closeEvent( QCloseEvent* e )
   {
   if ( view()->close() )
      {
      e->accept();
      }
   }

void ChildFrame::paintEvent( QPaintEvent* /*e*/ )
   {
   if (isVisible() && m_View && !m_Ready)
      {
      m_Ready = true;
      m_View->SelectWindow();
      }
   }

////////////////////////////////////////////////////////////////////////
// MIL: Used to update status bar with frame rate
////////////////////////////////////////////////////////////////////////
void ChildFrame::UpdateStatusBarWithFrameRate(double CurrentRate)
   {
   QString strCurrentRate = tr("%1 fps").arg( CurrentRate, 0, 'f', 2 );
   m_FramerateIndicator->setText(strCurrentRate);
   }

////////////////////////////////////////////////////////////////////////
// MIL: Used to update status bar with zoom factor
////////////////////////////////////////////////////////////////////////
void ChildFrame::UpdateStatusBarWithScale(double CurrentScale)
   {
   QString strCurrentScale = QString::number( CurrentScale, 'f', 4 );
   m_ScaleIndicator->setText(strCurrentScale);
   }

////////////////////////////////////////////////////////////////////////
// MIL: Used to update status bar with ROI Position
////////////////////////////////////////////////////////////////////////
void ChildFrame::UpdateStatusBarWithROI(long OffsetX, long OffsetY, long SizeX, long SizeY)
   {
   long TotalX = OffsetX + SizeX;
   long TotalY = OffsetY + SizeY;
   QString strCurrentROI;
   
   if(!OffsetX && !OffsetY && !SizeX && !SizeY)
      {
      strCurrentROI =tr("No ROI Set");
      m_ROIIndicator->setText(strCurrentROI);
      }
   else
      {
      strCurrentROI=tr("ROI:(%1,%2)->(%3,%4)").arg(OffsetX,3).arg(OffsetY,3).arg(TotalX,3).arg(TotalY,3);
      m_ROIIndicator->setText(strCurrentROI);
      }
   
   }

////////////////////////////////////////////////////////////////////////
// MIL: Used to update status bar with Mouse Position
////////////////////////////////////////////////////////////////////////
void ChildFrame::UpdateStatusBarWithMousePosition(long DispX, long DispY, double BufX, double BufY)
   {
   QString strCurrentMousePosition;

   strCurrentMousePosition=tr("M:(%1,%2)->(%3,%4)").arg(DispX,3).arg(DispY,3).arg(BufX, 0,'f',2).arg(BufY, 0,'f',2);
   m_MouseIndicator->setText(strCurrentMousePosition);

   }

QSize ChildFrame::sizeHint() const
   {
   if(m_View)
      return m_View->sizeHint();
   else
      return QSize(300, 200);
   }

void ChildFrame::UpdateContentSize(long SizeX, long SizeY)
   {
   resize(SizeX, SizeY + statusBar()->height());
   }


