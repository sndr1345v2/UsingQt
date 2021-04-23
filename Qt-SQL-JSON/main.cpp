#include "principal.h"
#include "menu_dialog.h"
#include <qdebug.h>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Principal ventana;

    ventana.comenzar();
    return a.exec();


}


