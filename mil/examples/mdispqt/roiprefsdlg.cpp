#include "roiprefsdlg.h"
#include "ui_roiprefsdlg.h"
#include "mdispqtview.h"

#include <QColorDialog>

RoiPrefsDlg::RoiPrefsDlg(QWidget *parent, MIL_ID MilDisplay) :
    QDialog(parent),
    ui(new Ui::RoiPrefsDlg),
    m_MilDisplay(MilDisplay)
{
   QPalette palette;

   ui->setupUi(this);

   MIL_INT linecolor = MdispInquire(m_MilDisplay, M_ROI_LINE_COLOR, M_NULL);
   MIL_INT anchorcolor= MdispInquire(m_MilDisplay, M_ROI_HANDLE_COLOR, M_NULL);

   m_LineColor.setRgb(M_RGB888_r(linecolor),
                      M_RGB888_g(linecolor),
                      M_RGB888_b(linecolor));

   m_AnchorColor.setRgb(M_RGB888_r(anchorcolor),
                        M_RGB888_g(anchorcolor),
                        M_RGB888_b(anchorcolor));

   palette.setColor(ui->RoiLineButton->backgroundRole(), m_LineColor);
   ui->RoiLineButton->setPalette(palette);
   ui->RoiLineButton->setAutoFillBackground(true);
   ui->RoiLineButton->setFocusPolicy(Qt::NoFocus);

   ui->RoiHandlesButton->setPalette(QPalette(m_AnchorColor));
   ui->RoiHandlesButton->setAutoFillBackground(true);
   ui->RoiHandlesButton->setFocusPolicy(Qt::NoFocus);

   connect(ui->RoiOkButton, SIGNAL(clicked()), SLOT(close()));

}

RoiPrefsDlg::~RoiPrefsDlg()
{
    delete ui;
}

void RoiPrefsDlg::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void RoiPrefsDlg::on_RoiLineButton_clicked()
{
   QColor c = QColorDialog::getColor( ui->RoiLineButton->palette().background().color(), this );
   if ( c.isValid() )
      {
      m_LineColor = c;
      ui->RoiLineButton->setPalette(QPalette(m_LineColor));
      MIL_INT linecolor = M_RGB888(c.red(),c.green(),c.blue());
      MdispControl(m_MilDisplay, M_ROI_LINE_COLOR, linecolor);
      MdispControl(m_MilDisplay, M_UPDATE, M_NULL);
      }
}

void RoiPrefsDlg::on_RoiHandlesButton_clicked()
{
   QColor c = QColorDialog::getColor( ui->RoiHandlesButton->palette().background().color(), this );
   if ( c.isValid() )
      {
      m_AnchorColor = c;
      ui->RoiHandlesButton->setPalette(QPalette(m_AnchorColor));
      MIL_INT anchorcolor = M_RGB888(c.red(),c.green(),c.blue());
      MdispControl(m_MilDisplay, M_ROI_HANDLE_COLOR, anchorcolor);
      MdispControl(m_MilDisplay, M_UPDATE, M_NULL);
      }
}

