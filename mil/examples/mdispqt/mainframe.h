#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <QComboBox>
#include "childframe.h"

class QWorkspace;
class QSignalMapper;

enum {
   VIEW_MODE_DEFAULT,
   VIEW_MODE_TRANSPARENT,
   VIEW_MODE_AUTO_SCALE,
   VIEW_MODE_MULTI_BYTES,
   VIEW_MODE_BIT_SHIFT2,
   VIEW_MODE_BIT_SHIFT4,
   VIEW_MODE_BIT_SHIFT8,
};

namespace Ui {
    class MainFrame;
}

class MainFrame : public QMainWindow {
    Q_OBJECT
public:
    MainFrame(QWidget *parent = 0);
    ~MainFrame();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *);

private:
    Ui::MainFrame *ui;
    QWorkspace *m_Workspace;
    QSignalMapper *m_WindowMapper;
    QComboBox *m_ViewModeComboBox;

    ChildFrame* CreateChildFrame();
    ChildFrame* activeChild();
    void updateActions(ChildFrame *cf);

private slots:
    void on_actionGraphicsAnnotations_triggered(bool checked);
    void on_actionDMILFactor60_triggered();
    void on_actionDMILFactor70_triggered();
    void on_actionDMILFactor75_triggered();
    void on_actionDMILFactor80_triggered();
    void on_actionDMILFactor82_triggered();
    void on_actionDMILFactor85_triggered();
    void on_actionDMILFactor87_triggered();
    void on_actionDMILFactor90_triggered();
    void on_actionDMILFactor92_triggered();
    void on_actionDMILFactor95_triggered();
    void on_actionDMILFactor99_triggered();
    void on_actionDMILCompressLossless_triggered();
    void on_actionDMILCompressLossy_triggered();
    void on_actionDMILCompressNone_triggered();
    void on_actionDMILASyncMax_triggered();
    void on_actionDMILASync30_triggered();
    void on_actionDMILASync15_triggered();
    void on_actionDMILASync10_triggered();
    void on_actionDMILASync5_triggered();
    void on_actionDMILASync1_triggered();
    void on_actionDMILASyncDisable_triggered();
    void on_actionViewBitShift8_triggered();
    void on_actionViewBitShift4_triggered();
    void on_actionViewBitShift2_triggered();
    void on_actionVieewMultiBytes_triggered();
    void on_actionViewAutoScale_triggered();
    void on_actionViewTransparent_triggered();
    void on_actionViewDefault_triggered();
    void on_actionNoTearing_triggered(bool checked);
    void on_actionIntFast_triggered();
    void on_actionIntNearest_triggered();
    void on_actionIntDefault_triggered();
    void on_actionFillDisplay_triggered(bool checked);
    void on_actionNoZoom_triggered();
    void on_actionZoomOut_triggered();
    void on_actionZoomIn_triggered();
    void on_actionX11Annotation_triggered(bool checked);
    void on_actionRestrictedCursor_triggered(bool checked);
    void on_actionROIShow_triggered(bool checked);
    void on_actionROIDefine_triggered(bool checked);
    void on_actionGrabStop_triggered();
    void on_actionGrabStart_triggered();
    void on_actionViewStdToolbar_triggered(bool checked);
    void on_actionClose_triggered();
    void on_actionSaveRoiAs_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_triggered();
    void on_actionOpen_triggered();
    void on_actionOverlay_triggered(bool checked);
    void on_actionNew_triggered();
    void on_actionROIPreferences_triggered();
    void on_actionAbout_triggered();
    void ViewModeChanged(int Mode);
    void windowMenuAboutToShow();
    void windowMenuActivated( QWidget* w);
    void windowActivated( QWidget* w );
 };

#endif // MAINFRAME_H
