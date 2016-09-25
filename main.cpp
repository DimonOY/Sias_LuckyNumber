#include "widget.h"
#include "mylcd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    //MyLCD *mylcd = new MyLCD;

    //mylcd->show();
    w.show();

    return a.exec();
}
