#include "osgqt.h"

#include "QtOsgView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    osgqt w;
    w.show();
    return a.exec();
}
