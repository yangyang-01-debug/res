#include "widget.h"
#include "logindialog.h"
#include "basicwindow.h"
#include "firstscreen.h"
#include "chooselevelwidget.h"
#include "form.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
   LoginDialog w;
//    ChooseLevelWidget w;
//    BasicWindow w;
//    FirstScreen w;
//    Form w;
    w.show();
    return a.exec();
}
