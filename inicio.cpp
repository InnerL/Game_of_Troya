#include "inicio.h"
#include "qapplication.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "mapa3.h"

Inicio::Inicio(QWidget *parent)
    : QWidget(parent)
{

    // Configuración del layout y los widgets
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/inicio.png")); // Cambia la ruta a la imagen de inicio
    backgroundLabel->setAlignment(Qt::AlignCenter);

    iniciarButton = new QPushButton("Iniciar", this);
    salirButton = new QPushButton("Salir", this);

    buttonLayout->addWidget(iniciarButton);
    buttonLayout->addWidget(salirButton);

    mainLayout->addWidget(backgroundLabel);
    mainLayout->addLayout(buttonLayout);



    connect(iniciarButton,&QPushButton::clicked , this,[&](){
        iniciarClicked();
    });

    connect(salirButton,&QPushButton::clicked, this, &QApplication::quit);

    setLayout(mainLayout);
}

void Inicio::iniciarClicked()
{
/*
    MainWindow *w = new MainWindow;
    w->createScene1();
    //w->showFullScreen();
    w->show();
    this->close();

    Mapa2 *mapa2 = new Mapa2();
    mapa2->showFullScreen();
    this->close();
*/
    Mapa3 *mapa3 = new Mapa3();
    mapa3->showFullScreen();
    this->close();

}


