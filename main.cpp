#include <QtGui/QApplication>
#include "btccm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    btccm w;
    w.show();

    return a.exec();
}
