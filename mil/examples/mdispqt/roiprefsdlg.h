#ifndef ROIPREFSDLG_H
#define ROIPREFSDLG_H

#include <QDialog>
#include <mil.h>

namespace Ui {
    class RoiPrefsDlg;
}

class RoiPrefsDlg : public QDialog {
    Q_OBJECT
public:
    RoiPrefsDlg(QWidget *parent = 0, MIL_ID MilDisplay = M_NULL);
    ~RoiPrefsDlg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::RoiPrefsDlg *ui;
    QColor m_LineColor;
    QColor m_AnchorColor;
    MIL_ID m_MilDisplay;

private slots:
    void on_RoiHandlesButton_clicked();
    void on_RoiLineButton_clicked();


};

#endif // ROIPREFSDLG_H
