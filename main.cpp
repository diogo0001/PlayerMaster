#include "playermaster.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerMaster w;
    w.show();

    return a.exec();
}
