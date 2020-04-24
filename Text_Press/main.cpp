#include <QtGui/QApplication>
#include "fun_connect.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Fun_connect w;
    w.show();

    return a.exec();
}
