#include "rfidmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RfidMainWindow w;
    w.show();

    return a.exec();
}
