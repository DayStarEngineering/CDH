#ifndef MDISPWINDOWQT_H
#define MDISPWINDOWQT_H

#include <mil.h>
#include <QMainWindow>

class PaintArea : public QWidget
   {
   Q_OBJECT

   public:
      PaintArea(QWidget* parent = 0);

      void startMil();

      virtual QSize sizeHint() const;

      WId UserWindowHandle() const { return m_UserWindowHandle;} 
  
   protected:
      virtual bool event(QEvent* e);

   private:
      WId    m_UserWindowHandle;
   };

class MilWindow : public QMainWindow
   {
   Q_OBJECT

   public:
      MilWindow();
      QToolBar* ToolBar() const { return m_Tools;}

   public slots:
      void start();

   private:
      PaintArea* m_PaintArea;
      QToolBar *m_Tools;
   };

#endif // MDISPWINDOWQT_H
