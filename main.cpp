#include "mainwindow.h"
#include "inicio.h"
#include "mapa3.h"
#include "mapa2.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Inicio inicio;
    inicio.show();

/*

    Mapa2 *mapa2 = new Mapa2();
    mapa2->show();

    Mapa3 *mapa3 = new Mapa3();
    mapa3->show();



*/
    return a.exec();
}
