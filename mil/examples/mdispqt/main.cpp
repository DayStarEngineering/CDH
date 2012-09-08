#include <QtGui/QApplication>
#include "mainframe.h"
#include "mdispqtapp.h"
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
   XInitThreads();
   MdispQtApp app( argc, argv );
   return app.exec();

}
