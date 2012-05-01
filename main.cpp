#include <QtGui/QApplication>
#include "pongclient.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PongClient w;
    w.show();

    return a.exec();
}
