#include "japm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JAPM w;
    w.show();
    return a.exec();
}
