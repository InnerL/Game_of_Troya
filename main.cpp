#include "mainwindow.h"
#include "inicio.h"
#include "mapa3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    Inicio inicio;


    inicio.show();
    */
    Mapa3 *mapa3 = new Mapa3();
    mapa3->showFullScreen();

    return a.exec();
}
