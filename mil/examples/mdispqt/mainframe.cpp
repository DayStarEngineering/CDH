#include "mainframe.h"
#include "ui_mainframe.h"
#include "aboutbox.h"
#include "roiprefsdlg.h"
#include "childframe.h"
#include "mdispqtview.h"
#include "mdispqtapp.h"

#include <QWorkspace>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);
    m_ViewModeComboBox = new QComboBox;
    m_ViewModeComboBox->addItem(tr("M_DEFAULT"),     VIEW_MODE_DEFAULT);
    m_ViewModeComboBox->addItem(tr("M_TRANSPARENT"), VIEW_MODE_TRANSPARENT);
    m_ViewModeComboBox->addItem(tr("M_AUTO_SCALE"),  VIEW_MODE_AUTO_SCALE);
    m_ViewModeComboBox->addItem(tr("M_MULTI_BYTES"), VIEW_MODE_MULTI_BYTES);
    m_ViewModeComboBox->addItem(tr("M_BIT_SHIFT:2"), VIEW_MODE_BIT_SHIFT2);
    m_ViewModeComboBox->addItem(tr("M_BIT_SHIFT:4"), VIEW_MODE_BIT_SHIFT4);
    m_ViewModeComboBox->addItem(tr("M_BIT_SHIFT:8"), VIEW_MODE_BIT_SHIFT8);
    ui->DispToolBar->addWidget(m_ViewModeComboBox);

    m_Workspace = new QWorkspace;
    m_Workspace->setScrollBarsEnabled(true);
    setCentralWidget(m_Workspace);
    setAttribute(Qt::WA_DeleteOnClose);

    connect( ui->actionExit,   SIGNAL(triggered()), qApp, SLOT(closeAllWindows()) );
    connect( ui->menuHelp,    SIGNAL(aboutToShow()), this, SLOT(windowMenuAboutToShow()) );
    connect( ui->action_Cascade, SIGNAL(triggered()), m_Workspace, SLOT(cascade()) );
    connect( ui->action_Tile, SIGNAL(triggered()), m_Workspace, SLOT(tile()) );
    connect( m_Workspace, SIGNAL(windowActivated(QWidget*)), this, SLOT(windowActivated(QWidget*)) );
    m_WindowMapper = new QSignalMapper(this);
    connect(m_WindowMapper, SIGNAL(mapped(QWidget *)),  this, SLOT(windowMenuActivated(QWidget *)));
    connect(m_ViewModeComboBox, SIGNAL(activated(int)), this, SLOT(ViewModeChanged(int)));


    updateActions(NULL);
}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

ChildFrame* MainFrame::activeChild()
   {
   return qobject_cast<ChildFrame *>(m_Workspace->activeWindow());
   }

ChildFrame *MainFrame::CreateChildFrame()
   {
   ChildFrame* cf = new ChildFrame;
   m_Workspace->addWindow(cf);
   // to add actions
   return cf;
   }

//////////////////////////////////////////
// Action Handler
void MainFrame::on_actionAbout_triggered()
{
   AboutBox about(this);
   about.exec();
}



void MainFrame::closeEvent( QCloseEvent* e )
   {
   m_Workspace->closeAllWindows();
   if(activeChild())
      e->ignore();
   else
      e->accept();
   }

void MainFrame::on_actionNew_triggered()
{
   ChildFrame* cf = CreateChildFrame();
   if ( !cf->view()->newDoc() )
   {
      QMessageBox::warning( this, tr("MdispQt"),
                            tr("Could not create new document."),
                            QMessageBox::Ok | QMessageBox::Default,
                            QMessageBox::NoButton );
      cf->close();
   }
   else
   {
      cf->show();
   }

}

void MainFrame::on_actionOpen_triggered()
{
   QString fn = QFileDialog::getOpenFileName( this,
                                              tr("Open File"),
                                              tr("Image Files (*.mim;*.bmp;*.tif;*.jpg;*.jp2;*.raw)"));
   if ( !fn.isEmpty() )
   {
      ChildFrame* cf = CreateChildFrame();
      if ( !cf->view()->load(fn) )
      {
         QMessageBox::warning( this, tr("MdispQt"),
                               tr("Could not load image from \"%1\".").arg(fn),
                               QMessageBox::Ok | QMessageBox::Default,
                               QMessageBox::NoButton );
         cf->close();
      }
      else
      {
         cf->show();
      }
   }
}

void MainFrame::on_actionSave_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->view()->save();
   }
}

void MainFrame::on_actionSaveAs_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->view()->saveAs();
   }
}

void MainFrame::on_actionSaveRoiAs_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->view()->saveROIAs();
   }
}

void MainFrame::on_actionClose_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->close();
   }
}

void MainFrame::on_actionViewStdToolbar_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->statusBar()->setShown(on);
   }
   else
   {
      statusBar()->setShown(on);
   }
}


void MainFrame::on_actionGrabStart_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->view()->GrabStart();
      updateActions(cf);
   }
}

void MainFrame::on_actionGrabStop_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
   {
      cf->view()->GrabStop();
      updateActions(cf);
   }
}


void MainFrame::on_actionROIDefine_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ROIDefine(on);
      updateActions(cf);
      }
}


void MainFrame::on_actionROIShow_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ROIShow(on);
      updateActions(cf);
      }
}

void MainFrame::on_actionROIPreferences_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      RoiPrefsDlg dlg(this, cf->view()->MilDisplay());
      dlg.exec();
   }
}

void MainFrame::on_actionOverlay_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->Overlay(on);
      updateActions(cf);
      }
}

void MainFrame::on_actionRestrictedCursor_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->RestrictCursor(on);
      updateActions(cf);
      }
}


void MainFrame::on_actionX11Annotation_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->X11Annotations(on);
      updateActions(cf);
      }
}


void MainFrame::on_actionGraphicsAnnotations_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->GraphicsAnnotations(on);
      updateActions(cf);
      }
}
void MainFrame::on_actionZoomIn_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ZoomIn();
      updateActions(cf);
      }
}


void MainFrame::on_actionZoomOut_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ZoomOut();
      updateActions(cf);
      }
}



void MainFrame::on_actionNoZoom_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->NoZoom();
      updateActions(cf);
      }
}


void MainFrame::on_actionFillDisplay_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->FillDisplay(on);
      updateActions(cf);
      }
}


void MainFrame::on_actionIntDefault_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeInterpolationMode(M_DEFAULT);
      updateActions(cf);
      }
}

void MainFrame::on_actionIntNearest_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeInterpolationMode(M_NEAREST_NEIGHBOR);
      updateActions(cf);
      }
}


void MainFrame::on_actionIntFast_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeInterpolationMode(M_FAST);
      updateActions(cf);
      }
}


void MainFrame::on_actionNoTearing_triggered(bool on)
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->NoTearing(on);
      updateActions(cf);
      }
}

void MainFrame::ViewModeChanged(int Mode)
{
    switch(Mode)
    {
    case VIEW_MODE_DEFAULT:
        on_actionViewDefault_triggered();
        break;

    case VIEW_MODE_TRANSPARENT:
        on_actionViewTransparent_triggered();
        break;

    case VIEW_MODE_AUTO_SCALE:
        on_actionViewAutoScale_triggered();
        break;

    case VIEW_MODE_MULTI_BYTES:
        on_actionVieewMultiBytes_triggered();
        break;

    case VIEW_MODE_BIT_SHIFT2:
        on_actionViewBitShift2_triggered();
        break;

    case VIEW_MODE_BIT_SHIFT4:
        on_actionViewBitShift4_triggered();
        break;

    case VIEW_MODE_BIT_SHIFT8:
        on_actionViewBitShift8_triggered();
        break;

    default:
        on_actionViewDefault_triggered();
        break;
    }
}

void MainFrame::on_actionViewDefault_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_DEFAULT);
      updateActions(cf);
      }
}

void MainFrame::on_actionViewTransparent_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_TRANSPARENT);
      updateActions(cf);
      }
}

void MainFrame::on_actionViewAutoScale_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_AUTO_SCALE);
      updateActions(cf);
      }
}

void MainFrame::on_actionVieewMultiBytes_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_MULTI_BYTES);
      updateActions(cf);
      }
}

void MainFrame::on_actionViewBitShift2_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_BIT_SHIFT, 2);
      updateActions(cf);
      }
}

void MainFrame::on_actionViewBitShift4_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_BIT_SHIFT, 4);
      updateActions(cf);
      }
}

void MainFrame::on_actionViewBitShift8_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeViewMode(M_BIT_SHIFT, 8);
      updateActions(cf);
      }
}


void MainFrame::on_actionDMILASyncDisable_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(false,M_DISABLE);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILASync1_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,1);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILASync5_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,5);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILASync10_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,10);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILASync15_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,15);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILASync30_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,30);
      updateActions(cf);
      }
}


void MainFrame::on_actionDMILASyncMax_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeAsynchronousMode(true,M_INFINITE);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILCompressNone_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeCompressionType(M_NULL);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILCompressLossy_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeCompressionType(M_JPEG_LOSSY);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILCompressLossless_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeCompressionType(M_JPEG_LOSSLESS);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor60_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(60);
      updateActions(cf);
      }
}


void MainFrame::on_actionDMILFactor70_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(70);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor75_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(70);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor80_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(80);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor82_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(82);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor85_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(85);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor87_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(87);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor90_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(90);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor92_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(92);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor95_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(95);
      updateActions(cf);
      }
}

void MainFrame::on_actionDMILFactor99_triggered()
{
   ChildFrame* cf = activeChild();
   if (cf)
      {
      cf->view()->ChangeQFactor(99);
      updateActions(cf);
      }
}

void MainFrame::windowMenuAboutToShow()
   {
   ui->menuHelp->clear();
   ui->menuHelp->addAction(ui->action_Cascade);
   ui->menuHelp->addAction(ui->action_Tile);
   if ( m_Workspace->windowList().isEmpty() )
      {
      ui->action_Cascade->setEnabled(false);
      ui->action_Tile->setEnabled(false);
      }
   else
      {
      ui->action_Cascade->setEnabled(true);
      ui->action_Tile->setEnabled(true);
      }
    ui->menuHelp->addSeparator();

    QWidgetList windows = m_Workspace->windowList( QWorkspace::CreationOrder );
    for ( int i=0; i<windows.size(); i++ )
       {
       QWidget* window = windows[i];
       ChildFrame* cf = (ChildFrame*) window;
       QString text;
       if(cf)
          text = tr("%1 %2").arg(i+1).arg(cf->view()->filename());
       else
          text = tr("%1 Image").arg(i+1);

       QAction *action = ui->menuHelp->addAction(text);
       
       //connect(action,SIGNAL(triggered()), this, SLOT(windowMenuActivated(int)));
       action->setCheckable(true);
       action->setChecked(m_Workspace->activeWindow() == window);
       connect(action, SIGNAL(triggered()), m_WindowMapper, SLOT(map()));
       m_WindowMapper->setMapping(action, windows.at(i));

       }
   }

void MainFrame::windowMenuActivated( QWidget* w )
   {
   if (w)
      {
      w->showNormal();
      }
   w->setFocus();
   }

void MainFrame::windowActivated( QWidget* w )
   {
    updateActions((ChildFrame *)w);
   }


void MainFrame::updateActions(ChildFrame *cf)
{
   m_ViewModeComboBox->setEnabled(cf);
   ui->actionClose->setEnabled(cf);
   ui->actionSave->setEnabled(cf);
   ui->actionSaveAs->setEnabled(cf);
   ui->actionSaveRoiAs->setEnabled(cf);


   ui->actionOverlay->setEnabled(cf);
   ui->actionX11Annotation->setEnabled(cf);
   ui->actionGraphicsAnnotations->setEnabled(cf);
   ui->menuInterpolation_Mode->setEnabled(cf);
   ui->actionIntNearest->setEnabled(cf);
   ui->actionIntFast->setEnabled(cf);
   ui->menuView_Mode->setEnabled(cf);
   ui->actionViewDefault->setEnabled(cf);
   ui->actionViewTransparent->setEnabled(cf);
   ui->actionViewAutoScale->setEnabled(cf);
   ui->actionVieewMultiBytes->setEnabled(cf);
   ui->actionViewBitShift2->setEnabled(cf);
   ui->actionViewBitShift4->setEnabled(cf);
   ui->actionViewBitShift8->setEnabled(cf);

   if (cf)
   {
      MdispQtApp* app = (MdispQtApp*) qApp;
      MdispQtView* view = cf->view();

      ui->actionGrabStart->setEnabled( app->m_numberOfDigitizer != 0
                                       && !(app->m_pGrabView && app->m_isGrabStarted) );
      ui->actionGrabStop->setEnabled( app->m_pGrabView && app->m_isGrabStarted );

      ui->actionOverlay->setChecked( cf->view()->IsOverlayEnabled() );
      ui->actionX11Annotation->setChecked( cf->view()->IsX11AnnotationsEnabled() );
      ui->actionGraphicsAnnotations->setChecked( cf->view()->IsGraphicsAnnotationsEnabled() );
      ui->actionFillDisplay->setChecked( cf->view()->IsFillDisplayEnabled() );

      if(cf->view()->IsROISupported() && 
         cf->view()->IsWindowed()     &&
         !cf->view()->IsFillDisplayEnabled())
      {
         ui->actionSaveRoiAs->setEnabled(true);
         ui->actionROIDefine->setEnabled(true);
         ui->actionROIShow->setEnabled(true);
         ui->actionROIPreferences->setEnabled(true);
         ui->actionROIDefine->setChecked(cf->view()->IsInROIDefineMode());
         ui->actionROIShow->setChecked(cf->view()->IsInROIShowMode());
      }
      else
      {
         ui->actionSaveRoiAs->setEnabled(false);
         ui->actionROIDefine->setEnabled(false);
         ui->actionROIShow->setEnabled(false);
         ui->actionROIPreferences->setEnabled(false);
      }

      if ( view->IsFillDisplayEnabled() || cf->view()->IsExclusive())
      {
         ui->actionNoZoom->setEnabled(false);
         ui->actionZoomIn->setEnabled(false);
         ui->actionZoomOut->setEnabled(false);
      }
      else
      {
         ui->actionZoomIn->setEnabled( cf->view()->CurrentZoomFactor() < 16.0 );
         ui->actionZoomOut->setEnabled( cf->view()->CurrentZoomFactor() > 1.0/16.0 );
         ui->actionNoZoom->setEnabled(true);
      }
      ui->actionFillDisplay->setEnabled( ((cf->view()->CurrentZoomFactor() == 1.0 ) && (!cf->view()->IsExclusive())));

      if(cf->view()->IsExclusive())
      {
         ui->actionRestrictedCursor->setEnabled(true);
         ui->actionRestrictedCursor->setChecked(view->CurrentRestrictCursor() == M_ENABLE);
      }
      else
      {
         ui->actionRestrictedCursor->setEnabled(false);
      }
      ui->actionIntNearest->setChecked( view->CurrentInterpolationMode() == M_NEAREST_NEIGHBOR );
      ui->actionIntFast->setChecked( view->CurrentInterpolationMode() == M_FAST );
      ui->actionIntDefault->setChecked( view->CurrentInterpolationMode() == M_DEFAULT );

      ui->actionViewDefault->setChecked(view->CurrentViewMode()==M_DEFAULT);
      ui->actionViewTransparent->setChecked(view->CurrentViewMode()==M_TRANSPARENT);
      ui->actionViewAutoScale->setChecked(view->CurrentViewMode()==M_AUTO_SCALE);
      ui->actionVieewMultiBytes->setChecked(view->CurrentViewMode()==M_MULTI_BYTES);
      ui->actionViewBitShift2->setChecked((view->CurrentViewMode()==M_BIT_SHIFT)&& (view->CurrentShiftValue()==2));
      ui->actionViewBitShift4->setChecked((view->CurrentViewMode()==M_BIT_SHIFT)&& (view->CurrentShiftValue()==4));
      ui->actionViewBitShift8->setChecked((view->CurrentViewMode()==M_BIT_SHIFT)&& (view->CurrentShiftValue()==8));
      int ViewValue = VIEW_MODE_DEFAULT;
      switch(view->CurrentViewMode())
      {
      case M_DEFAULT:
          ViewValue = VIEW_MODE_DEFAULT;
          break;
      case M_TRANSPARENT:
          ViewValue = VIEW_MODE_TRANSPARENT;
          break;
      case M_AUTO_SCALE:
          ViewValue = VIEW_MODE_AUTO_SCALE;
          break;
      case M_MULTI_BYTES:
          ViewValue = VIEW_MODE_MULTI_BYTES;
          break;
      case M_BIT_SHIFT:
          {
              if(view->CurrentShiftValue() == 2)
                  ViewValue = VIEW_MODE_BIT_SHIFT2;
              else if(view->CurrentShiftValue() == 4)
                  ViewValue = VIEW_MODE_BIT_SHIFT4;
              else if(view->CurrentShiftValue() == 8)
                  ViewValue = VIEW_MODE_BIT_SHIFT8;
          }
          break;
      }
      m_ViewModeComboBox->setCurrentIndex(ViewValue);
      if(view->IsNetworkedSystem())
      {
         ui->menuASynchronous_mode->setEnabled(true);
         ui->menuCompression->setEnabled(true);
         ui->menuQFactor->setEnabled(true);
         if(!view->IsInAsynchronousMode())
            ui->actionDMILASyncDisable->setChecked(true);
         else
         {
            ui->actionDMILASync1->setChecked(view->AsynchronousFrameRate()==1);
            ui->actionDMILASync5->setChecked(view->AsynchronousFrameRate()==5);
            ui->actionDMILASync10->setChecked(view->AsynchronousFrameRate()==10);
            ui->actionDMILASync15->setChecked(view->AsynchronousFrameRate()==15);
            ui->actionDMILASync30->setChecked(view->AsynchronousFrameRate()==30);
            ui->actionDMILASyncMax->setChecked(view->AsynchronousFrameRate()==M_INFINITE);
         }
         ui->actionDMILCompressNone->setChecked(view->CompressionType()==M_NULL);
         ui->actionDMILCompressLossy->setChecked(view->CompressionType()==M_JPEG_LOSSY);
         ui->actionDMILCompressLossless->setChecked(view->CompressionType()==M_JPEG_LOSSLESS);

         ui->actionDMILFactor60->setChecked(view->QFactor()==60);
         ui->actionDMILFactor70->setChecked(view->QFactor()==70);
         ui->actionDMILFactor75->setChecked(view->QFactor()==75);
         ui->actionDMILFactor80->setChecked(view->QFactor()==80);
         ui->actionDMILFactor82->setChecked(view->QFactor()==82);
         ui->actionDMILFactor85->setChecked(view->QFactor()==85);
         ui->actionDMILFactor87->setChecked(view->QFactor()==87);
         ui->actionDMILFactor90->setChecked(view->QFactor()==90);
         ui->actionDMILFactor92->setChecked(view->QFactor()==92);
         ui->actionDMILFactor95->setChecked(view->QFactor()==95);
         ui->actionDMILFactor99->setChecked(view->QFactor()==99);

      }
      else
      {
         ui->menuASynchronous_mode->setEnabled(false);
         ui->menuCompression->setEnabled(false);
         ui->menuQFactor->setEnabled(false);
      }

      if ( view->CurrentZoomFactor() == 1.0 )
      {
         ui->actionNoTearing->setEnabled(true);
         if ( view->IsNoTearingEnabled() )
         {
            ui->actionNoTearing->setChecked(true);
            ui->menuInterpolation_Mode->setEnabled(false);
         }
      }
      else
      {
         ui->actionNoTearing->setEnabled(false);
         ui->actionNoTearing->setChecked(false);
      }

      ui->actionViewStatusBar->setChecked( cf->statusBar()->isVisible() );
   }
   else
   {
      ui->actionGrabStart->setEnabled(false);
      ui->actionGrabStop->setEnabled(false);

      ui->actionOverlay->setChecked(false);
      ui->actionX11Annotation->setChecked(false);
      ui->actionGraphicsAnnotations->setChecked(false);
      ui->actionZoomIn->setEnabled(false);
      ui->actionZoomOut->setEnabled(false);
      ui->actionNoZoom->setEnabled(false);
      ui->actionRestrictedCursor->setEnabled(false);
      ui->actionFillDisplay->setEnabled(false);
      ui->actionIntNearest->setChecked(false);
      ui->actionIntFast->setChecked(false);
      ui->actionNoTearing->setEnabled(false);
      ui->actionROIShow->setEnabled(false);
      ui->actionROIDefine->setEnabled(false);
      ui->actionViewStatusBar->setChecked( statusBar()->isVisible() );
      ui->menuASynchronous_mode->setEnabled(false);
      ui->menuCompression->setEnabled(false);
      ui->menuQFactor->setEnabled(false);

   }
}



